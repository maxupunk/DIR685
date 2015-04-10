#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <xmldb.h>
#include <libxmldbc.h>
#include "fcrss_parser.h"
#include "fcrss_command.h"
#include "fcrss_serialize.h"
#include "file_tool.h"
#include "rgdb_node_define.h"

FcNode *fcxml_node=NULL, *fcxml_item_node=NULL, *fcxml_show_node=NULL;
Net_FcNode net_node;
pthread_t tid[5]={-1, -1, -1, -1, -1};
pthread_mutex_t fcxml_mutex = PTHREAD_MUTEX_INITIALIZER;
char selected_guid[512];
char remote_resetid[256], remote_channel_xml[256], remote_channellist_xml[256], remote_channelshow_xml[256];
static int register_status=0, subtree_thread_start=0, showtree_thread_start=0, tree_thread_start=0;
static int subtree_update_version=0, showtree_update_version=0;

FcNode* get_fcxml_subtree(char *guid)
{
	FcNode *son_fcnode=NULL;						
	char *xml_file;
	char xml_path[1024]; //note, this is important set!!
	int flag;
		
	memset(xml_path, 0, 1024);
	sprintf(xml_path, "%s%s", remote_channel_xml, guid);			
	while(1)
	{			
		flag=get_remote_file(REMOTE_HOST, xml_path, LOCAL_CHANNEL_XML);		
		if(flag==1)
		{
			xml_file=get_xml_strbuff(LOCAL_CHANNEL_XML);												
			if(xml_file!=0)
			{						
				son_fcnode=create_fcnode_tree(xml_file, LOCAL_CHANNELS_DIR);									
				free(xml_file);									
				return son_fcnode;			
			}else{				
				return NULL;
			}
		}					
	}
}	

void get_remain_file()
{			
	FcNode *head=fcxml_node;
				
	while(head!=NULL)
	{														        
		if(head->local_file_path!=NULL)
		{
          while(!check_file_exist(head->local_file_path)) 
          {
            	get_remote_file_v2(head->remote_file_path, head->local_file_path);																	                        
          }                    		
        }   			
		head=head->brother_node;								
	}	
}

void* get_remain_file_r(void *arg)
{				
	pthread_detach(pthread_self());
	dprintf("\n[framechannel get remain file.........start]\n");			
	//pthread_mutex_lock(&fcxml_mutex);
	get_remain_file(fcxml_node);	
	//pthread_mutex_unlock(&fcxml_mutex);
	dprintf("\n[framechannel get remain file.........end]\n");
	pthread_exit(NULL);	
	return NULL;
}


FcNode* get_fcxml_tree()
{	
	FcNode *head=NULL, *tail=NULL;
	char *xml_file;	
	int flag, count;
			
	while(1)
	{						
		flag=get_remote_file(REMOTE_HOST, remote_channellist_xml, LOCAL_CHANNEL_LIST_XML);		
		if(flag==0) return NULL;		
		xml_file=get_xml_strbuff(LOCAL_CHANNEL_LIST_XML);						 	
		if(xml_file!=0)
		{					
			head=create_fcnode_tree(xml_file, LOCAL_CHANNEL_LIST_DIR);	
			free(xml_file);	
			count=0;
			tail=head;			
			while(tail!=NULL) //just get some small icon.
			{																
		        if(tail->local_file_path!=NULL) 
		        {
		        	count++;
		        	if(count<=PREPARE_DOWNLOAD_COUNT)
		        	{
		            	while(!check_file_exist(tail->local_file_path)) 
		            	{
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
	}	
}	

FcNode* get_fcxmlshow_tree(int parser_exist_file)
{	
	FcNode *head=NULL;
	char *xml_file=NULL;	
	int flag=1;	
		
	while(1)
	{						
		if(!parser_exist_file) flag=get_remote_file(REMOTE_HOST, remote_channelshow_xml, LOCAL_CHANNEL_SHOW_XML);						
		if(flag==1)
		{
		 	xml_file=get_xml_strbuff(LOCAL_CHANNEL_SHOW_XML);		 							 	
			if(xml_file!=0){					
				head=create_fcnode_tree(xml_file, LOCAL_CHANNEL_SHOW_DIR);						
				free(xml_file);									               	                    							
				return head;		
		 	}else{			 		
		 		return NULL;		
			}		 	
		}else{			
			return NULL;
		}			
	}	
}

void showtree_update()
{			
	FcNode *tmp_node=NULL;				
			
	tmp_node = fcxml_show_node;					
	fcxml_show_node=get_fcxmlshow_tree(NOT_PARSER_EXIST_FILE);							
   	if(fcxml_show_node!=NULL)
   	{
    	if(tmp_node!=NULL) 
    	{        		        		
    		rm_cmpsubtree_file(fcxml_show_node, tmp_node);
    		delete_subtree(tmp_node);																			        	        		
    	}	              	  	        	
	}else{
		if(tmp_node!=NULL) fcxml_show_node=tmp_node;																							        	        		    	
	}						
}


void subtree_update(char *guid)
{			
	FcNode *tmp_node=NULL;				
			
	tmp_node = fcxml_item_node;					
	fcxml_item_node=get_fcxml_subtree(guid);							
   	if(fcxml_item_node!=NULL)
   	{
    	if(tmp_node!=NULL) 
    	{        		        		
    		rm_cmpsubtree_file(fcxml_item_node, tmp_node);
    		delete_subtree(tmp_node);																			        	        		
    	}	              	  	        	
	}else{
		if(tmp_node!=NULL) fcxml_item_node=tmp_node;																							        	        		    	
	}						
}

void tree_update()
{			
	FcNode *tmp_node=NULL;	
																		
	tmp_node = fcxml_node;
	fcxml_node=get_fcxml_tree();							
    if(fcxml_node!=NULL) 
    {
    	if(tmp_node!=NULL) 
    	{        		        		
    		rm_cmpsubtree_file(fcxml_node, tmp_node);
    		delete_subtree(tmp_node);																			        	        		
    	}	              	  	    	    	
	}else{
		if(tmp_node!=NULL) fcxml_node=tmp_node;															        	        		    	
	}	
}

void* auto_showtree_update_r(void *arg)
{				
	pthread_detach(pthread_self());
	int xml_ttl, wan_status=0; //xml update time
										
	while(1)
	{		
		xml_ttl=fcxml_node->ttl+1;				
		xml_ttl=xml_ttl*60;				
		sleep(xml_ttl);								
		
		if(showtree_thread_start)
		{		
			wan_status = get_wan_status();
			if(wan_status)
			{																				
				dprintf("\n[framechannel auto showtree update.........start]\n");
				pthread_mutex_lock(&fcxml_mutex);
				showtree_update();
				if(showtree_update_version > 5000) showtree_update_version=0;
				showtree_update_version++;
				pthread_mutex_unlock(&fcxml_mutex);								
				dprintf("\n[framechannel auto showtree update..........end]\n");				        							
			}	
		}	
	}		
	dprintf("\nauto update error\n");	
	pthread_exit(NULL);	
}

void* auto_subtree_update_r(void *arg)
{				
	pthread_detach(pthread_self());
	int xml_ttl, wan_status=0; //xml update time
										
	while(1)
	{		
		xml_ttl=fcxml_node->ttl+1;				
		xml_ttl=xml_ttl*60;					
		sleep(xml_ttl);		
										
		if(subtree_thread_start)
		{
			wan_status = get_wan_status();
			if(wan_status)
			{	
				dprintf("\n[framechannel auto subtree update.........start]\n");
				pthread_mutex_lock(&fcxml_mutex);		
				dprintf("\nselected_guid %s\n", selected_guid);																	
				subtree_update(selected_guid);
				if(subtree_update_version > 5000) subtree_update_version=0;
				subtree_update_version++;
				pthread_mutex_unlock(&fcxml_mutex);								
				dprintf("\n[framechannel auto subtree update..........end]\n");
			}	
		}	
	}		
	dprintf("\nauto update error\n");	
	pthread_exit(NULL);	
}

void* auto_tree_update_r(void *arg)
{				
	pthread_detach(pthread_self());
	int xml_ttl, wan_status=0; //xml update time
										
	while(1){		
		xml_ttl=fcxml_node->ttl+1;				
		xml_ttl=xml_ttl*60;								
		sleep(xml_ttl);		
										
		if(tree_thread_start)
		{			
			wan_status = get_wan_status();
			if(wan_status)
			{															
				dprintf("\n[framechannel auto update.........start]\n");
				pthread_mutex_lock(&fcxml_mutex);
				tree_update();		
				pthread_mutex_unlock(&fcxml_mutex);								
				dprintf("\n[framechannel auto update..........end]\n");				        							
			}	
		}	
	}		
	dprintf("\nauto update error\n");	
	pthread_exit(NULL);	
}

char* get_frame_id()
{
	int i, j=0;
	char mac[32], *mac2;
	
	mac2=(char*)malloc(32*sizeof(char));
	memset(mac, 0 ,32);			
	memset(mac2, 0 ,32);
	xmldbc_get_wb(NULL, 0, RGDB_INTERNET_MACADDR, mac, 32);		  					   			
	for(i=4; i<32;i++)
	{		
		if((mac[i])!=':')	mac2[j++]=mac[i];
	}			
	return mac2;
}	

void set_framechannel_info()
{
	char *frame_id, *product_id;
	
	frame_id=get_frame_id();		
	product_id=PRODUCTID;		
	memset(remote_resetid, 0 , sizeof(remote_resetid));	
 	memset(remote_channel_xml, 0, sizeof(remote_channel_xml));
 	memset(remote_channellist_xml, 0, sizeof(remote_channellist_xml)); 	 	
 	memset(remote_channelshow_xml, 0, sizeof(remote_channelshow_xml)); 	 	
 	sprintf(remote_resetid, "http://rss.framechannel.com/productId=%s/frameId=%s/resetId=true", product_id, frame_id); 	 	
 	sprintf(remote_channel_xml, "/productId=%s/frameId=%s/channelId=", product_id, frame_id);
 	sprintf(remote_channellist_xml, "/productId=%s/frameId=%s/channelList=true", product_id, frame_id);	
 	sprintf(remote_channelshow_xml,"/productId=%s/frameId=%s", product_id, frame_id); 
 	free(frame_id);	
}	

FcNode* check_register_status()
{
	char *xml_file=NULL;
	int i, flag=0;
	FcNode *setup_info=NULL;
	
	for(i=0; i<5&&flag==0; i++)
	{	
		if((flag=get_remote_file(REMOTE_HOST, remote_channelshow_xml, LOCAL_CHANNEL_SHOW_XML))==1)
		{
			xml_file=get_xml_strbuff(LOCAL_CHANNEL_SHOW_XML);			
			setup_info=get_show_setup_info(xml_file);					
			free(xml_file);	
			if(setup_info!=NULL) 
			{			
				dprintf("\nNever register, activation code path = %s and file type = %s\n", setup_info->remote_file_path, setup_info->file_type);									
				register_status=0;				
			}else{
				dprintf("\nEver register\n");				
				register_status=1;				
			}				
		}
		dprintf("\ndownload file flag %d\n", flag);
		sleep(1);				
	}	
	return setup_info;
}

FcNode* get_resetid_cmd()
{
	char *xml_file=NULL;
	int i, flag=0;
	FcNode *setup_info=NULL;
	
	for(i=0; i<3&&flag==0; i++)
	{	
		if((flag=get_remote_file_v2(remote_resetid, LOCAL_RESETID_XML))==1)
		{
			xml_file=get_xml_strbuff(LOCAL_RESETID_XML);
			dprintf("\nresetid_xml content: = %s\n", xml_file);
			setup_info=get_show_setup_info(xml_file);					
			free(xml_file);				
		}
		sleep(1);				
	}	
	return setup_info;
}


void get_activation_code(FcNode *setup_info)
{										
	int i, flag=0;
		
	for(i=0; i<5&&flag==0; i++)
	{									
		remove(LOCAL_REG_IMG);		
		flag=get_remote_file_v2(setup_info->remote_file_path, LOCAL_REG_IMG);				
		dprintf("\nflag=%d, 1 mean success, 2 mean fail, activation code path = %s\n", flag, setup_info->remote_file_path);
		sleep(1);			
	}											
}

void destroy_service()
{				
	pthread_mutex_lock(&fcxml_mutex);
	if(tid[1]!=-1) 
	{
		pthread_cancel(tid[1]);	
		tid[1]=-1;
	}	
	if(tid[2]!=-1) 
	{
		pthread_cancel(tid[2]);				
		tid[2]=-1;
	}	
	if(tid[3]!=-1) 
	{
		pthread_cancel(tid[3]);			
		tid[3]=-1;
	}	
	if(tid[4]!=-1) 
	{
		pthread_cancel(tid[4]);		
		tid[4]=-1;
	}	
	pthread_mutex_unlock(&fcxml_mutex);
	if(fcxml_node!=NULL) fcxml_node=delete_fcnode_tree(fcxml_node);
	if(fcxml_show_node!=NULL) fcxml_show_node=delete_fcnode_tree(fcxml_show_node);
	if(fcxml_item_node!=NULL) fcxml_item_node=delete_fcnode_tree(fcxml_item_node);	
	register_status=0;
}	

void init_service(int paser_file_flag)
{	
	int i, count=3;
	
	if(fcxml_show_node!=NULL) fcxml_show_node=delete_fcnode_tree(fcxml_show_node);
	for(i=0; i< count&&fcxml_show_node==NULL; i++)
	{
		fcxml_show_node=get_fcxmlshow_tree(paser_file_flag);		
	}
	
	if(fcxml_node!=NULL) fcxml_node=delete_fcnode_tree(fcxml_node);			
	if(fcxml_show_node!=NULL) 
	{		
		for(i=0; i< count&&fcxml_node==NULL; i++)
		{
			fcxml_node=get_fcxml_tree();												
		}
	}	
				
	if(fcxml_node!=NULL&&fcxml_show_node!=NULL)
	{							
		memset(selected_guid, 0, 512);
		strncpy(selected_guid, fcxml_node->this_guid, 511); //first this_guid almost "MyPhoto".
		if(tid[1]!=-1) pthread_cancel(tid[1]);		
		pthread_create(&tid[1], NULL, &get_remain_file_r, NULL); //get remain small icons, just run once.
		if(tid[2]!=-1) pthread_cancel(tid[2]);			
		pthread_create(&tid[2], NULL, &auto_tree_update_r, NULL); //auto update channel_list.xml thread. 
		if(tid[3]!=-1) pthread_cancel(tid[3]);		
		pthread_create(&tid[3], NULL, &auto_showtree_update_r, NULL); //auto update channel_show.xml thread. 
		if(tid[4]!=-1) pthread_cancel(tid[4]);		
		pthread_create(&tid[4], NULL, &auto_subtree_update_r, NULL); //auto update channel.xml thread. 						
		register_status=1;		
		remove(LOCAL_REG_IMG);								
	}else{
		destroy_service();		
	}	
}

//process client request
void* server_cmd_handler_r(void *arg)
{	
	char guid[512];
	int connfd, from_client, to_client;
	int wan_status=0, run_register_func=0;	
	FcNode *setup_info=NULL;
	
	connfd=*((int*)arg);
	pthread_detach(pthread_self());				
	wan_status = get_wan_status(); 	
	recv(connfd, &from_client, sizeof(int), 0);					
	
	//check wan status		
	if(!wan_status){	
		dprintf("\nWan down\n");		
		to_client=WAN_ERROR;								
		send(connfd, &to_client, sizeof(int), 0);				
	}else{						
		//check fcxml_node and fcxml_show_node, if both is null, we will init service
		if(fcxml_node==NULL||fcxml_show_node==NULL)
		{												
			dprintf("\nNode is null\n");		
			
			//check register status, it may reset register_status	
			setup_info=check_register_status(); 
			
			if(!register_status) 
			{	
				//if user unregistered,we get activation code image
				dprintf("\nrun register func\n");		
				to_client=NEVER_REGISTER;
				
				//send "NEVER_REGISTER" to client, client must create an alert to notify user
				send(connfd, &to_client, sizeof(int), 0);			
				
				//client may send "GET_ACTIVE_CODE" or "GET_ACTIVE_CODE_FAIL" to server
				recv(connfd, &from_client, sizeof(int), 0);			
				
				if(from_client==GET_ACTIVE_CODE)
				{ 					
					dprintf("\nnever register ,get_activation_code\n");
					
					//get activation code
					get_activation_code(setup_info);					
					
					//if LOCAL_REG_IMG exist, server send "GET_ACTIVE_CODE_FINISH" to client
					//, or send "GET_ACTIVE_CODE_FAIL" to client
					if(check_file_exist(LOCAL_REG_IMG))
					{
						to_client=GET_ACTIVE_CODE_FINISH;
						
						//server will send "GET_ACTIVE_CODE_FINISH" to client, client must create an alert to notify user
						send(connfd, &to_client, sizeof(int), 0);	
						
						//client will send "CHECK_REGISTER_STATUS" to server
						recv(connfd, &from_client, sizeof(int), 0); 
												
						if(from_client==CHECK_REGISTER_STATUS)
						{ 										
							destroy_service();
							if(setup_info!=NULL) delete_subtree(setup_info);
							
							//check register status again
							setup_info=check_register_status(); 
							dprintf("\nregister_status %d\n", register_status);
														
							if(register_status) 
							{																
								init_service(PARSER_EXIST_FILE); 								
								
								//server send "EVER_REGISTER" to client, client will create an alert to notify user
								to_client = EVER_REGISTER;
								send(connfd, &to_client, sizeof(int), 0);
								
								//send fcxml_node to client								
								pthread_mutex_lock(&fcxml_mutex);
								send_nodes(connfd, fcxml_node, net_node);	
								pthread_mutex_unlock(&fcxml_mutex);	
							}else{ 
								//server send "NEVER_REGISTER" to client, client will create an alert to notify user
								to_client = NEVER_REGISTER; 			
								send(connfd, &to_client, sizeof(int), 0);					
							}																													
						}				
					}else{
						//server send "GET_ACTIVE_CODE_FAIL" to client, client will create an alert to notify user
						to_client=GET_ACTIVE_CODE_FAIL;
						send(connfd, &to_client, sizeof(int), 0);							
					}																	
				}					
				run_register_func=1;
			}
			if(setup_info!=NULL) delete_subtree(setup_info);				
		}
																																  				
		if(!run_register_func)
		{															
			//user ever registered, if fcxml_node or fcxml_show_node is null, we should create them
			if(fcxml_node==NULL||fcxml_show_node==NULL)
			{
				dprintf("\never register, but node is null\n");	
				to_client=FCNODE_ISNULL;
				send(connfd, &to_client, sizeof(int), 0);													
				destroy_service();
				init_service(PARSER_EXIST_FILE); 
				if(!register_status) to_client=FCNODE_ISNULL;
				else to_client=FCNODE_NOTNULL;				
				send(connfd, &to_client, sizeof(int), 0);		
			}else{
				to_client=FCNODE_NOTNULL;
				send(connfd, &to_client, sizeof(int), 0);																		
			}
			
			//checking finish, server will provider service																												
			if(fcxml_node!=NULL&&fcxml_show_node!=NULL)
			{													
				switch(from_client)
				{			
					case CHANNEL_LIST_UPDATE:																	        							        					
			        					pthread_mutex_lock(&fcxml_mutex);		
			        					if(tid[2]!=-1) pthread_cancel(tid[2]);
			        					if(tid[3]!=-1) pthread_cancel(tid[3]);
			        					dprintf("\n[framechannel manual update.........start]\n");							
										tree_update();		
										get_remain_file();						
										showtree_update();
										if(fcxml_node==NULL||fcxml_show_node==NULL) to_client=FCNODE_ISNULL;
										else to_client=FCNODE_NOTNULL;								
										send(connfd, &to_client, sizeof(int), 0);
										dprintf("\n[framechannel manual update...........end]\n");								
										pthread_mutex_unlock(&fcxml_mutex);						
										pthread_create(&tid[2], NULL, &auto_tree_update_r, NULL);
										pthread_create(&tid[3], NULL, &auto_showtree_update_r, NULL);			
										break;		
					case CHANNEL_LIST_GET:							
										dprintf("\nget channel list\n");										
										pthread_mutex_lock(&fcxml_mutex);
										send_nodes(connfd, fcxml_node, net_node);	
										tree_thread_start=1;							
										pthread_mutex_unlock(&fcxml_mutex);		
										break;
					case CHANNEL_LIST_THREAD_STOP:
										dprintf("\nstop channel list update\n");
										tree_thread_start=0;		
										to_client=CHANNEL_LIST_THREAD_STOP;									
										send(connfd, &to_client, sizeof(int), 0);	
										break;											
					case CHANNEL_UPDATE:	
										system("rm -rf "LOCAL_CHANNELS_DIR"*");
										if(fcxml_item_node==NULL) to_client=FCNODE_ISNULL;
										else to_client=FCNODE_NOTNULL;  									
										send(connfd, &to_client, sizeof(int), 0);
										if(to_client==FCNODE_NOTNULL) send_nodes(connfd, fcxml_item_node, net_node);							        									
										break;
					case CHANNEL_GET:																																										
										dprintf("\nget channel\n");
										recv(connfd, &guid, sizeof(guid), 0);
										pthread_mutex_lock(&fcxml_mutex);																		
										subtree_update(guid);
										if(fcxml_item_node==NULL) to_client=FCNODE_ISNULL;
										else to_client=FCNODE_NOTNULL;  									
										send(connfd, &to_client, sizeof(int), 0);								
										if(to_client==FCNODE_NOTNULL)
										{																								
											memset(selected_guid, 0, 512);	
											strncpy(selected_guid, guid, 511);									
											send_nodes(connfd, fcxml_item_node, net_node);																				
											subtree_thread_start=1;
										}	
										pthread_mutex_unlock(&fcxml_mutex);																
										break;
					case CHANNEL_THREAD_STOP:
										dprintf("\nstop channel update\n");
										subtree_thread_start=0;		
										to_client=CHANNEL_THREAD_STOP;									
										send(connfd, &to_client, sizeof(int), 0);	
										break;
					case CHANNEL_SHOW_UPDATE:	
										system("rm -rf "LOCAL_CHANNEL_SHOW_DIR"*");											
					case CHANNEL_SHOW_GET:
										dprintf("\nget channel show update and get\n");
										pthread_mutex_lock(&fcxml_mutex);
										send_nodes(connfd, fcxml_show_node, net_node);	
										showtree_thread_start=1;
										pthread_mutex_unlock(&fcxml_mutex);		
										break;	
					case CHANNEL_SHOW_THREAD_STOP:
										dprintf("\nstop channel show update\n");
										showtree_thread_start=0;		
										to_client=CHANNEL_SHOW_THREAD_STOP;									
										send(connfd, &to_client, sizeof(int), 0);	
										break;												
					case RESET_FRAMEID:																								
										dprintf("\nreset framechannel id\n");
										remove(LOCAL_REG_IMG);										
										setup_info=get_resetid_cmd();		
										if(setup_info!=NULL)
										{																												 										
											destroy_service();											
											get_activation_code(setup_info);										
											delete_subtree(setup_info);																									
											to_client=RESET_FRAMEID;
											system("rm -rf "LOCAL_PIC_DIR"*");				
											system("mkdir -p "LOCAL_CHANNEL_LIST_DIR);
											system("mkdir -p "LOCAL_CHANNEL_SHOW_DIR);
											system("mkdir -p "LOCAL_CHANNELS_DIR);
										}else{ 										
											to_client=RESET_FRAMEID_FAIL;																																		
										}										
										send(connfd, &to_client, sizeof(int), 0);	
										break;		
					case GET_CHANNELS_UPDATE_VERSION:		
										dprintf("\nget channels update version\n");						
										send(connfd, &subtree_update_version, sizeof(int), 0);	
										break;
					case GET_CHANNEL_SHOW_UPDATE_VERSION:												
										dprintf("\nget channels show update version\n");														
										send(connfd, &showtree_update_version, sizeof(int), 0);	
										break;			
					default:		
										break;															
				}	
			}	
		}	
	}		
								
	close(connfd);		
	return NULL;
}

int main(int argc, char *argv[])     
{     	        
	socklen_t clilen;         
	struct sockaddr_un servaddr, cliaddr;			
	int listenfd, connfd, run_once=1, wan_status=0, i;
	FcNode *setup_info=NULL; 
			
	//initiate server
	system("rm -rf "LOCAL_PIC_DIR"*");				
	system("mkdir -p "LOCAL_CHANNEL_LIST_DIR);
	system("mkdir -p "LOCAL_CHANNEL_SHOW_DIR);
	system("mkdir -p "LOCAL_CHANNELS_DIR);
	register_status=0;		
	set_framechannel_info();				
		
	//ingnore sinal
	signal(SIGCLD, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);						
			
	nice(-18);	
	
	//goto point		
	error_status:	
	
	//initiate socket
	unlink(SOCKNAME);		
	listenfd = socket(AF_LOCAL, SOCK_STREAM, 0); 	  	 	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, SOCKNAME);	
	
	if ((bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) == -1)
	{
		perror("catch - bind failed");
		goto error_status;	 
	}
	
	if ((listen(listenfd, 0)) == -1)
	{
		perror("catch - listen failed");
		goto error_status;	  
	}
				
	for(;;)
	{							
		if(run_once)
		{						
			//avoid to get wrong wan status value, so try get valeu three time.
			for(i=0; i<3&&wan_status==0;i ++) 
			{
				wan_status = get_wan_status();						
				dprintf("\nwan_status %d\n", wan_status);
				sleep(1);
			}
												
			if(wan_status)
			{				
				//if user registered, will get channel_show.xml, or if user unregistered, will get register_pic(activation code image)
				setup_info=check_register_status(); 				
				if(setup_info!=NULL) delete_subtree(setup_info); 	
				
				//if channel_show.xml is not exist, we pass NOT_PARSER_EXIST_FILE flag to init_service(),
				//and if user already registered, we pass PARSER_EXIST_FILE to init_service();																
				if(register_status)	init_service(PARSER_EXIST_FILE);	 						
			}				
			run_once=0;						
		}
		
		clilen=sizeof(cliaddr);
		if((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen))!=-1)
		{																					
			pthread_create(&tid[0], NULL, &server_cmd_handler_r, &connfd);																							
		}					
	}
	close(connfd);	
	close(listenfd);	
}

