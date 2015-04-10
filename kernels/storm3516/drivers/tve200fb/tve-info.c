#include "ffb.h"
#include "tve200-fb.h"

//debug_Aaron D1
#define FFB_MAX_XRES    720	
#define FFB_MAX_YRES    576	

#ifdef CONFIG_STD_TV
static ffb_hw_param_t ctrl1[] = {
	[0] = {
	       //.value = 0x53010AE0,                      /* input source D1, input data mode 4:2:2 */
	       //.value = 0x530186a1,			  /* input source VGA, RGB 888 */
	       .value = 0x53018aa1,			  /* input source D1, RGB 888 */
	       .flags =
	       FFB_MODE_NTSC | FFB_MODE_PAL | FFB_MODE_RGB |
	       FFB_MODE_YUV420 | FFB_MODE_YUV422,
	       },
};

static ffb_hw_param_t ctrl3[] = {
	[0] = {
	       .value = 0x8000,
	       .flags =
	       FFB_MODE_NTSC | FFB_MODE_PAL | FFB_MODE_RGB |
	       FFB_MODE_YUV420 | FFB_MODE_YUV422,
	       },
};

static ffb_hw_res_t res[] = {
	[0] = {
	       .xres = FFB_MAX_XRES,
	       .yres = FFB_MAX_YRES,
	       .flags = FFB_MODE_NTSC,
	       },
	[1] = {
	       .xres = FFB_MAX_XRES,
	       .yres = FFB_MAX_YRES,
	       .flags = FFB_MODE_PAL,
	       },
};

static struct tve_mach_info pannel_info = {
	.pixclock = 39722,
	.max_xres = FFB_MAX_XRES,
	.max_yres = FFB_MAX_YRES,
	.max_bpp = 24,
	.sync = FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	.num_ctrl1 = ARRAY_SIZE(ctrl1),
	.ctrl1 = ctrl1,
	.num_ctrl3 = ARRAY_SIZE(ctrl3),
	.ctrl3 = ctrl3,
	.num_res = ARRAY_SIZE(res),
	.res = res,
	.support_modes =
	    (FFB_MODE_NTSC | FFB_MODE_PAL | FFB_MODE_RGB | FFB_MODE_YUV420
	     | FFB_MODE_YUV422),
	.cmap_invert_clock = 1,
};
#endif				/* CONFIG_STD_TV  */

#ifdef CONFIG_TECHWELL
static ffb_hw_param_t ctrl1[] = {
	[0] = {
	       .value = 0x53010BE0,
	       .flags =
	       FFB_MODE_NTSC | FFB_MODE_PAL | FFB_MODE_RGB |
	       FFB_MODE_YUV420 | FFB_MODE_YUV422,
	       },
};

static ffb_hw_param_t ctrl3[] = {
	[0] = {
	       .value = 0x8000,
	       .flags =
	       FFB_MODE_NTSC | FFB_MODE_PAL | FFB_MODE_RGB |
	       FFB_MODE_YUV420 | FFB_MODE_YUV422,
	       },
};

static ffb_hw_res_t res[] = {
	[0] = {
	       .xres = 720,
	       .yres = 480,
	       .flags = FFB_MODE_NTSC,
	       },
	[1] = {
	       .xres = 720,
	       .yres = 576,
	       .flags = FFB_MODE_PAL,
	       },
};

static struct tve_mach_info pannel_info = {
	.pixclock = 39722,
	.max_xres = 720,
	.max_yres = 576,
	.max_bpp = 24,
	.sync = FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	.num_ctrl1 = ARRAY_SIZE(ctrl1),
	.ctrl1 = ctrl1,
	.num_ctrl3 = ARRAY_SIZE(ctrl3),
	.ctrl3 = ctrl3,
	.num_res = ARRAY_SIZE(res),
	.res = res,
	.support_modes =
	    (FFB_MODE_NTSC | FFB_MODE_PAL | FFB_MODE_RGB | FFB_MODE_YUV420
	     | FFB_MODE_YUV422),
	.cmap_invert_clock = 1,
};
#endif				/* CONFIG_TECHWELL */
