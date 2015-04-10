#include <signal.h>
#include <stdio.h>
#define SATA_STAT "/proc/sata_stat"
//check the sata status in every seconds
//if it is plug or unplug, send the signal to kernel
void sata_hotplug(char *port,int status)
{
	if(strcmp(port,"P0:")==0)//P0
	{
		if(status==1)
			system("echo \"scsi add-single-device 1 0 0 0\" > /proc/scsi/scsi");
		else if(status==0)
			system("echo \"scsi remove-single-device 1 0 0 0\" > /proc/scsi/scsi");
	}
	else//P1
	{
		if(status==1)
			system("echo \"scsi add-single-device 0 0 0 0\" > /proc/scsi/scsi");
		else if(status==0)
			system("echo \"scsi remove-single-device 0 0 0 0\" > /proc/scsi/scsi");
	}
}
void check_status()
{
	FILE *fp=NULL;
	char port[10];
	char kernel_name[10];
	char *tmp;
	int status;
	fp=fopen(SATA_STAT,"r");
    while(!feof(fp))
    {
       fscanf(fp,"%s %d %s\n",&port,&status,&kernel_name);
       //printf("&read_in_buff %s,&status %d,kernel_name %s \n",port,status,kernel_name);
       sata_hotplug(port,status);              
    }
	fclose(fp);
}
void main()
{
	check_status();							
	if( fork() == 0 )    //child
	{
		while( 1 )
		{			
			check_status();							
			sleep(1);
		}
	}
	else
	{
		if( signal( SIGINT, SIG_DFL ) != SIG_DFL )
			signal( SIGINT, SIG_DFL );
		if( signal( SIGKILL, SIG_DFL ) != SIG_DFL )
			signal( SIGKILL, SIG_DFL );
		exit( 0 );
	} /* End if( fork() ) 	*/
}