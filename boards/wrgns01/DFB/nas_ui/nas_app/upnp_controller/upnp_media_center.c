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
//end extern variable or function from main.c

static char *menu_title[]={"Select Media Renderer","Select Media Server", "0x"};
static char *menu_icon_path[]={UPNP_1_G, UPNP_0_G,"0x"};

extern int UPnP_Media_Renderer(IDirectFBEventBuffer *p_eventbuffer);
extern void UPnP_Media_Server(IDirectFBEventBuffer *p_eventbuffer);
void UPnP_Setup_End(IDirectFBEventBuffer *p_eventbuffer, IconObj *icon);

void UPnP_Setup_Start(IDirectFBEventBuffer *p_eventbuffer)
{					
	FcNode *upnp_media_node=NULL;	
	int key=0, grid_count=0, node_count=0; 	
	
	upnp_media_node=create_menu_tree(menu_title, menu_icon_path);									
	grid_count=get_grid_count(grid);
	node_count=get_fcnode_count(upnp_media_node);		
			
	redraw: //goto point		
	draw_icon_tree(upnp_media_node, icon, menu_icon_space, gp_dfb);			      	                             					
	icon->window->MoveTo(icon->window, 213, 150);	
	icon->window->SetOpacity(icon->window, 255);	
	icon->right->window->MoveTo(icon->right->window, 213, 150);		
    draw_title_string(menu_title[0], font_title, rgba, title_space, title_window_surface);     	                                             	                                
	while(1){            
		key = GetInputDeviceEventByType(p_eventbuffer, PTYPE_DEFAULT_API);  			           							
     	if( key == DIKI_UP ){     
     		icon_opacity(icon, 0);	
 			upnp_media_node=delete_fcnode_tree(upnp_media_node);     			     			     			 			
 			return;	             			           																																													
		}else if( key == DIKI_ENTER ){								 														         																																																								
			icon->window->SetOpacity(icon->window, 0);
			if(UPnP_Media_Renderer(p_eventbuffer)==REQ_SUCCESS)
			{				
				draw_title_string(menu_title[1], font_title, rgba, title_space, title_window_surface);
				UPnP_Setup_End(p_eventbuffer, icon->right);				
			}	
			icon->window->SetOpacity(icon->window, 255);																									
			draw_title_string(menu_title[0], font_title, rgba, title_space, title_window_surface);																																																																					
//		}else if( key == DIKI_A || key == DIKI_B ){					
//			Detect_USBMount(p_eventbuffer);
//			goto redraw;					
		}
		p_eventbuffer->Reset(p_eventbuffer);					
	}	    				                        
}

void UPnP_Setup_End(IDirectFBEventBuffer *p_eventbuffer, IconObj *icon)
{
	int key=0;
	
	draw_title_string(menu_title[1], font_title, rgba, title_space, title_window_surface);
	title_window_surface->Flip(title_window_surface, NULL, DSFLIP_NONE);			
	icon->window->SetOpacity(icon->window, 255);				
		
	while(1)
	{            
		key = GetInputDeviceEventByType(p_eventbuffer, PTYPE_DEFAULT_API);  			           							
     	if( key == DIKI_UP ){     
     		icon->window->SetOpacity(icon->window, 0); 			     			     			     			 			
 			return;	             			           																																													
		}else if( key == DIKI_ENTER ){								 														         																																																								
			icon->window->SetOpacity(icon->window, 0);			
			UPnP_Media_Server(p_eventbuffer);																			
			icon->window->SetOpacity(icon->window, 255);																															
//		}else if( key == DIKI_A || key == DIKI_B ){					
//			Detect_USBMount(p_eventbuffer);			
		}
		p_eventbuffer->Reset(p_eventbuffer);					
	}	    				                        
}


