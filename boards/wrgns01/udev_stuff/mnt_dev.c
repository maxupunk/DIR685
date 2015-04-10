#include <stdio.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include<linux/kd.h>
#include<linux/input.h>
#include<errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/keyboard.h>
#include "mnt.h"

#define GET_KEY_FILE "/sbin/udevd"
int g_sem_id;//semaphore id
char g_cmd_buf[1024];

void press_button(int value_code);
void inform_panel(char *devname);

static int sem_wait(const int sem_id)
{
	struct sembuf sem_b;

	sem_b.sem_num = 0;
	sem_b.sem_op = -1;
	sem_b.sem_flg = SEM_UNDO;
	return semop(sem_id, &sem_b, 1);
}
static int sem_signal(const int sem_id)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = 1;
	sem_b.sem_flg = SEM_UNDO;
	return semop(sem_id, &sem_b, 1);
}

void reload_smbd_if_open_mode()
{
	FILE *fp=fopen("/var/open_mode","r");
	if(fp!=NULL)
	{
		system("/etc/templates/network_access.sh reload");	
		fclose(fp);
	}
}
int mount_SATA_HD(char *source,char *target)
{
	FILE *out_f=NULL;
	char *devname = strrchr(source,'/')+1;
	char mount_type[50];
	char mount_args[50];
	
	#ifdef DEFAULT_STORAGE_FS
		if(strcmp(DEFAULT_STORAGE_FS,"EXT3")==0)
		{
			strcpy( mount_type, "ext3"); 
			strcpy( mount_args, ""); 
		}
		else if(strcmp(DEFAULT_STORAGE_FS,"EXT2")==0)
		{
			strcpy( mount_type, "ext2");
			strcpy( mount_args, ""); 
		}
		else
		{	
			strcpy( mount_type, "ufsd");
			strcpy( mount_args, "umask=000"); 
		}
	#else
		strcpy( mount_type, "ufsd");
		strcpy( mount_args, "umask=000"); 
	#endif
	
	printf("default mount_type is %s\n", mount_type);
	
	/*we check if hd format type is our default format type*/
	if((mount(source, target,mount_type,0,mount_args))==0)
	{	//mount success
		char data[128];
		char file[128];
		FILE *fp=NULL;
		char *tmp=NULL;
		char port[10];
		char kernel_name[10];
		char tmp_kernel_name[10];
		int hd_status;
		char command[100];
		
		int hd_is_plugged_from_beginning = 0;
		
		#ifdef DEFAULT_STORAGE_FS
			strcpy(data,DEFAULT_STORAGE_FS);
		#else
			strcpy(data,"NTFS");
		#endif
		
		strcpy(file,"/var/fs_");
		strcat(file,devname);
		export_to_file(data,file,"w+");
		printf("Mount SATA_HD in %s fs\n", mount_type);
		
		//read sata_stat again, if it is HD, save to db
		fp=fopen("/proc/sata_stat","r");
   
       	fscanf(fp,"%s %d %s\n",&port,&hd_status,&tmp_kernel_name);
       	fclose(fp);
       	sprintf(kernel_name,"/dev/%s",tmp_kernel_name);
       	printf("====marco hd_status %d source %s kernel_name %s \n",hd_status,source,kernel_name);
		if(hd_status==1 && (strcmp(source,kernel_name)==0) )
		{
			tmp=target;
			tmp+=strlen("/tmp/storage_dev/");
			sprintf(command,"rgdb -i -s /runtime/nas/store_dev/mount %s",tmp);
			
			system(command);
		}	
		reload_smbd_if_open_mode();	
		return 1;
	}
	else
	{	//mount failed
		char command[50];
		sprintf(command,"rm -rf %s &\n",target);
		system(command);
		out_f=fopen(DEVNAME_TOBE_FORMATTED_FILE,"w+");
		if(out_f==NULL)
		{
			printf("Open file failed : %s \n", DEVNAME_TOBE_FORMATTED_FILE);
		    return 0;
		}
		fprintf(out_f,"%s",devname);
		fclose(out_f);
		
		return 0;
	}	
}

int mount_USB(char *source,char *target)
{
	char *devname = strrchr(source,'/')+1;
	int ret = 0;
	if((ret=mount(source, target,"ufsd",0,"umask=000"))==0)
	{	
		printf("Mount USB in NTFS fs\n");
	}
	else if((ret=mount(source, target,"ext3",0,""))==0)
	{
		printf("Mount USB in ext3 fs\n");
		//char fstab_data[128];
		//sprintf(fstab_data,"%s %s ext3 defaults,usrquota,grpquota 0 0",source,target);
		//export_to_file(fstab_data,"/var/fstab");
		/*inform panel an usb is plugged*/
		//press_button(KEY_A);
		//return 1;
	}
	else if((ret=mount(source, target,"ext2",0,""))==0 )
	{
		printf("Mount USB in ext2 fs\n");
		//char fstab_data[128];
		//sprintf(fstab_data,"%s %s ext2 defaults,usrquota,grpquota 0 0",source,target);
		//export_to_file(fstab_data,"/var/fstab");
		/*inform panel an usb is plugged*/
		//press_button(KEY_A);
		//return 1;
	}
	else if((ret=mount(source, target,"vfat",0,"iocharset=utf8,umask=000,shortname=winnt"))==0 )
	{
		/*inform panel an usb is plugged*/
		//press_button(KEY_A);
		//return 1;
	}
	
	
	if(ret == 0)
	{	//mount USB success
		/* +++ Teresa Ke, move to final finish. */
		//inform USBa or USBb to the panel
		//inform_panel(devname);
		
		reload_smbd_if_open_mode();	
		return 1;
	}
	else
	{	//mount failed
		/*inform panel an unknown device is plugged*/
		char command[50];
		sprintf(command,"rm -rf %s &\n",target);
		system(command);
		/* +++ Teresa Ke, move to final finish. */
		//press_button(KEY_E);
		printf("ret is : %d\n", ret);
		printf("errno is : %d : %s\n",errno, strerror(errno));
		//fprintf(stderr, "errno is : %d : %s\n",errno, strerror(errno));
		return 0;
	}	
}

int mount_dev(char *source,char *target, int is_sata)
{
	if (is_sata)	
		return mount_SATA_HD(source,target);
	else
		return mount_USB(source,target);
}

int import_from_file(char *filename, char *p_buffer, int buf_len)
{
	int total_read = 0;
	FILE *fd=NULL;
    fd=fopen(filename,"r");
    if(fd==NULL)
    {
    	printf("Open file failed : %s \n", filename);
    	return -1;
	}
	total_read  = fread(p_buffer ,1, buf_len ,fd);
    fclose(fd);
    return total_read;
}

int export_to_file(char *data,char *file,char *mode)
{
	FILE *out_f=NULL;
    out_f=fopen(file,mode);
    if(out_f==NULL)
    {
    	printf("Open file failed : %s \n", file);
        return 0;
	}
	//hendry modify : "%s\n" to "%s"
	fprintf(out_f,"%s\n",data);
    fclose(out_f);
    return 1;
}
void press_button(int value_code)
{
	struct input_event event;
	int fd;
	fd=open("/dev/input/event0",O_RDWR);
	if (fd < 0)
	{
       perror("Can't open device...\n");
       sem_signal(g_sem_id);
       exit(1);
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

static int is_sata()
{
    if(is_exist("/var/is_sata_hd"))
    {
	    //directly delete the file if exist
	    printf("It is sata hd\n");
	    printf("Deleting file\n");
	    system("rm -rf /var/is_sata_hd");
		return 1;
	}
	else
		return 0;
}

void inform_panel(char *devname)
{
	/*
		look for /var/USBa and /var/USBb. If either is empty, fill it with devname of USB. 
	*/
	char filename[100];
	
	if(is_exist(USB1_DETECT_FILE))
	{
		if(is_exist(USB2_DETECT_FILE))
		{
			strcpy(filename, "");
		}
		else
		{
			strcpy(filename, USB2_DETECT_FILE);
			//send key B to inform panel USBb is plugged
			press_button(KEY_B);
		}
	}
	else
	{
		strcpy(filename, USB1_DETECT_FILE);
		//send key A to inform panel USBa is plugged
		press_button(KEY_A);
	}
    
    if(strcmp(filename, "")==0)
    {
    	printf("USB ports are full. TODO case\n");
    	return;
    }
    
	if(export_to_file(devname, filename,"w+")==0)
		printf("[hendry] Inform panel failed\n");
	else
		printf("[hendry] Inform panel success, create file %s\n",filename );	
}
#if 0
void handle_str(char *input)
{
	char *tmp=NULL;
	int i=0,len=0,y=0;
	char buf[100];
	tmp=strstr(input,"  ");
	if(tmp!=NULL)
		*(char *)tmp=NULL;
	tmp=strstr(input,"\"");
	if(tmp!=NULL)
		*(char *)tmp=NULL;	
#if 1			
	//we check any special character inside the string
	//if it contains any special character, we will replace it with '_'	
	len=strlen(input);
	for(i=0;i<len;i++)
	{
		if( !isalnum(input[i]) )
			continue;
		else
		{	
			buf[y]=input[i];
			y++;
		}
	}
	buf[y]='\0';
	strcpy(input,buf);	
#else	
	tmp=strstr(input," ");
	while(tmp!=NULL)
	{
		*(char *)tmp='_';
		tmp++;
		tmp=strstr(tmp," ");
	}
#endif	
}

int get_attr_by_popen(char *buf,int opt,char *argv)
{
	FILE *fp=0;
	char read_model_path[200];
	char read_in_buf[100];
	char *tmp=NULL,*tmp1=NULL;
	int try_again=0;
	if(opt==1)//get serial
	{
		sprintf(read_model_path,"udevinfo -a -p /sys/block/%s/ | grep ATTRS{serial}==",argv);
		fp=popen(read_model_path,"r");
		fread(read_in_buf,100,1,fp);
		fclose(fp);
		
		//printf("====marco in %s read_in_buf %s===\n",__FUNCTION__,read_in_buf);
		tmp=strstr(read_in_buf,"ATTRS{serial}==");
		if(tmp!=NULL)
		{
			tmp+=strlen("ATTRS{serial}==")+1;		
			tmp1=strstr(tmp,"\"");
			if(tmp1!=NULL)
				*(char *)tmp1=NULL;	
			printf("====tmp %s\n",tmp);	
			tmp+=strlen(tmp)-8;	//we use the last 8 digit only
			strcpy(buf,tmp);
			return 1;
		}	
		else
		{
			strcpy(buf,"no_serial");
			//buf=NULL;	
			return 0;
		}
	}
	else//get model
	{

		sprintf(read_model_path,"udevinfo -a -p /sys/block/%s/ | grep ATTRS{model}==",argv);
TRY_AGAIN:		
		fp=popen(read_model_path,"r");
		fread(read_in_buf,100,1,fp);
		fclose(fp);	
		tmp=strstr(read_in_buf,"ATTRS{model}==");	
		if(tmp!=NULL)
		{
			tmp+=strlen("ATTRS{model}==")+1;
			strcpy(buf,tmp);

			return 1;
		}	
		else
		{
			if(try_again<5)
			{
				try_again++;
				sleep(1);//marco ,wait for sysfs ready
				goto TRY_AGAIN;
			}
			else
			{
				strcpy(buf,"non_brand");
				return 0;	
			}
		}	
	}

}
#endif
void main(int argc, char *argv[])//mnt_dev and write the mount table to /tmp/mnt_table finally
{
	char source[30];
	char target[256];
	char command[100];
	int is_sata_hd = 0;
	
	key_t sem_key;
//	int i=0;
//	FILE *fp=fopen("/var/test.log","w");
//	fprintf(fp,"argc %d\n",argc);
//	for(i=1;i<argc;i++)
//	{
//		fprintf(fp,"%s\n",argv[i]);
//	}
//	fclose(fp);
//	return;
//	if(argc!=3)
//	{
//		printf("Please use %s in this format %s dev_name HD_or_usb\n",argv[0],argv[0]);
////		return;
//	}
	//if it has partition and it is sata hd, do not mount it
	//we check the 4 char of the dev name 
	//ex. if it is sda1 and argv[2]!=1(HARDISK)
	//we will return
	is_sata_hd = is_sata();
	if(argv[1][3]!=NULL && is_sata_hd )
	{
		return;
	}
	sem_key = ftok(GET_KEY_FILE, 21);
	g_sem_id = semget(sem_key, 1, IPC_EXCL |IPC_CREAT); //checck sem. is exist or not
    if(g_sem_id < 0)//it exists
   	{
   		printf("sem exists \n");
   		g_sem_id = semget(sem_key, 1, 0666 |IPC_CREAT); //checck sem. is exist or not
   		if(g_sem_id < 0)//it exists
     	{
     		fprintf(stderr, "Program sema cannot find semaphore, exiting.\n");
      		exit(0);
      	}
   	}
   	else
   	{
   		if (semctl(g_sem_id, 0, SETVAL, 1) == -1)
		{
			printf("error 2");
			return;
		}	
	}
	sem_wait(g_sem_id);
	sprintf(source,"/dev/%s",argv[1]);
#if 0	
	p_tmp=strstr(argv[3]," ");
	
	if(p_tmp!=NULL)
		*(char *)p_tmp='_';	
	
	if( strcmp(argv[2],"1")==0 )
	{
		printf("USB FLASH DRIVE \n");
		sprintf(target,"/tmp/storage_dev/USB_%s",argv[3]);
	}
	else
	{
		printf("SATA HD \n");
		sprintf(target,"/tmp/storage_dev/HD_%s",argv[3]);
	}
#else
	//char model_buf[100],serial_buf[100],parent_dev[5];;
	char naming[200];
	char *serial=NULL;
	char *last_char=NULL;
	memset(naming,0x0,200);
	int y=0;
	int ret=0,hv_partition=0;;
	//if USB device has partition, we get info. from it's parent device		
	if( strcmp(argv[2],"1")==0 && argv[1][3]!=NULL)
	{
		hv_partition=1;
		//snprintf(parent_dev,4,"%s",argv[1]);
		for(y=3;y<argc;y++)
		{
			serial=strstr(argv[y],"-->");
			if(serial==NULL)
			{
				strcat(naming,"_");
				strcat(naming,argv[y]);
			}
			else//we hv serial
			{
				strcat(naming,"_");
				strncat(naming,argv[y],serial-argv[y]);//copy model no.
				serial+=3;
				if( isalnum(serial[0]) )
				{
					strcat(naming,"_");
					if(strlen(serial)>7)//we only need first 7 char of the seiral no.
					{
						last_char=serial+strlen(serial)-7;
						strncat(naming,last_char,7);
						//strncat(naming,serial,7);
					}
					else
						strcat(naming,serial);
				}
				
			}			
		}
//		if(get_attr_by_popen(model_buf,0,parent_dev))//get model
//			handle_str(model_buf);
//		
//		if(ret=get_attr_by_popen(serial_buf,1,parent_dev))//get serial
//			handle_str(serial_buf);				
	}
	else
	{	if(argv[1][3]!=NULL)
			hv_partition=1;
		for(y=3;y<argc;y++)
		{
			serial=strstr(argv[y],"-->");
			if(serial==NULL)
			{
				strcat(naming,"_");
				strcat(naming,argv[y]);
			}
			else//we hv serial
			{
				strcat(naming,"_");
				strncat(naming,argv[y],serial-argv[y]);//copy model no.
				serial+=3;
				if( isalnum(serial[0]) )
				{
					strcat(naming,"_");
					if(strlen(serial)>7)//we only need first 7 char of the seiral no.
					{
						last_char=serial+strlen(serial)-7;
						strncat(naming,last_char,7);
						//strncat(naming,serial,7);
					}
					else
						strcat(naming,serial);
				}
			}		
		}
		//use popen to get model and serial from udevinfo
//		if(get_attr_by_popen(model_buf,0,argv[1]))//get model
//			handle_str(model_buf);
//	
//		if(ret=get_attr_by_popen(serial_buf,1,argv[1]))//get serial
//			handle_str(serial_buf);				
	}
	
	//if( strcmp(argv[2],"1")==0 )
	if( !is_sata_hd )
	{
		printf("USB FLASH DRIVE \n");
		if(ret==1)//hv serial
		{
			if(hv_partition)//if hv partition, add the partition no. to the mount path
				//sprintf(target,"/tmp/storage_dev/USB_%s_%s_%c",model_buf,serial_buf,argv[1][3]);
				sprintf(target,"/tmp/storage_dev/USB%s_%c",naming,argv[1][3]);
			else
				sprintf(target,"/tmp/storage_dev/USB%s",naming);
		}
		else
		{
			if(hv_partition)
				sprintf(target,"/tmp/storage_dev/USB%s_%c",naming,argv[1][3]);
			else
				sprintf(target,"/tmp/storage_dev/USB%s",naming);			
		}
	}
	else
	{
		printf("SATA HD \n");
		if(ret==1)//hv serial
			sprintf(target,"/tmp/storage_dev/HD%s",naming);
		else
		sprintf(target,"/tmp/storage_dev/HD%s",naming);
	}
	
	
#endif	
	//sprintf(command,"/bin/mkdir -p %s",target);
	//system(command);
	mkdir(target,777);
	//make a symlink to the mount point to see it is sata device or usb device
	/*hendry modify, differentiate between usb and sata_hd*/
	//is_sata_hd = is_sata();
	printf("is_sata : %d,source : %s %s\n",is_sata_hd,source,argv[1]);
	if(mount_dev(source,target,is_sata_hd))
	{
		export_to_file(argv[1],"/tmp/mount_table","a+");
		export_to_file(target,"/tmp/mount_table","a+");
		
		/* send signal to lcd to inform mount is success */
		if(is_sata_hd)
		{
			/*we don't need to check if hd is plugged from beginning. 
			Always send the KEY_I to lcd program. If hd is plugged from beginning, lcd program 
			won't arise yet and no one will receive the key .*/
			press_button(KEY_I);
		}
		else
		{
			//inform USBa or USBb to the panel
			inform_panel(argv[1]);			
		}
		
		/* hendry modify : change permissions after mount */
		sprintf(command,"/bin/chmod 777 %s",target);
		system(command);
		/*
		Warning !!!: do not change below string if mount success. 
		Format program use below string to check whether format success or not 	
		*/
		printf("Mount success : %s to %s\n",source,target);		
		//+++joel add wcn 1.0 the path is hard code in wcnufd
		export_to_file(target,"/var/run/diskup","w+");
		system("wcnufd");
		unlink("/var/run/diskup");
		//---
	}
	else//mount fail with our support fs
	{
		if(is_sata_hd)
		{
			//inform re-format is needed
			printf("Sending F key..\n");
			press_button(KEY_F);
		}
		else
		{
			/* +++ Teresa Ke, copy from mount_USB func. */
			press_button(KEY_E);	
		}
		
		sprintf(command,"/bin/rm -r %s",target);
		system(command);
		/*
		Warning !!!: do not change below string if mount fails. 
		Format program use below string to check whether format success or not 
		*/
		printf("\nMount failed, %s to %s\n",source,target);	
	}
	
	sem_signal(g_sem_id);
}
