#ifndef _ALERT_CENTER_H_
#define _ALERT_CENTER_H_

#include "menu_tool.h"

#define D_MOVE_UP       0 
#define D_MOVE_DOWN     1
#define D_MOVE_CENTER	2		
#define D_MOVE_RIGHT	3		
#define D_MOVE_LEFT		4	
		
IconObj* channel_alert(char *alert_msg);
void alert_commit(IDirectFBSurface *surface);
void alert_ui(IconObj *icon, DFBRectangle *alert_space, char *alert_msg, int commit);
void Alert_Center(IDirectFBEventBuffer *p_eventbuffer, char *msg);
void register_alert(IDirectFBEventBuffer *p_eventbuffer, char *file_path);
void close_icon_alert();
void* icon_twinkle_r(void *arg);
void icon_alert(char *file_path, int direct);
void switch_port_icon();
#endif
