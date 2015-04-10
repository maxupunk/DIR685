#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "config.h"

smart_attr smart_data;
int health_check = 0;
char hd_name[100];

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

void convert_byte_to_gbyte(char *p_value)
{
	/*p_value example : "200,049,674,000 bytes"
	  we change it to : "200.049"
	*/
	int tmp = find_chr(p_value,' ');	//to omit bytes
	if(tmp == 0 ) {printf("Error with capacity value\n");return;}
	if(tmp < 11) {printf("capacity value doesn't reach Gbytes\n");p_value[0]=0;return;}
	
	p_value[tmp-12] = 0;	//we omit the ",049,674,000" and the "bytes".(don't take decimal)
	//p_value[tmp-8-4] = '.';	//we change the ',' to '.'
	
	strcat(p_value, " GB");
}

int export_from_file(char *filename, char *p_buffer, int buf_len)
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

int device_is_up()
{
	if(export_from_file("/var/hd_status", g_content_file_buf, CONTENT_FILE_SIZE_D)==-1)
		printf("Can't get content from %s\n","/var/hd_status");	
		
	if(strstr(g_content_file_buf, "active") == NULL)
		return 0;
	else
		return 1;
}

int smart_is_enabled(char *src_info)
{
	if(export_from_file(src_info, g_content_file_buf, CONTENT_FILE_SIZE_D)==-1)
		printf("Can't get content from %s\n",src_info);	
		
	if(strstr(g_content_file_buf, "SMART Enabled") == NULL)
		return 0;
	else
		return 1;
}

void reverse_size(char *size_str)
{
	int int_value = 0;
	int_value = strtol(size_str, NULL, 10);	
	
	DEBUG_PRINTF("int_value : %d, size_str is : %s ,", int_value,size_str);
	if(strstr(size_str,"G")!=0)
	{
		int_value = int_value * (107374) / 100000;
		sprintf(size_str, "%d GB",int_value);
	}
	else if(strstr(size_str,"M")!=0)
	{
		int_value = int_value * (104857) / 100000;
		sprintf(size_str, "%d MB",int_value);
	}
	else if(strstr(size_str,"K")!=0)
	{
		int_value = int_value * (1024) / 1000;
		sprintf(size_str, "%d KB",int_value);
	}
	DEBUG_PRINTF("%s \n",size_str);
}

void parse_disk_space_info(char *line)
{
	/*
	printf("Line is : %s\n", line);
	"/dev/sda             195360980    794568 194566412   0% /var/tmp/storage_dev/sda"
	*/
	int i = 0;
	char capacity[20];
	char available[20];
	char used[20];
	char perc_used[10];
	
	memset(capacity, 0x00, 20);
	memset(available, 0x00, 20);
	memset(used, 0x00, 20);
	
	if(sscanf(line, "%*s %s %s %s %s %*s",capacity,used,available,perc_used)!=4)
	{
		printf("scan fail %s\n",line);	
		return ;
	}
	
	#if 1
	/*
	the values retrieved is in humand mode read, which total size are divided by 1024s.
	This will make hd looks smaller. We prefer to use 1000 as dividers, instead 1024. So we 
	reverse the values retrieved. 
	Ex : total size = 315050377216
		 human read mode (divided by 1024) = 315050377216 / 1024^3 = 293.4G (this is what we get from df)
		 to reverse back 293.4 * 1.07374 = 315 GB 
		 
		 if we get Gb as unit from df, we reverse by multiplying 1.07374.
		 if we get Mb as unit from df, we reverse by multiplying 1.04857.
		 if we get Kb as unit from df, we reverse by multiplying 1.024.
	*/
	
	/*we use "smartctl -i" to retrieve total capacity.Bcoz df only show capacity after excluded 
	by inodes capacity. Ex : total 320GB, df only show 315GB since 5GB is reserved for inodes. */
	//reverse_size(capacity); 
	reverse_size(used);
	reverse_size(available);
	#else
	if(find_chr(capacity,'B')==0)
		strcat(capacity,"B");
	if(find_chr(used,'B')==0)
		strcat(used,"B");
	if(find_chr(available,'B')==0)
		strcat(available,"B");
	#endif
	
	//DEBUG_PRINTF("[update_disk_usage] capacity is : %s\n", capacity);
	DEBUG_PRINTF("[update_disk_usage] used is : %s\n", used);
	DEBUG_PRINTF("[update_disk_usage] available is : %s\n", available);
	DEBUG_PRINTF("[update_disk_usage] perc_used is : %s\n", perc_used);
	
	//xmldbc_set(NULL, 0, XML_STORE_CAPCITY_NODE, capacity);
	xmldbc_set(NULL, 0, XML_STORE_USED_NODE, used);
	xmldbc_set(NULL, 0, XML_STORE_AVAILABLE_NODE, available);
	xmldbc_set(NULL, 0, XML_STORE_USED_PERCENTAGE_NODE, perc_used);
}

void parse_general_info(char *line)
{
	int i =0;
	int attr_len = 0;	
	Data_general data;
	
	if(line[0] == 0x0a || line[0] == 0x0d)
		return;
	
	/*get field */
	attr_len = find_chr(line,':');
	line[attr_len] = 0;
	data.field = line;
	
	/*get value */
	line = line+attr_len+1;
	while(line[0] == ' ')
		line++;
	data.value = line;
	attr_len = find_chr(data.value,0x0a);
	data.value[attr_len] = 0;
	
	if(strcmp(data.field, "Device Model") == 0 ) 
	{
		xmldbc_set(NULL, 0, XML_STORE_HD_NAME_NODE, data.value);
		memset(hd_name, 0x0, 100);
		strcpy(hd_name, data.value);
		//printf("data->field : %s\n", data.field);
		//printf(" data->value : %s\n", data.value);	
	}
	else if(strcmp(data.field, "User Capacity") == 0 )
	{
		// convert units from bytes into Gbytes
		convert_byte_to_gbyte(data.value);
		xmldbc_set(NULL, 0, XML_STORE_CAPCITY_NODE, data.value);
	}
}

void parse_health_info(char *line)
{
	int attr_len = 0 ;
	char *health_status = 0;
	
	if(line[0] == 0x0a || line[0] == 0x0d)
		return;
	
	if(strstr(line, "SMART overall-health self-assessment")== NULL)
		return;
	
	attr_len = find_chr(line,':');
	health_status = line+attr_len+1;	//skip the ':' 
	while(health_status[0] == ' ')
		health_status++;
	attr_len = find_chr(health_status,0x0a);
	health_status[attr_len] = 0;
	
	if(strcmp(health_status, "PASSED")==0)
	{
		xmldbc_set(NULL, 0, XML_STORE_HD_HEALTH_CHECK_SMRTCTL, "1");
		health_check = 1;
	}
	else
	{
		xmldbc_set(NULL, 0, XML_STORE_HD_HEALTH_CHECK_SMRTCTL, "0");
		health_check = -1;
	}
}

void parse_attribute_info(char *line)
{
	//Data_attributes attr;
	int id;
	char attr_name[50];
	int flag;
	int value;
	int worst;
	int thresh;
	char type[20];					//1 is Pre-fail, 2 is Old_age 
	char updated[20];				//1 is Always, 2 is Offline	
	char when_failed[20];			//1 is '-'
	char raw_value[20];
	
	if(line[0] == 0x0a || line[0] == 0x0d)
		return;
	
	//   1 Raw_Read_Error_Rate     0x000b   100   100   062    Pre-fail  Always       -       0
	sscanf(line,"%d%s%X%d%d%d%s%s%s%s\n", &id,attr_name,&flag,&value,&worst,&thresh,type,updated,when_failed,raw_value);
	/*
	printf("id              : %d\n", id);
	printf("attr_name       : %s\n", attr_name);
	printf("flag            : 0x%.4X\n", flag);
	printf("value           : %d\n", value);
	printf("worst           : %d\n", worst);
	printf("thresh          : %d\n", thresh);
	printf("type            : %s\n", type);
	printf("updated         : %s\n", updated);
	printf("when_failed     : %s\n", when_failed);
	printf("raw_value       : %s\n\n", raw_value);
	*/
	
	/*+++ hendry*/
	switch(id)
	{
		case ATTR_ID_Temperature_Celcius :
			{
				int fahr_val = 0;
				char tmp_fahr_buf[10];
				xmldbc_set(NULL, 0, XML_STORE_HD_TEMP_CELCIUS_NODE,raw_value);
				//also provide Fahrenheit degree
				fahr_val = (atoi(raw_value)*9/5)+32;
				sprintf(tmp_fahr_buf, "%d",fahr_val);
				xmldbc_set(NULL, 0, XML_STORE_HD_TEMP_FAHRENHEIT_NODE,tmp_fahr_buf);
				//printf("Temperature_Celsius is : %d\n", atoi(raw_value));
				//printf("Fahrenheit_Celsius is : %d\n", fahr_val);
			}
			break;
		
		case ATTR_ID_Reallocated_Sectors_Count :
				smart_data.val_Reallocated_Sectors_Count = strtoul(raw_value,0,16);
			break;
		case ATTR_ID_Seek_Error_Rate :
				smart_data.val_Seek_Error_Rate = strtoul(raw_value,0,16);
			break;
		case ATTR_ID_Spin_Retry_Count :
				smart_data.val_Spin_Retry_Count = strtoul(raw_value,0,16);
			break;
		case ATTR_ID_Reallocation_Event_Count :
				smart_data.val_Reallocation_Event_Count = strtoul(raw_value,0,16);
			break;
		case ATTR_ID_Current_Pending_Sector_Count :
				smart_data.val_Current_Pending_Sector_Count = strtoul(raw_value,0,16);
			break;
		case ATTR_ID_Uncorrectable_Sector_Count :
				smart_data.val_Uncorrectable_Sector_Count = strtoul(raw_value,0,16);
			break;
	}
}


void parse_line(char *line, int mode)
{
	switch(mode)
	{
		case 1 :
			DEBUG_PRINTF("General info : %s\n", line);
			parse_general_info(line);
			break;
		
		case 2 : 
			DEBUG_PRINTF("Health info : %s\n", line); 
			parse_health_info(line);
			break;
			
		case 3 : 
			DEBUG_PRINTF("Attribute info : %s\n", line); 
			parse_attribute_info(line);
			break;
		
		default :
		break;
	}	
}

int parse_disk_usage_info(char *devname, char *filename)
{
    int mode =0;
    
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen(filename, "r");
    if (fp == NULL)
   		return -1;
   	
    while ((read = getline(&line, &len, fp)) != -1) 
    {
		if(strncmp(line, "Filesystem", strlen("Filesystem"))==0)
			continue;
			
		if(strstr(line, devname))
		{
			parse_disk_space_info(line);
		}
    }
    
    if (line)
		free(line);
    
    return 0;
}

int parse_smart_info(char *filename)
{
    int mode =0;
    
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen(filename, "r");
    if (fp == NULL)
   		return -1;
   	
    while ((read = getline(&line, &len, fp)) != -1) 
    {
		if(strncmp(line, "=== START OF INFORMATION SECTION ===", strlen("=== START OF INFORMATION SECTION ==="))==0)
		{
			read = getline(&line, &len, fp);	//skip the title
			mode = 1; //parse general info 
		}
		else if (strncmp(line, "=== START OF READ SMART DATA SECTION ===", strlen("=== START OF READ SMART DATA SECTION ==="))==0)
		{
			read = getline(&line, &len, fp);	//skip the title
			mode = 2; //parse health info	
		}
		else if (strncmp(line, "ID# ATTRIBUTE_NAME", strlen("ID# ATTRIBUTE_NAME"))==0)
		{
			read = getline(&line, &len, fp);	//skip the title
			mode = 3; //parse attributes value	
		}
		parse_line(line, mode);	
    }
    
    if (line)
		free(line);
    
    return 0;
}

void update_disk_usage(char *devname)
{
	int total_read = 0;
	sprintf(g_cmd_buf, "%s %s -h > %s", DF_PATH_D, devname, DUMP_OUTPUT_D);
	system(g_cmd_buf);
	parse_disk_usage_info(devname,DUMP_OUTPUT_D);
}

void update_fs(char *diskname)
{	
	int total_read = 0;
	int tmp = 0;
	char content_buf[10];	//size 4 is actually enough to store fs name
	char node_buf[200];
	
	char file[128];
	memset(content_buf, 0x00, 10);
	
	strcpy(file,"/var/fs_");
	strcat(file,diskname);
	
	if(export_from_file(file, content_buf, 10)==-1)
		printf("Can't get file system from %s\n", file);
	
	if( (tmp = find_chr(content_buf,0x0a)))
		content_buf[tmp] = 0;
	
	xmldbc_set(NULL, 0, XML_STORE_HD_FILESYSTEM_NODE, content_buf);
}

void update_smart_info(char *devname)
{
	/*moved to script. This code will cause ata1: timeout problem.*/
	/*
	unlink(DUMP_OUTPUT_D);
	// turn on SMART on disk
	sprintf(g_cmd_buf, "%s -s on %s > %s",SMARTCTL_PATH_D ,devname, DUMP_OUTPUT_D);
	system(g_cmd_buf);
	if(!smart_is_enabled(DUMP_OUTPUT_D))
	{
		printf("SMART can't be enabled ..\n");	
		return;
	}
	*/
	
	/* update smart values */
	sprintf(g_cmd_buf, "%s -iHA %s > %s",SMARTCTL_PATH_D ,devname, DUMP_OUTPUT_SMART);
	system(g_cmd_buf);
	
	parse_smart_info(DUMP_OUTPUT_SMART);	
}

void update_health()
{
	/*
	based on hdsentinel calculation
	S.M.A.R.T. attribute						Weight	Limit% 
	[5] Reallocated sectors count				1		70 
	[7] Seek error rate							0.5		20 
	[10] Spin retry count						3		60 
	[196] Reallocation event count				0.6		30 
	[197] Current pending sectors count			0.6		48 
	[198] Off line uncorrectable sectors count	1		70 
	*/
	
	char buf[10];
	int overall_health = 100;
	int decrease_val = 0;
	/*
	printf("val_Reallocated_Sectors_Count	: %d\n", smart_data.val_Reallocated_Sectors_Count);
	printf("val_Seek_Error_Rate		 		: %d\n", smart_data.val_Seek_Error_Rate);
	printf("val_Spin_Retry_Count 			: %d\n", smart_data.val_Spin_Retry_Count);
	printf("val_Reallocation_Event_Count	: %d\n", smart_data.val_Reallocation_Event_Count);
	printf("val_Current_Pending_Sector_Count: %d\n", smart_data.val_Current_Pending_Sector_Count);
	printf("val_Uncorrectable_Sector_Count	: %d\n", smart_data.val_Uncorrectable_Sector_Count);
	*/
	decrease_val = smart_data.val_Reallocated_Sectors_Count*1; 
	decrease_val = (decrease_val > 70) ? 70 : decrease_val;
	overall_health -= decrease_val;
	DEBUG_PRINTF("[disk health] att \"Reallocated sectors count\t\" : decrease %d\n",decrease_val);
	
	/*NOTe : for seagate harddisk, we exclude the seek error rate[7] into calculation, since
		this attribute is proprietory for seagate */
	if(strncmp(hd_name, "ST", 2)==0)	//seagate hd begins with ST
	{
		decrease_val = 0;
	} else
	{
		decrease_val = smart_data.val_Seek_Error_Rate*1/2; 
		decrease_val = (decrease_val > 20) ? 20 : decrease_val;			
	}
	overall_health -= decrease_val;
	DEBUG_PRINTF("[disk health] att \"Seek error rate\t\" : decrease %d\n",decrease_val);
	
	decrease_val = smart_data.val_Spin_Retry_Count*3; 
	decrease_val = (decrease_val > 60) ? 60 : decrease_val;
	overall_health -= decrease_val;
	DEBUG_PRINTF("[disk health] att \"Spin retry count\t\" : decrease %d\n",decrease_val);
	
	decrease_val = smart_data.val_Reallocation_Event_Count*3/5; 
	decrease_val = (decrease_val > 30) ? 30 : decrease_val;
	overall_health -= decrease_val;	
	DEBUG_PRINTF("[disk health] att \"Reallocation event count\t\" : decrease %d\n",decrease_val);

	decrease_val = smart_data.val_Current_Pending_Sector_Count*3/5; 
	decrease_val = (decrease_val > 48) ? 48 : decrease_val;
	overall_health -= decrease_val;	
	DEBUG_PRINTF("[disk health] att \"Current pending sectors count\t\" : decrease %d\n",decrease_val);
	
	decrease_val = smart_data.val_Uncorrectable_Sector_Count*1; 
	decrease_val = (decrease_val > 70) ? 70 : decrease_val;
	overall_health -= decrease_val;
	DEBUG_PRINTF("[disk health] att \"Off line uncorrectable sectors count\t\" : decrease %d\n",decrease_val);
	

	
	if(overall_health < 0)
	{
		overall_health = 0;
		printf("warning, health is below 0%\n");
		//TODO : give alert key to panel
	}else
		printf("overall_health is %d\n",overall_health);
	
	if(overall_health > 80 && overall_health <= 100)
	{
		sprintf(buf, "%s","Very good");
	} else if (overall_health > 60 && overall_health <= 80)
	{
		sprintf(buf, "%s","Good");
	} else if (overall_health > 40 && overall_health <= 60)
	{
		sprintf(buf, "%s","Not So Good");
	} else if (overall_health > 20 && overall_health <= 40)
	{
		sprintf(buf, "%s","Poor");
	} else if (overall_health >= 0 && overall_health <= 20)
	{
		sprintf(buf, "%s","Very Poor");	
	}
	
	if(health_check==-1) //we also check "health self assesment" which is done by smartctl, whether passed or not
	{
		xmldbc_set(NULL, 0, XML_STORE_HD_HEALTH_NODE, "Very Poor!! Replace in 24h");
	}else
		xmldbc_set(NULL, 0, XML_STORE_HD_HEALTH_NODE, buf);			
}

void test_db_vals()
{
	char tmp_buf[200];
	xmldbc_get_wb(NULL, 0, XML_STORE_HD_NAME_NODE, tmp_buf, 200);
	printf("/runtime/nas/store_dev/name is : %s\n", tmp_buf);

	xmldbc_get_wb(NULL, 0, XML_STORE_HD_FILESYSTEM_NODE, tmp_buf, 200);
	printf("/runtime/nas/store_dev/fsname is : %s\n", tmp_buf);

	xmldbc_get_wb(NULL, 0, XML_STORE_HD_TEMP_CELCIUS_NODE, tmp_buf, 200);
	printf("/runtime/nas/store_dev/temp/celsius is : %s\n", tmp_buf);

	xmldbc_get_wb(NULL, 0, XML_STORE_HD_TEMP_FAHRENHEIT_NODE, tmp_buf, 200);
	printf("/runtime/nas/store_dev/temp/fahrenheit is : %s\n", tmp_buf);
	
	xmldbc_get_wb(NULL, 0, XML_STORE_HD_HEALTH_NODE, tmp_buf, 200);
	printf("/runtime/nas/store_dev/health is : %s\n", tmp_buf);		
	
	xmldbc_get_wb(NULL, 0, XML_STORE_CAPCITY_NODE, tmp_buf, 200);
	printf("/runtime/nas/store_dev/capacity is : %s\n", tmp_buf);
	
	xmldbc_get_wb(NULL, 0, XML_STORE_AVAILABLE_NODE, tmp_buf, 200);
	printf("/runtime/nas/store_dev/available is : %s\n", tmp_buf);
	
	xmldbc_get_wb(NULL, 0, XML_STORE_USED_NODE, tmp_buf, 200);
	printf("/runtime/nas/store_dev/used is : %s\n", tmp_buf);
}

void clear_db()
{
	xmldbc_del(NULL, 0, XML_STORE_CAPCITY_NODE);
	xmldbc_del(NULL, 0, XML_STORE_USED_NODE);
	xmldbc_del(NULL, 0, XML_STORE_AVAILABLE_NODE);
	xmldbc_del(NULL, 0, XML_STORE_HD_NAME_NODE);
	xmldbc_del(NULL, 0, XML_STORE_HD_HEALTH_NODE);
	xmldbc_del(NULL, 0, XML_STORE_HD_HEALTH_CHECK_SMRTCTL);
	xmldbc_del(NULL, 0, XML_STORE_HD_TEMP_CELCIUS_NODE);
	xmldbc_del(NULL, 0, XML_STORE_HD_TEMP_FAHRENHEIT_NODE);
	xmldbc_del(NULL, 0, XML_STORE_HD_FILESYSTEM_NODE);
}


void unlock(int flock)
{
	if(flock>=0)
	{
		lockf(flock, F_UNLCK, 0);
		close(flock);
	}
}

int lock(char *lockfile)
{
	/* create a lock file, and lock the file */
	int flock;
	if((flock=open(lockfile, O_CREAT | O_WRONLY, 0644))<0)
		{ printf("Unable to open lock %s: %s!!\n",lockfile); }
	else
		{ lockf(flock, F_LOCK, 0); }

	return flock;
}


static int is_exist(char *filename)
{
	if(access(filename, F_OK)==0)
		return 1;
	else
		return 0;
}

static int proceed_to_work(char *lockfile)
{
	/* 1. check if another smartmon is running 
	   2. if already run, then wait for first process to finish, and return without doing nothing 
	   3. if not yet run, then this process become first process, and proceed as usual. 
	*/
	   
	DEBUG_PRINTF("##### smartmon %d start \n", getpid());
	
	if(is_exist(lockfile))
	{
		/* other then first process reach here */
		int flock = open(lockfile, O_WRONLY, 0644);
		if(flock < 0)
		{
			printf("Error : can't open existing lock_file, process %d terminate \n\n", getpid());
			return 0;	
		}
		
		/* wait first process to release lock, and then this process return directly */
		lockf(flock, F_LOCK, 0);
		unlock(flock);
		DEBUG_PRINTF("##### smartmon %d terminate \n\n", getpid());
		return 0;
	}
	DEBUG_PRINTF("##### smartmon %d BECOME FIRST PROCESS \n", getpid());
	return 1;	
}

void do_get_temp(char *devname)
{
	int junk = 0;
	char junk_char[40];
	char raw_value[20];
	
    FILE * fp;
    size_t len = 0;

    sprintf(g_cmd_buf, "%s -A %s | grep 194 > %s" , SMARTCTL_PATH_D , devname, DUMP_OUTPUT_TEMP);
	system(g_cmd_buf);
	
	fp = fopen(DUMP_OUTPUT_TEMP, "r");
    if (fp == NULL)
   		return -1;
	
    if(export_from_file(DUMP_OUTPUT_TEMP, g_content_file_buf, CONTENT_FILE_SIZE_D)!=-1)
    {
    	//   194 Temperature_Celsius     0x000b   100   100   062    Pre-fail  Always       -       0
		sscanf(g_content_file_buf,"%d%s%X%d%d%d%s%s%s%s\n", &junk,junk_char,&junk,&junk,&junk,&junk,junk_char,junk_char,junk_char,raw_value);
		//printf("temp is %d\n", atoi(raw_value));
		xmldbc_set(NULL, 0, XML_STORE_HD_TEMP_CELCIUS_NODE, raw_value);
    }
    else
    	printf("Can't get hd_temp\n");
    	
    DEBUG_PRINTF("**** get hd temp success\n");
}

void do_smartmon(int argc, char *argv[])
{
	char *p_diskname;
	char *devname;					//Device name for the disk.
	
	/*clear all xmldb data*/
	if(strcmp(argv[1],"-F")==0)
	{
		clear_db();
		//test_db_vals();
		return;
	}
			
	devname = argv[1];
	
	/* update disk information, health and attributes (using smartctl pgrm) */
	update_smart_info(devname);
	
	//test only
	//parse_smart_info("/var/hendry1");
	
	/* update health information, based on smart attributes values */
	update_health();
	
	/* update file system (format_type) */
	p_diskname = strrchr(argv[1], '/');
	if(p_diskname) p_diskname++; 	//skip the '/' by +1
	update_fs(p_diskname);
	
	/* update disk usage */
	update_disk_usage(devname);

	#ifdef DEBUG_MODE
	DEBUG_PRINTF("\n");
	test_db_vals();
	#endif
	
	printf("Update storage device info to xml ... success \n");
}

void do_get_temp_main(int argc, char *argv[])
{
	char *devname;					//Device name for the disk.
	int lock_id = 0;
	
	/* don't do if same process already exist */
	if(!proceed_to_work(LOCK_FILE2_TEMPERATURE))
		return 0;	
	
	/* first process */
	if((lock_id=lock(LOCK_FILE2_TEMPERATURE))>0)
	{
		devname = argv[2];
		do_get_temp(devname);

		unlock(lock_id);
		unlink(LOCK_FILE2_TEMPERATURE);
	}
	DEBUG_PRINTF("##### smartmon %d temp FIRST PROCESS terminate \n\n", getpid());
}

void do_smartmon_main(int argc, char *argv[])
{
	int lock_id = 0;
	/* don't do if same process already exist */
	if(!proceed_to_work(LOCK_FILE))
		return 0;	
	
	/* first process */
	if((lock_id=lock(LOCK_FILE))>0)
	{
		do_smartmon(argc, argv);

		unlock(lock_id);
		unlink(LOCK_FILE);
	}
	DEBUG_PRINTF("##### smartmon display %d FIRST PROCESS terminate \n\n", getpid());
}
	
void main(int argc, char *argv[])
{
	if(argc < 2 || (strcmp(argv[1],"-h")==0))
	{
		printf("Usage 1, update all info to db  -> smartmon [dev] \n");
		printf("Usage 2, update temp info to db -> smartmon -t [dev]\n");
		printf("Usage 3, clear all info from db -> smartmon -F \n");
		return;
	}
	
	/* update disk temperature only */
	if(strcmp(argv[1],"-t")==0)
	{
		do_get_temp_main(argc, argv);
		return;
	}
	
	do_smartmon_main(argc, argv);
	return ;	
}


