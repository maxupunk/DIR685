#ifndef __TVE200_FB_H__
#define __TVE200_FB_H__

#define IPMODULE TVE
#define IPNAME   FTTVEC200


//debug_Aaron
//#define TVE_FTTVEC200_0_PA_BASE         0xf6a00000
//#define TVE_FTTVEC200_0_PA_LIMIT        0xf6a80000
#define TVE_FTTVEC200_IRQ               13

#include "tve-config.h"

typedef struct {
	u_long ctrl1;
	u_long ctrl3;
	u_short xres;
	u_short yres;
} tve_mach_timer_t;

struct tve_mach_info {
	u_long num_ctrl1;
	ffb_hw_param_t *ctrl1;
	u_long num_ctrl3;
	ffb_hw_param_t *ctrl3;
	u_long num_res;
	ffb_hw_res_t *res;
	u_long support_modes;
	u_long bypass;		// pmu 0x14
	u_long pixclock;
	u_long max_xres;	// x resolution
	u_long max_yres;	// y resolution
	u_char max_bpp;
	u_char sync;
	u_int cmap_grayscale:1,
	    cmap_inverse:1, cmap_static:1, cmap_invert_clock:1, unused:28;
};

typedef struct TVETag {
	u32 Ybase;		//0x00
	u32 Ubase;		//0x04
	u32 Vbase;		//0x08

	u32 INTEn;		//0x0c
	u32 INTClr;		//0x10
	u32 INTSts;		//0x14

	u32 Ctrl1;		//0x18
	u32 Ctrl2;		//0x1c          
	u32 Ctrl3;		//0x20
	u32 Ctrl4;		//0x24
} TVE200_Register;

struct tve_mach_data {
	u_long ctrl1;
	u_long ctrl3;
	u_long int_mask;
	u_long u_offset;
	u_long v_offset;
};

//The interface for platform depend
extern void tve_platform_pmu_on(void);
extern void tve_platform_pmu_off(void);
extern void tve_platform_setup_i2c(u_long type);

//debug_Aaron
char *fmem_alloc(int size, u32 *dma_handle, u32 offset);
void *fmem_free(size_t size, void *cpu_addr, dma_addr_t handle);

#endif				/* __TVE200_FB_H__ */
