#include <stdio.h>
#include <sys/un.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "packet_serialize.h"
#include "str_tool.h"

UPnPNode* get_unode_head(UPnPNode *node)
{	
	UPnPNode *head=NULL;
	
	while(node!=NULL)
	{				
		head=node;
		node=node->elder_brother_node;
	}		
	return head;
}

void delete_unode_tree(UPnPNode *head)
{
	UPnPNode *tmp;
	
	head=get_unode_head(head);
	while(head!=NULL)
	{
		tmp=head;				
		head=head->brother_node;
		free(tmp);
	}	
}	

void serial_unode(PacketNode *pnode, UPnPNode *node)
{								
	pnode->index=node->index;
	sam_strnarr((char*)&pnode->guid, node->guid);							
	sam_strnarr((char*)&pnode->service_name, node->service_name);								
}	

void unserial_unode(UPnPNode *node, PacketNode *pnode)
{		
	node->index=pnode->index;
	node->guid=sam_strncpy(pnode->guid, strlen(pnode->guid));
	node->service_name=sam_strncpy(pnode->service_name, strlen(pnode->service_name));    
}

void send_nodes_upnp(int connfd, UPnPNode *node, PacketNode pnode)
{
	UPnPNode *head=NULL;					
	int serv_msg=1, client_msg=100;			
	head=get_unode_head(node);														
	while(head!=NULL)
	{			
		send(connfd, &serv_msg, sizeof(int), 0);																	
		recv(connfd, &client_msg, sizeof(int), 0);				
		serial_unode(&pnode, head);		
		send(connfd, &pnode, sizeof(pnode), 0);									
		recv(connfd, &client_msg, sizeof(int), 0);			
		head=head->brother_node;								
	}			
	serv_msg=0;
	send(connfd, &serv_msg, sizeof(int), 0);						
}	

UPnPNode* recv_nodes_upnp(int sockfd, PacketNode pnode)
{		
	UPnPNode *head=NULL, *tail=NULL, *tmp=NULL;	
	int serv_msg, client_msg=1;		
	
	while(1)
	{				
		recv(sockfd, &serv_msg, sizeof(int), 0);			
		if(serv_msg==0) break;						
		send(sockfd, &client_msg, sizeof(int), 0);					
		recv(sockfd, &pnode, sizeof(pnode), 0);		
					
		if(head==NULL){ 
			head=(UPnPNode*)malloc(sizeof(UPnPNode));				
			unserial_unode(head, &pnode);									
			head->elder_brother_node=NULL;
			tail=head;
		}else{						
			tmp=(UPnPNode*)malloc(sizeof(UPnPNode));									
			tmp->elder_brother_node=tail;
			tail->brother_node=tmp;
			tail=tmp;			
			unserial_unode(tail, &pnode);						
		}			
						
		tail->brother_node=NULL;						
		send(sockfd, &client_msg, sizeof(int), 0);							
	}	
	return head;		
}
