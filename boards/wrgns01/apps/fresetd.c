/* vi: set sw=4 ts=4: */
/*
 *	fresetd.c
 *
 *	A daemon program to control reset button and LEDs.
 *
 *	David Hsieh <david_hsieh@alphanetworks.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/sysinfo.h>
//#include <sys/socket.h>
#include <sys/ioctl.h>
//#include <net/if.h>
//#include <netinet/in.h>

#include <dtrace.h>
#include <sloop.h>
#include <unixsock.h>
#include <fcntl.h>
#include<linux/kd.h>
#include<linux/input.h>

#ifdef RTL8366RB
#include "drivers/net/rtl8366rb/rtl8368s_asicdrv.h"
#include "drivers/net/rtl8366rb/rtl8366rb_api.h" 
#include <drivers/net/rtl8366rb/rtl8366_ioctl.h>
#else
#include "drivers/net/rtl8366s/rtl8366s_asicdrv.h"
#include "drivers/net/rtl8366s/rtl8366s_api.h"
#include <drivers/net/rtl8366s/rtl8366_ioctl.h>
#endif
/***************************GLOBAL VARIABLE***********************************************/
#define GPIO_FAN_SWITCH_INIT() gpio_outen(1,6,1)	/* Port B, line 6, output */
#define GPIO_FAN_SWITCH(val)		gpio_out(1,6,(val))
#define GPIO_WPS_LED_INIT()			gpio_outen(0,7,1)	/* Port A, line 7, output */
#define GPIO_WPS_LED(val)		gpio_out(0,7,(val))

#define GPIO_INIT_RESET()		gpio_outen(0,8,0)	/* Port A, line 8, input */
#define GPIO_IN_RESET()			gpio_in(0,8)

#define GPIO_HD_LED_BLUE_INIT()		gpio_outen(0,11,1)	/* Port A, line 11, output */
#define GPIO_HD_LED_BLUE(val)		{gpio_out(0,12,0);gpio_out(0,11,!(val));}
//marco the hd light is high active, while others are low active

#define GPIO_HD_LED_ORANGE_INIT()		gpio_outen(0,12,1)	/* Port A, line 12, output */
#define GPIO_HD_LED_ORANGE(val)		{gpio_out(0,11,0);gpio_out(0,12,!(val));}
//marco the hd light is high active, while others are low active

#define GPIO_HD_BUTTON_INIT()		gpio_outen(0,13,0)	/* Port A, line 13, input */
#define GPIO_HD_BUTTON(val)		gpio_in(0,13)

#define ON	0
#define OFF 1
#define USOCK_NAME	"/var/run/fresetd_unixsock"
#define USOCK_HD "/var/run/hd_unixsock"
#define RTL8366S_IOCTL_DEV  "/dev/rtl8366sr"
#define GPIO_RETRY	3
#define SATA_STAT "/proc/sata_stat"

int g_hd_status=0;
static int		o_test = 0;				/* test mode */
static int		o_freset_time = 5;		/* number of seconds to active factory reset state*/
static int		o_reset_time = 2;		/* number of seconds to active reset state */
static char		__cmdbuf[256];
static char *	o_wps_command = "/etc/templates/wps.sh pbc &";			/* Command to start WPS. */
static char *	o_wps_result = "xmldbc -i -s /runtime/wps/result WPS_SUCCESS";	/* Command to update the wps result. */
static char *	o_wps_setxmldb = "/etc/templates/wps_setnodes.sh &";	/* Command to write the WPS information back xmldb */
static char *	o_process_restart_command = "/etc/templates/hd_process.sh restart &"; /*Command to start or stop all hd related process like,samba, itunes*/
static char *	o_process_start_command = "/etc/templates/hd_process.sh start &"; /*Command to start all hd related process like,samba, itunes*/

enum { WPS_NONE, WPS_IN_PROGRESS, WPS_ERROR, WPS_OVERLAP, WPS_SUCCESS , HD_ORG_NONE, HD_UMOUNTING,
	HD_CAN_REMOVE, NO_HD, HD_DETECT, HD_BUSY};

static struct _usock_data
{
	usock_handle usock;
	sloop_handle sloop;
}usock_data = {NULL,NULL},usock_for_hd={NULL,NULL};

/* WPS button & LEDs */
static struct _wps_led_data
{
	int mode;
	int led;
	int overlap;
}wps_led_data = { WPS_NONE, 0, 0 },hd_led_data = { HD_ORG_NONE, 0, 0 };
/* HD button */
static struct _pbc_data
{
    long pressed_start;
    long pressed_time;
}hd_pbc_data = {0,0},freset_data = {0,0};;

/* Status LED */
static struct _status_data
{
	int data;
	int state;
}status_data = {0,1};

/////////////////////
//switch related
/////////////////////
typedef enum _LINK_TYPE
{
    TYPE_DISCONNECT = 0,
    TYPE_100FULL = 1,
    TYPE_100HALF = 2,
    TYPE_10FULL = 3,	
    TYPE_10HALF = 4,
	TYPE_1000FULL = 5,
	TYPE_1000HALF = 6,
    TYPE_UNKNOWN = 99
}
LINK_TYPE;

static void gpio_out(int port, int line, int val);
static int gpio_in(int port, int line);
static void gpio_outen(int port, int line, int enable);
static int usock_handler(int sock, void * param, void * sloop_data);
static void wps_set_led(int mode);
static void hd_pbc_handler(void * param, void * sloop_data);
static void hd_set_led(int mode);

/**************************GLOBAL VARIABLE*******************************/

static int is_exist(char *filename)
{
	FILE *fd=NULL;
	fd=fopen(filename,"r");
	if(fd==NULL)
	{
    	printf("[hendry] file NOT exist : %s\n",filename );
    	return 0;
    }
    else
    {
    	printf("[hendry] file exist : %s\n",filename );
    	fclose(fd);
    	return 1;
    }
}

static int export_to_file(char *data,char *file)
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

static int sig_term(int sig, void * param, void * sloop_data)
{
	d_dbg("%s: got sig %d, exit the program!\n", __FUNCTION__, sig);
	sloop_terminate();
	return 0;
}

static int sig_ignr(int sig, void * param, void * sloop_data)
{
	d_dbg("%s: got sig %d, ignore it !\n", __FUNCTION__, sig);
	return 0;
}
static inline long get_uptime(void)
{
	struct sysinfo info;
	sysinfo(&info);
	return info.uptime;
}
//////////////////////////////////////////////////////////////////////////
static void freset_handler(void * param, void * sloop_data)
{
	struct _pbc_data * data = (struct _pbc_data *)param;

	sloop_register_timeout(1,0, freset_handler, &freset_data);

	if (GPIO_IN_RESET()==0)//jana: reading data of ping 8. if value=0
	{
		if (data->pressed_start > 0)
		{
			data->pressed_time = get_uptime() - data->pressed_start;
			printf("reset button pressed for %d secs\n", (int)data->pressed_time);
			if (data->pressed_time > o_freset_time)		status_data.state = 3;
			else if (data->pressed_time > o_reset_time)	status_data.state = 2;
		}
		else
		{
			data->pressed_start = get_uptime();
		}
	}
	else
	{
		if (data->pressed_start > 0)
		{
			if (status_data.state == 2)
			{
				printf("DO reset !!!\n");
				/* Turn off all the LED */
				GPIO_WPS_LED(OFF);
				GPIO_HD_LED_BLUE(OFF);
				GPIO_HD_LED_ORANGE(OFF);
				if (!o_test) system("reboot");
			}
			else if (status_data.state == 3)
			{
				printf("DO freset !!!\n");
				/* Turn off all the LED */
				GPIO_WPS_LED(OFF);
				GPIO_HD_LED_BLUE(OFF);
				GPIO_HD_LED_ORANGE(OFF);
				if (!o_test) system("submit FRESET");
			}
			else
			{
				printf("DO nothing !!!\n");
			}
		}
		status_data.state = 1;
		data->pressed_time = 0;
		data->pressed_start = 0;
	}
}
static void show_usage(int exit_code)
{
	printf(	"Usage: fresetd [OPTION]\n"
			"  -h                show this help message.\n"
			"  -t                test mode, will not really reset.\n"
			"  -f {second}       specify the time of seconds that active factory reset. (default is 3)\n"
			"  -r {second}       specify the time of seconds that active system reset. (default is 3)\n"
			"  -s {WPS command}  specify the WPS command.\n"
			"  -i {interface}    interface used to read/write mii registers.\n"
			);
	exit(exit_code);
}
static void parse_args(int argc, char * argv[])
{
	int opt;
	while ((opt = getopt(argc, argv, "htf:r:s:")) > 0)
	{
		switch (opt)
		{
		case 'h':	show_usage(0);					break;
		case 't':	o_test++;						break;
		case 'f':	o_freset_time = atoi(optarg);	break;
		case 'r':	o_reset_time = atoi(optarg);	break;
		default:	show_usage(-1);					break;
		}
	}
}

void modules_up()
{
	FILE *fptr=NULL;
	char command[100];
	char tmp_port[10];
	char tmp_kernel_name[10];
	int tmp_status;
	int retry = 0;
	
insert_module :
	/*hendry fix : inform that it is sata hd before run modules*/
	if(export_to_file("", "/var/is_sata_hd")==0)
		printf("[hendry] Can't inform sata_hd\n");
	else	
		printf("[hendry] Informing mnt_dev it is a sata_hd\n");
	sleep(1);//marco, add to wait for hw ready
	system("insmod /lib/modules/sata.ko");
	hd_set_led(HD_DETECT);
	
	fptr=fopen(SATA_STAT,"r");
	fscanf(fptr,"%s %d %s\n",tmp_port,&tmp_status,tmp_kernel_name);
	fclose(fptr);
	
	//+++ hendry
	/*if devname returned is "NUL", we try again 5 times*/
	if(strstr(tmp_kernel_name, "NUL") && retry < 5)
	{
		system("rmmod sata");
		retry ++ ;
		sleep(1);//marco, add to wait for hw ready
		goto insert_module;
	}

	sprintf(command,"rgdb -i -s /runtime/nas/store_dev/devname %s",tmp_kernel_name);
	system(command);
	
//	p_tmp=strstr(tmp_kernel_name,"d");
//
//	if(p_tmp!=NULL)
//	{
//		p_tmp++;
//		sprintf(mount_path,"HD_%s",p_tmp);
//		sprintf(command,"rgdb -i -s /runtime/nas/store_dev/mount %s",mount_path);
//		system(command);
//	}	
#if 0	//move to /etc/templates/hd_process.sh stop
	/*hendry add to turn on smart_spindown*/
	memset(read_in_buf, 0x00, 10);
	xmldbc_get_wb(NULL, 0, "/nas/store_dev/sleep_time", read_in_buf, 10);
	sprintf(command,"smart_spindown /dev/%s %s &",tmp_kernel_name, read_in_buf);
	system(command);
#endif
	/* +++ Teresa Ke add. 2009/1/8 03:38¤U¤È  */
	system(o_process_start_command);
}
void sata_hotplug(char *port,int status,char *kernel_name)
{
	static int pre_status=0;
	char command[100];
	if(strcmp(port,"P0:")==0)//P0
	{
		if(pre_status==status)
			return;
		else
		{
		    pre_status=status;					    
		}
		if(status==1)
		{
			/*TODO */
			system("ssignal 36 &"); /*inform panel to show "detecting is in progress". */
			sloop_register_timeout(3,0, modules_up,	NULL);
		}
		else if(status==0)
		{
			sprintf(command,"rgdb -i -s /runtime/nas/store_dev/devname \"\"");
			system(command);
			sprintf(command,"rgdb -i -s /runtime/nas/store_dev/mount \"\"");
			system(command);
			//marco , umount dev if users unplug the hd without click the umount button
		//	system(o_process_restart_command);
			system("/etc/templates/hd_process.sh restart_without_echo");	
			/*hendry add to clear re-format workflow */
			if(is_exist("/var/dev_need_format"))
				unlink("/var/dev_need_format");	
						
			hd_set_led(NO_HD);
			GPIO_FAN_SWITCH(0);//fan close
		}
	}
//	else//P1 support one bay only
//	{
//		if(status==1)
//			system("echo \"scsi add-single-device 0 0 0 0\" > /proc/scsi/scsi");
//		else if(status==0)
//			system("echo \"scsi remove-single-device 0 0 0 0\" > /proc/scsi/scsi");
//	}
}

void check_hd_status()
{
	FILE *fp=NULL;
	char port[10];
	char kernel_name[10];
	
	
	sloop_register_timeout(1,0, check_hd_status, NULL);
	fp=fopen(SATA_STAT,"r");
   
       fscanf(fp,"%s %d %s\n",port,&g_hd_status,kernel_name);
       //printf("&read_in_buff %s,&status %d,kernel_name %s \n",port,status,kernel_name);
    sata_hotplug(port,g_hd_status,kernel_name);              
	fclose(fp);
}

/**************************************************************************/
#define SWITCH_WAN_PORT     4

/* Check WAN link status*/
unsigned int Read_Reg(unsigned int port)
{
	int fd,ret;
	getPortLinkState_t portLinkState;

	fd = open(RTL8366S_IOCTL_DEV, O_RDONLY);
	if (fd <=0) {
		 return -1;
	}
	portLinkState.port = port;
	ioctl(fd, GETPORTLINKSTATE, &portLinkState);
	//printf("port:%d, speed:%d, duplex:%d,link:%d, txPause:%d, rxPause:%d, nWay:%d\n", portLinkState.port, portLinkState.speed, portLinkState.duplex, portLinkState.link, portLinkState.txPause, portLinkState.rxPause, portLinkState.nWay);
	if (!portLinkState.link)
		ret=TYPE_DISCONNECT;
	else
		ret=TYPE_100FULL;//connect, always return 1
	
	if(fd) close(fd);
	return ret;
}

int getportstatus(int port)
{
	return Read_Reg(port);
}

static int wan_link_data = 1;
static void wan_link_handler( void * param, void * sloop_data )
{
	int *link_data = (int *)param;
	int link_status = getportstatus( SWITCH_WAN_PORT );
	if( link_status == 1 && *link_data == 0 )
	{
		system("killall -SIGUSR1 udhcpc");	//-----always send signal whatever the wam type is
		sloop_register_timeout(20, 0, wan_link_handler, &wan_link_data);
	}
	else
		sloop_register_timeout(1, 0, wan_link_handler, &wan_link_data);
	wan_link_data = link_status;
}
/**************************************************************************/

static int fresetd_main(int argc, char * argv[])
{
	//we check the dev/RTL8366S_IOCTL_DEV first,sory here...
	
//jana start
#ifdef PHY_RTL8306S
	rtl8306_workaround();
#endif

	parse_args(argc, argv);
	printf("Factory reset time : %d secs\n", o_freset_time);
	printf("System reset time  : %d secs\n", o_reset_time);
	if (o_test) printf("Test mode enabled !\n");

	sloop_init(NULL);

	sloop_register_signal(SIGTERM, sig_term, NULL);
	sloop_register_signal(SIGINT,  sig_term, NULL);
	sloop_register_signal(SIGKILL, sig_term, NULL);
	sloop_register_signal(SIGPIPE, sig_ignr, NULL);
	sloop_register_signal(SIGALRM, sig_term, NULL);
	sloop_register_signal(SIGUSR1, sig_ignr, NULL);
	sloop_register_signal(SIGUSR2, sig_ignr, NULL);

	/* Setup GPIOs */
	GPIO_FAN_SWITCH_INIT();
	GPIO_WPS_LED_INIT();
	GPIO_INIT_RESET();
	GPIO_HD_LED_BLUE_INIT();
	GPIO_HD_LED_ORANGE_INIT();
	//we chabge to interrupt method,no need to init.
	//GPIO_HD_BUTTON_INIT();

	/* Turn off all the LED */
	GPIO_WPS_LED(OFF);
	GPIO_HD_LED_BLUE(OFF);
	GPIO_HD_LED_ORANGE(OFF);

	
	/* Register handler */

	sloop_register_timeout(0,0, freset_handler,		&freset_data);
	sloop_register_timeout(0,0, hd_pbc_handler,		&hd_pbc_data);
	sloop_register_timeout(0,0, check_hd_status,NULL);//check sata status from /proc/sata_stat
	sloop_register_timeout(0,0, wan_link_handler, &wan_link_data);
	//sloop_register_timeout(0,0, wps_pbc_handler,	&wps_pbc_data);

	/* create a unixsock server for incomming commands */
	usock_data.usock = usock_open(1, USOCK_NAME);
	if (usock_data.usock == NULL)
		fprintf(stderr, "Unable to create unix domain socket !!!\n");
	else
		usock_data.sloop = sloop_register_read_sock(usock_fd(usock_data.usock), usock_handler, &usock_data);

	usock_for_hd.usock = usock_open(1, USOCK_HD);
	if (usock_for_hd.usock == NULL)
		fprintf(stderr, "Unable to create unix domain socket !!!\n");
	else
		usock_for_hd.sloop = sloop_register_read_sock(usock_fd(usock_for_hd.usock), usock_handler, &usock_for_hd);
	/* Let's do it */
	sloop_run();

	
	/* Turn off all the LED */
	GPIO_WPS_LED(OFF);
	GPIO_HD_LED_BLUE(OFF);
	GPIO_HD_LED_ORANGE(OFF);

	if (usock_data.sloop) sloop_cancel_read_sock(usock_data.sloop);
	if (usock_data.usock) usock_close(usock_data.usock);
//jana end	
	
	return 0;
}
/**********************HD button and led handler************************************************/
static sloop_handle hd_led_handle = NULL;

static void hd_led_handler(void * param, void * sloop_data)
{
	struct _wps_led_data * data = (struct _wps_led_data *)param;
	int blue_or_orange=0;//0 for blue, 1 for orange
	FILE *fp;
	
	hd_led_handle = NULL;
	switch (data->mode)
	{
	default:
	case HD_ORG_NONE:
		data->led = 0;
		blue_or_orange=1;
		break;		
	case HD_CAN_REMOVE://solid orange
		data->led = 1;
		blue_or_orange=1;
		break;

	case HD_UMOUNTING://blinking
		//if hd driver remove succesfully, /var/test will be created
		//this file is created by hd_process.sh
		if( (fp=fopen("/var/test","r"))!=NULL )
		{
			sleep(1);
			hd_set_led(HD_CAN_REMOVE); //|Solid Orange   |HD can be remove safely. 
			fclose(fp);
			system("rm /var/test");					
		}
		else
		{
			hd_led_handle = sloop_register_timeout(0, 100000,
								hd_led_handler, &hd_led_data);
			data->led ^= 1;
			blue_or_orange=1;
		}
		break;
	case NO_HD:
		data->led = 0;
		blue_or_orange=0;
		break;	
	case HD_DETECT:
		data->led = 1;
		blue_or_orange=0;
		break;
	case HD_BUSY:
		hd_led_handle = sloop_register_timeout(0, 100000,
							hd_led_handler, &hd_led_data);
		data->led ^= 1;
		blue_or_orange=0;
		break;
	}
	if(blue_or_orange)
		{GPIO_HD_LED_ORANGE((data->led) ? ON:OFF);}
	else
		{GPIO_HD_LED_BLUE((data->led) ? ON:OFF);}		
}
static void hd_set_led(int mode)
{
	if (hd_led_handle) sloop_cancel_timeout(hd_led_handle);

	hd_led_data.mode = mode;
	hd_led_data.led = 0;
	hd_led_data.overlap = 0;
	hd_led_handle = sloop_register_timeout(0, 0, hd_led_handler, &hd_led_data);
}
static void hd_pbc_handler(void * param, void * sloop_data)
{
	struct _pbc_data * data = (struct _pbc_data *)param;
		
  	sloop_register_timeout(1, 0, hd_pbc_handler, &hd_pbc_data);
	if (GPIO_HD_BUTTON()==1)
    {
		if( g_hd_status==1 && data->pressed_start == 0)
		{	
			data->pressed_start = 1;
	        printf("Umount HD!\n");
	        
	        /* send KEY_K to inform lcd is unmounting */
	        system("ssignal 37 &");
	        hd_set_led(HD_UMOUNTING);//Orange |Blinking       |System is un-mounting the HD. 

			system("rgdb -i -s /runtime/nas/store_dev/devname \"\"");
			/*hendry to clear mount node*/
			system("rgdb -i -s /runtime/nas/store_dev/mount \"\"");
			sync();
			system(o_process_restart_command);//restart related process
			
			/*hendry add to clear re-format workflow */
			if(is_exist("/var/dev_need_format"))
				unlink("/var/dev_need_format");	
    	}
    else
        data->pressed_start = 0;
    }
}

/************************usock_handler**************************************************/
static int usock_handler(int sock, void * param, void * sloop_data)
{
	char buf[256];
	int ret;
	struct _usock_data * data = (struct _usock_data *)param;

	memset(buf, 0, sizeof(buf));
	ret = usock_recv(data->usock, buf, sizeof(buf), 0);
	if (ret < 0)
	{
		data->sloop = NULL;
		return -1;
	}

	d_dbg("%s: recv return %d, got message[%s]\n",__FUNCTION__, ret, buf);
	if (ret > 0)
	{
		if (strncmp(buf, "WPSCMD:", 7)==0)
		{
			memset(__cmdbuf, 0, sizeof(__cmdbuf));
			strncpy(__cmdbuf, &buf[7], sizeof(__cmdbuf)-1);
			o_wps_command = __cmdbuf;
			printf("WPS command is set to : [%s]\n",__cmdbuf);
		}
		else if (strcmp(buf, "WPS_IN_PROGRESS")==0)	wps_set_led(WPS_IN_PROGRESS);
		else if (strcmp(buf, "WPS_OVERLAP")==0)		wps_set_led(WPS_OVERLAP);
		else if (strcmp(buf, "WPS_ERROR")==0)		wps_set_led(WPS_ERROR);
		else if (strcmp(buf, "WPS_NONE")==0)		wps_set_led(WPS_NONE);
		else if (strcmp(buf, "WPS_SUCCESS")==0)		{wps_set_led(WPS_SUCCESS);system(o_wps_result);}
		else if (strcmp(buf, "WPS_SET_PROFILE")==0)	system(o_wps_setxmldb);
		else if (strcmp(buf, "WPS_START")==0)	system(o_wps_command);
		else if (strcmp(buf, "HD_BUSY")==0)		{hd_set_led(HD_BUSY);}
		else if (strcmp(buf, "HD_UMOUNT")==0)		{hd_set_led(HD_UMOUNTING);}
		else if (strcmp(buf, "HD_DETECT")==0)		{hd_set_led(HD_DETECT);}
		else if (strcmp(buf, "HD_ORG_NONE")==0)		{hd_set_led(HD_ORG_NONE);}
		else if (strcmp(buf, "HD_CAN_REMOVE")==0)		{hd_set_led(HD_CAN_REMOVE);}
		else if (strcmp(buf, "NO_HD")==0)		{hd_set_led(NO_HD);}
		else d_error("%s: unknown command [%s]\n",__FUNCTION__, buf);
	}
	return 0;
}
/************************wps led handler**************************************************/
void press_button(int value_code)
{
	struct input_event event;
	int fd;
	fd=open("/dev/input/event0",O_RDWR);
	if (fd < 0)
	{
       perror("Can't open device...\n");
       return;
    }     	
	event.type = EV_KEY;
    event.code = value_code;
    event.value = 1;    	
    gettimeofday(&event.time,0);
    
    if(write(fd,&event,sizeof(event))==-1)
       	printf("write failed \n");
    fflush(0);
    event.type = EV_KEY;
    event.code = value_code;
    event.value = 0;    	
    gettimeofday(&event.time,0);
    if(write(fd,&event,sizeof(event))==-1)
     	printf("write failed \n");
   	fflush(0);
	close(fd);	
}
static sloop_handle wps_led_handle = NULL;

static void wps_led_handler(void * param, void * sloop_data)
{
	struct _wps_led_data * data = (struct _wps_led_data *)param;

	wps_led_handle = NULL;
	switch (data->mode)
	{
	default:
	case WPS_NONE:
		data->led = 0;
		break;

	case WPS_IN_PROGRESS:
		wps_led_handle = sloop_register_timeout(0,
							(data->led) ? 100000 : 200000,
							wps_led_handler, &wps_led_data);
		data->led ^= 1;
		break;

	case WPS_ERROR:
		wps_led_handle = sloop_register_timeout(0, 100000,
							wps_led_handler, &wps_led_data);
		data->led ^= 1;
		break;

	case WPS_OVERLAP:
		if (data->overlap < 10)
		{
			wps_led_handle = sloop_register_timeout(0, 100000,
								wps_led_handler, &wps_led_data);
			data->overlap++;
			data->led ^= 1;
		}
		else
		{
			wps_led_handle = sloop_register_timeout(0, 500000,
								wps_led_handler, &wps_led_data);
			data->overlap = 0;
			data->led = 0;			
		}
		break;

	case WPS_SUCCESS:
		if (data->led == 0) wps_led_handle = sloop_register_timeout(5, 0,
								wps_led_handler, &wps_led_data);
		data->led ^= 1;
		break;
	}
	GPIO_WPS_LED((data->led) ? ON:OFF);
}
static void wps_set_led(int mode)
{
	if (wps_led_handle) sloop_cancel_timeout(wps_led_handle);

	wps_led_data.mode = mode;
	if(mode==WPS_NONE)
		press_button(KEY_0);
	else if(mode==WPS_IN_PROGRESS)
		press_button(KEY_1);
	else if(mode==WPS_ERROR)
		press_button(KEY_2);
	else if(mode==WPS_OVERLAP)
		press_button(KEY_3);
	else if(mode==WPS_SUCCESS)
		press_button(KEY_4);
	wps_led_data.led = 0;
	wps_led_data.overlap = 0;
	wps_led_handle = sloop_register_timeout(0, 0, wps_led_handler, &wps_led_data);
}
/**************************************************************************/
////////////////////////////////////////////////////////////////
//switch related
//////////////////////////////////////////////////////////////////
typedef enum _CABLE_STATUS
{
    CABLE_UNKNOWN_ERROR = 0,
    CABLE_CONNECTED = 1,
    CABLE_OPEN = 2,
    CABLE_SHORT = 3,
    CABLE_NOCABLE = 4
}
CABLE_STATUS;

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

static int gpio_in(int port, int line)
{
	char buf[64];
	FILE * fh = NULL;
	int retry;

	sprintf(buf, "/proc/nas_gpio/gpio/data_p%c_%d", port+'a', line);
	for (retry=0; retry<GPIO_RETRY && !fh; retry++) fh = fopen(buf, "r");
	if (fh)
	{
		fread(buf, sizeof(char), sizeof(buf), fh);
		fclose(fh);
		if (buf[0] == '0') return 0;
	}
	else
	{
		//fprintf(stderr, "%s: can not open [%s] to read, retry = %d.\n",__FUNCTION__, buf, retry);
	}
	return 1;
}

static int psts_main(int argc, char * argv[])
{
	int opt, fd;
	int port = -1;

	getPortLinkState_t portLinkState;

	fd = open(RTL8366S_IOCTL_DEV, O_RDONLY);
	if (fd <=0) {
		 return -1;
	}
	while ((opt = getopt(argc, argv, "hi:")) > 0)
	{
		switch (opt)
		{
			case 'h':
				printf("Usage: psts [OPTIONE]\n");
				printf("    -h          show this message.\n");
				printf("    -i {port}   specify port index.\n");
				return 0;
				break;
			case 'i':
				port = atoi(optarg);
				break;
		}
	}

	if (port < 0 || port > 4)
	{
		printf("Invalid port number, should be 0~4 !\n");
		if(fd) close(fd);
		return -1;
	}
	portLinkState.port = port;
	ioctl(fd, GETPORTLINKSTATE, &portLinkState);
//	printf("port:%d, speed:%d, duplex:%d,link:%d, txPause:%d, rxPause:%d, nWay:%d\n", portLinkState.port, portLinkState.speed, portLinkState.duplex, portLinkState.link, portLinkState.txPause, portLinkState.rxPause, portLinkState.nWay);
	if (!portLinkState.link)
		printf("%d\n",TYPE_DISCONNECT);
	else {
		if (portLinkState.speed == SPD_1000M) 
			printf("%d\n",(portLinkState.duplex ? TYPE_1000FULL:TYPE_1000HALF));
		else
		if (portLinkState.speed == SPD_100M)
			printf("%d\n",(portLinkState.duplex ? TYPE_100FULL:TYPE_100HALF));
		else
			printf("%d\n",(portLinkState.duplex ? TYPE_10FULL:TYPE_10HALF));
	}
	
	if(fd) close(fd);
	return 0;
}

static int ctest_main(int argc, char * argv[])
{
#if 1
        printf("do not support cable test now\n");
#else	
        int opt, fd;
	int port = -1, maxChannel, channelNum;
	setRtctTesting_t rtctTesting;
	getRtctResult_t	rtctResult;
	getPortLinkState_t portLinkState;
	getRtctResult_t rtctResults[CH_MAX];
	unsigned txRxStatus, txRxMeters;

	fd = open(RTL8366S_IOCTL_DEV, O_RDONLY);
	if (fd <=0) {
		 return -1;
	}

	while ((opt = getopt(argc, argv, "hi:")) > 0)
	{
		switch (opt)
		{
			case 'h':
				printf("Usage: ctest [OPTIONE]\n");
				printf("    -h          show this message.\n");
				printf("    -i {port}   specify port index.\n");
				return 0;
				break;
			case 'i':
				port = atoi(optarg);
				break;
		}
	}
	if (port < 0 || port > 4)
	{
		printf("Invalid port number, should be 0~4 !\n");
		if(fd) close(fd);
		return -1;
	}
	portLinkState.port = port;
	ioctl(fd, GETPORTLINKSTATE, &portLinkState);
	if (portLinkState.link) {
		printf("STATUS=1\nMETER=0\n");
	}
	else {
			maxChannel=4;
			rtctTesting.port = port;
			rtctResult.port = rtctTesting.port;
			for ( channelNum=0; channelNum < maxChannel; channelNum++) {
			
				rtctTesting.channel = channelNum;
				rtctResult.channel = rtctTesting.channel;
				ioctl(fd, SETRTCTTESTING, &rtctTesting);
				sleep(2);
				ioctl(fd, GETRTCTRESULT, &rtctResult);
//				printf("Port:%d,channel:%d,short:%d,open:%d,length:%d\n",rtctResult.port,rtctResult.channel,rtctResult.shortSts,rtctResult.openSts,rtctResult.length);
				memcpy(&rtctResults[channelNum], &rtctResult, sizeof(rtctResult));
			}
/*			
			printf("--------------------------------------------------------\n");
			for ( channelNum=0; channelNum < maxChannel; channelNum++) {
			printf("Port:%d,channel:%d,short:%d,open:%d,length:%d\n",
					rtctResults[channelNum].port,rtctResults[channelNum].channel,rtctResults[channelNum].shortSts,rtctResults[channelNum].openSts,rtctResults[channelNum].length);
			}
*/
			for ( channelNum=0; channelNum < maxChannel; channelNum++) {
				if (rtctResults[channelNum].shortSts == TRUE || rtctResults[channelNum].openSts == TRUE) {
					break;
				}
			}
			if (rtctResults[channelNum].openSts == TRUE) {
				txRxStatus = CABLE_OPEN;
				txRxMeters = rtctResults[channelNum].length;
				//+++jana
				txRxMeters--;
				if(txRxMeters < 0)
					txRxMeters++;
				//---jana
			} 
			else if (rtctResults[channelNum].shortSts == TRUE) {
				txRxStatus = CABLE_SHORT;
				txRxMeters = rtctResults[channelNum].length;
			}
			else {
				txRxStatus = 0;
				txRxMeters = 0;
			}
			printf("STATUS=%d\nMETER=%d\n",txRxStatus,txRxMeters);
			
		}	

	if(fd) close(fd);
	return 0;
#endif
}

static int slinktype_main(int argc, char * argv[])
{
	int opt, fd;
	int type = -1;
	int port = -1;

	setPhyEthernetPhy_t etPhy;
    fd = open(RTL8366S_IOCTL_DEV, O_RDONLY);
    if (fd <=0) {
	    return -1;
	}

	while ((opt = getopt(argc, argv, "hi:d:")) > 0)
	{
		switch (opt)
		{
			case 'h':
				printf("Usage: slinktype [OPTIONS]\n");
				printf("    -h           show this message.\n");
				printf("    -i {port}    specify port index.\n");
				printf("    -d {type}    specify media type.\n");
				printf("        0: auto-negotiation.\n");
				printf("        1: 100Full.\n");
				printf("        2: 100Half.\n");
				printf("        3: 10Full.\n");
				printf("        4: 10Half.\n");
				printf("        5: 1000Full.\n");
				return 0;
				break;
			case 'i':
				port = atoi(optarg);
				break;
			case 'd':
				type = atoi(optarg);
				break;
		}
	}

	if (port < 0 || port > 4)
	{
		printf("Invalid port number, should be 0~4 !\n");
		return -1;
	}
	etPhy.port = port;
	etPhy.mode = type;
	ioctl(fd, SETETHERNETPHY, &etPhy);
	if(fd) close(fd);
	return 0;
}
static int ptmode_main(int argc, char *argv[])
{
	int opt, fd, args=0;
	setPhyTestMode_t ptmode;
	

	fd = open(RTL8366S_IOCTL_DEV, O_RDONLY);
	if (fd <=0) {
		return -1;
	}	
	while ((opt = getopt(argc, argv, "hp:m:")) > 0)
	{
		switch(opt)
		{
			case 'h':
				printf("Usage: ptmode -p [phy] -m [testmode]\n");
				printf("phy: 0~4		mode:0~4\n");
				printf("This command is for switch 802.3 test only!!\n");
				break;
			case 'p':
				ptmode.phy = atoi(optarg);
				args++;
				break;
			case 'm':
				ptmode.mode = atoi(optarg);
				args++;
				break;
			default:
				break;
		}
	}
	if (args == 2)
		ioctl(fd, SETPHYTESTMODE, &ptmode);

	if(fd) close(fd);
	return 0;
}
static int gether_main(int argc, char *argv[])
{
	int opt, fd, args=0,enable=-1;

	fd = open(RTL8366S_IOCTL_DEV, O_RDONLY);
	if (fd <=0) {
		return -1;
	}	
	while ((opt = getopt(argc, argv, "he:")) > 0)
	{
		switch(opt)
		{
			case 'h':
				printf("Usage: gether -e [0/1]\n");
				break;
			case 'e':
				enable = atoi(optarg);
				args++;
				break;
			default:
				break;
		}
	}
	
	if (args == 1 && enable >= 0)
		ioctl(fd, SETGREENETHERNET, &enable);

	if(fd) close(fd);
	return 0;
}

/////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////



static int devmod_main(int argc, char *argv[])
{
	printf("need set gmac to bridge mode\n");
	return 0;
}
///////////////////////////////////////////////////////////////////
int main(int argc, char * argv[])
{
	int ret = 0;
	char * base;

	base = strrchr(argv[0], '/');
	if (base) base = base + 1;
	else base = argv[0];

	if		(strcmp(base, "fresetd")==0)	ret = fresetd_main(argc, argv);
	else if	(strcmp(base, "psts")==0)		ret = psts_main(argc, argv);
	else if	(strcmp(base, "ctest")==0)		ret = ctest_main(argc, argv);
	else if	(strcmp(base, "slinktype")==0)	ret = slinktype_main(argc, argv);
	else if (strcmp(base, "devmod")==0)		ret = devmod_main(argc, argv);
	else if (strcmp(base, "ptmod")==0)		ret = ptmode_main(argc, argv);
	else if	(strcmp(base, "gether")==0)		ret = gether_main(argc, argv);
	
	return ret;
}


