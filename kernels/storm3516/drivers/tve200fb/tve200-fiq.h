#ifndef __TVE200_FIQ_H__
#define __TVE200_FIQ_H__

#define TVE_CTRL_BASE   0
#define MACH_DATA_BASE  1
#define CT656_CTRL_BASE 2
#define INT_CTRL_BASE   3
#define FFB_FBI_BASE    4
#define FFB_DO_UPDATING 5    //do_updating 
#define FFB_OLD_FB      6    //old_fbnum
#define FFB_MISS        7    //miss_num
#define ACT_VBI_INFO    8    //act_vbi_info
#define G_VBI_INFO      9    //g_vbi_info
#define G_VBI_LINE     10    //g_vbi_line
#define TVE_FIQ_NUM    11    

#define TVE_DATA_LEN    12

#define ADDR_OFFSET(x)      (x << 2)

#define FBI_NUM   (offsetof(struct ffb_info,ppfb_num))
#define FBI_ppfb_num   FBI_NUM

//debug_Aaron
#define TVE_FTTVEC200_0_PA_BASE 	0x80000000
#define TVE_FTTVEC200_0_PA_LIMIT	0x8fffffff
#define TVE_FTTVEC200_IRQ		5
#define CT656_FTCT656_0_VA_BASE		0xc0000000
#define INTC_FTINTC010_VA_BASE		0xc0000000
#define FIQ_CLEAR_REG	12
#define FIQ_MASK_REG 	13

#
extern struct bus_type platform_bus_type;

#endif /* __TVE200_FIQ_H__  */
