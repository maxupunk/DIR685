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
#include "file_tool.h"
#include "draw_tool.h"
#include "menu_tool.h"		
#include "detect_info.h"
#include "application.h"

//start extern variable or function from main.c
extern IDirectFB *gp_dfb;
extern IDirectFBDisplayLayer *main_layer;
extern IDirectFBSurface *title_window_surface;
extern IDirectFBFont *font_title;	
extern DFBRectangle *menu_icon_space, *title_space;
extern RgbaType *rgba, *rgba2;
extern SlideObj *slide_info;
extern GridObj *grid;
extern IconObj *icon;
extern int GetInputDeviceEventByType(IDirectFBEventBuffer *p_eventbuffer, int PType);  
//end extern variable or function from main.c
FcNode *status_node;
static char *menu_title[]={TITLE_WIRELESS_STATUS,TITLE_HD_STATUS,TITLE_ROUTER_STATUS,TITLE_INTERNET_STATUS,TITLE_WIRED_STATUS, "0x"};//"Download Tasks"
static char *menu_icon_path[]={STAT_5_G, STAT_1_G, STAT_2_G, STAT_3_G, STAT_4_G, "0x"};//STAT_0_G

void Status_Menu(IDirectFBEventBuffer *p_eventbuffer)
{					
	int key=0; 							
	char *icon_select;
				  	        									                                                                                                        
//start draw menu_list init	                               
	status_node=create_menu_tree(menu_title, menu_icon_path);				
	draw_icon_tree(status_node, icon, menu_icon_space, gp_dfb);		
	blit_to_frame(status_node, slide_info, slide_info->frame, icon, gp_dfb);
	slide_info->frame->window->SetOpacity(slide_info->frame->window, 255);							      	                             
//end draw menu_list init		                 	           	                             
    icon_select = status_node->brother_node->brother_node->title;	
    draw_title_string(icon_select, font_title, rgba, title_space, title_window_surface);   	 	                                             	                        
	while(1){            
		key = GetInputDeviceEventByType(p_eventbuffer, PTYPE_DEFAULT_API); 			           							
     		if( key == DIKI_UP ){	     			
     			status_node=delete_fcnode_tree(status_node);
     			return;	             			           																	
		}else if( key == DIKI_LEFT ){				   
			icon_select = status_node->brother_node->title;	
			draw_title_string(icon_select, font_title, rgba, title_space, title_window_surface);     	  	    
			icon=slide_left(status_node, slide_info, icon, gp_dfb);	
			status_node=get_fcnode_head(status_node);											
		}else if( key == DIKI_RIGHT ){									   
		   	icon_select = status_node->brother_node->brother_node->brother_node->title;																	
			draw_title_string(icon_select, font_title, rgba, title_space, title_window_surface);     	  	
			icon=slide_right(status_node, slide_info, icon, gp_dfb);
			status_node=get_fcnode_head(status_node);											
		}else if( key == DIKI_ENTER ){								
			icon_select = status_node->brother_node->brother_node->title;				
			slide_info->frame->window->SetOpacity(slide_info->frame->window, 0);				
			if(!strcmp(icon_select,TITLE_ROUTER_STATUS)) {									
				Show_Router_Info(p_eventbuffer, 0);				
			}else if(!strcmp(icon_select,TITLE_INTERNET_STATUS)) {				
				Show_Router_Info(p_eventbuffer, 1);
			}else if(!strcmp(icon_select,TITLE_WIRED_STATUS)) {				
				Show_Router_Info(p_eventbuffer, 2);
			}else if(!strcmp(icon_select,TITLE_WIRELESS_STATUS)) {				
				Show_Router_Info(p_eventbuffer, 3);
			}else if(!strcmp(icon_select,TITLE_HD_STATUS)) {				
				Show_Router_Info(p_eventbuffer, 4);
			}																		
			redraw:
			draw_title_string(icon_select, font_title, rgba, title_space, title_window_surface);
			draw_icon_tree(status_node, icon, menu_icon_space, gp_dfb);
			blit_to_frame(status_node, slide_info, slide_info->frame, icon, gp_dfb);			
			slide_info->frame->window->SetOpacity(slide_info->frame->window, 255);													
		}else if( key == DIKI_A || key == DIKI_B ){					
			Detect_USBMount(p_eventbuffer);
			goto redraw;					
		}
		p_eventbuffer->Reset(p_eventbuffer);		
	}	    				                        
}



