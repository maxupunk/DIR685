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
#include "nas_str_define.h"
#include "draw_tool.h"
#include "file_tool.h"
#include "menu_tool.h"
#include "fcrss_parser.h"
#include "fcrss_command.h"
#include "fcrss_serialize.h"
#include "str_tool.h"
#include "frameit_parser.h"
#include "alert_center.h"
#include "detect_info.h"
#include "fcrss_handler.h"
#include "download_tool.h"

//start extern variable or function from main.c
extern IDirectFB *gp_dfb;
extern DFBWindowDescription win_dsc;
extern IDirectFBDisplayLayer *main_layer;
extern DFBRectangle *screen_space;
extern RgbaType *rgba, *rgba2; 
extern int GetInputDeviceEventByType(IDirectFBEventBuffer *p_eventbuffer, int PType); 
//end extern variable or function from main.c
FcNode *fitshow_node=NULL;

void FrameIt_Display_App(IDirectFBEventBuffer *p_eventbuffer)
{					
	GridObj *grid;		
	IconObj *icon, *alert_icon;	
	ViewObj *view;
	DownloadObj *dobj;
	pthread_t id, tid;
	int key = 0, cmd, serv_response; 						
	int grid_count=1, download_count=3, update_count=0, node_count, repeat=3;
	char msg[30]=FRAMEIT_DISPLAY_MSG;
			 		             		
	cmd= Mclient_cmd_handler(CHANNEL_SHOW_GET, NULL); 		
	serv_response=Malert_cmd_handler(p_eventbuffer, cmd, CHANNEL_SHOW_GET);				
	if(serv_response==0) return;			
	win_dsc.caps = DWCAPS_NONE;
	grid=create_view_tree(grid_count, screen_space);			
	icon=create_icon_tree(grid, main_layer, win_dsc); 				
	alert_icon=(IconObj*)channel_alert(msg);					
	fc_download_init(fitshow_node, download_count);	
	draw_image_scale(fitshow_node->local_file_path, screen_space, icon->window_surface, gp_dfb);		
	icon_opacity(icon, 255);	 	 	    			
	icon_stackclass(icon, DWSC_MIDDLE);	     
	icons_free(alert_icon);		
	view=(ViewObj*)malloc(sizeof(ViewObj));
	view->p_eventbuffer=p_eventbuffer;
	view->node=fitshow_node;
	dobj=(DownloadObj*)malloc(sizeof(DownloadObj));
	dobj->node=fitshow_node;
	dobj->d_count=download_count;	
	node_count=get_fcnode_count(fitshow_node);
	pthread_create(&id, NULL, &view_player_r, view);	
	                                          	  	
	while(1){            
		key = GetInputDeviceEventByType(p_eventbuffer,PTYPE_NOSCREEN_API);    			           							
 		if( key == DIKI_UP ){	
 			key_up:      	
 			free(view);	
 			free(dobj);
 			grid_free(grid);
 			icons_free(icon);
 			pthread_cancel(id);	     	
 			pthread_cancel(tid);		
 			remove_fcfile(fitshow_node);
 			fitshow_node=delete_fcnode_tree(fitshow_node);     						     			  			     			
 			win_dsc.caps = DWCAPS_ALPHACHANNEL;   			 			
 			return;	             			           												
		}else if( key == DIKI_LEFT && node_count>1){
			pthread_cancel(id);	 			
			shift_fcnode_left(fitshow_node);
			fitshow_node=get_fcnode_head(fitshow_node);				
			dobj->node=fitshow_node;
			pthread_create(&tid, NULL, &fc_download_r, dobj);						
			icon->window_surface->Clear(icon->window_surface, 0, 0, 0, 0);				
			draw_image_scale(fitshow_node->local_file_path, screen_space, icon->window_surface, gp_dfb);		
			icon->window_surface->Flip(icon->window_surface, NULL, DSFLIP_NONE );						
			pthread_join(tid, NULL);
		}else if( key == DIKI_RIGHT && node_count>1){							 												
			pthread_cancel(id);	
			shift_fcnode_right(fitshow_node);
			fitshow_node=get_fcnode_head(fitshow_node);							
			dobj->node=fitshow_node;
			pthread_create(&tid, NULL, &fc_download_r, dobj);							
			icon->window_surface->Clear(icon->window_surface, 0, 0, 0, 0);					
			draw_image_scale(fitshow_node->local_file_path, screen_space, icon->window_surface, gp_dfb);			
			icon->window_surface->Flip(icon->window_surface, NULL, DSFLIP_NONE );		
			pthread_join(tid, NULL);
		}else if( key == DIKI_V){				
			if(update_count==repeat*node_count) {
					update_count=0;	
					cmd= Mclient_cmd_handler(CHANNEL_SHOW_GET, NULL);  	 			
					if(Malert_cmd_handler(p_eventbuffer, cmd, CHANNEL_SHOW_GET)==0) goto key_up;					
					node_count=get_fcnode_count(fitshow_node);
					if(node_count==1) {
						update_count=-3600;						
						icon->window_surface->Clear(icon->window_surface, 0, 0, 0, 0);		
						fc_download_init(fitshow_node, download_count);					
						draw_image_scale(fitshow_node->local_file_path, screen_space, icon->window_surface, gp_dfb);			
						icon->window_surface->Flip(icon->window_surface, NULL, DSFLIP_NONE );											
					}	
			}
			
			if(node_count>1){	
				shift_fcnode_right(fitshow_node);
				fitshow_node=get_fcnode_head(fitshow_node);	
				dobj->node=fitshow_node;				
				pthread_create(&tid, NULL, &fc_download_r, dobj);								    
				icon->window_surface->Clear(icon->window_surface, 0, 0, 0, 0);											
				draw_image_scale(fitshow_node->local_file_path, screen_space, icon->window_surface, gp_dfb);			
				icon->window_surface->Flip(icon->window_surface, NULL, DSFLIP_NONE );
				pthread_join(tid, NULL);										
			}				
			update_count++;									
		}else if( key == DIKI_DOWN && node_count>1){	
			pthread_cancel(id);	 	
			view->p_eventbuffer=p_eventbuffer;					
			pthread_create(&id, NULL, &view_player_r, view);  			
		}else if( key == DIKI_A || key == DIKI_B ){			
			int flag;			
			pthread_cancel(tid);
			flag=pthread_cancel(id);
			icon_opacity(icon, 0);
			Detect_USBMount(p_eventbuffer);
			icon_opacity(icon, 255);
			view->p_eventbuffer=p_eventbuffer;
			if(flag==0) pthread_create(&id, NULL, &view_player_r, view);  									
		}		
		p_eventbuffer->Reset(p_eventbuffer);					
	}	    				                        
}
