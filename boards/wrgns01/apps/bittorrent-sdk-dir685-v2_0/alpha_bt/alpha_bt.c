/* vi: set sw=4 ts=4: */
/*
 * alpha_bt.c
 *
 *	for bittorrent-sdk-dir685
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netdb.h>
#include <fcntl.h>
#include <errno.h>

#include <dtrace.h>

#define HOST            "127.0.0.1"
#define PORT            63521
#define MAX_BUFFER_SIZE	2048
#define MAX_WAIT_TIME	3

static char *	o_host = HOST;
static int		o_port = PORT;
static int	 	o_time=MAX_WAIT_TIME;

static int connect_host()
{
 	fd_set write_fd;
	socklen_t optlen = sizeof(int);
	struct timeval tv;
	int fd, option, flags;
	struct sockaddr_in sa;
	struct hostent *he;
	
	fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(fd < 0)
	{
		return -1;
	}
	if((he=gethostbyname(o_host))==NULL)
	{
		return -1;
	}
	memset(&sa, 0, sizeof(sa));
    sa.sin_family       = AF_INET;
    sa.sin_port         = htons(o_port);
    sa.sin_addr.s_addr  = *((unsigned long *)he->h_addr);
	flags = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
	if (connect(fd, (struct sockaddr *)&sa, sizeof(struct sockaddr)) == -1)
    {
		if (errno == EINPROGRESS)
        {
			FD_ZERO(&write_fd);
            FD_SET(fd, &write_fd);
            tv.tv_sec = o_time;
            tv.tv_usec = 0;
            if (select(fd+1, NULL, &write_fd, NULL, &tv) > 0)
            {
            	if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &option, &optlen)==0)
                {
                	if (option == 0)
                    {
                    	flags = fcntl(fd, F_GETFL);
                        fcntl(fd, F_SETFL, flags & ~O_NONBLOCK);
                        return fd;
                    }
                }
            }
			close(fd);
			fd =0;
			d_info("%s: Can not connect to %s:%d\n",__FUNCTION__,o_host, o_port);
			return -1;
		}
	}
	
   return 0;
}

/*
bt server recive data example:
HTTP/1.1 200 OK\r\n
Content-Length: 517\r\n
Content-Type: text/html\r\n
Cache-Control: no-cache\r\n
Connection: keep-alive\r\n
\r\n
{"torrents" : [ .... ]}=
*/

static int send_tcp_data_and_reply(const char *buf, size_t size)
{
	int fd,recv_size=0,body_size=0,total_recv_size=0;
 	fd_set read_fd;
	struct timeval tv;
	char tmp[MAX_BUFFER_SIZE];
	
	if ((fd=connect_host()) < 0) return -1;
	size = send(fd, buf, size, 0);
	if (size < 0)
	{
		d_error("%s: send tcp socket error!!\n",__FUNCTION__);
		close(fd);
		fd=	0;
		return -1;
	}
	
	FD_ZERO(&read_fd);
    FD_SET(fd, &read_fd);
    tv.tv_sec = o_time;
    tv.tv_usec = 0;
    if (select(fd+1, &read_fd, NULL, NULL, &tv) > 0)
    {
		if(FD_ISSET(fd, &read_fd))
		{
			d_dbg("recv data\n");
			
			recv_size = read( fd, tmp, sizeof(tmp)-1);
			tmp[recv_size]='\0';
			//get body size to count and read data from bt server.
			strcpy(tmp,strstr(tmp,"Content-Length: "));
			sscanf(tmp,"Content-Length: %d\r\n",&body_size);
			//skip header
			strcpy(tmp,strstr(tmp,"\r\n\r\n"));
			d_dbg("body_size(%d)\n",body_size);
			total_recv_size=strlen(tmp)-4;	//bc. include '\r\n\r\n'
			//ie must include 'Cache-Control: no-cache'
			printf("Cache-Control: no-cache\r\nContent-Type: text/html%s",tmp);
			
			while(total_recv_size<body_size && (recv_size = read( fd, tmp, sizeof(tmp)-1)) > 0)
			{
				tmp[recv_size]='\0';
				printf("%s",tmp);
				total_recv_size+=recv_size;
				d_dbg("while2 total_recv_size(%d)=%s=\n",total_recv_size,tmp);
			}
		}
	}
	else
	{
		d_dbg("%s: Debug 1!\n",__FUNCTION__);
	}
	
	close(fd);
	fd=	0;
	return 0;
}

int bt_main(int argc, char * argv[], char * env[])
{
	char *pURI,buf[MAX_BUFFER_SIZE];
	int cmd_len=0;
	
 	d_output_file("/dev/console");

	d_dbg("start %s\n",__FUNCTION__);
	
	pURI 		= getenv("REQUEST_URI");
	
/*
Add new torrent have two method, 
1st:Post torrent-add?start=yes
	Define on mathopd upload.c file.
2nd:Get torrent-add?url=http://xxx.xxxx.xxx
	Web query string use 'torrent-add-url', so this must change original string.
*/
	if(!strncasecmp(pURI, "/api/torrent-add-url", 20))
		cmd_len+=sprintf(buf+cmd_len, "GET /api/torrent-add%s HTTP/1.1\r\n", strchr(pURI,'?'));
	else
		cmd_len+=sprintf(buf+cmd_len, "GET %s HTTP/1.1\r\n", pURI);
	cmd_len+=sprintf(buf+cmd_len, "Accept: */*\r\nHost: %s\r\nKeep-Alive: 300\r\nConnection: keep-alive\r\n\r\n", o_host);
	send_tcp_data_and_reply(buf,strlen(buf));
	
    return 0;
}
