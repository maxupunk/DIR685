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
#include "menu_tool.h"
#include "confirm_center.h"
#include "alert_center.h"
#include "rgdb_node_define.h"
#include <sys/resource.h>

//start extern variable or function from main.c
extern IDirectFB *gp_dfb;
extern DFBWindowDescription win_dsc;
extern IDirectFBDisplayLayer *main_layer;
extern DFBRectangle *screen_space;
extern int GetInputDeviceEventByType(IDirectFBEventBuffer *p_eventbuffer, int PType); 
//end extern variable or function from main.c
int switch_icon_alert=1;

void alert_commit(IDirectFBSurface *surface)
{
	DFBRectangle *space;
	RgbaType *text_rga;
	IDirectFBFont *font;
	
	font = (IDirectFBFont*)InitFont(34);
	space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	text_rga = (RgbaType*)malloc(sizeof(RgbaType));			
	set_rgba(text_rga, 0x7D, 0xC2, 0xF4, 255);	
	grid_init(space, 250, 300, 100, 50);
	draw_text(space, ALERT_CENTER_MSG , font, DSTF_CENTER, text_rga, surface);	
	surface->Flip( surface, NULL, DSFLIP_NONE );	
	font->Release(font);	
	free(text_rga);	
	free(space);	
}

void alert_ui(IconObj *icon, DFBRectangle *alert_space, char *msg, int commit)
{
	DFBRectangle *space=NULL;
	IDirectFBFont *font=NULL;
	RgbaType *text_rga=NULL; 	
	char buffer[128],tmsg[DEFAULT_MSG_MAX_LINE][DEFAULT_MSG_MAX_TEXT_LENGTH],*pstr;
	int tmsg_size=0,i;	
			
	font = (IDirectFBFont*)InitFont(34);
	space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	text_rga = (RgbaType*)malloc(sizeof(RgbaType));	
	DrawBackground(icon->window_surface, space, text_rga, alert_space->w, alert_space->h);	
	set_rgba(text_rga, 0xff, 0xff, 0xff, 255);
	if(strstr(msg,"\n"))
	{
		strcpy(buffer,msg);
		strcpy(tmsg[tmsg_size++],strtok(buffer,"\n"));
		while((pstr=strtok(NULL,"\n"))!=NULL)
			strcpy(tmsg[tmsg_size++],pstr);
	}
	else
		strcpy(tmsg[tmsg_size++],msg);
		
	for(i=0;i<tmsg_size;i++)
	{
		grid_init(space, alert_space->w/2, (alert_space->h-30)/(tmsg_size+1)*(i+1), alert_space->w, alert_space->h);
		draw_text(space, tmsg[i], font, DSTF_CENTER, text_rga, icon->window_surface);	
	}

	if(commit==1) alert_commit(icon->window_surface);		
	icon->window->SetOpacity(icon->window, 255);
	font->Release( font );	
	free(text_rga);
	free(space);
}

void Alert_Center(IDirectFBEventBuffer *p_eventbuffer, char *msg)
{		
	DFBRectangle *alert_space;
	GridObj *grid;
	IconObj *icon;	
	int key = 0, grid_count=1, commit=1;
			
	alert_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	grid_init(alert_space, 70, 70, screen_space->w-(70*2), screen_space->h-(70*2));
	grid=create_view_tree(grid_count, alert_space);			
	icon=create_icon_tree(grid, main_layer, win_dsc); 	
	alert_ui(icon, alert_space, msg, commit);
	
	while(1)
	{
		key = GetInputDeviceEventByType(p_eventbuffer, PTYPE_NOSCREEN_API);
		if( key == DIKI_ENTER )
		{					
			free(alert_space);
			grid_free(grid);
			icons_free(icon);				
			p_eventbuffer->Reset(p_eventbuffer);
			break;
		}		
	}
}

IconObj* channel_alert(char *msg)
{		
	DFBRectangle *alert_space;
	GridObj *grid;
	IconObj *icon;	
	int grid_count=1, commit=0;	
		
	alert_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	grid_init(alert_space, 70, 70, screen_space->w-(70*2), screen_space->h-(70*2));
	grid=create_view_tree(grid_count, alert_space);			
	icon=create_icon_tree(grid, main_layer, win_dsc); 	
	alert_ui(icon, alert_space, msg, commit);
	free(alert_space);
	grid_free(grid);	
	return icon;
}

void register_alert(IDirectFBEventBuffer *p_eventbuffer, char *file_path)
{					
	GridObj *grid;		
	IconObj *icon;		
	int key = 0; 						
	int grid_count=1;	
	
	win_dsc.caps = DWCAPS_NONE; 		        			                       			
	grid=create_view_tree(grid_count, screen_space);			
	icon=create_icon_tree(grid, main_layer, win_dsc); 				
	draw_image(file_path, screen_space, icon->window_surface, gp_dfb);		
	icon_opacity(icon, 255);	 	 	    			
	icon_stackclass(icon, DWSC_MIDDLE);	     	
		                                              	  	
	while(1){            
		key = GetInputDeviceEventByType(p_eventbuffer,PTYPE_NOSCREEN_API);    			           							
 		if( key == DIKI_ENTER)
 		{	      	
 			grid_free(grid); 			
 			icons_free(icon); 					 			
 			win_dsc.caps = DWCAPS_ALPHACHANNEL;
 			p_eventbuffer->Reset(p_eventbuffer);   			
 			return;	             			           												
		}
	}	    				                        
}

void close_icon_alert()
{										
	switch_icon_alert=0;	
}

void* icon_twinkle_r(void *arg)
{	
	pthread_detach(pthread_self());		
	IconObj *icon=NULL;
				
	icon=(IconObj*)arg;	
	switch_icon_alert=1;
	
	while(1)
	{            
		if( !switch_icon_alert) break;
		icon->window->SetOpacity(icon->window, 255);
		usleep(80000);
		if( !switch_icon_alert) break;
		usleep(80000);
		if( !switch_icon_alert) break;
		icon->window->SetOpacity(icon->window, 200);			
		usleep(80000);
		if( !switch_icon_alert) break;
		usleep(80000);
		if( !switch_icon_alert) break;
		icon->window->SetOpacity(icon->window, 150);			
		usleep(80000);
		if( !switch_icon_alert) break;
		usleep(80000);
		if( !switch_icon_alert) break;
		icon->window->SetOpacity(icon->window, 100);	
		usleep(80000);
		if( !switch_icon_alert) break;
		usleep(80000);
		if( !switch_icon_alert) break;
		icon->window->SetOpacity(icon->window, 50);			
		usleep(160000);	 				
	}	    	
		
	icons_free(icon);  	
	pthread_exit(NULL);		 								 			 			 				 	     			           													
}	

void icon_alert(char *file_path, int direct)
{					
	DFBRectangle *alert_space;		
	GridObj *grid, *grid2;		
	IconObj *icon, *icon2;			
	pthread_t tid;
	int grid_count=1, thread_flag=0;	
		
	win_dsc.caps = DWCAPS_ALPHACHANNEL; 		        			                   
	grid2=create_view_tree(grid_count, screen_space);			
	icon2=create_icon_tree(grid2, main_layer, win_dsc); 									
	icon2->window_surface->Clear(icon2->window_surface, 0, 0, 0, 100);						
	alert_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	
	switch(direct)
	{	
		case D_MOVE_CENTER:
			grid_init(alert_space, 230, 150, 180, 180);					
			icon2->window->SetOpacity(icon2->window, 255);
			break;
		case D_MOVE_RIGHT:
			grid_init(alert_space, 480, 300, 180, 180);		
			icon2->window->SetOpacity(icon2->window, 0);			
			break;	
		case D_MOVE_LEFT:
			grid_init(alert_space, 0, 300, 180, 180);		
			icon2->window->SetOpacity(icon2->window, 0);			
			break;	
		case D_MOVE_UP:
			grid_init(alert_space, 230, 75, 180, 180);		
			icon2->window->SetOpacity(icon2->window, 0);			
			break;	
		case D_MOVE_DOWN:
			grid_init(alert_space, 230, 225, 180, 180);		
			icon2->window->SetOpacity(icon2->window, 0);			
			break;							
		default:			
			break;				
	}	
	grid=create_view_tree(grid_count, alert_space);			
	icon=create_icon_tree(grid, main_layer, win_dsc); 
	grid_init(alert_space, 0, 0, 180, 180);					
	draw_image_scale(file_path, alert_space, icon->window_surface, gp_dfb);				
	icon_stackclass(icon, DWSC_UPPER);			
	icon->window->PutAtop(icon->window, icon2->window); 
	grid->next=grid2;
	icon->right=icon2;			
	free(alert_space);
 	grid_free(grid); 	 	 
	thread_flag=pthread_create(&tid, NULL, &icon_twinkle_r, icon); 				
	pthread_create_msg(thread_flag);
}

int get_switch_port_status(int port_type)
{
	int port_status=0;
	char buff[2]={'\0', '\0'}, *node=NULL;
	
	if(port_type==0)
		node= RGDB_INTERNET_CABLE_STATUS;		
	else if(port_type==1)
		node= RGDB_WIRED_CABLE_P1 ;
	else if(port_type==2)
		node= RGDB_WIRED_CABLE_P2 ;
	else if(port_type==3)
		node= RGDB_WIRED_CABLE_P3 ;
	else if(port_type==4)
		node= RGDB_WIRED_CABLE_P4 ;
		
	xmldbc_get_wb(NULL, 0, node, buff, 2);		  					   			
	port_status = atoi(buff);	
	return port_status;
}

void switch_port_icon()
{
	DFBRectangle *alert_space;		
	GridObj *grid;		
	IconObj *bg, *ports_down, *lan_port1, *lan_port2, *lan_port3, *lan_port4, *wan_port;				
	int grid_count=1;
	int wan_port_status=0, lan_port1_status=0, lan_port2_status=0,lan_port3_status=0, lan_port4_status=0;		
		
	win_dsc.caps = DWCAPS_ALPHACHANNEL; 		        			                   	
	//background
	grid=create_view_tree(grid_count, screen_space);			
	bg=create_icon_tree(grid, main_layer, win_dsc); 									
	icon_stackclass(bg, DWSC_UPPER);	
	bg->window_surface->Clear(bg->window_surface, 0, 0, 0, 255);									
	bg->window->SetOpacity(bg->window, 255);			
	grid_free(grid);
				
	alert_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));					
	//all ports down icon
	grid_init(alert_space, 0, 0, 500, 100);									
	grid=create_view_tree(grid_count, alert_space);			
	ports_down=create_icon_tree(grid, main_layer, win_dsc); 
	icon_stackclass(ports_down, DWSC_UPPER);										
	ports_down->window->PutAtop(ports_down->window, bg->window);
	draw_image_scale(ALL_PORT_DOWN_G, alert_space, ports_down->window_surface, gp_dfb);						
	ports_down->window->MoveTo(ports_down->window, 57, 211-26);	
	ports_down->window->SetOpacity(ports_down->window, 255);					
	grid_free(grid);			
					
	//wan port	
	grid_init(alert_space, 0, 0, 60, 60);									
	grid=create_view_tree(grid_count, alert_space);			
	wan_port=create_icon_tree(grid, main_layer, win_dsc); 			
	icon_stackclass(wan_port, DWSC_UPPER);	
	wan_port->window->PutAtop(wan_port->window, ports_down->window);	
	draw_image_scale(WAN_PORT_UP_G, alert_space, wan_port->window_surface, gp_dfb);						
	wan_port->window->MoveTo(wan_port->window, 57+23, 211);				
	grid_free(grid); 	 		
	
	//lan ports																		
	grid=create_view_tree(grid_count, alert_space);				
	lan_port1=create_icon_tree(grid, main_layer, win_dsc); 
	icon_stackclass(lan_port1, DWSC_UPPER);		
	lan_port1->window->PutAtop(lan_port1->window, ports_down->window);	
	draw_image_scale(LAN_PORT_1_UP_G, alert_space, lan_port1->window_surface, gp_dfb);	
	lan_port1->window->MoveTo(lan_port1->window, 422+57, 211);	
	grid_free(grid); 	 					
	
	grid=create_view_tree(grid_count, alert_space);			
	lan_port2=create_icon_tree(grid, main_layer, win_dsc); 
	icon_stackclass(lan_port2, DWSC_UPPER);		
	lan_port2->window->PutAtop(lan_port2->window, ports_down->window);	
	draw_image_scale(LAN_PORT_2_UP_G, alert_space, lan_port2->window_surface, gp_dfb);	
	lan_port2->window->MoveTo(lan_port2->window, 323+57, 211);		
	grid_free(grid); 	 
	
	grid=create_view_tree(grid_count, alert_space);			
	lan_port3=create_icon_tree(grid, main_layer, win_dsc); 
	icon_stackclass(lan_port3, DWSC_UPPER);		
	lan_port3->window->PutAtop(lan_port3->window, ports_down->window);	
	draw_image_scale(LAN_PORT_3_UP_G, alert_space, lan_port3->window_surface, gp_dfb);				
	lan_port3->window->MoveTo(lan_port3->window, 223+57, 211);	
	grid_free(grid); 
	
	grid=create_view_tree(grid_count, alert_space);			
	lan_port4=create_icon_tree(grid, main_layer, win_dsc); 	
	icon_stackclass(lan_port4, DWSC_UPPER);	
	lan_port4->window->PutAtop(lan_port4->window, ports_down->window);	
	draw_image_scale(LAN_PORT_4_UP_G, alert_space, lan_port4->window_surface, gp_dfb);	
	lan_port4->window->MoveTo(lan_port4->window, 123+57, 211);			
	grid_free(grid); 	 		 		
	
	wan_port_status = get_switch_port_status(0);
	lan_port1_status = get_switch_port_status(1);
	lan_port2_status = get_switch_port_status(2);
	lan_port3_status = get_switch_port_status(3);
	lan_port4_status = get_switch_port_status(4);
			
	if(wan_port_status==0) wan_port->window->SetOpacity(wan_port->window, 0);
	else wan_port->window->SetOpacity(wan_port->window, 255);		
		
	if(lan_port1_status==0) lan_port1->window->SetOpacity(lan_port1->window, 0);
	else lan_port1->window->SetOpacity(lan_port1->window, 255);		
		
	if(lan_port2_status==0) lan_port2->window->SetOpacity(lan_port2->window, 0);
	else lan_port2->window->SetOpacity(lan_port2->window, 255);		
		
	if(lan_port3_status==0) lan_port3->window->SetOpacity(lan_port3->window, 0);
	else lan_port3->window->SetOpacity(lan_port3->window, 255);		
	
	if(lan_port4_status==0) lan_port4->window->SetOpacity(lan_port4->window, 0);
	else lan_port4->window->SetOpacity(lan_port4->window, 255);		
	
	sleep(3);	
							
	free(alert_space); 	
	icons_free(bg);
	icons_free(wan_port);	
	icons_free(lan_port1);
	icons_free(lan_port2);
	icons_free(lan_port3);
	icons_free(lan_port4);	
	icons_free(ports_down);			
}

	