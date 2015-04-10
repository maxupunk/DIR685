#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "str_tool.h"

char* sam_strcat(char *str_one, char *str_two){
	char *str_new=NULL;
	int len=0;
	
	if(str_one!=NULL && str_two!=NULL){
		len=strlen(str_one)+strlen(str_two)+1;
		str_new=(char*)malloc(len*sizeof(char));			
		memset(str_new, 0, len);
		strcpy(str_new, str_one);
		strcat(str_new, str_two);		
	}	
	return str_new;	
}	

char* sam_strncpy(char *str, int count){
	char *str_new=NULL;
	int len=0;
	
	len=count+1;
	if(str!=NULL){
		str_new=(char*)malloc(len*sizeof(char));
		memset(str_new, 0, len);
		strncpy(str_new,  str, count);	
	}		
	return str_new;
}

void sam_strnarr(char *array, char *str){	
	memset(array, 0, strlen(array));
	if(str!=NULL) strncpy(array, str, strlen(str));	
} 

char* sam_strreplace(char *str, char *split)
{		
		char *str_new=NULL, *tmp, *tmp2, *cp;
		int len=0;
		
		while((cp=strstr(str, split))!=NULL){				
				len=strlen(str)-strlen(cp);
				tmp=sam_strncpy(str, len);
				str=str+len+strlen(split);				
				if(str_new==NULL) {
                     str_new=tmp;
                }else {
                     tmp2=str_new; 
                     str_new=sam_strcat(str_new, tmp);
                     free(tmp2);
                     free(tmp);
                }     
		}	
		
		if(str_new!=NULL&&str!=NULL){
              tmp2=str_new; 
              str_new=sam_strcat(str_new, str);
              free(tmp2);                                          
        }   	        
        return str_new;		
}

