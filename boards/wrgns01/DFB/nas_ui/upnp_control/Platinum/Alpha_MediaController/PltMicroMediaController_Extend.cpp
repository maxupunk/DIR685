/*****************************************************************
	this file add by sam_pan
*****************************************************************/
#include "PltMicroMediaController.h" 
#include "PltLeaks.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "ctrl_default_define.h"
#include "packet_serialize.h"
#include "upnp_ctrl_cmd.h"

UPnPNode* create_node_tree_upnp(PLT_StringMap nameTable)
{
	UPnPNode *head=NULL, *tail=NULL, *tmp=NULL;
	int count=0;
	
	NPT_List<PLT_StringMapEntry*> entries = nameTable.GetEntries();
	if (entries.GetItemCount() == 0) 		
	{
	    printf("None available\n"); 
	    return NULL;	    
	}else{
	    // display the list of entries
	    NPT_List<PLT_StringMapEntry*>::Iterator entry = entries.GetFirstItem();	    
	    while (entry) 
	    {
	        count++;
	        printf("%d)\t%s (%s)\n", count, (const char*)(*entry)->GetValue(), (const char*)(*entry)->GetKey());						            						            
	        if(head==NULL)
	        {
	        	head=(UPnPNode*)malloc(sizeof(UPnPNode));
	        	head->service_name=NULL;
	        	head->guid=NULL;
	        	head->brother_node=NULL;
	        	head->elder_brother_node=NULL;
	        	tail=head;
	    	}else{
	    		tmp=tail;
	    		tail=(UPnPNode*)malloc(sizeof(UPnPNode));
	        	tail->service_name=NULL;
	        	tail->guid=NULL;
	        	tail->brother_node=NULL;
	        	tail->elder_brother_node=tmp;
	        	tmp->brother_node=tail;       	
	    	}		    	
	    	tail->index=count;
	    	tail->service_name=(char*)(*entry)->GetValue();
	        tail->guid=(char*)(*entry)->GetKey();
	        ++entry;
	  	}
	  	return head;
	}  	
}	

void* Command_Handler_r(void *arg)
{	
	int connfd, from_client, to_client, flag;		
	SocketNode *node=NULL;
	PLT_MicroMediaController *controller;
	PLT_StringMap nameTable, containerTable;
	PacketNode pnode;	
	UPnPNode *head=NULL;
	int size=500;
	char msg[500];	
				
	pthread_detach(pthread_self());					
	node=(SocketNode*)arg;		
	connfd=node->connfd;
	controller=node->controller;	
	recv(connfd, &from_client, sizeof(int), 0);																		
	
	switch(from_client)
	{					
		case SHOWMS:														
							nameTable = controller->GetMediaServerTable();	
							head = create_node_tree_upnp(nameTable);									
							send_nodes_upnp(connfd , head, pnode);
							delete_unode_tree(head);	
							break;		
		case SHOWMR:														
							nameTable = controller->GetMediaRendererTable();	
							head = create_node_tree_upnp(nameTable);									
							send_nodes_upnp(connfd , head, pnode);
							delete_unode_tree(head);	
							break;							
		case SETMS:																												
							
							memset(msg, 0 , size);
							recv(connfd, msg, size, 0);
							controller->GetMediaServerDevice(msg);																																											
							break;
		case SETMR:																												
						
							memset(msg, 0 , size);
							recv(connfd, msg, size, 0);
							controller->GetMediaRendererDevice(msg);																															
							break;							
		case LS:		
							containerTable=controller->ViewMediaContainers();														
							head = create_node_tree_upnp(containerTable);
							send_nodes_upnp(connfd , head, pnode);
							delete_unode_tree(head);	
							break;
		case CD:														
														
							memset(msg, 0 , size);
							recv(connfd, msg, size, 0);								
							flag = controller->ChangeMediaDir(msg);										
							to_client=flag;
							send(connfd, &to_client, sizeof(int), 0);								
							break;					
		case OPEN:							
							memset(msg, 0 , size);
							recv(connfd, msg, size, 0);		
							flag = controller->OpenMediaItem(msg);																																
							to_client=flag;
							printf("\ntest open server, to_client %d\n", to_client);											
							send(connfd, &to_client, sizeof(int), 0);																	
							break;		
		case PLAY:							
							controller->PlayMediaItem();																	
							break;														
		case STOP:							
							controller->StopMediaItem();																																
							break;					
		
		case PAUSE:							
							controller->PauseMediaItem();																												
							break;					
		case MUTE:							
							controller->MuteMediaItem();
							break;					
		case VUP:							
							controller->VoiceUpMediaItem();															
							break;					
		
		case VDOWN:							
							controller->VoiceDownMediaItem();															
							break;		
		case CDUP:
							controller->CdUpMediaItem();
							break;												
		default:		
							break;		
	}																																																																																							
	close(connfd);		
	return NULL;
}


void ProcessCommandSocket(PLT_MicroMediaController *controller)
{					
	socklen_t clilen;         
	struct sockaddr_un servaddr, cliaddr;			
	int listenfd, connfd;
	pthread_t tid[1];
	SocketNode *node=NULL;
							
	nice(-17);	
			
	error_status:	//goto point
	unlink(UPNP_SOCKNAME);	
	listenfd = socket(AF_LOCAL, SOCK_STREAM, 0); 	  	 	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, UPNP_SOCKNAME);	
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
	
	node=(SocketNode*)malloc(sizeof(SocketNode));
	node->controller=controller;		
		
	for(;;)
	{											
		clilen=sizeof(cliaddr);
		if((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen))!=-1)
		{																								
			node->connfd=connfd;									
			pthread_create(&tid[0], NULL, &Command_Handler_r, node);																							
		}	
	}
	free(node);
	close(connfd);	
	close(listenfd);	
}	