#ifndef _FCRSS_PARSER_H_
#define _FCRSS_PARSER_H_

//#define DEBUG 1
#define LOCAL_PIC_DIR 			"/tmp/fc_icon/"
#define LOCAL_CHANNEL_LIST_DIR 	LOCAL_PIC_DIR"channel_list_icon/"
#define LOCAL_CHANNEL_SHOW_DIR 	LOCAL_PIC_DIR"channel_show_icon/"
#define LOCAL_CHANNELS_DIR      LOCAL_PIC_DIR"channels_icon/"  
#define LOCAL_CHANNEL_LIST_XML  LOCAL_PIC_DIR"channel_list.xml"
#define LOCAL_CHANNEL_XML  		LOCAL_PIC_DIR"channel.xml"
#define LOCAL_REG_IMG  			LOCAL_PIC_DIR"register_pic"
#define LOCAL_RESETID_XML  		LOCAL_PIC_DIR"resetid.xml"
#define LOCAL_CHANNEL_SHOW_XML  LOCAL_PIC_DIR"channel_show.xml"
#define REMOTE_HOST 			"rss.framechannel.com"
#define PRODUCTID 				"DIR685"
#define PREPARE_DOWNLOAD_COUNT 	5
#define PREPARE_PHOTO_COUNT 	10
#define SOCKNAME  				"/tmp/p_n_c"
#define PARSER_EXIST_FILE 1
#define NOT_PARSER_EXIST_FILE 0

#ifndef DEBUG
	#define dprintf(format, args...)
#else
	#define dprintf(format, args...)	fprintf( stderr, format, ##args)
#endif

typedef struct fc_node{
	//int index;
	int ttl;
	int duration;	
	int scale_size;
	char *title;	
	char *this_guid;				
	char *remote_file_path;
	char *local_file_path;				
	char *file_type;
	struct fc_node *father_node;
	struct fc_node *brother_node;
	struct fc_node *elder_brother_node;
	struct fc_node *son_node;
}FcNode;

typedef struct net_fc_node{
	int ttl;
	int duration;
	char title[1024];
	char this_guid[1024];				
	char remote_file_path[1024];
	char local_file_path[1024];		
}Net_FcNode;

char* get_host_name(char *media_path);
char* get_file_path(char *media_path);
char* get_file_name(char *media_path);
char* get_node_value(char *xml_file, char *node_name);
char* get_node_attr_value(char *xml_file, char *node_name);
char* get_xml_strbuff(char *local_file);
FcNode* create_fcnode_tree(char *xml_file, char *storage_path);
FcNode* search_node_guid(FcNode *node, char *guid);
FcNode* get_fcnode_head(FcNode *node);
FcNode* get_fcnode_tail(FcNode *node);
FcNode* clone_fcnode(FcNode *src);
int get_wan_status();
int get_fcnode_count(FcNode *node);
int get_remote_file_v2(char *media_path, char *local_file_path);
void delete_tree(FcNode *head);
void delete_subtree(FcNode *head);
void node_info_print(FcNode *node, char *stop_point);
void rm_cmpsubtree_file(FcNode *node_new, FcNode *node_old);
void rm_cmptree_file(FcNode *node_new, FcNode *node_old);
void print_netnode(Net_FcNode *node);
void print_subtree(FcNode *head);
void clone_fctree(FcNode *node);
void* delete_fcnode_tree(FcNode *head);
void shift_fcnode_left(FcNode *node);
void shift_fcnode_right(FcNode *node);
char* get_file_type(char *file_type);
FcNode* get_show_setup_info(char *xml_file);
#endif
 
