#ifndef _PACKET_SERIALIZE_H_
#define _PACKET_SERIALIZE_H_

#define UPNP_SOCKNAME "/tmp/upnp_ctp_socket"

typedef struct packet_node{	
	int index;
	char guid[1024];
	char service_name[1024];						
}PacketNode;

typedef struct upnp_node{	
	int index;
	char *guid;
	char *service_name;
	struct upnp_node *brother_node;
	struct upnp_node *elder_brother_node;
}UPnPNode;

UPnPNode* get_unode_head(UPnPNode *node);
UPnPNode* recv_nodes_upnp(int sockfd, PacketNode pnode);
void delete_unode_tree(UPnPNode *head);
void unserial_unode(UPnPNode *node, PacketNode *pnode);
void send_nodes_upnp(int connfd, UPnPNode *node, PacketNode pnode);
void serial_unode(PacketNode *pnode, UPnPNode *node);
#endif 

