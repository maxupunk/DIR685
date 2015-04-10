#ifndef _APPLICATION_H_
#define _APPLICATION_H_
void Album_Local_App(IDirectFBEventBuffer *p_eventbuffer, char *root_dev_path, int is_top_layer, IconObj *folder);		
void Channels_Display_App(IDirectFBEventBuffer *p_eventbuffer);
void Channel_App(IDirectFBEventBuffer *p_eventbuffer, FcNode *target_node);			
void FrameChannel_Menu(IDirectFBEventBuffer *p_eventbuffer, int first_app_exe);			
void FrameIt_Display_App(IDirectFBEventBuffer *p_eventbuffer);							
void Status_Menu(IDirectFBEventBuffer *p_eventbuffer);											
void Setting_Menu(IDirectFBEventBuffer *p_eventbuffer);	
void Show_Router_Info(IDirectFBEventBuffer *p_eventbuffer, int segment);
void Show_Statistics(IDirectFBEventBuffer *p_eventbuffer, IDirectFBDisplayLayer *main_layer);
void Wps_Menu(IDirectFBEventBuffer *p_eventbuffer);			
void UPnP_Menu(IDirectFBEventBuffer *p_eventbuffer);			
int Channels_Update_App(IDirectFBEventBuffer *p_eventbuffer);
int Reset_Frameid_App(IDirectFBEventBuffer *p_eventbuffer);
#endif
