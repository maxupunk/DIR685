#include <stdio.h>
#include <dirent.h>
#include <stddef.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <netdb.h>
#include "alpha_dfb_define.h"
#include "str_tool.h"
#include "file_tool.h"
#include "webtcpreq.h"

char* parser_bracket(char *file_path)
{
	int c='(', len=0, count=0;
	char *s=NULL, *tmp=NULL, *s2=NULL;
	
	len=strlen(file_path);	
	s=file_path;
	while(s!=NULL)
	{
		s=strchr(s,c);
		if(s!=NULL) 
		{
			printf("\ns %s\n", s);
			s=s+1;
			printf("\ns %s\n", s);
			count++;
		}	
	}	
		
	printf("\ncount %d\n", count);
	if(count>0) 
	{
		len=len+count*2+1;
		s2=(char*)malloc(len*sizeof(char*));			
		memset(s2, 0, len);
		s=file_path;				
		while(s!=NULL)
		{
			tmp=s;
			s=strchr(s,c);
			if(s!=NULL){ 			
				strncat(s2, tmp, strlen(tmp)-strlen(s));
				strcat(s2, "\(");
				s=s+1;			
			}	
		}	 	
		printf("\nfile_path_parser %s\n", s2);
		return s2;
	}	
	
	return file_path;
}

int get_file_size(char *local_file)
{		
	struct stat fstat;	
	
	if(stat(local_file,&fstat)==0){
		return fstat.st_size;
	}else{
		return -1;
	}	
}

int check_file_exist(char *local_file)
{
	FILE *fd;
		
	if((fd = fopen(local_file, "r")) != NULL)
	{
		fclose(fd);		
		return 1;
	}
	else{
		return 0;
	}		
}

int get_remote_file(char *remote_server, char *remote_file, char *local_file)
{ 
    int flag=0;
    
  	if(remote_server==NULL||remote_file == NULL||local_file==NULL) return flag; 
  	else if(remote_server !=NULL && strlen(remote_server)==0) return flag;
  	else if(remote_file !=NULL && strlen(remote_file)==0) return flag;
  	else if(local_file !=NULL && strlen(local_file)==0) return flag;  	        
#ifdef ALWAYS_CHECK_DOMAIN_NAME    
    flag=get_dns_status(CHECK_DOMAIN_NAME, remote_server);	                
    if(flag==1)
    {    	    	
    	flag=web_tcpreq_v2(WEB_TCPREQ, remote_server, remote_file, local_file);    	    	
    }	
#else
    flag=web_tcpreq(remote_server, remote_file, local_file);  
#endif    
    return flag;        	
}

//file:type>0 or dir:type=4
char* get_path(int type, char *old_path, char *item_name)
{
	char *new_path = NULL;
	int old_path_len = 0, item_name_len = 0, buffer_len = 2, total_len;
		
	old_path_len = strlen(old_path);
	item_name_len = strlen(item_name);	
	total_len = old_path_len+item_name_len+buffer_len;
	new_path = (char*)malloc(total_len*sizeof(char));
	memset(new_path, 0, total_len);
	strcpy(new_path, old_path);	
	strcat(new_path, item_name);						
	if(type==4) strcat(new_path, "/");							
	return new_path;
		
	dprintf("\nget_path(): path_name = %s\n", old_path);
	dprintf("\nget_path(): new_path = %s\n", new_path);	
}	
	
int check_image_sizesafe(char *file_path, int file_size)
{	
	struct stat fstat;	
	
	if(stat(file_path, &fstat)==0)
	{
		if(fstat.st_size<file_size) return 1;					   	
	}
	
	return 0;	
}

char* replace_subname(char *file_path, char *subname)
{
	int c='.', len=0;	
	char *s, *s2;
			
	s=strrchr(file_path, c);	
	if(s!=NULL) 
	{
		len=strlen(file_path)-strlen(s)+strlen(subname)+1;
		s2=(char*)malloc(len*sizeof(char));
		memset(s2, 0, len);
		strncat(s2, file_path, strlen(file_path)-strlen(s));
		strcat(s2, subname);				
		return s2;
	}		
	return file_path;
}	

int do_fork_execv(char *cmd_path, char **cmd)
{
	pid_t pid;
	int status;
							
	if((pid=fork())==0)
	{		
		//nice(-2);		
		if(execv(cmd_path, cmd)==-1) 
		{
				printf("fail\n");										
				exit(0);
		}			
		//nice(2);
	}	
	if((pid=wait(&status))==-1) return 0;
	else return 1;	
}	

int check_photo_compress(char *file_path)
{				
	if(img_search(file_path, ONLY_JPEG_TYPE)==0) return 0;							
	if(!check_image_sizesafe(file_path, NEED_COMPRESS_SIZE)) return 1;		
	else return 0;
}	
	
int jpeg_compress(char *remote_file_path, char *local_file_path, int scale_size)
{				
	int compress_status=0;		
	char *scale="1/1";

	dprintf("\nscale_size %d\n", scale_size);		
	if(scale_size==1) scale="1/1";
	else if(scale_size==2) scale="1/2";
	else if(scale_size==4) scale="1/4";
	else if(scale_size==8) scale="1/8";
	
	char *cmd[]={"djpeg","-color","128","-scale",scale,"-gif","-outfile",local_file_path,remote_file_path,0};		
	compress_status=do_fork_execv("/directfb/djpeg", cmd);			
	if(compress_status==1) return 1;
	else return 0;		
}	
			
int slash_search(char *path_name)
{
	int path_len = 0, item_len = 0,count = 0, i = 0;	
	item_len=strlen(strrchr(path_name,'/'));
	path_len = strlen(path_name);				
	if(item_len == 1){		
		for(i=path_len-1; i>=0; i--){			    		    			
			if(path_name[i]=='/') count++;							
	             	if(count == 2) break;			
		}
		return i;						
	}else		
		return path_len-item_len;						
}	
	
void namelist_free(int total_count, struct dirent **namelist)
{	
	while(total_count--){
		free(namelist[total_count]);
	}
	free(namelist);					
}

int export_from_file(char *filename, char *p_eventbuffer, int buf_len)
{
	FILE *fd=NULL;
    fd=fopen(filename,"r");
    if(fd==NULL)
    {
    	printf("Open file failed : %s \n", filename);
    	return -1;
	}
	fread(p_eventbuffer ,1, buf_len ,fd);
    fclose(fd);
    return 1;
}


char* get_file_subname(char *file_path)
{	
	char *tmp=NULL;
	int c='.';	
	
	tmp=strrchr(file_path, c);			
	return strrchr(file_path, c);		
}	

int img_search(char *tmp_path, int file_type)
{
	int i=0;
	char *file_subname=NULL;
	char **img_sub=NULL;	
	char *img_sub2[]={".gif",".png",".jpe",".jpeg",".jpg","0x"};
	char *img_sub3[]={".jpe",".jpeg",".jpg","0x"};
	
	if(file_type==ALL_IMAGE_TYPE){		
		img_sub=img_sub2;
	}else if(file_type==ONLY_JPEG_TYPE){		
		img_sub=img_sub3;
	}	
	
	file_subname=get_file_subname(tmp_path);									
	while(1)
	{					
		if(file_subname!=NULL&&(char*)strcasestr( file_subname, img_sub[i]) != NULL) return 1;
		if( strstr(img_sub[i],"0x")!=NULL) return 0;
		i++;		
	}						
	return 0;	
}

int get_dns_status(char *exe_path, char *remote_server)
{
	FILE  *fp;
  	char  buf[5];  	
  	int   ch, flag=1;
  	char command[1024];
  	
  	sprintf(command,"%s %s", exe_path, remote_server);  		
  	memset(buf, '\0', sizeof(buf));  	  		
	fp=popen(command,"r");	
	
	if (fp!=NULL) 
	{
	    ch=fread(buf,sizeof(char), 5, fp);	
	    if (ch > 0)	
	    {	    	
	    	if(strstr(buf,"ok")!=NULL) flag=1;
	    	else flag=0;	
	    }	        
	    
    	pclose(fp);    	
    	return flag;
  	}else  	   
    	return flag;		
}


int web_tcpreq_v2(char *exe_path, char *remote_server, char *remote_file, char *local_file)
{
	FILE  *fp;
  	char  buf[5];  	
  	int   ch, flag=0;
  	char command[2048];
  	  	  	  	  	
  	sprintf(command,"%s %s %s %s", exe_path, remote_server, remote_file, local_file);  	  	
  	memset(buf, '\0', sizeof(buf));    
	fp=popen(command,"r");		
	
	if (fp!=NULL) 
	{
	    ch=fread(buf,sizeof(char), 5, fp);		   
	    if (ch > 0)	
	    {	    		    		    	
	    	if(strstr(buf,"1")!=NULL) flag=1;
	    	else flag=0;	
	    }	        
	    
    	pclose(fp);    	
    	return flag;
  	}else  	   
    	return flag;		    	
}

//auto make file name
char* get_file_name_v3(char *media_path, char *old_file_name, char *local_dir_path) 
{
	char *file_name=NULL, *tmp=NULL;
	int file_num=0, c=0, len=0;
				
	while(*media_path!='\0')
	{
		c=*media_path;		
		file_num=file_num+c;
		media_path++;
	}
			
	len=strlen(old_file_name)+strlen(local_dir_path);	
	len=len+50;	
	file_name=(char*)malloc(len*sizeof(char));	
	memset(file_name, 0, len);
	sprintf(file_name,"%s/photo_%d_", local_dir_path, file_num);		
	tmp=strrchr(old_file_name,'.');	
	len=strlen(old_file_name)-strlen(tmp);
	strncat(file_name, old_file_name, len);
	strcat(file_name,".gif");	
	return file_name;	
}