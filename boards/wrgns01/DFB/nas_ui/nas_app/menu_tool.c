#include <stdio.h>
#include <unistd.h>
#include <directfb.h>
#include <dirent.h>
#include <string.h>
#include <stddef.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include "alpha_dfb_define.h"
#include "draw_tool.h"
#include "menu_tool.h"
#include "str_tool.h"
#include "file_tool.h"
#include "fcrss_parser.h"
#include "fcrss_command.h"
#include "download_tool.h"
#include "confirm_center.h"
#include "packet_serialize.h" 

int file_select(const struct direct *entry)
{	
	char str[2];
	
	memset(str, 0, 2);
	str[0]=	*(entry->d_name+0);	
	if ((strcmp(str, ".") == 0) ||(strcmp(entry->d_name, "..") == 0)) return 0;		
	if(entry->d_type==4) return 1;
	return img_search((char*)entry->d_name, ALL_IMAGE_TYPE); 												
}

int alphasort(const void *_a, const void *_b)
{
    int flag;
    struct dirent **a = (struct dirent **)_a;
    struct dirent **b = (struct dirent **)_b;
    flag=strcoll(&((*a)->d_type), &((*b)->d_type));
    return flag; 
}

//free directory entries
void fcfile_free(struct dirent **namelist, int node_count)
{
		int n=node_count;
 		while(n--) {                   
              free(namelist[n]);
        }
        free(namelist);
}

//tranform directory entries into FcNode tree for photo view function
FcNode* create_fcfile_tree(char *local_dir_path, int is_top_layer, int *folder_exist_flag, IDirectFB *gp_dfb)
{
	FcNode *head=NULL, *tail=NULL, *tmp=NULL;
	struct dirent **namelist;	
	char *local_file_path=NULL, *new_local_file_path=NULL;
    int i, node_count, d_type, str_len, scale_size, unsupport_flag;        
		
	//scan a directory for matching entries
    node_count = scandir(local_dir_path, &namelist, file_select, alphasort);        
    if(node_count<=0) return head;    
    
    str_len=strlen(FOLDER_G);                              
    
    //create node tree
    for(i=0;i <node_count; i++)
    {    							
		//default scale 1:1
		scale_size=1;		
		 
		//check entry type, if d->type is 4, it is folder, or is file
		d_type=namelist[i]->d_type;  									
		if(d_type!=4) 
		{
			unsupport_flag=0;		
			local_file_path=get_path(d_type, local_dir_path, namelist[i]->d_name);															 		
			if(check_image_sizesafe(local_file_path, FILE_MAX_SIZE)) 			
			{				
				if(img_search(local_file_path, ONLY_JPEG_TYPE))
				{					
					//if scale_size ==0, this file is not support for DFB drawing					
					scale_size=get_scale_size(local_file_path, gp_dfb);				
					if(scale_size==0)  unsupport_flag=1;											
				}else{
					if(!check_image_sizesafe(local_file_path, NOTJPEG_MAX_SIZE)) unsupport_flag=1;					
				}					
			}else{
				unsupport_flag=1;	
			}	
			
			if(unsupport_flag==1)
			{
				dprintf("\n%s is bad image file\n", local_file_path);
				free(local_file_path);					
				continue;	
			}else{
				free(local_file_path);		
			}	 			
		}		
				
		if(head==NULL){
			head=(FcNode*)malloc(sizeof(FcNode));    	
			head->elder_brother_node=NULL;							
			tail=head;    			
		}else{
			tmp=(FcNode*)malloc(sizeof(FcNode));    			
			tmp->elder_brother_node=tail;
			tail->brother_node=tmp;
			tail=tmp;    	
		}	       	
		
		//folder or file name
		tail->title=sam_strncpy(namelist[i]->d_name, strlen(namelist[i]->d_name));					
		tail->scale_size=scale_size;
		
		//check entry type, if d->type is 4, it is folder, or is file
		d_type=namelist[i]->d_type;  				
		if(d_type==4) 
		{ 
			*folder_exist_flag=1;
			//if this is folder, tail->this_guid is not null
			tail->this_guid=get_path(d_type, local_dir_path, namelist[i]->d_name);		    										
						
			if(is_top_layer)
			{
				if(strstr(namelist[i]->d_name,"HD_")!=NULL){ 
					str_len=strlen(HD_G);
					local_file_path=sam_strncpy(HD_G, str_len);					
				}else if(strstr(namelist[i]->d_name,"USB_")!=NULL){ 
					str_len=strlen(USB_G);
					local_file_path=sam_strncpy(USB_G, str_len);					
				}else{ 
					str_len=strlen(FOLDER_G);
					local_file_path=sam_strncpy(FOLDER_G, str_len);					
				}	
			}else{
				str_len=strlen(FOLDER_G);
				local_file_path=sam_strncpy(FOLDER_G, str_len);	
			}	
		}else{
			//if this is file, tail->this_guid is null
			tail->this_guid=NULL;
			local_file_path=get_path(d_type, local_dir_path, namelist[i]->d_name);										 
		}
		
		//slide show duration time	
		tail->duration=10;			
		tail->remote_file_path=local_file_path; 			
		if(check_photo_compress(local_file_path)) 
		{
			new_local_file_path=get_file_name_v3(local_file_path, namelist[i]->d_name, PHOTO_TMP_DIR);
			tail->local_file_path=new_local_file_path;										
		}else{	
			str_len=strlen(local_file_path);
			tail->local_file_path=sam_strncpy(local_file_path, str_len);						
		}	
		dprintf("\ntail->local_file_path %s, tail->remote_file_path %s\n", tail->local_file_path, tail->remote_file_path);						
		tail->brother_node=NULL;									 		    				
    }	
    
    //free directory entries        	
	fcfile_free(namelist, node_count); 	
	if(head==NULL&&node_count>0) *folder_exist_flag=-1;
	return head;
}	

//compare node and back_node title, if return value is equal, move head point to node of back_node that title was equal
FcNode *get_fcnode_back(FcNode *node, FcNode *back_node)
{
	FcNode *head=NULL, *tail=NULL;	
	
	head=get_fcnode_head(node);				
	tail=get_fcnode_tail(node);				
	
	while(node!=NULL)
	{
		if(!strcmp(node->title, back_node->title))
		{
			tail->brother_node=head;
			head->elder_brother_node=tail;			
			head=node;
			tail=node->elder_brother_node;
			head->elder_brother_node=NULL;
			tail->brother_node=NULL;						
			break;
		}	
		node=node->brother_node;
	}
	return head;
}	

//create photo tree for photo view function
FcNode* filter_photo_tree(FcNode *node) 
{
	FcNode *head=NULL, *tail=NULL, *tmp=NULL, *old_node=NULL;	
	int i=0;
	
	//old_node include files and folders
	old_node=node;			
	
	//filter out fodlers, we create file tree only
	node=get_fcnode_head(node);			
	while(node!=NULL)
	{		
		if(node->this_guid==NULL)
		{			
			if(head==NULL){								
				head=clone_fcnode(node);														
				head->elder_brother_node=NULL;
				tail=head;
			}else{			
				tmp=clone_fcnode(node);									
				tmp->elder_brother_node=tail;
				tail->brother_node=tmp;						
				tail=tmp;
			}							
			tail->brother_node=NULL;					
		}			
						
		if(i>99) break;		
		node=node->brother_node;			
	}
	
	//compare node and back_node title, if return value is equal, move head point to node of back_node that title was equal	
	head=get_fcnode_back(head, old_node);		
	return head;
}




/*------------------------------
	  icon function
-------------------------------*/

//set window description
void set_windsc_xywh(DFBWindowDescription *dsc, DFBRectangle *gridItem)
{
	dsc->posx   = gridItem->x;
	dsc->posy   = gridItem->y;        
    dsc->width  = gridItem->w;        
    dsc->height = gridItem->h;     
}	

//set icon->winodw and icon->winodw_surface
void set_icon_window(IDirectFBDisplayLayer *main_layer, DFBWindowDescription win_dsc, IconObj *icon){
	main_layer->CreateWindow( main_layer, &win_dsc, &icon->window);               	
   	icon->window->GetSurface( icon->window, &icon->window_surface );     	
   	icon->window_surface->Clear(icon->window_surface, 0, 0, 0, 0);		       	       	
}

//set icon->dsc and icon->icon_path
void set_icon_value(IconObj *icon, char *icon_dsc, char *icon_path, int index)
{
	icon->icon_dsc=NULL;
	icon->icon_path=NULL;
	if(icon_dsc!=NULL) icon->icon_dsc = strdup(icon_dsc);
	if(icon_path!=NULL) icon->icon_path = strdup(icon_path);		
	if(index!=-1) icon->index=index;		
}	
 
void icons_free(IconObj *icon)
{	
	IconObj *head, *tmp;	
		
	head=get_icon_head(icon);		   
	
	while(head!=NULL)
	{
		tmp=head;						
		if(head->icon_dsc!=NULL) free(head->icon_dsc);
		if(head->icon_path!=NULL) free(head->icon_path);
		if(head->window_surface!=NULL) head->window_surface->Release(head->window_surface);
		if(head->window!=NULL)
		{
			head->window->Destroy(head->window);															
			head->window->Release(head->window);
		}
		head=head->right;		
		free(tmp);				
	}				
}	

void icon_opacity(IconObj *icon, int opacity_value)
{	
	IconObj *head;
	
	head=get_icon_head(icon);
	while(head!=NULL)
	{
		head->window->SetOpacity(head->window, opacity_value);					
		head=head->right;
	}			
}

void icon_stackclass(IconObj *icon, DFBWindowStackingClass stack_leve)
{
	IconObj *head;
	
	head=get_icon_head(icon);
	while(head!=NULL)
	{
		head->window->SetStackingClass(head->window, stack_leve);					
		head=head->right;
	}			
}

void icon_clear(IconObj *icon, RgbaType *rgba)
{
	IconObj *head;
	
	head=icon;
	while(head!=NULL)
	{
		head->window_surface->Clear(head->window_surface, rgba->r, rgba->g, rgba->b, rgba->a);					
		head->window_surface->Flip( head->window_surface, NULL, DSFLIP_NONE );
		head=head->right;
	}			
}


IconObj* get_icon_head(IconObj *icon)
{	
	IconObj *head=NULL;
	
	while(icon!=NULL)
	{				
		head=icon;
		icon=icon->left;		
	}		
	
	return head;
}

IconObj* get_icon_tail(IconObj *icon)
{
	IconObj *tail=NULL;
	
	while(icon!=NULL)
	{		
		tail=icon;
		icon=icon->right;
	}	
	return tail;
}

int get_icon_count(IconObj *icon)
{
	IconObj *head;
	int count=0;
	
	head=get_icon_head(icon);	
	
	while(head!=NULL)
	{
		count++;		
		head=head->right;
	}	
	return count;		
}

IconObj* create_icon_tree(GridObj *grid, IDirectFBDisplayLayer *main_layer, DFBWindowDescription win_dsc)
{		
	IconObj *head=NULL, *tail=NULL, *tmp=NULL;	
		
	while(grid!=NULL)
	{				
		if(head==NULL)
		{ 
			head=(IconObj*)malloc(sizeof(IconObj));
			head->left=NULL;										
			tail=head;
		}else{			
			tmp=tail->right;
			tmp=(IconObj*)malloc(sizeof(IconObj));							
			tmp->left=tail;
			tail->right=tmp;
			tail=tmp;									
		}										
		set_windsc_xywh(&win_dsc, grid->rect);   			
		set_icon_window(main_layer, win_dsc, tail);					
		tail->icon_dsc=NULL;	
		tail->icon_path=NULL;
		tail->right=NULL;					
		grid=grid->next;
	}
				
	return head;
}	

void draw_icon_tree(FcNode *node, IconObj *icon, DFBRectangle *icon_space, IDirectFB *gp_dfb)
{ 
	//In this function, node count must biger than icon count				
	icon=get_icon_head(icon);			
	node=get_fcnode_head(node);
	while(icon!=NULL&&node!=NULL)
	{   					
		icon->window_surface->Clear(icon->window_surface, 0, 0, 0, 0);						
		draw_image(node->local_file_path, icon_space, icon->window_surface, gp_dfb);		
		icon->window_surface->Flip(icon->window_surface, NULL, DSFLIP_NONE );				
		node=node->brother_node;										
		icon=icon->right;				
	}		
}	
	

/*-----------------------
	menu function
-----------------------*/

//get node that we selected
FcNode* get_fcnode_selected(int node_count, FcNode *node, int flag)
{		
	FcNode *head;
	
	head=get_fcnode_head(node);
	
	if(node_count==1){ 
		return node;
	}else if(node_count==2){ 
		 if(flag==DIKI_RIGHT)
		 	return node->brother_node;	 
		 else 
		 	return node;		 	
    }else if(node_count>2){     	
    	if(flag==DIKI_LEFT){
    		return node->brother_node;	      
    	}else if(flag==DIKI_RIGHT){
    		return node->brother_node->brother_node->brother_node;	          		
    	}else if(flag==DIKI_ENTER||flag==0){
    		return node->brother_node->brother_node;	      
    	}		
    }	
    return NULL;
}

FcNode* create_menu_tree(char *menu_title[], char *menu_icon_path[])
{	
	FcNode *head=NULL, *tail=NULL, *tmp=NULL;	
	int i;					
	
	for(i=0; strcmp(menu_title[i], "0x")!=0; i++){				
		if(head==NULL){ 
			head=(FcNode*)malloc(sizeof(FcNode));							
			head->elder_brother_node=NULL;
			tail=head;			
		}else{						
			tmp=(FcNode*)malloc(sizeof(FcNode));							
			tmp->elder_brother_node=tail;			
			tail->brother_node=tmp;
			tail=tmp;									
		}								
		tail->this_guid=NULL;		
		tail->title=sam_strncpy(menu_title[i], strlen(menu_title[i]));								
		tail->local_file_path=sam_strncpy(menu_icon_path[i], strlen(menu_icon_path[i]));				
		tail->remote_file_path=NULL;		
		tail->brother_node=NULL;				
	}
		
	return head;	
}

//make a special folder icon that user selected
IconObj* folder_selected(char *file_path, IDirectFB *gp_dfb, IDirectFBDisplayLayer *main_layer, DFBWindowDescription win_dsc)
{					
	DFBRectangle *alert_space;		
	GridObj *grid;		
	IconObj *icon;				
	int grid_count=1;	
															
	win_dsc.caps = DWCAPS_ALPHACHANNEL; 		        			                   	
	alert_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));		
	grid_init(alert_space, 230, 160, 180, 180);									
	grid=create_view_tree(grid_count, alert_space);			
	icon=create_icon_tree(grid, main_layer, win_dsc); 
	grid_init(alert_space, 0, 0, 180, 180);						
	draw_image_scale(file_path, alert_space, icon->window_surface, gp_dfb);			
	icon_stackclass(icon, DWSC_MIDDLE);					
	free(alert_space);
 	grid_free(grid); 	 	
 	return icon;									                                              	  		                  
}

/*-----------------------
	slide function
-----------------------*/
SlideObj* slide_init(GridObj *grid, int slide_step)
{
	GridObj *head;
	SlideObj *slide_info;
	int end_x=0, count=0;
	
	head=grid;	
	slide_info = (SlideObj*)malloc(sizeof(SlideObj));	
	while(head!=NULL)
	{
		count++;
		if(count==1)
		{ 
			slide_info->x = head->rect->x;
			slide_info->y = head->rect->y;
  			slide_info->len = head->rect->w;  	    	  	
		}else{	
			end_x=head->rect->x;
		}	
		head=head->next;
	}						  	
  	slide_info->end_x = end_x;  	
  	slide_info->step=slide_step;  	  		  	
  	return slide_info;
}


void shift_icon_left(IconObj *icon)
{
	IconObj *ihead, *itail, *itmp;
		
	ihead=get_icon_head(icon);	
	itail=get_icon_tail(icon);			
	ihead->left=itail;		
	itail->right=ihead;	
	itmp=itail->left;		
	ihead=itail;
	itail=itmp;
	ihead->left=NULL;
	itail->right=NULL;	
}

void shift_icon_right(IconObj *icon)
{
	IconObj *ihead, *itail, *itmp;
			
	ihead=get_icon_head(icon);
	itail=get_icon_tail(icon);		
	ihead->left=itail;
	itail->right=ihead;
	itmp=ihead->right;	
	itail=ihead;
	ihead=itmp;
	ihead->left=NULL;
	itail->right=NULL;
}
	

void blit_to_frame(FcNode *node, SlideObj *slide_info, IconObj *frame, IconObj *icon, IDirectFB *gp_dfb)
{	
	FcNode *fhead;
	IconObj *head;								
	int i, x, y, icon_count, node_count;	
	
	node_count=get_fcnode_count(node);		
	icon_count=get_icon_count(icon);					
	head=get_icon_head(icon);	
	fhead=get_fcnode_head(node);		
	frame->window_surface->Clear(frame->window_surface, 0, 0 ,0, 0);	
#if SHOW_BIG			
	slide_info->frame3->window_surface->Clear(slide_info->frame3->window_surface, 0, 0 ,0, 0);	
#endif	
	if(node_count==1){
		for(i=0, x=0, y=0; i<icon_count; i++){																								
				if(i==2) frame->window_surface->Blit(frame->window_surface, head->window_surface, NULL, x, y);											
				x=x+slide_info->len;							
		}			
	}else if(node_count==2){
		for(i=0, x=slide_info->len*2, y=0; i<node_count; i++){																																
				frame->window_surface->Blit(frame->window_surface, head->window_surface, NULL, x, y);																																
				x=x+slide_info->len;											
				head=head->right;		
		}			
	}else{				
		for(i=0, x=10, y=0; i<icon_count; i++){					
				frame->window_surface->Blit(frame->window_surface, head->window_surface, NULL, x, y);			
#if SHOW_BIG				
				if(i==2) draw_image(fhead->local_file_path, slide_info->big_icon_space, head->window_surface, gp_dfb);																							
				slide_info->frame3->window_surface->Blit(slide_info->frame3->window_surface, head->window_surface, NULL, x, y);			
				if(i==2) { 					
					head->window_surface->Clear(head->window_surface, 0, 0, 0, 0);
					draw_image(fhead->local_file_path, slide_info->icon_space, head->window_surface, gp_dfb);																			
				}
#endif				
				x=x+slide_info->len;			
				head=head->right;																			
				fhead=fhead->brother_node;
		}			
	}	
	frame->window_surface->Flip(frame->window_surface, NULL, DSFLIP_NONE);	
#if SHOW_BIG					
	slide_info->frame3->window_surface->Flip(slide_info->frame3->window_surface, NULL, DSFLIP_NONE);	
#endif	
}	
	
IconObj* slide_left(FcNode *node, SlideObj *slide_info, IconObj *icon, IDirectFB *gp_dfb)
{
	FcNode *fhead=NULL;
	IconObj *head=NULL, *tmp=NULL;								
	int i, x, y;	
	int node_count, move_len, total_len;
				
	node_count=get_fcnode_count(node);			
	if(node_count>2){			
		slide_info->frame->window->SetOpacity(slide_info->frame->window, 255);	
#if SHOW_BIG					
		slide_info->frame3->window->SetOpacity(slide_info->frame3->window, 0);			
#endif		
		move_len=slide_info->len/slide_info->step;		
		for(i = slide_info->step, total_len=0; i>0; i--){			
			slide_info->frame->window->Move(slide_info->frame->window, move_len, 0);					
			total_len=total_len+move_len;
		}	
		if((move_len=slide_info->len-total_len)>0) slide_info->frame->window->Move(slide_info->frame->window, move_len, 0);												
		shift_fcnode_left(node);
		shift_icon_left(icon);				
		fhead=get_fcnode_head(node);
		head=get_icon_head(icon);									
		draw_image(fhead->local_file_path, slide_info->icon_space, head->window_surface, gp_dfb);									
		blit_to_frame(fhead, slide_info, slide_info->frame2, head, gp_dfb);						
		slide_info->frame2->window->PutAtop(slide_info->frame2->window, slide_info->frame->window);	
		slide_info->frame2->window->SetOpacity(slide_info->frame2->window, 255);
		slide_info->frame->window->SetOpacity(slide_info->frame->window, 0);
		slide_info->frame->window->Move(slide_info->frame->window, -slide_info->len, 0);					
		tmp=slide_info->frame;
		slide_info->frame=slide_info->frame2;
		slide_info->frame2=tmp;			
	}else if(node_count==2){			
		head=get_icon_head(icon);					 							
		slide_info->frame->window_surface->Clear(slide_info->frame->window_surface, 0, 0 ,0, 0);			
		for(i=0, x=slide_info->len*2, y=0; i<node_count; i++){																															
				slide_info->frame->window_surface->Blit(slide_info->frame->window_surface, head->window_surface, NULL, x, y);															
				x=x+slide_info->len;											
				head=head->right;																			
		}	
		slide_info->frame->window_surface->Flip(slide_info->frame->window_surface, NULL, DSFLIP_NONE);								
	}		
	return get_icon_head(icon);		
}


IconObj* slide_right(FcNode *node, SlideObj *slide_info, IconObj *icon, IDirectFB *gp_dfb)
{	
	FcNode *fhead;
	IconObj *head, *tail, *tmp;								
	int i, x, y;	
	int icon_count, node_count,move_len, total_len;
				
	node_count=get_fcnode_count(node);	
	icon_count=get_icon_count(icon);
	
	if(node_count>2){
		slide_info->frame->window->SetOpacity(slide_info->frame->window, 255);		
#if SHOW_BIG									
		slide_info->frame3->window->SetOpacity(slide_info->frame3->window, 0);					
#endif		
		move_len=slide_info->len/slide_info->step;		
		for(i = slide_info->step, total_len=0; i>0; i--){			
			slide_info->frame->window->Move(slide_info->frame->window, -move_len, 0);					
			total_len=total_len+move_len;
		}	
		if((move_len=slide_info->len-total_len)>0) slide_info->frame->window->Move(slide_info->frame->window, -move_len, 0);														
		shift_fcnode_right(node);
		shift_icon_right(icon);						
		fhead=get_fcnode_head(node);	
		for(i=0;i<icon_count-1;i++){
			fhead=fhead->brother_node;
		}		
		tail=get_icon_tail(icon);					
		draw_image(fhead->local_file_path, slide_info->icon_space, tail->window_surface, gp_dfb);					
		blit_to_frame(node, slide_info, slide_info->frame2, tail, gp_dfb);
		slide_info->frame2->window->PutAtop(slide_info->frame2->window, slide_info->frame->window);	
		slide_info->frame2->window->SetOpacity(slide_info->frame2->window, 255);			
		slide_info->frame->window->SetOpacity(slide_info->frame->window, 0);	
		slide_info->frame->window->Move(slide_info->frame->window, slide_info->len, 0);					
		tmp=slide_info->frame;
		slide_info->frame=slide_info->frame2;
		slide_info->frame2=tmp;			
	}else if(node_count==2){
		head=get_icon_head(icon);									
		slide_info->frame->window_surface->Clear(slide_info->frame->window_surface, 0, 0 ,0, 0);			
		for(i=0, x=slide_info->len, y=0; i<node_count; i++){																												
				slide_info->frame->window_surface->Blit(slide_info->frame->window_surface, head->window_surface, NULL, x, y);						
				head=head->right;																							
				x=x+slide_info->len;							
		}				
		slide_info->frame->window_surface->Flip(slide_info->frame->window_surface, NULL, DSFLIP_NONE);					
	}			
	return get_icon_head(icon);	
}

//slide show function
void view_player(ViewObj *view)
{									
	FcNode *head=NULL;
	DFBInputEvent event;
	IDirectFBEventBuffer *p_eventbuffer;	
	int duration;
	int flag;
		
	p_eventbuffer = view->p_eventbuffer;	
	head=view->node;	
	flag=view->flag;
	event.clazz = DFEC_INPUT;
	event.type = DIET_KEYPRESS;
	event.key_id = DIKI_V;				
		
	duration = head->duration;	
	//duration = 2;		
	if(duration<=0) duration=10;	
	dprintf("\nview player, flag %d, wait filename->%s, duration %d\n", flag, head->local_file_path, duration);						
	if(flag==1) sleep(duration);							
	p_eventbuffer->PostEvent (p_eventbuffer, DFB_EVENT(&event));																																	
}

void* view_player_r(void *arg)
{
	pthread_detach(pthread_self());
	ViewObj *view;	
	view=(ViewObj*)arg;
	view_player(view);	
	pthread_exit(NULL);
}	

void pthread_cancel_msg(int thread_flag)
{
	if(thread_flag==0) dprintf("\ncancel success\n");																
	else if(thread_flag==ESRCH) dprintf("\nESRCH\n");
	else dprintf("\ncancel fail\n");
}

void pthread_create_msg(int thread_flag)
{
	if(thread_flag==0) dprintf("\nthread create success\n");
	else if(thread_flag==EAGAIN) dprintf("\nEAGAIN\n");
	else if(thread_flag==ENOMEM) dprintf("\nENOMEM\n");	
}	

/**********************************************
		Text Function
***********************************************/





TextObj* get_text_head(TextObj *text)
{	
	TextObj *head=NULL;
	
	while(text!=NULL){				
		head=text;
		text=text->left;		
	}		
	
	return head;
}

TextObj* get_text_tail(TextObj *text)
{
	TextObj *tail=NULL;
	
	while(text!=NULL){		
		tail=text;
		text=text->right;
	}	
	return tail;
}

int get_text_count(TextObj *text)
{
	TextObj *head;
	int count=0;
	
	head=get_text_head(text);	
	
	while(head!=NULL){
		count++;		
		head=head->right;
	}	
	return count;		
}

void texts_free(TextObj *text)
{	
	TextObj *head, *tmp;	
		
	head=get_text_head(text);		   	
	while(head!=NULL)
	{
		tmp=head;		
		if(head->content!=NULL) free(head->content);										
		head=head->right;		
		free(tmp);				
	}				
}

void texts_content_clear(TextObj *text)
{	
	TextObj *head=NULL;	
		
	head=get_text_head(text);		   	
	while(head!=NULL)
	{		
		dprintf("\nhead->content %s\n", head->content);
		head->content=NULL;
		head=head->right;				
	}				
}

TextObj* create_text_node_tree(GridObj *grid)
{
	TextObj *head=NULL, *tail=NULL, *tmp=NULL;	
	int i=0;
		
	while(grid!=NULL)
	{				
		if(head==NULL){ 
			head=(TextObj*)malloc(sizeof(TextObj));
			head->left=NULL;										
			tail=head;
		}else{			
			tmp=tail->right;
			tmp=(TextObj*)malloc(sizeof(TextObj));							
			tmp->left=tail;
			tail->right=tmp;
			tail=tmp;									
		}																
		tail->index=i;
		tail->content=NULL;			
		tail->text_space = grid->rect;		
		dprintf("\ntail->text_space->x %d, tail->text_space->y %d\n", tail->text_space->x, tail->text_space->y);
		tail->right=NULL;					
		grid=grid->next;
	}
				
	return head;	
}	

void upnp_text_node_map(UPnPNode *uhead, TextObj *thead)
{	
	char *content=NULL;
	int len=0;
	
	while(thead!=NULL&&uhead!=NULL)
	{				
		thead->index = uhead->index;
		if(uhead->index!=0) 
		{
			len=strlen(uhead->service_name);
			len=len+10;
			content=(char*)malloc(len*sizeof(char));
			memset( content, 0, len);		
			sprintf(content,"%d) %s", uhead->index, uhead->service_name);															
			thead->content = content;
		}else{
			thead->content = sam_strncpy(uhead->service_name, strlen(uhead->service_name));
		}	
		uhead = uhead->brother_node;
		thead = thead->right;
	}	  		
}	
	
void draw_text_table(TextObj *head, IDirectFBSurface *surface)
{
	DFBRectangle *text_space;
	IDirectFBFont *font;	
	RgbaType *text_rga;	  			
	int i=0;
		
  	font = (IDirectFBFont*)InitFont(34);
	text_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	text_rga = (RgbaType*)malloc(sizeof(RgbaType));					
	while(head!=NULL)
	{								
		if(head->content==NULL) break;						
		if(i==0) set_rgba(text_rga, 0x7D, 0xC2, 0xF4, 255);	
		else set_rgba(text_rga, 255, 255, 255, 255);												
		draw_text(head->text_space, head->content, font, DSTF_LEFT, text_rga, surface);
		head = head->right;
		i++;
	}
	surface->Flip( surface, NULL, DSFLIP_NONE );	
	font->Release(font);
	free(text_rga);	
	free(text_space);		
}	


void shift_text_left(TextObj **head, IDirectFBSurface *surface)
{	
	DFBRectangle *text_space;
	IDirectFBFont *font;	
	RgbaType *text_rga;	  				
	TextObj *tmp;
	
	tmp=*head;	
	font = (IDirectFBFont*)InitFont(34);
	text_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	text_rga = (RgbaType*)malloc(sizeof(RgbaType));			
	set_rgba(text_rga, 255, 255, 255, 255);	
	draw_text(tmp->text_space, tmp->content, font, DSTF_LEFT, text_rga, surface);
	tmp=tmp->left;	
	*head=tmp;
	set_rgba(text_rga, 0x7D, 0xC2, 0xF4, 255);	
	draw_text(tmp->text_space, tmp->content, font, DSTF_LEFT, text_rga, surface);
	surface->Flip( surface, NULL, DSFLIP_NONE );	
	font->Release(font);
	free(text_rga);	
	free(text_space);			
}

void shift_text_right(TextObj **head, IDirectFBSurface *surface)
{	
	DFBRectangle *text_space;
	IDirectFBFont *font;	
	RgbaType *text_rga;	  				
	TextObj *tmp;
	
	tmp=*head;		
	font = (IDirectFBFont*)InitFont(34);
	text_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	text_rga = (RgbaType*)malloc(sizeof(RgbaType));			
	set_rgba(text_rga, 255, 255, 255, 255);	
	draw_text(tmp->text_space, tmp->content, font, DSTF_LEFT, text_rga, surface);
	tmp=tmp->right;	
	*head=tmp;
	set_rgba(text_rga, 0x7D, 0xC2, 0xF4, 255);	
	draw_text(tmp->text_space, tmp->content, font, DSTF_LEFT, text_rga, surface);
	surface->Flip( surface, NULL, DSFLIP_NONE );	
	font->Release(font);
	free(text_rga);	
	free(text_space);			
}

void go_next_page(UPnPNode *unode, TextObj *tnode, IDirectFBSurface *surface)
{	
	texts_content_clear(tnode);	
	surface->Clear(surface, 0, 0, 0, 0);
	upnp_text_node_map(unode, tnode); 			
	draw_text_table(tnode, surface);
	surface->Flip( surface, NULL, DSFLIP_NONE );	
}	
	
void go_prev_page(int page_size, UPnPNode **unode, TextObj *tnode, IDirectFBSurface *surface)
{	
	int i;
	
	texts_content_clear(tnode);	
	surface->Clear(surface, 0, 0, 0, 0);
	for(i=0; i<page_size; i++)
	{		
		*unode=(*unode)->elder_brother_node;		
	}	
	upnp_text_node_map(*unode, tnode); 			
	draw_text_table(tnode, surface);
	surface->Flip( surface, NULL, DSFLIP_NONE );	
}	
