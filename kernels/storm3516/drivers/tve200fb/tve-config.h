#ifndef __TVE_CONFIG_H__
#define __TVE_CONFIG_H__

//#define CONFIG_PP_FRAME_NO    7	//CONFIG_PP_FRAME_NO must bigger than 5 for ffplay.
#define CONFIG_PP_FRAME_NO   1 	//CONFIG_PP_FRAME_NO must bigger than 5 for ffplay.

//#define OUTPUT_TECHWELL     1

#if defined(OUTPUT_TECHWELL)
#define CONFIG_TECHWELL     1
#define CONFIG_CT656_VBI    1
#define CONFIG_USE_FIQ 1
#else
#define CONFIG_STD_TV      1
#define CONFIG_TV_Encoder  1
//debug_Aaron
//#define CONFIG_USE_FIQ 1
#endif

#define CONFIG_MODE_NTSC    1
//#define CONFIG_COLOR_YUV420 1
#define CONFIG_COLOR_RGB   1

#endif	/* __TVE_CONFIG_H__ */
