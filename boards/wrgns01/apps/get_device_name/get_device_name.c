#include<stdio.h>
//this app is used to get the folder(device) under /tmp/storage_dev
//we get the name and the save it to /nas/network_access_open_mode/share_path:x/path
//it is for samba used
void main()
{
	char device_name[256];
	char command[512];
	int i=1;
	FILE *fp=popen("ls /tmp/storage_dev/","r");
	if(fp==NULL)
	{
		printf("Open file failed \n");
		return;
	}	
	while( !feof(fp))
	{
		fscanf(fp,"%s\n",device_name);
		if( (strncmp(device_name,"HD",2)!=0)&&(strncmp(device_name,"USB",2)!=0) )
		{	
			strcpy(device_name," ");
		}
		sprintf(command,"rgdb -s /nas/network_access_open_mode/share_path:%d/path \"%s\"",i,device_name);
		system(command);
		i++;
		
	}
	fclose(fp);
	sprintf(command,"rgdb -d /nas/network_access_open_mode/share_path:%d",i);
	system(command);
}
