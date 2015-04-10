#include <stdio.h>
#include <sys/un.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "str_tool.h"	
#include "fcrss_parser.h"

void serial_node(Net_FcNode *net_node, FcNode *node){					
	net_node->ttl=node->ttl;	
	net_node->duration=node->duration;	
	sam_strnarr((char*)&net_node->title, node->title);
	sam_strnarr((char*)&net_node->this_guid, node->this_guid);		
	sam_strnarr((char*)&net_node->remote_file_path, node->remote_file_path);							
	sam_strnarr((char*)&net_node->local_file_path, node->local_file_path);							
	//print_netnode(net_node);
}	

void unserial_node(FcNode *node, Net_FcNode *net_node){	
	node->ttl=net_node->ttl;
	node->duration=net_node->duration;
	node->title=sam_strncpy(net_node->title, strlen(net_node->title));
	node->this_guid=sam_strncpy(net_node->this_guid, strlen(net_node->this_guid));
    node->remote_file_path=sam_strncpy(net_node->remote_file_path, strlen(net_node->remote_file_path));			
	node->local_file_path=sam_strncpy(net_node->local_file_path, strlen(net_node->local_file_path));		
}

void send_nodes(int connfd, FcNode *node, Net_FcNode net_node)
{
	FcNode *head=NULL;					
	int serv_msg=1, client_msg=100;			
	head=get_fcnode_head(node);														
	while(head!=NULL){			
		send(connfd, &serv_msg, sizeof(int), 0);																	
		recv(connfd, &client_msg, sizeof(int), 0);				
		serial_node(&net_node, head);		
		send(connfd, &net_node, sizeof(net_node), 0);									
		recv(connfd, &client_msg, sizeof(int), 0);			
		head=head->brother_node;								
	}			
	serv_msg=0;
	send(connfd, &serv_msg, sizeof(int), 0);						
}	

FcNode* recv_nodes(int sockfd, Net_FcNode net_node)
{		
	FcNode *head=NULL, *tail=NULL, *tmp=NULL;	
	int serv_msg, client_msg=1;		
	
	while(1){				
		recv(sockfd, &serv_msg, sizeof(int), 0);			
		if(serv_msg==0) break;						
		send(sockfd, &client_msg, sizeof(int), 0);					
		recv(sockfd, &net_node, sizeof(net_node), 0);		
					
		if(head==NULL){ 
			head=(FcNode*)malloc(sizeof(FcNode));				
			unserial_node(head, &net_node);									
			head->elder_brother_node=NULL;
			tail=head;
		}else{						
			tmp=(FcNode*)malloc(sizeof(FcNode));									
			tmp->elder_brother_node=tail;
			tail->brother_node=tmp;
			tail=tmp;			
			unserial_node(tail, &net_node);						
		}			
				
		tail->father_node=NULL;													
		tail->son_node=NULL;				
		tail->brother_node=NULL;						
		send(sockfd, &client_msg, sizeof(int), 0);							
	}	
	return head;		
}
