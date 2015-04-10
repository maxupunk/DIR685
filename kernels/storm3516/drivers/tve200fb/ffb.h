#ifndef __FFB_H
#define __FFB_H

#define FFB_VERSION      "0.3.0"
#define FFB_MODULE_NAME  "GM_fb"

#define PFX		 FFB_MODULE_NAME

//debug_Aaron
#include <linux/platform_device.h>

#include <linux/fb.h>
#include <linux/types.h>
#include "config.h"
#include "ffb-api.h"

struct ffb_rgb {
	struct fb_bitfield red;
	struct fb_bitfield green;
	struct fb_bitfield blue;
	struct fb_bitfield transp;
};

#define RGB_8	(0)
#define RGB_16	(1)
#define RGB_24	(2)
#define NR_RGB	 3

struct ffb_info {
	struct fb_info fb;
	struct device *dev;
	struct ffb_rgb *rgb[NR_RGB];

	u_int max_bpp;
	u_int max_xres;
	u_int max_yres;

	/*
	 * These are the addresses we mapped
	 * the framebuffer memory region to.
	 */
	dma_addr_t map_dma;
	u_char *map_cpu;
	u_int map_size;

	u_char *screen_cpu;
	dma_addr_t screen_dma;
	u16 *palette_cpu;
	dma_addr_t palette_dma;
	u_int palette_size;

	u_int cmap_inverse:1, cmap_static:1, unused:30;

	volatile u_char state;
	volatile u_char task_state;
	struct semaphore ctrlr_sem;
	wait_queue_head_t ctrlr_wait;
	struct work_struct task;

	u_long io_base;
	u_long smode;
	u_char *ppfb_cpu[CONFIG_MAX_FRAME_NO];
	dma_addr_t ppfb_dma[CONFIG_MAX_FRAME_NO];
	u_long ppfb_num;
};

struct ffb_mach_ops {
        int (*ffb_dev_init)(struct ffb_info *fbi);
	int (*ffb_activate_var) (struct fb_var_screeninfo *var,
				 struct ffb_info *fbi);
	int (*ffb_set_var) (struct ffb_info * fbi, u_long type);
	void (*ffb_controller_enable) (struct ffb_info *fbi);
	void (*ffb_controller_disable) (struct ffb_info *fbi);
	int (*ffb_isr_init) (struct platform_device *pdev, struct ffb_info *fbi);
	void (*ffb_isr_release) (struct platform_device *pdev, struct ffb_info *fbi);
};

struct ffb_mach_info {
	u_long support_modes;
	void *mach_data;
};

typedef struct {
	u_long value;
	u_long flags;
} ffb_hw_param_t;

typedef struct {
	u_long xres;
	u_long yres;
	u_long flags;
} ffb_hw_res_t;


#define __type_entry(ptr,type,member) ((type *)((char *)(ptr)-offsetof(type,member)))

#define TO_INF(ptr,member)	__type_entry(ptr,struct ffb_info,member)

/*
 * These are the actions for set_ctrlr_state
 */
#define C_DISABLE		(0)
#define C_ENABLE		(1)
#define C_DISABLE_CLKCHANGE	(2)
#define C_ENABLE_CLKCHANGE	(3)
#define C_REENABLE		(4)
#define C_DISABLE_PM		(5)
#define C_ENABLE_PM		(6)
#define C_STARTUP		(7)

#define FFB_MODE_RGB          0x00000001
#define FFB_MODE_YUV420       0x00000002
#define FFB_MODE_YUV422       0x00000004
#define FFB_MODE_NTSC         0x00000100
#define FFB_MODE_PAL          0x00000200
#define FFB_MODE_TV640        0x00000400
#define FFB_MODE_LCD          0x00000800

/*
 * Minimum X and Y resolutions
 */
#define MIN_XRES	64
#define MIN_YRES	64

//ffb-lib => The interface for framebuffer.
extern int ffb_check_var(struct fb_var_screeninfo *var,
			 struct fb_info *info);
extern int ffb_set_par(struct fb_info *info);
extern int ffb_setcolreg(u_int regno, u_int red, u_int green, u_int blue,
			 u_int trans, struct fb_info *info);
extern int ffb_blank(int blank, struct fb_info *info);
extern int ffb_mmap(struct fb_info *info, struct file *file,
		    struct vm_area_struct *vma);
extern int ffb_ioctl(struct inode *inode, struct file *file,
		     unsigned int cmd, unsigned long arg,
		     struct fb_info *info);
extern int ffb_probe(struct device *dev);
extern int ffb_remove(struct device *dev);
extern int ffb_identify_mode(char *buf, ssize_t bufsize, u_long flags);
extern ffb_hw_param_t *ffb_get_hw_param(ffb_hw_param_t * array,
					u_long num_array, u_long type);
extern ffb_hw_res_t *ffb_get_hw_res(ffb_hw_res_t * array, u_long num_array,
				    u_long type);
extern irqreturn_t ffb_handle_irq(int irq, void *dev_id,
				  struct pt_regs *regs);

extern int ffb_device_register(struct ffb_mach_ops *ops);

//ffb-lib => The interface for PM
#ifdef CONFIG_PM
extern int ffb_suspend(struct device *dev, pm_message_t state);
extern int ffb_resume(struct device *dev);
#else
#define ffb_suspend  NULL
#define ffb_resume   NULL
#endif
#endif				/* __FFB_H */
