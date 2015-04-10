#include <stdio.h>
#include <stdlib.h>
#include <sys/mount.h>
#include "mnt.h"

/*
Input:kernel name 
finally umount it and remove the directory
*/

#define DEBUG_MODE 1

#if DEBUG_MODE
#define DPRINTF printf
#else
#define DPRINTF
#endif
int export_to_file(char *tmp_buff)
{
	FILE *fp=NULL;
	fp=fopen("/tmp/mount_table","w");
	if(fp==NULL)
		return 0;
	fprintf(fp,"%s",tmp_buff);	
	fclose(fp);	
	return 1;
}

static int import_from_file(char *filename, char *p_buffer, int buf_len)
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

void dumpmem(char *str , long size)
{
	int i = 0;
	for (i=0; i<size; i++)
	{
		printf("[%d] %c : %d\n",i, str[i], str[i]);	
	}
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
void main(int argc, char *argv[])
{
	FILE *fp=NULL;
	char read_in_buff[100];
	char link_path[100];
	char *tmp_buff=NULL;
	char command[200];
	char buf[256];
	char devname[256];
	memset(devname,0x00, sizeof(devname));
	strcpy(devname, argv[1]);
	printf("==== read_in_buff %d \n",__LINE__);

	//tmp_buff read all the data from the file except the one that we umount and  then store back to file
	tmp_buff=malloc(1024);
	fp=fopen("/tmp/mount_table","r");
	
//	printf("==== read_in_buff %d \n",__LINE__);	
	while(!feof(fp))//use looping to check input kernel name is mounted or not
	{
		fscanf(fp,"%s\n",&read_in_buff);
//		printf("==== read_in_buff %s \n",read_in_buff);
		if(strncmp(argv[1],read_in_buff,strlen(argv[1]))==0)//match,get the kernel name and link_path from file
		{
			fscanf(fp,"%s\n",&link_path);
//			printf("==== link_path %s \n",link_path);
		}
		else//not match, skip one line and continue
		{
			sprintf(tmp_buff,"%s%s\n",tmp_buff,read_in_buff);
			fscanf(fp,"%s\n",&read_in_buff);
			sprintf(tmp_buff,"%s%s\n",tmp_buff,read_in_buff);			
		}
	}
	fclose(fp);		
	

	if(umount(link_path)<0)
	{	//umount fail
		printf("Umount failed \n");
		return;
	}
	else
	{
		
		export_to_file(tmp_buff);
		sprintf(command,"/bin/rm -r %s",link_path);
		system(command);
		reload_smbd_if_open_mode();			

		/*hendry : for USB*/
		if(import_from_file(USB1_DETECT_FILE, buf, sizeof(buf))!= -1)
		{	//export success
			int test  = 0 ;
			DPRINTF("Found USBa\n");
			if( (test=strncmp(buf,devname ,strlen(devname)))==0)
			{
				unlink(USB1_DETECT_FILE);
				DPRINTF("Deleting USBa\n");
				//send key C to inform panel USBa is unplugged
				system("ssignal 46 &");
				return;
			}
			
			#if DEBUG_MODE
			printf("buf : %s\n", buf);
			dumpmem(buf, 10);
			printf("devname : %s\n", devname);
			dumpmem(devname, 10);
			printf("test is : %d\n", test);
			#endif
		}
		
		if(import_from_file(USB2_DETECT_FILE, buf, sizeof(buf))!= -1)
		{	//export success
			int test = 0;
			DPRINTF("Found USBb\n");
			if( (test = strncmp(buf,devname ,strlen(devname)))==0)
			{
				unlink(USB2_DETECT_FILE);
				DPRINTF("Found, deleting USBb\n");
				//send key D to inform panel USBb is unplugged
				system("ssignal 32 &");
				return;
			}
			#if DEBUG_MODE
			printf("buf : %s\n", buf);
			dumpmem(buf, 10);
			printf("devname : %s\n", devname);
			dumpmem(devname, 10);
			printf("test is : %d\n", test);
			#endif
		}
		
	}
}

