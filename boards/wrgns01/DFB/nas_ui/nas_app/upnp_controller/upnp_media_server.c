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
#include "alpha_dfb_define.h"
#include "draw_tool.h"
#include "file_tool.h"
#include "menu_tool.h"
#include "fcrss_parser.h"
#include "fcrss_command.h"
#include "str_tool.h"
#include "alert_center.h"
#include "confirm_center.h"
#include "detect_info.h"
#include "fcrss_handler.h"
#include "packet_serialize.h" 
#include "upnp_ctrl_cmd.h"

//start extern variable or function from main.c
extern DFBRectangle *screen_space, *title_space;
extern DFBWindowDescription win_dsc;
extern IDirectFB *gp_dfb;
extern IDirectFBDisplayLayer *main_layer;
extern IDirectFBSurface *title_window_surface;
extern IDirectFBFont *font_title;	
extern RgbaType *rgba;

extern int GetInputDeviceEventByType(IDirectFBEventBuffer *p_eventbuffer, int PType); 
//end extern variable or function from main.c

extern int upnp_cmd_handler(IDirectFBEventBuffer *p_eventbuffer, UPnPNode **init_node, char *media_device_guid, int cmd);
void UPnP_OpenMediaServer(IDirectFBEventBuffer *p_eventbuffer, char *media_device_guid);
void UPnP_MediaController(IDirectFBEventBuffer *p_eventbuffer, char *media_device_guid);

void UPnP_Media_Server(IDirectFBEventBuffer *p_eventbuffer)
{							
	GridObj *grid=NULL, *text_grid=NULL;		
	IconObj *icon=NULL;				
	TextObj *text=NULL, *text_selected=NULL;
	UPnPNode *head=NULL, *unode_selected=NULL;	
	DFBRectangle *page_space;
	int key = 0, grid_count = 1, serv_response = 0;	
	int page_size=5, line_distance=50;
						     
	serv_response = upnp_cmd_handler(p_eventbuffer, &head, NULL, SHOWMS); 	
	if(serv_response!=REQ_SUCCESS) return; 	
	icon_alert(PHOTO_LOADING_G, D_MOVE_CENTER);
	page_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	grid_init(page_space, screen_space->x+50, screen_space->y+80, screen_space->w-100, screen_space->h-160);
	grid=create_view_tree(grid_count, page_space);			
	icon=create_icon_tree(grid, main_layer, win_dsc); 				
	text_grid = create_text_grid_tree(page_size, line_distance, page_space);	
	text = create_text_node_tree(text_grid); 				
	upnp_text_node_map(head, text); 			
	draw_text_table(text, icon->window_surface);
	icon_opacity(icon, 255);	 	 	    			
	icon_stackclass(icon, DWSC_MIDDLE);	     	
	close_icon_alert();
	text_selected=text;
	unode_selected=head;	
	
	while(1)
	{            
		key = GetInputDeviceEventByType(p_eventbuffer,PTYPE_NOSCREEN_API);    			           							
 		if( key == DIKI_UP )
 		{ 	 			 			 						
	 		upnp_cmd_handler(p_eventbuffer, NULL, NULL, CDUP); 	
	 		free(page_space);
	 		grid_free(grid);
			grid_free(text_grid);
	 		icons_free(icon); 		
	 		texts_free(text);		 			
	 		delete_unode_tree(head);	 			
	 		return;	       	 			 					 			
		}else if( key == DIKI_LEFT ){												
			if(unode_selected->elder_brother_node!=NULL) 
 			{
	 			if(text_selected->left!=NULL&&text_selected->left->content!=NULL)
	 			{	 				
		 				unode_selected=unode_selected->elder_brother_node;
		 				shift_text_left(&text_selected, icon->window_surface); 						 				
	 			}else { 									
						go_prev_page(page_size, &unode_selected, text, icon->window_surface);
						text_selected=text;											
	 			}
 			} 											
		}else if( key == DIKI_RIGHT ){							 															
			if(unode_selected->brother_node!=NULL) 
			{
				unode_selected=unode_selected->brother_node;
				if(text_selected->right!=NULL&&text_selected->right->content!=NULL)
				{ 					
					shift_text_right(&text_selected, icon->window_surface);												
				}else{										
					go_next_page(unode_selected, text, icon->window_surface);
					text_selected=text;											
				}	
			}  																	
		}else if( key == DIKI_DOWN ){													
				 		
		}else if( key == DIKI_ENTER ){
			serv_response = upnp_cmd_handler(p_eventbuffer, NULL, unode_selected->guid, SETMS); 							
			icon_opacity(icon, 0);	
			UPnP_OpenMediaServer(p_eventbuffer, NULL);		
			draw_title_string("Select Media Server", font_title, rgba, title_space, title_window_surface); 
			title_window_surface->Flip(title_window_surface, NULL, DSFLIP_NONE);		
			icon_opacity(icon, 255);				
		}else if( key == DIKI_A || key == DIKI_B ){																	
			icon_opacity(icon, 0);
			Detect_USBMount(p_eventbuffer);
			icon_opacity(icon, 255);
			p_eventbuffer->Reset(p_eventbuffer);						
		}
		p_eventbuffer->Reset(p_eventbuffer);							
	}	    				                        
}


void UPnP_OpenMediaServer(IDirectFBEventBuffer *p_eventbuffer, char *media_device_guid)
{							
	GridObj *grid=NULL, *text_grid=NULL;		
	IconObj *icon=NULL;				
	TextObj *text=NULL, *text_selected=NULL;
	UPnPNode *head=NULL, *unode_selected=NULL;	
	DFBRectangle *page_space;
	int key = 0, grid_count = 1, serv_response = 0;	
	int page_size=5, line_distance=50;
						     	
	serv_response = upnp_cmd_handler(p_eventbuffer, &head, media_device_guid, LS); 		
	if(serv_response!=REQ_SUCCESS) return; 
	draw_title_string("Select Media File", font_title, rgba, title_space, title_window_surface);    
	icon_alert(PHOTO_LOADING_G, D_MOVE_CENTER);
	page_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	grid_init(page_space, screen_space->x+50, screen_space->y+80, screen_space->w-100, screen_space->h-160);
	grid=create_view_tree(grid_count, page_space);			
	icon=create_icon_tree(grid, main_layer, win_dsc); 				
	text_grid = create_text_grid_tree(page_size, line_distance, page_space);	
	text = create_text_node_tree(text_grid); 				
	upnp_text_node_map(head, text); 			
	draw_text_table(text, icon->window_surface);
	icon_opacity(icon, 255);	 	 	    			
	icon_stackclass(icon, DWSC_MIDDLE);	     	
	close_icon_alert();
	text_selected=text;
	unode_selected=head;
	
	while(1)
	{            
		key = GetInputDeviceEventByType(p_eventbuffer,PTYPE_NOSCREEN_API);    			           							
 		if( key == DIKI_UP )
 		{ 	 			
 			upnp_cmd_handler(p_eventbuffer, NULL, NULL, CDUP); 	
 			free(page_space);
 			grid_free(grid);
			grid_free(text_grid);
 			icons_free(icon); 		
 			texts_free(text);		 			
 			delete_unode_tree(head);
 			return;	       		 			 			
		}else if( key == DIKI_LEFT ){												
			if(unode_selected->elder_brother_node!=NULL) 
 			{
	 			if(text_selected->left!=NULL&&text_selected->left->content!=NULL)
	 			{	 				
		 				unode_selected=unode_selected->elder_brother_node;
		 				shift_text_left(&text_selected, icon->window_surface); 						 				
	 			}else { 									
						go_prev_page(page_size, &unode_selected, text, icon->window_surface);
						text_selected=text;											
	 			}
 			} 								
		}else if( key == DIKI_RIGHT ){
			if(unode_selected->brother_node!=NULL) 
			{
				unode_selected=unode_selected->brother_node;
				if(text_selected->right!=NULL&&text_selected->right->content!=NULL)
				{ 					
					shift_text_right(&text_selected, icon->window_surface);												
				}else{										
					go_next_page(unode_selected, text, icon->window_surface);
					text_selected=text;											
				}	
			}							 																																		
		}else if( key == DIKI_DOWN ){		
				                           										
		}else if( key == DIKI_ENTER ){
			serv_response = upnp_cmd_handler(p_eventbuffer, &head, unode_selected->guid, CD);				
			if(serv_response==REQ_SUCCESS)
			{					
				icon_opacity(icon, 0);
				UPnP_OpenMediaServer(p_eventbuffer, unode_selected->guid);						
				icon_opacity(icon, 255);	
			}else{
				UPnP_MediaController(p_eventbuffer, unode_selected->guid);
			}			
		}else if( key == DIKI_A || key == DIKI_B ){																	
			icon_opacity(icon, 0);
			Detect_USBMount(p_eventbuffer);
			icon_opacity(icon, 255);
			p_eventbuffer->Reset(p_eventbuffer);						
		}
		p_eventbuffer->Reset(p_eventbuffer);							
	}	    				                        
}

void UPnP_MediaController(IDirectFBEventBuffer *p_eventbuffer, char *media_device_guid)
{
	GridObj *grid=NULL;		
	IconObj *toolbar_icon=NULL;						
	FcNode *toolbar_node=NULL;
	DFBRectangle *toolbar_space, *toolbar_icon_space;
	int key = 0, grid_count = 6, serv_response = 0, toolbar_style=H_STYLE;		
	char *toolbar[]={"play","pause","stop","mute","voice up","voice down","0x"};
	char *toolbar_path[]={MEDIA_PLAY_0_G, MEDIA_PLAY_1_G, MEDIA_PLAY_2_G, MEDIA_PLAY_3_G, MEDIA_PLAY_4_G, MEDIA_PLAY_5_G,"0x"};
			
	serv_response = upnp_cmd_handler(p_eventbuffer, NULL, media_device_guid, OPEN);
	if(serv_response !=REQ_SUCCESS) return;						
	toolbar_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));	
	toolbar_icon_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));	
	grid_init(toolbar_space, screen_space->x+100, screen_space->y+380, screen_space->w-100, screen_space->h-350);
	grid_init(toolbar_icon_space, 0, 0, 50, 50);
	grid=create_button_tree(grid_count, toolbar_space, toolbar_style);				
	toolbar_icon=create_icon_tree(grid, main_layer, win_dsc);
	toolbar_node=create_menu_tree(toolbar, toolbar_path);	
	draw_icon_tree(toolbar_node, toolbar_icon, toolbar_icon_space, gp_dfb);	
	icon_opacity(toolbar_icon, 100);	 	 	    			
	toolbar_icon->window->SetOpacity(toolbar_icon->window, 255);
	icon_stackclass(toolbar_icon, DWSC_MIDDLE);	     		
	
	while(1)
	{            
		key = GetInputDeviceEventByType(p_eventbuffer,PTYPE_NOSCREEN_API);    			           							
 		if( key == DIKI_UP )
 		{ 	 			 			
 			free(toolbar_space);	 												
 			free(toolbar_icon_space);	 	
			grid_free(grid);			
 			icons_free(toolbar_icon); 	 		
 			delete_fcnode_tree(toolbar_node);			 			
 			return;	       		 		 			
		}else if( key == DIKI_LEFT ){	
			if(toolbar_node->elder_brother_node!=NULL) 
			{
				toolbar_node=toolbar_node->elder_brother_node;	
				toolbar_icon->window->SetOpacity(toolbar_icon->window, 100);		
				toolbar_icon=toolbar_icon->left;								
				toolbar_icon->window->SetOpacity(toolbar_icon->window, 255);		
			}	
		}else if( key == DIKI_RIGHT ){						 		
			if(toolbar_node->brother_node!=NULL) 
			{
				toolbar_node=toolbar_node->brother_node;
				toolbar_icon->window->SetOpacity(toolbar_icon->window, 100);		
				toolbar_icon=toolbar_icon->right;																																								
				toolbar_icon->window->SetOpacity(toolbar_icon->window, 255);	
			}	
		}else if( key == DIKI_DOWN ){		
			free(toolbar_space);	 	
			free(toolbar_icon_space);	 	
			grid_free(grid);			
 			icons_free(toolbar_icon); 	 				 			 			
 			delete_fcnode_tree(toolbar_node);			 			
 			return;	       		 		
		}else if( key == DIKI_ENTER ){						
			if(!strcmp(toolbar_node->title,toolbar[0])){							
				serv_response = upnp_cmd_handler(p_eventbuffer, NULL, NULL, PLAY);															
			}else if(!strcmp(toolbar_node->title,toolbar[1])){								
				serv_response = upnp_cmd_handler(p_eventbuffer, NULL, NULL, STOP);							
			}else if(!strcmp(toolbar_node->title,toolbar[2])){					
				serv_response = upnp_cmd_handler(p_eventbuffer, NULL, NULL, PAUSE);							
			}else if(!strcmp(toolbar_node->title,toolbar[3])){					
				serv_response = upnp_cmd_handler(p_eventbuffer, NULL, NULL, MUTE);							
			}else if(!strcmp(toolbar_node->title,toolbar[4])){									
				serv_response = upnp_cmd_handler(p_eventbuffer, NULL, NULL, VUP);						
			}else if(!strcmp(toolbar_node->title,toolbar[5])){								
				serv_response = upnp_cmd_handler(p_eventbuffer, NULL, NULL, VDOWN);					
			}			
		}else if( key == DIKI_A || key == DIKI_B ){																	
			icon_opacity(toolbar_icon, 0);
			Detect_USBMount(p_eventbuffer);
			icon_opacity(toolbar_icon, 255);
			p_eventbuffer->Reset(p_eventbuffer);						
		}
		p_eventbuffer->Reset(p_eventbuffer);							
	}	    				                			
}
	