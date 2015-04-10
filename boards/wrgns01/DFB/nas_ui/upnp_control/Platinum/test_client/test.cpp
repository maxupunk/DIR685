#include <stdio.h>
#include <netdb.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <unistd.h>
#include "upnp_ctrl_cmd.h"
#include "packet_serialize.h" 

int main(int argc, char *argv[])
{
	int sockfd, to_server=0, from_server=0, result=0;			
	struct sockaddr_un servaddr;
	PacketNode pnode;		
	UPnPNode *head=NULL;		
	
	to_server=SHOWMS;		
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, SOCKNAME);
	sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
	connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	send(sockfd, &to_server, sizeof(int), 0);
	head=recv_nodes(sockfd, pnode);	
	while(head!=NULL)
	{
		printf("\n client recv data service name %s, guid %s\n", head->service_name, head->guid);
		head = head->brother_node;	
	}
	close(sockfd);		
	return result;			
}
