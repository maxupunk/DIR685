#ifndef __FFB_API_H__
#define __FFB_API_H__

#include "config.h"

//debug_Aaron
//#include "ct656.h"

#ifndef __KERNEL__
#include <stdint.h>
#endif

//IOCTL CMD
struct flcd_data {
	unsigned int buf_len;
	unsigned int uv_offset;
	unsigned int frame_no;
	unsigned int mp4_map_dma[CONFIG_MAX_FRAME_NO];
};

#define FLCD_GET_DATA_SEP   0x46db
#define FLCD_SET_FB_NUM     0x46dd
#define FLCD_SET_SPECIAL_FB 0x46df
#define FLCD_BYPASS    	    0x46e0

#define FOSD_SETPOS    		0x46e1
#define FOSD_SETDIM    		0x46e2
#define FOSD_SETSCAL    	0x46e3
#define FLCD_SET_TRANSPARENT    0x46e4
#define FLCD_SET_STRING    	0x46e5
#define FOSD_ON    		0x46e6
#define FOSD_OFF    		0x46e7
//Add By Ken.Hsieh
#define FOSD_QUERY_CHARMAP    	0x46e8
#define FOSD_RMCHAR    		0x46e9
#define FOSD_SET_CHAR    	0x46ea

struct fosd_string {
	unsigned int Str_row;	
	//Add By Ken.Hsieh on 2007.11.29 for specific column and length color
	unsigned int column;
	unsigned int len;
	unsigned int display_mode;
	unsigned int fg_color;
	unsigned int bg_color;
	unsigned char Str_OSD[31];
};
//Add By Ken.Hsieh
//#define OSD_MAX_CHAR_MAX	256

//Add BY Ken.Hsieh for OSD Font database build
/*
typedef struct fiosd_char {
	        unsigned char font_index;
		uint8_t fbitmap[32];
} fiosd_char_t;

//Add By Ken.Hsieh for recording setting font
typedef struct fiosd_charmap {
	 int map[OSD_MAX_CHAR_MAX];
} fiosd_charmap_t;
static fiosd_charmap_t charmap;
*/
struct fosd_data {
	unsigned int HPos;
	unsigned int VPos;
	unsigned int HDim;
	unsigned int VDim;
	unsigned int transparent_level;
	unsigned int HScal;
	unsigned int VScal;
	struct fosd_string Str_Data[31];
};

//debug_aaron
#if 0
struct ct656_vbi_ins_info {
	struct ct656_vbi_data field[2];
};
#endif

//FLCDS_INPUT_RES
#define TVE_INPUT_RES_CIF 0
#define TVE_INPUT_RES_VGA 1
#define TVE_INPUT_RES_D1  2

//debug_Aaron for RGB ORDER
#define TVE_RGB_ORDER_555	0
#define TVE_RGB_ORDER_565	1	
#define TVE_RGB_ORDER_888       2	

#define FFB_BUFFMT_NONINTERLACE 0
#define FFB_BUFFMT_INTERLACE    1

#define FFB_IOC_MAGIC  'c'

#define FFB_BYPASS_SRC        _IOW(FFB_IOC_MAGIC, 1, unsigned int)
#define CT656_VBI_IOCSDATA    _IOW(FFB_IOC_MAGIC, 2, struct ct656_vbi_ins_info)
#define CT656_VBI_IOCSLINE    _IOW(FFB_IOC_MAGIC, 3, unsigned int)
#define CT656_VBI_INS_ENABLE  _IOW(FFB_IOC_MAGIC, 4, unsigned int)
#define CT656_VBI_INS_DISABLE _IO(FFB_IOC_MAGIC,  5)
#define FFB_INPUT_RES         _IOW(FFB_IOC_MAGIC, 6, unsigned int)
#define CT656_CT_CTRL         _IOW(FFB_IOC_MAGIC, 7, unsigned int)
#define CT656_CT_MODE         _IOW(FFB_IOC_MAGIC, 8, struct ct656_CT_mode)
#define CT656_CT_REGION       _IOW(FFB_IOC_MAGIC, 9, struct ct656_CT_rect)
#define FFB_GET_DATA_SEP      _IOW(FFB_IOC_MAGIC, 10, struct flcd_data)
#define FFB_SET_FB_NUM        _IOW(FFB_IOC_MAGIC, 11, unsigned int)
#define FFB_SET_SPECIAL_FB    _IOW(FFB_IOC_MAGIC, 12, unsigned int)
#define FFB_BYPASS    	      _IOW(FFB_IOC_MAGIC, 13, unsigned int)
#define FFB_IOSBUFFMT         _IOW(FFB_IOC_MAGIC, 14, unsigned int)
#define FFB_IOGBUFFMT         _IOR(FFB_IOC_MAGIC, 15, unsigned int)

//debug_Aaron
#define FFB_SET_RGB_ORDER     _IOR(FFB_IOC_MAGIC, 16, unsigned int)
#define FFB_GET_CTRL1_VAL     _IOR(FFB_IOC_MAGIC, 17, unsigned int)
#endif		/* __FFB_API_H__ */
