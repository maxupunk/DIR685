#ifndef _FCRSS_SOCKET_H_

#define _FCRSS_SOCKET_H_

void serial_node(Net_FcNode *net_node, FcNode *node);
void unserial_node(FcNode *node, Net_FcNode *net_node);
void send_nodes(int connfd, FcNode *node, Net_FcNode net_node);
FcNode* recv_nodes(int sockfd, Net_FcNode net_node);
#endif

		

