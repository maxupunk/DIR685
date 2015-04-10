#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <xmldb.h>
#include <libxmldbc.h>
#include "fcrss_parser.h"
#include "fcrss_command.h"
#include "fcrss_serialize.h"
#include "frameit_parser.h"
#include "file_tool.h"
#include "str_tool.h"
#include "rgdb_node_define.h"

FcNode *fitxml_show_node=NULL;
Net_FcNode net_node;
pthread_t tid, t2id;
pthread_mutex_t fcxml_mutex=PTHREAD_MUTEX_INITIALIZER;
char remote_host[256];

char* check_file_type(char *local_file_path, char *file_type){	
	char *tmp;
	if(img_search(local_file_path, ALL_IMAGE_TYPE)==0){
		if((file_type=(char*)get_file_type(file_type))!=NULL){
			tmp=local_file_path;
			local_file_path=(char*)sam_strcat(local_file_path, file_type);
			free(tmp);
			return local_file_path;
		}
	}
	return local_file_path;	
}	

FcNode* get_fitxmlshow_tree(){	
	FcNode *head=NULL, *tail=NULL;
	char *xml_file;	
	int flag, count;	
		
	while(1){						
		flag=get_remote_file(remote_host, "/", LOCAL_FRAMEIT_SHOW_XML);				
		if(flag==1){
			 xml_file=get_xml_strbuff(LOCAL_FRAMEIT_SHOW_XML);				 					 	
				if(xml_file!=0){					
					head=create_fcnode_tree(xml_file, LOCAL_PIC_DIR2);	
					free(xml_file);	
					count=0;
					tail=head;					
					while(tail!=NULL){																		
                        if(tail->local_file_path!=NULL) {                        	
                        	tail->local_file_path=check_file_type(tail->local_file_path, tail->file_type);  //just for frameit_server, not find the code in fcrss_server.                      	
                        	//printf("\ntail->local_file_path %s\n", tail->local_file_path);                        	
                        	count++;
                        	if(count<=PREPARE_DOWNLOAD_COUNT){                        		
	                        	while(!check_file_exist(tail->local_file_path)) {	             	                        		 
	                        		get_remote_file_v2(tail->remote_file_path, tail->local_file_path);		                        		
	                        	}	      	                        	
	                        }	                       
                        }							
						tail=tail->brother_node;								
					}						               	                    							
					return head;		
			 	}else{			 		
			 		return NULL;		
				}		 	
		}else{			
			return NULL;
		}			
	}	
}

void showtree_update(){			
	FcNode *tmp_node=NULL;				
			
	tmp_node = fitxml_show_node;					
	fitxml_show_node=get_fitxmlshow_tree();							
   	if(fitxml_show_node!=NULL){
    	if(tmp_node!=NULL) {        		        		
    		rm_cmpsubtree_file(fitxml_show_node, tmp_node);
    		delete_subtree(tmp_node);																			        	        		
    	}	              	  	        	
	}else{
		if(tmp_node!=NULL) fitxml_show_node=tmp_node;																							        	        		    	
	}						
}


void* auto_showtree_update_r(void *arg){				
	int xml_ttl; //xml update time
										
	while(1){		
		xml_ttl=fitxml_show_node->ttl+1;				
		xml_ttl=xml_ttl*60;						
		sleep(xml_ttl);																	
		printf("\n[frameit auto showtree update.........start]\n");
		pthread_mutex_lock(&fcxml_mutex);
		showtree_update();
		pthread_mutex_unlock(&fcxml_mutex);								
		printf("\n[frameit auto showtree update..........end]\n");				        							
	}		
	printf("\nauto update error\n");	
	pthread_cancel(pthread_self());	
}

void* server_cmd_handler_r(void *arg){
	int connfd;
	int cmd, cmd2;			
	
	connfd=*((int*)arg);
	pthread_detach(pthread_self());	
	recv(connfd, &cmd, sizeof(int), 0);			
	
	if(fitxml_show_node==NULL){
		cmd2=FCNODE_ISNULL;								
		send(connfd, &cmd2, sizeof(int), 0);		
	}else{				
		cmd2=FCNODE_NOTNULL;								
		send(connfd, &cmd2, sizeof(int), 0);					
		switch(cmd){					
			case CHANNEL_SHOW_GET:
				send_nodes(connfd, fitxml_show_node, net_node);	
				break;						
			default:		
				break;															
		}	
	}												
	close(connfd);		
	return NULL;
}	

void wakeup_process(){
	printf("\nrecv sigusr1, wake up process\n");
	return;
}	

void set_framechannel_info(){
	char collection_id[RGDBBUFFER_SIZE];
	
	memset(collection_id, 0 ,RGDBBUFFER_SIZE);
	xmldbc_get_wb(NULL, 0, RGDB_FRAMEIT_COLLECTIONID, collection_id, RGDBBUFFER_SIZE);			
	memset(remote_host, 0 , sizeof(remote_host));	
 	sprintf(remote_host,"%s%s", collection_id, FEEDURL); 	
 	//printf("\nremote_host=%s\n", remote_host);
}	

int main(int argc, char *argv[])     
{     	        
	socklen_t clilen;         
	struct sockaddr_un servaddr, cliaddr;			
	int listenfd, connfd, count;
	int max_ttl=900, min_ttl=120;
	
	//system("mkdir -p /tmp/fit_icon/");			
	system("rm -f /tmp/fit_icon/*.*");
	sleep(1);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGCLD, SIG_IGN);	
	//signal(SIGUSR1, &wakeup_process);								
	
	state1:
	set_framechannel_info();	
	if(strcmp(remote_host, FEEDURL)){
		if(min_ttl>=max_ttl) min_ttl=max_ttl;		
		while(((struct hostent*)gethostbyname(REMOTE_HOST))!=NULL){					
			count=0;	
			unlink(SOCKNAME2);
			fitxml_show_node=get_fitxmlshow_tree();						
			if(fitxml_show_node==NULL){									
				min_ttl=min_ttl+60;
				sleep(min_ttl);
				goto state1;				
			}													
			pthread_create(&tid, NULL, &auto_showtree_update_r, NULL);	
			listenfd = socket(AF_LOCAL, SOCK_STREAM, 0); 	  	 	
			bzero(&servaddr, sizeof(servaddr));
			servaddr.sun_family = AF_LOCAL;
			strcpy(servaddr.sun_path, SOCKNAME2);
			
			if ((bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) == -1) {
			  perror("catch - bind failed");
			  goto state1;	 
			}
			
			if ((listen(listenfd, 0)) == -1) {
			  perror("catch - listen failed");
			  goto state1;	  
			}
			printf("\nframeits_server service start\n");
			for(;;){								
				clilen=sizeof(cliaddr);
				if((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen))!=-1){						
					if(fitxml_show_node==NULL){
						printf("\nerror:fitxml_show_node==NULL, frameit_server service stop\n");												
						system("rm -f /tmp/fit_icon/*.*");		
						sleep(1);						
						pthread_cancel(tid);									
						pthread_create(&t2id, NULL, &server_cmd_handler_r, &connfd);							
						break;							
					}else{				
						pthread_create(&t2id, NULL, &server_cmd_handler_r, &connfd);		
					}	
				}	
			}
			close(connfd);	
			close(listenfd);
			goto state1;	
		}
	}		
	sleep(5);				
	goto state1;	
}

