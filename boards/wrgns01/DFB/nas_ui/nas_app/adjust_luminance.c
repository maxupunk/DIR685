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
#include "setting.h"
#include "detect_info.h"
#include "rgdb_node_define.h"
#include "confirm_center.h"

//start extern variable or function from main.c
extern IconObj *itime;
extern IDirectFB *gp_dfb;
extern IDirectFBSurface *page_surface;
extern IDirectFBSurface *title_window_surface;
extern IDirectFBFont *font_title;	
extern DFBRectangle *title_space;
extern RgbaType *rgba;
extern RgbaType *rgba2;
extern SlideObj *slide_info;
extern int bright;
extern int GetInputDeviceEventByType(IDirectFBEventBuffer *p_eventbuffer, int PType); 
//end extern variable or function from main.c

//extern function from show_statistic.c
extern void draw_text_onsubsurface(int x, int y,DFBRectangle *rectstring, char *text, IDirectFBFont *font, DFBSurfaceTextFlags flags, RgbaType *rgba, IDirectFBSurface *window_surface_pic);
//extern function from display_saving.c

//#define DEBUG_ADJ 1
#ifdef DEBUG_ADJ
	#define adj_printf printf 
#else
	#define adj_printf(x,args...) 
#endif

/******************************************************************************/
int saving_setting(IDirectFBEventBuffer *p_eventbuffer)
{
	int ret=0;	
	Messages MsgTable[1];
	
	memset(MsgTable,0,sizeof(MsgTable));
	MsgTable[0].msg=SAVE_MSG;
	ret = Confirm_Center(p_eventbuffer, MsgTable, sizeof(MsgTable)/sizeof(MsgTable[0]));
	return ret;
}

int luminance_width=BRI_W;
void Adjust_Luminance(IDirectFBEventBuffer *p_eventbuffer, IDirectFBDisplayLayer *main_layer)
{
		//window for all	
		IDirectFBWindow        *window_all;
		IDirectFBSurface       *window_surface_all;
		IDirectFBSurface       *subsurface_darkpic;
		IDirectFBSurface       *subsurface_bripic;
		 
		//window for Move pic
		IDirectFBWindow			*window_movepic;
		IDirectFBSurface		*surface_movepic; 
		
		IDirectFBFont			*font=NULL;		 				
		RgbaType				*rgba_text;
		DFBRectangle			*rect_text;

		int count=0;
				 
		char *word;
		int fontheight,key=0,dis_x=0;		
   		char input_bri[128],show_bri[128];
        int pre_set_bri=0,ans=0; 
   		
   		//Write the title and draw right&left button	 	 	
		draw_title_string(TITLE_LCD_LUN, font_title, rgba, title_space, title_window_surface);							

		
		//calculate now bright's width. bright:0~64 luminance_width=0~588.
	 	if(bright>=58)
	 		luminance_width=588;
	 	else	 
			luminance_width=20*(bright/2)+8;
	 	
	 	//record begin bright
	 	pre_set_bri=bright;
	 			 
     	/************************   Set Font Description   ***********************************/ 
        DFBFontDescription Fdesc;               
        Fdesc.flags = DFDESC_HEIGHT;
        Fdesc.height = 28;          
        DFBCHECK(gp_dfb->CreateFont( gp_dfb, FONTS_DECKER, &Fdesc, &font ));  
        font->GetHeight( font, &fontheight );          
      	
      	/********************   write words and set pic*********************/        
        DFBWindowDescription desc;
                    
        desc.flags  = ( DWDESC_POSX | DWDESC_POSY |DWDESC_WIDTH | DWDESC_HEIGHT | DWDESC_CAPS );
        desc.caps   = DWCAPS_ALPHACHANNEL;
                    
        desc.posx   = 20+dis_x;
        desc.posy   = 130;
        desc.width  = DARK_W;
        desc.height = DARK_H+fontheight+MOVE_H+10+100;
					
		//Create all window & surface
      	DFBCHECK(main_layer->CreateWindow( main_layer, &desc, &window_all ) );
      	window_all->GetSurface( window_all, &window_surface_all );    
		window_surface_all->Clear(window_surface_all,0,0,0,0);

		//draw word(subsurface)
		rect_text=(DFBRectangle*)malloc(sizeof(DFBRectangle));		
		rgba_text=(RgbaType*)malloc(sizeof(RgbaType));
			
		set_rgba(rgba_text, 255, 255, 255, 255);

		word=LCD_LUM_DARK;
		grid_init(rect_text,0, DARK_H+MOVE_H+10 , DARK_W/2, fontheight+10 );	
		draw_text_onsubsurface(5,0,rect_text, word, font, DSTF_TOPLEFT, rgba_text, window_surface_all);
				  
		word=LCD_LUM_BRI;
		grid_init(rect_text, DARK_W/2 , DARK_H+MOVE_H+10 , DARK_W/2, fontheight+10 );	
		draw_text_onsubsurface(DARK_W/2-10,0,rect_text, word, font, DSTF_TOPRIGHT, rgba_text, window_surface_all);

		//Set Darker pic(subsurface)
        DFBRectangle rectdarkpic= { 0, MOVE_H , DARK_W, DARK_H };	          
		window_surface_all->GetSubSurface(window_surface_all,&rectdarkpic,&subsurface_darkpic); 
		draw_image(DARKER, NULL,subsurface_darkpic, gp_dfb);
			
		//Set Bringhter pic(window)
        DFBRectangle rectbri= { 3,MOVE_H+5,BRI_W,BRI_H };		
		window_surface_all->GetSubSurface(window_surface_all,&rectbri,&subsurface_bripic); 
		subsurface_bripic->Clear(subsurface_bripic,0,0,0,0); 													
		draw_image(DARKER, NULL,subsurface_darkpic, gp_dfb);
										
		DFBRectangle *rectbripic;
		rectbripic=(DFBRectangle*)malloc(sizeof(DFBRectangle));		
		grid_init(rectbripic, 0,0,luminance_width,BRI_H );						
		draw_image(BRINGHTER, rectbripic,subsurface_bripic, gp_dfb);
					
		//Set Move pic(window)
        desc.posx   = luminance_width+3+dis_x;
        desc.posy   = 135;
        desc.width  = MOVE_W;
        desc.height = MOVE_H;  
        DFBCHECK(main_layer->CreateWindow( main_layer, &desc, &window_movepic ) );
        window_movepic->GetSurface( window_movepic, &surface_movepic );    
		surface_movepic->Clear(surface_movepic,0,0,0,0);  
		draw_image(MOVE, NULL,surface_movepic, gp_dfb);
		subsurface_bripic->Flip(subsurface_bripic,NULL,0);
		
		adj_printf("set bright\n");						
		//set bright
		memset(show_bri, 0x0, 128);
		sprintf(show_bri,"echo %d > /proc/brightness",bright); //show bright
		system(show_bri);
		
		sprintf(input_bri,"%d",bright);
		xmldbc_set(NULL, 0, RGDB_LCD_BRIGHTNESS , input_bri );//set bright to rgdb
		system("submit COMMIT &");	

		//show windows
        window_movepic->SetOpacity( window_movepic, 0xFF ); 
        window_all->SetOpacity( window_all, 0xFF );                                             
          
             			/*********************** moving by keyboard*********************************/ 		
		while(1){            
			key = GetInputDeviceEventByType(p_eventbuffer, PTYPE_DEFAULT_API); 		

			if( key == DIKI_UP ){	//go back to "LCD Luminance Settings" page
				
				adj_printf("Press Leave=> bright %d\n",bright);
				ans=saving_setting(p_eventbuffer);
							
				if(ans==1){	
					
					sprintf(input_bri,"%d",bright);	
					dprintf("\nSaving input_bri=%s in DB\n",input_bri);					
					xmldbc_set(NULL, 0, RGDB_LCD_BRIGHTNESS , input_bri );
					adj_printf("Choose Save=> bright %d\n",bright);				
					system("submit COMMIT &");	
					pre_set_bri=bright;						
				
				}else if(ans==0){	
							
					bright=pre_set_bri;	
					memset(show_bri, 0x0, 128);
					sprintf(show_bri,"echo %d > /proc/brightness",bright);
					adj_printf("Choose NOT Save=> bright %d\n",bright);						
					system(show_bri);							
				}		             					
				  	
				draw_title_string(TITLE_LCD_LUN_SET, font_title, rgba, title_space, title_window_surface);						
				
				dprintf("\n bright=%d \n",bright);
							
				//release 
				free(rectbripic);
				free(rect_text);
				free(rgba_text);
				font->Release( font );     					
							
				subsurface_darkpic->Release(subsurface_darkpic);     						     						   						  
				subsurface_bripic->Release(subsurface_bripic);      						
				surface_movepic->Release(surface_movepic);
				window_surface_all->Release(window_surface_all); 
						    							     
				window_movepic->Destroy( window_movepic);
				window_all->Destroy( window_all);
				window_movepic->Release( window_movepic);
				window_all->Release( window_all);
						 	
				return;	 
					 	
            }else if( key == DIKI_RIGHT ){ // press the "->" button, Let LCD brighter            	             				
				
				count++;
				adj_printf("count %d\n",count);
				
				subsurface_bripic->Clear(subsurface_bripic,0,0,0,0); 
				draw_image(DARKER, NULL,subsurface_darkpic, gp_dfb);		
								     					                                             			
		    	if(luminance_width+20>=DARK_W)
				{						
					luminance_width=BRI_W;
					bright=64;

					memset(show_bri, 0x0, 128);
					sprintf(show_bri,"echo %d > /proc/brightness",bright);
					system(show_bri);		
					
					//move the  bripic to right               
					grid_init(rectbripic, 0,0,luminance_width,BRI_H );									
					draw_image(BRINGHTER, rectbripic,subsurface_bripic, gp_dfb);
					subsurface_bripic->Flip(subsurface_bripic,NULL,0);		
	
				}
				else	
				{	
					luminance_width=luminance_width+20;
					bright=bright+2;
					
					memset(show_bri, 0x0, 128);
					sprintf(show_bri,"echo %d > /proc/brightness",bright);
					system(show_bri);		
					
					//move the  bripic to right               
					grid_init(rectbripic, 0,0,luminance_width,BRI_H );									
					draw_image(BRINGHTER, rectbripic,subsurface_bripic, gp_dfb);
					subsurface_bripic->Flip(subsurface_bripic,NULL,0);							
					
					window_movepic->Move(window_movepic,20,0);	//move the  movepic to right	
				}
					
				//usleep(100000);		
											
				adj_printf("Try change more brighter=> bright %d luminance_width %d\n",bright,luminance_width);
										
			}else if( key == DIKI_LEFT ){	// press the "<-" button, Let LCD darker

				count++;
				adj_printf("count %d\n",count);
							
				subsurface_bripic->Clear(subsurface_bripic,0,0,0,0); 								
				draw_image(DARKER, NULL,subsurface_darkpic, gp_dfb);	
								
				if(luminance_width<=8)
				{
					luminance_width=8;
					bright=0;

					memset(show_bri, 0x0, 128);
					sprintf(show_bri,"echo %d > /proc/brightness",bright);
					system(show_bri);	
					
					//move the  bripic to right               
					grid_init(rectbripic, 0,0,luminance_width,BRI_H );									
					draw_image(BRINGHTER, rectbripic,subsurface_bripic, gp_dfb);
					subsurface_bripic->Flip(subsurface_bripic,NULL,0);		

				}
				else	
				{
					luminance_width=luminance_width-20;
					bright=bright-2;

					memset(show_bri, 0x0, 128);
					sprintf(show_bri,"echo %d > /proc/brightness",bright);
					system(show_bri);		
					
					//move the  bripic to right               
					grid_init(rectbripic, 0,0,luminance_width,BRI_H );									
					draw_image(BRINGHTER, rectbripic,subsurface_bripic, gp_dfb);
					subsurface_bripic->Flip(subsurface_bripic,NULL,0);		

					window_movepic->Move(window_movepic,-20,0);	//move the  movepic to right		
				}							
				
				//usleep(100000);		
						
				adj_printf("Try change more darker=> bright %d luminance_width %d\n",bright,luminance_width);
													
			}else if( key == DIKI_A || key == DIKI_B ){							 		
				window_all->SetOpacity( window_all, 0 ); 
				window_movepic->SetOpacity( window_movepic, 0 ); 				
				Detect_USBMount(p_eventbuffer);											
				window_all->SetOpacity( window_all, 255 ); 
				window_movepic->SetOpacity( window_movepic, 255 ); 
				draw_title_string(TITLE_LCD_LUN, font_title, rgba, title_space, title_window_surface);										
			
				adj_printf("Press A or B => bright %d luminance_width %d\n",bright,luminance_width);
			}
			p_eventbuffer->Reset(p_eventbuffer);						
   }
}
