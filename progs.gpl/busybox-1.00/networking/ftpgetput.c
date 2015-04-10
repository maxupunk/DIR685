/* vi: set sw=4 ts=4: */
/*
 * ftpget
 *
 * Mini implementation of FTP to retrieve a remote file.
 *
 * Copyright (C) 2002 Jeff Angielski, The PTR Group <jeff@theptrgroup.com>
 * Copyright (C) 2002 Glenn McGrath <bug1@iinet.net.au>
 *
 * Based on wget.c by Chip Rosenthal Covad Communications
 * <chip@laserlink.net>
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

#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/stat.h>

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
/*FW_log_20070412, start {, Added by Erick*/
/*ELBOX_PROGS_GPL_SYSLOGD*/
#include <syslog.h>
#include "../../../include/asyslog.h"
/*FW_log_20070412, End }, Added by Erick*/
#include "../../../include/elbox_config.h"/*ftp_tftp_FW_CG_20070125 Erick*/

#include "busybox.h"

typedef struct ftp_host_info_s {
	char *user;
	char *password;
	struct sockaddr_in *s_in;
} ftp_host_info_t;

static char verbose_flag = 0;
static char do_continue = 0;
/*ftp_tftp_FW_CG_20070125 Erick*//*start {*/
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG
static char Get_FW = 0;
static char Put_CG = 0;
static char Get_CG = 0;

extern char g_signature[50];/*ftp_tftp_FW_CG_20070112 Erick*/
#define RGDBGET(x, y, args...) _cli_rgdb_get_(x, y, ##args)/*ftp_tftp_FW_CG_20070112 Erick*/

char *ftp_buffer;
char *ftp_buffer_ptr;
int  ftp_len;
#define MAX_FW_BUFFER_SIZE 16*1024*1024 /*FW_log_20070412, Added by Erick*/ 
#define MAX_CFG_BUFFER_SIZE 1*1024*1024
#define Config_Path "/var/config.bin"
#endif
/*ftp_tftp_FW_CG_20070125 Erick*//*End }*/

/*Update_Bootloader_20070307, Builder, 20070307*/
/*+++*/
int bootloader_main(int argc, char **argv)
{
    char *srcf, *dstf = "/dev/mtdblock/3";
    struct stat src_stat;
    FILE *srcfd, *dstfd;
    
    if (argc!=2){
        bb_show_usage();
        return -1;
    }
        
    srcf = argv[1];

    if (lstat(srcf, &src_stat) < 0) {
        if (errno != ENOENT) {
            bb_perror_msg("unable to stat `%s'", srcf);
        }else{
            bb_perror_msg("%s", srcf);
        }
        return -1;
    }
    
    if(copy_file(srcf, dstf, 2)!=0){
        return -1;
    }else{
        if(remove_file(srcf, 2)!=0)
            return -1;
    }

    return 0;
}
/*+++*/
/*Update_Bootloader_20070307, Builder, 20070307*/

static int ftpcmd(const char *s1, const char *s2, FILE *stream, char *buf)
{
	if (verbose_flag) {
		bb_error_msg("cmd %s%s", s1, s2);
	}

	if (s1) {
		if (s2) {
			fprintf(stream, "%s%s\r\n", s1, s2);/*ftp_tftp_FW_CG_20070125 Erick*/
		} else {
			fprintf(stream, "%s\r\n", s1);/*ftp_tftp_FW_CG_20070125 Erick*/
		}
	}
	do {
		char *buf_ptr;

		if (fgets(buf, 510, stream) == NULL) {
			bb_perror_msg_and_die("fgets()");
		}
		buf_ptr = strstr(buf, "\r\n");
		if (buf_ptr) {
			*buf_ptr = '\0';
		}
	} while (! isdigit(buf[0]) || buf[3] != ' ');

	return atoi(buf);
}

static int xconnect_ftpdata(ftp_host_info_t *server, const char *buf)
{
	char *buf_ptr;
	unsigned short port_num;

	buf_ptr = strrchr(buf, ',');
	*buf_ptr = '\0';
	port_num = atoi(buf_ptr + 1);

	buf_ptr = strrchr(buf, ',');
	*buf_ptr = '\0';
	port_num += atoi(buf_ptr + 1) * 256;

	server->s_in->sin_port=htons(port_num);
	return(xconnect(server->s_in));
}

static FILE *ftp_login(ftp_host_info_t *server)
{
	FILE *control_stream;
	char buf[512];

	/* Connect to the command socket */
	control_stream = fdopen(xconnect(server->s_in), "r+");
	if (control_stream == NULL) {
		bb_perror_msg_and_die("Couldnt open control stream");
	}

	if (ftpcmd(NULL, NULL, control_stream, buf) != 220) {
		bb_error_msg_and_die("%s", buf + 4);
	}

	/*  Login to the server */
	switch (ftpcmd("USER ", server->user, control_stream, buf)) {
	case 230:
		break;
	case 331:
		if (ftpcmd("PASS ", server->password, control_stream, buf) != 230) {
			bb_error_msg_and_die("PASS error: %s", buf + 4);
		}
		break;
	default:
		bb_error_msg_and_die("USER error: %s", buf + 4);
	}

	ftpcmd("TYPE I", NULL, control_stream, buf);

	return(control_stream);
}

#ifdef CONFIG_FTPGET
static int ftp_recieve(ftp_host_info_t *server, FILE *control_stream,
		const char *local_path, char *server_path)
{
	char buf[512];
	off_t filesize = 0;
	int fd_data;
	int fd_local = -1;
	off_t beg_range = 0;
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG /*ftp_tftp_FW_CG_20070125 Erick*/
	char sbuf[50];
#endif

	/* Connect to the data socket */
	if (ftpcmd("PASV", NULL, control_stream, buf) != 227) {
		bb_error_msg_and_die("PASV error: %s", buf + 4);
	}
	fd_data = xconnect_ftpdata(server, buf);

	if (ftpcmd("SIZE ", server_path, control_stream, buf) == 213) {
		unsigned long value=filesize;
		if (safe_strtoul(buf + 4, &value))
			bb_error_msg_and_die("SIZE error: %s", buf + 4);
		filesize = value;
	} else
	{
		filesize = -1;
		do_continue = 0;
	}
/*ftp_tftp_FW_CG_20070125 Erick*//*start {*/
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG
    if(Get_CG)
    {
	        /*The configuration file will be saved to /var/config.bin, 
	        and we will parse it after we get it by using ftp.*/
	        sprintf(sbuf,Config_Path);
	        //printf("set local_path to /var/config.bin\n");
	        local_path = sbuf;
	}
    if(!Get_CG && !Get_FW)/*ftp_tftp_FW_CG_200609028 Erick*/
#endif
/*ftp_tftp_FW_CG_20070125 Erick*//*End }*/
	if ((local_path[0] == '-') && (local_path[1] == '\0')) {
		fd_local = STDOUT_FILENO;
		do_continue = 0;
	}

/*ftp_tftp_FW_CG_20070125 Erick*//*start {*/
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG
    if(Get_FW || Get_CG)
    {
    	
    	
        if(Get_FW){
        		system("cp /usr/sbin/reboot /var/run/reboot");                      
              system("rgdb -i -s /runtime/update/fwimage/status 1");
	        ftp_buffer=malloc(MAX_FW_BUFFER_SIZE);
	      }
	    else
	        ftp_buffer=malloc(MAX_CFG_BUFFER_SIZE);
	    
	    
        if(ftp_buffer)
        {
            ftp_buffer_ptr=ftp_buffer;
            ftp_len=0;
           // printf("ftp allocate download_buffer->OK!\n");
        }
        else
        {
           // printf("ftp allocate download_buffer->Fail!\n");
            exit(EXIT_FAILURE);
        } 
        
    }
#endif
/*ftp_tftp_FW_CG_20070125 Erick*//*End }*/
	if (do_continue) {
		struct stat sbuf;
		if (lstat(local_path, &sbuf) < 0) {
			bb_perror_msg_and_die("fstat()");
		}
		if (sbuf.st_size > 0) {
			beg_range = sbuf.st_size;
		} else {
			do_continue = 0;
		}
	}

	if (do_continue) {
		sprintf(buf, "REST %ld", (long)beg_range);
		if (ftpcmd(buf, NULL, control_stream, buf) != 350) {
			do_continue = 0;
		} else {
			filesize -= beg_range;
		}
	}

	if (ftpcmd("RETR ", server_path, control_stream, buf) > 150) {
		bb_error_msg_and_die("RETR error: %s", buf + 4);
	}

	/* only make a local file if we know that one exists on the remote server */
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG/*ftp_tftp_FW_CG_20070125 Erick*/
	if (fd_local == -1 && !Get_FW) {
#else
	if (fd_local == -1) {
#endif
		if (do_continue) {
			fd_local = bb_xopen(local_path, O_APPEND | O_WRONLY);
		} else {
			fd_local = bb_xopen(local_path, O_CREAT | O_TRUNC | O_WRONLY);
		}
	}


#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG/*ftp_tftp_FW_CG_20070503 Erick*/
	/* Copy the file */
	if (filesize != -1 && (!Get_FW) && (!Get_CG)) {
#else
	/* Copy the file */
	if (filesize != -1) {
#endif	    
		if (-1 == bb_copyfd_size(fd_data, fd_local, filesize))
		exit(EXIT_FAILURE);
	} else {
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG/*ftp_tftp_FW_CG_20070125 Erick*/
	    if (Get_FW)
	    {
	        if (-1 == (ftp_len=bb_copyfd2buff_eof(fd_data, ftp_buffer_ptr, MAX_FW_BUFFER_SIZE)))
	        {
/*FW_log_20070412, start {, Added by Erick*/   
                 bb_error_msg("Fail to get the file, please check the IP address and check the file name.");	            
#if ELBOX_PROGS_GPL_SYSLOGD  
                /*ftp_tftp_log_20070427*/
                 syslog(ALOG_AP_SYSACT|LOG_WARNING,"[SYSACT]Fail to get the file, please check the IP address and check the file name.");
#endif 
/*FW_log_20070412, End }, Added by Erick*/ 	            
		exit(EXIT_FAILURE);
	}
	    }else if (Get_CG)
	    {
	        if (-1 == (ftp_len=bb_copyfd2buff_eof(fd_data, ftp_buffer_ptr, MAX_CFG_BUFFER_SIZE)))
	        {
	           /*FW_log_20070412, start {, Added by Erick*/   
               bb_error_msg("Fail to get the file.");	
               /*Remove local file /var/config.bin*/
	           unlink(Config_Path); 
	            /*FW_log_20070412, End }, Added by Erick*/      
		    exit(EXIT_FAILURE);
		    }
	    }else
#endif /*ftp_tftp_FW_CG_20070125 Erick*/
	    {   
                    if (-1 == bb_copyfd_eof(fd_data, fd_local))
		    exit(EXIT_FAILURE);
	    }
	}
	/* close it all down */
	close(fd_data);
	if (ftpcmd(NULL, NULL, control_stream, buf) != 226) {
		bb_error_msg_and_die("ftp error: %s", buf + 4);
	}
	ftpcmd("QUIT", NULL, control_stream, buf);

/*ftp_tftp_FW_CG_20070125 Erick*//*start {*/
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG
    if(Get_FW)
    {

#ifdef ELBOX_PROGS_PRIV_CLI_SUPER
                    {
                        char xmldb_buff[10];
                        
                        memset(xmldb_buff, 0x0, sizeof(xmldb_buff));
                        RGDBGET(xmldb_buff, 10, "/runtime/sys/super");
                        //xmldbc_get_wb(NULL, 0, "/runtime/sys/super", xmldb_buff, sizeof(xmldb_buff)-1);
                        if(atoi(xmldb_buff)==1){
#ifdef ELBOX_FIRMWARE_HEADER_VERSION
                            if(ELBOX_FIRMWARE_HEADER_VERSION == 3){
                                burn_image(ftp_buffer, ftp_len);
                                return(EXIT_SUCCESS);
                            }else if(ELBOX_FIRMWARE_HEADER_VERSION == 2){
                                v2_burn_image(ftp_buffer, ftp_len);
                                return(EXIT_SUCCESS);
                            }
#else
                            v2_burn_image(ftp_buffer, ftp_len);
                            return(EXIT_SUCCESS);
#endif /*ELBOX_FIRMWARE_HEADER_VERSION*/
                        }
                    }
#endif /*ELBOX_PROGS_PRIV_CLI_SUPER*/
#ifdef ELBOX_FIRMWARE_HEADER_VERSION
                    if(ELBOX_FIRMWARE_HEADER_VERSION == 3){
                        if (v3_image_check(ftp_buffer, ftp_len)==0)
                        {
                            v3_burn_image(ftp_buffer, ftp_len);
                        }
                    }else if(ELBOX_FIRMWARE_HEADER_VERSION == 2){
                        if (v2_image_check(ftp_buffer, ftp_len)==0)
                        {
                            v2_burn_image(ftp_buffer, ftp_len);
                        }                        
                    }
#else
                    if (v2_image_check(ftp_buffer, ftp_len)==0)
                    {
                        v2_burn_image(ftp_buffer, ftp_len);
                    }
                    else
                    {

                    }
#endif /*ELBOX_FIRMWARE_HEADER_VERSION*/
    }
    

    if(Get_CG)
	{
	    
	        memset(g_signature,0,50);
                RGDBGET(g_signature, 50, "/runtime/layout/image_sign");

	        ftp_buffer_ptr=ftp_buffer;
	        ftp_buffer_ptr+=strlen(g_signature)+1;
	        ftp_len-=strlen(g_signature)+1;
	        
	        if(write(fd_local,ftp_buffer_ptr,ftp_len)<=0)
	        {
	            bb_error_msg("Write config to dev->fail");
	        }
	        else
	        {
	            system("/etc/scripts/misc/profile.sh reset /var/config.bin");
	            system("/etc/scripts/misc/profile.sh put");/*Save_config_20070426 Erick*/
	            /*FW_log_20070412, Added by Erick*/                 	
                bb_error_msg("Update configuraion file successfully!");
	        }

	        close(fd_local);
	        /*Remove local file /var/config.bin*/
	        unlink(Config_Path);
	}		
    
    if(ftp_buffer)
    {
        free(ftp_buffer);
        ftp_buffer=NULL;
       // printf("Free download_buffer\n");
    }
#endif
/*ftp_tftp_FW_CG_20070125 Erick*//*End }*/	
	return(EXIT_SUCCESS);
}
#endif

#ifdef CONFIG_FTPPUT
static int ftp_send(ftp_host_info_t *server, FILE *control_stream,
		const char *server_path, char *local_path)
{
	struct stat sbuf;
	char buf[512];
	int fd_data;
	int fd_local;
	int response;
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG /*ftp_tftp_FW_CG_20070125 Erick*/
	char ssbuf[50]; 
#endif
	/*  Connect to the data socket */
	if (ftpcmd("PASV", NULL, control_stream, buf) != 227) {
		bb_error_msg_and_die("PASV error: %s", buf + 4);
	}
	fd_data = xconnect_ftpdata(server, buf);
/*ftp_tftp_FW_CG_200609028 Erick*//*start {*/
/*	if (ftpcmd("CWD ", server_path, control_stream, buf) != 250) {
		bb_error_msg_and_die("CWD error: %s", buf + 4);
	}*/
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG /*ftp_tftp_FW_CG_20070125 Erick*//*start {*/
    if(Put_CG)
    {
	        /*To generate the configuration file to put to PC*/
	        //printf("get config from flash\n");
	        system("/usr/sbin/sys -s configsave");
	        /*The file will be /var/config.bin*/
	        //printf("set local file to /var/config.bin\n");
	        sprintf(ssbuf,Config_Path);
	        local_path = ssbuf;
	}
#endif
/*ftp_tftp_FW_CG_20070125 Erick*//*End }*/
	/* get the local file */
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG /*ftp_tftp_FW_CG_20070125 Erick*/
	if ((local_path[0] == '-') && (local_path[1] == '\0') && !Put_CG) {/*ftp_tftp_FW_CG_200609028 Erick*/
#else
	if ((local_path[0] == '-') && (local_path[1] == '\0')) {
#endif
		fd_local = STDIN_FILENO;
	} else {
		fd_local = bb_xopen(local_path, O_RDONLY);
		fstat(fd_local, &sbuf);
/*ftp_tftp_FW_CG_20070125 Erick*//*Disabled by Erick*//*start {*/
		/*sprintf(buf, "ALLO %lu", (unsigned long)sbuf.st_size);
		response = ftpcmd(buf, NULL, control_stream, buf);
		switch (response) {
		case 200:
		case 202:
			break;
		default:
			close(fd_local);
			bb_error_msg_and_die("ALLO error: %s", buf + 4);
			break;
		}*//*ftp_tftp_FW_CG_200609028 Erick*//*End }*/
		}
	response = ftpcmd("STOR ", server_path, control_stream, buf);/*ftp_tftp_FW_CG_20070125 Erick*/
	switch (response) {
	case 125:
	case 150:
		break;
	default:
		close(fd_local);
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG /*FW_log_20070412,start{, Added by Erick*/ 
        if(Put_CG)
        {		
            /*Remove local file /var/config.bin*/
	        unlink(local_path);
	        bb_error_msg("Put configuraion file fail!");
        }
#endif /*FW_log_20070412,End}, Added by Erick*/
		bb_error_msg_and_die("STOR error: %s", buf + 4);
	}

	/* transfer the file  */
	if (bb_copyfd_eof(fd_local, fd_data) == -1) {
		exit(EXIT_FAILURE);
	}

	/* close it all down */
	close(fd_data);
	if (ftpcmd(NULL, NULL, control_stream, buf) != 226) {
		bb_error_msg_and_die("error: %s", buf + 4);
	}
	ftpcmd("QUIT", NULL, control_stream, buf);
/*ftp_tftp_FW_CG_20070125 Erick*//*start {*/
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG 
    if(Put_CG)
    {
        close(fd_local);
	    /*Remove local file /var/config.bin*/
	    unlink(local_path);
	    /*FW_log_20070412, Added by Erick*/ 
	    bb_error_msg("Put configuraion file successfully!");
    }
#endif    
/*ftp_tftp_FW_CG_20070125 Erick*//*End }*/
	return(EXIT_SUCCESS);
}
#endif

#define FTPGETPUT_OPT_CONTINUE	1
/*ftp_tftp_FW_CG_20070125 Erick*//*start {*/
#define FTPGETPUT_OPT_FW     	2
#define FTPGETPUT_OPT_PUT_CG	4
#define FTPGETPUT_OPT_GET_CG	8
#define FTPGETPUT_OPT_VERBOSE	0x10
#define FTPGETPUT_OPT_USER	0x20
#define FTPGETPUT_OPT_PASSWORD	0x40
#define FTPGETPUT_OPT_PORT	0x80
/*ftp_tftp_FW_CG_20070125 Erick*//*End }*/

static const struct option ftpgetput_long_options[] = {
	{"continue", 1, NULL, 'c'},
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG /*ftp_tftp_FW_CG_20070125 Erick*//*start {*/
	{"firmware", 1, NULL, 'f'},
	{"put_config", 1, NULL, 't'},
	{"get_config", 1, NULL, 'd'},
#endif
	{"verbose", 0, NULL, 'v'},
	{"username", 1, NULL, 'u'},
	{"password", 1, NULL, 'p'},
	{"port", 1, NULL, 'P'},
	{0, 0, 0, 0}
};

int ftpgetput_main(int argc, char **argv)
{
	/* content-length of the file */
	unsigned long opt;
	char *port = "ftp";

	/* socket to ftp server */
	FILE *control_stream;
	struct sockaddr_in s_in;

	/* continue a prev transfer (-c) */
	ftp_host_info_t *server;

	int (*ftp_action)(ftp_host_info_t *, FILE *, const char *, char *) = NULL;

	/* Check to see if the command is ftpget or ftput */
#ifdef CONFIG_FTPPUT
# ifdef CONFIG_FTPGET
	if (bb_applet_name[3] == 'p') {
		ftp_action = ftp_send;
	}
# else
	ftp_action = ftp_send;
# endif
#endif
#ifdef CONFIG_FTPGET
# ifdef CONFIG_FTPPUT
	if (bb_applet_name[3] == 'g') {
		ftp_action = ftp_recieve;
	}
# else
	ftp_action = ftp_recieve;
# endif
#endif

	/* Set default values */
	server = xmalloc(sizeof(ftp_host_info_t));
	server->user = "anonymous";
	server->password = "busybox@";
	verbose_flag = 0;

	/*
	 * Decipher the command line
	 */
	bb_applet_long_options = ftpgetput_long_options;
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG /*ftp_tftp_FW_CG_20070125 Erick*//*start {*/
	opt = bb_getopt_ulflags(argc, argv, "cftdvu:p:P:", &server->user, &server->password, &port);/*ftp_tftp_FW_CG_200609028 Erick*/

		Get_FW = 0;
		Put_CG = 0;
		Get_CG = 0;
	
	if (opt & FTPGETPUT_OPT_FW) {
		Get_FW = 1;
	}
	if (opt & FTPGETPUT_OPT_PUT_CG) {
		Put_CG = 1;
	}
	if (opt & FTPGETPUT_OPT_GET_CG) {
		Get_CG = 1;
	}
/*ftp_tftp_FW_CG_20070125 Erick*//*End }*/
#else
	opt = bb_getopt_ulflags(argc, argv, "cvu:p:P:", &server->user, &server->password, &port);
#endif

	/* Process the non-option command line arguments */
	if (argc - optind != 3) {
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG /*ftp_tftp_FW_CG_20070125 Erick*//*start {*/
	    if((Get_FW || Get_CG || Put_CG) &&(argc - optind != 2))
		bb_show_usage();
		else if(!(Get_FW || Get_CG || Put_CG))
#endif
/*ftp_tftp_FW_CG_20070125 Erick*//*End }*/
		bb_show_usage();
	}

	if (opt & FTPGETPUT_OPT_CONTINUE) {
		do_continue = 1;
	}
	if (opt & FTPGETPUT_OPT_VERBOSE) {
		verbose_flag = 1;
	}

	/* We want to do exactly _one_ DNS lookup, since some
	 * sites (i.e. ftp.us.debian.org) use round-robin DNS
	 * and we want to connect to only one IP... */
	server->s_in = &s_in;
	bb_lookup_host(&s_in, argv[optind]);
	s_in.sin_port = bb_lookup_port(port, "tcp", 21);
	if (verbose_flag) {
		printf("Connecting to %s[%s]:%d\n",
				argv[optind], inet_ntoa(s_in.sin_addr), ntohs(s_in.sin_port));
	}

	/*  Connect/Setup/Configure the FTP session */
	control_stream = ftp_login(server);
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG /*ftp_tftp_FW_CG_20070125 Erick*//*start {*/
    if((Get_FW || Get_CG || Put_CG))
    return(ftp_action(server, control_stream, argv[optind + 1], argv[optind + 1]));
    else
#endif
/*ftp_tftp_FW_CG_20070125 Erick*//*End }*/
	return(ftp_action(server, control_stream, argv[optind + 1], argv[optind + 2]));
}

/*
Local Variables:
c-file-style: "linux"
c-basic-offset: 4
tab-width: 4
End:
*/
