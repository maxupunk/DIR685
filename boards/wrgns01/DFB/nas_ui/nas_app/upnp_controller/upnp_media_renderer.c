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
extern DFBRectangle *screen_space;
extern DFBWindowDescription win_dsc;
extern IDirectFB *gp_dfb;
extern IDirectFBDisplayLayer *main_layer;
extern int GetInputDeviceEventByType(IDirectFBEventBuffer *p_eventbuffer, int PType); 
//end extern variable or function from main.c
extern int upnp_cmd_handler(IDirectFBEventBuffer *p_eventbuffer, UPnPNode **init_node, char *media_device_guid, int cmd);

int UPnP_Media_Renderer(IDirectFBEventBuffer *p_eventbuffer)
{							
	GridObj *grid=NULL, *text_grid=NULL;		
	IconObj *icon=NULL;				
	TextObj *text=NULL, *text_selected=NULL;
	UPnPNode *head=NULL, *unode_selected=NULL;	
	DFBRectangle *page_space;
	int key = 0, grid_count = 1, serv_response = 0, set_flag=REQ_FAIL;	
	int page_size=5, line_distance=50;
					     
	serv_response = upnp_cmd_handler(p_eventbuffer, &head, NULL, SHOWMR); 	
	if(serv_response!=REQ_SUCCESS) return REQ_FAIL; 
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
 			back_point:
 			free(page_space);	 	
 			grid_free(grid);
			grid_free(text_grid);
 			icons_free(icon); 		
 			texts_free(text);		 			
 			delete_unode_tree(head);
 			return set_flag;	     			 			
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
			Messages MsgTable[1];
			memset(MsgTable, 0, sizeof(MsgTable));	
			MsgTable[0].msg="Use This Media Renderer?";
			int ret = Confirm_Center(p_eventbuffer, MsgTable, sizeof(MsgTable)/sizeof(MsgTable[0]));
			if(ret)	//yes
			{					
				serv_response = upnp_cmd_handler(p_eventbuffer, NULL, unode_selected->guid, SETMR);								
				set_flag=REQ_SUCCESS;
				goto back_point;
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

