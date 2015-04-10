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
#include "alpha_dfb_define.h"
#include "nas_str_define.h"
#include "draw_tool.h"
#include "file_tool.h"
#include "menu_tool.h"
#include "fcrss_parser.h"
#include "fcrss_command.h"
#include "fcrss_serialize.h"
#include "str_tool.h"
#include "confirm_center.h"
#include "alert_center.h"
#include "fcrss_handler.h"

int Reset_Frameid_App(IDirectFBEventBuffer *p_eventbuffer)
{							    
	
	int serv_response, ret=0;	
	Messages MsgTable[1];
	
	memset(MsgTable,0,sizeof(MsgTable));	
	MsgTable[0].msg=RESET_FRAMEID_MSG;
	ret = Confirm_Center(p_eventbuffer, MsgTable, sizeof(MsgTable)/sizeof(MsgTable[0]));
	if(ret)	//yes
	{		
		icon_alert(PHOTO_LOADING_G, D_MOVE_CENTER);	
		serv_response = client_cmd_handler(p_eventbuffer, RESET_FRAMEID, NULL);				
		if(serv_response==WAN_ERROR) alert_cmd_handler(p_eventbuffer, WAN_ERROR);								
		close_icon_alert();
		return serv_response;
	}				                             	
	return 0;
}



