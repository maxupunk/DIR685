#include <asm/uaccess.h>
#include <asm/arch/spec.h>
#include <linux/delay.h>

#include "ffb.h"
#include "tve-config.h"
#include "gmfb-i2c.c"

#define CS4954

void tve_platform_setup_i2c(u_long type)
{
#ifdef CONFIG_STD_TV

#ifdef CS4954
	if (FFB_MODE_PAL & type) {
		TV = TV_PAL;
		TV_init = TV_CS4954_init_PAL;
	} else {
		TV = TV_NTSC;
		TV_init = TV_CS4954_init_NTSC;
	}

	set_data_direct(0, 0x20, 0x20);	//GPIO 5 reset CS4954 100 us, high->low->high
	set_data_output(0, 0x20, 0x20);
	udelay(400);
	set_data_output(0, 0x20, 0);
	udelay(400);
	set_data_output(0, 0x20, 0x20);
	tv_CS4954();
#else
	if (FFB_MODE_PAL & type) {
		TV = TV_PAL;
		TV_init = TV_init_PAL;
	} else {
		TV = TV_NTSC;
		TV_init = TV_init_NTSC;
	}

	tv_init1();
	tv_init2();
#endif

#endif
}

inline void tve_platform_pmu_on(void)
{
	outl(inl(PMU_FTPMU010_VA_BASE + 0x130) | 0x08000000,
	     PMU_FTPMU010_VA_BASE + 0x130);
}

inline void tve_platform_pmu_off(void)
{
	outl(inl(PMU_FTPMU010_VA_BASE + 0x130) & ~0x08000000,
	     PMU_FTPMU010_VA_BASE + 0x130);
}
