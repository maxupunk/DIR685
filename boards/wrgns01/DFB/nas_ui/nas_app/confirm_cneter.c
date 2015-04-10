#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <pthread.h>
#include <stddef.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <directfb.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "alpha_dfb_define.h"
#include "nas_str_define.h"
#include "menu_tool.h"
#include "confirm_center.h"
#include "detect_info.h"
#include "alert_center.h"

//start extern variable or function from main.c
extern IDirectFB *gp_dfb;
extern DFBWindowDescription win_dsc;
extern IDirectFBDisplayLayer *main_layer;
extern DFBRectangle *screen_space;
extern int GetInputDeviceEventByType(IDirectFBEventBuffer *p_eventbuffer, int PType);

int gYesOrNo=1;	//Yes:1, No:0
int gRadio_Selected_Index=1;	//selected index from 1~
int gdraw_act_ui_flag=0;

typedef struct _MessageCenterThreadTable
{
	IconObj *icon;
	DFBRectangle *screen_info_space;
	GridObj *grid;
	Messages *ptmsg;
	int tmsg_size;
	char *comm;
	char *message;
	int *flag;					/* additional flag */
}MessageCenterThreadTable;

IDirectFBFont* InitFont(int size)
{
	IDirectFBFont *font;
	DFBFontDescription font_dsc;
	
	font_dsc.flags = DFDESC_HEIGHT;
	font_dsc.height = size;
	font =(IDirectFBFont*)getFont(FONTS_DECKER, font_dsc, gp_dfb);
	return font;
}

/*
Draw message box style
*/
void DrawBackground(IDirectFBSurface *surface, DFBRectangle *space, RgbaType *text_rga, int page_width, int page_height)
{
	// use background from confirm.png
	grid_init(space, 0, 0, page_width, page_height);
	draw_image(CONFIRM_BG, space, surface, gp_dfb);
	/*grid_init(space, 0, 0, page_width, page_height);
	set_rgba(text_rga, 0xff, 0xff, 0xff, 255);
	clear_screen(text_rga, space, surface);
	grid_init(space, 5, 5, page_width-10, page_height-10);
	set_rgba(text_rga, 0, 0, 0, 255);
	clear_screen(text_rga, space, surface);*/
}

int draw_select_item(IDirectFBSurface *surface, int page_width, int page_height, int segment)
{
	DFBRectangle *space;
	RgbaType *text_rga_y,*text_rga_n;
	IDirectFBFont *fontT=InitFont(34);
	
	space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	text_rga_y = (RgbaType*)malloc(sizeof(RgbaType));
	text_rga_n = (RgbaType*)malloc(sizeof(RgbaType));
	
	if(segment==1)
	{
		set_rgba(text_rga_y, 0x4C, 0xFC, 0xFF, 255);	//0x05, 0xD3, 0xFF
		set_rgba(text_rga_n, 0xAD, 0xAD, 0xAD, 255);	//0x5A, 0x5A, 0x5A
	}
	else
	{
		set_rgba(text_rga_y, 0xAD, 0xAD, 0xAD, 255);
		set_rgba(text_rga_n, 0x4C, 0xFC, 0xFF, 255);
	}
	grid_init(space, 170, 300, 100, 50);
	draw_text(space, SELECT_YES,fontT, DSTF_LEFT, text_rga_y, surface);
	grid_init(space, 300, 300, 100, 50);
	draw_text(space, SELECT_NO ,fontT, DSTF_LEFT, text_rga_n, surface);
	
	surface->Flip( surface, NULL, DSFLIP_NONE );
	
	fontT->Release( fontT );
	free(text_rga_y);
	free(text_rga_n);
	free(space);
	return segment;
}

void draw_detected_ui(IconObj *icon, DFBRectangle *main_space, Messages *ptmsg, int tmsg_size, int havebtn)
{
	DFBRectangle *space;
	IDirectFBFont *font=InitFont(34);
	RgbaType *text_rga;
	int page_width=main_space->w,page_height=main_space->h,i;
	int draw_text_width=0,msg_size=0;
	char buffer[128],tmsg[DEFAULT_MSG_MAX_LINE][DEFAULT_MSG_MAX_TEXT_LENGTH],*pstr;
	
	space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	text_rga = (RgbaType*)malloc(sizeof(RgbaType));
	
	DrawBackground(icon->window_surface,space,text_rga,page_width, page_height);
	set_rgba(text_rga, 0xff, 0xff, 0xff, 255);

	for(i=0;i<tmsg_size;i++)
	{
		if(strstr(ptmsg[i].msg,"\n"))
		{
			strcpy(buffer,ptmsg[i].msg);
			strcpy(tmsg[msg_size++],strtok(buffer,"\n"));
			while((pstr=strtok(NULL,"\n"))!=NULL)
				strcpy(tmsg[msg_size++],pstr);
		}
		else
			strcpy(tmsg[msg_size++],ptmsg[i].msg);
	}
	for(i=0;i<msg_size;i++)
	{
		grid_init(space, page_width/2, page_height/(msg_size+1)*(i+1), page_width, page_height);
		draw_text_width=draw_text(space, tmsg[i],font, DSTF_CENTER, text_rga, icon->window_surface);
	}

	if(havebtn==HAVECONFIRM)
		gYesOrNo = draw_select_item(icon->window_surface, page_width, page_height, gYesOrNo);
		
	icon->window->SetOpacity(icon->window,255);
	icon->window->SetStackingClass(icon->window, DWSC_UPPER); 
	icon->window->RaiseToTop(icon->window);
	font->Release( font );
	free(text_rga);
	free(space);
}

void draw_message_ui(IconObj *icon, DFBRectangle *main_space, char *ptitle, Messages *ptmsg, int tmsg_size, int selected, int havebtn)
{
	DFBRectangle *space;
	IDirectFBFont *font=InitFont(34);
	RgbaType *text_rga;	
	int page_width,page_height,mid_area_height,i;
	int draw_text_width=0,msg_size=0,j,k;
	char buffer[DEFAULT_MSG_MAX_LINE][128],*pstr;
	char tmsg[DEFAULT_MSG_MAX_LINE][DEFAULT_MSG_MAX_LINE][DEFAULT_MSG_MAX_TEXT_LENGTH];
	
	page_width=main_space->w;
	page_height=main_space->h;
	mid_area_height=page_height-100;//up+down=100
	space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	text_rga = (RgbaType*)malloc(sizeof(RgbaType));
	
	DrawBackground(icon->window_surface,space,text_rga,page_width, page_height);
	set_rgba(text_rga, 0xff, 0xff, 0xff, 255);
	/* Draw title area */
	grid_init(space, page_width/2, 20, page_width, page_height);
	draw_text(space, ptitle, font, DSTF_TOPCENTER, text_rga, icon->window_surface);
	for(i=0;i<tmsg_size;i++)
	{
		j=0;
		if(strstr(ptmsg[i].msg,"\n"))
		{
			strcpy(buffer[i],ptmsg[i].msg);
			sprintf(tmsg[i][j++],"%d. %s",i+1,strtok(buffer[i],"\n"));
			msg_size++;
			while((pstr=strtok(NULL,"\n"))!=NULL)
			{
				strcpy(tmsg[i][j++],pstr);
				msg_size++;
			}
		}
		else
		{
			sprintf(tmsg[i][j++],"%d. %s",i+1,ptmsg[i].msg);
			msg_size++;
		}
		strcpy(tmsg[i][j],"\0");
	}
	for(i=0,k=0;i<tmsg_size&&k<msg_size;i++)
	{
		j=0;
		if(selected==(i+1))	set_rgba(text_rga, 0x4C, 0xFC, 0xFF, 255); //0x05, 0xD3, 0xFF
		else			set_rgba(text_rga, 0xAD, 0xAD, 0xAD, 255); //0x5A, 0x5A, 0x5A
		while(strcmp(tmsg[i][j],"\0")!=0)
		{
			grid_init(space, 50, (mid_area_height/(msg_size+1)*(k+1))+50, page_width, mid_area_height);
			draw_text_width=draw_text(space, tmsg[i][j], font, DSTF_LEFT, text_rga, icon->window_surface);
			j++;k++;
		}
	}
	
	if(havebtn==HAVECONFIRM)
		gYesOrNo = draw_select_item(icon->window_surface, page_width, page_height, gYesOrNo);
	
	icon->window->SetOpacity(icon->window,255);
	font->Release( font );
	free(text_rga);
	free(space);
}

void* draw_act_ui(void *arg)
{
	FILE *fp;
	MessageCenterThreadTable *ttable=(MessageCenterThreadTable *)arg;
	DFBRectangle *space;
	IDirectFBFont *font=InitFont(34);
	RgbaType *text_rga;
	int page_width=ttable->screen_info_space->w;
	int page_height=ttable->screen_info_space->h;
	char percentage[6],msg_str[64];
	
	space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	text_rga = (RgbaType*)malloc(sizeof(RgbaType));
	
	ttable->icon->window->SetOpacity(ttable->icon->window,255);
	while(gdraw_act_ui_flag)
	{
		DrawBackground(ttable->icon->window_surface,space,text_rga,page_width, page_height);
		set_rgba(text_rga, 0xff, 0xff, 0xff, 255);
		grid_init(space, page_width/2, page_height/2, page_width, page_height);
	
		memset(percentage,0,sizeof(percentage));
		memset(msg_str,0,sizeof(msg_str));
		
		if((fp = popen(ttable->comm, "r"))!=NULL)
		{
			fscanf(fp,"%s",percentage);
			if(strcmp(percentage,"")==0)	
				strcpy(percentage,"0");
			pclose(fp);
		}
		sprintf(msg_str,"%s ... %s%%",ttable->message,percentage);
		draw_text(space, msg_str, font, DSTF_CENTER, text_rga, ttable->icon->window_surface);
		
		ttable->icon->window_surface->Flip( ttable->icon->window_surface, NULL, DSFLIP_NONE );
		sleep(2);
	}
	
	font->Release( font );
	free(text_rga);
	free(space);
	return NULL;
}

/*	
Purpose of draw_action_in_process :
	draw the small box showing "detecting" or "unmounting" proccess.
*/
void* draw_action_in_process(void *arg)
{
	MessageCenterThreadTable *ttable=(MessageCenterThreadTable *)arg;
	DFBRectangle *space;
	IDirectFBFont *font=InitFont(34);
	RgbaType *text_rga;
	int page_width=ttable->screen_info_space->w;
	int page_height=ttable->screen_info_space->h;
	
	space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	text_rga = (RgbaType*)malloc(sizeof(RgbaType));
	
	//sprintf(msg_str, "%s %s", ttable->ptmsg[0].msg, ttable->ptmsg[1].msg);
	//dprintf("ttable->ptmsg[0].msg : %s\n", ttable->ptmsg[0].msg);
	//dprintf("ttable->ptmsg[1].msg : %s\n", ttable->ptmsg[1].msg);
	
	ttable->icon->window->SetOpacity(ttable->icon->window,255);
	
	DrawBackground(ttable->icon->window_surface,space,text_rga,page_width, page_height);
	set_rgba(text_rga, 0xff, 0xff, 0xff, 255);
	grid_init(space, page_width/2, page_height/2, page_width, page_height);
	
	draw_text(space, ttable->ptmsg[0].msg, font, DSTF_CENTER, text_rga, ttable->icon->window_surface);
	
	ttable->icon->window_surface->Flip( ttable->icon->window_surface, NULL, DSFLIP_NONE );
	
	while( *(ttable->flag) )
	{
		sleep(1); //check every seconds, and wait to be closed
	}
	
	font->Release( font );
	free(text_rga);
	free(space);
	
	return NULL;
}

void receive_specific_key(IDirectFBEventBuffer *p_eventbuffer, int type, pthread_t thread_id, MessageCenterThreadTable *mcttable,int *gflag)
{
	int key=0;
	switch(type)
	{
		case PTYPE_DETECTING_DEVICE :		/* detecting process */
			while(1)
			{
				key = GetInputDeviceEventByType(p_eventbuffer,PTYPE_DETECTING_DEVICE);
				dprintf("GetInputDeviceEventByType success\n");
				if(key == DIKI_I || key == DIKI_F || key == DIKI_G || key == DIKI_E)
				{
					*gflag = 0;
					pthread_join(thread_id, NULL);
					free(mcttable->screen_info_space);
					grid_free(mcttable->grid);
					icons_free(mcttable->icon);
					free(mcttable);
				}
				
				if(key == DIKI_I)
				{
					dprintf("user key press DIKI_I, and detect Hard Drive mount success\n");
					Detect_HWMount(p_eventbuffer);
					break;	
				} else if (key == DIKI_F)
				{
					dprintf("user key press DIKI_F, and detect Hard Drive format\n");
					Detect_HW(p_eventbuffer);
					break;	
				} else if (key == DIKI_E)
				{
					dprintf("user key press DIKI_E. Display error message\n");
					Alert_Center(p_eventbuffer, DETECT_INFO_DODETECT_ERROR);
					break;	
				}
				
				p_eventbuffer->Reset(p_eventbuffer);
			}
			break;
		case PTYPE_UNMOUNTING_DEVICE :		/* unmounting process */
			while(1)
			{
				key = GetInputDeviceEventByType(p_eventbuffer,PTYPE_UNMOUNTING_DEVICE);
				dprintf("GetInputDeviceEventByType success\n");
				if(key == DIKI_L || key == DIKI_M)
				{
					*gflag = 0;
					pthread_join(thread_id, NULL);
					free(mcttable->screen_info_space);
					grid_free(mcttable->grid);
					icons_free(mcttable->icon);
					free(mcttable);
				}
				
				if(key == DIKI_L)
				{
					Alert_Center(p_eventbuffer, DETECT_INFO_DOUNMOUNTING_SUCCESS);
					break;
				}
				else if(key == DIKI_M)
				{
					Alert_Center(p_eventbuffer, DETECT_INFO_DOUNMOUNTING_ERROR);
					break;
				}
				p_eventbuffer->Reset(p_eventbuffer);
			}
			break;
		default :
			break;
	}
}

void show_process_control(IDirectFBEventBuffer *p_eventbuffer, Messages *ptmsg, int tmsg_size, int *g_active_flag, void* (*pfunc)(void), int type)
{
	DFBRectangle *screen_info_space;
	GridObj *grid;
	IconObj *icon;							
	int grid_count=1;
	
	pthread_t thread_id;
	MessageCenterThreadTable *mcttable=NULL;
	
	//start draw menu init	        
	screen_info_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	grid_init(screen_info_space, 70*2, 70*2, screen_space->w-(65*4), screen_space->h-(70*4));
	grid=create_view_tree(grid_count, screen_info_space);			
	icon=create_icon_tree(grid, main_layer, win_dsc);
	
	*g_active_flag=1;
	//thread need data
	mcttable=(MessageCenterThreadTable*)malloc(sizeof(MessageCenterThreadTable));
	mcttable->icon=icon;
	mcttable->screen_info_space=screen_info_space;
	mcttable->ptmsg=ptmsg;
	mcttable->tmsg_size=tmsg_size;
	mcttable->flag=g_active_flag;
	mcttable->grid=grid;
	
	pthread_create(&thread_id, NULL, pfunc, mcttable);
	receive_specific_key(p_eventbuffer, type, thread_id, mcttable, g_active_flag);
	return;
}

/*
Input:
	ptmsg(Message) is struct char array and this will draw multiple line message in accordance with tmsg_size,
	and include confirm(select) box. tmsg_size is struct array length.
Return:
	user choose answer include yes:1 or no:0
*/
int Confirm_Center(IDirectFBEventBuffer *p_eventbuffer, Messages *ptmsg, int tmsg_size)
{
	return Confirm_Center_Control(p_eventbuffer, ptmsg, tmsg_size, SELECT_FREE);
}

int Confirm_Center_Control(IDirectFBEventBuffer *p_eventbuffer, Messages *ptmsg, int tmsg_size, int free_select)
{
	DFBRectangle *screen_info_space;
	GridObj *grid;
	IconObj *icon;
	int key = 0; 						
	int grid_count=1;
	
	//start draw menu init	        
	screen_info_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	grid_init(screen_info_space, 70, 70, screen_space->w-(70*2), screen_space->h-(70*2));
	grid=create_view_tree(grid_count, screen_info_space);			
	icon=create_icon_tree(grid, main_layer, win_dsc); 
	
	draw_detected_ui(icon, screen_info_space, ptmsg, tmsg_size, HAVECONFIRM);
	
	while(1)
	{
		key = GetInputDeviceEventByType(p_eventbuffer,PTYPE_DETECT_INFO);
		if( key == DIKI_ENTER ){
			break;
		}
		else if( key == DIKI_LEFT ){
			if(free_select==SELECT_LIMIT)
			{
				if(gYesOrNo==0)
					gYesOrNo = draw_select_item(icon->window_surface, screen_info_space->w, screen_info_space->h, 1);
			}
			else
			{
				if(gYesOrNo==0)
					gYesOrNo = draw_select_item(icon->window_surface, screen_info_space->w, screen_info_space->h, 1);
				else
					gYesOrNo = draw_select_item(icon->window_surface, screen_info_space->w, screen_info_space->h, 0);
			}
			
		}
		else if( key == DIKI_RIGHT ){
			if(free_select==SELECT_LIMIT)
			{
				if(gYesOrNo==1)
					gYesOrNo = draw_select_item(icon->window_surface, screen_info_space->w, screen_info_space->h, 0);
			}
			else
			{
				if(gYesOrNo==0)
					gYesOrNo = draw_select_item(icon->window_surface, screen_info_space->w, screen_info_space->h, 1);
				else
					gYesOrNo = draw_select_item(icon->window_surface, screen_info_space->w, screen_info_space->h, 0);
			}			
		}
		p_eventbuffer->Reset(p_eventbuffer);
	}
	
	free(screen_info_space);
	grid_free(grid);
	icons_free(icon);
	return gYesOrNo;
}

/*
Input:
	ptmsg(Message) is struct char array and this will draw multiple line message in accordance with tmsg_size.
	tmsg_size is struct array length.	First draw warning message from ptmsg, and execute pfunc. 
	when finished to show alert_center message from pfunc return result(*char).
*/
void Message_Center(IDirectFBEventBuffer *p_eventbuffer, Messages *ptmsg, int tmsg_size, char* (*pfunc)(void))
{
	Message_Center_Control(p_eventbuffer, ptmsg, tmsg_size, pfunc, NULL, NULL);
}

void Message_Center_Control(IDirectFBEventBuffer *p_eventbuffer, Messages *ptmsg, int tmsg_size, char* (*pfunc)(void), char *comm, char *staymsg)
{
	DFBRectangle *screen_info_space;
	GridObj *grid;
	IconObj *icon;							
	int grid_count=1;
	char *result;
	pthread_t thread_id;
	MessageCenterThreadTable *mcttable=NULL;
	
	//start draw menu init	        
	screen_info_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	grid_init(screen_info_space, 70, 70, screen_space->w-(70*2), screen_space->h-(70*2));
	grid=create_view_tree(grid_count, screen_info_space);			
	icon=create_icon_tree(grid, main_layer, win_dsc); 
	
	if(comm==NULL)
		draw_detected_ui(icon, screen_info_space, ptmsg, tmsg_size, DONOTHAVECONFIRM);
	else
	{
		gdraw_act_ui_flag=1;
		//thread need data
		mcttable=(MessageCenterThreadTable*)malloc(sizeof(MessageCenterThreadTable));
		mcttable->icon=icon;
		mcttable->screen_info_space=screen_info_space;
		mcttable->ptmsg=ptmsg;
		mcttable->tmsg_size=tmsg_size;
		mcttable->comm=comm;
		mcttable->message=staymsg;
		pthread_create(&thread_id, NULL, draw_act_ui, mcttable);
	}
	result = pfunc();
	if(comm!=NULL)
	{
		gdraw_act_ui_flag=0;
		pthread_join(thread_id, NULL);
		free(mcttable);
	}
	
	free(screen_info_space);
	grid_free(grid);
	icons_free(icon);
	Alert_Center(p_eventbuffer, result);
	return;
}

void Detect_Message_Center_Control(IDirectFBEventBuffer *p_eventbuffer, Messages *ptmsg, int tmsg_size)
{
	static int gDetecting_active = 0;	//used for timeout if detecting hd has no response
	show_process_control(p_eventbuffer,ptmsg,tmsg_size,&gDetecting_active,&draw_action_in_process,PTYPE_DETECTING_DEVICE);
	return;
		}
		
void Unmounting_Message_Center_Control(IDirectFBEventBuffer *p_eventbuffer, Messages *ptmsg, int tmsg_size)
		{
	static int gUnmounting_active = 0;	//used for timeout if unmounting hd has no response
	show_process_control(p_eventbuffer,ptmsg,tmsg_size,&gUnmounting_active,&draw_action_in_process,PTYPE_UNMOUNTING_DEVICE);
	return;
}

/*
*/
int RadioButton_Center(IDirectFBEventBuffer *p_eventbuffer, char *ptitle, Messages *ptmsg, int tmsg_size)
{
	DFBRectangle *screen_info_space;
	GridObj *grid;
	IconObj *icon;
	int key = 0; 						
	int grid_count=1;
	
	//start draw menu init	        
	screen_info_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	grid_init(screen_info_space, 70, 70, screen_space->w-(70*2), screen_space->h-(70*2));
	grid=create_view_tree(grid_count, screen_info_space);			
	icon=create_icon_tree(grid, main_layer, win_dsc); 
	draw_message_ui(icon, screen_info_space, ptitle, ptmsg, tmsg_size, gRadio_Selected_Index, HAVECONFIRM);

	while(1){
		key = GetInputDeviceEventByType(p_eventbuffer,PTYPE_DETECT_INFO);
		if( key == DIKI_ENTER ){
			break;
		}
		else if( key == DIKI_LEFT ){
			if(gYesOrNo==0){
				//printf("\n\n0->YesOrNo=%d\n\n", gYesOrNo);
				gYesOrNo = draw_select_item(icon->window_surface, screen_info_space->w, screen_info_space->h, 1);	
				//printf("\n\n0->YesOrNo=%d\n\n", gYesOrNo);			
			}else{
				//printf("\n\n1->YesOrNo=%d\n\n", gYesOrNo);
				gYesOrNo = draw_select_item(icon->window_surface, screen_info_space->w, screen_info_space->h, 0);
				//printf("\n\n1->YesOrNo=%d\n\n", gYesOrNo);
			}	
		}
		else if( key == DIKI_RIGHT ){
			if(gYesOrNo==0)
				gYesOrNo = draw_select_item(icon->window_surface, screen_info_space->w, screen_info_space->h, 1);
			else
				gYesOrNo = draw_select_item(icon->window_surface, screen_info_space->w, screen_info_space->h, 0);
		}
		else if( key == DIKI_UP ){
			if(gRadio_Selected_Index>1)
			{
				gRadio_Selected_Index--;
				draw_message_ui(icon, screen_info_space, ptitle, ptmsg, tmsg_size, gRadio_Selected_Index, HAVECONFIRM);
			}
		}
		else if( key == DIKI_DOWN ){
			if(gRadio_Selected_Index<tmsg_size)
			{
				gRadio_Selected_Index++;
				draw_message_ui(icon, screen_info_space, ptitle, ptmsg, tmsg_size, gRadio_Selected_Index, HAVECONFIRM);
			}
		}
		p_eventbuffer->Reset(p_eventbuffer);
	}
	
	free(screen_info_space);
	grid_free(grid);
	icons_free(icon);
	if(gYesOrNo==0){
		//printf("\ngYesOrNo=%d\n", gYesOrNo);
		return gYesOrNo;
	}else{
		//printf("\ngRadio_Selected_Index=%d\n", gRadio_Selected_Index);
		return gRadio_Selected_Index;
	}	
}
