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
#include <xmldb.h>
#include <libxmldbc.h>
#include "alpha_dfb_define.h"
#include "nas_str_define.h"
#include "draw_tool.h"
#include "file_tool.h"
#include "menu_tool.h"
#include "alert_center.h"
#include "detect_info.h"
#include "rgdb_node_define.h"

//start extern variable or function from main.c
extern IDirectFB *gp_dfb;
extern DFBWindowDescription win_dsc;
extern IDirectFBDisplayLayer *main_layer;
extern IDirectFBSurface *title_window_surface;
extern IDirectFBFont *font_title;	
extern DFBRectangle *screen_space, *title_space;
extern RgbaType *rgba, *rgba2;
extern SlideObj *slide_info;
//extern IconObj *icon;
extern int GetInputDeviceEventByType(IDirectFBEventBuffer *p_eventbuffer, int PType); 
//end extern variable or function from main.c

void wps_alert(IDirectFBEventBuffer *p_eventbuffer)
{		
	DFBRectangle *alert_space;
	GridObj *grid;
	IconObj *icon;	
	int key = 0, grid_count=1, commit=1;
	char msg[125]=WPS_MSG;
		
	alert_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	grid_init(alert_space, 70, 70, screen_space->w-(70*2), screen_space->h-(70*2));
	grid=create_view_tree(grid_count, alert_space);			
	icon=create_icon_tree(grid, main_layer, win_dsc); 	
	alert_ui(icon, alert_space, msg, commit);
				
	while(1){
		key = GetInputDeviceEventByType(p_eventbuffer, PTYPE_NOSCREEN_API);		
		 if(key == DIKI_ENTER){ 
			free(alert_space);
			grid_free(grid);
			icons_free(icon);					
			break;
		 }else if( key == DIKI_2){
			free(alert_space);
			grid_free(grid);
			icons_free(icon);		
			char msg[125]=WPS_ERROR;						
			Alert_Center(p_eventbuffer, msg);
			break;
		}else if( key == DIKI_3){
			free(alert_space);
			grid_free(grid);
			icons_free(icon);					
			char msg[125]=WPS_OVERLAP;						
			Alert_Center(p_eventbuffer, msg);
			break;
		}else if( key == DIKI_4){
			free(alert_space);
			grid_free(grid);
			icons_free(icon);			
			char msg[125]=WPS_SUCCESS;						
			Alert_Center(p_eventbuffer, msg);		
			break;
		}	
	}	
}

void wps_pin_alert(IDirectFBEventBuffer *p_eventbuffer)
{		
	DFBRectangle *alert_space;
	GridObj *grid;
	IconObj *icon;	
	_u8 pin_code[RGDBBUFFER_SIZE];
	int grid_count=1, commit=0;	
	char msg[30];
		
	memset(pin_code, 0, RGDBBUFFER_SIZE);
	memset(msg, 0, 30);
	alert_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	grid_init(alert_space, 70, 70, screen_space->w-(70*2), screen_space->h-(70*2));
	grid=create_view_tree(grid_count, alert_space);			
	icon=create_icon_tree(grid, main_layer, win_dsc); 		
	sprintf(msg,WPS_GET_PIN);
	alert_ui(icon, alert_space, msg, commit);				
	xmldbc_get_wb(NULL, 0, RGDB_WPS_SET_PIN_CODE, pin_code, RGDBBUFFER_SIZE);
	//joel add //default setting need read runtime node
	if(pin_code[0]=='\0')
		xmldbc_get_wb(NULL, 0, RGDB_WIRELESS_RUNTIME_WPS_PIN, pin_code, RGDBBUFFER_SIZE);
	//xmldbc_get_wb(NULL, 0, RGDB_WPS_GET_PIN_CODE, pin_code, RGDBBUFFER_SIZE);						
	//xmldbc_set(NULL, 0, RGDB_WPS_SET_PIN_CODE, pin_code);		
	memset(msg, 0, 30);
	if(pin_code[0]!='\0'){											
		//system("echo 'submit COMMIT;submit WLAN' > /var/wpswlanrestart.sh");
		//system("sh /var/wpswlanrestart.sh &");
//		system("submit COMMIT");
//		system("submit WLAN &");
		free(alert_space);
		grid_free(grid);
		icons_free(icon);											
		sprintf(msg, "PIN:%s", pin_code);
		Alert_Center(p_eventbuffer, msg);	
		
	}else{				
		free(alert_space);
		grid_free(grid);
		icons_free(icon);		
		sprintf(msg,WPS_PIN_ERROR);
		Alert_Center(p_eventbuffer, msg);	
	}	
}

void Wps_Menu(IDirectFBEventBuffer *p_eventbuffer)
{				
	IconObj *icon, *icon1, *icon2, *icon3;
	int button_right_flag=0, button_left_flag =1;		
	int key = 0; 							
	DFBRectangle *left_icon_space, *right_icon_space, *big_left_icon_space, *big_right_icon_space;			
				
	        												                                                                                                            
//start draw menu_list init	  		                                       		
	big_left_icon_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));	
	big_right_icon_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));		        	
	left_icon_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));	
	right_icon_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));	
	grid_init(big_left_icon_space, 60, 120, 280, 380); 
	grid_init(big_right_icon_space, 300, 120, 280, 380); 
	grid_init(left_icon_space, 60, 150, 240, 300); 
	grid_init(right_icon_space, 330, 150, 240, 300); 		
	icon=(IconObj*)malloc(sizeof(IconObj));
	icon1=(IconObj*)malloc(sizeof(IconObj));
	icon2=(IconObj*)malloc(sizeof(IconObj));
	icon3=(IconObj*)malloc(sizeof(IconObj));	
	icon->left=NULL;
	icon->right=icon1;
	icon1->right=icon2;
	icon2->right=icon3;	
	icon3->right=NULL;
	set_icon_value(icon,"icon", WPS_0_G, 0);
	set_icon_value(icon1,"icon1", WPS_1_G, 1);
	set_icon_value(icon2,"icon2", WPS_0_G, 1);
	set_icon_value(icon3,"icon3", WPS_1_G, 2);		
	set_windsc_xywh(&win_dsc, left_icon_space);   			
	set_icon_window(main_layer, win_dsc, icon);	
	set_windsc_xywh(&win_dsc, right_icon_space);   			
	set_icon_window(main_layer, win_dsc, icon1);	
	set_windsc_xywh(&win_dsc, big_left_icon_space);   			
	set_icon_window(main_layer, win_dsc, icon2);	
	set_windsc_xywh(&win_dsc, big_right_icon_space);   			
	set_icon_window(main_layer, win_dsc, icon3);						
	draw_image(icon->icon_path, NULL, icon->window_surface, gp_dfb);	 		
	draw_image(icon1->icon_path, NULL, icon1->window_surface, gp_dfb);	
	draw_image(icon2->icon_path, NULL, icon2->window_surface, gp_dfb);		
	draw_image(icon3->icon_path, NULL, icon3->window_surface, gp_dfb);		
	icon2->window->SetOpacity(icon2->window, 255);
	icon1->window->SetOpacity(icon1->window, 255);		
	icon_stackclass(icon, DWSC_MIDDLE);		
//end draw menu_list init		                                             	       
                   
	while(1){            
		key = GetInputDeviceEventByType(p_eventbuffer, PTYPE_DEFAULT_API);    			           							
     	if( key == DIKI_UP ){	     			     					     			     			
     			free(big_left_icon_space);
     			free(big_right_icon_space);     			
     			free(left_icon_space);
     			free(right_icon_space);     			     			
     			icons_free(icon);     
     			return;	             			           																	
		}else if( key == DIKI_LEFT ){				    	
			if(button_left_flag==0){  				  																					
				button_right_flag=0;				
				button_left_flag =1;
				icon2->window->SetOpacity(icon2->window, 255);
				icon3->window->SetOpacity(icon3->window, 0);				
				icon1->window->SetOpacity(icon1->window, 255);												
				icon->window->SetOpacity(icon->window, 0);
			}									
		}else if( key == DIKI_RIGHT ){									   		   	
			if(button_right_flag==0){																																					
				button_left_flag=0;				
				button_right_flag =1;
				icon3->window->SetOpacity(icon3->window, 255);
				icon2->window->SetOpacity(icon2->window, 0);
				icon->window->SetOpacity(icon->window, 255);					
				icon1->window->SetOpacity(icon1->window, 0);
			}										
		}else if( key == DIKI_ENTER ){						
			char wps_enable[2];
			xmldbc_get_wb(NULL, 0, RGDB_WPS_ENABLE, wps_enable, 1);								 														         																															
			if(wps_enable[0]=='1')
			{
				if(button_right_flag==1){																				
					system("usockc /var/run/fresetd_unixsock WPS_START");														
					wps_alert(p_eventbuffer);									
				}else if(button_left_flag==1){
					wps_pin_alert(p_eventbuffer);												
				}																																			
			}else{								
				Alert_Center(p_eventbuffer, WPS_DISABLE);									
			}	
		}else if( key == DIKI_A || key == DIKI_B ){				
			icon_opacity(icon, 0);												
			Detect_USBMount(p_eventbuffer);
			draw_title_string(TITLE_WPS, font_title, rgba, title_space, title_window_surface);
			slide_info->frame->window_surface->Clear(slide_info->frame->window_surface, 0, 0, 0, 0);		
			slide_info->frame->window_surface->Flip(slide_info->frame->window_surface, NULL, DSFLIP_NONE);	
			icon->window->SetOpacity(icon->window, 255);
			icon1->window->SetOpacity(icon1->window, 255);	
		}
		p_eventbuffer->Reset(p_eventbuffer);					
	}	    				                        
}



