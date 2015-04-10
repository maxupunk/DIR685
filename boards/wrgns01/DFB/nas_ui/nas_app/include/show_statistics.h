#ifndef _SHOW_STATISTICS_H_
#define _SHOW_STATISTICS_H_

#include "alpha_dfb_define.h"
/******************************************************************************/
#define N_IMAGE (int)((sizeof (image_names) / sizeof (image_names[0])))
#define W_IMAGE 236
#define H_IMAGE 140
#define N_DIS 3   //distant for numbers
#define N_NUM (int)((sizeof (num_pic) / sizeof (num_pic[0])))
#define W_NUM 43
#define H_NUM 77
/******************************************************************************/
//static int MAX=1000;
#define DEBUG_STATISTIC 0
#define USE_TEXT 1	//draw numbers by text, not use images
#define DRAW_BG_NUM 0 //draw background numbers.
#define USE_COLOR 1 //Speed Gauge(have color->green,yellow,red)
#define DRAW_BY_LATTICES 0 //draw images' lattics one by one
/******************************************************************************/
#define RTL8366S_IOCTL_DEV  "/dev/rtl8366sr"

static int gigabit_ehternet[14]={0,256,512,1024,1,2,4,8,15,30,62,125,250,500};

#if USE_COLOR
	#define IMAGE_FORMAT ".png"
	#define DATADIR ONBOARD_PATH"images/SPEED"
#else
	#define IMAGE_FORMAT ".gif"
	#define DATADIR ONBOARD_PATH"images/000"
#endif

static char *image_names[] =
{
  DATADIR"/01"IMAGE_FORMAT,  //begin pic(when statistic num=0)
  DATADIR"/01"IMAGE_FORMAT,  //1st pic...
  DATADIR"/02"IMAGE_FORMAT,  //2nd pic...
  DATADIR"/03"IMAGE_FORMAT,  //3rd pic...
  DATADIR"/04"IMAGE_FORMAT,  
  DATADIR"/05"IMAGE_FORMAT,  
  DATADIR"/06"IMAGE_FORMAT,  
  DATADIR"/07"IMAGE_FORMAT,  
  DATADIR"/08"IMAGE_FORMAT,  
  DATADIR"/09"IMAGE_FORMAT,  
  DATADIR"/10"IMAGE_FORMAT,  
  DATADIR"/11"IMAGE_FORMAT,  
  DATADIR"/12"IMAGE_FORMAT,
  DATADIR"/13"IMAGE_FORMAT,  
  DATADIR"/14"IMAGE_FORMAT,
  DATADIR"/15"IMAGE_FORMAT,
  DATADIR"/16"IMAGE_FORMAT,
  DATADIR"/17"IMAGE_FORMAT,
  DATADIR"/18"IMAGE_FORMAT,
  DATADIR"/19"IMAGE_FORMAT,
  DATADIR"/20"IMAGE_FORMAT,
  DATADIR"/21"IMAGE_FORMAT,
  DATADIR"/22"IMAGE_FORMAT,
  DATADIR"/23"IMAGE_FORMAT,
  DATADIR"/24"IMAGE_FORMAT,
  DATADIR"/25"IMAGE_FORMAT,
  DATADIR"/26"IMAGE_FORMAT,
  DATADIR"/27"IMAGE_FORMAT,
  DATADIR"/28"IMAGE_FORMAT,
  DATADIR"/29"IMAGE_FORMAT,
  DATADIR"/30"IMAGE_FORMAT,
  DATADIR"/31"IMAGE_FORMAT,
  DATADIR"/32"IMAGE_FORMAT,  //32th pic...
};
/******************************************************************************/
//If USE_TEXT, then don't need images of numbers. 
#if !USE_TEXT	
	#define DATADIR_NUM ONBOARD_PATH"images/000"
	static char *num_pic[] =
	{
	  DATADIR_NUM"/0.gif",  
	  DATADIR_NUM"/1.gif",  
	  DATADIR_NUM"/2.gif",  
	  DATADIR_NUM"/3.gif",  
	  DATADIR_NUM"/4.gif",  
	  DATADIR_NUM"/5.gif",  
	  DATADIR_NUM"/6.gif",  
	  DATADIR_NUM"/7.gif",
	  DATADIR_NUM"/8.gif",
	  DATADIR_NUM"/9.gif",
	};
#endif
/******************************************************************************/

#endif 
