#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <directfb.h>
#include <time.h>
#include <math.h>
#include <xmldb.h>
#include <libxmldbc.h>
#include "alpha_dfb_define.h"
#include "detect_info.h"
#include "nas_str_define.h"
#include "rgdb_node_define.h"
#include "alert_center.h"

extern IDirectFB *gp_dfb;
extern TimeTab gTimeTab;		
extern void wps_alert(IDirectFBEventBuffer *p_eventbuffer);
extern int Show_Screen_Saver(IDirectFBEventBuffer *p_eventbuffer);
extern void Get_Sys_Time(time_t *time);
extern void get_timeout_from_xml(void);

IDirectFBEventBuffer* InitInputDeviceEvent(void)
{
	IDirectFBInputDevice *p_keyboard = NULL;
	IDirectFBEventBuffer *p_eventbuffer = NULL;
	
	DFBCHECK (gp_dfb->GetInputDevice (gp_dfb, DIDID_KEYBOARD, &p_keyboard));
	DFBCHECK (p_keyboard->CreateEventBuffer (p_keyboard, &p_eventbuffer));	
	return p_eventbuffer;
}

/****************************************************************************************************************************** 
InternalKey isn't touch pad key().
if have special key will return key_id, if detect device(somthing) will return 0.
when screen saver(display, hd timeout) act and detect special key, it will re-show interface and execute special key function.
*******************************************************************************************************************************/
int HaveNeedInternalKey(IDirectFBEventBuffer *p_eventbuffer, int PType)
{
	DFBInputEvent event;
	int key=0;
	char wps_enable[2];
			
	if(p_eventbuffer->GetEvent (p_eventbuffer, DFB_EVENT(&event)) == DFB_OK){	
		if (event.type == DIET_KEYPRESS) key=event.key_id;		
	}		
	
	switch(key)
	{
		case DIKI_J:
			dprintf("user key press DIKI_J, and is detecting device\n");
			Detecting_HW(p_eventbuffer);
			break;
		case DIKI_K:
			dprintf("user key press DIKI_K, and is umounting device\n");
			Unmounting_HW(p_eventbuffer);
			break;
		/* moved into Detecting_HW
		case DIKI_F:
			dprintf("user key press DIKI_F, and detect Hard Drive format \n");
			Detect_HW(p_eventbuffer);
			break;
		*/
		case DIKI_G:
			dprintf("user key press DIKI_G, and want to format Hard Drive\n");
			Detect_AND_FORMAT_HD(p_eventbuffer);
			break;
		
		case DIKI_U:
			dprintf("user key press DIKI_U, and detect Firmware Upgrade\n");
			Detect_FWUpgrade(p_eventbuffer);
			break;
		/* moved into Detecting_HW
		case DIKI_I:
			dprintf("user key press DIKI_I, and detect Hard Drive mount success\n");
			Detect_HWMount(p_eventbuffer);
			break;					
		*/
		case DIKI_A:
			dprintf("user key press DIKI_A, and detect USB mount success\n");
			//Detect_USBMount(p_eventbuffer,"usbA");
			break;
		case DIKI_B:
			dprintf("user key press DIKI_B, and detect USB mount success\n");
			//Detect_USBMount(p_eventbuffer,"usbB");
			break;				
		case DIKI_N:
			dprintf("user key press DIKI_N, and NTP server update systime\n");
			Get_Sys_Time(&gTimeTab.timep);
			break;				
		case DIKI_W:									
			xmldbc_get_wb(NULL, 0, RGDB_WPS_ENABLE, wps_enable, 1);								 														         																															
			if(wps_enable[0]=='1')
			{			
				system("usockc /var/run/fresetd_unixsock WPS_START");
				wps_alert(p_eventbuffer); 
			}else{								
				Alert_Center(p_eventbuffer, WPS_DISABLE);									
			}					
			break;
		case DIKI_P:									
			dprintf("user key press DIKI_P, and show pin code from client.\n");
			wps_pin_alert(p_eventbuffer);		
			break;
		case DIKI_H:
			dprintf("user key press DIKI_H, and update lcd timeout\n");
			get_timeout_from_xml();
			break;
		case DIKI_O:
			switch_port_icon();
			break;	
		default:
			return key;
	}
		
	return key;	
}

int GetInputDeviceEventByType(IDirectFBEventBuffer *p_eventbuffer, int PType)
{
	DFBResult dfbresult=DFB_OK;
	int timeout, retkeyid=0;
	
	switch(PType){					
		case PTYPE_DEFAULT_API:			
			if( gTimeTab.ScreenSaverTimeout >= gTimeTab.DisplaySaverTimeout ) 
				timeout = gTimeTab.DisplaySaverTimeout; 
			else
				timeout = gTimeTab.ScreenSaverTimeout;
			if(timeout==NEVER_RUN_TIMEOUT)
				dfbresult = p_eventbuffer->WaitForEvent (p_eventbuffer);	//always return DFB_OK
			else
				dfbresult = p_eventbuffer->WaitForEventWithTimeout(p_eventbuffer, timeout, 0);		
			if(dfbresult==DFB_TIMEOUT){
				if( gTimeTab.ScreenSaverTimeout < gTimeTab.DisplaySaverTimeout ){					
						Show_Screen_Saver(p_eventbuffer);
						HaveNeedInternalKey(p_eventbuffer,PTYPE_DEFAULT_API);
				}else if( gTimeTab.ScreenSaverTimeout >= gTimeTab.DisplaySaverTimeout ){
						printf("back light disable\n");
						system("echo 0 > /proc/lcd");
						DFBCHECK (p_eventbuffer->WaitForEvent (p_eventbuffer));
						printf("back light enable\n");
						system("echo 1 > /proc/lcd");											
						HaveNeedInternalKey(p_eventbuffer, PType);									
				}
			}else if(dfbresult==DFB_OK){
				retkeyid=HaveNeedInternalKey(p_eventbuffer,PTYPE_DEFAULT_API);				
			}	
			break;
		case PTYPE_SCREEN_SAVER:			
			if(gTimeTab.DisplaySaverTimeout==NEVER_RUN_TIMEOUT)
			{
				p_eventbuffer->WaitForEvent (p_eventbuffer);	//always return DFB_OK
				break;
			}
			else
			{
				timeout = gTimeTab.DisplaySaverTimeout - gTimeTab.ScreenSaverTimeout;
				dfbresult = p_eventbuffer->WaitForEventWithTimeout(p_eventbuffer, timeout, 0);
			}
			if(dfbresult==DFB_TIMEOUT){
				printf("back light disable\n");
				system("echo 0 > /proc/lcd");
				DFBCHECK (p_eventbuffer->WaitForEvent (p_eventbuffer));
				printf("back light enable\n");
				system("echo 1 > /proc/lcd");
			}
			break;
		case PTYPE_DETECTING_DEVICE:
			timeout = DETECTING_TIMEOUT;
			dfbresult = p_eventbuffer->WaitForEventWithTimeout(p_eventbuffer, timeout, 0);		
			
			if(dfbresult==DFB_TIMEOUT)
			{	/* mount failed */
				dprintf("Detect device failed\n" );
				retkeyid = DIKI_E;	//error key, should show error message.
				break;	
			}
			retkeyid=HaveNeedInternalKey(p_eventbuffer, PType);					
			break;
		
		case PTYPE_UNMOUNTING_DEVICE:
			timeout = UNMOUNTING_TIMEOUT;
			dfbresult = p_eventbuffer->WaitForEventWithTimeout(p_eventbuffer, timeout, 0);		
			
			if(dfbresult==DFB_TIMEOUT)
			{	/* mount failed */
				dprintf("Unmounting device failed\n" );
				retkeyid = DIKI_M;	//error key, should show error message.
				break;	
			}
			retkeyid=HaveNeedInternalKey(p_eventbuffer, PType);					
			break;

		default:				
			p_eventbuffer->WaitForEvent(p_eventbuffer);
			retkeyid=HaveNeedInternalKey(p_eventbuffer, PType);					
	}	
	return retkeyid;
}


int special_key_table(int key)
{		
	switch(key)
	{
		case DIKI_F: break;
		case DIKI_G: break;
		case DIKI_U: break;
		case DIKI_I: break;					
		case DIKI_A: break;
		case DIKI_B: break;				
		case DIKI_N: break;				
		case DIKI_W: break;
		case DIKI_H: break;
		default: return 0;
	}		
	return 1;	
}

/*
void filter_special_key(IDirectFBEventBuffer *p_eventbuffer) 
{
	DFBInputEvent event;
	int is_spec_key=0, i=0;
		
	{			
		printf("\ni %d\n", i);
		i++;		
		p_eventbuffer->PeekEvent(p_eventbuffer, &event); 			
		is_spec_key=special_key_table(event.key_id);				
		if(!is_spec_key) p_eventbuffer->GetEvent(p_eventbuffer, &event);
	}while(is_spec_key==0&&p_eventbuffer->HasEvent(p_eventbuffer)==DFB_OK)			
	if(!is_spec_key) p_eventbuffer->Reset(p_eventbuffer);	 
}*/
	