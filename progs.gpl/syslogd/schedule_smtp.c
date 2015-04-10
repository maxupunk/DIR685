#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <elbox_config.h>
#include "sloop.h"

/* initial the variables of mail*/
static char Nomessage[]	   = "No log message event.\n";
static char tmp_path[]	   = "/var/log/tmpmsg";		/* the no log messsage of the mail. */
static char *mail_subject  = "Log Message";		/* -s , the subject of the mail. */
static char *sender_addr   = NULL;			/* -a , sender e-mail address. */
static char *src_host      = "RG-Administrator";	/* -H , The host name of SMTP Client. */
static char *mail_host     = NULL;			/* -S , SMTP server IP. */
static char *receiver_addr = NULL;			/* -r , receiver e-mail address.*/
static char *timeout	   = NULL;			/* -T , the timeout for send email to Client.*/
static char *username	   = NULL;
static char *password	   = NULL;
static char *log_path ;					/* the path of SMTP log message. */
unsigned int t_min = 0;
unsigned int smtp_count = 0;					

static void show_usage()
{
	printf("\n");
	printf("schedule_smtp Options:\n");
	printf("\n");
	printf("  -s mail_subject       :Subject\n");
	printf("  -a sender_addr        :The sender e-mail address.\n");
	printf("  -H src_host_name      :Host name to provide as source of message.\n");
	printf("  -S mailhost           :SMTP Server IP.\n");
	printf("  -P mail_port          :Port where MTA can be contacted via SMTP.\n");
	printf("  -r receiver_addr      :The receiver e-maill address.\n");
	printf("  -t log_file_path      :The log file path.\n");
	printf("  -T time_sloop     	:The time set of minute by sloop_register_timeout.\n");
	return ;
}

static void smtp_log()
{
	if(access(log_path,R_OK)==0) 
	{
#if ELBOX_PROGS_GPL_EMAILCLIENT
	system("rgdb -s /runtime/syslog/email_esmtp auth");
#else
	system("rgdb -s /runtime/syslog/auth_esmtp auth");
#endif
	remove(log_path);
	} else {
#if ELBOX_PROGS_GPL_EMAILCLIENT
	system("rgdb -s /runtime/syslog/email_esmtp schedule");
#else	
	system("rgdb -s /runtime/syslog/auth_esmtp schedule");	
#endif
	}
}

static void timer_count()
	{
	smtp_count++;
	if(smtp_count == t_min)
	{
		smtp_log();
		smtp_count = 0;	
	}
	sloop_register_timeout(60, 0, timer_count, NULL);	
}

int main(int argc, char **argv)
{
	char 	opt;
	int 	fd;
	while ((opt = getopt(argc, argv, "s:a:H:S:P:r:t:T:u:"))>0)
	{
		switch (opt) 
		{
			case 's':
				mail_subject = optarg;
				break;
			case 'a':
				sender_addr = optarg;
				break;
                	case 'H':
				src_host = optarg;
				break;
			case 'S':
				mail_host = optarg;
				break;
			case 'r':
				receiver_addr = optarg;
				break;
			case 't':
				log_path = optarg;
				break;
			case 'T':
				timeout = optarg;
				t_min =atoi(timeout);
				break;
			case 'P':
				password = optarg;
				break;
			case 'u':
				username = optarg;
				break;
			default:
				show_usage();
				break;
		}
	}
	
	fd = open (tmp_path, O_WRONLY | O_CREAT | O_TRUNC);
	write(fd,Nomessage,sizeof(Nomessage));
	close(fd);
	if(t_min != 0)
	{
	sloop_init(NULL);
		sloop_register_timeout(60, 0, timer_count, NULL);
	sloop_run();
	}else {
		return EXIT_SUCCESS;
	}
	return EXIT_SUCCESS;
}
 	
