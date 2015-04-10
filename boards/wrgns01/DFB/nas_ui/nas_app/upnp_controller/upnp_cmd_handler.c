#include <stdio.h>
#include <netdb.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <directfb.h>
#include <stdlib.h>
#include <unistd.h>
#include "alpha_dfb_define.h"	
#include "menu_tool.h"
#include "alert_center.h"
#include "fcrss_command.h"
#include "upnp_ctrl_cmd.h"
#include "packet_serialize.h" 

#define NODE_ISNULL 100
#define NODE_NOTNULL 101
static int alert_cmd_handler(IDirectFBEventBuffer *p_eventbuffer, int cmd);

int upnp_cmd_handler(IDirectFBEventBuffer *p_eventbuffer, UPnPNode **init_node, char *media_device_guid, int cmd)
{
	int sockfd, to_server=0 ,from_server=0, alert_cmd=0, result=0;			
	struct sockaddr_un servaddr;
	PacketNode pnode;		
	UPnPNode *head=NULL;		
	int size=500;
	char msg[size];
		
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, UPNP_SOCKNAME);
	if((sockfd = socket(AF_LOCAL, SOCK_STREAM, 0))==-1) 
	{		
		alert_cmd=UNIXSOCK_FAIL;		
		return result; //socket error not close socket
	}	
			
	if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))==-1) alert_cmd=UNIXSOCK_FAIL;
		
	switch(cmd)
	{		
		case SHOWMS:						
						to_server=cmd;
						send(sockfd, &to_server, sizeof(int), 0);
						head=recv_nodes_upnp(sockfd, pnode);		
						if(head!=NULL)
						{ 
							*init_node=head;											
							result=REQ_SUCCESS;
						}else{
							result=alert_cmd_handler(p_eventbuffer, MS_NODE_ISNULL);
						}	
						break;
		case SHOWMR:						
						to_server=cmd;
						send(sockfd, &to_server, sizeof(int), 0);
						head=recv_nodes_upnp(sockfd, pnode);		
						if(head!=NULL)
						{ 
							*init_node=head;											
							result=REQ_SUCCESS;
						}else{
							result=alert_cmd_handler(p_eventbuffer, MR_NODE_ISNULL);
						}	
						break;						
		case SETMS:																									
						to_server=cmd;
						send(sockfd, &to_server, sizeof(int), 0);																																
						memset(msg, 0, size);						
						strncpy(msg, media_device_guid, size);													
						send(sockfd, msg, size, 0);							
						result=REQ_SUCCESS;
						break;
		case SETMR:																									
						to_server=cmd;
						send(sockfd, &to_server, sizeof(int), 0);						
						memset(msg, 0, size);						
						strncpy(msg, media_device_guid, size);													
						send(sockfd, msg, size, 0);							
						result=REQ_SUCCESS;
						break;		
		case LS:
						to_server=cmd;
						send(sockfd, &to_server, sizeof(int), 0);
						head=recv_nodes_upnp(sockfd, pnode);		
						if(head!=NULL)
						{ 
							*init_node=head;																									
							result=REQ_SUCCESS;
						}else{
							result=alert_cmd_handler(p_eventbuffer, NODE_ISNULL);
						}	
						break;										
		case CD:
						to_server=cmd;
						send(sockfd, &to_server, sizeof(int), 0);																			
						memset(msg, 0, size);						
						strncpy(msg, media_device_guid, size);													
						send(sockfd, msg, size, 0);																											
						recv(sockfd, &from_server, sizeof(int), 0);													
						if(from_server==IS_UPNP_DIR) result=REQ_SUCCESS;						
						else if(from_server==NOT_UPNP_DIR) result=REQ_FAIL;						
						break;		
		case OPEN:
						to_server=cmd;						
						send(sockfd, &to_server, sizeof(int), 0);																									
						memset(msg, 0, size);						
						strncpy(msg, media_device_guid, size);													
						send(sockfd, msg, size, 0);																					
						recv(sockfd, &from_server, sizeof(int), 0);		
						printf("\ntest open, from_server %d\n", from_server);											
						if(from_server==1) result = alert_cmd_handler(p_eventbuffer, OPEN_SUCCESS);			
						else if(from_server==0) result = alert_cmd_handler(p_eventbuffer, OPEN_FAIL);																					
						break;
		case PLAY:
						to_server=cmd;						
						send(sockfd, &to_server, sizeof(int), 0);	
						break;													
		case STOP:
						to_server=cmd;						
						send(sockfd, &to_server, sizeof(int), 0);								
						break;
		case PAUSE:
						to_server=cmd;						
						send(sockfd, &to_server, sizeof(int), 0);								
						break;
		case MUTE:
						to_server=cmd;						
						send(sockfd, &to_server, sizeof(int), 0);								
						break;
		case VUP:
						to_server=cmd;						
						send(sockfd, &to_server, sizeof(int), 0);								
						break;
		case VDOWN:
						to_server=cmd;						
						send(sockfd, &to_server, sizeof(int), 0);																																												
						break;
		case CDUP:
						to_server=cmd;						
						send(sockfd, &to_server, sizeof(int), 0);																																												
						break;						
		default:
						break;										
	}	
	close(sockfd);		
	printf("\n\ngo go go\n\n");
	return result;			
}


static int alert_cmd_handler(IDirectFBEventBuffer *p_eventbuffer, int cmd)
{		
	char msg[30];	
	IconObj *alert_icon=NULL;
		
	switch(cmd)
	{		
		case UNIXSOCK_FAIL:														
							memset(msg, 0, 30);	
							sprintf(msg,"Try to Connect Server..");
							Alert_Center(p_eventbuffer, msg);										
							return UNIXSOCK_FAIL;							
		case MS_NODE_ISNULL:														
							memset(msg, 0, 30);	
							sprintf(msg,"Can't find Media Servers");
							Alert_Center(p_eventbuffer, msg);					
							return REQ_FAIL;							
		case MR_NODE_ISNULL:														
							memset(msg, 0, 30);	
							sprintf(msg,"Can't find Media Renderers");
							Alert_Center(p_eventbuffer, msg);					
							return REQ_FAIL;		
		case OPEN_SUCCESS:
							memset(msg, 0, 30);								
							sprintf(msg,"Add File to PlayList");							
							alert_icon=(IconObj*)channel_alert(msg);
							sleep(1);
							icons_free(alert_icon);								
							return REQ_SUCCESS;																					
		case OPEN_FAIL:
							memset(msg, 0, 30);	
							sprintf(msg,"Can't Open this Media File");
							Alert_Center(p_eventbuffer, msg);					
							return REQ_FAIL;														
		case NODE_NOTNULL:						
							return REQ_SUCCESS;									
		default:
							return REQ_FAIL;				
	}	
}
