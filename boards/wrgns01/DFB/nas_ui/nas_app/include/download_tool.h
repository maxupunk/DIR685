#ifndef _DOWNLOAD_TOOL_H_
#define _DOWNLOAD_TOOL_H_
#include "fcrss_parser.h"

typedef struct download_obj{
	FcNode *node;
	int d_count;
	int d_flag;
}DownloadObj; 

int fc_download_init_v2(FcNode *head);
void threadid_pool_clear(int *threadid_pool);
void fc_download_init(FcNode *node, int download_count);
void* fc_download_r(void *obj);
FcNode* create_download_tree(FcNode *head, int download_count, int d_flag, int *if_head_delete);
#endif
