#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <xmldb.h>
#include <libxmldbc.h>
#include <netdb.h>
#include <sys/socket.h>
#include "fcrss_parser.h"
#include "str_tool.h"
#include "file_tool.h"
#include "rgdb_node_define.h"

char *xml_node[]={"<ttl>","<item>","<title>","<media:content","<guid isPermaLink=\"false\">","<guid isPermaLink=\"true\">"};
char *xml_attr[]={"url","type","duration"};

char* get_host_name(char *media_path){
	char *p_header[]={"http://", "ftp://"};
	char *tmp_path, *host_name;
	int i=0, count;
			
	for(i=0; i<2;i++){
		count=0;
		if((tmp_path=strstr(media_path, p_header[i]))!=NULL) {
			tmp_path+=strlen(p_header[i]);		
			media_path+=strlen(p_header[i]);				
			
			while(*tmp_path!='/'){				
				tmp_path++;					
				count++;				
			}					
			
			host_name=sam_strncpy(media_path, count);			
			return host_name;			
		}	
	}				
	return NULL;
}	

char* get_file_path(char *media_path){
	char *host_name=NULL, *file_path=NULL, *tmp_path=NULL;
	int count;
	
	host_name=get_host_name(media_path);
	if((tmp_path=strstr(media_path, host_name))!=NULL) {
		tmp_path+=strlen(host_name);				
		count=strlen(tmp_path);
		file_path=sam_strncpy(tmp_path, count);
	}		
	free(host_name);
	return file_path;
}

char* get_file_name_v2(char *media_path) //auto make file name
{
	char *file_name=NULL, *old_file_name=NULL;
	int file_num=0, c=0, len=0;
	
	old_file_name=get_file_name(media_path);
		
	while(*media_path!='\0')
	{
		c=*media_path;		
		file_num=file_num+c;
		media_path++;
	}
	
	len=strlen(old_file_name);	
	len=len+30;	
	file_name=(char*)malloc(len*sizeof(char));
	memset(file_name, 0, len);
	sprintf(file_name,"photo_%d_%s", file_num, old_file_name);
	free(old_file_name);
	return file_name;	
}

char* get_file_name(char *media_path)
{
	char *file_path=NULL, *file_name=NULL, *tmp_path=NULL;	
	int count;
	
	file_path=get_file_path(media_path);
	if((tmp_path=strrchr(file_path,'/'))!=NULL) 
	{
		tmp_path+=1;				
		count=strlen(tmp_path);	
		file_name=sam_strncpy(tmp_path, count);													
	}		
	
	free(file_path);
	return file_name;
}		


char* get_file_type(char *file_type){
	int i=0;
	char *type_set[]={"image/gif","image/jpeg","image/pjpeg","image/x-xbitmap","0x"}; 
	char *img_sub[]={".gif",".jpeg",".xbm","0x"};
	while(1){						
		if( (char*)strcasestr( file_type, type_set[i]) != NULL) {
			switch(i){
				case 0:						
						return img_sub[0];						
						break;
				case 1:
						return img_sub[1];
						break;
				case 2:
						return img_sub[1];
						break;
				case 3:	
						return img_sub[2];		
						break;	
			}					
		}	
		if( strstr(type_set[i],"0x")!=NULL) return NULL;
		i++;		
	}						
	return NULL;	
}	

char* get_node_value(char *xml_file, char *node_name){
	char *xml_cpy, *node_value;		
	int count=0;
	
	xml_file+=strlen(node_name);		
	xml_cpy=xml_file;	
			
	while(*xml_cpy!='<'){				
		xml_cpy++;					
		count++;				
	}		
	
	node_value=sam_strncpy(xml_file, count);	
	return node_value;
}	


char* get_node_attrs(char *xml_file, char *node_attr){
	char *xml_cpy;		
	int count=0;
					
	xml_cpy=xml_file;					
	while(*xml_cpy!='>'){				
		xml_cpy++;					
		count++;				
	}	
	xml_cpy=sam_strncpy(xml_file, count);			
	return xml_cpy;
}

char* get_node_attr_value(char *xml_file, char *node_attr){
	char *xml_cpy, *xml_cpy2,*node_value=NULL, *tmp, *tmp2;			
	char split[]="amp;";
	int count=0;
	
	xml_cpy=get_node_attrs(xml_file, node_attr);
	tmp2=xml_cpy;				
	if((xml_cpy = strstr(xml_cpy, node_attr)) != NULL ) {
		xml_cpy+=strlen(node_attr)+2;		
		xml_cpy2=xml_cpy;
		while(*xml_cpy2!='\"'){				
			xml_cpy2++;					
			count++;				
		}	
		
		if(count>0) {
			node_value=sam_strncpy(xml_cpy, count);						
			tmp=node_value;
			node_value=(char*)sam_strreplace(node_value, split);
			if(node_value==NULL) node_value=tmp;
			else free(tmp);
		}	
	}	
	free(tmp2);
	return node_value;
}	
 
int get_remote_file_v2(char *media_path, char *local_file_path)
{
	char *remote_host, *remote_file_path;
	int flag=0;
			
	if(media_path==NULL||local_file_path==NULL) return flag;
	else if(media_path!=NULL&&strlen(media_path)==0) return flag;
	else if(local_file_path!=NULL&&strlen(local_file_path)==0) return flag;	
	remote_host=get_host_name(media_path);
	remote_file_path=get_file_path(media_path);		
	flag=get_remote_file(remote_host, remote_file_path, local_file_path);				
	free(remote_host);
	free(remote_file_path);
	return flag;
}	

FcNode* create_fcnode_tree(char *xml_file, char *storage_path){
	FcNode *head=NULL, *tail=NULL, *tmp=NULL;	
	char *xml_cpy, *xml_node_ptr;
	int xml_ttl=15, node_count=0, node_limit=99, flag=1;
			
	xml_cpy=xml_file;		
	if((xml_cpy = strstr(xml_cpy, xml_node[0])) != NULL ) xml_ttl=atoi(get_node_value(xml_cpy, xml_node[0]));	
	while( (xml_cpy = strstr(xml_cpy, xml_node[1])) != NULL )
	{							
		xml_cpy+=strlen(xml_node[1]);					
		if(head==NULL) {
			head=(FcNode*)malloc(sizeof(FcNode));						
			head->title=NULL;		
			head->remote_file_path=NULL;		
			head->this_guid=NULL;		
			head->father_node=NULL;				
			head->brother_node=NULL;				
			head->elder_brother_node=NULL;				
			head->son_node=NULL;		
			tail=head;		
		}else{
			tmp=(FcNode*)malloc(sizeof(FcNode));							
			tmp->elder_brother_node=tail;			
			tail->brother_node=tmp;			
			tail=tmp;
			tail->brother_node=NULL;							
			tail->title=NULL;		
			tail->remote_file_path=NULL;		
			tail->this_guid=NULL;		
			tail->father_node=NULL;				
			tail->brother_node=NULL;		
		}						
		
		tail->ttl=xml_ttl;
		tail->scale_size=1;
		
		if((xml_node_ptr = strstr(xml_cpy, xml_node[2])) != NULL ) 
			tail->title=get_node_value(xml_node_ptr, xml_node[2]);											
		else
			flag=0;					
						
		if((xml_node_ptr = strstr(xml_cpy, xml_node[3])) != NULL ) 
		{			
			char *duration=NULL, *local_file_path=NULL;						
						
			tail->remote_file_path=get_node_attr_value(xml_node_ptr, xml_attr[0]);									
			if(tail->remote_file_path!=NULL) 
				local_file_path=get_file_name_v2(tail->remote_file_path);				
			else
				flag=0;
					
			if(local_file_path!=NULL)
			{												
				tail->local_file_path=sam_strcat(storage_path, local_file_path);																								
				free(local_file_path);
			}else {
				tail->local_file_path=NULL;				
			}	
			tail->file_type=get_node_attr_value(xml_node_ptr, xml_attr[1]);									
			duration=get_node_attr_value(xml_node_ptr, xml_attr[2]);													
			tail->duration=(duration!=NULL)?atoi(duration):10;
			free(duration);										
		}else{
			flag=0;	
		}	
		if((xml_node_ptr = strstr(xml_cpy, xml_node[4])) != NULL ) tail->this_guid=get_node_value(xml_node_ptr, xml_node[4]);															
		if((xml_node_ptr = strstr(xml_cpy, xml_node[5])) != NULL ) tail->this_guid=get_node_value(xml_node_ptr, xml_node[5]);												
		if(tail->this_guid==NULL) flag=0;		
		if(flag==0)
		{			
			tmp=tail;
			tail=tail->elder_brother_node;
			tail->brother_node=NULL;	
			free(tmp);		
			break;
		}			
		//printf("\n\ntail->ttl %d, tail->title %s, tail->remote_file_path %s, tail->local_file_path %s, tail->duration %d\n\n", tail->ttl, tail->title, tail->remote_file_path, tail->local_file_path, tail->duration);
        node_count++;
		if(node_count>=node_limit) break;
	}		
	return head;
}	

char* get_xml_strbuff(char *local_file)
{
	FILE *fd;
	char *pbuffer;
	int file_size=0;
		
	file_size = get_file_size(local_file);	
	if(file_size<=0) return 0;	
	if((fd = fopen(local_file, "r")) == NULL) return 0;				
	pbuffer=(char*)malloc(file_size+1);
	memset(pbuffer, 0, file_size+1);	
	fread(pbuffer, file_size, 1, fd);		
	fclose(fd);				
	return pbuffer;
}


FcNode* get_show_setup_info(char *xml_file) 
{	
	char *xml_cpy=NULL, *xml_node_ptr=NULL;	
	FcNode *head=NULL;
				
	
	xml_cpy=xml_file;										
	while( (xml_cpy = strstr(xml_cpy, "Framechannel Setup")) != NULL )
	{			
		
		head=(FcNode*)malloc(sizeof(FcNode));						
		head->title=NULL;					
		head->remote_file_path=NULL;		
		head->local_file_path=NULL;		
		head->this_guid=NULL;		
		head->father_node=NULL;				
		head->brother_node=NULL;				
		head->elder_brother_node=NULL;						
		head->son_node=NULL;	
		head->file_type=NULL;
		
		xml_cpy++;
		if((xml_node_ptr = strstr(xml_cpy, xml_node[3])) != NULL ) 
		{															
			head->remote_file_path=get_node_attr_value(xml_node_ptr, xml_attr[0]);											
			head->file_type=get_node_attr_value(xml_node_ptr, xml_attr[1]);						
		}								
	}		
	return head;
}	

FcNode* search_node_guid(FcNode *node, char *guid){
	FcNode *head=NULL;
	
	head=node;
	while(head!=NULL){	
		if(strcmp(head->this_guid, guid)==0) break;
		head=head->brother_node;  		
	}		
	return head;
}
	
	
void delete_subtree(FcNode *head){		
	if(head!=NULL){															
		delete_subtree(head->brother_node);	
        if(head->title!=NULL) free(head->title);
		if(head->this_guid!=NULL) free(head->this_guid);		
		if(head->local_file_path!=NULL) free(head->local_file_path);
		if(head->remote_file_path!=NULL) free(head->remote_file_path);												
		if(head->file_type!=NULL) free(head->file_type);												
		free(head);
	}
}

void delete_tree(FcNode *head){		
	if(head!=NULL){																		
		delete_tree(head->brother_node);												
		delete_subtree(head->son_node);									
        if(head->title!=NULL) free(head->title);
		if(head->this_guid!=NULL) free(head->this_guid);		
		if(head->local_file_path!=NULL) free(head->local_file_path);
		if(head->remote_file_path!=NULL) free(head->remote_file_path);												
		if(head->file_type!=NULL) free(head->file_type);												
		free(head);
	}
}

void print_subtree(FcNode *head){
	if(head!=NULL) {
		print_subtree(head->brother_node);
		printf("\nson_node: node->ttl=%d , node->this_guid=%s , node->title=%s , node->remote_file_path=%s , node->local_file_path=%s , node->duration=%d\n", \
		head->ttl,head->this_guid, head->title, head->remote_file_path, head->local_file_path, head->duration);					
	}			
}	

void print_tree(FcNode *head){		
	if(head!=NULL){
		print_tree(head->brother_node);
		print_subtree(head->son_node);
		printf("\nfather_node: node->ttl=%d , node->this_guid=%s , node->title=%s , node->remote_file_path=%s , node->local_file_path=%s , node->duration=%d\n", \
		head->ttl, head->this_guid, head->title, head->remote_file_path, head->local_file_path, head->duration);											
	}		
}							

void print_netnode(Net_FcNode *node){		
	printf("\nnet_node: node->ttl=%d , node->this_guid=%s , node->title=%s , node->remote_file_path=%s , node->local_file_path=%s , node->duration=%d\n", \
	node->ttl, node->this_guid, node->title, node->remote_file_path, node->local_file_path, node->duration);									
}



void rm_subtree_file(FcNode *head){		
	if(head!=NULL){															
		rm_subtree_file(head->brother_node);	        
		if(head->local_file_path!=NULL) 
		{
			if(check_file_exist(head->local_file_path))	remove(head->local_file_path);		
		}	
	}
}

void rm_tree_file(FcNode *head){		
	if(head!=NULL){																				
		rm_subtree_file(head->son_node);									        
		if(head->local_file_path!=NULL)
		{
			if(check_file_exist(head->local_file_path)) remove(head->local_file_path);		
		}	 
	}
}

void rm_cmpsubtree_file(FcNode *node_new, FcNode *node_old){
	FcNode *tmp;
	int flag;
	
	tmp=node_new;	
	while(node_old!=NULL){				
		if(node_old->local_file_path!=NULL){
			flag=0;			
			while(node_new!=NULL){								
				if(node_new->local_file_path!=NULL&&strcmp(node_new->local_file_path, node_old->local_file_path)==0) {					
					flag=1;
					break;
				}	
				node_new=node_new->brother_node;
			}
			node_new=tmp;
			if(flag==0) 
			{
				if(check_file_exist(node_old->local_file_path)) remove(node_old->local_file_path);							
			}	
		}			
		node_old=node_old->brother_node;
	}		
}	
	
void rm_cmptree_file(FcNode *node_new, FcNode *node_old){
	FcNode *tmp;
	int flag;
	
	tmp=node_new;	
	while(node_old!=NULL){				
		if(node_old->local_file_path!=NULL){
			flag=0;			
			while(node_new!=NULL){				
				if(node_new->local_file_path!=NULL&&strcmp(node_new->local_file_path, node_old->local_file_path)==0) {
					rm_cmpsubtree_file(node_new->son_node, node_old->son_node);
					flag=1;
					break;
				}	
				node_new=node_new->brother_node;
			}
			node_new=tmp;
			if(flag==0) rm_tree_file(node_old);								
		}			
		node_old=node_old->brother_node;
	}		
}

FcNode* get_fcnode_head(FcNode *node){	
	FcNode *head=NULL;
	
	while(node!=NULL){				
		head=node;
		node=node->elder_brother_node;
	}		
	return head;;
}

FcNode* get_fcnode_tail(FcNode *node){
	FcNode *tail=NULL;
	
	while(node!=NULL){
		tail=node;
		node=node->brother_node;			
	}	
	return tail;
}	

int get_fcnode_count(FcNode *node){
	FcNode *head=NULL;
	int count=0;
	
	head=get_fcnode_head(node);	
	while(head!=NULL){		
		count++;		
		head=head->brother_node;
	}	
	return count;		
}

FcNode* clone_fcnode(FcNode *src)
{
	FcNode *dst=NULL;	
	int count;
	
	dst=(FcNode*)malloc(sizeof(FcNode));		
	dst->ttl=src->ttl;
	dst->duration=src->duration;
	dst->scale_size=src->scale_size;
	dst->title=NULL;
	dst->this_guid=NULL;
	dst->local_file_path=NULL;		
	dst->remote_file_path=NULL;
	if(src->title!=NULL&&(count=strlen(src->title))>0) dst->title=sam_strncpy(src->title, count);					
	if(src->this_guid!=NULL&&(count=strlen(src->this_guid))>0) dst->this_guid=sam_strncpy(src->this_guid, count);						
	if(src->local_file_path!=NULL&&(count=strlen(src->local_file_path))>0) dst->local_file_path=sam_strncpy(src->local_file_path, count);
	if(src->remote_file_path!=NULL&&(count=strlen(src->remote_file_path))>0) dst->remote_file_path=sam_strncpy(src->remote_file_path, count);	
	dst->father_node=NULL;
	dst->brother_node=NULL;
	dst->elder_brother_node=NULL;
	dst->son_node=NULL;		
	return dst;
}

void clone_fctree(FcNode *node)
{
	FcNode *head=NULL, *tail=NULL, *tmp=NULL;	
	FcNode *new_head=NULL, *new_tail=NULL;			
	
	head=get_fcnode_head(node);
	tail=get_fcnode_tail(node);			
	while(head!=NULL){
		if(new_head==NULL){
			new_head=clone_fcnode(head);						
			new_head->elder_brother_node=NULL;			
			new_tail=new_head;
		}else{			
			tmp=clone_fcnode(head);						
			tmp->elder_brother_node=new_tail;
			new_tail->brother_node=tmp;						
			new_tail=tmp;
		}			
		new_tail->brother_node=NULL;				
		head=head->brother_node;			
	}	
	
	tail->brother_node=new_head;	
	new_head->elder_brother_node=tail;							
}		


void* delete_fcnode_tree(FcNode *node)
{
	FcNode *tmp;	
			
	node=get_fcnode_head(node);	
	while(node!=NULL){		
		tmp=node;			
		if(node->title!=NULL) free(node->title);									
		if(node->local_file_path!=NULL) free(node->local_file_path);									
		if(node->this_guid!=NULL) free(node->this_guid);				
		if(node->remote_file_path!=NULL) free(node->remote_file_path);																					
		node=node->brother_node;		
		free(tmp);				
	}
	return NULL;			
}

void remove_fcfile(FcNode *node)
{
	int count=0, max_count=1;
		
	node=get_fcnode_head(node);	
	
	while(node!=NULL){		
		if(!strcmp(node->title,"My Photos")) max_count=10;	
		if(node->local_file_path!=NULL&&check_file_exist(node->local_file_path)){			
			count++;
			if(count>=max_count) remove(node->local_file_path);																	
		}						
		node=node->brother_node;							
	}			
}	

void shift_fcnode_left(FcNode *node){
	FcNode *head, *tail, *tmp;	
			
	head=get_fcnode_head(node);
	tail=get_fcnode_tail(node);		
	head->elder_brother_node=tail;
	tail->brother_node=head;
	tmp=tail->elder_brother_node;	
	head=tail;
	tail=tmp;
	head->elder_brother_node=NULL;
	tail->brother_node=NULL;
}	

void shift_fcnode_right(FcNode *node){
	FcNode *head, *tail, *tmp;
				
	head=get_fcnode_head(node);
	tail=get_fcnode_tail(node);		
	head->elder_brother_node=tail;
	tail->brother_node=head;
	tmp=head->brother_node;	
	tail=head;
	head=tmp;
	head->elder_brother_node=NULL;
	tail->brother_node=NULL;
}

int get_wan_status()
{						
	_u8 rgdb_val_buf[RGDBBUFFER_SIZE]; 
	int connect_type, cable_status, wan_status=0;	
	            
    memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
    xmldbc_get_wb(NULL, 0, RGDB_INTERNET_CONNECT_TYPE, rgdb_val_buf, RGDBBUFFER_SIZE);
    connect_type=atoi(rgdb_val_buf);    
    
    if(connect_type<3)
    {    
	    memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
	    xmldbc_get_wb(NULL, 0, RGDB_INTERNET_CABLE_STATUS, rgdb_val_buf, RGDBBUFFER_SIZE);
	    cable_status=atoi(rgdb_val_buf);    	       	    
	    if(cable_status!=0) 
	    {
		    wan_status=1;
		    if(connect_type==2)
		    {
		    	memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
				xmldbc_get_wb(NULL, 0, RGDB_INTERNET_NETWORK_STATUS, rgdb_val_buf, RGDBBUFFER_SIZE);
				if(!strcmp(rgdb_val_buf,"connected")) wan_status=1;	    		    		    	
				else wan_status=0;
		    }	
		 }   
	}else{					    	
		memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
		xmldbc_get_wb(NULL, 0, RGDB_INTERNET_NETWORK_STATUS, rgdb_val_buf, RGDBBUFFER_SIZE);
		if(!strcmp(rgdb_val_buf,"connected")) wan_status=1;	    		    		    			
	}	  	
	  	
  	return wan_status;
}

	