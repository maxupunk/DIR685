#include <linux/init.h>
#include <linux/delay.h>
#include <linux/dma-mapping.h>
#include <linux/interrupt.h>
#include <linux/device.h>
#include <linux/proc_fs.h>

#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>
#include <asm/mach-types.h>

//debug_Aaron
//#include <asm/arch/spec.h>
//#include <asm/arch/fmem.h>
#include <asm/arch/sl2312.h>

#include "ffb.h"
//#define FFBDBG_LV   100 
#include "debug.h"

extern const unsigned int config_fb_number;
int g_fb_open=0;//marco
static struct flcd_data f_data;

static struct ffb_mach_ops *ffb_mach_ctl;

//debug_Aaron
extern char *FB_MODE;
/*
 * IMHO this looks wrong.  In 8BPP, length should be 8.
 */
static struct ffb_rgb rgb_8 = {
	.red = {.offset = 0,.length = 4,},
	.green = {.offset = 0,.length = 4,},
	.blue = {.offset = 0,.length = 4,},
	.transp = {.offset = 0,.length = 0,},
};

static struct ffb_rgb def_rgb_16 = {
	.red = {.offset = 0,.length = 5,.msb_right = 0},
	.green = {.offset = 5,.length = 6,.msb_right = 0},
	.blue = {.offset = 11,.length = 5,.msb_right = 0},
	.transp = {.offset = 15,.length = 1,.msb_right = 0},
};

static struct ffb_rgb def_rgb_24 = {
	.red = {.offset = 0,.length = 8,.msb_right = 0},
	.green = {.offset = 0,.length = 8,.msb_right = 0},
	.blue = {.offset = 0,.length = 8,.msb_right = 0},
	.transp = {.offset = 0,.length = 0,.msb_right = 0},
};

static inline void ffb_schedule_work(struct ffb_info *fbi, u_int state)
{
	unsigned long flags;

	local_irq_save(flags);
	/*
	 * We need to handle two requests being made at the same time.
	 * There are two important cases:
	 *  1. When we are changing VT (C_REENABLE) while unblanking (C_ENABLE)
	 *     We must perform the unblanking, which will do our REENABLE for us.
	 *  2. When we are blanking, but immediately unblank before we have
	 *     blanked.  We do the "REENABLE" thing here as well, just to be sure.
	 */
	if (fbi->task_state == C_ENABLE && state == C_REENABLE)
		state = (u_int) - 1;
	if (fbi->task_state == C_DISABLE && state == C_ENABLE)
		state = C_REENABLE;

	if (state != (u_int) - 1) {
		fbi->task_state = state;
		schedule_work(&fbi->task);
	}
	local_irq_restore(flags);
}

static inline u_int chan_to_field(u_int chan, struct fb_bitfield *bf)
{
	chan &= 0xffff;
	chan >>= 16 - bf->length;
	return chan << bf->offset;
}

static int ffb_setpalettereg(u_int regno, u_int red, u_int green,
			     u_int blue, u_int trans, struct fb_info *info)
{
	struct ffb_info *fbi = (struct ffb_info *) info;
	u_int val, ret = 1;

	DBGENTER(1);
	
	if (regno < fbi->palette_size) {
		val = ((red >> 0) & 0xf800);
		val |= ((green >> 5) & 0x07e0);
		val |= ((blue >> 11) & 0x001f);

		fbi->palette_cpu[regno] = val;
		ret = 0;
	}

	DBGLEAVE(1);
	return ret;
}

int ffb_setcolreg(u_int regno, u_int red, u_int green, u_int blue,
		  u_int trans, struct fb_info *info)
{
	
	struct ffb_info *fbi = (struct ffb_info *) info;
	unsigned int val;
	int ret = 1;

	DBGENTER(1);
	/*
	 * If inverse mode was selected, invert all the colours
	 * rather than the register number.  The register number
	 * is what you poke into the framebuffer to produce the
	 * colour you requested.
	 */
	if (fbi->cmap_inverse) {
		red = 0xffff - red;
		green = 0xffff - green;
		blue = 0xffff - blue;
	}

	/*
	 * If greyscale is true, then we convert the RGB value
	 * to greyscale no mater what visual we are using.
	 */
	if (fbi->fb.var.grayscale)
		red = green = blue = (19595 * red + 38470 * green +
				      7471 * blue) >> 16;

	switch (fbi->fb.fix.visual) {
	case FB_VISUAL_TRUECOLOR:
		/*
		 * 12 or 16-bit True Colour.  We encode the RGB value
		 * according to the RGB bitfield information.
		 */
		if (regno < 16) {
			u32 *pal = fbi->fb.pseudo_palette;

			val = chan_to_field(red, &fbi->fb.var.red);
			val |= chan_to_field(green, &fbi->fb.var.green);
			val |= chan_to_field(blue, &fbi->fb.var.blue);

			pal[regno] = val;
			ret = 0;
		}
		break;

	case FB_VISUAL_STATIC_PSEUDOCOLOR:
	case FB_VISUAL_PSEUDOCOLOR:
		if (fbi->smode & FFB_MODE_RGB)
			ret =
			    ffb_setpalettereg(regno, red, green, blue,
					      trans, info);
		break;
	}

	DBGLEAVE(1);
	return ret;
}


/*
 * ffb_blank():
 *	Blank the display by setting all palette values to zero.  Note, the 
 * 	12 and 16 bpp modes don't really use the palette, so this will not
 *      blank the display in all modes.  
 */
int ffb_blank(int blank, struct fb_info *info)
{
#if 0
	struct ffb_info *fbi = (struct ffb_info *) info;
	int i;

	DBGENTER(1);

	DBGPRINT(3, "blank=%d\n", blank);

	switch (blank) {
	case FB_BLANK_POWERDOWN:
	case FB_BLANK_VSYNC_SUSPEND:
	case FB_BLANK_HSYNC_SUSPEND:
	case FB_BLANK_NORMAL:
		if (fbi->fb.fix.visual == FB_VISUAL_PSEUDOCOLOR ||
		    fbi->fb.fix.visual == FB_VISUAL_STATIC_PSEUDOCOLOR)
			for (i = 0; i < fbi->palette_size; i++)
				ffb_setpalettereg(i, 0, 0, 0, 0, info);
		ffb_schedule_work(fbi, C_DISABLE);
		break;

	case FB_BLANK_UNBLANK:
		if (fbi->fb.fix.visual == FB_VISUAL_PSEUDOCOLOR ||
		    fbi->fb.fix.visual == FB_VISUAL_STATIC_PSEUDOCOLOR)
			fb_set_cmap(&fbi->fb.cmap, info);
		ffb_schedule_work(fbi, C_ENABLE);
		break;
	}
	DBGLEAVE(1);
#endif

	return 0;
}

/*
 *  ffb_check_var():
 *    Round up in the following order: bits_per_pixel, xres,
 *    yres, xres_virtual, yres_virtual, xoffset, yoffset, grayscale,
 *    bitfields, horizontal timing, vertical timing.
 */
int ffb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	struct ffb_info *fbi = (struct ffb_info *) info;
	int rgbidx;

	DBGENTER(1);
	if (var->xres < MIN_XRES)
		var->xres = MIN_XRES;
	if (var->yres < MIN_YRES)
		var->yres = MIN_YRES;
	if (var->xres > fbi->max_xres)
		var->xres = fbi->max_xres;
	if (var->yres > fbi->max_yres)
		var->yres = fbi->max_yres;
	var->xres_virtual = max(var->xres_virtual, var->xres);
	var->yres_virtual = max(var->yres_virtual, var->yres);

	DBGPRINT(2, "var->bits_per_pixel=%d\n", var->bits_per_pixel);
	switch (var->bits_per_pixel) {
	case 4:
		rgbidx = RGB_8;
		break;
	case 8:
		rgbidx = RGB_8;
		break;
	case 16:
		rgbidx = RGB_16;
		break;
	case 24:
		rgbidx = RGB_24;
		break;
	default:
		return -EINVAL;
	}

	/*
	 * Copy the RGB parameters for this display
	 * from the machine specific parameters.
	 */
	var->red = fbi->rgb[rgbidx]->red;
	var->green = fbi->rgb[rgbidx]->green;
	var->blue = fbi->rgb[rgbidx]->blue;
	var->transp = fbi->rgb[rgbidx]->transp;

	DBGPRINT(2, "RGBT length = %d:%d:%d:%d\n",
		 var->red.length, var->green.length, var->blue.length,
		 var->transp.length);

	DBGPRINT(2, "RGBT offset = %d:%d:%d:%d\n",
		 var->red.offset, var->green.offset, var->blue.offset,
		 var->transp.offset);

	DBGLEAVE(1);
	return 0;
}


/*
 * ffb_set_par():
 *	Set the user defined part of the display for the specified console
 */
int ffb_set_par(struct fb_info *info)
{
	struct ffb_info *fbi = (struct ffb_info *) info;
	struct fb_var_screeninfo *var = &info->var;
	unsigned long palette_mem_size;

	DBGENTER(1);

//debug_Aaron on 04/30/2008, YUV bpp=8 should return TRUE COLOR also
//debug_Aaron on 05/02/2008, can not return TRUE COLOR if bpp=8
	//if (var->bits_per_pixel == 16)
	if (var->bits_per_pixel == 16 || var->bits_per_pixel == 24)
		fbi->fb.fix.visual = FB_VISUAL_TRUECOLOR;
	else if (!fbi->cmap_static)
		fbi->fb.fix.visual = FB_VISUAL_PSEUDOCOLOR;
	else {
		/*
		 * Some people have weird ideas about wanting static
		 * pseudocolor maps.  I suspect their user space
		 * applications are broken.
		 */
		fbi->fb.fix.visual = FB_VISUAL_STATIC_PSEUDOCOLOR;
	}

//debug_Aaron on 04/30/2008, if RGB mode bpp=24 should return 32
//debug_Aaron
//printk("%s: FB_MODE=%s\r\n", __func__, FB_MODE);
	if (FB_MODE[0]==0 || ((!strcmp(FB_MODE, "RGB")) && var->bits_per_pixel == 24))
	{
		fbi->fb.fix.line_length = var->xres_virtual * (var->bits_per_pixel + 8) / 8;
	}
	else
	{
		fbi->fb.fix.line_length = var->xres_virtual * var->bits_per_pixel / 8;
	}
//debug_aron
//printk("%s: var->bits_per_pixel=%d, fbi->fb.fix.visual=%d, var->xres_virtual=%d, fbi->fb.fix.line_length=%d\r\n", __func__, var->bits_per_pixel, fbi->fb.fix.visual, var->xres_virtual, fbi->fb.fix.line_length);

	fbi->palette_size = var->bits_per_pixel == 8 ? 256 : 16;

	palette_mem_size = fbi->palette_size * sizeof(u16);

	DBGPRINT(2, "palette_mem_size = 0x%08lx\n",
		 (u_long) palette_mem_size);

	fbi->palette_cpu =
	    (u16 *) (fbi->map_cpu + PAGE_SIZE - palette_mem_size);
	fbi->palette_dma = fbi->map_dma + PAGE_SIZE - palette_mem_size;
	f_data.uv_offset = (var->xres * var->yres + 0xffff) & 0xffff0000;

	/*
	 * Set (any) board control register to handle new color depth
	 */
	if (ffb_mach_ctl->ffb_activate_var(var, fbi))
		ffb_schedule_work(fbi, C_REENABLE);
	DBGLEAVE(1);
	return 0;
}

int ffb_mmap(struct fb_info *info, struct file *file,
	     struct vm_area_struct *vma)
{
	g_fb_open=1;	//marco
	struct ffb_info *fbi = (struct ffb_info *) info;
	unsigned long off = vma->vm_pgoff << PAGE_SHIFT;
	int ret = -EINVAL;

	DBGENTER(1);


	if (off < info->fix.smem_len * config_fb_number) {
//debug_Aaron on 05/13/2008, for 2nd CPU
#ifdef CPU1_BASE_OFFSET 
		off += (fbi->screen_dma  - CPU1_BASE_OFFSET) & PAGE_MASK;
#else
		off += (fbi->screen_dma) & PAGE_MASK;
#endif
		vma->vm_pgoff = off >> PAGE_SHIFT;
		vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);
		vma->vm_flags |= VM_RESERVED;
		ret = remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
				      vma->vm_end - vma->vm_start,
				      vma->vm_page_prot);
		DBGPRINT(3, "p=%#x, v=%#x, size=%#x\n", off, vma->vm_start,
			 vma->vm_end - vma->vm_start);
	} else {
		err("buffer mapping error !!\n");
	}

	DBGLEAVE(1);

	return ret;
}

/*
 * This function must be called from task context only, since it will
 * sleep when disabling the LCD controller, or if we get two contending
 * processes trying to alter state.
 */
static void set_ctrlr_state(struct ffb_info *fbi, u_int state)
{
	u_int old_state;

	down(&fbi->ctrlr_sem);

	old_state = fbi->state;

	/*
	 * Hack around fbcon initialisation.
	 */
	if (old_state == C_STARTUP && state == C_REENABLE)
		state = C_ENABLE;

	switch (state) {
	case C_DISABLE_PM:
	case C_DISABLE:
		/*
		 * Disable controller
		 */
		if (old_state != C_DISABLE) {
			fbi->state = state;
			ffb_mach_ctl->ffb_controller_disable(fbi);
		}
		break;

	case C_REENABLE:
		/*
		 * Re-enable the controller only if it was already
		 * enabled.  This is so we reprogram the control
		 * registers.
		 */
		if (old_state == C_ENABLE) {
			ffb_mach_ctl->ffb_controller_disable(fbi);
			ffb_mach_ctl->ffb_controller_enable(fbi);
		}
		break;

	case C_ENABLE_PM:
		/*
		 * Re-enable the controller after PM.  This is not
		 * perfect - think about the case where we were doing
		 * a clock change, and we suspended half-way through.
		 */
		if (old_state != C_DISABLE_PM)
			break;
		/* fall through */

	case C_ENABLE:
		/*
		 * Power up the LCD screen, enable controller, and
		 * turn on the backlight.
		 */
		if (old_state != C_ENABLE) {
			fbi->state = C_ENABLE;
			ffb_mach_ctl->ffb_controller_enable(fbi);
		}
		break;
	}
	up(&fbi->ctrlr_sem);
}

/*
 * Our LCD controller task (which is called when we blank or unblank)
 * via keventd.
 */
static void ffb_task(void *dummy)
{
	struct ffb_info *fbi = dummy;
	u_int state;

	DBGENTER(2);
	state = xchg(&fbi->task_state, -1);
	set_ctrlr_state(fbi, state);
	DBGLEAVE(2);
}

/* Fake monspecs to fill in fbinfo structure */
static struct fb_monspecs monspecs __initdata = {
	.hfmin = 30000,
	.hfmax = 70000,
	.vfmin = 50,
	.vfmax = 65,
};

#define FRAME_SIZE_RGB(xres,yres,mbpp)     ((xres) * (yres) * (mbpp) / 8)
#define FRAME_SIZE_YUV422(xres,yres,mbpp)  (((xres) * (yres) * (mbpp) / 8) * 2)
#define FRAME_SIZE_YUV420(xres,yres,mbpp)  (((((xres) * (yres) * (mbpp) / 8) + 0xffff) & 0xffff0000) * 3 / 2)

static inline u32 ffb_cal_frame_buf_size(struct ffb_info *fbi)
{
	u32 szfb_rgb, szfb_yuv420, szfb_yuv422, szfb_yuv;
	//debug_Aaron
	int bpp, size;

	//debug_Aaron
	DBGPRINT(3, "%s: fbi->max_xres=%d, fbi->max_yres=%d, fbi->max_bpp=%d\r\n", __func__, fbi->max_xres, fbi->max_yres, fbi->max_bpp);

	//debug_Aaron bpp=24 should allocate 32 bits
                if (fbi->max_bpp == 24)
                        bpp = 32;
                else
                        bpp = fbi->max_bpp;

	if ((fbi->max_xres == 640) || ((fbi->max_xres == 720))) {
	//	szfb_rgb = FRAME_SIZE_RGB(720, fbi->max_yres, fbi->max_bpp);
		szfb_rgb = FRAME_SIZE_RGB(fbi->max_xres, fbi->max_yres, bpp);
		
		szfb_yuv422 = FRAME_SIZE_YUV422(720, fbi->max_yres, 8);
		szfb_yuv420 = FRAME_SIZE_YUV420(720, fbi->max_yres, 8);
	} else if (fbi->max_xres == 320) {
//debug_Aaron
		//szfb_rgb = FRAME_SIZE_RGB(320, fbi->max_yres, fbi->max_bpp);
		szfb_rgb = FRAME_SIZE_RGB(320, fbi->max_yres, bpp);

		szfb_yuv422 = FRAME_SIZE_YUV422(320, fbi->max_yres, 8);
		szfb_yuv420 = FRAME_SIZE_YUV420(320, fbi->max_yres, 8);
	} else {
//debug_Aaron
//		szfb_rgb = FRAME_SIZE_RGB(fbi->max_xres, fbi->max_yres, fbi->max_bpp);
		szfb_rgb = FRAME_SIZE_RGB(fbi->max_xres, fbi->max_yres, bpp);

		szfb_yuv422 = FRAME_SIZE_YUV422(fbi->max_xres, fbi->max_yres, 8);
		szfb_yuv420 = FRAME_SIZE_YUV420(fbi->max_xres, fbi->max_yres, 8);
	}

	//debug_Aaron on 05/06/2008 return the exactly size
#if 0
	if (szfb_yuv422 > szfb_yuv420)
		szfb_yuv = szfb_yuv422;
	else
		szfb_yuv = szfb_yuv420;

	//debug_Aaron
	DBGPRINT(3, "%s: szfb_rgb=%d, szfb_yuv=%d\r\n", __func__, szfb_rgb, szfb_yuv);

	if (szfb_rgb > szfb_yuv)
		return szfb_rgb;
	else
		return szfb_yuv;
#else
	//debug_Aaron on 06/12/2008 allocate the maximum size
#if 1 
	if (fbi->smode & FFB_MODE_YUV422) 
	 	size = szfb_yuv422;
	else if (fbi->smode & FFB_MODE_YUV420) 
	 	size = szfb_yuv420;
	else
	 	size = szfb_rgb;
#endif
//	size = 720*576*4;
	
	DBGPRINT(3, "%s: video memory size=%d\r\n", __func__, size);
	return size;
#endif
}



/*
 * ffb_map_video_memory():
 *      Allocates the DRAM memory for the frame buffer.  This buffer is  
 *	remapped into a non-cached, non-buffered, memory region to  
 *      allow palette and pixel writes to occur without flushing the 
 *      cache.  Once this area is remapped, all virtual memory
 *      access to the video memory should occur at the new region.
 */
static int __init ffb_map_video_memory(struct ffb_info *fbi)
{
	size_t size;

	/*
	 * We reserve one page for the palette, plus the size
	 * of the framebuffer.
	 */
	fbi->map_size = PAGE_ALIGN(fbi->fb.fix.smem_len + PAGE_SIZE);
	
	size = fbi->map_size + (fbi->map_size-PAGE_SIZE)*(config_fb_number-1) + PAGE_SIZE;
	
	//debug_Aaron
	DBGPRINT(3, "%s: fbi->map_size=%d, PAGE_SIZE=%d, config_fb_number=%d\r\n", __func__, fbi->map_size, PAGE_SIZE, config_fb_number);
	DBGPRINT(3, "%s: PG prot=%d\r\n", __func__, pgprot_writecombine(pgprot_kernel));

	fbi->map_cpu = fmem_alloc(size, &fbi->map_dma, pgprot_writecombine(pgprot_kernel));
//debug_Aaron
//printk("%s: fbi->map_dma=0x%x\r\n", __func__, fbi->map_dma);
	if (fbi->map_cpu) {
		u32 i;
		size = fbi->map_size - PAGE_SIZE;
		for (i = 0; i < config_fb_number; i++) {
			fbi->ppfb_cpu[i] = fbi->map_cpu + PAGE_SIZE + (i * size);
			fbi->ppfb_dma[i] = fbi->map_dma + PAGE_SIZE + (i * size);
			f_data.mp4_map_dma[i] = fbi->ppfb_dma[i];
		}

		f_data.buf_len = size;
		f_data.frame_no = config_fb_number;
		
		fbi->fb.screen_base = fbi->map_cpu + PAGE_SIZE;
		fbi->screen_dma = fbi->map_dma + PAGE_SIZE;
		fbi->fb.fix.smem_start = fbi->screen_dma;
	}

	return fbi->map_cpu ? 0 : -ENOMEM;
}

static inline void ffb_clean_screen(struct ffb_info *fbi)
{
	//debug_Aaron
        int bits_per_pixel;

	DBGPRINT(3, "%s: fbi->smode=%d\r\n", __func__, fbi->smode);

	if (fbi->smode & FFB_MODE_YUV422) {
		unsigned int *pbuf;
		int i;
		pbuf = (unsigned int *) (fbi->ppfb_cpu[0] + PAGE_SIZE);
		for (i = 0; i < (fbi->fb.var.xres * fbi->fb.var.yres) >> 1;
		     i++)
			pbuf[i] = 0x10801080;
	} else if (fbi->smode & FFB_MODE_YUV420) {
		unsigned char *pbuf;
		//pbuf = fbi->ppfb_cpu[0] + PAGE_SIZE;
		pbuf = fbi->ppfb_cpu[0];
		memset(pbuf, 16, fbi->fb.var.xres * fbi->fb.var.yres);
		memset(pbuf + fbi->fb.var.xres * fbi->fb.var.yres, 128, fbi->fb.var.xres * fbi->fb.var.yres / 4);
		memset(pbuf + (fbi->fb.var.xres * fbi->fb.var.yres) * 5 / 4, 128, fbi->fb.var.xres * fbi->fb.var.yres / 4);
	} else {
		unsigned char *pbuf;
	//debug_Aaron
		//pbuf = fbi->ppfb_cpu[0] + PAGE_SIZE;
		pbuf =  fbi->fb.screen_base;

	DBGPRINT(3, "%s: pbuf=0x%x, fbi->fb.var.xres=%d, fbi->fb.var.yres=%d, fbi->fb.var.bits_per_pixel=%d, f_data.buf_len=%d\r\n",
       		__func__, pbuf, fbi->fb.var.xres, fbi->fb.var.yres, fbi->fb.var.bits_per_pixel, f_data.buf_len);

		memset(pbuf, 0, f_data.buf_len);
	}

	//printk("%s: Exit...\r\n", __func__);
}

static inline void ffb_unmap_video_memory(struct ffb_info *fbi)
{
	size_t size;

	//debug_Aaron
	size = fbi->map_size+f_data.buf_len*(config_fb_number-1) + PAGE_SIZE;
	fmem_free(size, fbi->map_cpu, fbi->map_dma);
}

static struct ffb_info *__init ffb_init_fbinfo(struct device *dev)
{
	struct ffb_info *fbi;
	struct ffb_mach_info *minf;

	DBGENTER(1);

	fbi =
	    kmalloc(sizeof(struct ffb_info) + sizeof(u32) * 16,
		    GFP_KERNEL);
	if (!fbi) {
		goto err;
	}

	memset(fbi, 0, sizeof(struct ffb_info));
	fbi->dev = dev;

	if (ffb_mach_ctl->ffb_dev_init(fbi) < 0)
		goto err;

	fbi->fb.fix.type = FB_TYPE_PACKED_PIXELS;
	fbi->fb.fix.type_aux = 0;
	fbi->fb.fix.xpanstep = 0;
	fbi->fb.fix.ypanstep = 0;
	fbi->fb.fix.ywrapstep = 0;
	fbi->fb.fix.accel = FB_ACCEL_NONE;

	//debug_Aaron


	fbi->fb.var.nonstd = 0;
	fbi->fb.var.activate = FB_ACTIVATE_NOW;
	fbi->fb.var.height = -1;
	fbi->fb.var.width = -1;
	fbi->fb.var.accel_flags = 0;
	fbi->fb.var.vmode = FB_VMODE_NONINTERLACED;

	fbi->fb.flags = FBINFO_DEFAULT;
	fbi->fb.monspecs = monspecs;
	fbi->fb.pseudo_palette = (fbi + 1);

	fbi->rgb[RGB_8] = &rgb_8;
	fbi->rgb[RGB_16] = &def_rgb_16;
	fbi->rgb[RGB_24] = &def_rgb_24;

	minf = (struct ffb_mach_info *) dev->platform_data;
	if (ffb_mach_ctl->ffb_set_var(fbi, 0))
		goto err;

	fbi->state = C_STARTUP;
	fbi->task_state = (u_char) - 1;
	fbi->fb.fix.smem_len = ffb_cal_frame_buf_size(fbi);

	init_waitqueue_head(&fbi->ctrlr_wait);
	INIT_WORK(&fbi->task, ffb_task, fbi);
	init_MUTEX(&fbi->ctrlr_sem);

	DBGLEAVE(1);
	return fbi;
      err:
	kfree(fbi);
	DBGLEAVE(1);
	return NULL;

}

static ssize_t ffb_show_version(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%s:%s\n", FFB_MODULE_NAME,
			FFB_VERSION);
}

static DEVICE_ATTR(version, S_IRUGO, ffb_show_version, NULL);

static inline u_int index2bit(u_int index)
{
	u_int flags = 1;

	return (flags << index);
}

const char *mode_string[] = {
	"NTSC",
	"PAL",
	"TV640",
	"LCD",
};

const char *color_string[] = {
	"RGB",
	"YUV420",
	"YUV422",
};

static int show_2way_string(char *buf, ssize_t bufsize, char *string1,
			    char *string2)
{
	if (string1[0] == '\0' && string2[0] == '\0')
		return 0;
	else
		return snprintf(buf, bufsize, "%22s | %22s\n", string1,
				string2);
}

static int show_mode_string(char *buf, ssize_t bufsize, u_long flags)
{
	int r = 0;
	int i = 0, j = 0;
	int total_size = bufsize;
	u_char index1 = 0, index2 = 0;
	char string1[22];
	char string2[22];
	u_long color_flag = flags & 0xFF;
	u_long mode_flag = (flags >> 8) & 0xFF;
	int finish = 0;


	while (!finish) {
		while (i <= 8) {
			index1 = (mode_flag >> i) & 0x01;
			if (index1)
				break;
			i++;
		}

		while (j <= 8) {
			index2 = (color_flag >> j) & 0x01;
			if (index2)
				break;
			j++;
		}

		if (index1) {
			snprintf(string1, 22, "%-12s   0x%02x00",
				 mode_string[i], i);
		} else {
			string1[0] = '\0';
		}

		if (index2) {
			snprintf(string2, 22, "%-12s   0x%04x",
				 color_string[j], j);
		} else {
			string2[0] = '\0';
		}

		r = show_2way_string(buf, bufsize, string1, string2);
		buf += r;
		bufsize -= r;
		if (!bufsize)
			goto end;
		i++;
		j++;

		if (i >= 8 && j >= 8)
			finish = 1;
	}

      end:
	return total_size - bufsize;
}

static ssize_t ffb_show_mode_tables(struct device *dev,
				    struct device_attribute *attr,
				    char *buf)
{
	ssize_t bufsize = PAGE_SIZE;
	int r = 0;
	struct ffb_mach_info *minf =
	    (struct ffb_mach_info *) dev->platform_data;
	char string1[22];
	char string2[22];

	snprintf(string1, 22, "%-12s   %5s", "Mode", "Index");
	snprintf(string2, 22, "%-12s   %5s", "Color Space", "Index");
	r = show_2way_string(buf, bufsize, string1, string2);
	buf += r;
	bufsize -= r;
	if (!bufsize)
		goto end;

	r = show_2way_string(buf, bufsize, "----------------------",
			     "----------------------");
	buf += r;
	bufsize -= r;
	if (!bufsize)
		goto end;
	r = show_mode_string(buf, bufsize, minf->support_modes);
	bufsize -= r;
      end:
	return PAGE_SIZE - bufsize;
}

int ffb_identify_mode(char *buf, ssize_t bufsize, u_long flags)
{
	int i = 0, j = 0;
	int r = 0;
	u_char index1 = 0, index2 = 0;
	u_long color_flag = flags & 0xFF;
	u_long mode_flag = (flags >> 8) & 0xFF;
	ssize_t t_bufsize = bufsize;

	while (i <= 8) {
		index1 = (mode_flag >> i) & 0x01;
		if (index1)
			break;
		i++;
	}

	while (j <= 8) {
		index2 = (color_flag >> j) & 0x01;
		if (index2)
			break;
		j++;
	}

	if (index1) {
		r = snprintf(buf, bufsize, "%s", mode_string[i]);
	}
	buf += r;
	bufsize -= r;
	if (!bufsize)
		goto end;
	if (index2) {
		r = snprintf(buf, bufsize, "(%s)", color_string[j]);
	}
	buf += r;
	bufsize -= r;
      end:
	return t_bufsize - bufsize;
}

static ssize_t ffb_show_mode(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	struct ffb_info *fbi = dev_get_drvdata(dev);

	int r = 0;

	if (fbi) {
		r = ffb_identify_mode(buf, PAGE_SIZE - 1, fbi->smode);
		buf[r] = '\n';
		r++;
	} else
		r = -ENODEV;
	return r;
}

static ssize_t ffb_store_mode(struct device *dev,
			      struct device_attribute *attr,
			      const char *buf, size_t size)
{
	struct ffb_info *fbi = dev_get_drvdata(dev);
	int r = 0;

	if (fbi) {
		u_long tmode = 0;
		if (sscanf(buf, "%16lx", &tmode) == 1) {
			tmode =
			    index2bit(tmode & 0x1f) |
			    (index2bit((tmode >> 8) & 0x1f) << 8);
			if (ffb_mach_ctl->ffb_set_var(fbi, tmode))
				return -EINVAL;
			fbi->smode &= ~0x0000ffff;
			fbi->smode |= tmode;
			fb_set_var(&fbi->fb, &fbi->fb.var);
			ffb_check_var(&fbi->fb.var, &fbi->fb);
			ffb_set_par(&fbi->fb);
			ffb_clean_screen(fbi);
		} else
			r = -EINVAL;
	} else
		r = -ENODEV;
	return r ? r : size;
}

static DEVICE_ATTR(mode_tables, 0444, ffb_show_mode_tables, NULL);
static DEVICE_ATTR(ffb_mode, 0664, ffb_show_mode, ffb_store_mode);

static struct attribute *ffb_attrs[] = {
	&dev_attr_mode_tables.attr,
	&dev_attr_ffb_mode.attr,
	NULL,
};

static struct attribute_group ffb_attrs_grp = {
	.name = "ffb_attrs",
	.attrs = ffb_attrs,
};


static int ffb_register_sysfs(struct ffb_info *fbi)
{
	int ret;

	if ((ret = device_create_file(fbi->dev, &dev_attr_version)))
		goto fail0;

	if ((ret = sysfs_create_group(&fbi->dev->kobj, &ffb_attrs_grp)))
		goto fail1;

	return 0;

	sysfs_remove_group(&fbi->dev->kobj, &ffb_attrs_grp);
      fail1:
	device_remove_file(fbi->dev, &dev_attr_version);
      fail0:
	err("unable to register sysfs interface\n");
	return ret;
}

static void ffb_unregister_sysfs(struct ffb_info *fbi)
{
	sysfs_remove_group(&fbi->dev->kobj, &ffb_attrs_grp);
	device_remove_file(fbi->dev, &dev_attr_version);
}

#if defined(CONFIG_FB_SIGNAL)
static struct proc_dir_entry *info_entry;
pid_t mpid = 0;

static int flcd_atoi(char *s)
{
	int k = 0;

	k = 0;
	while (*s != '\0' && *s >= '0' && *s <= '9') {
		k = 10 * k + (*s - '0');
		s++;
	}
	return k;
}

static int proc_read_flcd_info(char *page, char **start, off_t off,
			       int count, int *eof, void *data)
{
	int len;
	len = sprintf(page, "%d\n", mpid);
	*eof = 1;		//end of file
	*start = page + off;
	len = len - off;
	return len;
}

static int proc_write_flcd_info(struct file *file, const char *buffer,
				unsigned long count, void *data)
{
	int len = count;
	unsigned char value[20];
	if (copy_from_user(value, buffer, len))
		return 0;
	value[len] = '\0';
	mpid = flcd_atoi(value);
	return count;
}
#endif


int ffb_probe(struct device *dev)
{
	struct platform_device *pdev;
	struct ffb_info *fbi;
	int ret = 0;
	
	DBGENTER(1);
	
	pdev = to_platform_device(dev);

	fbi = ffb_init_fbinfo(&pdev->dev);

	if (!fbi) {
		err("unable to allocate memory for device info\n");
		ret = -ENOMEM;
		goto cleanup;
	}

	/* Initialize video memory */
	ret = ffb_map_video_memory(fbi);

	if (ret < 0) {
		goto cleanup;
	}

	/*
	 * This makes sure that our colour bitfield
	 * descriptors are correctly initialised.
	 */
	ffb_check_var(&fbi->fb.var, &fbi->fb);
	ffb_set_par(&fbi->fb);
	ffb_schedule_work(fbi, C_REENABLE);
	dev_set_drvdata(&pdev->dev, fbi);

	ret = register_framebuffer(&fbi->fb);

	//debug_Aaron
	DBGPRINT(3, "%s: register_framebuffer(), ret=%d\r\n", __func__, ret);

	if (ret < 0) {
		err("register_framebuffer failed\n");
		goto err_free_map;
	}

	ret = ffb_mach_ctl->ffb_isr_init(pdev, fbi);
	if(ret < 0) {
		goto err_free_reg;
	}	

	ffb_clean_screen(fbi);

	ret = ffb_register_sysfs(fbi);
	if (ret)
		goto err_free_isr;

#if defined(CONFIG_FB_SIGNAL)
	info_entry = create_proc_entry(pdev->name, 777, NULL);
	if (info_entry == NULL) {
		err("Fail to create proc entry: info!\n");
		ret = -EINVAL;
		goto err_free_sysfs;
	}

	info_entry->read_proc = (read_proc_t *) proc_read_flcd_info;
	info_entry->write_proc = (write_proc_t *) proc_write_flcd_info;
	info_entry->owner = THIS_MODULE;

	mpid = 0;
#endif
	DBGLEAVE(1);

	return 0;
#if defined(CONFIG_FB_SIGNAL)
      err_free_sysfs:
	ffb_unregister_sysfs(fbi);
#endif
      err_free_isr:
	ffb_mach_ctl->ffb_isr_release(pdev, fbi);
      err_free_reg:
	unregister_framebuffer(&fbi->fb);
      err_free_map:
	ffb_unmap_video_memory(fbi);
      cleanup:
	dev_set_drvdata(&pdev->dev, NULL);

	kfree(fbi);
	DBGLEAVE(1);
	return ret;
}

/* Called when the device is being detached from the driver */
int ffb_remove(struct device *dev)
{
	struct platform_device *pdev;
	struct ffb_info *fbi = dev_get_drvdata(dev);

	DBGENTER(1);
	pdev = to_platform_device(dev);

	remove_proc_entry("flcd", NULL);
	ffb_unregister_sysfs(fbi);

	set_ctrlr_state(fbi, C_DISABLE);

	ffb_mach_ctl->ffb_isr_release(pdev, fbi);

	unregister_framebuffer(&fbi->fb);
	ffb_unmap_video_memory(fbi);
	dev_set_drvdata(&pdev->dev, NULL);
	kfree(fbi);
	DBGLEAVE(1);
	
	return 0;
}

#ifdef CONFIG_PM
/* suspend and resume support for the lcd controller */

int ffb_suspend(struct device *dev, pm_message_t state)
{
	struct ffb_info *fbi = dev_get_drvdata(dev);

	DBGENTER(1);

	if (level == SUSPEND_DISABLE || level == SUSPEND_POWER_DOWN)
		set_ctrlr_state(fbi, C_DISABLE_PM);

	DBGLEAVE(1);
	return 0;
}

int ffb_resume(struct device *dev)
{
	struct ffb_info *fbi = dev_get_drvdata(dev);

	DBGENTER(1);

	if (level == RESUME_ENABLE)
		set_ctrlr_state(fbi, C_ENABLE_PM);

	DBGLEAVE(1);
	return 0;
}

#endif

int ffb_ioctl(struct inode *inode, struct file *file, unsigned int cmd,
	      unsigned long arg, struct fb_info *info)
{
	int ret = 0;

	DBGENTER(1);

	switch (cmd) {
	case FLCD_GET_DATA_SEP:
	case FFB_GET_DATA_SEP:
		DBGPRINT(3, "FFB_GET_DATA_SEP:\n");
		if (copy_to_user
		    ((struct flcd_data *) arg, &f_data,
		     sizeof(struct flcd_data)))
			ret = -EFAULT;
		break;
	default:
		DBGPRINT(3, "cmd(0x%x) no define!\n", cmd);
		ret = -EFAULT;
		break;
	}
	DBGLEAVE(1);
	return ret;
}

ffb_hw_param_t *ffb_get_hw_param(ffb_hw_param_t * array, u_long num_array,
				 u_long type)
{
	int i;

	for (i = 0; i < num_array; i++) {
		ffb_hw_param_t *r = &array[i];
		if ((r->flags & type & 0xff) && (r->flags & type & 0xff00))
			return r;
	}
	return NULL;
}

ffb_hw_res_t *ffb_get_hw_res(ffb_hw_res_t * array, u_long num_array,
			     u_long type)
{
	int i;

	for (i = 0; i < num_array; i++) {
		ffb_hw_res_t *r = &array[i];

		if (r->flags & type & 0xff00)
			return r;
	}
	return NULL;
}


int ffb_device_register(struct ffb_mach_ops *ops)
{
	int ret = 0;
	ffb_mach_ctl = ops;
	return ret;
}

MODULE_VERSION(FFB_VERSION);
