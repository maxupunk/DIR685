#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stddef.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <directfb.h>
#include <sys/stat.h>
#include "alpha_dfb_define.h"
/*#include "nas_str_define.h"
#include "draw_tool.h"
#include "file_tool.h"
#include "menu_tool.h"
#include "setting.h"
#include "detect_info.h"*/

//start extern variable or function from main.c
extern IDirectFBDisplayLayer *main_layer;
extern int GetInputDeviceEventByType(IDirectFBEventBuffer *p_eventbuffer, int PType); 
//end extern variable or function from main.c
/*
  ssignal 2 -->red
  ssignal 3 -->green
  ssignal 4 -->blue
  ssignal 5 -->black 
  ssignal 6 -->exit function
*/
void Test_Model(IDirectFBEventBuffer *p_eventbuffer)
{			
	int key;	
	printf("\nwelcome enter test model\n");         
	system("echo 1 > /proc/lcd");
	main_layer->SetBackgroundColor(main_layer, 255, 255, 255, 255);  	                           	                        
	while(1)
	{            
		key = GetInputDeviceEventByType(p_eventbuffer, PTYPE_NOSCREEN_API); 			           							
     	if( key == DIKI_UP ||key == DIKI_5){	     		     		
     		system("echo 0 > /proc/lcd");
     		printf("\nbye bye\n");
     		break;	
		}else if( key == DIKI_LEFT || key == DIKI_1){				   
			main_layer->SetBackgroundColor(main_layer, 255, 0, 0, 255);  													  	    
		}else if( key == DIKI_RIGHT || key == DIKI_2){									   		   																	
			main_layer->SetBackgroundColor(main_layer, 0, 255, 0, 255);  
		}else if( key == DIKI_DOWN || key == DIKI_3){		
			main_layer->SetBackgroundColor(main_layer, 0, 0, 255, 255);  	
		}else if( key == DIKI_ENTER || key == DIKI_4){														         																														
			main_layer->SetBackgroundColor(main_layer, 0, 0, 0, 255);  	                           	                        
		}
		
		p_eventbuffer->Reset(p_eventbuffer);					
	}	    				                        
}



