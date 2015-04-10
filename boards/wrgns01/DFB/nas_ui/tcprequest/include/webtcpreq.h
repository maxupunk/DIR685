#ifndef _WEBTCPREQ_H_ 
#define _WEBTCPREQ_H_ 

#define DEF_SRVPORT 80
#define DEF_MAXDATASIZE 1024
#define CONN 1
#define READ 2
#define FIN 3

typedef struct web_file{
	int sockfd;
	int status_flag;
	int chunked_flag;
	int header_flag;
	int remote_port;
	char *remote_server;
	char *remote_file;
	char *local_file;		
}WebFile;

int web_tcpreq(char *remote_server, char *remote_file, char *local_file);
#endif
