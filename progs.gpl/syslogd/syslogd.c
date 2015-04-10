/* vi: set sw=4 ts=4: */
/*
 * Mini syslogd implementation for busybox
 *
 * Copyright (C) 1999,2000 by Lineo, inc. and Erik Andersen
 * Copyright (C) 1999,2000,2001 by Erik Andersen <andersee@debian.org>
 *
 * Copyright (C) 2000 by Karl M. Hegbloom <karlheg@debian.org>
 *
 * "circular buffer" Copyright (C) 2001 by Gennady Feldman <gfeldman@cachier.com>
 *
 * Maintainer: Gennady Feldman <gena01@cachier.com> as of Mar 12, 2001
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <paths.h>
#include <signal.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <sys/param.h>
#if SYSLOG_AP
#include <sys/sysinfo.h>	/*	Timestamp synchronized , Jordan_2007_01_15	*/
#include "lrgbin.h"
#include "rgdb.h"
#endif /*SYSLOG_AP*/
#ifdef REMOTE_LOG/*	RemoteLog_2007_01_19 , Jordan	start */
//#define ALPHA_DBG	/*Jordan test 2007/1/17 06:54下午*/
#include <sys/file.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/signal.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#endif/* RemoteLog_2007_01_19 , Jordan	end */

/* SYSLOG_NAMES defined to pull some extra junk from syslog.h */
#define SYSLOG_NAMES
#include <sys/syslog.h>
#include <sys/uio.h>
#define ASYSLOG_NAMES
#include <asyslog.h>
#include <elbox_config.h>
#ifdef REMOTE_LOG/*	RemoteLog_2007_01_19 , Jordan	start */
static const int DEFDATALEN = 56;
static const int MAXIPLEN = 60;
static const int MAXICMPLEN = 76;
#endif/* RemoteLog_2007_01_19 , Jordan	end */
enum   BOOL {FALSE=0, TRUE};
#define BUF_SIZE 8192

static int  proclog=TRUE;
static int 	asyslogflag = 0;
#if SYSLOG_AP
#define defMaxLine 500
static int 	aloglevel    = 5; 
static int  first_init = 0;
static char *fw_version = NULL;
#else
#define defMaxLine 400
#endif
/* Path for the file where all log messages are written */
/*schedule_smtp.2008_03_26.allen*/
#define __LOG_FILE "/var/log/messages"
#define SMTP_LOG_FILE "/var/log/smtpmsg"

/* Path to the unix socket */
static char lfile[MAXPATHLEN];
static char *logFilePath = __LOG_FILE;
#ifdef AP_SMTP_SCHEDULE
static char *tmplogPath;
#endif

/* interval between marks in seconds */
//static int MarkInterval = 20 * 60;

/* localhost's name */
static char LocalHostName[64];

#ifdef REMOTE_LOG
#include <netinet/in.h>
static int  remotefd 		= -1;	 /* udp socket for logging to remote host */
static char *RemoteHost; 			 /* where do we log? */
static int  RemotePort 		= 514;	 /* what port to log to? */
static int  doRemoteLog 	= FALSE; /* To remote log or not to remote log. */
static int  local_logging 	= FALSE;
#endif

#if SYSLOG_AP
static int   systimeSynced = FALSE;	/* The flag to show if time has been synchronized. Jordan , 2007/1/4 03:23下午 */
static char * o_unixsock = NULL;	/* syslog_2007_04_09, Jordan */
#endif
#ifdef REMOTE_LOG
static int	First_init_RemoLog = 0;	/* The flag to judge if the remote log has sent once. */
static int  RemoLog_connection_status =0;
static int	SvrReady = 0;
	struct 	sockaddr_in remoteaddr;
	struct	 hostent *hostinfo;
#endif
/*	RemoteLog_2007_01_19 , Jordan	end */
/*smtp_2007_02_16 , Jordan */
#ifdef AP_SMTP
static int	SMTP_enable		  = 0;
#endif
/* joanw add for mailing log message. 2004.04.14 */
/* initial the variables of mail				 */
static int  mail_log      = 0;						/* -m , Enable mail log message.		*/
static char *mail_subject = "Log Message.";			/* -s , the subject of the mail.		*/
static char *mail_host    = NULL;					/* -S , SMTP server IP.					*/
//static char *mail_port    = "25";				/* -P , Port for contacting via SMTP.	*/
char 		mail_from[128]= "admin@";
char 		*src_host     = "RG-Administrator";		/* -H , The host name of SMTP Client.	*/
static int  mime_style    = 0;						/* -M , Use the MIME style.				*/
/*syslogd_2008_03_03.allen*/
static char *sender_addr   = NULL;			/* -a , sender e-mail address .	        */
static char *receiver_addr = NULL;			/* -r , receiver e-mail address .	*/

static int	send_mail	  = 0; 
static int	tlog		  = 0;						/* -t , use tlog.						*/
static char *log_path 	  = "/var/log/messages";	/* the path of log message.				*/
static char *temp_log_path = "/var/run/mail.log";	/* the path of the renamed log message.	*/
/*schedule_smtp.2008_03_26.allen*/
//static char *smtp_path	  = "/usr/sbin/sendmail";		/* the path of smtp client				*/
static char *username	  = NULL;				/* -u ,the username of sendmail use. */
static char *password	  = NULL;				/* -p ,the password of sebdmail use. */
static int auth_SMTP_enable = 0;                    /* -A , Enable Auth SMTP */ 

#define MAXLINE         	1024					/* maximum line length */

static void show_usage(char **argv)
{
	char *p = argv[0];

	while (strchr(p, '/'))
	{
		p=strchr(p, '/')+1;
	}

	printf("\n");
	printf("\n");
	printf("Usage: %s [-l level] [-d]\n", p);
	printf("\n");
	printf("Syslogd Options:\n");
	printf("\n");
	printf("  -p                    :Proclog\n");
	printf("  -n                    :Don't do fork.\n");
	printf("  -O path               :Log File Path.\n");
#ifdef REMOTE_LOG
	printf("  -R remote_ip:port     :Remote logging.\n");
#endif
	printf("  -L                    :Local logging.\n");
#ifdef IPC_SYSLOG
	printf("  -C                    :Circular logging the message.\n");
#endif
#ifdef ASYSLOG_NAMES
	printf("  -F flag_name          :Alphanetworks System Log message flag name.\n");
	printf("	 sysact : system activity\n");
	printf("	 debug  : debug information\n");
	printf("	 attack : attacks\n");
	printf("	 drop   : dropped packet\n");
	printf("	 notice : notice\n");
	printf("  -m                    :Enable mail log message when message file is full.\n");
	printf("\n");
#endif
	printf("Mail Options:\n");
	printf("  -s mail_subject       :Subject\n");
	printf("  -S mailhost           :SMTP Server IP.\n");
	printf("  -P mail_port          :Port where MTA can be contacted via SMTP.\n");
	printf("  -H src_host_name      :Host name to provide as source of message.\n");
	printf("  -M                    :Use MIME-style translation to quoted-printable.\n");
	/*syslogd_2008_03_03.allen*/
	printf("  -a sender_addr        :The sender e-mail address.\n");
	printf("  -r receiver_addr      :The receiver e-maill address.\n");
	
	printf("  -t tlog_file_path     :the tlog file path.\n");
	printf("  -A                    :Use authentication SMTP server\n");
	printf("\n");
	return;
}
static void perror_msg_and_die(const char *s, ...)
{
	va_list p;
	va_start(p, s);

	fflush(stdout);
	fprintf(stderr, "syslogd: ");
	vfprintf(stderr, s, p);
	fprintf(stderr, ": %s\n", strerror(errno));
	va_end(p);
	exit(EXIT_FAILURE);
}

/* circular buffer variables/structures */
#ifdef IPC_SYSLOG
#if __GNU_LIBRARY__ < 5
#error Sorry.  Looks like you are using libc5.
#error libc5 shm support isnt good enough.
#error Please disable IPC_SYSLOG
#endif

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

/* our shared key */
static const long KEY_ID = 0x414e4547; /*"GENA"*/

/* Semaphore operation structures */
static struct shbuf_ds 
{
	int  size;               /* size of data written	*/
	int  head;               /* start of message list	*/
	int  tail;               /* end of message list		*/
	char data[1];            /* data/messages			*/
} *buf = NULL;               /* shared memory pointer	*/

static struct sembuf SMwup[1] = {{1, -1, IPC_NOWAIT}};		/* set SMwup 			*/
static struct sembuf SMwdn[3] = {{0, 0}, {1, 0}, {1, +1}};	/* set SMwdn 			*/

static int    shmid 			= -1;						/* ipc shared memory id	*/
static int    s_semid 			= -1;						/* ipc semaphore id		*/
int			  data_size 		= 32000;					/* data size			*/
int			  shm_size 			= 32000 + sizeof(*buf);		/* our buffer size		*/
static int	  circular_logging 	= FALSE;


/*
 * sem_up - up()'s a semaphore.
 */
static inline void sem_up(int semid)
{
	if ( semop(semid, SMwup, 1) == -1 )
		perror_msg_and_die("semop[SMwup]");
}

/*
 * sem_down - down()'s a semaphore
 */
static inline void sem_down(int semid)
{
	if ( semop(semid, SMwdn, 3) == -1 )
		perror_msg_and_die("semop[SMwdn]");
}


void ipcsyslog_cleanup(void){
	printf("Exiting Syslogd!\n");
	if (shmid != -1)
		shmdt(buf);

	if (shmid != -1)
		shmctl(shmid, IPC_RMID, NULL);
	if (s_semid != -1)
		semctl(s_semid, 0, IPC_RMID, 0);
}

void ipcsyslog_init(void)
{
	if (buf == NULL)
	{
		if ((shmid = shmget(KEY_ID, shm_size, IPC_CREAT | 1023)) == -1)
			perror_msg_and_die("shmget");

		if ((buf = shmat(shmid, NULL, 0)) == NULL)
			perror_msg_and_die("shmat");

		buf->size=data_size;
		buf->head=buf->tail=0;

		/* we'll trust the OS to set initial semval to 0 (let's hope) */
		if ((s_semid = semget(KEY_ID, 2, IPC_CREAT | IPC_EXCL | 1023)) == -1)
		{
			if (errno == EEXIST)
			{
				if ((s_semid = semget(KEY_ID, 2, 0)) == -1)
					perror_msg_and_die("semget");
			}
			else
			{
				perror_msg_and_die("semget");
			}
		}
	}
	else
	{
		printf("Buffer already allocated just grab the semaphore?");
	}
}

/* write message to buffer */
void circ_message(const char *msg)
{
	int l=strlen(msg)+1; /* count the whole message w/ '\0' included */

	sem_down(s_semid);

	/*
	 * Circular Buffer Algorithm:
	 * --------------------------
	 *
	 * Start-off w/ empty buffer of specific size SHM_SIZ
	 * Start filling it up w/ messages. I use '\0' as separator to break up messages.
	 * This is also very handy since we can do printf on message.
	 *
	 * Once the buffer is full we need to get rid of the first message in buffer and
	 * insert the new message. (Note: if the message being added is >1 message then
	 * we will need to "remove" >1 old message from the buffer). The way this is done
	 * is the following:
	 *      When we reach the end of the buffer we set a mark and start from the beginning.
	 *      Now what about the beginning and end of the buffer? Well we have the "head"
	 *      index/pointer which is the starting point for the messages and we have "tail"
	 *      index/pointer which is the ending point for the messages. When we "display" the
	 *      messages we start from the beginning and continue until we reach "tail". If we
	 *      reach end of buffer, then we just start from the beginning (offset 0). "head" and
	 *      "tail" are actually offsets from the beginning of the buffer.
	 *
	 * Note: This algorithm uses Linux IPC mechanism w/ shared memory and semaphores to provide
	 *       a threasafe way of handling shared memory operations.
	 */
	if ( (buf->tail + l) < buf->size )
	{
		/* before we append the message we need to check the HEAD so that we won't
		 * overwrite any of the message that we still need and adjust HEAD to point
		 * to the next message! 
		 */
		if ( buf->tail < buf->head)
		{
			if ( (buf->tail + l) >= buf->head )
			{
			  /* we need to move the HEAD to point to the next message
			   * Theoretically we have enough room to add the whole message to the
			   * buffer, because of the first outer IF statement, so we don't have
			   * to worry about overflows here!
			   */
				/* we need to know how many bytes we are overwriting to make enough room */	
			 	int k= buf->tail + l - buf->head;
				char *c=memchr(buf->data+buf->head + k,'\0',buf->size - (buf->head + k));
				if (c != NULL) /* do a sanity check just in case! */
				{
					/* we need to convert pointer to offset + skip the '\0' 
					 * since we need to point to the beginning of the next message 
					 */
					buf->head = c - buf->data + 1; 
					/* Note: HEAD is only used to "retrieve" messages, it's not used
					 *when writing messages into our buffer 
					 */
				}
				else /* show an error message to know we messed up? */
				{ 
					printf("Weird! Can't find the terminator token??? \n");
					buf->head=0;
				}
			}
		} /* in other cases no overflows have been done yet, so we don't care! */

		/* we should be ok to append the message now */
		strncpy(buf->data + buf->tail,msg,l); /* append our message */
		buf->tail+=l; /* count full message w/ '\0' terminating char */
	}
	else
	{
		/* we need to break up the message and "circle" it around */
		char *c;
		int  k=buf->tail + l - buf->size; /* count # of bytes we don't fit */

		/* We need to move HEAD! This is always the case since we are going
		 * to "circle" the message.
		 */
		c=memchr(buf->data + k ,'\0', buf->size - k);

		if (c != NULL) /* if we don't have '\0'??? weird!!! */
		{
			/* move head pointer*/
			buf->head=c-buf->data+1;

			/* now write the first part of the message */
			strncpy(buf->data + buf->tail, msg, l - k - 1);

			/* ALWAYS terminate end of buffer w/ '\0' */
			buf->data[buf->size-1]='\0';

			/* now write out the rest of the string to the beginning of the buffer */
			strcpy(buf->data, &msg[l-k-1]);

			/* we need to place the TAIL at the end of the message */
			buf->tail = k + 1;
		}
		else
		{
			printf("Weird! Can't find the terminator token from the beginning??? \n");
			buf->head = buf->tail = 0; /* reset buffer, since it's probably corrupted */
		}
	}
	sem_up(s_semid);
}
#endif  /* IPC_SYSLOG */

static void dbprint(char *pstrFormat, ...)
{
/* Set on the Flag in the Makefile, then the Debug message, bdprint, will be enabled.*/
#ifdef ALPHA_DBG
	va_list valist;
	va_start(valist, pstrFormat);
	vprintf(pstrFormat, valist);
	va_end(valist);
#endif
}

static size_t proc_log(char *pcBuf, size_t iSizebuf, int *MaxLine)
{
	size_t iPos=0;
	int iLines=0;
	if(pcBuf)
	{
		while(iSizebuf--)
		{
			if(*(pcBuf+iPos++)=='\n')
			{
				iLines++;
				if(iLines >= *MaxLine-1)
				break;
			}
		}
	}
	*MaxLine=iLines;
	return iPos;
}

static size_t read_log(char *pstrFilename, char **pcBuffer)
{
	FILE   *pfileLog=NULL;
	size_t iBufLen=0;

	/*-----Open file and read it into memry-----*/
	if(NULL==(pfileLog=fopen(pstrFilename, "r")))
	{
		dbprint("No log file exists. Create one => %s\n", pstrFilename);
	}
	else
	{
		if(fseek(pfileLog, 0, SEEK_END)==0)
		{
			iBufLen=ftell(pfileLog);
			if(*pcBuffer)
				free(*pcBuffer);
			if(iBufLen > 0 && NULL!=(*pcBuffer=(char *)malloc(sizeof(char)*iBufLen)))
			{
				size_t iRead=0;
				fseek(pfileLog, 0, SEEK_SET);
				iRead=fread(*pcBuffer, sizeof(char), iBufLen, pfileLog);
				if(iBufLen > iRead)
					iBufLen = iRead;

				fclose(pfileLog);
				return iBufLen;
			}
		}
		fclose(pfileLog);
	}
	return -1;
}

#if SYSLOG_AP	/*	Timestamp synchronized , Jordan_2007_01_15	*/
size_t TimeAdjust(char *oldmsgbuf, size_t Mo_iBufLen) {	

	char 		* msgtmp ;
	char 		* msgtest ;
	/* syslog_2007_04_24 , Jordan start */
	char 		tmp_day[10] , tmp_hour[10] , tmp_min[10] ,tmp_sec[10];
	char 		retimestamp[64];
	char 		tmp_aaaa[Mo_iBufLen];	
	int 		t_day , t_hour , t_min , t_sec;
	/* syslog_2007_04_24 , Jordan end */
	struct sysinfo time_info;
	time_t 		time_now;
	time_t		t_modified;
	int 		t_delta;
	int 		msg_len=0;	
	int 		total_len=0;	
	size_t		K_iBufLen;
	
	memset(tmp_day,0,10);
	memset(tmp_hour,0,10);
	memset(tmp_min,0,10);
	memset(tmp_sec,0,10);
	
	K_iBufLen = Mo_iBufLen;
	msgtmp = strstr(oldmsgbuf, "Uptime");
	sysinfo(&time_info);
	time(&time_now);

	while(msgtmp){
		
		memset(retimestamp,0,sizeof(char)*64);
		
		/*************	transfer time format to retimestamp	**************************/		
		/*catch day*/
		msgtmp+=7;
		memcpy(tmp_day,msgtmp,6);
		t_day=atoi(tmp_day);
		
		/*catch hour*/
		msgtmp = strstr(msgtmp, "day");
		msgtmp+=4;
		memcpy(tmp_hour,msgtmp,2);
		t_hour=atoi(tmp_hour);
		
		/*catch minute*/
		msgtmp+=3;
		memcpy(tmp_min,msgtmp,2);
		t_min=atoi(tmp_min);
		
		/*catch second*/
		msgtmp+=3;
		memcpy(tmp_sec,msgtmp,2);
		t_sec=atoi(tmp_sec);
				
		/*the difference time*/
		t_sec = t_sec + (60 * (t_min + 60 * (t_hour + 24 * t_day))); 		
		t_delta = time_info.uptime - t_sec;
		t_modified = time_now - t_delta;	

		sprintf(&retimestamp[0], "%s", ctime(&t_modified));/* syslog_2007_04_24 , Jordan */
		/*************	transfer time format to retimestamp	end**************************/		

		memcpy((tmp_aaaa + total_len) , &retimestamp[4] , 15);/* syslog_2007_04_24 , Jordan */

		msgtmp+=2;
		
		msgtest = strstr(msgtmp, "Uptime");

		if(msgtest){
			msg_len = msgtest - msgtmp ;

			total_len = 15 + total_len ;

			strncpy(tmp_aaaa + total_len , msgtmp, msg_len);	
			
			total_len = msg_len + total_len ;		

		}else{

			total_len = 15 + total_len ;
			
			strcpy(tmp_aaaa+total_len , msgtmp);
		}

		msgtmp=msgtest;		
		K_iBufLen=K_iBufLen-6;
		
	}
	memcpy(oldmsgbuf , tmp_aaaa , K_iBufLen);

	return K_iBufLen;	
}
#endif/*	Timestamp synchronized , Jordan_2007_01_15	*/

static void insert_log(const char *pstrMsg)
{
	FILE   *pfileLog	= NULL;
	char   *pcBuf		= NULL;
	char   buf[255];
	int    iLines		= defMaxLine;
	size_t iBufLen		= -1;
	char   mailmsg[255];
	time_t now;
#if SYSLOG_AP
	time_t 		t_critical;
#endif		

	iBufLen=read_log(logFilePath, &pcBuf);
	/*-----Count Lines and delete the oldest data-----*/
	if(iBufLen)
		iBufLen=proc_log(pcBuf, iBufLen, &iLines);

	if(NULL!=(pfileLog=fopen(logFilePath,"w")))
	{
		fprintf(pfileLog, "%s", pstrMsg);

		/*-----Write old data into log-----*/
		if(pcBuf||pfileLog)//add by yuda
		{
#if SYSLOG_AP	/*	Timestamp synchronized , Jordan_2007_01_15	*/		
			time(&t_critical);
			
			if (t_critical>1167580800) {			
				if(!systimeSynced)
				{
					/* syslog_2007_04_09, Jordan */
				    int fd=0;
				    char synced_buf[16];/* syslog_2007_04_24 , Jordan */
				    char *synced = "synced";
					
					if (!o_unixsock) o_unixsock = strdup(RGDB_DEFAULT_UNIXSOCK);
					fd = lrgdb_open(o_unixsock);
					if (lrgdb_getwb(fd, synced_buf, 1, "%s", "/runtime/systimeSynced")<=0) 
					lrgdb_close(fd);   
					if (0!=strncmp(synced_buf,synced,1)){
						if(pcBuf){//add by yuda
					iBufLen=TimeAdjust(pcBuf,iBufLen);
					}
					systimeSynced = TRUE;
					system("rgdb -i -s /runtime/systimeSynced s");
					}
  				}  				
			}		
			
#endif	/*	Timestamp synchronized , Jordan_2007_01_15	*/		

		if(pcBuf){//add by yuda
			fwrite(pcBuf, iBufLen, sizeof(char), pfileLog);
			free(pcBuf);
		}
		}
		fclose(pfileLog);
		dbprint("Insert log: %s\n(Total lines: %d)\n", pstrMsg, iLines+1);
	}
	else
		fprintf(stderr, "Could not create log file\n");

	/* joanw add for mail the log message. 2004.04.14 */
//#ifdef AP_SMTP/*smtp_2007_02_16, Jordan*/
//	if(SMTP_enable)
//#else /*AP_SMTP*/
	//if((iLines >= defMaxLine-2) && mail_log)
	if ((iLines >= defMaxLine-1) && mail_log)
//#endif /*AP_SMTP*/
	{
#ifdef AP_SMTP	/*smtp_2007_02_16, Jordan*/
		send_mail = 1;
#else /*AP_SMTP*/		
		if(tlog)
		{
			sprintf(buf, "tlogs -l %s > %s", log_path, temp_log_path);
			system(buf);
			
			send_mail = 1;
		}
		else if(!rename(log_path , temp_log_path)) 
			send_mail = 1;
		memset(buf, 0, sizeof(buf));
		sprintf(buf, "rgdb -i -s /runtime/syslog/temp_log_file %s", temp_log_path);
		system(buf);
		system("rgdb -i -s /runtime/syslog/full 1");
#endif /*AP_SMTP*/		
		if(send_mail)
		{
#ifdef AP_SMTP_SCHEDULE
		/*schedule_smtp.2008_03_26.allen*/
			if(strcmp(logFilePath,SMTP_LOG_FILE) == 0)
			{
#if ELBOX_PROGS_GPL_EMAILCLIENT
			system("rgdb -s /runtime/syslog/email_esmtp auth");
#else
			system("rgdb -s /runtime/syslog/auth_esmtp auth");
#endif
#else

			//sprintf(buf, "%s -s \"%s\" -S \"%s\" -a \"%s\" -t \"%s\" -u \"%s\" -p \"%s\" -f \"%s\"",
			//	smtp_path , mail_subject, mail_host, sender_addr, receiver_addr, username, password, log_path);
			//system(buf);
#endif
#ifndef AP_SMTP						
	    /* 2008_04_03 alan wu */
			if(auth_SMTP_enable == 1)
#if ELBOX_PROGS_GPL_EMAILCLIENT
				system("rgdb -s /runtime/syslog/emailauth 1");
#else			
				system("rgdb -s /runtime/syslog/auth_sendmail 1");
#endif
			else
#if ELBOX_PROGS_GPL_EMAILCLIENT
				system("rgdb -s /runtime/syslog/emailinternal 1");
#else	
				system("rgdb -s /runtime/syslog/sendmail 1");
#endif
#endif /*AP_SMTP*/

#ifdef AP_SMTP_SCHEDULE
				remove(SMTP_LOG_FILE);/*schedule_smtp.2008_03_26.allen*/
			}
#endif

#ifdef AP_SMTP/*smtp_2007_02_16, Jordan*/
			
#else /*AP_SMTP*/	
			if(NULL!=(pfileLog=fopen(logFilePath,"w")))
			{
				time(&now);
				memcpy(mailmsg, ctime(&now)+4, 15);
				mailmsg[15]='\0';
#ifdef LOGNUM
				fprintf(pfileLog,"%s  |  SYS:003[%s]\n", mailmsg, sender_addr);
#else
				fprintf(pfileLog,"%s  |  Log Message is full. Mailed the Log Message file to %s.\n",
							mailmsg, sender_addr);
#endif
				fclose(pfileLog);
			}
#endif/*AP_SMTP*/
		}
	}
}

/* Note: There is also a function called "message()" in init.c	*/
/* Print a message to the log file.								*/
static void message (char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
static void message (char *fmt, ...)
{
	int 	fd;
	struct 	flock fl;
	va_list arguments;
	char 	buf[BUF_SIZE];
	int 	len;

	fl.l_whence = SEEK_SET;
	fl.l_start  = 0;
	fl.l_len    = 1;

#ifdef IPC_SYSLOG
	if ((circular_logging == TRUE) && (buf != NULL))
	{
		char b[1024];
		va_start (arguments, fmt);
		vsnprintf (b, sizeof(b)-1, fmt, arguments);
		va_end (arguments);
		circ_message(b);
	}
	else
#endif
	if (proclog)
	{
		/*-----This section will cause crash in samsun S3C2510
					char b[1024];
					va_start (arguments, fmt);
					vsnprintf (b, sizeof(b)-1, fmt, arguments);
					va_end (arguments);
					insert_log(b); -----*/
		va_start (arguments, fmt);
		len = vsprintf(buf, fmt, arguments);
        insert_log(buf);
		va_end (arguments);
	}
	else
	if ((fd = open (logFilePath, O_WRONLY | O_CREAT | O_NOCTTY | O_APPEND | O_NONBLOCK, 0600)) >= 0)	{
		fl.l_type = F_WRLCK;
		fcntl (fd, F_SETLKW, &fl);
		va_start (arguments, fmt);
		len = vsprintf(buf, fmt, arguments);
		write(fd, buf, len);
		va_end (arguments);
		fl.l_type = F_UNLCK;
		fcntl (fd, F_SETLKW, &fl);
		close (fd);
	}
	else
	{
		/* Always send console messages to /dev/console so people will see them. */
		if ((fd = open(_PATH_CONSOLE, O_WRONLY | O_NOCTTY | O_NONBLOCK, 0600)) >= 0) 
		{
			va_start (arguments, fmt);
			len = vsprintf(buf, fmt, arguments);
			write(fd, buf, len);
			va_end (arguments);
			close (fd);
		}
		else
		{
			fprintf (stderr, "Bummer, can't print: ");
			va_start (arguments, fmt);
			vfprintf (stderr, fmt, arguments);
			fflush (stderr);
			va_end (arguments);
		}
	}
}
/*	RemoteLog_2007_01_19 , Jordan	start */
#ifdef REMOTE_LOG
static int in_cksum(unsigned short *buf, int sz)
{
	int nleft = sz;
	int sum = 0;
	unsigned short *w = buf;
	unsigned short ans = 0;

	while (nleft > 1) {
		sum += *w++;
		nleft -= 2;
	}
	if (nleft == 1) {
		*(unsigned char *) (&ans) = *(unsigned char *) w;
		sum += ans;
	}
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	ans = ~sum;
	return (ans);
}

static char *hostname = NULL;

static int RemoteSvrCheck(const char *host)
{
	struct hostent *h;
	struct sockaddr_in pingaddr;
	struct icmp *pkt;
	int pingsock, c;
	char packet[DEFDATALEN + MAXIPLEN + MAXICMPLEN];
	time_t	t1,t2;
	
	if ((pingsock = socket(AF_INET, SOCK_RAW,1)) < 0) {
		 dbprint("socket is not ready\n");
		 perror("socket");
	}else{
		dbprint("socket ready\n");
	}
	//pingsock = socket(AF_INET, SOCK_RAW,1);
	
	setuid(getuid());
	
	memset(&pingaddr, 0, sizeof(struct sockaddr_in));

	pingaddr.sin_family = AF_INET;

	h = gethostbyname(host);
	memcpy(&pingaddr.sin_addr, h->h_addr, sizeof(pingaddr.sin_addr));
	hostname = h->h_name;

	pkt = (struct icmp *) packet;
	memset(pkt, 0, sizeof(packet));
	pkt->icmp_type = ICMP_ECHO;
	pkt->icmp_cksum = in_cksum((unsigned short *) pkt, sizeof(packet));

	c = sendto(pingsock, packet, sizeof(packet), 0,
			   (struct sockaddr *) &pingaddr, sizeof(struct sockaddr_in));

	if (c < 0 || c != sizeof(packet))
	{
			perror("sendto");
			return 0;
	}

//	signal(SIGALRM, noresp);
//	alarm(5);					/* give the host 5000ms to respond */
	
	/* listen for replies */
	time(&t1);
	while (1) {
		struct sockaddr_in from;
		size_t fromlen = sizeof(from);

		if ((c = recvfrom(pingsock, packet, sizeof(packet), 0,
						  (struct sockaddr *) &from, &fromlen)) < 0) {
			time(&t2);
			if ((t2-t1)>=5){
				return 0;
				}
			if (errno == EINTR)
				continue;
			perror("recvfrom");	
			continue;
		}
		if (c >= 76) {			/* ip + icmp */
			struct iphdr *iphdr = (struct iphdr *) packet;

			pkt = (struct icmp *) (packet + (iphdr->ihl << 2));	/* skip ip hdr */
			if (pkt->icmp_type == ICMP_ECHOREPLY)
				break;
		}
		return 0;/* syslogd_2007_02_09 , Jordan */
	}
	dbprint("Remote log Server:%s is alive!\n", hostname);
	
	if (RemoLog_connection_status==0)
	{
	    if ( 0 != (connect(remotefd, (struct sockaddr *) &remoteaddr, sizeof(remoteaddr))))
	    {
	        RemoLog_connection_status=0;
	        dbprint("2 connect remotefd fail\n");
	    }
	    else
	    {
	        RemoLog_connection_status=1;
	        dbprint("2 connect remotefd success\n");
	    }
	}
	else
	    dbprint("RemoLog_connection_status is OK\n");
	    
	return 1;
}

#endif
/*	RemoteLog_2007_01_19 , Jordan	end */
static void logMessage (int pri, char *msg)
{
	time_t 		now;
	char 		*timestamp;
	static char res[20] = "";
	CODE 		*c_pri, *c_fac;
	char * ptr;
#if SYSLOG_AP
	time_t 		t_critical;	
	time_t 		time1;
	time_t 		time2;
	char 		msgbuf[128];//*msgbuf= (char *)calloc(1,128);	/* Jordan_2007_01_15 *//* syslog_2007_04_24 , Jordan */
	struct sysinfo info;
#endif

	if (pri != 0)
	{
		for (c_fac = afacilitynames;
				c_fac->c_name && !(c_fac->c_val == LOG_FAC(pri) << 3); c_fac++);
		for (c_pri = prioritynames;
				c_pri->c_name && !(c_pri->c_val == LOG_PRI(pri)); c_pri++);
		if (c_fac->c_name == NULL || c_pri->c_name == NULL)
			snprintf(res, sizeof(res), "<%d>", pri);
		else
			snprintf(res, sizeof(res), "%s.%s", c_fac->c_name, c_pri->c_name);
	}
	
	/* joanw debug */
	dbprint("asyslogflag is set as %d.\n", asyslogflag);
	dbprint("pri=%d\n", pri);
	dbprint("LOG_FAC(pri)=%d\n", LOG_FAC(pri));
	dbprint("If LOG_FAC(pri) is between 24~28, the message might be log.\n");

	/* filter log message */
#if SYSLOG_AP
	if((((asyslogflag & 0x01) && (24 == LOG_FAC(pri))) ||
		((asyslogflag & 0x02) && (25 == LOG_FAC(pri))) ||
		((asyslogflag & 0x04) && (26 == LOG_FAC(pri))) ||
		((asyslogflag & 0x08) && (27 == LOG_FAC(pri))) ||
		((asyslogflag & 0x10) && (28 == LOG_FAC(pri))) ||
		((asyslogflag & 0x20) && (29 == LOG_FAC(pri))) ||/*syslogd_2007_01_23 , Jordan*/
		((asyslogflag & 0x40) && (30 == LOG_FAC(pri))) ||/*syslogd_2007_02_02 , Jordan*/
		((asyslogflag & 0x80) && (31 == LOG_FAC(pri))) ||/*syslogd_2007_04_13 , Jordan*/
		(32 == LOG_FAC(pri)))/*syslogd_2007_02_02 , Jordan*/				
		&& (aloglevel >= LOG_PRI(pri)))/*syslogd_2007_01_23 , Jordan*/
#else
	if(	((asyslogflag & 0x01) && (24 == LOG_FAC(pri))) ||
		((asyslogflag & 0x02) && (25 == LOG_FAC(pri))) ||
		((asyslogflag & 0x04) && (26 == LOG_FAC(pri))) ||
		((asyslogflag & 0x08) && (27 == LOG_FAC(pri))) ||
		((asyslogflag & 0x10) && (28 == LOG_FAC(pri)))	)
#endif
	{
		/* joanw debug */
		dbprint("enter the if loop.\n");		
		if ( strlen(msg) < 16 || msg[3] != ' ' || msg[6] != ' ' || msg[9] != ':' || 
			 msg[12] != ':'   || msg[15] != ' ') 
		{
			time(&now);
			timestamp = ctime(&now) + 4;
			timestamp[15] = '\0';
		}
		else
		{
			timestamp = msg;
			timestamp[15] = '\0';
			msg += 16;
#if SYSLOG_AP
			memset(msgbuf,0,128);		
			strcpy(msgbuf, msg);	/*Jordan 2007/1/8 10:08上午*/		
#endif
		}
#if SYSLOG_AP	/*	Timestamp synchronized , Jordan_2007_01_15	*/
		
		/*	Synchronize timestamp	,	Jordan 2007/1/4 10:02上午  */	
		/* 
		 * Synchronize timestamp and if time is non-synchronized, timestamp will be set as Uptime.
		 * As the timestamp is synchronized, the log messages that recorded in /var/log/message 
		 * have to correct in realtime.
		 */

		time(&t_critical);
		localtime(&time2);
		time(&time1);
		sysinfo(&info);
		
		/*
		 *  +1167580800 is the delta time for "Jan  1 00:00:00 2007".
		 *  If the delta time, t_critical, is smaller than 1167580800 , it should be regarded as a
		 * overdue time. That overdue timestamp must be replaced by "Uptime" at the header. 
		 */	
		 		 
		if (t_critical<=1167580800) {
			
            struct 		tm ltm;
            int 		days;
            int 		hours;
			char 		timestamp2[128];  /* syslog_2007_04_24 , Jordan */
            		
			days = info.uptime / (60*60*24);
			//hours = info.uptime / (60*60);            
			hours = (info.uptime - days*60*60*24) / (60*60);  /* time_2007_05_07 */
			bcopy((char *)localtime (&info.uptime), (char *)&ltm, sizeof(struct tm));
			sprintf(timestamp2, "Uptime %d day %02d:%02d:%02d", days, hours, ltm.tm_min, ltm.tm_sec);
			msg += 6;	
			strcpy(timestamp, timestamp2);	
			strcpy(msg, msgbuf);
		}

#endif	/*	Timestamp synchronized , Jordan_2007_01_15	*/

		/* todo: supress duplicates */

#ifdef REMOTE_LOG
		/* send message to remote logger */
		if ( -1 != remotefd){
			static const int IOV_COUNT = 2;
			struct iovec iov[IOV_COUNT];
			struct iovec *v = iov;
	
			/*	RemoteLog_2007_01_19 , Jordan	start */
			if(First_init_RemoLog) 
			{			
			    SvrReady=0;			
				SvrReady=RemoteSvrCheck(RemoteHost);/*Jordan , 2007/1/19 10:01上午*/
				
				if( SvrReady ) 
				{					
					char   		*pcBuf		= NULL;
					size_t 		iBufLen		= -1;
					char 		* msgtmp ;
					char 		* msgend ;
					int 		msg_len=0;	
					char 		msg_send[256];// 	= (char *)malloc(sizeof(char)*256);/* syslog_2007_04_24 , Jordan */

					dbprint("Remote Log Svr is ready!!\nsend all the log message\n");
					iBufLen=read_log(logFilePath, &pcBuf);
					if (iBufLen > 0 && pcBuf)
					{
					msgtmp = strrchr(pcBuf, '|');
					
					while(msgtmp)
					{
						struct iovec iov1[IOV_COUNT];
						struct iovec *v1 = iov1;
						
						msgtmp=msgtmp+3;
						
						msgend = strrchr(msgtmp, '\n');
								
						msg_len = msgend - msgtmp ;
						
						memset(&res, 0, sizeof(res));
						memset(msg_send,0,sizeof(char)*256);
						
						snprintf(msg_send, msg_len+9, "syslog: %s", msgtmp);
						snprintf(res, sizeof(res), "<%d>", LOG_INFO);
						v1->iov_base = res ;
						v1->iov_len = strlen(res);
						v1++;		
						
						v1->iov_base = msg_send;
						v1->iov_len = strlen(msg_send);
						
					writev_retry1:          	
						
						if ( -1 == writev(remotefd,iov1, IOV_COUNT))
						{
							printf("err %d: %s\n", errno, strerror(errno));
							if (errno == EINTR) goto writev_retry1;
						}
						
						msgtmp=msgtmp-3;
						memset((char *)msgtmp,0, msg_len+1);
						msgtmp = strrchr(pcBuf, '|');
					}	
					
						//free(msg_send);	/* syslog_2007_04_24 , Jordan */
						if(pcBuf)
						free(pcBuf);/* syslog_2007_04_24 , Jordan */
                        
						First_init_RemoLog=0;
						system("rgdb -i -s /runtime/log/Remote_log_init 0");
					    }
				}else {
					dbprint("Remote Log Svr is not ready!!\n");
				}
			} /* if(First_init_RemoLog) */
			/*	RemoteLog_2007_01_19 , Jordan	end */	
			
			memset(&res, 0, sizeof(res));
			/* joanw fixed 
			 * When REMOTE_LOG, we set the all the message's priority as 6,LOG_INFO,
			 * and priority should be between 0 to 7(you can find out the detail in the syslog.h),
			 * or the message will be refused by the remote host.
			 */
			 //snprintf(res, sizeof(res), "<%d>", pri);
			snprintf(res, sizeof(res), "<%d>", LOG_INFO);
			v->iov_base = res ;
			v->iov_len = strlen(res);
			v++;
	
			v->iov_base = msg;
			v->iov_len = strlen(msg);
writev_retry:
			if ( -1 == writev(remotefd,iov, IOV_COUNT))
			{
				dbprint("err %d: %s\n", errno, strerror(errno));
				if (errno == EINTR) goto writev_retry;
				/* joanw fixed													 */
				/* we don't want syslogd to terminate, so we mark below 2 lines. */
				 //perror_msg_and_die("cannot write to remote file handle on"
				 //		"%s:%d",RemoteHost,RemotePort);
			}
		} /* if ( -1 != remotefd) */
		/* joanw fixed 																  */
		/* whatever remote logging or local logging, we both log the message locally, */
		/* so we mark the below 1 line.												  */
		 //if (local_logging == TRUE)

#endif /* endif of REMOTE_LOG */
		/* now spew out the message to wherever it is supposed to go */
		//message("%s %s %s%s\n", timestamp, res, msg, postfix);
		ptr = strchr(msg, ':');
		if (ptr) msg = ptr + 2;
		message("%s  |  %s\n", timestamp, msg);
		/*input same log message to other file */
		/*schedule_smtp.2008_03_26.allen*/
#ifdef AP_SMTP_SCHEDULE
		if(mail_log == 1)
		{
		    	tmplogPath=logFilePath;
			logFilePath = SMTP_LOG_FILE;
			message("%s  |  %s\n", timestamp, msg );
			logFilePath = tmplogPath;
		}
#endif
	}
}

static void quit_signal(int sig)
{
	logMessage(LOG_SYSLOG | LOG_INFO, "System log daemon exiting.");
	unlink(lfile);
#ifdef IPC_SYSLOG
	ipcsyslog_cleanup();
#endif

	exit(TRUE);
}

#ifdef ORG_CODE
static void domark(int sig)
{
	if (MarkInterval > 0) {
		logMessage(LOG_SYSLOG | LOG_INFO, "-- MARK --");
		alarm(MarkInterval);
	}
}
#endif

/* This must be a #define, since when DODEBUG and BUFFERS_GO_IN_BSS are
 * enabled, we otherwise get a "storage size isn't constant error. */
static int serveConnection (char* tmpbuf, int n_read)
{
	char *p = tmpbuf;
	/* joanw debug */
	dbprint("\n----- from serveConnection ---- \n");
	dbprint("tmpbuf= %s\n\n", tmpbuf);

	while (p < tmpbuf + n_read) 
	{

		int           pri = (LOG_USER | LOG_NOTICE);
		char          line[ MAXLINE + 1 ];
		unsigned char c;

		char *q = line;

		while ( (c = *p) && q < &line[ sizeof (line) - 1 ]) 
		{
			if (c == '<') 
			{
				/* Parse the magic priority number. */
				pri = 0;
				while (isdigit (*(++p))) 
				{
					pri = 10 * pri + (*p - '0');
				}
				if (pri & ~(LOG_FACMASK | LOG_PRIMASK))
				{
					pri = (LOG_USER | LOG_NOTICE);
				}
			} 
			else if (c == '\n') 
			{
				*q++ = ' ';
			} 
			else if (iscntrl (c) && (c < 0177)) 
			{
				*q++ = '^';
				*q++ = c ^ 0100;
			} 
			else 
			{
				*q++ = c;
			}
			p++;
		}
		*q = '\0';
		p++;

		/* joanw debug */
		dbprint("enter logMessage\n");
		/* Now log it */
		logMessage (pri, line);
		dbprint("leave logMessage\n");
		dbprint("----------------------\n");
	}
	return n_read;
}


#ifdef REMOTE_LOG
static void init_RemoteLog (void)
{
	/* joanw debug */
	dbprint("init_RemotedLog\n");

	int		len = sizeof(remoteaddr);

	memset(&remoteaddr, 0, len);

	remotefd = socket(AF_INET, SOCK_DGRAM, 0);

	if (remotefd < 0) 
	{
    	perror_msg_and_die("cannot create socket");
	}

	if ((hostinfo = gethostbyname(RemoteHost)) == NULL)
		perror_msg_and_die("%s", RemoteHost);

	remoteaddr.sin_family = AF_INET;
	remoteaddr.sin_addr = *(struct in_addr *) *hostinfo->h_addr_list;
	remoteaddr.sin_port = htons(RemotePort);

	/*
	 *  Since we are using UDP sockets, connect just sets the default host and port
	 *  for future operations
	 */
	RemoLog_connection_status=0;
	if ( 0 != (connect(remotefd, (struct sockaddr *) &remoteaddr, len)))
	{
	    RemoLog_connection_status=0;
		//perror_msg_and_die("cannot connect to remote host %s:%d", RemoteHost, RemotePort);
		dbprint("1 connect remotefd fail\n");
	}
	else
	{
	    RemoLog_connection_status=1;
	    dbprint("1 connect remotefd success\n");
	}
}
#endif

//static void doSyslogd (void) __attribute__ ((noreturn));
static void doSyslogd (void)
{
	struct sockaddr_un sunx;
	socklen_t addrLength;

	int sock_fd;
	fd_set fds;

	/* Set up signal handlers. */
	signal (SIGINT,  quit_signal);
	signal (SIGTERM, quit_signal);
	signal (SIGQUIT, quit_signal);
	signal (SIGHUP,  SIG_IGN);
	signal (SIGCHLD, SIG_IGN);
#ifdef SIGCLD
	signal (SIGCLD,  SIG_IGN);
#endif
	/*signal (SIGALRM, domark);
	alarm (MarkInterval);*/

	/* Create the syslog file so realpath() can work. */
	if (realpath (_PATH_LOG, lfile) != NULL)
		unlink (lfile);

	memset (&sunx, 0, sizeof (sunx));
	sunx.sun_family = AF_UNIX;
	strncpy (sunx.sun_path, lfile, sizeof (sunx.sun_path));
	if ((sock_fd = socket (AF_UNIX, SOCK_DGRAM, 0)) < 0)
		perror_msg_and_die("Couldn't get file descriptor for socket " _PATH_LOG);

	addrLength = sizeof (sunx.sun_family) + strlen (sunx.sun_path);
	if (bind(sock_fd, (struct sockaddr *) &sunx, addrLength) < 0)
		perror_msg_and_die("Could not connect to socket " _PATH_LOG);

	if (chmod (lfile, 0666) < 0)
		perror_msg_and_die("Could not set permission on " _PATH_LOG);

#ifdef IPC_SYSLOG
	if (circular_logging == TRUE )
	{
	   ipcsyslog_init();
	}
#endif

#ifdef REMOTE_LOG
	if (doRemoteLog == TRUE)
	{
	  init_RemoteLog();
	}
#endif
#if SYSLOG_AP
	    if(first_init==1)
		{
		    syslog(ALOG_AP_SYSACT| LOG_NOTICE,"[SYSACT]Device start with f/w version:%s \n",fw_version);
		    first_init=0;
		}
#endif
	logMessage (LOG_SYSLOG | LOG_INFO, "syslogd started: ");

	for (;;) 
	{
		FD_ZERO (&fds);
		FD_SET (sock_fd, &fds);

		if (select (sock_fd+1, &fds, NULL, NULL, NULL) < 0) 
		{
			if (errno == EINTR) 
			{
				/* alarm may have happened. */
				continue;
			}
			perror_msg_and_die("select error");
		}

		if (FD_ISSET (sock_fd, &fds)) 
		{
			int   i;
			char tmpbuf[BUFSIZ+1];
			memset(tmpbuf, '\0', BUFSIZ+1);
			if ( (i = recv(sock_fd, tmpbuf, BUFSIZ, 0)) > 0) 
			{
				serveConnection(tmpbuf, i);
			} 
			else 
			{
				perror_msg_and_die("UNIX socket error");
			}
		}/* FD_ISSET() */
	} /* for main loop */
}

int main(int argc, char **argv)
{
	int 	opt;
#if ! defined(__uClinux__)
	int 	doFork = TRUE;
#endif

	char 	*p;

	/* do normal option parsing */
#if SYSLOG_AP
	while ((opt = getopt(argc, argv, "b:l:pnO:R:iLCF:ms:S:f:P:H:Ma:r:t:u:")) > 0) 
#else
	while ((opt = getopt(argc, argv, "pnO:R:LCF:ms:S:f:P:H:Ma:r:t:Au:")) > 0) 
#endif
	{
		switch (opt) 
		{
#if SYSLOG_AP
                       case 'l':
		        if ((optarg == NULL) || (optarg[1] != '\0')) {
				    show_usage(argv);
			    }
		        aloglevel = *optarg - '0';
		        if (aloglevel > 7 ||aloglevel <0) {
				    show_usage(argv);
			    }
		         dbprint("aloglevel=%d\n", aloglevel);
		        break;
#endif
			case 'p':
				proclog = TRUE;
				break;
#if ! defined(__uClinux__)
			case 'n':
				doFork = FALSE;
				break;
#endif
			case 'O':
				logFilePath = optarg;
				break;
#ifdef REMOTE_LOG
			case 'R':
				RemoteHost = optarg;
				if ( (p = strchr(RemoteHost, ':')))
				{
					RemotePort = atoi(p+1);
					*p = '\0';
				}
				doRemoteLog = TRUE;
				break;
#if SYSLOG_AP				
			case 'i':
                First_init_RemoLog = 1;
                dbprint("First_init_RemoLog = 1\n");  
				break;				
#endif				
			case 'L':
				local_logging = TRUE;
				break;
#endif
#ifdef IPC_SYSLOG
			case 'C':
				circular_logging = TRUE;
				break;
#endif
#ifdef ASYSLOG_NAMES
			case 'F':
				/* joanw add for Alpha System Log Message filter. 2004.04.22
				  *   	0x01: 00000001 system activity
				 * 	 	0x02: 00000010 debug information
				 * 	 	0x04: 00000100 attacks
				 * 	 	0x08: 00001000 dropped packet
				 * 	 	0x10: 00010000 notice
				 *      0x20: 00100000 wireless information for ap
				 *      0x40: 01000000 system activity for ap (apsysact)
				 *      0x80: 10000000 notice for ap (apnotice)
				 ************************************************************/
				if(0 == strcmp("sysact", optarg))
					asyslogflag |= 0x01;
				else if(0 == strcmp("debug", optarg))
					asyslogflag |= 0x02;
				else if(0 == strcmp("attack", optarg))
					asyslogflag |= 0x04;
				else if(0 == strcmp("drop", optarg))
					asyslogflag |= 0x08;
				else if(0 == strcmp("notice", optarg))
					asyslogflag |= 0x10;
#if SYSLOG_AP
			        else if(0 == strcmp("wireless", optarg))/*syslogd_2007_01_23 , Jordan*/
					asyslogflag |= 0x20;
			        else if(0 == strcmp("apsysact", optarg))/*syslogd_2007_02_02 , Jordan*/
					asyslogflag |= 0x40;
			        else if(0 == strcmp("apnotice", optarg))/*syslogd_2007_02_02 , Jordan*/
					asyslogflag |= 0x80;										
#endif
				else
					show_usage(argv);

				/* joanw debug */
				dbprint("asyslogflag=%d\n", asyslogflag);
				break;
#endif
			/* joanw add for mail log message 2004.04.14 */
			case 'm':
				mail_log = 1;
				break;
			case 's':
				mail_subject = optarg;
				break;
			case 'S':
#ifdef AP_SMTP/*smtp_2007_02_16 , Jordan */
				SMTP_enable=1;
#endif
				mail_host = optarg;
				break;
			//case 'P':
			//	mail_port = optarg;
			//	break;
			case 'H':
				src_host = optarg;
				strcat(mail_from, optarg);
				strcat(mail_from, ".com");
				break;
			case 'M':
				mime_style = 1;
				break;
			case 'a': /*syslogd_2008_03_03.allen*/
				sender_addr = optarg;
				break;
			case 'r':/*syslogd_2008_03_03.allen*/
				receiver_addr = optarg;
				break;
			case 't':
				tlog = 1;
				log_path = optarg;
				break;
#if SYSLOG_AP
			case 'b':/*syslog_2007_02_16 , Jordan*/
				fw_version = optarg;
                                first_init = 1;
                                dbprint("klog fw_version=%s\n", fw_version);    
				break;				
#endif
			case 'A': /* auth SMTP , 2008_04_03 alan wu */
				auth_SMTP_enable = 1; 
				break;
			case 'P':/* auth ESMTP_2008_04_29,allen */
				password = optarg;
				break;				
			case 'u':
				username = optarg;
				break;				
			default:
				show_usage(argv);
				break;
		}
	}

#ifdef REMOTE_LOG
	/* If they have not specified remote logging, then log locally */
	if (doRemoteLog == FALSE)
		local_logging = TRUE;
#endif

	/* Store away localhost's name before the fork */
	gethostname(LocalHostName, sizeof(LocalHostName));
	if ((p = strchr(LocalHostName, '.'))) 
	{
		*p++ = '\0';
	}

	umask(0);

#if 0 // ! defined(__uClinux__)
	if (doFork == TRUE) 
	{
		if (daemon(0, 1) < 0)
			perror_msg_and_die("daemon");
	}
#endif
	doSyslogd();

	return EXIT_SUCCESS;
}
/*
Local Variables
c-file-style: "linux"
c-basic-offset: 4
tab-width: 4
End:
*/
