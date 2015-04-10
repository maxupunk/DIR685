#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stddef.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <directfb.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <errno.h>
#include <stdlib.h>
#include <xmldb.h>
#include <libxmldbc.h>
#include "alpha_dfb_define.h"
#include "nas_str_define.h"
#include "menu_tool.h"
#include "confirm_center.h"
#include "st_router_info.h"
#include "alert_center.h"
#include "application.h"
#include "rgdb_node_define.h"

//start extern variable or function from main.c
extern IDirectFB *gp_dfb;
extern DFBWindowDescription win_dsc;
extern IDirectFBDisplayLayer *main_layer;
extern DFBRectangle *screen_space;
extern TimeTab gTimeTab;

extern int export_from_file(char *filename, char *p_eventbuffer, int buf_len);

//*********************************************

unsigned char ghd_devname[RGDBBUFFER_SIZE];
	
void GetHardDriveName(char *hd_devname)
{
	memset(hd_devname, 0x0, RGDBBUFFER_SIZE);
	xmldbc_get_wb(NULL, 0, RGDB_HD_DEVNAME, hd_devname, RGDBBUFFER_SIZE);
	return;
}

#define DEFAULT_CHECK_FORMAT_PATH "/var/dev_need_format"
#define DEFAULT_FORMATTING_STATUS "/var/format_pgrs"
#define FORMAT_HD_RETRY 2
int gdev_need_format_from_web=0; //support web ui to do format

#if 0
int check_format_and_mount(char *diskname)
{
	/* hendry modify : */
	char source[30];
	char target[30];
	int ret = 0;
	char command[128];
	char *p_tmp=NULL;
	
	sprintf(source,"/dev/%s",diskname);
	p_tmp=strstr(diskname,"d");
	p_tmp++;
	sprintf(target,"/tmp/storage_dev/HD_%s",p_tmp);
	
	sprintf(command,"/bin/mkdir -p %s",target);
	system(command);
	
	#ifdef DEFAULT_STORAGE_FS
		printf("DEFAULT_STORAGE_FS : %s\n", DEFAULT_STORAGE_FS);
		printf("source : %s\ntarget : %s\n", source, target);
		if(strcmp(DEFAULT_STORAGE_FS,"EXT3")==0)
		{
			if((ret = mount(source, target,"ext3",0,""))==0)
				return 1;
			else
			{ 
				printf("ret is : %d\n", ret);
				printf("errno is : %d : %s\n",errno, strerror(errno));
				return 0;
			}
		}
		else if(strcmp(DEFAULT_STORAGE_FS,"EXT2")==0)
		{
			if((mount(source, target,"ext2",0,""))==0)
				return 1;
			else 
			{
				printf("ret is : %d\n", ret);
				printf("errno is : %d : %s\n",errno, strerror(errno));
				return 0;
			}
		}
		else	//NTFS format
		{
			if((mount(source, target,"ufsd",0,"umask=000"))==0)
				return 1;
			else 
			{
				printf("ret is : %d\n", ret);
				printf("errno is : %d : %s\n",errno, strerror(errno));
				return 0;
			}
		}
		
	#else
		if((mount(source, target,"ufsd",0,"umask=000"))==0)
			return 1;
		else 
		{
			printf("ret is : %d\n", ret);
			printf("errno is : %d : %s\n",errno, strerror(errno));
			return 0;
		}
		printf("source : %s\ntarget : %s\n", source, target);
	#endif
}
#else
#define DEFINE_MOUNT_CHECK_PATH "/var/mnt_dev_tmp.txt"
int check_format_and_mount(char *diskname)
{
	/* +++ hendry modify 
		1. Check if we can mount the new hd
		2. Check if format process reach above 97%, return success.
		   
		Note :   
			The second check is needed, because the first check is not so valid if the format process
		   	is from trigerred from the web, since the mount will always success. 
	*/
	
	char command[128];
	FILE *fp;
	char *buff=NULL,*pstr=NULL;
	int size=0,ret=0;
	
	sprintf(command,"/etc/templates/hd_process.sh start_process_for_format > %s",DEFINE_MOUNT_CHECK_PATH);
	printf(command);
	system(command);
	//1. Check if we can mount the new hd
	size=get_file_size(DEFINE_MOUNT_CHECK_PATH)+1;
	sprintf(command,"cat %s",DEFINE_MOUNT_CHECK_PATH);
	if((fp = popen(command, "r"))!=NULL)
	{
		buff=(char*)malloc(size*sizeof(char));
		memset(buff, 0, size);
		fread(buff, 1, size, fp);
		pclose(fp);
		unlink(DEFINE_MOUNT_CHECK_PATH);
		if((pstr=strstr(buff,"Mount success")))
		{
			printf("Mount success\n");
			ret=1;
		}
		else
		{
			printf("Mount failed\n");
			ret=0;
		}
		free(buff);
	}
	//2. Check if format process reach above 97%, return success.
	/* double check (above check isn't so valid if doing format from web) */
	if(ret==1)
	{
		
		if(access(DEFAULT_FORMATTING_STATUS, F_OK)==0)	//if file exist
		{
			size=get_file_size(DEFAULT_FORMATTING_STATUS)+1;
			sprintf(command,"cat %s",DEFAULT_FORMATTING_STATUS);
			if((fp = popen(command, "r"))!=NULL)
			{
				buff=(char*)malloc(size*sizeof(char));
				memset(buff, 0, size);
				fread(buff, 1, size, fp);
				pclose(fp);
				printf("buff is : %s\n", buff);
				
				if(atoi(buff)>97)	//assume that if progress already reach 97%, format is success. 
					ret = 1;	
				else 
					ret = 0;	
						
				free(buff);
			}
		} else
			ret = 0;
	}
	return ret;
}
#endif

//**********************************************
char* do_format(void)
{
	char diskname[128],command[128];
	unsigned char *resultmsg;
	int i,do_flag=0;
	
	resultmsg=(char *)malloc(24);
	memset(resultmsg,0,sizeof(resultmsg));
	memset(diskname,0,sizeof(diskname));
	
	if((do_flag=export_from_file(DEFAULT_CHECK_FORMAT_PATH, diskname, sizeof(diskname)))==-1)
	{
		if(gdev_need_format_from_web==1)
		{
			do_flag=1;
			strncpy(diskname,ghd_devname,strlen(ghd_devname));
		}
		else
			printf("Format: %s and gdev_need_format_from_web flag is not setting.\n",DEFAULT_CHECK_FORMAT_PATH);
	}
	if(do_flag==1)
	{
		system("/etc/templates/hd_process.sh end_process_for_format\n");
		for(i=0;i<FORMAT_HD_RETRY;i++)
		{
			/*hendry modify for choosing default filesystem from arch.mk*/
#ifdef DEFAULT_STORAGE_FS
				if(strcmp(DEFAULT_STORAGE_FS,"EXT3")==0)
					sprintf(command, "mke2fs /dev/%s -m 1 -j -F -v ", diskname);
				else if(strcmp(DEFAULT_STORAGE_FS,"EXT2")==0)
					sprintf(command, "mke2fs /dev/%s -m 1 -F -v ", diskname);
				else	//NTFS format
					sprintf(command, "mkntfs /dev/%s -f -F -v ", diskname);
#else
			sprintf(command, "mkntfs /dev/%s -f -F -v > /var/format_result", diskname);
#endif
			dprintf("********* system command=%s **************\n",command);
			system(command);
			
			if(check_format_and_mount(diskname))
			{
				//mount ok means format ok
				sprintf(command, "rgdb -i -g /runtime/nas/store_dev/devname %s", diskname);
				system(command);
				/* +++ Teresa, move to hd_process.sh
				//restarting smart spindown count
				system("killall smart_spindown");
				if(gTimeTab.HardDriveTimeout==NEVER_RUN_TIMEOUT)
					sprintf(command, "smart_spindown /dev/%s 0 &", diskname);//never=0
				else
					sprintf(command, "smart_spindown /dev/%s %d &", diskname, gTimeTab.HardDriveTimeout);
				system(command);
				*/
				unlink(DEFAULT_CHECK_FORMAT_PATH);
				unlink(DEFAULT_FORMATTING_STATUS);
#ifndef DEFAULT_STORAGE_FS
				unlink(FORMAT_RESULT_FILE);
#endif
				strcpy(resultmsg, DETECT_INFO_FORMAT_OK);
				break;
			}
			dprintf("Format: format error and retry.\n");
		}
	}
	if(resultmsg[0]=='\0')
	{
		//format error
		strcpy(resultmsg, DETECT_INFO_FORMAT_FAIL);
	}
	return resultmsg;
}

void Detect_AND_FORMAT_HD(IDirectFBEventBuffer *p_eventbuffer)
{		
	int ret;
	Messages MsgTable[2];
	
	memset(MsgTable,0,sizeof(MsgTable));
	MsgTable[0].msg=DETECT_INFO_FORMAT_HD;
	MsgTable[1].msg=DETECT_INFO_ASK;
	ret = Confirm_Center_Control(p_eventbuffer,MsgTable,sizeof(MsgTable)/sizeof(MsgTable[0]),SELECT_LIMIT);
	if(ret)	//yes
	{
		GetHardDriveName(ghd_devname);
		gdev_need_format_from_web=1;
		memset(MsgTable,0,sizeof(MsgTable));
		MsgTable[0].msg=DETECT_INFO_DOFORMAT;
		MsgTable[1].msg=DETECT_INFO_WAIT;
		//Message_Center_Control(p_eventbuffer,MsgTable,sizeof(MsgTable)/sizeof(MsgTable[0]),&do_format,"cat "DEFAULT_FORMATTING_STATUS,"Finish formatting");//jana removed
		Message_Center_Control(p_eventbuffer,MsgTable,sizeof(MsgTable)/sizeof(MsgTable[0]),&do_format,"cat "DEFAULT_FORMATTING_STATUS,"Formatting");//jana added
		gdev_need_format_from_web=0;
	}
}

void Detect_HW(IDirectFBEventBuffer *p_eventbuffer)
{		
	int ret;
	Messages MsgTable[2];
	
	memset(MsgTable,0,sizeof(MsgTable));
	MsgTable[0].msg=DETECT_INFO_DETECT_HD;
	MsgTable[1].msg=DETECT_INFO_ASK;
	ret = Confirm_Center_Control(p_eventbuffer,MsgTable,sizeof(MsgTable)/sizeof(MsgTable[0]),SELECT_LIMIT);
	if(ret)	//yes
	{
		memset(MsgTable,0,sizeof(MsgTable));
		MsgTable[0].msg=DETECT_INFO_DOFORMAT;
		MsgTable[1].msg=DETECT_INFO_WAIT;
		Message_Center_Control(p_eventbuffer,MsgTable,sizeof(MsgTable)/sizeof(MsgTable[0]),&do_format,"cat "DEFAULT_FORMATTING_STATUS,"Formatting");
	}
}

void Detecting_HW(IDirectFBEventBuffer *p_eventbuffer)
{
	Messages MsgTable[2];
	
	memset(MsgTable,0,sizeof(MsgTable));
	MsgTable[0].msg=DETECT_INFO_DODETECT;
	
	Detect_Message_Center_Control(p_eventbuffer,MsgTable,sizeof(MsgTable)/sizeof(MsgTable[0]));
}

void Unmounting_HW(IDirectFBEventBuffer *p_eventbuffer)
{
	Messages MsgTable[2];
	
	memset(MsgTable,0,sizeof(MsgTable));
	MsgTable[0].msg=DETECT_INFO_DOUNMOUNTING;
	
	Unmounting_Message_Center_Control(p_eventbuffer,MsgTable,sizeof(MsgTable)/sizeof(MsgTable[0]));
}

void Detect_FWUpgrade(IDirectFBEventBuffer *p_eventbuffer)
{		
	DFBRectangle *screen_info_space;
	GridObj *grid;
	IconObj *icon;		
	int grid_count=1;
	Messages MsgTable[3];
	
	//start draw menu init	        
	screen_info_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	grid_init(screen_info_space, 70, 70, screen_space->w-(70*2), screen_space->h-(70*2));
	grid=create_view_tree(grid_count, screen_info_space);			
	icon=create_icon_tree(grid, main_layer, win_dsc); 
	memset(MsgTable,0,sizeof(MsgTable));
	MsgTable[0].msg=DETECT_INFO_FIRMWARE;
	MsgTable[1].msg=DETECT_INFO_WAIT;
	MsgTable[2].msg=DETECT_INFO_DOBACKUP_HD;
	draw_detected_ui(icon, screen_info_space, MsgTable, sizeof(MsgTable)/sizeof(MsgTable[0]), DONOTHAVECONFIRM);
	
	while(1)
	{
		//process already die.
	}
}

void Detect_HWMount(IDirectFBEventBuffer *p_eventbuffer)
{		
	Alert_Center(p_eventbuffer,DETECT_INFO_DETECT_HDMOUNT);
}

//+++ for USB backup
char gdetect_usb_path[128];

#define DEFINE_TMP_SIZE_FILE "/var/size_tmp"
unsigned int get_available_size(char *name)
{
	FILE *fp;
	char command[128];
	unsigned int size=0;
	
	sprintf(command,"/bin/df|grep %s|scut -f 4 > %s",name,DEFINE_TMP_SIZE_FILE);
	system(command);
	if((fp = fopen(DEFINE_TMP_SIZE_FILE, "r"))!=NULL)
	{
		fscanf(fp,"%d",&size);
		fclose(fp);
		unlink(DEFINE_TMP_SIZE_FILE);
	}
	return size;
}

char* get_mount_devpath(char *pkname){
	FILE *file;	
	char *buff=NULL, *devpath=NULL, *pstrbuff=NULL;	
	int size, len;
	char strbuf[64]="";
		
	file=fopen(MOUNT_TABLE_PATH, "r");
	if(file!=NULL){
		size=get_file_size(MOUNT_TABLE_PATH)+1;		
		pstrbuff=(char*)malloc(size*sizeof(char));
		memset(pstrbuff, 0, size);
		fread(pstrbuff, 1, size, file);		
		buff=pstrbuff;
		do {			
			if(*(buff+1)=='\0') break;	//last line
			if(*buff=='\n')	buff++;		
			if(strncmp(buff,pkname,strlen(pkname))==0 && *pkname!='\0')
			{
				buff=strstr(buff,"\n");
				buff++;
				strncpy(strbuf,buff,strstr(buff,"\n")-buff+1);
				devpath=strbuf;
				break;
			}
			devpath=buff;									
		}while((buff=strstr(buff,"\n"))!=NULL);
		devpath=strdup(devpath);				
		free(pstrbuff);
		if((len=strlen(devpath))>1)		//avoid devpath==""
			*(devpath+len-1)='/';
		fclose(file);	
	}else{
		printf("\n\nusb_error\n\n");
	}	
	return devpath;
}	

char* do_backup_fromUSB(void)
{
	struct tm *p_time;
	char path_buf[128],command[256],*hd_devpath;
	unsigned int dst_size=0,sourse_size=0;
	char *resultmsg;
	
	resultmsg=(char *)malloc(24);
	memset(path_buf,0,sizeof(path_buf));
	
	dst_size=get_available_size(ghd_devname);
	strncpy(path_buf,gdetect_usb_path,strlen(gdetect_usb_path)-1);
	sourse_size=get_available_size(path_buf);
	hd_devpath=get_mount_devpath(ghd_devname);
	if(dst_size>sourse_size && dst_size!=0 && sourse_size!=0)
	{
		if( sourse_size<(20*1024*1024)/*20GB*/ )
		{
			p_time=localtime(&gTimeTab.timep);	
			sprintf(path_buf,"%sUSB_%d%02d%02d_%02d%02d%02d_%02d",
					hd_devpath,(1900+p_time->tm_year),
					(1+p_time->tm_mon),p_time->tm_mday,p_time->tm_hour,p_time->tm_min,p_time->tm_sec, 
					(int)(random()%100));
			mkdir(path_buf,0777);
			sprintf(command,"cp -r '%s.' %s",gdetect_usb_path,path_buf);
			//dprintf("command=%s\n",command);
			system(command);
			
			/* +++ hendry : to let others modify/edit the backup data */
			sprintf(command,"chmod -R 0777 %s",path_buf);
			system(command);
			/* --- hendry */
						
			resultmsg=DETECT_INFO_BACKUP_OK;
		}
		else
			resultmsg=DETECT_INFO_BACKUP_ERR;
	}
	else
	{
		resultmsg=DETECT_INFO_BACKUP_FAIL;
	}
	free(hd_devpath);
	return resultmsg;
}

void Detect_USBMount(IDirectFBEventBuffer *p_eventbuffer)
{		
	Messages MsgTable[2];	
	char *devpath;
	int msg_count=0,ret, is_top_layer=0;
	IconObj *folder;
	
	GetHardDriveName(ghd_devname);
	memset(MsgTable,0,sizeof(MsgTable));
	MsgTable[msg_count++].msg=DETECT_INFO_VIEW_PHOTO;
	if(ghd_devname[0]!='\0')
		MsgTable[msg_count++].msg=DETECT_INFO_BACKUP_USB;
	ret = RadioButton_Center(p_eventbuffer, DETECT_INFO_DETECT_USB, MsgTable, msg_count);
	
	devpath=get_mount_devpath("");		
	if(devpath==NULL) return;			
//	dprintf("\ndevpath %s\n", devpath);
	switch(ret)
	{
		case 1:			
			//create a UI direction to show folder that we selected			
			folder=folder_selected(FOLDER_SELECTED_G, gp_dfb, main_layer, win_dsc);			
			//photo		
			Album_Local_App(p_eventbuffer, devpath, is_top_layer, folder);
			icons_free(folder);
			break;
		case 2:
			//backup	
			msg_count=0;
			memset(MsgTable,0,sizeof(MsgTable));
			MsgTable[msg_count++].msg=DETECT_INFO_DOBACKUP_USB;
			strcpy(gdetect_usb_path,devpath);
			Message_Center(p_eventbuffer, MsgTable, msg_count, &do_backup_fromUSB);
			break;
	}			
	free(devpath);
}
