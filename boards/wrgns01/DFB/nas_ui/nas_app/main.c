#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <directfb.h>
#include <time.h>
#include <signal.h>
#include <math.h>
#include <stdlib.h>
#include <xmldb.h>
#include <libxmldbc.h>
#include <sys/resource.h>
#include "alpha_dfb_define.h"
#include "nas_str_define.h"
#include "draw_tool.h"
#include "menu_tool.h"
#include "file_tool.h"
#include "fcrss_parser.h"
#include "fcrss_command.h"
#include "alert_center.h"
#include "detect_info.h"
#include "application.h"
#include "rgdb_node_define.h"

IDirectFB *gp_dfb;
IDirectFBDisplayLayer *main_layer;
IDirectFBSurface *page_surface, *title_window_surface;
IDirectFBFont *font_title;	
DFBWindowDescription win_dsc;
DFBRectangle *title_space,*screen_space, *menu_icon_space, *iframe_space;
RgbaType *rgba, *rgba2; 		
SlideObj *slide_info;
FcNode *main_node;
GridObj *grid, *iframe_grid;
IconObj *icon, *itime, *iframe;
TimeTab gTimeTab;		
int bright, photo_time_display;

#ifdef FRAMECHANNEL
	#ifdef UPNP_CONTROLLER
		static char *menu_title[]={TITLE_ROUTER_SET,TITLE_PHOTOS,TITLE_FRAMECHANNEL,TITLE_STATISTIC_SHOW,TITLE_STATUS,TITLE_WPS,"UPnP Media Controller","0x"};
		static char *menu_icon_path[]={MENU_0_G, APP_2_G, MENU_1_G, MENU_2_G, MENU_3_G, MENU_4_G, MENU_6_G,"0x"};	
	#else
		static char *menu_title[]={TITLE_ROUTER_SET,TITLE_PHOTOS,TITLE_FRAMECHANNEL,TITLE_STATISTIC_SHOW,TITLE_STATUS,TITLE_WPS,"0x"};
		static char *menu_icon_path[]={MENU_0_G, APP_2_G, MENU_1_G, MENU_2_G, MENU_3_G, MENU_4_G,"0x"};		
	#endif	
#else
	#ifdef UPNP_CONTROLLER
		static char *menu_title[]={TITLE_ROUTER_SET,TITLE_PHOTOS,"FrameIt",TITLE_STATISTIC_SHOW,TITLE_STATUS,TITLE_WPS,"UPnP Media Controller","0x"};
		static char *menu_icon_path[]={MENU_0_G, APP_2_G, MENU_5_G, MENU_2_G, MENU_3_G, MENU_4_G, MENU_6_G,"0x"};		
	#else
		static char *menu_title[]={TITLE_ROUTER_SET,TITLE_PHOTOS,"FrameIt",TITLE_STATISTIC_SHOW,TITLE_STATUS,TITLE_WPS,"0x"};
		static char *menu_icon_path[]={MENU_0_G, APP_2_G, MENU_5_G, MENU_2_G, MENU_3_G, MENU_4_G,"0x"};		
	#endif	
#endif

void Get_Sys_Time(time_t *time);
void* draw_time_obj(void *arg);
void get_timeout_from_xml(void);

extern void IDirectFBImageProvider_DFIFF();
extern void IDirectFBImageProvider_GIF();
extern void IDirectFBImageProvider_JPEG();
extern void IDirectFBImageProvider_PNG();
extern void IDirectFBFont_FT2();
extern IDirectFBEventBuffer* InitInputDeviceEvent(void);
extern int GetInputDeviceEventByType(IDirectFBEventBuffer *p_eventbuffer, int PType);
	
int main (int argc, char *argv[])
{  		
	IDirectFBImageProvider_DFIFF();
	IDirectFBImageProvider_GIF();
	IDirectFBImageProvider_JPEG();
	IDirectFBImageProvider_PNG();
	IDirectFBFont_FT2();
		 				
	IDirectFBWindow *title_window;	
	IDirectFBImageProvider *provider;	
	IDirectFBEventBuffer *p_eventbuffer;			
	DFBDisplayLayerConfig main_layer_config;	
	DFBGraphicsDeviceDescription gdsc;		
	DFBSurfaceDescription sur_dsc;			
	DFBFontDescription font_dsc;					
	DFBRectangle *time_space;				
	GridObj *time_grid;	
	pthread_t tid;			
	int grid_count=5, frame_count=2, node_count, key=0, slide_step=2, is_top_layer=1;	
	char *icon_select, root_dev_path[50]=STORAGE_DEV_PATH;
			
	//system set	
	nice(-19);	
	dprintf("1.main getpriority PRIO_PROCESS 	: %d\n",getpriority( PRIO_PROCESS, 0) );		
	/*{
		struct rlimit ptr;
		int flag;
		
		ptr.rlim_cur=40;
		ptr.rlim_max=40;
		flag=setrlimit(RLIMIT_NOFILE,&ptr);	
		printf("\nsetrlmit return value %d\n", flag);
		
		if (flag=getrlimit(RLIMIT_NOFILE,&ptr) != 0)
	    {
	        	printf("getrlimit error");
	        	exit(1);
	    }
    
    	printf("\nsetrlmit return value %d soft limit %d hard limit %d\n", flag, ptr.rlim_cur, ptr.rlim_max);
    }*/
	
	//start dfb init		
	DFBCHECK (DirectFBInit (&argc, &argv));  
	DFBCHECK (DirectFBCreate (&gp_dfb));  
	rgba = (RgbaType*)malloc(sizeof(RgbaType));
	rgba2 = (RgbaType*)malloc(sizeof(RgbaType));	
	set_rgba(rgba, 255, 255, 255, 255);							
	set_rgba(rgba2, 0, 0, 0, 0);			
	
//start dfb init		
  	//- main_layer		  	
  	DFBCHECK(gp_dfb->GetDisplayLayer( gp_dfb, DLID_PRIMARY, &main_layer ));
	if (!((gdsc.blitting_flags & DSBLIT_BLEND_ALPHACHANNEL) &&(gdsc.blitting_flags & DSBLIT_BLEND_COLORALPHA  )))     	
	{          
		main_layer_config.flags = DLCONF_BUFFERMODE;          
		main_layer_config.buffermode = DLBM_TRIPLE;          		
		main_layer->SetConfiguration( main_layer, &main_layer_config );     		
	}     		  	
	main_layer->SetCooperativeLevel( main_layer, DLSCL_ADMINISTRATIVE );
 	main_layer->GetConfiguration( main_layer, &main_layer_config );          	 	
 	main_layer->SetBackgroundColor(main_layer, 0, 0, 0, 255);  
	
	//-set event	  	    	                
  	p_eventbuffer = (IDirectFBEventBuffer*)InitInputDeviceEvent();	  	  	
  		
	if(argc==2&&!strcmp(argv[1], "test"))
	{		
		Test_Model(p_eventbuffer);
		exit(0);		
	}
	
    // - set background
	sur_dsc.flags = DSDESC_CAPS;
	main_layer_config.width=640;
	main_layer_config.height=480;
	sur_dsc.width  = main_layer_config.width;        
	sur_dsc.height = main_layer_config.height;        
    sur_dsc.caps  = DSCAPS_PRIMARY;     				 
  	DFBCHECK(gp_dfb->CreateSurface( gp_dfb, &sur_dsc, &page_surface ));  
  	DFBCHECK(gp_dfb->CreateImageProvider( gp_dfb, BG_0_G,&provider ));
  	screen_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));	
  	grid_init(screen_space, 0, 0, main_layer_config.width, main_layer_config.height); 	
	provider->RenderTo( provider, page_surface, screen_space );        
	provider->Release( provider );                                               		
  	main_layer->SetBackgroundImage( main_layer, page_surface );        
  	main_layer->SetBackgroundMode( main_layer, DLBM_IMAGE );      
  	
	//-set font  	
  	font_dsc.flags = DFDESC_HEIGHT;  	
	font_dsc.height = 38;
	font_title =(IDirectFBFont*)getFont(FONTS_DECKER, font_dsc, gp_dfb);	
									  	
//end dfb init

	win_dsc.flags  = ( DWDESC_POSX | DWDESC_POSY | DWDESC_WIDTH | DWDESC_HEIGHT | DWDESC_CAPS );       	
  	win_dsc.caps   = DWCAPS_ALPHACHANNEL;  		
  		  	   	
//start draw time   	
	//create time_space for settng surface size		  	  	
	time_space=(DFBRectangle*)malloc(sizeof(DFBRectangle));		
	grid_init(time_space, 180, 440, 300, 35);			
	time_grid=(GridObj*)malloc(sizeof(GridObj));
  	time_grid->rect=time_space;
  	time_grid->next=NULL;
  	
  	//create icon node
  	itime=create_icon_tree(time_grid, main_layer, win_dsc);	  	         	
  	
  	//get value of RGDB_PHOTO_TIME_DISPLAY node to decide clock showing or not
  	_u8 rgdb_val_buf[RGDBBUFFER_SIZE]; 
    memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
    xmldbc_get_wb(NULL, 0, RGDB_PHOTO_TIME_DISPLAY, rgdb_val_buf, RGDBBUFFER_SIZE);        
 	photo_time_display=atoi(rgdb_val_buf); 	  	  	 	
 	
   	//+++ Teresa, every 5 seconds to get timeout value from xml.    
	get_timeout_from_xml();
  	pthread_create(&tid, NULL, draw_time_obj, NULL);  	  	
  	grid_free(time_grid);  	  	 	
//end draw time

//start LCD brightness 	
	system("echo 1 > /proc/lcd");	
	memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
	xmldbc_get_wb(NULL, 0, RGDB_LCD_BRIGHTNESS , rgdb_val_buf, RGDBBUFFER_SIZE);
	bright=atoi(rgdb_val_buf);
	if(strcmp(rgdb_val_buf,"")==0)
	{
		dprintf("brightness(DB) no data,set brightness=64\n");
		bright=64;
		system("echo 64 > /proc/brightness");	 		
	}
	else
	{
		bright=atoi(rgdb_val_buf);
	} 	 	
//end LCD brightness 	 	
  	
//start create title window  		 		  		  	
  	title_space=(DFBRectangle*)malloc(sizeof(DFBRectangle));
  	grid_init(title_space, 0, 20, 640, 80);    	  	
  	set_windsc_xywh(&win_dsc, title_space);    
  	DFBCHECK(main_layer->CreateWindow( main_layer, &win_dsc, &title_window));               	  	  	
   	title_window->GetSurface( title_window, &title_window_surface );
   	title_window->SetOpacity(title_window, 255); 
   	title_window->SetStackingClass(title_window, DWSC_MIDDLE);         	
   	grid_init(title_space, 320, 20, 640, 80);   	        
//end create title window	
  	  	  	  	
//start draw menu_list init	           
	main_node=create_menu_tree(menu_title, menu_icon_path);			
	node_count=get_fcnode_count(main_node);				        
	iframe_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));	            	  		  	  		  		  		  	  	  		  		  		     	            	    	  	  	  							
	menu_icon_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));		
	grid_init(iframe_space, 0, 150, 640, 250);
	grid_init(menu_icon_space, 10, 10, 180, 230); 	
	grid=create_grid_tree(grid_count, iframe_space);		
	icon=create_icon_tree(grid, main_layer, win_dsc);	   		
	draw_icon_tree(main_node, icon, menu_icon_space, gp_dfb);								
	icon_stackclass(icon, DWSC_MIDDLE);	          	                             		
	slide_info = slide_init(grid, slide_step);	          	                             		
	grid_init(iframe_space, slide_info->x, slide_info->y, grid_count*(slide_info->len), grid->rect->h);	
	iframe_grid=create_view_tree(frame_count, iframe_space); 	
	iframe=create_icon_tree(iframe_grid, main_layer, win_dsc);		
	grid_free(iframe_grid);
	slide_info->frame=iframe;  			
	slide_info->frame2=iframe->right;	
	slide_info->icon_space=menu_icon_space;	
	blit_to_frame(main_node, slide_info, slide_info->frame, icon, gp_dfb);	
	slide_info->frame->window->SetOpacity(slide_info->frame->window, 255);					
//end draw menu_list init		           
	
	icon_select = main_node->brother_node->brother_node->title;	
	draw_title_string(icon_select, font_title, rgba, title_space, title_window_surface);   	 	    
//start storage dev init 	
    if(check_file_exist("/var/dev_need_format")==1) Detect_HW(p_eventbuffer);
    system("mkdir -p "PHOTO_TMP_DIR);
//end storage dev init		
		
	while(1)
	{			
		key = GetInputDeviceEventByType(p_eventbuffer, PTYPE_DEFAULT_API); 
																	
		if( key == DIKI_LEFT)						
		{		 							
			icon_select = main_node->brother_node->title;						
			draw_title_string(icon_select, font_title, rgba, title_space, title_window_surface);     	
			icon=slide_left(main_node, slide_info, icon, gp_dfb);	
			main_node=get_fcnode_head(main_node);											
		}	
		else if( key == DIKI_RIGHT)		
		{																	
			icon_select = main_node->brother_node->brother_node->brother_node->title;	
			draw_title_string(icon_select, font_title, rgba, title_space, title_window_surface);    
			icon=slide_right(main_node, slide_info, icon, gp_dfb);
			main_node=get_fcnode_head(main_node);						
		}
		else if ( key == DIKI_ENTER )
		{																		
			icon_select = main_node->brother_node->brother_node->title;				
			if(!strcmp(icon_select,TITLE_FRAMECHANNEL)) {															
				FrameChannel_Menu(p_eventbuffer, ALL_CHANNELS_EXE);
			}else if(!strcmp(icon_select,"FrameIt")) {						
				FrameIt_Display_App(p_eventbuffer);				
			}else if(!strcmp(icon_select,TITLE_WPS)) {					
				slide_info->frame->window->SetOpacity(slide_info->frame->window, 0);
				Wps_Menu(p_eventbuffer);
				slide_info->frame->window->SetOpacity(slide_info->frame->window, 255);				
			}else if(!strcmp(icon_select,TITLE_STATISTIC_SHOW)) {	
				slide_info->frame->window->SetOpacity(slide_info->frame->window, 0);
				Show_Statistics(p_eventbuffer, main_layer);																								
				slide_info->frame->window->SetOpacity(slide_info->frame->window, 255);				
			}else if(!strcmp(icon_select,TITLE_PHOTOS)) {																
				//create a UI direction to show folder that we selected
				IconObj *folder=folder_selected(FOLDER_SELECTED_G, gp_dfb, main_layer, win_dsc);				
				Album_Local_App(p_eventbuffer, root_dev_path, is_top_layer, folder);				
				icons_free(folder);																				
			}else if(!strcmp(icon_select,TITLE_STATUS)) {						
				Status_Menu(p_eventbuffer);								
			}else if(!strcmp(icon_select,TITLE_ROUTER_SET)) {						
				Setting_Menu(p_eventbuffer);				
			}else if(!strcmp(icon_select,"UPnP Media Controller")) {			
				system(ONBOARD_PATH"MicroMediaController &");         
				//system("/mnt/MicroMediaController &");         
				slide_info->frame->window->SetOpacity(slide_info->frame->window, 0);				
				UPnP_Setup_Start(p_eventbuffer);		
				slide_info->frame->window->SetOpacity(slide_info->frame->window, 255);				
				system("killall -9 MicroMediaController");  		
			}	
			redraw:
			grid_init(menu_icon_space, 10, 10, 180, 230);  
			draw_title_string(icon_select, font_title, rgba, title_space, title_window_surface); 			
			draw_icon_tree(main_node, icon, menu_icon_space, gp_dfb);					
			blit_to_frame(main_node, slide_info, slide_info->frame, icon, gp_dfb);		
			slide_info->frame->window->SetOpacity(slide_info->frame->window, 255);										
		}else if( key == DIKI_A || key == DIKI_B ){									
			Detect_USBMount(p_eventbuffer);			
			goto redraw;
		}	
		
		p_eventbuffer->Reset(p_eventbuffer);														
	}
	pthread_cancel(tid);	
	grid_free(grid);			
	delete_fcnode_tree(main_node);
	free(title_space);	
	free(menu_icon_space);	
	icons_free(icon);
	icons_free(iframe);	
	icons_free(itime);	
	title_window->Destroy(title_window);
	title_window->Release(title_window);
	title_window_surface->Release(title_window_surface);	
	font_title->Release (font_title);			
	p_eventbuffer->Release (p_eventbuffer);	
	page_surface->Release(page_surface );			
	gp_dfb->Release (gp_dfb);			
	return 0;
}

IDirectFBWindow* small_icon_loader(char *file_path, DFBRectangle *win_space, DFBRectangle *surface_space)
{
	IDirectFBWindow *window;	
	IDirectFBSurface *window_surface;
		  	  	
  	set_windsc_xywh(&win_dsc, win_space);
  	main_layer->CreateWindow( main_layer, &win_dsc, &window);
   	window->GetSurface( window, &window_surface);   	
   	draw_image(file_path, surface_space, window_surface, gp_dfb);		   	   	
   	window->SetStackingClass(window, DWSC_MIDDLE);         	   
	return window;
}

IDirectFBWindow* wan_status_icon(IDirectFBWindow *window)
{		
	DFBRectangle *win_space=NULL, *surface_space=NULL;
	int wan_status;
		
	if(window==NULL)
	{	
		win_space=(DFBRectangle*)malloc(sizeof(DFBRectangle));
		surface_space=(DFBRectangle*)malloc(sizeof(DFBRectangle));
	  	grid_init(win_space, 10, 440, 98, 44);    
	  	grid_init(surface_space, 0, 0, 98, 44);    	  		  	  	  	
	  	window=small_icon_loader(WAN_ON_G, win_space, surface_space);	  		  	
	  	free(win_space);
  		free(surface_space);
	}	
	
	wan_status=get_wan_status();
	if(wan_status==1) window->SetOpacity(window, 255);      		
	else window->SetOpacity(window, 0);  
	
  	return window;
}	

void get_timeout_from_xml(void)
{
	//Get Screen Saver time	    
	_u8 rgdb_val_buf[RGDBBUFFER_SIZE]; 
    memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
    xmldbc_get_wb(NULL, 0, RGDB_SCREENSAVER_SLEEPTIME , rgdb_val_buf, RGDBBUFFER_SIZE);
 	gTimeTab.ScreenSaverTimeout=atoi(rgdb_val_buf);
 	if(gTimeTab.ScreenSaverTimeout==0)	gTimeTab.ScreenSaverTimeout=NEVER_RUN_TIMEOUT;
 	
	//Get LCD sleep time	    
    memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
    xmldbc_get_wb(NULL, 0, RGDB_LCD_SLEEPTIME , rgdb_val_buf, RGDBBUFFER_SIZE);
 	gTimeTab.DisplaySaverTimeout=atoi(rgdb_val_buf);
 	if(gTimeTab.DisplaySaverTimeout==0)	gTimeTab.DisplaySaverTimeout=NEVER_RUN_TIMEOUT;
 	
    //Get HD sleep time
    memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
    xmldbc_get_wb(NULL, 0, RGDB_HD_SLEEPTIME , rgdb_val_buf, RGDBBUFFER_SIZE);
 	gTimeTab.HardDriveTimeout=atoi(rgdb_val_buf);
 	if(gTimeTab.HardDriveTimeout==0) gTimeTab.HardDriveTimeout=NEVER_RUN_TIMEOUT;
 	
}
	
void* draw_time_obj(void *arg)
{		
	pthread_detach(pthread_self());
	IDirectFBWindow *wan_window=NULL;
	IDirectFBFont *font;
	DFBFontDescription font_dsc;		
	DFBRectangle *space;			
	struct tm *p_time;	
	char TimeStr[128];
	char *wday[]={WEEK_SUN,WEEK_MON,WEEK_TUE,WEEK_WED,WEEK_THU,WEEK_FRI,WEEK_SAT};
	int  tmp_time=0;
		
	font_dsc.flags = DFDESC_HEIGHT;
	font_dsc.height = 26;
	font =(IDirectFBFont*)getFont(FONTS_DECKER, font_dsc, gp_dfb);
	space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	grid_init(space, 0, 0, 300, 35);			
	itime->window->SetOpacity(itime->window, 255); 
	if(photo_time_display==1) itime->window->SetStackingClass(itime->window, DWSC_UPPER);   
   	else itime->window->SetStackingClass(itime->window, DWSC_MIDDLE);     	   	
   	wan_window=wan_status_icon(wan_window);   	   	   						
   	
	while(1)
	{					
		if(tmp_time-- <= 0)
		{
			Get_Sys_Time(&gTimeTab.timep);
			//get_timezone();
			tmp_time=60;	// every 60 seconds sync real-time
		}			
		if(tmp_time%5==0)
		{
			//get_timeout_from_xml();			//+++ Teresa, update timeout from website and send KEY_H.
			wan_window=wan_status_icon(wan_window);												
		}	
		//p_time=gmtime(&gTimeTab.timep);
		p_time=localtime(&gTimeTab.timep);
		itime->window_surface->Clear(itime->window_surface,0,0,0,0);			
		sprintf(TimeStr,"%02d:%02d:%02d %s %d/%d/%d  %s", (p_time->tm_hour>12?p_time->tm_hour-12:p_time->tm_hour), p_time->tm_min, p_time->tm_sec, (p_time->tm_hour>12?"PM":"AM"), (1900+p_time->tm_year), (1+p_time->tm_mon), p_time->tm_mday, wday[p_time->tm_wday]);	
		draw_text(space, TimeStr, font, DSTF_TOPLEFT, rgba, itime->window_surface);						
		itime->window_surface->Flip(itime->window_surface, NULL, DSFLIP_NONE );		
		gTimeTab.timep++;
		sleep(1);					
	}	
	free(space);	
	font->Release (font);				
}

void Get_Sys_Time(time_t *ptime)
{
	time((time_t*)ptime);
	return;
}
