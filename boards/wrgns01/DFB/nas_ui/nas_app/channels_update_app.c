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
#include "draw_tool.h"
#include "file_tool.h"
#include "menu_tool.h"
#include "fcrss_parser.h"
#include "fcrss_command.h"
#include "fcrss_serialize.h"
#include "str_tool.h"
#include "alert_center.h"
#include "detect_info.h"
#include "fcrss_handler.h"

int Channels_Update_App(IDirectFBEventBuffer *p_eventbuffer)
{						
	int serv_response; 									   
    
    icon_alert(PHOTO_LOADING_G, D_MOVE_CENTER);	
	serv_response = client_cmd_handler(p_eventbuffer, CHANNEL_LIST_UPDATE, NULL);		
	if(serv_response==WAN_ERROR) alert_cmd_handler(p_eventbuffer, WAN_ERROR);	
	close_icon_alert();
	return serv_response;
}



