#ifndef _SETTING_H_
#define _SETTING_H_

#include "alpha_dfb_define.h"

#define BRINGHTER ONBOARD_PATH"images/screen_blue_bar.png"
#define BRI_W 588
#define BRI_H 43

#define DARKER ONBOARD_PATH"images/screen_darker.png"
#define DARK_W 595
#define DARK_H 54

#define MOVE ONBOARD_PATH"images/screen_move.png"
#define MOVE_SAVING ONBOARD_PATH"images/screen_move_saving.png"
#define MOVE_W 39
#define MOVE_H 27

#define SLEEP_BLUEBAR ONBOARD_PATH"images/screen_blue_bar.png"
#define SLEEP_BLUEBAR_W 588
#define SLEEP_BLUEBAR_H 43

//#define SLEEP_LINE2 ONBOARD_PATH"images/time_line.png"
//#define SLEEP_WHITELINE_W 640
//#define SLEEP_WHITELINE_H 11

#define SLEEP_WHITELINE ONBOARD_PATH"images/time_white_line.png"
#define SLEEP_WHITELINE_W 640
#define SLEEP_WHITELINE_H 41

				  //300  600   900  1800  3600  5400  7200		
static int sleep_time[8]={5*60,10*60,15*60,30*60,60*60,90*60,120*60,NEVER_RUN_TIMEOUT};
static int move_dis[8]={45,  120,  190,  265,  335,  410,  480,   565};

void Adjust_Luminance(IDirectFBEventBuffer *p_eventbuffer, IDirectFBDisplayLayer *main_layer);
void Sleeptime_Saving(IDirectFBEventBuffer *p_eventbuffer, IDirectFBDisplayLayer *main_layer,char *name);
void Clock_Display_Setting(IDirectFBEventBuffer *p_eventbuffer);
#endif
