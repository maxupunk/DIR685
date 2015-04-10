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
#include "str_tool.h"
#include "confirm_center.h"
#include "alert_center.h"
#include "rgdb_node_define.h"

//start extern variable or function from main.c
extern IconObj *itime;
//end extern variable or function from main.c

void Clock_Display_Setting(IDirectFBEventBuffer *p_eventbuffer)
{							    	
	int ret=0;	
	Messages MsgTable[1];
	
	memset(MsgTable,0,sizeof(MsgTable));	
	MsgTable[0].msg=CLOCK_DISPLAY_MSG;
	ret = Confirm_Center(p_eventbuffer, MsgTable, sizeof(MsgTable)/sizeof(MsgTable[0]));
	if(ret)	//yes
	{		
		xmldbc_set(NULL, 0, RGDB_PHOTO_TIME_DISPLAY, "1" );		        
		itime->window->SetStackingClass(itime->window, DWSC_UPPER);      		
	}else{
		xmldbc_set(NULL, 0, RGDB_PHOTO_TIME_DISPLAY, "0" );		
   		itime->window->SetStackingClass(itime->window, DWSC_MIDDLE);     	
	}				                             		
}



