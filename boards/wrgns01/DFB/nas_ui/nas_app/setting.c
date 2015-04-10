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
#include "setting.h"
#include "detect_info.h"

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
FcNode *setting_node;
static char *menu_title[]={TITLE_LCD_LUN_SET,TITLE_HD_SLEEP_SET,TITLE_LCD_SLEEP_SET,TITLE_CLOCK_DISPLAY_SET, "0x"};
static char *menu_icon_path[]={SET_0_G,SET_1_G,SET_2_G,SET_4_G,"0x"};

void Setting_Menu(IDirectFBEventBuffer *p_eventbuffer)
{			
		
	int key=0; 						
	int grid_count, node_count;		
	char *icon_select;
				  	        									                                                                                                        
//start draw menu_list init	                               
	setting_node=create_menu_tree(menu_title, menu_icon_path);			
	node_count=get_fcnode_count(setting_node);	
	grid_count = get_grid_count(grid);	
	if(node_count<grid_count) clone_fctree(setting_node);					
	draw_icon_tree(setting_node, icon, menu_icon_space, gp_dfb);		
	blit_to_frame(setting_node, slide_info, slide_info->frame, icon, gp_dfb);
	slide_info->frame->window->SetOpacity(slide_info->frame->window, 255);									      	                             
//end draw menu_list init		                 	           	                             
	icon_select = setting_node->brother_node->brother_node->title;	
    draw_title_string(icon_select, font_title, rgba, title_space, title_window_surface);   	                                             	                        
	while(1){            
		key = GetInputDeviceEventByType(p_eventbuffer, PTYPE_DEFAULT_API); 			           							
     	if( key == DIKI_UP ){	
     			setting_node=delete_fcnode_tree(setting_node);
     			return;	             			           																	
		}else if( key == DIKI_LEFT ){				   
			icon_select = setting_node->brother_node->title;
			draw_title_string(icon_select, font_title, rgba, title_space, title_window_surface);     
			icon=slide_left(setting_node, slide_info, icon, gp_dfb);	
			setting_node=get_fcnode_head(setting_node);												  	    
		}else if( key == DIKI_RIGHT ){									   		   																	
			icon_select = setting_node->brother_node->brother_node->brother_node->title;	
			draw_title_string(icon_select, font_title, rgba, title_space, title_window_surface);     	  	
			icon=slide_right(setting_node, slide_info, icon, gp_dfb);
			setting_node=get_fcnode_head(setting_node);											
		}else if( key == DIKI_ENTER ){														         																														
			icon_select = setting_node->brother_node->brother_node->title;	
			slide_info->frame->window->SetOpacity(slide_info->frame->window, 0);	
			if(!strcmp(icon_select,TITLE_LCD_LUN_SET)) {													
				Adjust_Luminance(p_eventbuffer, main_layer);									
			}else if(!strcmp(icon_select,TITLE_HD_SLEEP_SET)) {					
				Sleeptime_Saving(p_eventbuffer, main_layer,"HD");																																
			}else if(!strcmp(icon_select,TITLE_LCD_SLEEP_SET)) {					
				Sleeptime_Saving(p_eventbuffer, main_layer,"LCD");																																
			}else if(!strcmp(icon_select,TITLE_CLOCK_DISPLAY_SET)) {					
				Clock_Display_Setting(p_eventbuffer);
			}				
			redraw:
			draw_title_string(icon_select, font_title, rgba, title_space, title_window_surface); 				 		
			draw_icon_tree(setting_node, icon, menu_icon_space, gp_dfb);
			blit_to_frame(setting_node, slide_info, slide_info->frame, icon, gp_dfb);			
			slide_info->frame->window->SetOpacity(slide_info->frame->window, 255);																																																																	
		}else if( key == DIKI_A || key == DIKI_B ){					
			Detect_USBMount(p_eventbuffer);
			goto redraw;					
		}
		p_eventbuffer->Reset(p_eventbuffer);					
	}	    				                        
}



