#ifndef _DETECT_INFO_H_
#define _DETECT_INFO_H_
void Detect_HW(IDirectFBEventBuffer *p_eventbuffer);
void Detect_FWUpgrade(IDirectFBEventBuffer *p_eventbuffer);
void Detect_HWMount(IDirectFBEventBuffer *p_eventbuffer);
void Detect_USBMount(IDirectFBEventBuffer *p_eventbuffer);
void Detect_AND_FORMAT_HD(IDirectFBEventBuffer *p_eventbuffer);
void Detecting_HW(IDirectFBEventBuffer *p_eventbuffer);
void Unmounting_HW(IDirectFBEventBuffer *p_eventbuffer);
#endif


