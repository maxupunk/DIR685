#ifndef _COMPRESS_TOOL_H_
#define _COMPRESS_TOOL_H_
#include "fcrss_parser.h"

void fc_compress_init(FcNode *head, int compress_count);
void* fc_compress_r(void *arg);
#endif
