#ifndef _CONFIRM_CENTER_H_
#define _CONFIRM_CENTER_H_

#define HAVECONFIRM 1
#define DONOTHAVECONFIRM 0
typedef struct _Messages
{
	char *msg;
}Messages;

#define SELECT_FREE 0	//for confirm select button
#define SELECT_LIMIT 1	//for confirm select button

int Confirm_Center(IDirectFBEventBuffer *p_eventbuffer, Messages *ptmsg, int tmsg_size);
int Confirm_Center_Control(IDirectFBEventBuffer *p_eventbuffer, Messages *ptmsg, int tmsg_size, int free_select);
void Message_Center(IDirectFBEventBuffer *p_eventbuffer, Messages *ptmsg, int tmsg_size, char* (*pfunc)(void));
void Message_Center_Control(IDirectFBEventBuffer *p_eventbuffer, Messages *ptmsg, int tmsg_size, char* (*pfunc)(void), char *comm, char *staymsg);
void draw_detected_ui(IconObj *icon, DFBRectangle *main_space, Messages *ptmsg, int tmsg_size, int havebtn);
int RadioButton_Center(IDirectFBEventBuffer *p_eventbuffer, char *ptitle, Messages *ptmsg, int tmsg_size);
IDirectFBFont* InitFont(int size);
void DrawBackground(IDirectFBSurface *surface, DFBRectangle *space, RgbaType *text_rga, int page_width, int page_height);
void Detect_Message_Center_Control(IDirectFBEventBuffer *p_eventbuffer, Messages *ptmsg, int tmsg_size);
void Unmounting_Message_Center_Control(IDirectFBEventBuffer *p_eventbuffer, Messages *ptmsg, int tmsg_size);
#endif /* _CONFIRM_CENTER_H_ */
