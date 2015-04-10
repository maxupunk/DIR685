#ifndef _CTRL_DEFAULT_DEFINE_H_
#define _CTRL_DEFAULT_DEFINE_H_

#include "PltMicroMediaController.h" 

typedef struct socket_node{
	int connfd;
	PLT_MicroMediaController *controller;
}SocketNode;	

void ProcessCommandSocket(PLT_MicroMediaController *controller);
#endif 

