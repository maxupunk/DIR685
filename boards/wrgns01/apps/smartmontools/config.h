#ifndef SMART_MON_CONFIG_H
#define SMART_MON_CONFIG_H
 
//#define DEBUG_MODE

#ifdef DEBUG_MODE
#define DEBUG_PRINTF			printf
#else 
#define DEBUG_PRINTF			
#endif

#define PRE_FAIL			1
#define OLD_AGE				2
#define ALWAYS				1
#define OFFLINE				2

#define SMARTCTL_PATH_D			"smartctl"
#define DF_PATH_D				"df"

#define CONTENT_FILE_SIZE_D 	5000
#define CMD_BUF_SIZE_D 	  		1000
#define DUMP_OUTPUT_D			"/var/dump"
#define DUMP_OUTPUT_SMART		"/var/dump_smart"
#define DUMP_OUTPUT_TEMP		"/var/dump_temp"


#define XML_STORE_CAPCITY_NODE				"/runtime/nas/store_dev/capacity"
#define XML_STORE_USED_NODE					"/runtime/nas/store_dev/used"
#define XML_STORE_USED_PERCENTAGE_NODE		"/runtime/nas/store_dev/used_percent"
#define XML_STORE_AVAILABLE_NODE 			"/runtime/nas/store_dev/available"
#define XML_STORE_HD_NAME_NODE				"/runtime/nas/store_dev/name"
#define XML_STORE_HD_HEALTH_NODE			"/runtime/nas/store_dev/health"
#define XML_STORE_HD_HEALTH_CHECK_SMRTCTL	"/runtime/nas/store_dev/health_check"
#define XML_STORE_HD_TEMP_CELCIUS_NODE		"/runtime/nas/store_dev/temp/celsius"
#define XML_STORE_HD_TEMP_FAHRENHEIT_NODE 	"/runtime/nas/store_dev/temp/fahrenheit"
#define XML_STORE_HD_FILESYSTEM_NODE		"/runtime/nas/store_dev/fsname"

/*SMART ATTRIBUTES ID*/
#define ATTR_ID_Reallocated_Sectors_Count 		5
#define ATTR_ID_Seek_Error_Rate 				7
#define ATTR_ID_Spin_Retry_Count 				10
#define ATTR_ID_Temperature_Celcius				194
#define ATTR_ID_Reallocation_Event_Count 		196
#define ATTR_ID_Current_Pending_Sector_Count 	197
#define ATTR_ID_Uncorrectable_Sector_Count 		198

#define LOCK_FILE 				"/var/lock_smartmon.txt"
#define LOCK_FILE2_TEMPERATURE 	"/var/lock_smartmon_temperature.txt"

void unlock(int flock);
int lock(char *lockfile);
static int is_exist(char *filename);

char g_cmd_buf[CMD_BUF_SIZE_D];
char g_content_file_buf[CONTENT_FILE_SIZE_D];
int find_chr(char *tmp_buf, char chr);
int export_first_num_from_file(char *filename);
int export_from_file(char *filename, char *p_buffer, int buf_len);
int device_is_up();

typedef struct {
	char *field;
	char *value;
} Data_general;

typedef struct {
	unsigned long val_Reallocated_Sectors_Count;
	unsigned long val_Seek_Error_Rate;
	unsigned long val_Spin_Retry_Count;
	unsigned long val_Reallocation_Event_Count;
	unsigned long val_Current_Pending_Sector_Count;
	unsigned long val_Uncorrectable_Sector_Count;
} smart_attr_t;

typedef smart_attr_t smart_attr;



#endif
