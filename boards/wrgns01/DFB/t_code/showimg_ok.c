#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <directfb.h>

#define DEBUG y
#ifndef DEBUG
	#define dprintf(format, args...)
#else
	#define dprintf(format, args...)	fprintf( stderr, format, ##args)
#endif

#define DFBCHECK(x...)                                                    \
     {                                                                    \
          DFBResult err = x;                                                        \
          if (err != DFB_OK) {                                            \
               dprintf( "%s <%d>:\n\t", __FILE__, __LINE__ );     \
               DirectFBErrorFatal( #x, err );                             \
          }                                                               \
     }

IDirectFB               *gp_dfb=NULL;
IDirectFBSurface        *gp_primary=NULL;

int g_screen_width  = 0;
int g_screen_height = 0;


typedef struct IconValuesTable{
	char *name;
	char *path;
} IconValuesTable_t;

IconValuesTable_t ICONS[] = 
{
	{"Clock", "flickr_photo/1.jpg"},
	{"Flickr", "flickr_photo/2.jpg"},
	{"Weather", "flickr_photo/3.jpg"},
	{"Stock", "flickr_photo/4.jpg"},
	{"News", "flickr_photo/5.jpg"},
};

#define N_IMAGES (int)((sizeof (ICONS) / sizeof (ICONS[0])))	//images number

#define MODEL_NAME  "ALPHA"
//#define BACKGROUND_NAME  DATADIR"/background.jpg"
#define BACKGROUND_NAME  "images/background.png"
#define SECTION_BACKGROUND_NAME "images/iconback.png"
#define FONT_NAME "font/decker.ttf"

#define SECTION_X_NUM 4			//record row number
#define TITLE_HEIGHT 30
#define SECTION_WIDTH 60	//record icon step width
#define SECTION_HEIGHT 80	//record icon step height
#define StartX 30	// start x coordinate
#define StartY 35	// start y coordinate

typedef struct SelectBGPosTable{
	int x;	// for draw item icon
	int y;	// for draw item icon
} SelectBGPosTable_t;

int g_choosing_icon = 1;	//bc. first start will be choose first item
int RecordFirstIconInPage = 1;	// recorded show first icon
int Display_Width = SECTION_WIDTH*SECTION_X_NUM;
int Display_Height = SECTION_HEIGHT*((N_IMAGES/SECTION_X_NUM)+(N_IMAGES%SECTION_X_NUM>0?1:0));

IDirectFBSurface *gp_main_menu_images[N_IMAGES];

/**********************************************************/
/* 
when DrawFlag==1, create surface and set surface include alpha color or blend,
				  and width and height of fillrectangle.
when DrawFlag==0, only create surface and return
*/ 
IDirectFBSurface* Create_IMG_Surface(char *fname, int DrawFlag, int width, int height)
{
	IDirectFBSurface *p_window_surface;
	DFBSurfaceDescription   dsc;
	IDirectFBImageProvider *p_provider;
	
	if(fname == NULL)	return NULL;
	dprintf("fname=%s\n",fname);
	DFBCHECK(gp_dfb->CreateImageProvider (gp_dfb, fname, &p_provider));
	
	DFBCHECK(p_provider->GetSurfaceDescription (p_provider, &dsc));
	dsc.width = 720;
	dsc.height = 576;
	DFBCHECK (gp_dfb->CreateSurface (gp_dfb, &dsc, &p_window_surface));
	p_provider->RenderTo (p_provider, p_window_surface, NULL);
	p_provider->Release (p_provider);
	if (DrawFlag)
	{
		//drawing control with fill rectangle
		p_window_surface->SetDrawingFlags( p_window_surface, DSDRAW_SRC_PREMULTIPLY | DSDRAW_BLEND );
		p_window_surface->SetPorterDuff( p_window_surface, DSPD_SRC_IN );
		p_window_surface->SetColor( p_window_surface, 0x0, 0xFF, 0xFF, 0x90 );
		p_window_surface->FillRectangle( p_window_surface, 0, 0, width, height );	
	}
	
	return p_window_surface;
}

void LoadIconImages(IconValuesTable_t *pIcon, int ShowNum)
{
	int i;
	
    for (i = 0; i < sizeof(ICONS)/sizeof(IconValuesTable_t); i++)
		gp_main_menu_images[i] = Create_IMG_Surface( pIcon[i].path , 0/*Don't set blend*/, 0, 0);
}

void ReleaseImages(int ShowNum)
{
	int i;
	
	for (i = 0; i < ShowNum; i++)
		gp_main_menu_images[i]->Release (gp_main_menu_images[i]);
}

/*
when user change selected item, drawing background with select item.
*/
void DrawingSectionIcons(IconValuesTable_t *pIcon, int startx, int starty, int ShowNum, int FirstIndex)
{
	int i,x,y,start_icon=FirstIndex-1;
	
	dprintf("ShowNum=%d,Display_Width=%d,Display_Height=%d\n",ShowNum,Display_Width,Display_Height);
		
    for (i = 0; i < ShowNum; i++)
	{
		x = ((i % SECTION_X_NUM) * SECTION_WIDTH) + startx;
		y = (i / SECTION_X_NUM * SECTION_HEIGHT) + starty;
		dprintf("FirstIndex=%d,x=%d,y=%d\n",start_icon,x,y);
		gp_primary->Blit( gp_primary, gp_main_menu_images[start_icon++], NULL, x, y );
	}
}

void DrawingSectionFonts(IDirectFBSurface *pSurface, char *pName, int align, int x, int y, int r, int g, int b, int alpha)
{
	//gp_primary->SetColor( gp_primary, 0x90, 0x30, 0x90, 0xFF );
	pSurface->SetColor( pSurface, r, g, b, alpha );
	pSurface->DrawString( pSurface, pName, -1, x, y, align );
}

/* Compute selected icon background pos and show number on main menu */
void ComputeBGPos( int EventInt, SelectBGPosTable_t *sgbpos, int *show_num)
{
	int line_num = (g_screen_height-StartY)/SECTION_HEIGHT;	//compute line num on main surface
	
	if ( EventInt == 1 )
	{
		g_choosing_icon = 1;
	}
	else if ( EventInt == DIKI_UP )
	{
		if(g_choosing_icon-SECTION_X_NUM > 0)
			g_choosing_icon -= SECTION_X_NUM;
	}
	else if ( EventInt == DIKI_DOWN )
	{
		if(g_choosing_icon+SECTION_X_NUM <= N_IMAGES)
			g_choosing_icon += SECTION_X_NUM;
	}
	else if ( EventInt == DIKI_LEFT )
	{
		if(g_choosing_icon-1 > 0)
			g_choosing_icon -= 1;
		else
			g_choosing_icon = N_IMAGES;
	}
	else if ( EventInt == DIKI_RIGHT )
	{
		if(g_choosing_icon+1 <= N_IMAGES)
			g_choosing_icon += 1;
		else
			g_choosing_icon = 1;
	}
	//compute RecordFirstIconInPage
	if(g_choosing_icon > RecordFirstIconInPage+(SECTION_X_NUM*line_num-1 ))
		RecordFirstIconInPage += SECTION_X_NUM;
	else if(g_choosing_icon < RecordFirstIconInPage)
		RecordFirstIconInPage -= SECTION_X_NUM;
	//compute x,y
	sgbpos->x = (g_choosing_icon-(SECTION_X_NUM*((int)(g_choosing_icon-1)/SECTION_X_NUM))-1)*SECTION_WIDTH+StartX;
	sgbpos->y = (SECTION_HEIGHT*((g_choosing_icon-RecordFirstIconInPage)/SECTION_X_NUM))+StartY;	
	//compute show_num
	*show_num = N_IMAGES - RecordFirstIconInPage + 1;
	if(*show_num > (SECTION_X_NUM*line_num))
		*show_num = SECTION_X_NUM*line_num;
	
}

/*
when first time execute this, selection-bg photo the coordinate will set (0,0) or other, so set EventInt=1.
This will create background, create selection-bg and create section icon.
Every time will do...
*/
void step_option (IDirectFBSurface *p_bg, IDirectFBSurface *p_icon_bg, int EventInt)
{
	int show_num = N_IMAGES;
	SelectBGPosTable_t BGPos = {0,0};
	
	dprintf("\n");
	ComputeBGPos(EventInt, &BGPos, &show_num);
	
	dprintf("RecordFirstIconInPage=%d\n",RecordFirstIconInPage);
	dprintf("section_x=%d,section_y=%d\n",BGPos.x,BGPos.y);
	dprintf("g_choosing_icon=%d\n",g_choosing_icon);

	//clear gp_primary surface and repaint ,when g_screen_width&g_screen_height > p_bg.size
	gp_primary->SetColor( gp_primary, 0x00, 0x00, 0x00, 0xFF );
	gp_primary->FillRectangle( gp_primary, 0, TITLE_HEIGHT, g_screen_width, g_screen_height );
	
	gp_primary->Blit (gp_primary, p_bg, NULL, 0, TITLE_HEIGHT);
	
	//gp_primary->Blit( gp_primary, p_icon_bg, NULL, BGPos.x, BGPos.y );
	
	//when screen size < displays size, control to show icons number
	
	//to create icon and string
	gp_primary->Blit( gp_primary, gp_main_menu_images[EventInt], NULL, 0, 0 );
	//DrawingSectionIcons( ICONS , StartX + 5/*set center*/, StartY + 5/*set center*/, show_num, RecordFirstIconInPage );
	DrawingSectionFonts( gp_primary, ICONS[g_choosing_icon-1].name, DSTF_CENTER, 
						 0, 
						 0,
						 0x90, 0x30, 0x90, 0xFF );
	
	gp_primary->Flip( gp_primary, NULL, DSFLIP_NONE );
	
}

/* set fixed title rectangle width=g_screen_width and height=30, background and text color */
void CreateTitle ( char *pname, char *pfontname )
{
	IDirectFBSurface        *p_title=NULL;
	
	DFBSurfaceDescription dsc;
	IDirectFBFont    *p_fontTitle;
	DFBFontDescription     fdscTitle;
	
	dsc.flags = DSDESC_WIDTH | DSDESC_HEIGHT;
	dsc.width = g_screen_width;
	dsc.height = TITLE_HEIGHT;
	DFBCHECK (gp_dfb->CreateSurface( gp_dfb, &dsc, &p_title ));
	p_title->SetColor( p_title, 0x1C, 0x44, 0x9A, 0xF0 );
	p_title->FillRectangle( p_title, 0, 0, g_screen_width, TITLE_HEIGHT );
	
	fdscTitle.flags = DFDESC_HEIGHT;
	fdscTitle.height = 36;
	DFBCHECK(gp_dfb->CreateFont( gp_dfb, pfontname, &fdscTitle, &p_fontTitle ));
	p_title->SetFont( p_title, p_fontTitle );
	p_title->SetColor( p_title, 0xFF, 0xFF, 0xFF, 0xFF );
	p_title->DrawString( p_title, pname, -1, g_screen_width/2, TITLE_HEIGHT-1, DSTF_CENTER );
	gp_primary->Blit( gp_primary, p_title, NULL, 0, 0 );
	//gp_primary->Flip( gp_primary, NULL, DSFLIP_NONE );
	
	p_fontTitle->Release( p_fontTitle );
	p_title->Release( p_title );
}

void CreateFontAndSetStyle (IDirectFBSurface *pSurface, char *pFontName, int font_size)
{
	IDirectFBFont    *p_font;
	DFBFontDescription     fdsc;
	
	fdsc.flags = DFDESC_HEIGHT;
	fdsc.height = font_size;
	DFBCHECK(gp_dfb->CreateFont( gp_dfb, pFontName, &fdsc, &p_font ));
	pSurface->SetFont( pSurface, p_font );
	p_font->Release( p_font );
	
	return;
}

/**********************************************************/
void init_api(int argc, char **argv)
{
	DFBSurfaceDescription dsc;
	
	DFBCHECK (DirectFBInit (&argc, &argv));  
	DFBCHECK (DirectFBCreate (&gp_dfb));  

	DFBCHECK (gp_dfb->SetCooperativeLevel (gp_dfb, DFSCL_FULLSCREEN));  
	dsc.flags = DSDESC_CAPS;  
	dsc.caps  = DSCAPS_PRIMARY | DSCAPS_FLIPPING;  
	DFBCHECK (gp_dfb->CreateSurface( gp_dfb, &dsc, &gp_primary ));  
	DFBCHECK (gp_primary->GetSize (gp_primary, &g_screen_width, &g_screen_height));
	//g_screen_width = 320;
	//g_screen_height = 200;
	dprintf("g_screen_width=%d,g_screen_height=%d\n",g_screen_width,g_screen_height);
	gp_primary->SetBlittingFlags( gp_primary, DSBLIT_BLEND_ALPHACHANNEL );
	
	return;
}

IDirectFBEventBuffer* InitInputDeviceEvent(void)
{
	IDirectFBInputDevice *p_keyboard = NULL;
	IDirectFBEventBuffer *p_eventbuffer = NULL;
	
	DFBCHECK (gp_dfb->GetInputDevice (gp_dfb, DIDID_KEYBOARD, &p_keyboard));
	DFBCHECK (p_keyboard->CreateEventBuffer (p_keyboard, &p_eventbuffer));
	
	return p_eventbuffer;
}

int GetInputDeviceEvent(IDirectFBEventBuffer *p_eventbuffer)
{
	DFBInputEvent event;
	
	while(1)
	{
		DFBCHECK (p_eventbuffer->WaitForEvent (p_eventbuffer));
		while (p_eventbuffer->GetEvent (p_eventbuffer, DFB_EVENT(&event)) == DFB_OK)
		{
			if (event.type == DIET_KEYPRESS)
			{
				return event.key_id;
			}
		}
	}
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <syslog.h>
#include <errno.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <errno.h>
#include "../../tve200fb/ffb-api.h"
void set_ioctl()
{
	int fb_fd=0;
	unsigned int input_res,RGBorder=2;
	if( (fb_fd = open("/dev/fb1", O_RDWR)) < 0)
    {
        printf("open %s fail !\n", "/dev/tve");
        return ;
     }
	 //debug_Aaron, fix the input resolution to D1
	 input_res=2;
     ioctl(fb_fd, FFB_INPUT_RES, &input_res);
     ioctl(fb_fd, FFB_SET_RGB_ORDER, &RGBorder);
     close(fb_fd);
}				
int main (int argc, char **argv)
{  
	set_ioctl();
	IDirectFBSurface *p_background=NULL;
	IDirectFBSurface *p_icon_background=NULL;
	IDirectFBEventBuffer *p_eventbuffer = NULL;
	int quit = 0, key = 0;
	//marco
		IDirectFBImageProvider_DFIFF();
	IDirectFBImageProvider_GIF();
	IDirectFBImageProvider_PNG();
	IDirectFBImageProvider_JPEG();
	IDirectFBFont_FT2();
	init_api (argc, argv);
	
	p_background = Create_IMG_Surface( BACKGROUND_NAME , 0/*Don't set blend*/, 0, 0);
	dprintf("p_background\n");
	//create back image of section
	p_icon_background = Create_IMG_Surface( SECTION_BACKGROUND_NAME, 1/*Set blend*/, SECTION_WIDTH, SECTION_HEIGHT );
	dprintf("p_icon_background\n");
	
	//CreateTitle( MODEL_NAME, FONT_NAME );
	
	//CreateFontAndSetStyle(gp_primary, FONT_NAME, 36);
	
	LoadIconImages(ICONS, N_IMAGES);
	
//	p_eventbuffer = InitInputDeviceEvent();
	
	for(key=0;key<sizeof(ICONS)/sizeof(IconValuesTable_t);key++)
	{
		step_option(p_background,p_icon_background,key);
		sleep(3);
	}
//	gp_primary->SetColor( gp_primary, 0x0, 0xFF, 0, 0x0 );//g b a r
//	gp_primary->FillRectangle( gp_primary, 0, 0, g_screen_width, g_screen_height );
//	gp_primary->SetColor( gp_primary, 0xFF, 0x0, 0x00, 0xFF );
//	gp_primary->FillRectangle( gp_primary, 100, 0, g_screen_width, g_screen_height );
//	gp_primary->SetColor( gp_primary, 0x00, 0xFF, 0x00, 0xFF );
//	gp_primary->FillRectangle( gp_primary, 200, g_screen_height/3, g_screen_width, g_screen_height/3 );
//	gp_primary->SetColor( gp_primary, 0x00, 0x00, 0xFF, 0xFF );
//	gp_primary->FillRectangle( gp_primary, 300, g_screen_height/3*2, g_screen_width, g_screen_height/3 );
	fprintf(stderr,"screen_width=%d,screen_height=%d\n",g_screen_width,g_screen_height);
//	gp_primary->Flip( gp_primary, NULL, DSFLIP_NONE );
//	sleep(30);
	
	ReleaseImages(N_IMAGES);
//	p_eventbuffer->Release (p_eventbuffer);
	p_icon_background->Release( p_icon_background );
	p_background->Release( p_background );
	gp_primary->Release (gp_primary);
	gp_dfb->Release (gp_dfb);
	
	return 0;
}
