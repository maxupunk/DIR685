#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "fcrss_parser.h"
#include "str_tool.h"
#include "file_tool.h"
#include "download_tool.h"

extern pthread_mutex_t f_mutex;
extern pthread_cond_t f_cond;
extern int pthread_num_f;

void fc_download_init(FcNode *head, int download_count)
{				
	FcNode *tail=NULL;
	int i=0, flag=0, node_count, all_count;
	int wan_status=0;
	
	all_count=2*download_count+1;
	node_count=get_fcnode_count(head);			
	tail=get_fcnode_tail(head);
		
	if(node_count>all_count)
	{				
		for(i=0;i<=download_count&&head!=NULL;i++)
		{			
			if(head->local_file_path!=NULL&&!check_file_exist(head->local_file_path))
			{						
				wan_status=get_wan_status();
				if(wan_status) 
					flag=get_remote_file_v2(head->remote_file_path, head->local_file_path);											
				else
					break;					
			}						
			head=head->brother_node;													
		}
					
		for(i=0;i<download_count&&tail!=NULL;i++)
		{
			if(tail->local_file_path!=NULL&&!check_file_exist(tail->local_file_path))
			{						
				wan_status=get_wan_status();
				if(wan_status) 
					flag=get_remote_file_v2(tail->remote_file_path, tail->local_file_path);							
				else
					break;					
			}
			tail=tail->elder_brother_node;													
		}	
								
		if(tail!=NULL) tail=tail->elder_brother_node;															
		if(tail!=NULL)
		{
			if(tail->local_file_path!=NULL&&check_file_exist(tail->local_file_path)) remove(tail->local_file_path);									
		}									
	}else{
		while(head!=NULL)
		{   							
			if(head->local_file_path!=NULL&&!check_file_exist(head->local_file_path))
			{						
				wan_status=get_wan_status();
				if(wan_status) 
					flag=get_remote_file_v2(head->remote_file_path, head->local_file_path);							
				else
					break;					
			}
			head=head->brother_node;													
		}	
	}					
}

//download thread
void* fc_download_r(void *arg)
{	
	pthread_detach(pthread_self());
	
	DownloadObj *dobj=NULL;
	FcNode *head=NULL, *tmp=NULL;
	int i=0, j=0, if_delete_head=1, wan_status=0;
	
	pthread_mutex_lock(&f_mutex);				
	pthread_num_f++;
	dprintf("\n++pthread_num %d\n", pthread_num_f);
	pthread_mutex_unlock(&f_mutex);		
		
	dobj=(DownloadObj*)arg;						
	head=create_download_tree(dobj->node, dobj->d_count, dobj->d_flag, &if_delete_head);		
	tmp=head;
				
	while(head!=NULL)
	{   							
		if(i==0&&if_delete_head==1)
		{
			if(head->local_file_path!=NULL&&check_file_exist(head->local_file_path)) remove(head->local_file_path);	
		}else{	
			if(head->local_file_path!=NULL)
			{													
				if(!check_file_exist(head->local_file_path))
				{
					wan_status=get_wan_status();
					if(wan_status)
					{ 						
						get_remote_file_v2(head->remote_file_path, head->local_file_path);		
						dprintf("\ndownload remote file %s, local file %s\n", head->remote_file_path, head->local_file_path);															
					}else
						break;					
				}
			
				if(j==1) 
				{					
					usleep(50000);					
					pthread_mutex_lock(&f_mutex);	
					pthread_cond_broadcast(&f_cond);
					pthread_mutex_unlock(&f_mutex);		
					dprintf("\nthread_signal1\n");					
				}	
				j++;		
			}
		}	
		head=head->brother_node;													
		i++;
	}	
	
	head=tmp;
	delete_fcnode_tree(head);
	pthread_mutex_lock(&f_mutex);	
	pthread_cond_broadcast(&f_cond);
	dprintf("\nthread_signal2\n");					
	pthread_num_f--;	
	if(pthread_num_f<0) pthread_num_f=0;
	dprintf("\n--pthread_num %d\n", pthread_num_f);	
	pthread_mutex_unlock(&f_mutex);			
	pthread_exit(NULL);		
}

//create download tree for download thread using, d_flag indicates direction for files downloading
//, if_head_flag indicates if first node will be deleted 
FcNode* create_download_tree(FcNode *head, int download_count, int d_flag, int *if_head_delete)
{		
	FcNode *tail=NULL, *dl_head=NULL, *dl_tail=NULL, *tmp=NULL;
	int i=0, node_count, all_count;
			
	all_count=2*download_count+1;
	node_count=get_fcnode_count(head);			
	tail=get_fcnode_tail(head);
		
	if(node_count>all_count)
	{	
		*if_head_delete=1;						
        for(i=0;i<=download_count&&head!=NULL;i++)
		{
			if(dl_head==NULL)
			{
				dl_head=clone_fcnode(head);
				dl_head->elder_brother_node=NULL;			
				dl_tail=dl_head;
			}else{
				tmp=clone_fcnode(head);						
				tmp->elder_brother_node=dl_tail;
				dl_tail->brother_node=tmp;						
				dl_tail=tmp;
			}	
			
			dl_tail->brother_node=NULL;
			head=head->brother_node;													
		}
																       
        for(i=0;i<download_count&&tail!=NULL;i++)
		{
			tmp=clone_fcnode(tail);						
			tmp->elder_brother_node=dl_tail;
			dl_tail->brother_node=tmp;						
			dl_tail=tmp;
			dl_tail->brother_node=NULL;			
			tail=tail->elder_brother_node;													
		}	
		
		if(d_flag==1)		
		{
			if(tail!=NULL)
			{ 
				tail=tail->elder_brother_node;
				if(tail!=NULL)
				{
					tmp=clone_fcnode(tail);						
					tmp->brother_node=dl_head;
					dl_head->elder_brother_node=tmp;						
					dl_head=tmp;
					dl_head->elder_brother_node=NULL;					
				}					
			}	
		}else{			
			if(head!=NULL) 
			{
				head=head->brother_node;		
				if(head!=NULL)
				{
					tmp=clone_fcnode(head);						
					tmp->brother_node=dl_head;
					dl_head->elder_brother_node=tmp;						
					dl_head=tmp;
					dl_head->elder_brother_node=NULL;			
				}	
			}	
		}
		return dl_head;								
	}else{
		*if_head_delete=0;
		while(head!=NULL)
		{   										
			if(dl_head==NULL)
			{
				dl_head=clone_fcnode(head);
				dl_head->elder_brother_node=NULL;			
				dl_tail=dl_head;
			}else{
				tmp=clone_fcnode(head);						
				tmp->elder_brother_node=dl_tail;
				dl_tail->brother_node=tmp;						
				dl_tail=tmp;
			}	
			
			dl_tail->brother_node=NULL;
			head=head->brother_node;																			
		}	
		
		return dl_head;
	}						
}

int fc_download_init_v2(FcNode *head)
{
	
	int flag=0, wan_status=0;
	
	while(!flag)
	{
		if(head->local_file_path!=NULL&&!check_file_exist(head->local_file_path))
		{						
			wan_status=get_wan_status();
			if(wan_status) 
				flag=get_remote_file_v2(head->remote_file_path, head->local_file_path);											
			else
				break;					
		}else{
			break;
		}							
	}	
	
	return flag;
}		