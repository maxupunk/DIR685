#ifndef _FILE_TOOL_H_ 
#define _FILE_TOOL_H_ 

#define ALL_IMAGE_TYPE   0
#define ONLY_JPEG_TYPE 	 1
int check_file_exist(char *local_file);
int check_image_sizesafe(char *file_path, int file_size);

int get_file_size(char *local_file);
int get_dns_status(char *exe_path, char *remote_server);
int get_remote_file(char *remote_server, char *remote_file, char *local_file);
int img_search(char *tmp_path, int file_type);
int do_fork_execv(char *cmd_path, char **cmd);
int check_photo_compress(char *file_path);
int web_tcpreq_v2(char *exe_path, char *remote_server, char *remote_file, char *local_file);
int jpeg_compress(char *remote_file_path, char *local_file_path, int scale_size);
char* replace_subname(char *file_path, char *subname);
char* get_path(int type,char *old_path, char *item_name);
char* get_file_name_v3(char *media_path, char *old_file_name, char *local_dir_name);
int check_otherimage_sizesafe(char *file_path);
#endif
