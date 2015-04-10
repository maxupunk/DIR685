#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stddef.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <directfb.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include "alpha_dfb_define.h"
#include "nas_str_define.h"
#include "draw_tool.h"
#include "file_tool.h"
#include "str_tool.h"
#include "menu_tool.h"
#include "fcrss_parser.h"
#include "alert_center.h"
#include "detect_info.h"
#include "download_tool.h"
#include "compress_tool.h"
#include <sys/resource.h>

//extern variable from main.c
extern IDirectFB *gp_dfb;
extern IDirectFBDisplayLayer *main_layer;
extern IDirectFBSurface *title_window_surface;
extern IDirectFBFont *font_title;	
extern DFBWindowDescription win_dsc;
extern DFBRectangle *title_space, *screen_space, *menu_icon_space;
extern RgbaType *rgba, *rgba2;
extern SlideObj *slide_info;
extern GridObj *grid;
extern IconObj *icon;
extern int GetInputDeviceEventByType(IDirectFBEventBuffer *p_eventbuffer, int PType);   

pthread_mutex_t p_mutex= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t p_cond = PTHREAD_COND_INITIALIZER;
int pthread_num=0;

void photo_view(IDirectFBEventBuffer *p_eventbuffer, FcNode *album_node, int album_node_count)
{	
	FcNode *photo_node=NULL;
	DownloadObj *dobj;
	GridObj *grid;
	IconObj *icon;		
	ViewObj *view;	
	pthread_t tid[2];	
	struct timespec ts;
	int key = 0, grid_count=1, node_count=0, compress_count=4;	
	int thread_flag=0;
	
	pthread_num=0;
		
	//create loading icon
	icon_alert(PHOTO_LOADING_G, D_MOVE_CENTER);			         
		 
	//create photo node tree, and get photo node count	
	photo_node=filter_photo_tree(album_node);	   			
	node_count=get_fcnode_count(photo_node);      	  					
		
	//create one window to show photo
    win_dsc.caps = DWCAPS_NONE;     	
	grid=create_view_tree(grid_count, screen_space);		 		
	icon=create_icon_tree(grid, main_layer, win_dsc);				
	
	//if photo is too big, we will compress it		
	if(!check_file_exist(photo_node->local_file_path)) 
	{		
		jpeg_compress(photo_node->remote_file_path, photo_node->local_file_path, photo_node->scale_size);		
	}			
	
	//clear tilte word
	title_window_surface->Clear(title_window_surface, 0, 0 ,0 ,0);  	
			
	//draw first photo, set window opacity and position of window stack 
	draw_image_scale(photo_node->local_file_path, screen_space, icon->window_surface, gp_dfb);
	icon_opacity(icon, 255);	  	    								
	icon_stackclass(icon, DWSC_MIDDLE);	   	
	
	//close loading icon
	close_icon_alert();	
	
	//create CompressObj for compress thread(thread id is tid[0])
	dobj=(DownloadObj*)malloc(sizeof(DownloadObj));
	dobj->node=photo_node;
	dobj->d_count=compress_count;
	dobj->d_flag=1;	
		
	//create ViewObj for slide-show thread(thread id is tid) to display photos 
	view=(ViewObj*)malloc(sizeof(ViewObj));
	view->p_eventbuffer=p_eventbuffer;
	view->node=photo_node;		
	view->flag=1;		
	pthread_create(&tid[1], NULL, &view_player_r, view);	
		
	while(1)
	{            		
		key = GetInputDeviceEventByType(p_eventbuffer, PTYPE_NOSCREEN_API);
 		if( key == DIKI_UP ){	    
 			//delete slide show thread
			dprintf("\ndelete old slide show thread by tid %d\n", (int)tid[1]);
			thread_flag=pthread_cancel(tid[1]);
			pthread_cancel_msg(thread_flag);
			 			
 			free(view);     	
 			free(dobj); 					
 			grid_free(grid);  		
 			icons_free(icon);     	     				     			
 			photo_node=delete_fcnode_tree(photo_node);    			     			
 			win_dsc.caps = DWCAPS_ALPHACHANNEL;   	     			
 			return;	             			           												
		}else if( key == DIKI_LEFT && node_count>1){		
			//delete slide show thread
			dprintf("\ndelete old slide show thread by tid %d\n", (int)tid[1]);
			thread_flag=pthread_cancel(tid[1]);
			pthread_cancel_msg(thread_flag);
							
			//move left
			shift_fcnode_left(photo_node);
			photo_node=get_fcnode_head(photo_node);	
			
			//create left-compress thread
			if(pthread_num<2)
			{			
				dobj->node=photo_node;		
				dobj->d_flag=0;		
				
				ts.tv_sec=time(NULL)+60;
				thread_flag=pthread_create(&tid[0], NULL, &fc_compress_r, dobj);
		        pthread_create_msg(thread_flag);	           		                        		       						
				pthread_mutex_lock(&p_mutex);	
				dprintf("\nbefore cond wait\n");																										
				if(pthread_num!=0) pthread_cond_timedwait(&p_cond, &p_mutex, &ts);				
				dprintf("\nafter cond wait\n");					
				pthread_mutex_unlock(&p_mutex);		
			}	
			
			
			icon->window_surface->Clear(icon->window_surface, 0, 0, 0, 0);									
			draw_image_scale(photo_node->local_file_path, screen_space, icon->window_surface, gp_dfb);
			icon->window_surface->Flip(icon->window_surface, NULL, DSFLIP_NONE );
			dprintf("\nphoto_node->local_file_path %s\n", photo_node->local_file_path);	
							
			p_eventbuffer->Reset(p_eventbuffer);													
		}else if( key == DIKI_RIGHT && node_count>1){								
			//delete slide show thread
			dprintf("\ndelete old slide show thread by tid %d\n", (int)tid[1]);
			thread_flag=pthread_cancel(tid[1]);
			pthread_cancel_msg(thread_flag);
			
			 //move right	
			shift_fcnode_right(photo_node);
			photo_node=get_fcnode_head(photo_node);	
			
			//create right-compress thread
			if(pthread_num<2)
			{								
				dobj->node=photo_node;			
				dobj->d_flag=1;	
				
				ts.tv_sec=time(NULL)+60;
				thread_flag=pthread_create(&tid[0], NULL, &fc_compress_r, dobj);			
				pthread_create_msg(thread_flag);																		
				pthread_mutex_lock(&p_mutex);	
				dprintf("\nbefore cond wait\n");																										
				if(pthread_num!=0) pthread_cond_timedwait(&p_cond, &p_mutex, &ts);				
				dprintf("\nafter cond wait\n");									
				pthread_mutex_unlock(&p_mutex);																					
			}	
						
			icon->window_surface->Clear(icon->window_surface, 0, 0, 0, 0);									
			draw_image_scale(photo_node->local_file_path, screen_space, icon->window_surface, gp_dfb);
			icon->window_surface->Flip(icon->window_surface, NULL, DSFLIP_NONE );
			dprintf("\nphoto_node->local_file_path %s\n", photo_node->local_file_path);	
											
			p_eventbuffer->Reset(p_eventbuffer);		
		}else if( key == DIKI_V && node_count>1){	
			//move right
			shift_fcnode_right(photo_node);
			photo_node=get_fcnode_head(photo_node);				
							
			//create right-compress thread
			if(pthread_num<2)
			{								
				dobj->node=photo_node;			
				dobj->d_flag=1;	
				
				ts.tv_sec=time(NULL)+60;
				thread_flag=pthread_create(&tid[0], NULL, &fc_compress_r, dobj);			
				pthread_create_msg(thread_flag);							
				pthread_mutex_lock(&p_mutex);	
				dprintf("\nbefore cond wait\n");		
				if(pthread_num!=0) pthread_cond_timedwait(&p_cond, &p_mutex, &ts);																												
				dprintf("\nafter cond wait\n");									
				pthread_mutex_unlock(&p_mutex);																								
			}	
							
			icon->window_surface->Clear(icon->window_surface, 0, 0, 0, 0);									
			draw_image_scale(photo_node->local_file_path, screen_space, icon->window_surface, gp_dfb);
			icon->window_surface->Flip(icon->window_surface, NULL, DSFLIP_NONE );							
			dprintf("\nphoto_node->local_file_path %s\n", photo_node->local_file_path);			
			
			//run slide show 			
			view->node=photo_node;									
			pthread_create(&tid[1], NULL, &view_player_r, view);											
		}else if( key == DIKI_DOWN && node_count>1){
			//delete slide show thread
			dprintf("\ndelete old slide show thread by tid %d\n", (int)tid[1]);
			thread_flag=pthread_cancel(tid[1]);
			pthread_cancel_msg(thread_flag);
			
			p_eventbuffer->Reset(p_eventbuffer);	
			view->node=photo_node;					
			pthread_create(&tid[1], NULL, &view_player_r, view);											
		}				
	}		    				         	
}	

int Album_Local_App(IDirectFBEventBuffer *p_eventbuffer, char *storage_dev_path, int is_top_layer, IconObj *folder)
{					
	DownloadObj *dobj=NULL;
	FcNode *album_node=NULL, *target_node=NULL;		
	pthread_t tid[2];		
	struct timespec ts;
	int key=0, grid_count=0, node_count=0, not_empty_node=0, compress_count=4, thread_flag=0, folder_exist_flag=0;		
	char *icon_select=NULL, *local_file_path=NULL;	
				
	//create loading icon									
	icon_alert(PHOTO_LOADING_G, D_MOVE_CENTER);	
	
	//create album node tree that include directorys and photos. 
	//is_top_layer can control UI style, set 1 will UI show HD or USB icon, set 0 will show folder or photo 	
	album_node=create_fcfile_tree(storage_dev_path, is_top_layer, &folder_exist_flag, gp_dfb);	
	if(album_node==NULL)
	{		
		close_icon_alert();	
		if(folder_exist_flag==-1) Alert_Center(p_eventbuffer, IMAGE_UNSUPPORT_ALERT);					
		else Alert_Center(p_eventbuffer, ALBUM_ALERT);			
		return 0;
	}
	
	//create directory to cache photos that had compressed	
	system("rm -rf /tmp/.photo/*");									
	
	//create icon node to show photos and directorys in storage device
	grid_init(menu_icon_space, 10, 10, 180, 180); 	
	node_count = get_fcnode_count(album_node);					
	grid_count = get_grid_count(grid);				
	if(node_count<grid_count&&node_count>2) clone_fctree(album_node);
	if(!folder_exist_flag)
	{ 		
		close_icon_alert();			
		usleep(80000);
		slide_info->frame->window_surface->Clear(slide_info->frame->window_surface, 0, 0 ,0, 0);					
		photo_view(p_eventbuffer, album_node, node_count);					
		icon_alert(PHOTO_LOADING_G, D_MOVE_CENTER);						
	}	
	//compress photo	
	fc_compress_init(album_node, compress_count);	
		
	//draw photo or directory					
	draw_icon_tree(album_node, icon, menu_icon_space, gp_dfb);
	blit_to_frame(album_node, slide_info, slide_info->frame, icon, gp_dfb);		
	slide_info->frame->window->SetOpacity(slide_info->frame->window, 255);		
			
	//draw title string, maybe photo file name, or directory name 
    target_node=get_fcnode_selected(node_count, album_node, key);    
    if(!strcmp(target_node->local_file_path, FOLDER_G)) folder->window->SetOpacity(folder->window, 255);	
    icon_select=target_node->title;        
    draw_title_string(icon_select, font_title, rgba, title_space, title_window_surface);   	 	                       
    //close loading icon
	close_icon_alert();	
	//create DownloadObj for compress thread(thread id is tid[0])
	dobj=(DownloadObj*)malloc(sizeof(DownloadObj));
	dobj->node=album_node;
	dobj->d_count=compress_count;
	dobj->d_flag=1;	
			    
	while(1)
	{            
		key = GetInputDeviceEventByType(p_eventbuffer, PTYPE_DEFAULT_API);   
		 			           							
     	if( key == DIKI_UP ){	     			 				       		
 			folder->window->SetOpacity(folder->window, 0);	 			 		
 			free(dobj); 	
 			album_node=delete_fcnode_tree(album_node);    			 					
 			slide_info->frame->window_surface->Clear(slide_info->frame->window_surface, 0 ,0 , 0, 0);       	     					    			   			 			     			 			
 			grid_init(menu_icon_space, 10, 10, 180, 230);    
 			system("rm -rf /tmp/.photo/*");	 	 							
 			return 1;	             			           																	
		}else if( key == DIKI_LEFT && node_count>1){		
			dprintf("\nleft right\n");									
			//hide folder direction 
			folder->window->SetOpacity(folder->window, 0);						
			target_node=get_fcnode_selected(node_count, album_node, key);										
						
			//create left-compress thread
			if(pthread_num<2)
			{			
				dobj->node=target_node;		
				dobj->d_flag=0;		
				
				ts.tv_sec=time(NULL)+60;		
				thread_flag=pthread_create(&tid[0], NULL, &fc_compress_r, dobj);
		        pthread_create_msg(thread_flag);	           		                        		       						
				pthread_mutex_lock(&p_mutex);		
				if(pthread_num!=0) pthread_cond_timedwait(&p_cond, &p_mutex, &ts);																	
				pthread_mutex_unlock(&p_mutex);	
			}	
			
			//draw title string, maybe photo file name, or directory name 
    		icon_select=target_node->title;
			draw_title_string(icon_select, font_title, rgba, title_space, title_window_surface);     			
			
			//move left
			icon=slide_left(album_node, slide_info, icon, gp_dfb);				
			album_node=get_fcnode_head(album_node);	
									
			//if user selected item that is folder, it will show folder direction 									
			if(!strcmp(target_node->local_file_path, FOLDER_G)) folder->window->SetOpacity(folder->window, 255);
			
			dprintf("\nleft end\n");			
		}else if( key == DIKI_RIGHT && node_count>1){																	
			//hide folder direction 
			folder->window->SetOpacity(folder->window, 0);   		
			
			target_node=get_fcnode_selected(node_count, album_node, key);	
									
			//create right-compress thread
			if(pthread_num<2)
			{								
				dobj->node=target_node;			
				dobj->d_flag=1;		
				
				ts.tv_sec=time(NULL)+60;			
				thread_flag=pthread_create(&tid[0], NULL, &fc_compress_r, dobj);			
				pthread_create_msg(thread_flag);																					
				pthread_mutex_lock(&p_mutex);	
				if(pthread_num!=0)  pthread_cond_timedwait(&p_cond, &p_mutex, &ts);				
				pthread_mutex_unlock(&p_mutex);																								
			}	
			
			//draw title string, maybe photo file name, or directory name 					
    		icon_select=target_node->title;
			draw_title_string(icon_select, font_title, rgba, title_space, title_window_surface);     	
			
			//move right
			icon=slide_right(album_node, slide_info, icon, gp_dfb);		
			album_node=get_fcnode_head(album_node);						
			
			//if user selected item that is folder, it will show folder direction 									
			if(!strcmp(target_node->local_file_path, FOLDER_G)) folder->window->SetOpacity(folder->window, 255);												
		}else if( key == DIKI_ENTER ){								
			icon_select = target_node->title;
													
			//target_node->this_guid is NULL, mean the item is photo			
			if(target_node->this_guid==NULL)
			{																						
				//start photo view 
				photo_view(p_eventbuffer, target_node, node_count);																
				
				//we should redraw title in this photo after finishing photo view		
	    		draw_title_string(icon_select, font_title, rgba, title_space, title_window_surface);   	 	          
			}else{																																																
				//hide folder direction
				folder->window->SetOpacity(folder->window, 0);									
				is_top_layer=0;
				
				//enter sub directory 				
				local_file_path = (char*)sam_strncpy(target_node->this_guid, strlen(target_node->this_guid));				
				not_empty_node=Album_Local_App(p_eventbuffer, local_file_path, is_top_layer, folder);												 																														
				free(local_file_path);							
				
				//we should redraw this directory's interface after entering sub directory 
				if(not_empty_node==1)
				{													
					icon_alert(PHOTO_LOADING_G, D_MOVE_CENTER);							
					grid_init(menu_icon_space, 10, 10, 180, 180);														
					target_node=get_fcnode_selected(node_count, album_node, key);					
		    		icon_select=target_node->title;    		    		
		    		draw_title_string(icon_select, font_title, rgba, title_space, title_window_surface);   	 	          		    				    				    		
		    		fc_compress_init(album_node, compress_count);		    				    				    					    				    		
					draw_icon_tree(album_node, icon, menu_icon_space, gp_dfb);														
					blit_to_frame(album_node, slide_info, slide_info->frame, icon, gp_dfb);			
					slide_info->frame->window->SetOpacity(slide_info->frame->window, 255);
					dprintf("\nalbum_node->local_file_path %s\n", target_node->local_file_path);
					if(!strcmp(target_node->local_file_path, FOLDER_G)) folder->window->SetOpacity(folder->window, 255);	
					close_icon_alert();
				}else{
					if(!strcmp(target_node->local_file_path, FOLDER_G)) folder->window->SetOpacity(folder->window, 255);	
				}
					
			}
		}		
		p_eventbuffer->Reset(p_eventbuffer);				
	}    				                        
}
