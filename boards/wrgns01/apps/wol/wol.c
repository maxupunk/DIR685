/*
* Step 1. Waiting udp or tcp packet(ex:WoL<udp> packet-port:9)
* Step 2. Send packet to Broadcast(ex:"192.168.0.255")
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <net/if.h>

#define MAXBUFLEN 1500
#define MAXPENDING 5    /* Maximum outstanding connection requests */

static char * o_udpport	 = NULL;	
static char * o_tcpport	 = NULL;
static char * o_broadcastinf= NULL;	
static char * o_waninf= NULL;	

enum Choose{
	DO_UDP,
	DO_TCP,
	DO_BOTH
};

#define debug 0

#if debug
	#define dprintf  printf
#else
	#define dprintf(x,args...)
#endif

/************start of parse args******************/

static void cleanup_exit(int exit_code)
{
	exit(exit_code);
}

static void show_usage(int exit_code)
{
	printf("Usage: server [OPTIONS]\n");
	printf("  -h                    show this help message.\n");
	printf("  -u                    open udp socket on this port and recevied data \n");
	printf("  -t                    open tcp socket on this port and recevied data \n");
	printf("  -w	                get packet from wan interface's ip \n");
	printf("  -i	                send packet to this interface's broadcast ip \n");
	cleanup_exit(exit_code);
}

static void parse_args(int argc, char * argv[])
{
	int opt;

	while ((opt = getopt(argc, argv, "hu:t:w:i:")) > 0)
	{
		switch (opt)
		{
		case 'h':	show_usage(0);				break;
		case 'u':	o_udpport	= optarg;		break;
		case 't':	o_tcpport	= optarg;		break;
		case 'w':	o_waninf	= optarg;		break;
		case 'i':	o_broadcastinf	= optarg;		break;
		default:	show_usage(-1);				break;
		}
	}
}
/***************end of parse args***************/

/*
  get_addr
     Retrieve the ipv4 broadcast or inet address for the specified network interface.

  Inputs:  ifn - the name of the network interface:
                 e.g. eth0, eth1, ppp0, plip0, plusb0 ...
           fd - socket 
  Outputs: ip - returned broadcast or inet address.
 */ 
char* get_addr(int fd,const char *ifn)
{
	struct ifreq ifr; /* points to one interface returned from ioctl */
	char *ip=NULL;
	int return_val=-1;
	
	strncpy (ifr.ifr_name, ifn, sizeof(ifr.ifr_name));

	/* Fetch the broadcast address of this interface by calling ioctl() */
	return_val = ioctl(fd,SIOCGIFBRDADDR, &ifr);
		
	if (return_val == 0 ) 
	{			
		if (ifr.ifr_broadaddr.sa_family == AF_INET) 
		{
			struct sockaddr_in *sin_ptr = (struct sockaddr_in *)&ifr.ifr_broadaddr;
			dprintf ("get_broad_addr: broadaddr %s\n",inet_ntoa(sin_ptr->sin_addr));
			ip=inet_ntoa(sin_ptr->sin_addr);
		} 
		else 
		{
			printf ("Wrong family for broadcast interface %s",ifn);
		}
	}
	else 
	{
		printf ("Get broadcast for interface %s failed\n", ifn);
	}	
	
	return ip;	
	
} /* end get_broad_addr() */

//////////////////START OPEN SOCKER//////////////////////////
/*
  open_udp_socket / open_tcp_socket
     open udp or tcp socket.

  Inputs:  udp_port or tcp_port - open this socket port for recv packets.
           
  Outputs: udp_sockfd or tcp_sockfd - returned udp or tcp socket.
 */
int open_udp_socket(char *udp_port)
{
    int udp_sockfd;
	struct sockaddr_in addr;
    unsigned short ServPort;     /* Server port */
	struct ifreq interface;
		
    ServPort = atoi(udp_port);  /* local port */
    
	udp_sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if( udp_sockfd== -1 ) 
    {
        perror("open_udp_socket error: socket\n");
        return -1;
    }

	//bind to device
	strncpy(interface.ifr_ifrn.ifrn_name, o_waninf , IFNAMSIZ);
	if (setsockopt(udp_sockfd, SOL_SOCKET, SO_BINDTODEVICE,(char *)&interface, sizeof(interface)) < 0)
	{
		printf("SO_BINDTODEVICE fail\n");
		close(udp_sockfd);
		return 0;
	}
 
 	 /* set up destination address */
	 memset(&addr,0,sizeof(struct sockaddr_in));
	 addr.sin_family=PF_INET;
	 addr.sin_addr.s_addr=htonl(INADDR_ANY); 
	 addr.sin_port=htons(ServPort);
			
    if ( bind(udp_sockfd,(struct sockaddr *) &addr,sizeof(struct sockaddr_in))== -1) 
    {
        perror("open_udp_socket error: bind\n");
        return -1;
    }
    
    dprintf("open_udp_socket:Successed\n");   
    
    return udp_sockfd;
}

int open_tcp_socket(char *tcp_port)
{
    int tcp_sockfd;
    struct sockaddr_in ServAddr; /* Local address */
    unsigned short ServPort;     /* Server port */

    ServPort = atoi(tcp_port);  /* local port */

    /* Create socket for incoming connections */
    if ((tcp_sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        perror("socket() failed");
    	return -1;
	} 
	
    /* Construct local address structure */
    memset(&ServAddr, 0, sizeof(ServAddr));   /* Zero out structure */
    ServAddr.sin_family = AF_INET;                /* Internet address family */
    ServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    ServAddr.sin_port = htons(ServPort);      /* Local port */

    /* Bind to the local address */
    if (bind(tcp_sockfd, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) < 0)
    {
        perror("bind() failed");
		return -1;
	}
    
    /* Mark the socket so it will listen for incoming connections */
    if (listen(tcp_sockfd, MAXPENDING) < 0)
    {
        perror("listen() failed");
		return -1;
	}
	    
    dprintf("open_tcp_socket:Successed\n");
    	
	return tcp_sockfd;
}
//////////////////END OPEN SOCKER//////////////////////////

//////////////////START RECV DATA//////////////////////////
/*
  recv_from_udp / recv_from_tcp
     recv udp or tcp packet.

  Inputs:  udp_fd - the name of the udp socket
           buf - store recv data
           
  Outputs: numbytes - returned data length.
 */ 
int recv_from_udp(int udp_fd,char *buf)
{
    size_t addr_len;
	struct sockaddr_in addr;
	int numbytes;
		 
    dprintf("\nrecv_from_udp: waiting to recvfrom...\n");

    addr_len = sizeof(struct sockaddr_in);
 	
    if ((numbytes = recvfrom(udp_fd, buf, MAXBUFLEN , 0,(struct sockaddr *)&addr, &addr_len)) == -1) 
    {
        perror("recvfrom failed");
        return -1;
    }
 	
    dprintf("recv_from_udp: got packet from %s\n", inet_ntoa(addr.sin_addr));
    dprintf("recv_from_udp: packet is %d bytes long\n", numbytes);
    
    buf[numbytes] = '\0';
	
    return numbytes;
}

int recv_from_tcp(int tcp_fd,char *buf)
{
    int clntSock;                /* Socket descriptor for client */    
    struct sockaddr_in ClntAddr; /* Client address */
    unsigned int clntLen;        /* Length of client address data structure */
    
    int numbytes=0;
	int ret=0;
	fd_set fdread;    
	struct   timeval   timeout;  
    
    dprintf("\nrecv_from_tcp: waiting to recvfrom...\n");
	
    /* Set the size of the in-out parameter */
    clntLen = sizeof(ClntAddr);

    /* Wait for a client to connect */
    if ((clntSock = accept(tcp_fd, (struct sockaddr *) &ClntAddr,&clntLen)) < 0)
    {
        perror("accept() failed");
		return -1;
	}

	dprintf("client %s\n", inet_ntoa(ClntAddr.sin_addr));	
	
	/* set timeout=3 sec avoid cannot recv data */	
	FD_ZERO(&fdread);     
	FD_SET(clntSock,&fdread);  
	timeout.tv_sec=3;   
	timeout.tv_usec=0;  
	
	ret=select( clntSock+1, &fdread, NULL, NULL, &timeout);
	
	if(ret==0) /*select timeout*/
	{
		printf("select timeout\n");   		
		close(clntSock);    /* Close client socket */
		return ret;
	}
	else if(ret==-1) /*select error*/
	{
		printf("select err\n");   	
		close(clntSock);    /* Close client socket */
		return ret;			
	}
	
    /* Receive message from client */
	if(ret>0 && FD_ISSET(clntSock,&fdread))   
	{
	    if ((numbytes = recv(clntSock, buf, MAXBUFLEN, 0)) < 0)
	        perror("recv() failed");			
	}
	
	close(clntSock);    /* Close client socket */

	dprintf("recv_from_tcp:recv_byte %d\n",numbytes); 	
	
	return numbytes;
}

//////////////////END RECV DATA//////////////////////////

//////////////////START SEND BROADCAST PACKET//////////////////////////
/*
  send_broadcast
     send data which recv from socket via broadcast.

  Inputs:  buf - data which recv from socket
           numbytes - data length
           ifname - the name of the network interface:
                 e.g. eth0, eth1, ppp0, plip0, plusb0 ...
           broadcast_port - send broadcast to this port
                 
  Outputs: numbytes - returned send data length.
 */
int send_broadcast(char *buf,int numbytes,char *ifname,char *broadcast_port)
{
    int sockfd;
    struct sockaddr_in their_addr; // connector's address information
	char *addr;
    int broadcast=1;  
    struct hostent *he;
    unsigned short ServPort;     /* Server port */
    
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd <0 ) 
    {
        perror("socket() failed");
        return -1;
    }

	addr=get_addr(sockfd,ifname);	
	dprintf("send_broadcast: broad_ip %s\n",addr);
		
	he=gethostbyname(addr);
    if(he == NULL) 
    {  // get the host info
        herror("gethostbyname failed");
        return -1;
    }  

    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast,sizeof(broadcast)) == -1) 
    {
        perror("setsockopt (SO_BROADCAST) failed");
        return -1;
    }
	
	ServPort=atoi(broadcast_port);
    
    their_addr.sin_family = AF_INET;     // host byte order
    their_addr.sin_port = htons(ServPort); // short, network byte order
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(their_addr.sin_zero, '\0', sizeof their_addr.sin_zero);

	numbytes=sendto(sockfd, buf, numbytes, 0,(struct sockaddr *)&their_addr, sizeof(their_addr));
    if (numbytes == -1) 
    {
        perror("sendto failed");
        return -1;
    }

    dprintf("sent %d bytes to %s\n", numbytes, inet_ntoa(their_addr.sin_addr));
    
    close(sockfd);
    
    return numbytes;
}
//////////////////END SEND BROADCAST PACKET//////////////////////////

void choose_type(int type,int sockfd)
{
	int recv_byte=0;
	char buf[MAXBUFLEN];  	

	if(type==DO_UDP)
	{
		recv_byte=recv_from_udp(sockfd,buf); 
		if(recv_byte >=0 )  /*recv data > 0, then send to broadcast(inf:o_broadcastinf),else go back to main func*/
		{
			dprintf("---Start send\n");
    		recv_byte=send_broadcast(buf,recv_byte,o_broadcastinf,o_udpport);   	    
			dprintf("send recv_byte %d\n",recv_byte); 
    	}	
	}
	else if(type==DO_TCP)
	{
		recv_byte=recv_from_tcp(sockfd,buf);   			
		if(recv_byte >=0 ) /*recv data > 0, then send to broadcast(inf:o_broadcastinf),else go back to main func*/
		{
			dprintf("---Start send\n");
    		recv_byte=send_broadcast(buf,recv_byte,o_broadcastinf,o_tcpport);   	    
			dprintf("send recv_byte %d\n",recv_byte); 
    	}		
	}
}

int main(int argc, char *argv[])
{
	int udp_fd=0,tcp_fd=0;//socket
	fd_set rfds;
	int max_fd=0;
	int retval=0;
	int choose=0;

	parse_args(argc, argv);	
	if(o_waninf==NULL)
	{
		printf("ERROR enter argv! Stop wol\nplease enter wan interface name\n");
		return -1;
	}
	else if(o_broadcastinf==NULL)
	{
		printf("ERROR enter argv! Stop wol\nplease enter interface to send broadcast packet\n");
		return -1;
	}
	else if(o_udpport==NULL&&o_tcpport!=NULL)
		choose=DO_TCP;
	else if(o_udpport!=NULL&&o_tcpport==NULL)
		choose=DO_UDP;
	else if(o_udpport!=NULL&&o_tcpport!=NULL)
		choose=DO_BOTH;
	else 
	{
		printf("ERROR enter argv! Stop wol\n");
		return -1;
	}
			    
    dprintf("\n---START Open Socket\n"); 

    if(choose==DO_UDP||choose==DO_BOTH)
		udp_fd=open_udp_socket(o_udpport);	    	
    if(choose==DO_TCP||choose==DO_BOTH)
		tcp_fd=open_tcp_socket(o_tcpport);
	
	if(choose==DO_BOTH)
		max_fd = (tcp_fd>udp_fd)?tcp_fd:udp_fd;	
	
	while(1)
	{		
		if(choose==DO_BOTH)
		{
			FD_ZERO(&rfds);
			FD_SET(udp_fd, &rfds); 
			FD_SET(tcp_fd, &rfds); 	
			
			dprintf("\n----select sock\n");
			retval = select(max_fd + 1, &rfds, NULL, NULL, NULL); 
			
			if(retval < 0)
			{
				perror("select failed!");
				break;
			}				
			if(FD_ISSET(udp_fd,&rfds))
			{
				dprintf("---udp_fd is ready \n");	
				choose_type(DO_UDP,udp_fd);
		    }
			else if(FD_ISSET(tcp_fd,&rfds))
			{
				dprintf("---tcp_fd is ready \n");	
				choose_type(DO_TCP,tcp_fd);	
			}	
		}
		else if(choose==DO_UDP)
		{
			choose_type(DO_UDP,udp_fd);			
		}
		else if(choose==DO_TCP)
		{
			choose_type(DO_TCP,tcp_fd);					
		}
					    	
	}
    
    close(udp_fd);
    close(tcp_fd);    
	
	return 1;
}
