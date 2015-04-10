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
#include "alert_center.h"
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
extern TimeTab gTimeTab;
extern int GetInputDeviceEventByType(IDirectFBEventBuffer *p_eventbuffer, int PType); 
//end extern variable or function from main.c

//extern function from show_statistic.c
extern void draw_text_onsubsurface(int x, int y,DFBRectangle *rectstring, char *text, IDirectFBFont *font, DFBSurfaceTextFlags flags, RgbaType *rgba, IDirectFBSurface *window_surface_pic);
//extern function from adjust_luminance.c
extern int saving_setting(IDirectFBEventBuffer *p_eventbuffer);
/******************************************************************************/
void Sleeptime_Saving(IDirectFBEventBuffer *p_eventbuffer, IDirectFBDisplayLayer *main_layer,char *name)
{
		//window
		IDirectFBWindow        *window_all;
		IDirectFBSurface       *window_surface_all;

		//window for picture-MOVE PIC
		IDirectFBWindow        *window_movepic;
		IDirectFBSurface       *surface_movepic;
        
		//window for picture-White Lines
		IDirectFBWindow        *window_whiteline;
		IDirectFBSurface       *surface_whiteline;        
        
        //subsurface for Blue Bar
        IDirectFBSurface       *subsurface_bluebar;	
		
		IDirectFBFont          *font=NULL;
		RgbaType				*rgba_text;
  	 	DFBRectangle 			*rect_text;
        
        char *word1,*word2,*word;
        int fontheight,key=0,dis_x=0,dis_y=40;
        char input_sleeptime[128],command[64];
        int current_set_timeout=0,ans=0;

		int i=0;   		
		int min=0;

		char *title=NULL,*title_uppage=NULL;
		int *timeout=NULL;
		int set_hdorlcd=0;

		//window for HDexist
		IDirectFBWindow        *window_HDexist;
		IDirectFBSurface       *surface_HDexist;			
		int HD_exist=1; //1:exist 0:not exist
		
		dprintf("set %s sleep timeout\n",name);

		if(strcmp(name,"HD")==0)	
		{	
			set_hdorlcd=0;	//set HD sleep timeout
			title=TITLE_HD_SLEEP;
			title_uppage=TITLE_HD_SLEEP_SET;
			timeout=&gTimeTab.HardDriveTimeout;
			word1=HD_SLEEP_MSG;
		}
		else 
		{
			set_hdorlcd=1;	//set LCD sleep timeout
			title=TITLE_LCD_SLEEP;
			title_uppage=TITLE_LCD_SLEEP_SET;				
			timeout=&gTimeTab.DisplaySaverTimeout;	
			word1=LCD_SLEEP_MSG1;									
			word2=LCD_SLEEP_MSG2;		
		}							

        draw_title_string(title, font_title, rgba,title_space, title_window_surface);		

	 	if(*timeout==NEVER_RUN_TIMEOUT)
	 	{	
	 		current_set_timeout=NEVER_RUN_TIMEOUT;
	 		min=7;
	 	}
	 	else
	 	{
	 		for(i=0;i<=7;i++)
	 		{
	 			if(sleep_time[i]== *timeout)
	 			{
	 				min=i;
	 				current_set_timeout=sleep_time[min];
	 				break;
	 			}
	 		}
	 	}

// 		dprintf("first current_set_timeout=%d sleep_time[min] %d move_dis[min] %d\n",current_set_timeout,sleep_time[min],move_dis[min]);
  		
  		/**************** Check HD exist **********************/ 
  		_u8 rgdb_devname[RGDBBUFFER_SIZE]; 
  		if(set_hdorlcd==0)
  		{	     
		    memset(rgdb_devname, 0x0, RGDBBUFFER_SIZE);  
			xmldbc_get_wb(NULL, 0, RGDB_HD_DEVNAME, rgdb_devname, RGDBBUFFER_SIZE); 	
							
			if(strcmp(rgdb_devname ,"" )==0)   
			{
				HD_exist=0;
				dprintf("\n no : HD_exist=%d \n",HD_exist); 	           
	        } 
		}	
		/************************   Set Font Description   ***********************************/ 

        DFBFontDescription Fdesc;               
        Fdesc.flags = DFDESC_HEIGHT;
        Fdesc.height = 30;
        
        DFBCHECK(gp_dfb->CreateFont( gp_dfb, FONTS_DECKER, &Fdesc, &font ));  

        font->GetHeight( font, &fontheight );
					     	
    	/*******************  set window_word description and write words ******************/ 
     
        DFBWindowDescription desc;
        
        desc.flags  = ( DWDESC_POSX | DWDESC_POSY |DWDESC_WIDTH | DWDESC_HEIGHT | DWDESC_CAPS );
        desc.caps   = DWCAPS_ALPHACHANNEL;

    	/*****************  write words *************************/          
				    
        desc.posx   = 15;
        desc.posy   = 110;
        desc.width  = 640;
        desc.height = fontheight+200;
				
        DFBCHECK(main_layer->CreateWindow( main_layer, &desc, &window_all ) );
        window_all->GetSurface( window_all, &window_surface_all );    
		window_surface_all->Clear(window_surface_all,0,0,0,0);
					
		//word
		rect_text=(DFBRectangle*)malloc(sizeof(DFBRectangle));		
		rgba_text=(RgbaType*)malloc(sizeof(RgbaType));
			
		set_rgba(rgba_text, 0, 197, 0, 255);
								
		grid_init(rect_text,2, 0 , 640, fontheight );	
		draw_text_onsubsurface(0,0,rect_text, word1, font, DSTF_TOPLEFT, rgba_text, window_surface_all);

		/*
		Because LCD cannot put "LCD sleep timeout" statement:"Set the display to hibernate when display is inactive for:" at one line
		therefore, cut this statement become two line:
		One for "Set the display to hibernate when display is "
		other for "inactive for:"
		*/
		if(set_hdorlcd==1)
		{							
			grid_init(rect_text,2, 30 , 340, fontheight );	
			draw_text_onsubsurface(0,0,rect_text, word2, font, DSTF_TOPLEFT, rgba_text, window_surface_all);
		}
		
/*		set_rgba(rgba_text, 255, 255, 255, 255);
		
		word=SLEEP_NEVER;				  
		grid_init(rect_text, (dis_x+SLEEP_W/15*14), 100+dis_y , 100, fontheight );	
		draw_text_onsubsurface(0,0,rect_text, word, font, DSTF_TOPLEFT, rgba_text, window_surface_all);

		word=SLEEP_5MIN;				  
		grid_init(rect_text, dis_x+45, 100+dis_y , 50, fontheight );	
		draw_text_onsubsurface(0,0,rect_text, word, font, DSTF_TOPLEFT, rgba_text, window_surface_all);

		word=SLEEP_10MIN;				  
		grid_init(rect_text, dis_x+110, 100+dis_y , 50, fontheight );	
		draw_text_onsubsurface(0,0,rect_text, word, font, DSTF_TOPLEFT, rgba_text, window_surface_all);

		word=SLEEP_15MIN;				  
		grid_init(rect_text, dis_x+180, 100+dis_y , 50, fontheight );	
		draw_text_onsubsurface(0,0,rect_text, word, font, DSTF_TOPLEFT, rgba_text, window_surface_all);

		word=SLEEP_30MIN;				  
		grid_init(rect_text, dis_x+255, 100+dis_y , 50, fontheight );	
		draw_text_onsubsurface(0,0,rect_text, word, font, DSTF_TOPLEFT, rgba_text, window_surface_all);

		word=SLEEP_60MIN;				  
		grid_init(rect_text, dis_x+330, 100+dis_y , 50, fontheight );	
		draw_text_onsubsurface(0,0,rect_text, word, font, DSTF_TOPLEFT, rgba_text, window_surface_all);

		word=SLEEP_90MIN;				  
		grid_init(rect_text, dis_x+400, 100+dis_y , 50, fontheight );	
		draw_text_onsubsurface(0,0,rect_text, word, font, DSTF_TOPLEFT, rgba_text, window_surface_all);

		word=SLEEP_120MIN;				  
		grid_init(rect_text, dis_x+450, 100+dis_y , 150, fontheight );	
		draw_text_onsubsurface(0,0,rect_text, word, font, DSTF_TOPLEFT, rgba_text, window_surface_all);
*/
     	/***********************   draw blue bar picture (Sub_surface)*********************************/ 

        DFBRectangle rectbluebar= { dis_x , 70+dis_y , SLEEP_BLUEBAR_W, SLEEP_BLUEBAR_H/3 };	          
		window_surface_all->GetSubSurface(window_surface_all,&rectbluebar,&subsurface_bluebar); 
		draw_image(SLEEP_BLUEBAR, NULL,subsurface_bluebar, gp_dfb);
										    	
        window_all->SetOpacity( window_all, 0xFF );  

        /**************** Set window_movepic and draw MOVE picture (window)**********************/ 

        desc.posx   = move_dis[min]+dis_x;
        desc.posy   = 157+dis_y;
        desc.width  = MOVE_W;
        desc.height = MOVE_H;

        DFBCHECK(main_layer->CreateWindow( main_layer, &desc, &window_movepic ) );
        window_movepic->GetSurface( window_movepic, &surface_movepic );    
		surface_movepic->Clear(surface_movepic,0,0,0,0);
		draw_image(MOVE_SAVING, NULL,surface_movepic, gp_dfb);
        window_movepic->SetOpacity( window_movepic, 255 ); 
     					    	
     	/***********************   draw white line picture(windows) *********************************/ 
        
        desc.posx   = dis_x;
        desc.posy   = 190+dis_y;
        desc.width  = SLEEP_WHITELINE_W;
        desc.height = SLEEP_WHITELINE_H;

        DFBCHECK(main_layer->CreateWindow( main_layer, &desc, &window_whiteline ) );
        window_whiteline->GetSurface( window_whiteline, &surface_whiteline );    
		surface_whiteline->Clear(surface_whiteline,0,0,0,0);
		draw_image(SLEEP_WHITELINE, NULL,surface_whiteline, gp_dfb);

        window_whiteline->SetOpacity( window_whiteline, 0xFF ); 

	    /***********************   draw text "HD_exist"(windows) *********************************/ 
  		
  		if(set_hdorlcd==0)
  		{
	        Fdesc.height = 36;
	        
	        DFBCHECK(gp_dfb->CreateFont( gp_dfb, FONTS_DECKER, &Fdesc, &font ));  
	
	        font->GetHeight( font, &fontheight );
	        
	        desc.posx   = 130;
	        desc.posy   = 300;
	        desc.width  = 400;
	        desc.height = 80;
	
	        DFBCHECK(main_layer->CreateWindow( main_layer, &desc, &window_HDexist ) );
	        window_HDexist->GetSurface( window_HDexist, &surface_HDexist );    
			surface_HDexist->Clear(surface_HDexist,0,0,0,0);	
			dprintf("HD_exist=%d\n",HD_exist);	
			
			if(HD_exist==1)
			{
		        window_HDexist->SetOpacity( window_HDexist, 0 ); 
			}else if(HD_exist==0)
			{
	
	        	surface_HDexist->SetColor( surface_HDexist,0,0,0,255 );
				surface_HDexist->FillRectangle(surface_HDexist,0, 0 , 380, 80);
	        	surface_HDexist->SetColor( surface_HDexist,255,255,255,255 );
				surface_HDexist->FillRectangle(surface_HDexist,5, 5 , 370, 70);
				word=NO_HD_ALERT;
				set_rgba(rgba_text, 255,0,0, 255);
				grid_init(rect_text, 20, 20 , 350, 50 );				
				draw_text(rect_text,  word,  font, DSTF_TOPLEFT, rgba_text,  surface_HDexist);
		        window_HDexist->SetOpacity( window_HDexist, 200 ); 
			}
        }	
   		/*********************** moving by keyboard*********************************/ 

		while(1){            
			key = GetInputDeviceEventByType(p_eventbuffer, PTYPE_DEFAULT_API);    	
			
				if( key == DIKI_UP ){	//go back to "Power Saving" page
  					
  					if(set_hdorlcd==0&&HD_exist==1) //set HD and HD exist
  					{							
						ans=saving_setting(p_eventbuffer);
						
						dprintf("\nans=%d (1:Save 0:Not Save)\n",ans);
	
						if(ans==1)	
						{
							if(current_set_timeout==NEVER_RUN_TIMEOUT)
		             		{
								xmldbc_set(NULL, 0, RGDB_HD_SLEEPTIME , "0");
		             		}
							else
							{
								sprintf(input_sleeptime,"%d",current_set_timeout);
								dprintf("\nSaving input_sleeptime=%s\n",input_sleeptime);
								xmldbc_set(NULL, 0, RGDB_HD_SLEEPTIME , input_sleeptime );
							}
							if(current_set_timeout==NEVER_RUN_TIMEOUT)
								sprintf(command, "smart_spindown /dev/%s 0 &", rgdb_devname);//never=0
							else
								sprintf(command, "smart_spindown /dev/%s %d &", rgdb_devname, current_set_timeout);

							system("killall smart_spindown");
							system(command);
							system("submit COMMIT &");		
							*timeout=current_set_timeout;
						}							
						//dprintf("\ntimeout=%d\n",*timeout);
					}
					else if(set_hdorlcd==1)	//set LCD
					{
						ans=saving_setting(p_eventbuffer);
	
						if(ans==1)	
						{
							if(current_set_timeout==NEVER_RUN_TIMEOUT)
								xmldbc_set(NULL, 0, RGDB_LCD_SLEEPTIME , "0" );
							else
							{
								sprintf(input_sleeptime,"%d",current_set_timeout);
								dprintf("\nSaving input_sleeptime=%s\n",input_sleeptime);
								xmldbc_set(NULL, 0, RGDB_LCD_SLEEPTIME , input_sleeptime );
							}
							system("submit COMMIT &");
							*timeout=current_set_timeout;	
						}		
					}
					
             		draw_title_string(title_uppage, font_title, rgba, title_space, title_window_surface);		

					//release 
     				font->Release( font );
					free(rect_text);
					free(rgba_text);
					
	   				if(set_hdorlcd==0) 
	   				{
	   					surface_HDexist->Release( surface_HDexist );  
     					window_HDexist->Release( window_HDexist );  						
					}
					
     				subsurface_bluebar->Release( subsurface_bluebar );     		
     				surface_movepic->Release( surface_movepic );      
     				surface_whiteline->Release( surface_whiteline );   
 
     				window_whiteline->Release( window_whiteline );     						       				    										
     				window_surface_all->Release( window_surface_all );      
		            window_movepic->Destroy( window_movepic);       						
		            window_all->Destroy( window_all);                    
        			window_movepic->Release( window_movepic);       						
		            window_all->Release( window_all);                    
        			                         
					return;	 		
             	}
             	else if( key == DIKI_RIGHT ){ // press the "->" button
             			
	           			if(set_hdorlcd==0&&HD_exist==0)
  						{
  							//do nothing	
             			}    	          		    					
    					else //Way1:set_hdorlcd==0&&HD_exist==1, Way2:set_hdorlcd==1
    					{
	    					//move the  movepic to right                                             			
	            			min++;				
							if(min>7)	min=7;
							current_set_timeout=sleep_time[min];
							window_movepic->MoveTo(window_movepic,move_dis[min],157+dis_y);
//	             			dprintf("DIKI_RIGHT current_set_timeout=%d min %d move_dis[min] %d\n",current_set_timeout,min,move_dis[min]);
    			    	}
				}
				else if( key == DIKI_LEFT ){	// press the "<-" button
												
	           			if(set_hdorlcd==0&&HD_exist==0)
  						{
  							//do nothing	
             			}    	          		    					
    					else //Way1:set_hdorlcd==0&&HD_exist==1, Way2:set_hdorlcd==1
    					{
							//move the  movepic to left                  
		  					min--;   
							if(min<0)	min=0;
	             			current_set_timeout=sleep_time[min];
	             			window_movepic->MoveTo(window_movepic,move_dis[min],157+dis_y);
//	           				dprintf("DIKI_LEFT current_set_timeout=%d min %d move_dis[min] %d\n",current_set_timeout,min,move_dis[min]);
             			}
             			        
		    	}else if( key == DIKI_A || key == DIKI_B ){				
		    						 		
					if(set_hdorlcd==0) window_HDexist->SetOpacity( window_HDexist, 0  );
     				window_whiteline->SetOpacity( window_whiteline, 0  );     						       				    										
		            window_movepic->SetOpacity( window_movepic, 0 );       						
		            window_all->SetOpacity( window_all, 0 ); 
		             
					Detect_USBMount(p_eventbuffer);					
		            
		            window_all->SetOpacity( window_all, 255 );    						
     				window_whiteline->SetOpacity( window_whiteline, 255  );     						       				    										     
		            window_movepic->SetOpacity( window_movepic, 255 );       						
  					
  					if(set_hdorlcd==0&&HD_exist==0)
						window_HDexist->SetOpacity( window_HDexist, 200  );
		            					
					draw_title_string(title, font_title, rgba, title_space, title_window_surface);										
				}
				p_eventbuffer->Reset(p_eventbuffer);		    		
   } 
}
