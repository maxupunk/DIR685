/*
#!/bin/sh
#
# smart_spindown rev. 1
#
# Copyright (C) 2003 by Bart Samwel
#
# You may do with this file (and parts thereof) whatever you want, as long
# as my copyright notice is retained.
#
#
# How it works: This program monitors the read activity on a disk. If there
# is no read activity for a while, the disk is spun down. The time without
# read activity that is required is dynamic, using a backoff factor. When
# the recent spun-down periods are relatively short, this means that the
# machine might be busy with something, so the script tries to wait for
# longer periods without activity before spinning down again. When spun-down
# periods are long, the backoff factor is decreased, and the disk is spun
# down after shorter periods without read activity.
#
# This script REQUIRES that laptop_mode is enabled on your kernel. This is
# because it assumes that after a couple of seconds without read activity,
# all dirty blocks will be flushed. If this is not done, the disc will
# spin up at random times
#
# Configuration
#
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>

//#define DEBUG_MODE

#ifdef DEBUG_MODE
#define DEBUG_PRINTF			printf
#else
#define DEBUG_PRINTF
#endif

#define HDPARM_PATH_D			"hdparm"
#define CONTENT_FILE_SIZE_D 	5000
#define CMD_BUF_SIZE_D 	  		300


#define GPIO_FAN_SWITCH(val)		gpio_out(1,6,(val))
#define GPIO_RETRY	3
#define FAN_ON_TEMP   46
#define FAN_OFF_TEMP  41  //add by siyou 2008/12/23 10:07

int find_chr(char *tmp_buf, char chr);
int export_first_num_from_file(char *filename);
int export_from_file(char *filename, char *p_buffer, int buf_len);
int device_is_up(char *devname);

/*global variables*/
char g_cmd_buf[CMD_BUF_SIZE_D];
char g_content_file_buf[CONTENT_FILE_SIZE_D];

int isnumber(char *str)
{
	int i = 0;
	for(i = 0 ; str[i] != 0; i++)
	{
		if(!isdigit(str[i]))
			return 0;	
	}
	return 1;
} 

int find_chr(char *tmp_buf, char chr)
{
	int i = 0 ;
	for(i = 0 ; i < strlen(tmp_buf) ; i++)
	{
		if(tmp_buf[i] == chr)
			return i;
	}
	return 0;
}

int export_first_num_from_file(char *filename)
{
	char tmp_buf[50];
	char *p_val = tmp_buf;
	int tmp = 0;
	int ret = 0;
	
	if(export_from_file(filename, tmp_buf, 50)==-1)
		return -1;	
	
	/*fix bug : sometimes the value is behind whitespaces*/
	while(p_val[0]==' ')	//omit whitespace, keep looking
		p_val++;
	
	tmp = find_chr(p_val, ' ');
	p_val[tmp] = 0;
	ret = atoi(p_val);	
	DEBUG_PRINTF("[disk activity] %d\n",ret);
	return ret;
}

int export_to_file(char *data,char *file)
{
	FILE *out_f=NULL;
    out_f=fopen(file,"w+");
    if(out_f==NULL)
    {
    	printf("Open file failed : %s \n", file);
        return 0;
	}
	fprintf(out_f,"%s\n",data);
    fclose(out_f);
    return 1;
}

int export_from_file(char *filename, char *p_buffer, int buf_len)
{
	FILE *fd=NULL;
    fd=fopen(filename,"r");
    if(fd==NULL)
    {
    	printf("Open file failed : %s \n", filename);
    	return -1;
	}
	fread(p_buffer ,1, buf_len ,fd);
    fclose(fd);
    return 1;
}

static int device_is_up(char *devname)
{
	DEBUG_PRINTF("[HENDRY][Check HD] %s -C %s\n", HDPARM_PATH_D, devname);
	sprintf(g_cmd_buf, "%s -C %s > /var/hd_status", HDPARM_PATH_D,devname);
	system(g_cmd_buf);
		
	if(export_from_file("/var/hd_status", g_content_file_buf, CONTENT_FILE_SIZE_D)==-1)
	{
		printf("Can't get content from %s\n","/var/hd_status");
		return 0;
	}
	
	if(strstr(g_content_file_buf, "active")==NULL)
	{
		/* we always update the hd status to db to synchronize with other programs */
		xmldbc_set(NULL, 0, "/runtime/nas/store_dev/status", "inactive");
		DEBUG_PRINTF("Drive is currently down.\n");
		return 0;
	}
	else
	{
		/* we always update the hd status to db to synchronize with other programs */
		xmldbc_set(NULL, 0, "/runtime/nas/store_dev/status", "active");
		DEBUG_PRINTF("Drive is currently up.\n");
		return 1;
	}
}

static void gpio_outen(int port, int line, int enable)
{
	char buf[64];
	FILE * fh = NULL;
	int retry;

	sprintf(buf, "/proc/nas_gpio/gpio/outen_p%c_%d", port+'a', line);
	for (retry=0; retry<GPIO_RETRY && !fh; retry++) fh = fopen(buf, "w");
	if (fh)
	{
		fwrite(enable ? "1" : "0", 2, 1, fh);
		fclose(fh);
	}
	else
	{
		fprintf(stderr, "%s: can not open [%s] to write, retry = %d.\n",__FUNCTION__,buf, retry);
	}
}

static void gpio_out(int port, int line, int val)
{
	char buf[64];
	FILE * fh = NULL;
	int retry;

	sprintf(buf, "/proc/nas_gpio/gpio/data_p%c_%d", port+'a', line);
	for (retry=0; retry<GPIO_RETRY && !fh; retry++) fh = fopen(buf, "w");
	if (fh)
	{
		fwrite(val ? "1" : "0", 2, 1, fh);
		fclose(fh);
	}
	else
	{
		fprintf(stderr, "%s: can not open [%s] to write, retry = %d.\n",__FUNCTION__,buf, retry);
	}
}
void check_hd_temp(char *diskname)
{
	char read_in_buf[20];
	char command[50];
		
	sprintf(command,"/usr/sbin/smartmon -t /dev/%s ",diskname);
	system(command);
	xmldbc_get_wb(NULL, 0, "/runtime/nas/store_dev/temp/celsius", read_in_buf, 20);
	if( atoi(read_in_buf)>=FAN_ON_TEMP)
	{
		GPIO_FAN_SWITCH(1);//fan start
	}
	if( atoi(read_in_buf)<=FAN_OFF_TEMP)
	{
		GPIO_FAN_SWITCH(0);//fan close
	}		
	
}
void do_smart_spindown(char *device, unsigned int seconds )
{
	/* begin main program */
	char statsfile[200];
	char *diskname = NULL;
	int this_wait 	= 0;				//idle time allowed for sata hd before sleep
	int interval_check = 30;			//time range to check the hd status (up/down)
										//user new assigned sleep time (debug purpose)
	int next_reads 	= 0;				//to check disk activity
	int prev_reads 	= 0;				//to check disk activity
	int num_equals 	= 0;


	diskname = strrchr(device, '/') ; 	
	if(diskname == NULL)
	{
		printf("Error in device name\n");
		return;
	}
	
	diskname = diskname +1;				/*skip the '/' by adding 1*/
	
	if(strcmp(diskname ,"")==0)
	{
		printf("No sata hd is plugged in\n");
		return;
	}
	printf("[hendry] start do_smart_spindown\n");	

	this_wait = seconds;
	
	DEBUG_PRINTF("[hendry] Start smart spindown on %s\n", device);
	sprintf(statsfile,"/sys/block/%s/stat", diskname);
	
	while(1)	//check every 30 seconds to see if hd is up or down
	{
		//check a flag to stop 
		DEBUG_PRINTF("Updating smart ... \n");	
		if(device_is_up(device))
		{
			prev_reads=-1;
			num_equals=0 ;
			DEBUG_PRINTF("Waiting for %d seconds of read inactivity...\n", this_wait);
	
			prev_reads=export_first_num_from_file(statsfile);
			if(prev_reads == -1)
			{
				printf("Can't check disk activity\n");
				return;
			}
			
			while ( (num_equals*interval_check) < this_wait)
			{
				sleep(interval_check);
				
				next_reads=export_first_num_from_file(statsfile);
				if(next_reads == -1)
				{
					printf("Can't check drive activity\n");
					return;
				}
				
				if (prev_reads != next_reads)
				{		//not idle
					num_equals=0 ;
					prev_reads=next_reads;
					DEBUG_PRINTF("Restarting...\n");
				}
				else	//idle										
				{
					num_equals=num_equals+1;
					DEBUG_PRINTF("Seconds of quiet: %d, waiting until %d\n", num_equals*interval_check, this_wait );
				}
				check_hd_temp(diskname);
			}
			/*we must guarantee that all cache is written before go to sleep*/
			sync();
				
			sprintf(g_cmd_buf, "%s -q -y %s", HDPARM_PATH_D,device);
			system(g_cmd_buf);
			
			DEBUG_PRINTF("Drive go to sleep after idle for %d seconds.\n", this_wait);
		}
		else
			GPIO_FAN_SWITCH(0);//fan close when hd sleep
		sleep(interval_check);
	} //end of while	
}

void show_usage()
{
	printf("\n");
	printf("smart_spindown [device] [seconds]\n");
}


void main(int argc, char *argv[])
{
	unsigned int seconds = 0;
	//rename the process to hd_daemon
	if(argc < 2)
	{
		show_usage();
		return;
	}
		
	if(strstr(argv[1],"h"))
	{
		show_usage();
		return;
	}
	
	if(!isnumber(argv[2]))
	{
		printf("[seconds] arg error\n");
		return;
	}
	
	seconds = strtoul((argv[2]),0,10);
	printf("seconds : %d\n",seconds );
	
	if(seconds==0)		//never sleep 
	{
		printf("device should never sleep\n");
		printf("joel just run spindown to do fan detect!!\n");
		seconds = 0xffffff;
		//return;
	}
	do_smart_spindown(argv[1], seconds);

}
