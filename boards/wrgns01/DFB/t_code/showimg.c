#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <directfb.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/**/
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
/**/
#include "../../tve200fb/ffb-api.h"
#define DFBCHECK(x...)                                                    \
     {                                                                    \
          DFBResult err = x;                                                        \
          if (err != DFB_OK) {                                            \
               fprintf( stderr, "%s <%d>:\n\t", __FILE__, __LINE__ );     \
               DirectFBErrorFatal( #x, err );                             \
          }                                                               \
     }

#define DATADIR "images"
#define FONT "font/decker.ttf"

/* DirectFB interfaces needed by df_andi */
static IDirectFB               *dfb=NULL;
static IDirectFBSurface        *primary=NULL;
static IDirectFBSurface        *title=NULL;
static IDirectFBSurface        *background=NULL;
static int screen_width  = 0;
static int screen_height = 0;
static int section_x = 0;
static int section_y = 0;
static int choosing_icon = 1;	//bc. first start will be choose first item
static int RecordFirstIconInPage = 1;	// recorded show first icon

typedef struct IconValuesTable{
	char *name;
	char *path;
} IconValuesTable_t;

IconValuesTable_t ICONS[] = 
{
	{"Setup 1", DATADIR"/apple-red.png"},
	{"Setup 2", DATADIR"/gnome-applets.png"},
	{"Setup 3", DATADIR"/gnome-calendar.png"},
	{"Setup 4", DATADIR"/gnome-foot.png"},
	{"Setup 5", DATADIR"/gnome-gmush.png"},
	{"Setup 6", DATADIR"/gnome-gimp.png"},
	{"Setup 7", DATADIR"/gnome-gsame.png"},
	{"Setup 8", DATADIR"/gnu-keys.png"}
};

#define N_IMAGES (int)((sizeof (ICONS) / sizeof (ICONS[0])))

#define MODEL_NAME  "ALPHA"
//#define BACKGROUND_NAME  DATADIR"/background.jpg"
#define BACKGROUND_NAME  "background.png"
#define SECTION_BACKGROUND_NAME "1back.png"

#define SECTION_X_NUM 4			//record row number

#define TITLE_HEIGHT 30
#define SECTION_WIDTH 60	//record icon step width
#define SECTION_HEIGHT 80	//record icon step height
int StartX = 30;	//record start x coordinate
int StartY = 35;	//record start y coordinate
int Display_Width = SECTION_WIDTH*SECTION_X_NUM;
int Display_Height = SECTION_HEIGHT*((N_IMAGES/SECTION_X_NUM)+(N_IMAGES%SECTION_X_NUM>0?1:0));

/**********************************************************/
/* 
when DrawFlag==1, create surface and set surface include alpha color or blend,
				  and width and height of fillrectangle.
when DrawFlag==0, only create surface and return
*/ 
IDirectFBSurface* Create_IMG_Surface(char *fname, int DrawFlag, int width, int height)
{
	IDirectFBSurface *window_surface;
	DFBSurfaceDescription   dsc;
	IDirectFBImageProvider *provider;
	
	if(fname == NULL)	return NULL;
	DFBCHECK(dfb->CreateImageProvider (dfb, fname, &provider));
	DFBCHECK(provider->GetSurfaceDescription (provider, &dsc));
	
	dsc.flags = DSDESC_WIDTH|DSDESC_HEIGHT;
	dsc.width = width;
	dsc.height = height;
	DFBCHECK (dfb->CreateSurface (dfb, &dsc, &window_surface));
	provider->RenderTo (provider, window_surface, NULL);
	provider->Release (provider);
	if (DrawFlag)
	{
		//drawing control with fill rectangle
		window_surface->SetDrawingFlags( window_surface, DSDRAW_SRC_PREMULTIPLY | DSDRAW_BLEND );
		window_surface->SetPorterDuff( window_surface, DSPD_SRC_IN );
		window_surface->SetColor( window_surface, 0xFF, 0xFF, 0xFF, 0x90 );
		window_surface->FillRectangle( window_surface, 0, 0, width, height );	
	}
	
	return window_surface;
}

void DrawingSectionIcons(IconValuesTable_t *pIcon, int startx, int starty, int ShowNum, int FirstIndex)
{
	IDirectFBSurface *images;
	int i,x,y,start_icon=FirstIndex-1;
	
	fprintf(stderr,"ShowNum=%d,Display_Width=%d,Display_Height=%d\n",ShowNum,Display_Width,Display_Height);
		
    for (i = 0; i < ShowNum; i++)
	{
		images = Create_IMG_Surface( pIcon[start_icon++].path , 0/*Don't set DrawFlag*/, SECTION_WIDTH, SECTION_HEIGHT);
		x = ((i % SECTION_X_NUM) * SECTION_WIDTH) + startx;
		y = (i / SECTION_X_NUM * SECTION_HEIGHT) + starty;
		fprintf(stderr,"FirstIndex=%d,x=%d,y=%d\n",start_icon-1,x,y);
		primary->Blit( primary, images, NULL, x, y );
		images->Release (images);
	}
}

void DrawingSectionFonts(char *pName, int x, int y)
{
	primary->SetColor( primary, 0x90, 0x30, 0x90, 0xFF );
	primary->DrawString( primary, pName, -1, x, y, DSTF_CENTER );
}

/*
when first time execute this, selection-bg photo the coordinate will set (0,0) or other, so set EventInt=1.
This will create background, create selection-bg and create section icon.
Every time will do...
*/
void step_option (int EventInt)
{
	IDirectFBSurface *bgarea_surface;
	//int first_icon_index = 0;	//mean start to show ICONS[0]
	int itmp,show_num = N_IMAGES;
	
	fprintf(stderr,"\n");
	if ( Display_Height > screen_height )
	{
		//can show item
		itmp = screen_height / SECTION_HEIGHT * SECTION_X_NUM;
		//set show item num
		//fprintf(stderr,"itmp=%d,(N_IMAGES/itmp)*itmp=%d\n",itmp,(N_IMAGES/itmp)*itmp);
//		if( (N_IMAGES/itmp)*itmp < choosing_icon && choosing_icon%itmp >= 1)
//			show_num = (N_IMAGES % itmp) + SECTION_X_NUM;
//		else
			show_num = itmp;
	}
	//fprintf(stderr,"EventInt=%d\n",EventInt);
	if ( EventInt == 1 )
	{
		section_x = 0 + StartX;
		section_y = 0 + StartY;
		choosing_icon = 1;
	}
//marco	if ( EventInt == DIKI_UP )
	if ( EventInt == DIKI_1 )
	{
		fprintf(stderr,"((( DIKI_UP )))\n");
		if ( section_y - SECTION_HEIGHT >= 0 )
		{
			fprintf(stderr,"1\n");
				if ( (N_IMAGES-RecordFirstIconInPage) >= ((int)SECTION_X_NUM*2) && Display_Height > screen_height )
				{
					show_num = SECTION_X_NUM;
					fprintf(stderr,"2\n");
				}
				else
				{
					show_num = N_IMAGES-RecordFirstIconInPage+1;
					fprintf(stderr,"3\n");
				}
			section_y -= SECTION_HEIGHT;
			choosing_icon -= SECTION_X_NUM;
		}
		else
		{
			if ( RecordFirstIconInPage - SECTION_X_NUM > 0 )
			{
				RecordFirstIconInPage -= SECTION_X_NUM;
				choosing_icon -= SECTION_X_NUM;
			}	
			fprintf(stderr,"height over\n");
		}
		/*
		if ( section_y - SECTION_HEIGHT >= 0 )
		{
			fprintf(stderr,"-----one\n");
			if ( Display_Height < screen_height )
			{
				section_y -= SECTION_HEIGHT;
				choosing_icon -= SECTION_X_NUM;
			}
			else
			{
				choosing_icon -= SECTION_X_NUM;
				if ( section_y - SECTION_HEIGHT > 0 )
				{
					section_y -= SECTION_HEIGHT;
				}
				int addNum;
				if(choosing_icon%SECTION_X_NUM == 0)
					addNum=2;
				else
					addNum=1;
				first_icon_index = SECTION_X_NUM * (((choosing_icon+SECTION_X_NUM)/SECTION_X_NUM)-addNum);
					if( (N_IMAGES/itmp)*itmp < (choosing_icon+SECTION_X_NUM) && 
						(choosing_icon+SECTION_X_NUM)%itmp >= 1)
						show_num = (N_IMAGES % itmp) + SECTION_X_NUM;
				
			}
		}
		else if ( choosing_icon - SECTION_X_NUM > 0)
		{
			fprintf(stderr,"-----two\n");
			choosing_icon -= SECTION_X_NUM;
		}*/
		
	}
//marco	if ( EventInt == DIKI_DOWN )
	if ( EventInt == DIKI_2 )
	{
		fprintf(stderr,"((( DIKI_DOWN )))\n");
		show_num = N_IMAGES-RecordFirstIconInPage+1;
		if ( (section_y + (int)SECTION_HEIGHT*2) <= screen_height && choosing_icon+SECTION_X_NUM <= N_IMAGES )
		{
			section_y += SECTION_HEIGHT;
			choosing_icon += SECTION_X_NUM;
		}
		else
		{
			//when window is 300*200 will do this
			if ( RecordFirstIconInPage + (SECTION_X_NUM*2) <= N_IMAGES && Display_Height > screen_height )
			{
				if ( RecordFirstIconInPage + ((int)SECTION_X_NUM*2) <= N_IMAGES )
					RecordFirstIconInPage += SECTION_X_NUM;
				if (N_IMAGES-RecordFirstIconInPage >= SECTION_X_NUM*2)
					show_num = SECTION_X_NUM;
				if ( choosing_icon > N_IMAGES )
				{
					choosing_icon = N_IMAGES;
					section_x = (N_IMAGES % SECTION_X_NUM - 1)*SECTION_WIDTH+StartX;
				}
			}
			else
			//when window is more than items
			{
				if (N_IMAGES % SECTION_X_NUM >0)
				{
					if ( choosing_icon+SECTION_X_NUM > N_IMAGES )
						choosing_icon = N_IMAGES;
					else
						choosing_icon += SECTION_X_NUM;
					section_x = (N_IMAGES % SECTION_X_NUM - 1)*SECTION_WIDTH+StartX;
					section_y = (N_IMAGES % SECTION_X_NUM)*SECTION_HEIGHT+StartY;
				}
			}
			fprintf(stderr,"height over\n");
		}
		/*
		fprintf(stderr,"section_y=%d,section_y + (SECTION_HEIGHT*2)=%d,screen_height=%d\n",section_y,section_y + (SECTION_HEIGHT*2),screen_height);
		if ( (section_y + ((int)SECTION_HEIGHT*2)) <= screen_height )
		{
			section_y += SECTION_HEIGHT;
			choosing_icon += SECTION_X_NUM;
			if ( Display_Height > screen_height )
			{
				int addNum;
				if(choosing_icon%SECTION_X_NUM == 0)
					addNum=2;
				else
					addNum=1;
				first_icon_index = SECTION_X_NUM * ((choosing_icon/SECTION_X_NUM)-addNum);
				if( (N_IMAGES/itmp)*itmp < choosing_icon && choosing_icon%itmp >= 1)
					show_num = (N_IMAGES % itmp) + SECTION_X_NUM;
				fprintf(stderr,"--------first_icon_index=%d,show_num=%d\n",first_icon_index,show_num);
				
			}
		}
		else// if ( choosing_icon+SECTION_X_NUM <= N_IMAGES )
		{
			//select icon over height
			fprintf(stderr,"==== select icon over height ====\n");
			if( choosing_icon + SECTION_X_NUM <= N_IMAGES)
				choosing_icon += SECTION_X_NUM;
			if ( Display_Height > screen_height )
			{
				first_icon_index = SECTION_X_NUM * ((choosing_icon/SECTION_X_NUM)-1);
				//fprintf(stderr,"first_icon_index=%d\n",first_icon_index);
				if( (N_IMAGES/itmp)*itmp < choosing_icon && choosing_icon%itmp >= 1)
					show_num = (N_IMAGES % itmp) + SECTION_X_NUM;
			}
			
		}*/
	}
//marco	if ( EventInt == DIKI_LEFT )
	if ( EventInt == DIKI_3 )
	{
		if ( section_x - SECTION_WIDTH >= 0 )
		{
			section_x -= SECTION_WIDTH;
			choosing_icon -= 1;
		}
		show_num = N_IMAGES-RecordFirstIconInPage+1;
		fprintf(stderr,"((( DIKI_LEFT )))\n");
		/*if ( section_x - SECTION_WIDTH >= 0 )
		{
			section_x -= SECTION_WIDTH;
			choosing_icon -= 1;
			if ( Display_Height > screen_height )
			{
				first_icon_index = SECTION_X_NUM * ((choosing_icon/SECTION_X_NUM)-1);
				if(first_icon_index<0)	first_icon_index=0;
				//fprintf(stderr,"first_icon_index=%d\n",first_icon_index);
				if( (N_IMAGES/itmp)*itmp < choosing_icon && choosing_icon%itmp >= 1)
					show_num = (N_IMAGES % itmp) + SECTION_X_NUM;
			}
		}*/
	}
//marco	if ( EventInt == DIKI_RIGHT )
if ( EventInt == DIKI_4 )
	{
		if ( section_x + SECTION_WIDTH < Display_Width && (choosing_icon+1) <= N_IMAGES)
		{
			section_x += SECTION_WIDTH;
			choosing_icon += 1;
			
		}
		show_num = N_IMAGES-RecordFirstIconInPage+1;
		fprintf(stderr,"((( DIKI_RIGHT )))\n");
		
		/*if ( section_x + SECTION_WIDTH < Display_Width )
		{
			section_x += SECTION_WIDTH;
			choosing_icon += 1;
			if ( Display_Height > screen_height )
			{
				first_icon_index = SECTION_X_NUM * ((choosing_icon/SECTION_X_NUM)-1);
				if(first_icon_index<0)	first_icon_index=0;
				//fprintf(stderr,"first_icon_index=%d\n",first_icon_index);
				if( (N_IMAGES/itmp)*itmp < choosing_icon && choosing_icon%itmp >= 1)
					show_num = (N_IMAGES % itmp) + SECTION_X_NUM;
			}
		}*/
	}
	fprintf(stderr,"RecordFirstIconInPage=%d\n",RecordFirstIconInPage);
	fprintf(stderr,"section_x=%d,section_y=%d\n",section_x,section_y);
	fprintf(stderr,"choosing_icon=%d\n",choosing_icon);

	//clear primary surface and repaint 
	primary->SetColor( primary, 0x00, 0x00, 0x00, 0xFF );
	//primary->FillRectangle( primary, 0, 0, screen_width, screen_height );
	primary->FillRectangle( primary, 0, TITLE_HEIGHT, screen_width, screen_height );
	//primary->Clear( primary, 0, 0, 0, 0xFF );
	
	primary->Blit (primary, background, NULL, 0, TITLE_HEIGHT);
	
	//create back image of section
	bgarea_surface = Create_IMG_Surface( SECTION_BACKGROUND_NAME, 1/*Set DrawFlag*/, SECTION_WIDTH, SECTION_HEIGHT );
	primary->Blit( primary, bgarea_surface, NULL, section_x, section_y );
	
	//when screen size < displays size, to control show icons number
	
	//to create icon and string
	DrawingSectionIcons( ICONS , StartX + 5/*set center*/, StartY + 5/*set center*/, show_num, RecordFirstIconInPage );
	DrawingSectionFonts( ICONS[choosing_icon-1].name, 
						 section_x+(SECTION_WIDTH/2)/*set font name on center*/, 
						 section_y+(SECTION_HEIGHT-5)/*set font name under icon*/ );
	
	primary->Flip( primary, NULL, DSFLIP_NONE );
	//fprintf(stderr,"step_option end\n");
	bgarea_surface->Release( bgarea_surface );
}

/* set fixed title rectangle width=screen_width and height=30, background and text color */
void CreateTitle ( char *pname )
{
	DFBSurfaceDescription dsc;
	IDirectFBFont    *fontTitle;
	DFBFontDescription     fdscTitle;
	
	dsc.flags = DSDESC_WIDTH | DSDESC_HEIGHT;
	dsc.width = screen_width;
	dsc.height = TITLE_HEIGHT;
	DFBCHECK (dfb->CreateSurface( dfb, &dsc, &title ));
	title->SetColor( title, 0x1C, 0x44, 0x9A, 0xF0 );
	
	title->FillRectangle( title, 0, 0, screen_width, TITLE_HEIGHT );
	
	fdscTitle.flags = DFDESC_HEIGHT;
	fdscTitle.height = 36;
	DFBCHECK(dfb->CreateFont( dfb, FONT, &fdscTitle, &fontTitle ));
	title->SetFont( title, fontTitle );
	title->SetColor( title, 0xFF, 0xFF, 0xFF, 0xFF );
	
	title->DrawString( title, pname, -1, screen_width/2, TITLE_HEIGHT-1, DSTF_CENTER );
	primary->Blit( primary, title, NULL, 0, 0 );
	//primary->Flip( primary, NULL, DSFLIP_NONE );
	
	fontTitle->Release( fontTitle );
	title->Release( title );
}

/**********************************************************/
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
	 input_res=0;
     ioctl(fb_fd, FFB_INPUT_RES, &input_res);
     ioctl(fb_fd, FFB_SET_RGB_ORDER, &RGBorder);
     close(fb_fd);
}

int main (int argc, char **argv)
{  
	DFBSurfaceDescription dsc;
	IDirectFBInputDevice *keyboard = NULL;
	IDirectFBEventBuffer *buffer = NULL;
	IDirectFBFont    *font;
	DFBFontDescription     fdsc;
	int quit = 0;
	//joel test install pronider
	set_ioctl();
	IDirectFBImageProvider_DFIFF();
	IDirectFBImageProvider_GIF();
	IDirectFBImageProvider_PNG();
	IDirectFBFont_FT2();
	//IDirectFBImageProvider_MPEG2();
	
	
	DFBCHECK (DirectFBInit (&argc, &argv));  
	DFBCHECK (DirectFBCreate (&dfb));  
	DFBCHECK (dfb->SetCooperativeLevel (dfb, DFSCL_FULLSCREEN));  
	dsc.flags = DSDESC_CAPS;  
	dsc.caps  = DSCAPS_PRIMARY | DSCAPS_FLIPPING;  
	DFBCHECK (dfb->CreateSurface( dfb, &dsc, &primary ));  
	DFBCHECK (primary->GetSize (primary, &screen_width, &screen_height));
	fprintf(stderr,"@@marco screen_width %d, &screen_height %d \n",screen_width, screen_height);
	primary->SetBlittingFlags( primary, DSBLIT_BLEND_ALPHACHANNEL );
	
	background = Create_IMG_Surface( BACKGROUND_NAME , 0/*Don't set DrawFlag*/, screen_width, screen_height);
	CreateTitle( MODEL_NAME );
	
	//create section name
	fdsc.flags = DFDESC_HEIGHT;
	fdsc.height = 14*2;
	DFBCHECK(dfb->CreateFont( dfb, FONT, &fdsc, &font ));
	primary->SetFont( primary, font );
	//drawing on DrawingSectionFonts()
	font->Release( font );
	
//	DFBCHECK (dfb->GetInputDevice (dfb, DIDID_KEYBOARD, &keyboard));
//	DFBCHECK (keyboard->CreateEventBuffer (keyboard, &buffer));
//
	step_option(1);
//
//	while (!quit)
//	{
//		
//		DFBInputEvent event;
//		DFBCHECK (buffer->WaitForEvent (buffer));
//		printf("@marco testing@1 \n");
//		while (buffer->GetEvent (buffer, DFB_EVENT(&event)) == DFB_OK)
//		{
//			printf("@marco testing@2 \n");
//			if (event.type == DIET_KEYPRESS)
//			{
//				printf("@marco testing@event.key_id %d \n",event.key_id);
//				if ( event.key_id == DIKI_ESCAPE)
//					quit = 1;
//				else 
//				if ( event.key_id == DIKI_1 ||
//					 event.key_id == DIKI_2 ||
//					 event.key_id == DIKI_3 ||
//					 event.key_id == DIKI_4)
//					step_option(event.key_id);
//				/*if ( event.key_id == DIKI_UP ||
//					 event.key_id == DIKI_DOWN ||
//					 event.key_id == DIKI_LEFT ||
//					 event.key_id == DIKI_RIGHT)
//					step_option(event.key_id);marco*/
//			}
//		}
//	}
//	printf("@marco testing@3 \n");
//	buffer->Release (buffer);
	keyboard->Release (keyboard);
	
	background->Release( background );
	primary->Release (primary);
	dfb->Release (dfb);
	
	return 0;
}
