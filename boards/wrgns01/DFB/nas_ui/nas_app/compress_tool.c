#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <directfb.h>
#include "fcrss_parser.h"
#include "str_tool.h"
#include "file_tool.h"
#include "download_tool.h"
#include "compress_tool.h"

extern IDirectFB *gp_dfb;
extern pthread_mutex_t p_mutex;
extern pthread_cond_t p_cond;
extern int pthread_num;

void fc_compress_init(FcNode *head, int compress_count)
{				
	FcNode *tail=NULL;
	int i=0, node_count, all_count;
	
	all_count=2*compress_count+1;
	node_count=get_fcnode_count(head);			
	tail=get_fcnode_tail(head);
	
	dprintf("\nnode_count %d\n", node_count);	
	if(node_count>all_count)
	{				
		for(i=0;i<=compress_count&&head!=NULL;i++)
		{			
			
			if(head->local_file_path!=NULL&&!check_file_exist(head->local_file_path))
			{													
				dprintf("\n1.head->remote_file_path %s, head->local_file_path %s\n",head->remote_file_path, head->local_file_path);				
				jpeg_compress(head->remote_file_path, head->local_file_path, head->scale_size);														
			}				
			head=head->brother_node;													
		}
					
		for(i=0;i<compress_count&&tail!=NULL;i++)
		{
			if(tail->local_file_path!=NULL&&!check_file_exist(tail->local_file_path))
			{				
				dprintf("\n1.tail->remote_file_path %s, tail->local_file_path %s\n",tail->remote_file_path, tail->local_file_path);				
				jpeg_compress(tail->remote_file_path, tail->local_file_path, tail->scale_size);						
			}	
			tail=tail->elder_brother_node;													
		}	
															
	}else{				
		while(head!=NULL)
		{   													
			if(head->local_file_path!=NULL&&!check_file_exist(head->local_file_path))
			{								
				dprintf("\n2.head->remote_file_path %s, head->local_file_path %s\n",head->remote_file_path, head->local_file_path);				
				jpeg_compress(head->remote_file_path, head->local_file_path, head->scale_size);												
			}	
			head=head->brother_node;													
		}	
	}			
}


//compress thread
void* fc_compress_r(void *arg)
{	
	pthread_detach(pthread_self());
	
	DownloadObj *dobj=NULL;
	FcNode *head=NULL, *tmp=NULL;
	int i=0, j=0, if_delete_head=1;
		
	pthread_mutex_lock(&p_mutex);				
	pthread_num++;
	dprintf("\n++pthread_num %d\n", pthread_num);
	pthread_mutex_unlock(&p_mutex);		
	
	dobj=(DownloadObj*)arg;						
	head=create_download_tree(dobj->node, dobj->d_count, dobj->d_flag, &if_delete_head);		
	tmp=head;
			
	while(head!=NULL)
	{   							
		if(i==0&&if_delete_head==1)
		{
			
			if(head->local_file_path!=NULL&&check_file_exist(head->local_file_path)) 
			{				
				if(strcmp(head->local_file_path, head->remote_file_path)!=0) 
				{
					dprintf("\nremove head->local_file_path %s\n", head->local_file_path);
					remove(head->local_file_path);	
				}	
			}	
		}else{	
			
			if(head->local_file_path!=NULL)
			{
				if(!check_file_exist(head->local_file_path))
				{						
						dprintf("\ncompress head->local_file_path %s\n", head->local_file_path);								
						jpeg_compress(head->remote_file_path, head->local_file_path, head->scale_size);	
						usleep(10);							
				}										
				if(j==2) 
				{					
					usleep(50000);					
					pthread_mutex_lock(&p_mutex);	
					pthread_cond_broadcast(&p_cond);
					pthread_mutex_unlock(&p_mutex);		
					dprintf("\nthread_signal1\n");					
				}	
				j++;			
			}	
		}	
		dprintf("\nall head->local_file_path %s\n", head->local_file_path);		
		head=head->brother_node;													
		i++;
	}	
	
	head=tmp;
	delete_fcnode_tree(head);				
	pthread_mutex_lock(&p_mutex);	
	pthread_cond_broadcast(&p_cond);
	dprintf("\nthread_signal2\n");					
	pthread_num--;	
	if(pthread_num<0) pthread_num=0;
	dprintf("\n--pthread_num %d\n", pthread_num);	
	pthread_mutex_unlock(&p_mutex);			
	pthread_exit(NULL);		
}
