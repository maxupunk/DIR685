#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "webtcpreq.h"

char* get_remote_host_name(char *media_path)
{
	char *p_header[]={"http://", "ftp://"};
	char *head=NULL, *tail=NULL, *host_name=NULL;
	int i=0, host_len=0;
			
	for(i=0; i<2;i++)
	{		
		if((tail=strstr(media_path, p_header[i]))!=NULL) 
		{
			tail+=strlen(p_header[i]);					
			head=tail;
			
			while(*tail!='/')
			{				
				tail++;					
				host_len++;				
			}	
										
			host_name++; //add '\0'							
			host_name=(char*)malloc((host_len)*sizeof(char));
			memset(host_name, 0, host_len);									
			strncpy(host_name, head, host_len);						
			return host_name;			
		}	
	}				
	return NULL;
}

char* get_remote_file_path(char *media_path)
{
	char *host_name=NULL, *file_path=NULL;
	char *head=NULL;
	int file_len=0;
	
	host_name=get_remote_host_name(media_path);
	if(host_name!=NULL)
	{
		if((head=strstr(media_path, host_name))!=NULL) 
		{
			head+=strlen(host_name); //omit host_name				
			file_len=strlen(head); 		
			file_len++; // add '\0'
			file_path=(char*)malloc((file_len)*sizeof(char));
			memset(file_path, 0 , file_len);
			file_path=strncpy(file_path, head, file_len);
		}		
		free(host_name);
		return file_path;
	}
	
	return NULL;	
}

int check_temporary_redirect(char *content, char *local_file) 
{
	char *msg[]={"HTTP/1.1 307 Temporary Redirect","Location: "};	
	char *head=NULL, *tail=NULL, *redirect_url=NULL;
	char *host_name=NULL, *file_path=NULL;
	int url_len=0, status_flag=-1;
			
	if((tail=strstr(content, msg[0]))!=NULL)
	{				
		tail++;		
		if((tail=strstr(tail,msg[1]))!=NULL)
		{						
			tail=tail+strlen(msg[1]);
			head=tail;			
									
			while(*tail!='\r'&&*tail!='\n')
			{																									
				tail++;
				url_len++;
			}
			
			url_len++; // add '\0' to terminal string
			redirect_url=(char*)malloc(url_len*sizeof(char));																
			memset(redirect_url, 0, url_len);
			strncpy(redirect_url, head, url_len);			
			host_name=get_remote_host_name(redirect_url);
			file_path=get_remote_file_path(redirect_url);		
			status_flag=web_tcpreq(host_name, file_path, local_file);			
			free(host_name);
			free(file_path);
			free(redirect_url);	  
			return status_flag;            
		}
	}
	
	return status_flag;											
}	

void sendcmd_to_server(WebFile *wf_obj, fd_set *rfd)
{
	int	cmd_len=0;
	char buf[DEF_MAXDATASIZE];	
				
	cmd_len=sprintf(buf, "GET %s HTTP/1.1\n", wf_obj->remote_file);
	sprintf(buf+cmd_len, "Accept: */*\nHost: %s\nConnection: Close\n\n", wf_obj->remote_server); 		
		
	if(send(wf_obj->sockfd, buf, strlen(buf), 0)!=-1)
	{			
		FD_SET(wf_obj->sockfd, rfd);	
		wf_obj->status_flag=READ; //sending command to server is success, and we can read server response from our buffer. 			
	}
}	

int conn_host(WebFile *wf_obj, fd_set *wfd, fd_set *rfd)
{
	int conn_status;	 	 	 	 
	struct hostent *host;
	struct sockaddr_in serv_addr;
				
	if((host=gethostbyname(wf_obj->remote_server))!=NULL)
	{	    
	    if((wf_obj->sockfd = socket(AF_INET, SOCK_STREAM, 0)) != -1)
	    {	       	    				
			serv_addr.sin_family=AF_INET;
			serv_addr.sin_port=htons(wf_obj->remote_port);
			serv_addr.sin_addr = *((struct in_addr *)host->h_addr);
			bzero(&(serv_addr.sin_zero),8);
			
		    if((conn_status=connect(wf_obj->sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)))==-1)
		    {
				if (errno == EINPROGRESS)
				{					
					wf_obj->status_flag=CONN;
					FD_SET(wf_obj->sockfd, wfd);
					FD_SET(wf_obj->sockfd, rfd);																				
					return 1;
				}								
			}else if(conn_status==0){					
					sendcmd_to_server(wf_obj, rfd);		
					return 1;			
			}
	    }  
	}
 	
 	return -1; 	
}
  
int http_header_clear(char *buf, int *header_flag, int buf_size){
	int i=0;
	
	while(i<buf_size&&*header_flag==0)
	{
		if(buf[i++]=='\r') 
			if(buf[i++]=='\n') 								
				if(buf[i++]=='\r') 
					if(buf[i++]=='\n') {										
						*header_flag=1;
						return i;
					}																								
	}
	return 0;
}	
    
int get_chunked_value2(char *buf)
{
	char tmp[64], *s;	
		
	strncpy(tmp, buf, sizeof(tmp));	
			
	if((s=strchr(tmp, '\n'))!=NULL){
		*s='\0';							
		return strtol(tmp, NULL, 16);
	}		
	return -1;
}
    
int get_next_break(char *buf, int buf_size){
	int i=0;
	while(i<buf_size){
		if(buf[i++]=='\n') return i;	
	}
	return 0;	
}	    

void init_wfobj(WebFile **web_file_obj, char *remote_server, char *remote_file, char *local_file)
{	
	
	WebFile *wf_obj;				
	
	wf_obj=(WebFile*)malloc(sizeof(WebFile));
	wf_obj->sockfd=-1;
	wf_obj->status_flag=FIN; //set flag to check file download status.
	wf_obj->chunked_flag=0;
	wf_obj->header_flag=0;	
	wf_obj->remote_port=DEF_SRVPORT;
	wf_obj->remote_server=remote_server;
	wf_obj->remote_file=remote_file;
	wf_obj->local_file=local_file;
	*web_file_obj=wf_obj;			
}	

int web_tcpreq(char *remote_server, char *remote_file, char *local_file)
{
	FILE *pFile;
	WebFile *wf_obj;			
	struct timeval tv;	
	char buf[DEF_MAXDATASIZE];	
	int conn_status, select_status;
	int recv_size=0, total_recv_size=0, chunk_size=-1, fd;	
	fd_set rfd, wfd;		
	
	init_wfobj(&wf_obj, remote_server, remote_file, local_file);					
	FD_ZERO(&wfd); 
	FD_ZERO(&rfd); 	
		
	if((conn_status=conn_host(wf_obj, &wfd, &rfd))!= -1)
	{					
		if((pFile=fopen(wf_obj->local_file, "w"))==NULL) 
		{					
			close(wf_obj->sockfd);
			free(wf_obj);
			return 0;					
		}else{
			//set file lock  						
			if((fd=open(wf_obj->local_file, O_RDWR))!=-1)
			{			
				if(lockf(fd, F_TLOCK, 0)==-1) 
				{					
					fclose(pFile);
					close(fd);
					close(wf_obj->sockfd);					
					free(wf_obj);
					return 0;
				}			
			}else{								
				fclose(pFile);
				close(wf_obj->sockfd);
				remove(wf_obj->local_file);		
				free(wf_obj);
				return 0;
			}
		}
			
		for(;;)
		{												
			tv.tv_sec = 30;			
			tv.tv_usec = 30;							
			
			if((select_status = select(wf_obj->sockfd+1, &rfd, &wfd, NULL, &tv))<=0) //set time expires  		
			{													
				if(select_status==-1&&errno==EINTR) continue;							
				fclose(pFile);
				close(fd);
				close(wf_obj->sockfd);						
				remove(wf_obj->local_file);				
				free(wf_obj);
				return 0;								
			}			
						
			if((wf_obj->status_flag==CONN)&&(FD_ISSET(wf_obj->sockfd, &wfd) || FD_ISSET(wf_obj->sockfd, &rfd)))
			{									
				int option;
				socklen_t optlen = sizeof(int);								
				if (getsockopt(wf_obj->sockfd, SOL_SOCKET, SO_ERROR, &option, &optlen) < 0 ||option != 0) 
				{
					fclose(pFile);
					close(fd);
					close(wf_obj->sockfd);
					remove(wf_obj->local_file);					
					free(wf_obj);
					return 0;								
				}													
				FD_CLR(wf_obj->sockfd, &wfd);						
				sendcmd_to_server(wf_obj, &rfd);																			
			}else if (wf_obj->status_flag==READ&&FD_ISSET(wf_obj->sockfd, &rfd)){								
				memset(buf, 0, DEF_MAXDATASIZE);  					
				recv_size = recv(wf_obj->sockfd, buf, DEF_MAXDATASIZE-1, 0);											  	
				if (recv_size == 0)
				{									
					FD_CLR(wf_obj->sockfd, &rfd);											
					wf_obj->status_flag=FIN;							
					break;
				}else if(recv_size>0){														
					int header_size=0, text_size=0, posi=0, tmp_size=0, redirect_flag=0;
					char *text;
					
					if((redirect_flag=check_temporary_redirect(buf, wf_obj->local_file))!=-1) //redirect_flag==-1 mean no temporary redirect
					{												
						fclose(pFile);
						close(fd);
						close(wf_obj->sockfd);						
						free(wf_obj);			
						return redirect_flag;							
					}	
															
					if(wf_obj->chunked_flag==0)
					{
						if(strstr(buf, "Transfer-Encoding: chunked")!=NULL) {
							wf_obj->chunked_flag=1;				        	
						}																						
					}
																		
					header_size=http_header_clear(buf, &wf_obj->header_flag, recv_size);						
					text=buf+header_size;								
					text_size=recv_size-header_size;																				
															
					if(wf_obj->chunked_flag==1)
					{																											
						if(chunk_size==-1)
						{ 																					
							chunk_size=get_chunked_value2(text);														
							if(chunk_size==0)
							{ 
								fclose(pFile);
								close(fd);
								close(wf_obj->sockfd);						
								remove(wf_obj->local_file);				
								free(wf_obj);
								return 0;																								
							}else if(chunk_size==-1) {
								fclose(pFile);
								close(fd);
								close(wf_obj->sockfd);						
								remove(wf_obj->local_file);				
								free(wf_obj);
								return 0;
							}		
							posi=get_next_break(text, text_size);
							text+=posi;
							text_size-=posi;									
							if(chunk_size >= text_size) 
							{
								tmp_size=text_size;
							}else {
								tmp_size=chunk_size; 								
							}	
							fwrite(text, 1, tmp_size, pFile);
							text+=tmp_size;
							text_size-=tmp_size;
							total_recv_size=tmp_size;																								
							if(chunk_size >= text_size) continue;
						}
						
						chunk_finish:	
						if(chunk_size == total_recv_size)
						{	
							text+=2; //+2 mean \r\n
							text_size-=2; //+2 mean \r\n									
							chunk_size=get_chunked_value2(text);										
							if(chunk_size==0) 
							{																						
								break;			
							}else if(chunk_size==-1){
								fclose(pFile);
								close(fd);
								close(wf_obj->sockfd);						
								remove(wf_obj->local_file);				
								free(wf_obj);
								return 0;
							}	
														
							posi=get_next_break(text, text_size);
							text+=posi;
							text_size-=posi;							
							total_recv_size=0;							
						}
												
						if(chunk_size > total_recv_size)
						{							
							tmp_size=chunk_size-total_recv_size;
							if(tmp_size >= text_size) tmp_size=text_size;							
							fwrite(text, 1, tmp_size, pFile);			
							text+=tmp_size;
							text_size-=tmp_size;				
							total_recv_size+=tmp_size;								
							if(text_size<=0) {								
								continue;
							}else if((text_size>0) || (chunk_size == total_recv_size)) goto chunk_finish;								
						}
					}else{										
      					fwrite(text, 1, text_size, pFile);	           										
      				}	
				}
			}										
		}			
	    fclose(pFile);
	    close(fd);
		close(wf_obj->sockfd);
		free(wf_obj);					
		return 1;
	}else{		
		close(wf_obj->sockfd);				
		free(wf_obj);				
		return 0;
	}		
}
