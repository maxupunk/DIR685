#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stddef.h>
#include <directfb.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctype.h>
#include "alpha_dfb_define.h"
#include "nas_str_define.h"
#include "draw_tool.h"
#include "menu_tool.h"
#include "file_tool.h"
#include "show_statistics.h"

//start extern variable or function from showimg.c
extern IDirectFB *gp_dfb;
extern IDirectFBDisplayLayer *main_layer;
extern IDirectFBSurface *page_surface;
extern DFBRectangle *screen_space;
extern IconObj *itime;
extern int GetInputDeviceEventByType(IDirectFBEventBuffer *p_eventbuffer, int PType); 
//end extern variable or function from showimg.c
extern TimeTab gTimeTab;

extern void GetHardDriveName(char *hd_devname);
extern char* get_mount_devpath(char *pkname);

typedef struct _Draw_Data{
	IDirectFBWindow *dot_window;
	IDirectFBSurface *window_surface,*dot_winsurface;
	DFBRectangle *space;
	RgbaType *text_rga; 
	IDirectFBFont *font,*font_day,*font_meridian;
}Draw_Data;

enum GTimeStrArray{
	GTSA_HOUR_H=0,
	GTSA_HOUR_L,
	GTSA_MIN_H,
    GTSA_MIN_L,
    GTSA_DOT,
    GTSA_AM,
    GTSA_PM
};
#define SIZEOF_GTimeStrArray 7

#define DEFAULT_TIMESTR_POS_H 70
//[x][0]:pos_x ; [x][1]:pos_y ;
//{hour_h},{hour_l},{min_h},{min_l},{dot},{meridian_am},{meridian_pm}
int gDefault_TimeStr_Pos[7][2]={{180,DEFAULT_TIMESTR_POS_H},{260,DEFAULT_TIMESTR_POS_H},{380,DEFAULT_TIMESTR_POS_H},	\
	{460,DEFAULT_TIMESTR_POS_H},{300,DEFAULT_TIMESTR_POS_H},{540,90},{540,150}};
		

void free_Draw_Data(Draw_Data *send_data)
{
	send_data->window_surface->Release(send_data->window_surface);	
	send_data->dot_winsurface->Release(send_data->dot_winsurface);	
	send_data->dot_window->Destroy(send_data->dot_window);/* can disregard this */
	send_data->dot_window->Release(send_data->dot_window);
	send_data->font->Release(send_data->font);	
	send_data->font_day->Release(send_data->font_day);	
	send_data->font_meridian->Release(send_data->font_meridian);	
	free(send_data->space);
	free(send_data->text_rga);
	free(send_data);
	return;
}

/* devpath=>'/tmp/HD/'; return=>path */
void GetBGPath(char *devpath, char *path)
{
	DIR * dir;
	struct dirent * ptr;
	
	dir=opendir(devpath);
	while((ptr = readdir(dir))!=NULL)
	{
		if(strcasecmp(ptr->d_name,SCREEN_SAVER_BG)==0)
		{
			sprintf(path,"%s%s",devpath,ptr->d_name);
			break;
		}
	}
	closedir(dir);
	return;
}
	
void* StartDraw(void *arg)
{
	Draw_Data *indata=(Draw_Data *) arg;
	int text_width=0;	
	struct tm *p_time;
	char TimeStr[256],datestr[4][2];
	int org_year=0,org_mon=0,org_day=0,org_hour=0,org_min=0;
	int update_flag=0,count=0,i;
	
	/* to record time string, datestr[0][0] include 0~9 and datestr[0][1] is always '\0' */
	memset(datestr,0,sizeof(datestr));
	while(1)
	{
		p_time=localtime(&gTimeTab.timep);
		update_flag=0;
		if(org_year!=p_time->tm_year)			{org_year=p_time->tm_year;update_flag++;}
		if(org_mon!=(1+p_time->tm_mon))			{org_mon=(1+p_time->tm_mon);update_flag++;}
		if(org_day!=p_time->tm_mday)			{org_day=p_time->tm_mday;update_flag++;}
		if(org_hour!=p_time->tm_hour)			{org_hour=p_time->tm_hour;update_flag++;}
		if(org_min!=p_time->tm_min)				{org_min=p_time->tm_min;update_flag++;}
		
		if(update_flag)
		{
			indata->window_surface->Clear( indata->window_surface, 0, 0, 0, 0);
			grid_init(indata->space, 175, 410, 200, 70);
			set_rgba(indata->text_rga, 0xFF, 0xFF, 0xFF, 255);
			sprintf(TimeStr,"%04d-%02d-%02d", (1900+p_time->tm_year), (1+p_time->tm_mon), p_time->tm_mday);
			text_width = draw_text(indata->space, TimeStr,indata->font_day, DSTF_TOPLEFT, indata->text_rga, indata->window_surface);
			
			if(p_time->tm_hour >= 12)	//pm
			{
				if(p_time->tm_hour > 12)
				{
					datestr[0][0]=(char)((p_time->tm_hour-12)/10+'0');
					datestr[1][0]=(char)((p_time->tm_hour-12)%10+'0');
				}
				else
				{
					datestr[0][0]=(char)(p_time->tm_hour/10+'0');
					datestr[1][0]=(char)(p_time->tm_hour%10+'0');
				}
				grid_init(indata->space, gDefault_TimeStr_Pos[GTSA_PM][0], gDefault_TimeStr_Pos[GTSA_PM][1], 200, 70);
				text_width = draw_text(indata->space, DEFAULT_MERIDIAN_PM,indata->font_meridian, DSTF_TOPRIGHT, indata->text_rga, indata->window_surface);
			}
			else	//am
			{
				datestr[0][0]=(char)(p_time->tm_hour/10+'0');
				datestr[1][0]=(char)(p_time->tm_hour%10+'0');
				grid_init(indata->space, gDefault_TimeStr_Pos[GTSA_AM][0], gDefault_TimeStr_Pos[GTSA_AM][1], 200, 70);
				text_width = draw_text(indata->space, DEFAULT_MERIDIAN_AM,indata->font_meridian, DSTF_TOPRIGHT, indata->text_rga, indata->window_surface);
			}
			datestr[2][0]=(char)(p_time->tm_min/10+'0');
			datestr[3][0]=(char)(p_time->tm_min%10+'0');
			
			for(i=0;i<4 /* drawing number of time-string */ ;i++)
			{
				grid_init(indata->space, gDefault_TimeStr_Pos[i][0], gDefault_TimeStr_Pos[i][1], 200, 70);
				text_width = draw_text(indata->space, datestr[i],indata->font, DSTF_TOPRIGHT, indata->text_rga, indata->window_surface);
				grid_init(indata->space, gDefault_TimeStr_Pos[i][0], gDefault_TimeStr_Pos[i][1], 200, 70);
				text_width = draw_text(indata->space, datestr[i],indata->font, DSTF_TOPRIGHT, indata->text_rga, indata->window_surface);
				grid_init(indata->space,gDefault_TimeStr_Pos[i][0], gDefault_TimeStr_Pos[i][1], 200, 70);
				text_width = draw_text(indata->space, datestr[i],indata->font, DSTF_TOPRIGHT, indata->text_rga, indata->window_surface);
				grid_init(indata->space, gDefault_TimeStr_Pos[i][0], gDefault_TimeStr_Pos[i][1], 200, 70);
				text_width = draw_text(indata->space, datestr[i],indata->font, DSTF_TOPRIGHT, indata->text_rga, indata->window_surface);
			}
			indata->window_surface->Flip( indata->window_surface, NULL, DSFLIP_BLIT );
		}
		if((count++)%2==0)
			indata->dot_window->SetOpacity(indata->dot_window,0);
		else
			indata->dot_window->SetOpacity(indata->dot_window,255);
		
		sleep(1);
	}
}

void create_time_dot_window(Draw_Data *send_data)
{		
	DFBWindowDescription win_dsc;
	
	win_dsc.flags  = ( DWDESC_POSX | DWDESC_POSY | DWDESC_WIDTH | DWDESC_HEIGHT | DWDESC_CAPS );
	win_dsc.posx = gDefault_TimeStr_Pos[GTSA_DOT][0]-35;
	win_dsc.posy = gDefault_TimeStr_Pos[GTSA_DOT][1];
	win_dsc.width  = 80;
	win_dsc.height = 160;
	win_dsc.caps   = DWCAPS_ALPHACHANNEL;
	DFBCHECK(main_layer->CreateWindow( main_layer, &win_dsc, &send_data->dot_window));
	send_data->dot_window->GetSurface( send_data->dot_window, &send_data->dot_winsurface );
	send_data->dot_window->SetStackingClass(send_data->dot_window, DWSC_UPPER);	
	send_data->dot_winsurface->Clear( send_data->dot_winsurface, 0, 0, 0, 0);
	set_rgba(send_data->text_rga, 0xff, 0xff, 0xff, 0xff);
	grid_init(send_data->space, 0, 0, 80, 160);
	draw_text(send_data->space, DEFAULT_TIMESTR_PART,send_data->font, DSTF_TOPLEFT, send_data->text_rga, send_data->dot_winsurface);
	return;
}

int Show_Screen_Saver(IDirectFBEventBuffer *p_eventbuffer)
{		
	IDirectFBWindow *bg_window, *window;
	DFBWindowDescription win_dsc;	
	IDirectFBSurface *bg_surface;
	Draw_Data *send_data=(Draw_Data*)malloc(sizeof(Draw_Data));
	DFBFontDescription font_dsc;
	pthread_t thread_id;
	char devname[256],devallpath[256],*devpath=NULL;
	int key=0,i;
	
	font_dsc.flags = DFDESC_HEIGHT;
	font_dsc.height = 160;
	send_data->font =(IDirectFBFont*)getFont(FONTS_DIGI, font_dsc, gp_dfb);
	font_dsc.height = 62;
	send_data->font_day =(IDirectFBFont*)getFont(FONTS_DIGI, font_dsc, gp_dfb);
	font_dsc.height = 50;
	send_data->font_meridian =(IDirectFBFont*)getFont(FONTS_DECKER, font_dsc, gp_dfb);
	
	send_data->space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	send_data->text_rga = (RgbaType*)malloc(sizeof(RgbaType));
	//start draw menu init	               
	win_dsc.flags  = ( DWDESC_POSX | DWDESC_POSY | DWDESC_WIDTH | DWDESC_HEIGHT | DWDESC_CAPS );       	  	
	win_dsc.caps   = DWCAPS_NONE;  				
	win_dsc.posx = 0;
	win_dsc.posy = 0;
	win_dsc.width  = screen_space->w;        
	win_dsc.height = screen_space->h;  
			
	DFBCHECK(main_layer->CreateWindow( main_layer, &win_dsc, &bg_window));	
	bg_window->GetSurface( bg_window, &bg_surface );
	bg_surface->Clear( bg_surface, 0, 0, 0, 255);
	bg_surface->SetDrawingFlags( bg_surface, DSDRAW_SRC_PREMULTIPLY | DSDRAW_BLEND );
	
	/* get hard drive path and get default SCREEN_SAVER_BG */
	memset(devname,0,sizeof(devname));
	memset(devallpath,0,sizeof(devallpath));
	GetHardDriveName(devname);
	if(strcmp(devname,"")!=0)
	{
		devpath=get_mount_devpath(devname);
		if(strcmp(devpath,"")!=0)
			GetBGPath(devpath, devallpath);
		free(devpath);
	}
	
	//start to draw background
	if(check_file_exist(devallpath))
	{
		draw_image_scale(devallpath,screen_space, bg_surface,gp_dfb);
		bg_surface->SetColor( bg_surface, 0xFF, 0xFF, 0xFF, 0x60 );
		bg_surface->FillRectangle( bg_surface, 0, 0, screen_space->w, screen_space->h );
	}
	
	set_rgba(send_data->text_rga, 0xff, 0xff, 0xff, 0x35);
	for(i=0;i<SIZEOF_GTimeStrArray;i++)
	{
		switch(i){
			case GTSA_DOT:
				grid_init(send_data->space, gDefault_TimeStr_Pos[i][0], gDefault_TimeStr_Pos[i][1], 200, 70);
				draw_text(send_data->space, DEFAULT_TIMESTR_PART,send_data->font, DSTF_TOPRIGHT, send_data->text_rga, bg_surface);
				break;
			case GTSA_AM:
				grid_init(send_data->space, gDefault_TimeStr_Pos[i][0], gDefault_TimeStr_Pos[i][1], 200, 70);
				draw_text(send_data->space, DEFAULT_MERIDIAN_AM,send_data->font_meridian, DSTF_TOPRIGHT, send_data->text_rga, bg_surface);
				break;
			case GTSA_PM:
				grid_init(send_data->space, gDefault_TimeStr_Pos[i][0], gDefault_TimeStr_Pos[i][1], 200, 70);
				draw_text(send_data->space, DEFAULT_MERIDIAN_PM,send_data->font_meridian, DSTF_TOPRIGHT, send_data->text_rga, bg_surface);
				break;
			default:
				grid_init(send_data->space, gDefault_TimeStr_Pos[i][0], gDefault_TimeStr_Pos[i][1], 200, 70);
				draw_text(send_data->space, "8",send_data->font, DSTF_TOPRIGHT, send_data->text_rga, bg_surface);
				break;
		}
	}
	//end to draw background

	bg_window->SetOpacity(bg_window,255);			
	win_dsc.caps   = DWCAPS_ALPHACHANNEL;  
	DFBCHECK(main_layer->CreateWindow( main_layer, &win_dsc, &window));	
	window->GetSurface( window, &send_data->window_surface );	
	window->SetStackingClass(window, DWSC_UPPER);
	window->SetOpacity(window,255);			
	
	create_time_dot_window(send_data);
	
	dprintf("\n Starting run Screen Saving!\n");	
	pthread_create(&thread_id, NULL, StartDraw, send_data);
	itime->window->SetOpacity(itime->window, 0); 
	GetInputDeviceEventByType(p_eventbuffer, PTYPE_SCREEN_SAVER);
	pthread_cancel( thread_id );
	pthread_join( thread_id, NULL );
	
	free_Draw_Data(send_data);
	
	bg_surface->Release(bg_surface);
	window->Destroy(window);/* can disregard this */
	window->Release( window );
	bg_window->Destroy(bg_window);/* can disregard this */
	bg_window->Release(bg_window );
	dprintf("\nEnding run Screen Saving!\n");		
	itime->window->SetOpacity(itime->window, 255); 
	return key;
}
