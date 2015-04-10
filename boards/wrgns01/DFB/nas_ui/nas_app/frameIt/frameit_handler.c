#include <stdio.h>
#include <netdb.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <directfb.h>
#include <stdlib.h>
#include <unistd.h>
#include "nas_str_define.h"
#include "str_tool.h"	
#include "fcrss_parser.h"
#include "fcrss_command.h"
#include "fcrss_serialize.h"
#include "menu_tool.h"
#include "fcrss_handler.h"
#include "frameit_parser.h"
#include "alert_center.h"

extern FcNode *fitshow_node;
static Net_FcNode net_node;

int Mclient_cmd_handler(int cmd, FcNode *node)
{						
	struct sockaddr_un servaddr;
	int sockfd, cmd2;
	FcNode *tmp_node;
	char msg[30]=FRAMEIT_HANDLER_MSG;		
	IconObj *alert_icon;
		
	bzero(&servaddr, sizeof(servaddr));	
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, SOCKNAME2);		
	if((struct hostent*)gethostbyname(REMOTE_HOST)==NULL) return DNS_ERROR;
	if((sockfd = socket(AF_LOCAL, SOCK_STREAM, 0))==-1) return UNIXSOCK_FAIL;				
	if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))==-1) return UNIXSOCK_FAIL;				
	if(send(sockfd, &cmd, sizeof(int), 0)==-1) return UNIXSOCK_FAIL;		
	if(recv(sockfd, &cmd2, sizeof(int), 0)==-1) return UNIXSOCK_FAIL;	
	if(cmd2==FCNODE_NOTNULL){
		switch(cmd){			
			case CHANNEL_SHOW_GET:
								alert_icon=(IconObj*)channel_alert(msg);
								tmp_node=NULL;		
								if(fitshow_node!=NULL) tmp_node=fitshow_node;
								fitshow_node=recv_nodes(sockfd, net_node);																																				
								if(tmp_node!=NULL) subtree_update(fitshow_node, tmp_node);								
								icons_free(alert_icon);
								return FCNODE_NOTNULL;
								break;																																																						
			default: 													
								break;					
		}	
	}else{		
		if(fitshow_node!=NULL) delete_fcnode_tree(fitshow_node);		
		fitshow_node=NULL;			
	}							
	close(sockfd);			
	return FCNODE_ISNULL;		
}	

int Malert_cmd_handler(IDirectFBEventBuffer *p_eventbuffer, int cmd, int super_cmd){		
	char msg[30];		
	memset(msg, 0, 30);	
	
	switch(cmd)
	{		
		case DNS_ERROR:
							sprintf(msg,NETWORK_ERROR);
							Alert_Center(p_eventbuffer, msg);	
							return 0;			
		case UNIXSOCK_FAIL:																					
							sprintf(msg,FRAMEIT_HANDLER_MSG);
							Alert_Center(p_eventbuffer, msg);										
							return 0;									
		case FCNODE_ISNULL:																
							sprintf(msg,FRAMEIT_HANDLER_MSG);
							Alert_Center(p_eventbuffer, msg);														
							return 0;							
		case FCNODE_NOTNULL:						
							return 1;											
		default:
							return 0;				
	}	
}


	