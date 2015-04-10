#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stddef.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <directfb.h>
#include <sys/stat.h>
#include "alpha_dfb_define.h"
#include "nas_str_define.h"
#include "draw_tool.h"
#include "file_tool.h"
#include "menu_tool.h"
#include "fcrss_parser.h"
#include "fcrss_command.h"
#include "fcrss_serialize.h"
#include "str_tool.h"
#include "alert_center.h"
#include "detect_info.h"
#include "application.h"
#include "fcrss_handler.h"

//start extern variable or function from main.c
extern DFBRectangle *menu_icon_space, *title_space;
extern GridObj *grid;
extern IDirectFB *gp_dfb;
extern IDirectFBSurface *title_window_surface;
extern IDirectFBFont *font_title;	
extern IconObj *icon;
extern RgbaType *rgba;
extern SlideObj *slide_info;
extern int GetInputDeviceEventByType(IDirectFBEventBuffer *p_eventbuffer, int PType); 

//extern variable from fcrss_handler.c
extern FcNode *fclist_node;

pthread_mutex_t f_mutex= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t f_cond = PTHREAD_COND_INITIALIZER;
int pthread_num_f=0;
static char *menu_title[]={TITLE_RESET_CHANNEL,TITLE_CHANNEL_UPDATA,TITLE_CHANNELS_DISPLAY, "0x"};
static char *menu_icon_path[]={SET_3_G, APP_6_G, APP_5_G,"0x"};

void FrameChannel_Menu(IDirectFBEventBuffer *p_eventbuffer, int first_app_exe)
{					
	FcNode *head=NULL, *tail=NULL, *framechannel_node=NULL, *target_node=NULL;	
	int key=0, grid_count=0, node_count=0, serv_response=0, opacity=0;
	char *icon_select=NULL;		
	         
	restart: //goto point 	
	icon_alert(PHOTO_LOADING_G, D_MOVE_CENTER);	            						
	serv_response = client_cmd_handler(p_eventbuffer, CHANNEL_LIST_GET, NULL);
	close_icon_alert();
		
	switch(serv_response)
	{						
		case WAN_ERROR:		
			alert_cmd_handler(p_eventbuffer, WAN_ERROR);	
			return;	
		case DNS_ERROR:		
			alert_cmd_handler(p_eventbuffer, DNS_ERROR);	
			return;		
		case UNIXSOCK_FAIL:
			fclist_node=delete_fcnode_tree(framechannel_node);
			return;					
		case REQ_FAIL:
			framechannel_node=create_menu_tree(menu_title, menu_icon_path);	
			fclist_node=framechannel_node;
			first_app_exe=2; //avoid recheck register status			
			break;
		case REQ_SUCCESS:
			framechannel_node=create_menu_tree(menu_title, menu_icon_path);	
			tail=get_fcnode_tail(framechannel_node);
			head=get_fcnode_head(fclist_node);								
			head->elder_brother_node=tail;
			tail->brother_node=head;
			fclist_node=framechannel_node;
			break;		
		default:						
			break;			
	}		
		
	//dprintf("\nfirst_app_exe %d\n", first_app_exe);			  			
	head=get_fcnode_head(fclist_node);				
	grid_count=get_grid_count(grid);
	node_count=get_fcnode_count(fclist_node);		
	if(node_count < grid_count&&node_count > 2) clone_fctree(fclist_node);	
			
	redraw: //goto point
	grid_init(menu_icon_space, 10, 10, 180, 180); 		
	draw_icon_tree(fclist_node, icon, menu_icon_space, gp_dfb);	
	slide_info->frame->window->SetOpacity(slide_info->frame->window, 0);			      	                             
	blit_to_frame(fclist_node, slide_info, slide_info->frame, icon, gp_dfb);
	if(first_app_exe==1) opacity=0;
	else opacity=255;
	slide_info->frame->window->SetOpacity(slide_info->frame->window, opacity);	
	target_node=get_fcnode_selected(node_count, fclist_node, 0);
    icon_select=target_node->title;    	
    draw_title_string(icon_select, font_title, rgba, title_space, title_window_surface);     	                                             	                        
    if(first_app_exe==1) 
	{		
		first_app_exe++;											
		goto first_app;			
	}	       
	while(1){            
		key = GetInputDeviceEventByType(p_eventbuffer, PTYPE_DEFAULT_API);  			           							
     	if( key == DIKI_UP ){      		
 			client_cmd_handler(p_eventbuffer, CHANNEL_LIST_THREAD_STOP, NULL);      			     				
 			grid_init(menu_icon_space, 10, 10, 180, 230);      						
 			fclist_node=delete_fcnode_tree(fclist_node);     			     			     			
 			return;	             			           																																			
		}else if( key == DIKI_LEFT ){					   
			target_node=get_fcnode_selected(node_count, fclist_node, key);
    		icon_select=target_node->title; 
			draw_title_string(icon_select, font_title, rgba, title_space, title_window_surface);     	  	    
			icon=slide_left(fclist_node, slide_info, icon, gp_dfb);	
			fclist_node=get_fcnode_head(fclist_node);					
		}else if( key == DIKI_RIGHT ){			
			target_node=get_fcnode_selected(node_count, fclist_node, key);
    		icon_select=target_node->title; 	
			draw_title_string(icon_select, font_title, rgba, title_space, title_window_surface);     	  	
			icon=slide_right(fclist_node, slide_info, icon, gp_dfb);
			fclist_node=get_fcnode_head(fclist_node);								
		}else if( key == DIKI_ENTER ){								 														         																														
			slide_info->frame->window->SetOpacity(slide_info->frame->window, 0);																									
			if(!strcmp(icon_select,TITLE_CHANNELS_DISPLAY)) {	
				first_app:														
				Channels_Display_App(p_eventbuffer);							
			}else if(!strcmp(icon_select,TITLE_CHANNEL_UPDATA)) {															
				if(Channels_Update_App(p_eventbuffer)==REQ_SUCCESS) goto restart;
			}else if(!strcmp(icon_select,TITLE_RESET_CHANNEL)){								
				if(Reset_Frameid_App(p_eventbuffer)==REQ_SUCCESS) goto restart;
			}else{
				Channel_App(p_eventbuffer, target_node);									
			}
			grid_init(menu_icon_space, 10, 10, 180, 180);				
			target_node=get_fcnode_selected(node_count, fclist_node, key);
    		icon_select=target_node->title; 	
			draw_title_string(icon_select, font_title, rgba, title_space, title_window_surface);
			draw_icon_tree(fclist_node, icon, menu_icon_space, gp_dfb);		
			blit_to_frame(fclist_node, slide_info, slide_info->frame, icon, gp_dfb);										
			slide_info->frame->window->SetOpacity(slide_info->frame->window, 255);																																																																										
		}else if( key == DIKI_A || key == DIKI_B ){					
			Detect_USBMount(p_eventbuffer);
			goto redraw;					
		}
		p_eventbuffer->Reset(p_eventbuffer);					
	}	    				                        
}



