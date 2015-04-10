#include <stdio.h>
#include <netdb.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <directfb.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "alpha_dfb_define.h"	
#include "nas_str_define.h"
#include "str_tool.h"	
#include "fcrss_parser.h"
#include "fcrss_command.h"
#include "fcrss_serialize.h"
#include "menu_tool.h"
#include "alert_center.h"

FcNode *fclist_node=NULL, *fcitem_node=NULL, *fcshow_node=NULL;
static Net_FcNode net_node;
static int subtree_update_version=0, showtree_update_version=0;
int alert_cmd_handler(IDirectFBEventBuffer *p_eventbuffer, int cmd);

void subtree_update(FcNode *node_new, FcNode *node_old)
{			
												
   	if(node_new!=NULL)
   	{    	    		
		rm_cmpsubtree_file(node_new, node_old);		
		delete_fcnode_tree(node_old);																																        	        		    		              	  	        	
	}else{
		node_new=node_old;																							        	        		    	
	}						
}

//send request to server and process response from server
int client_cmd_handler(IDirectFBEventBuffer *p_eventbuffer, int to_server, FcNode *node)
{						
	FcNode *tmp_node=NULL;	
	IconObj *alert_icon=NULL;
	char msg[30];
	int sockfd, from_server, alert_cmd=0, result=0, wan_status=0, dns_status=0, guid_len=0;			
	struct sockaddr_un servaddr;
			
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, SOCKNAME);
		
	if((sockfd = socket(AF_LOCAL, SOCK_STREAM, 0))==-1) 
	{		
		if(errno==EACCES) printf("\nEACCES\n");						
		else if(errno==EAFNOSUPPORT) printf("\nEAFNOSUPPORT\n");
		else if(errno==EINVAL) printf("\nEINVAL\n");
		else if(errno==EMFILE) printf("\nEMFILE\n");
		else if(errno==ENFILE) printf("\nENFILES\n");
		else if(errno==ENOBUFS) printf("\nENOBUFS\n");
		else if(errno==EPROTONOSUPPORT) printf("\nEACCES\n");
		else printf("\nerron %d\n", errno);
		
		alert_cmd=UNIXSOCK_FAIL;						
		result=alert_cmd_handler(p_eventbuffer, alert_cmd);											
		return result; //socket error not close socket
	}			
	dprintf("\nsocket ok %d\n", sockfd);
	
	wan_status = get_wan_status(); 
	if(!wan_status) 
	{
		close(sockfd);		
		return WAN_ERROR;				
	}	
	dprintf("\nwan ok\n");
		
	if(to_server==CHANNEL_LIST_GET||to_server==CHANNEL_GET)
	{	
#ifdef ALWAYS_CHECK_DOMAIN_NAME
		dns_status = get_dns_status(CHECK_DOMAIN_NAME, REMOTE_HOST);	
		if(!dns_status) 
		{
			close(sockfd);		
			return DNS_ERROR;				
		}	
		dprintf("\ndns ok 1\n");
#else		
		if(gethostbyname(REMOTE_HOST)==NULL) 
		{
			close(sockfd);		
			return DNS_ERROR;				
		}	
		dprintf("\ndns ok 2\n");			
#endif	
	}
		
	if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))==-1) alert_cmd=UNIXSOCK_FAIL;
	
	dprintf("\nconnect socket ok\n");
	if(send(sockfd, &to_server, sizeof(int), 0)==-1) alert_cmd=UNIXSOCK_FAIL;	
	dprintf("\nsend request1 to server ok\n");	
		
	if(recv(sockfd, &from_server, sizeof(int), 0)==-1) alert_cmd=UNIXSOCK_FAIL;			
	dprintf("\nrecv response1 from server ok\n");		
	
	if(alert_cmd!=UNIXSOCK_FAIL)
	{	
		if(from_server==WAN_ERROR){
			alert_cmd=WAN_ERROR;
			result=alert_cmd_handler(p_eventbuffer, alert_cmd);						
		}else if(from_server==NEVER_REGISTER&&to_server!=CHANNEL_LIST_THREAD_STOP&&to_server!=CHANNEL_SHOW_THREAD_STOP){																
			close_icon_alert();
			//create alert to notify user that server will get activation code 
			memset(msg, 0, 30);
			sprintf(msg,FCRSS_DO_GET_ACTIVE_CODE);
			alert_icon=(IconObj*)channel_alert(msg);
			
			//send request to server, and ask server to get activation code
			to_server=GET_ACTIVE_CODE;						
			if(send(sockfd, &to_server, sizeof(int), 0)==-1)
			{ 				
				icons_free(alert_icon);	
				alert_cmd=UNIXSOCK_FAIL;    												
			}else{										
				//response from server	            						
				if(recv(sockfd, &from_server, sizeof(int), 0)==-1) 
				{				
					icons_free(alert_icon);	
					alert_cmd=UNIXSOCK_FAIL;														
				}else{						
					icons_free(alert_icon);						
					//server get activation code success
					if(from_server==GET_ACTIVE_CODE_FINISH)
					{						
						//show activation code on panel, and wait for user pressing button
						alert_cmd_handler(p_eventbuffer, GET_ACTIVE_CODE); 
						
						//if user press button, client will create alert to notify user that server is checking register status now
						memset(msg, 0, 30);
						sprintf(msg,FCRSS_CHECK_REGISTER);
						alert_icon=(IconObj*)channel_alert(msg);
						
						//send request to server, and ask server to check register status
						to_server=CHECK_REGISTER_STATUS;					
						if(send(sockfd, &to_server, sizeof(int), 0)==-1) alert_cmd=UNIXSOCK_FAIL;
						if(recv(sockfd, &from_server, sizeof(int), 0)==-1) alert_cmd=UNIXSOCK_FAIL;							
						if(from_server==EVER_REGISTER)
						{ 
							//initiate fclist_node							
							if(fclist_node!=NULL) delete_fcnode_tree(fclist_node);							
							fclist_node=recv_nodes(sockfd, net_node);																																																																																												
						}
						icons_free(alert_icon);										
						result = alert_cmd_handler(p_eventbuffer, from_server);
					}else{		
						//server get activation code fail			
						result=alert_cmd_handler(p_eventbuffer, GET_ACTIVE_CODE_FAIL);																
					}											
				}	
			}	
		}else {									
			//server's run_register_func is 0, fcxml_node==NULL or fcxml_show_node==NULL 
			if(from_server==FCNODE_ISNULL)
			{								
				if(recv(sockfd, &from_server, sizeof(int), 0)==-1) alert_cmd=UNIXSOCK_FAIL;					
				if(from_server==FCNODE_ISNULL)
				{									
					alert_cmd=FCNODE_ISNULL;
					result=alert_cmd_handler(p_eventbuffer, alert_cmd);								
				}	
			}	
			
			//server starts to process formal request from client
			if(from_server==FCNODE_NOTNULL)
			{
				switch(to_server){
					case CHANNEL_LIST_UPDATE:										
										if(recv(sockfd, &to_server, sizeof(int), 0)==-1) 
										{																																
											alert_cmd=UNIXSOCK_FAIL;																				
										}else{
											if(to_server==FCNODE_NOTNULL)
											{ 
												alert_cmd=UPDATE_SUCCESS;
												fclist_node=delete_fcnode_tree(fclist_node);
												fcshow_node=delete_fcnode_tree(fcshow_node);
											}else {
												alert_cmd=UPDATE_FAIL;													
											}																						
											result=alert_cmd_handler(p_eventbuffer, alert_cmd);	
										}	
										break;
					case CHANNEL_LIST_GET:																			
										if(fclist_node!=NULL) delete_fcnode_tree(fclist_node);
										fclist_node=recv_nodes(sockfd, net_node);																																								
										if(fclist_node==NULL) alert_cmd=FCNODE_ISNULL;
										else alert_cmd=FCNODE_NOTNULL;																			
										result=alert_cmd_handler(p_eventbuffer, alert_cmd);											
										break;	
					case CHANNEL_LIST_THREAD_STOP:
										dprintf("\nstop channel list update finish\n");
										result=REQ_SUCCESS;			
										break;													
					case CHANNEL_UPDATE:
										if(recv(sockfd, &from_server, sizeof(int), 0)==-1)
										{
											alert_cmd=UNIXSOCK_FAIL;										
											break;
										}			
										if(fcitem_node!=NULL) tmp_node=fcitem_node;																				
										if(from_server==FCNODE_NOTNULL) 
										{												
											fcitem_node=recv_nodes(sockfd, net_node);
											if(tmp_node!=NULL) subtree_update(fcitem_node, tmp_node);																		
											alert_cmd=FCNODE_NOTNULL;																																																																																												
										}else{
											if(tmp_node!=NULL) delete_fcnode_tree(tmp_node);																		
											alert_cmd=FCNODE_ISNULL;													
										}															
										result=alert_cmd_handler(p_eventbuffer, alert_cmd);		
										break;																																
					case CHANNEL_GET:																																																																								
										guid_len=strlen(node->this_guid)+1;
										send(sockfd, node->this_guid, guid_len*sizeof(char), 0);										
										if(recv(sockfd, &from_server, sizeof(int), 0)==-1)
										{
											alert_cmd=UNIXSOCK_FAIL;										
											break;
										}									
										if(fcitem_node!=NULL) tmp_node=fcitem_node;																				
										if(from_server==FCNODE_NOTNULL) 
										{												
											fcitem_node=recv_nodes(sockfd, net_node);
											if(tmp_node!=NULL) subtree_update(fcitem_node, tmp_node);											
											alert_cmd=FCNODE_NOTNULL;																																																																																												
										}else{
											if(tmp_node!=NULL) delete_fcnode_tree(tmp_node);																		
											alert_cmd=FCNODE_ISNULL;													
										}																										
										result=alert_cmd_handler(p_eventbuffer, alert_cmd);		
										break;	
					case CHANNEL_THREAD_STOP:
										dprintf("\nstop channel update finish\n");
										result=REQ_SUCCESS;			
										break;								
					case CHANNEL_SHOW_UPDATE:																							
					case CHANNEL_SHOW_GET:																					
										if(fcshow_node!=NULL) tmp_node=fcshow_node;
										fcshow_node=recv_nodes(sockfd, net_node);																																				
										if(fcshow_node==NULL){
											if(tmp_node!=NULL) delete_fcnode_tree(tmp_node);											
											alert_cmd=FCNODE_ISNULL;										
										}else{	
											if(tmp_node!=NULL) subtree_update(fcshow_node, tmp_node);											
											alert_cmd=FCNODE_NOTNULL;										
										}											
										result=alert_cmd_handler(p_eventbuffer, alert_cmd);		
										break;	
					case CHANNEL_SHOW_THREAD_STOP:
										dprintf("\nstop channel show update finish\n");
										result=REQ_SUCCESS;			
										break;																			
					case RESET_FRAMEID:													
										if(recv(sockfd, &from_server, sizeof(int), 0)==-1)
										{											
											alert_cmd=UNIXSOCK_FAIL;																				
										}else{																															
											alert_cmd=from_server;	//RESET_FRAMEID_FAIL | RESET_FRAMEID
											result=alert_cmd_handler(p_eventbuffer, alert_cmd);		
										}									
										break;				
					case GET_CHANNELS_UPDATE_VERSION:																				
										if(recv(sockfd, &from_server, sizeof(int), 0)==-1)
										{
											alert_cmd=UNIXSOCK_FAIL;											
										}else{	
											dprintf("\nnew subtree_update_version=%d, subtree_update_version=%d\n", from_server, subtree_update_version);
											if(from_server > subtree_update_version)
											{ 
												subtree_update_version=from_server;											
												result=	DO_UPDATE;
											}else{
												if(from_server==0) subtree_update_version=0;
												result= DO_NOTHING;
											}	
										}	
										break;
					case GET_CHANNEL_SHOW_UPDATE_VERSION:																				
										if(recv(sockfd, &from_server, sizeof(int), 0)==-1)
										{
											alert_cmd=UNIXSOCK_FAIL;										
										}else{	
											dprintf("\nnew showtree_update_version=%d, showtree_update_version=%d\n", from_server, showtree_update_version);
											if(from_server > showtree_update_version) 
											{	
												showtree_update_version=from_server;
												alert_cmd=DO_UPDATE;
												result=alert_cmd;
											}else{	
												if(from_server==0) showtree_update_version=0;
												alert_cmd=DO_NOTHING;
												result=alert_cmd;
											}	
										}	
										break;		
					case CHECK_SERVER_STATUS:
										result=REQ_SUCCESS;										
					default: 																																													
										break;					
				}	
			}
		}	
	}
	
	if(alert_cmd==UNIXSOCK_FAIL)
	{ 
		result=alert_cmd_handler(p_eventbuffer, alert_cmd);					
	}	
	close(sockfd);		
	return result;		
}	


int alert_cmd_handler(IDirectFBEventBuffer *p_eventbuffer, int cmd)
{		
	char msg[30];	
				
	switch(cmd)
	{		
		case UNIXSOCK_FAIL:														
							close_icon_alert();
							memset(msg, 0, 30);	
							sprintf(msg,FCRSS_UNIXSOCK_FAIL);							
							Alert_Center(p_eventbuffer, msg);																	
							return UNIXSOCK_FAIL;			
		case WAN_ERROR:
							close_icon_alert();
							memset(msg, 0, 30);	
							sprintf(msg,NETWORK_ERROR);
							Alert_Center(p_eventbuffer, msg);	
							return WAN_ERROR;	
		case DNS_ERROR:
							close_icon_alert();
							//memset(msg, 0, 30);	
							//sprintf(msg,DNS_ERROR_MSG);
							Alert_Center(p_eventbuffer, DNS_ERROR_MSG);	
							return DNS_ERROR;								
		case GET_ACTIVE_CODE_FAIL:				
							close_icon_alert();			
							memset(msg, 0, 30);
							sprintf(msg,FCRSS_GET_ACTIVE_CODE_FAIL);				
							Alert_Center(p_eventbuffer, msg);																	
							return REQ_FAIL;			
		case GET_ACTIVE_CODE:
							close_icon_alert();
							register_alert(p_eventbuffer, LOCAL_REG_IMG);																																																	
							return REQ_FAIL;
		case EVER_REGISTER:	
							close_icon_alert();
							memset(msg, 0, 30);
							sprintf(msg,FCRSS_EVER_REGISTER);				
							Alert_Center(p_eventbuffer, msg);		
							return REQ_SUCCESS;
		case NEVER_REGISTER:
							memset(msg, 0, 30);
							sprintf(msg,FCRSS_NEVER_REGISTER);
							Alert_Center(p_eventbuffer, msg);		
							return REQ_FAIL;
		case FC_ERROR:																														
		case FCNODE_ISNULL:					
							close_icon_alert();
							if(fclist_node!=NULL) fclist_node=delete_fcnode_tree(fclist_node);
							if(fcitem_node!=NULL) fcitem_node=delete_fcnode_tree(fcitem_node);
							if(fcshow_node!=NULL) fcshow_node=delete_fcnode_tree(fcshow_node);										
							memset(msg, 0, 30);	
							sprintf(msg,FCRSS_FCNODE_ISNULL);
							Alert_Center(p_eventbuffer, msg);					
							return REQ_FAIL;							
		case FCNODE_NOTNULL:						
							return REQ_SUCCESS;							
		case RESET_FRAMEID_FAIL:			
							close_icon_alert();
							memset(msg, 0, 30);					
							sprintf(msg, FCRSS_RESET_FRAMEID_FAIL);			
							Alert_Center(p_eventbuffer, msg);			
							return REQ_FAIL;												
		case RESET_FRAMEID:	
							close_icon_alert();
							if(fclist_node!=NULL) fclist_node=delete_fcnode_tree(fclist_node);
							if(fcitem_node!=NULL) fcitem_node=delete_fcnode_tree(fcitem_node);
							if(fcshow_node!=NULL) fcshow_node=delete_fcnode_tree(fcshow_node);												
							memset(msg, 0, 30);
							sprintf(msg,FCRSS_RESET_FRAMEID);															
							Alert_Center(p_eventbuffer, msg);			
							return REQ_SUCCESS;		
		case UPDATE_SUCCESS:							
							close_icon_alert();
							memset(msg, 0, 30);	
							sprintf(msg, FCRSS_UPDATE_SUCCESS);	       	
							Alert_Center(p_eventbuffer, msg);										
							return REQ_SUCCESS;		
		case UPDATE_FAIL:											
							close_icon_alert();
							memset(msg, 0, 30);	
							sprintf(msg, FCRSS_UPDATE_FAIL);	       	
							Alert_Center(p_eventbuffer, msg);										
							return REQ_FAIL;		
		default:
							return REQ_FAIL;				
	}	
}
