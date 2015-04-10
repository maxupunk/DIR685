#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define DEF_TIMEOUT 5
#define DEF_SRVPORT 80
#define DEF_MAXDATASIZE 1024
#define REMOTE_SERVER_NAME_MAX_LEN  128
#define REMOTE_FILE_NAME_MAX_LEN	256

static char DefaultLocalFName[]="/var/remoteFwInfo";
static char *pgRemoteFile=NULL;
static char *pgRemoteServ=NULL;
static char *pgLocalFile = NULL;
static int 	gRemotePort= DEF_SRVPORT;
static char *pgUser = NULL;
static char *pgPass = NULL;
static char *pgSenddataFile=NULL;
static int  gRound = 0;

static int  gTimeout=DEF_TIMEOUT, gSkip=1;

int get_senddata_infile(char *buf,int buf_size ,char *File);

static int connectHost(char *HostName, const int PortNo)
{
 int sockfd, option, flags;
 fd_set write_fd;
 socklen_t optlen = sizeof(int);
 struct timeval tv;
 struct hostent *host;
 struct sockaddr_in serv_addr;

 if((host=gethostbyname(HostName))==NULL)
 {
    fprintf(stderr, "Can not get host by name: %s\n", HostName);
 }
 else
 {
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
       fprintf(stderr, "Can not create socket\n");
    }
    else
    {
       flags = fcntl(sockfd, F_GETFL);
       fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

       serv_addr.sin_family=AF_INET;
       serv_addr.sin_port=htons(PortNo);
       serv_addr.sin_addr = *((struct in_addr *)host->h_addr);
       bzero(&(serv_addr.sin_zero),8);
       if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1)
       {
			if (errno == EINPROGRESS)
			{
				FD_ZERO(&write_fd);
				FD_SET(sockfd, &write_fd);
				tv.tv_sec = gTimeout;
				tv.tv_usec = 0;
				if (select(sockfd+1, NULL, &write_fd, NULL, &tv) > 0)
				{
					if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &option, &optlen)==0)
					{
						if (option == 0)
						{
                            flags = fcntl(sockfd, F_GETFL);
                            fcntl(sockfd, F_SETFL, flags & ~O_NONBLOCK);
							return sockfd;
						}
					}
				}
			}
			close(sockfd);
			fprintf(stderr, "Can not connect to %s:%d\n",HostName, PortNo);
         }
      }
   }
 return -1;
}

static void showusage(void)
{
	printf("Usage:fwUpgrd -s Srv -p Port -f RemoteFileName [Options]\n");
	printf("\t-s	Remote server ip or DNS Name\n");
	printf("\t-p	Remote server port\n");
	printf("\t-f	Remote File path and Name you want to get\n");
	printf("\t-d	data File path the content you want to send,default we will using the firmware ing\n");
	printf("\tOptions:\n");
	printf("\t\t-l LocalFileNamn \t\t Local File path and Name you want to saved\n");
	printf("\t\t-t timeout       \t\t connection timeout, default is 5!\n");
	printf("\t\t-r Round         \t\t Retry times when connection failed, default is 0\n");
	printf("\t\t-u account       \t\t username if the Server is need to do authentication\n");
	printf("\t\t-a passwd        \t\t password if the Server is need to do authentication\n");
	printf("\t\t-g       		 \t\t keep http header\n");
 
}

/* parse arguments */
static void parse_args(int argc, char * argv[])
{
	int opt;

	while ((opt = getopt(argc, argv, "gd:s:p:f:l:t:r:u:a:")) > 0)
	{
		switch (opt)
		{
		case 'd':
		    pgSenddataFile = optarg;
		    break;
		case 's':
		    pgRemoteServ = optarg;
		    break;
		case 'p':
			gRemotePort = atoi(optarg);
			break;
		case 'f':
			pgRemoteFile=optarg;
			break;
		case 'l':
			pgLocalFile=optarg;
			break;
		case 't':
			gTimeout=atoi(optarg);
			if(gTimeout<=0)
			  gTimeout=DEF_TIMEOUT;
			break;
		case 'r':
			gRound = atoi(optarg);	
			break;
		case 'u':
			pgUser = optarg;
			break;
		case 'a':
			pgPass = optarg;
			break;
		case 'g':
			gSkip = 0;
			break;
		default:
			showusage();
			exit(0);
		}
	}
}
/* to get chunk size(hex). return value change to decimal */
int get_chunked_value(char *pbuf)
{
	char tmp[64];
	int i=0;
	
	strncpy(tmp,pbuf,sizeof(tmp));
	for(i=0;*pbuf != '\n';pbuf++ && i++);
	tmp[i-1]='\0';
	return strtol(tmp,NULL,16);
}
	
int main(int argc, char *argv[])
{
 FILE *pFile=stdout;
 int  connsocket, recvbytes, i, c, state=0;
 char buf[DEF_MAXDATASIZE];
 int totalrecvbytes=0,have_chunked=0,chunked_value=0,totalchunkedbytes=0;

 if(argc < 6)
 {
    showusage();
    return 0;
 }

 parse_args(argc, argv);

 if(pgLocalFile== NULL)
	pgLocalFile = DefaultLocalFName;
 
 if(!get_senddata_infile(buf,DEF_MAXDATASIZE,pgSenddataFile))
   return -1;
 
 //fprintf(stderr,"===ser %s local file %s port=%d\n",pgRemoteServ,pgLocalFile,gRemotePort);
 if((connsocket=connectHost(pgRemoteServ, gRemotePort))== -1)
   return -1;
 if ((recvbytes=send(connsocket, buf, strlen(buf), 0)) ==-1)
 {
    fprintf(stderr, "can not send request message\n");
 }
 else
 {
   if(pgLocalFile && NULL==(pFile=fopen(pgLocalFile, "w")))
		pFile=stdout;

   while(1)
   {
	  memset(buf, 0, DEF_MAXDATASIZE);
      recvbytes = recv(connsocket, buf, DEF_MAXDATASIZE, 0);
      i=0;
      
      //+++ add by teresa 2008/4/8 07:09下午
      //first time to do
      if(totalrecvbytes==0)
      {
	      if(strstr(buf,"Transfer-Encoding: chunked"))
	      {
	      	have_chunked = 1;
			//fprintf(stderr,"have chunked\n");
	      }
	  }
	  //--- add by teresa

	  //+++ add by siyou 2006/8/21 08:47下午 ---//
	  // to prevent block when remote send rst.
	  // the following code have "if(state<6) continue" which cause program block.
	  if ( recvbytes <= 0 )
			break;
	  //--- add by siyou 2006/8/21 08:47下午 ---//

      if(gSkip)
      {
          while(state<6 && i<recvbytes)
            {
             c=buf[i++];
             switch(state)
               {
                case 0:
                  switch(c)
                    {
                     default:       state=1; break;
                     case '\r':
                     case '\n':
                     case ' ':
                     case '\t':
                          break;                    
                    }
                  break;

                case 1:
                  switch(c)
                    {
                     case '\r':     state=2; break;
                     case '\n':     state=3; break;
                    }
                  break;

                case 2:
                  switch(c)
                    {
                     default:       state=1; break;
                     case '\n':     state=4; break;
                    }
                  break;

                case 3:
                  switch(c)
                    {
                     default:       state=1; break;
                     case '\n':     state=6; break;
                    }
                  break;

                case 4:
                  switch(c)
                    {
                     default:       state=1; break;
                     case '\r':     state=5; break;
                    }
                  break;

                case 5:
                  switch(c)
                    {
                     default:       state=1; break;
                     case '\n':     state=6; break;
                    }
                  break;
               }
            }
          if(state<6)
            continue;
          else
            gSkip=0;
        }

		if(recvbytes>0)
		{
			buf[recvbytes]=0;
			//fprintf(pFile, "%s",buf+i);
			
			if(i<recvbytes)
			{
		        //+++ add by teresa 2008/4/8 07:09下午
		        if(have_chunked)
		        {
		        	char *pstr;
		        	int j;
		        	
		        	pstr = buf+i;
		        	totalrecvbytes += recvbytes-i;
		        	recvbytes -= i;	//use recvbytes to count the read bytes
					packet_have_two_chunk:
			        if ( totalchunkedbytes >= chunked_value ) //to get the first time value of chunk.
			        {
			        	chunked_value = get_chunked_value( pstr );
						//fprintf(stderr,"---next chunk value =%d\n\n",chunked_value);
						if (chunked_value == 0)	 //mean finished.
							break;
			        	for( j=0; j<recvbytes-1 && *pstr++!='\n' ; j++);
			        	recvbytes -= (j+1);	//use recvbytes to count the read bytes
						totalchunkedbytes = 0;
			    	}
			    	
					/*
					chunk format: chunk-size [ chunk-extension ] CRLF chunk-data CRLF
					chunk-size is in hex value.
					*/
					if( (totalchunkedbytes + recvbytes) >= chunked_value)
					{
						//fprintf(stderr,"read finished or over., %d, %d\n",(totalchunkedbytes + recvbytes),chunked_value);
						fwrite(pstr, 1, chunked_value-totalchunkedbytes, pFile);
						//fprintf(stderr,pcapstring);
						pstr += chunked_value-totalchunkedbytes+2; //skip 0d 0a at the end of chunk.
						recvbytes -= chunked_value-totalchunkedbytes+2;
						totalchunkedbytes = chunked_value;
						//fprintf(stderr,pstr);
					}
					
					if( totalchunkedbytes >= chunked_value)
						goto packet_have_two_chunk;
						
					totalchunkedbytes += recvbytes;
					//fprintf(stderr,"read total chunk = %d\n",totalchunkedbytes);
					fwrite(pstr, 1, recvbytes , pFile);
				}
				//--- add by teresa 2008/4/8 07:09下午
				else
					fwrite(buf+i, 1, recvbytes-i, pFile);
			}
			continue;
		}
     	break;
     }
	if(pFile!=stdout)
		fclose(pFile);
  }
 close(connsocket);
 return 0;
}
int get_senddata_infile(char *buf,int buf_size ,char *File)
{
	 FILE *pFile;
	 
	 memset(buf,0,buf_size);
	 if(pgSenddataFile)
	 {
	 	  if(NULL != (pFile=fopen(pgSenddataFile,"r")))
	 	  {
		 	  int n;
		 	  n=fread(buf,buf_size,1,pFile);
		 	  if(n==buf_size)
	 	  		fprintf(stderr,"file size to larg please modify code\n");
	 	  	fclose(pFile);
	 	  }
	 	  else
	 	  {
	 	    fprintf(stderr,"open file file fail %s\n",pgSenddataFile);
	 	    return 0;
	 	  }
	 }
	 else
	 {
	 	  int n=0;
	 	  //fprintf(stderr,"pgRemoteFile=%s=\n",pgRemoteFile);
	 	  //default using the firmware info get
	 	  
//	 	  n+=sprintf(buf+n, "GET %s HTTP/1.0\r\n", pgRemoteFile);
//	 	  n+=sprintf(buf+n	, "Host: %s:80\r\nUser-Agent: DirectFB/1.1.1\r\nAccept: */*\r\nConnection: Close\r\n\r\n",pgRemoteServ); 
	 	  
	 	  n+=sprintf(buf+n, "GET %s HTTP/1.1\n", pgRemoteFile);
	 	  n+=sprintf(buf+n	, "Accept: */*\nUser-Agent: FwUpgrade\nHost: %s\nConnection: Close\n\n",pgRemoteServ); 

	 }
	 
	 //fprintf(stderr, "Dump the buf=%s!\n", buf);
	 return 1;
}
