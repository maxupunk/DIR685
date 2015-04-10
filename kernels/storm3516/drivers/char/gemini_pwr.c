/*
 * FILE NAME gemini_pwr.c
 *
 * BRIEF MODULE DESCRIPTION
 *  Driver for Power control.
 *
 *  Author: StorLink, Corp.
 *          Jason Lee
 *
 * Copyright 2005 StorLink, Corp.
 *
 *  This program is free software; you can redistribute  it and/or modify it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMit8712D  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE	LIABLE FOR ANY   DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMit8712D   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License along
 *  with this program; if not, writ8712  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <linux/module.h>
#include <linux/config.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/interrupt.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <linux/ioport.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <asm/io.h>
#include <asm/delay.h>
#include <linux/signal.h>
#include <linux/apm_bios.h>
#include <asm/hardware.h>
#include <asm/arch/sl2312.h>
#include <asm/arch/int_ctrl.h>
#include <asm/arch/gemini_gpio.h>
#include <asm/arch/gemini_cir.h>

#ifndef PWR_MINOR
#define PWR_MINOR	241		// Documents/devices.txt suggest to use 240~255 for local driver!!
#endif

#define GEMINI_PWR_IP_ID		0x00010500

#ifndef	SL2312_POWER_CTRL_BASE
#define	SL2312_POWER_CTRL_BASE		0x4B000000
#endif

#ifndef PWR_BASE_ADDR
#define	PWR_BASE_ADDR		IO_ADDRESS(SL2312_POWER_CTRL_BASE)
#endif
#define	PWR_CTRL_ID		*(unsigned int*)(PWR_BASE_ADDR+0x00)
#define	PWR_CTRL_REG		*(unsigned int*)(PWR_BASE_ADDR+0x04)
#define	PWR_STATUS_REG		*(unsigned int*)(PWR_BASE_ADDR+0x08)

#define	PWR_SHUTDOWN		0x01

#ifndef	IRQ_PWC
#define	IRQ_PWC		26
#endif


#ifndef SL2312_GPIO_BASE
#define SL2312_GPIO_BASE		0x4D000000
#endif
//#define SL2312_GPIO_BASE_ADDR	IO_ADDRESS(SL2312_GPIO_BASE1)

#define GPIO_LEVEL_TRIG		1
#define GPIO_EDGE_TRIG		0
#define GPIO_LOW_ACTIVE		1
#define GPIO_HIGH_ACTIVE	0
#define GPIO_FALL_ACTIVE	1
#define GPIO_RISE_ACTIVE	0
#define GPIO_BOTH_EDGE		1
#define GPIO_SINGLE_EDGE	0

enum GPIO_REG
{
    GPIO_DATA_OUT   		= 0x00,
    GPIO_DATA_IN    		= 0x04,
    GPIO_PIN_DIR    		= 0x08,
    GPIO_BY_PASS    		= 0x0C,
    GPIO_DATA_SET   		= 0x10,
    GPIO_DATA_CLEAR 		= 0x14,
    GPIO_PULL_ENABLE 		= 0x18,
    GPIO_PULL_TYPE 			= 0x1C,
    GPIO_INT_ENABLE 		= 0x20,
    GPIO_INT_RAW_STATUS 	= 0x24,
    GPIO_INT_MASK_STATUS 	= 0x28,
    GPIO_INT_MASK 			= 0x2C,
    GPIO_INT_CLEAR 			= 0x30,
    GPIO_INT_TRIG 			= 0x34,
    GPIO_INT_BOTH 			= 0x38,
    GPIO_INT_POLAR 			= 0x3C
};
#define GPIO_FAC_DEF		63
#define GPIO_FAC_PIN		BIT((GPIO_FAC_DEF%32))

#if (GPIO_FAC_DEF > 31)
#define SL2312_GPIO_BASE_ADDR	IO_ADDRESS(SL2312_GPIO_BASE1)
#else
#define SL2312_GPIO_BASE_ADDR	IO_ADDRESS(SL2312_GPIO_BASE)
#endif
#define LATCH_TIME			5
#define PUSH_VALUE			0
unsigned int Action=0;

static int gemini_pwr_debug = 0 ;
#define DEB(x)  if(gemini_pwr_debug>=1) x
unsigned int pwr_src=0;

wait_queue_head_t pwc_wait_q;

static unsigned int pwr_read_reg(unsigned int offset)
{
    unsigned int    reg_val;

    reg_val = readl(CIR_BASE_ADDR + offset);
	return (reg_val);
}

static void pwr_write_reg(unsigned int offset,unsigned int data,unsigned int bit_mask)
{
	unsigned int reg_val;
    unsigned int *addr;

	reg_val = ( pwr_read_reg(offset) & (~bit_mask) ) | (data & bit_mask);
	addr = (unsigned int *)(CIR_BASE_ADDR + offset);
    writel(reg_val,addr);
	return;
}

static int gemini_pwr_open(struct inode *inode, struct file *file)
{
//	PWR_CTRL_REG |= BIT(1);
//	if (request_irq(IRQ_PWC, pwr_interrupt, SA_INTERRUPT, "Power Control", NULL))
//		printk("Error: Register IRQ for Power control failed\n");

	return 0;
}

static int gemini_pwr_release(struct inode *inode, struct file *file)
{
	return 0;
}


// Interrupt handle
static irqreturn_t pwr_interrupt(int irq, void *dev_instance, struct pt_regs *regs)
{
	
	unsigned int reg_v,addr;
	// Get power interrupt source
	mdelay(1);
	pwr_src = PWR_STATUS_REG&0x70;
	
	
	printk("Power event by ");
	switch(pwr_src){
		case PWR_STAT_CIR:
			CIR_STATUS_REG &= ~BIT(0);	// Clear CIR interrupt indicator
			printk("CIR...\n");
			break;
		case PWR_STAT_RTC:
			printk("RTC...\n");
			break;
		case PWR_STAT_PUSH:
			printk("Button...\n");
			break;
		default:
			printk("Unknow Source \n");
	}
	
	mdelay(1);
	PWR_CTRL_REG |= BIT(2);
	Action = POWEROFF;
	
	addr = IO_ADDRESS(SL2312_INTERRUPT_BASE);
	reg_v = readl(addr+0x08);
	reg_v |= BIT(IRQ_PWC);
	writel(reg_v,addr+0x08);
	wmb();
	
	wake_up(&pwc_wait_q);
	Action = POWEROFF;
	return IRQ_RETVAL(IRQ_HANDLED);
}


static void gpio_handle()
{
	unsigned int int_src,addr,data,addr2;
	unsigned char i=0;
	
	addr = SL2312_GPIO_BASE_ADDR + GPIO_INT_RAW_STATUS ;

	int_src = readl(addr);
	if(int_src&GPIO_FAC_PIN){
		DEB(printk("Restore Factory Default\n"));
		wake_up(&pwc_wait_q);
		addr = SL2312_GPIO_BASE_ADDR + GPIO_INT_MASK ;
		data = readl(addr);
		data |= GPIO_FAC_PIN ;					// mask INT
		writel(data,addr);
		addr = SL2312_GPIO_BASE_ADDR + GPIO_INT_CLEAR ;
		data = readl(addr);
		data |= GPIO_FAC_PIN ;					// clear INT
		writel(data,addr);
		// count push time
		addr = SL2312_GPIO_BASE_ADDR + GPIO_DATA_IN ;
		for(i=0;i<=LATCH_TIME*10;i++){
			int_src = readl(addr);
			
			if((int_src & GPIO_FAC_PIN)==PUSH_VALUE) {
				if((i%10)==0)
					printk("\r%d seconds to restore default!!\r",LATCH_TIME-i/10);
				
				addr2 = SL2312_GPIO_BASE_ADDR + GPIO_INT_CLEAR ;
				data = readl(addr2);
				data |= GPIO_FAC_PIN ;					// clear INT
				writel(data,addr2);
			}
			else {
				break;
			}
			mdelay(100);
		}
		if((i/10)<1){					
			Action = SYSTEM_REBOOT;
			wake_up(&pwc_wait_q);
			printk("\nReboot\n");
		}
		else if((i/10)<LATCH_TIME) {
			Action = 0;
			printk("\nAbort!\n");
			return;
		}
		else{
			Action = RESTORE_DEFAULT;
			wake_up(&pwc_wait_q);
			printk("\nFactory Default\n");
		}
	}

}

void config_gpio_pin()
{
	request_gpio_irq(GPIO_FAC_DEF,gpio_handle,GPIO_EDGE_TRIG,GPIO_FALL_ACTIVE,GPIO_SINGLE_EDGE);
}

int gemini_pwr_wait (void)
{
	config_gpio_pin();
	interruptible_sleep_on(&pwc_wait_q);
	free_gpio_irq(GPIO_FAC_DEF);
	return pwr_src;
}

void gemini_pwr_set_time(unsigned int sec)
{
	sec = sec & 0x03;
	sec -= 3;
	//pwr_write_reg(PWR_CTRL_REG, 0, BIT(5)|BIT(6));
	//pwr_write_reg(PWR_CTRL_REG, sec<<5, BIT(5)|BIT(6));
	
	
}

static int gemini_pwr_ioctl(struct inode *inode, struct file *file,
	unsigned int cmd, unsigned long arg)
{
	int ret = 0;
	struct pwc_ioctl_data data;
	
	DEB(printk("power ioctl successly\n"));

	switch(cmd) {
		case PWC_SET_SHUT_TIME:
			if (copy_from_user(&data, (struct pwc_ioctl_data *)arg, sizeof(data)))
				return -EFAULT;
			gemini_pwr_set_time(data.data);
			break;
		
		case PWC_WAIT_BTN:
			if (copy_from_user(&data, (struct pwc_ioctl_data *)arg, sizeof(data)))
				return -EFAULT;
			ret = gemini_pwr_wait();				// Waiting Power Interrupt 
			data.data = ret ;
			data.action = Action;
			if (copy_to_user((struct pwc_ioctl_data *)arg, &data, sizeof(data)))
				return -EFAULT;
			break;
		default:
			return -1;
	}
	return 0;
}


void gemini_pwr_init(void)
{
	//pwr_write_reg(PWR_CTRL_REG, BIT(1), BIT(1));
	PWR_CTRL_REG |= BIT(1);
	
	if (request_irq(IRQ_PWC, pwr_interrupt, SA_INTERRUPT, "Power Control", NULL))
		printk("Error: Register IRQ for Power control failed\n");
	
}

static struct file_operations gemini_pwr_fops =
{
	.owner		=		THIS_MODULE,
	.ioctl		=		gemini_pwr_ioctl,
	.open		=		gemini_pwr_open,
	.release	=		gemini_pwr_release,
};

/* include/linux/miscdevice.h */
static struct miscdevice gminie_pwr_miscdev =
{
	PWR_MINOR,
	"sl_pwr",
	&gemini_pwr_fops
};

int __init gimini_pwr_init(void)
{
	unsigned int reg_v;
	
	if((PWR_CTRL_ID&0xFFFFFF00)!=GEMINI_PWR_IP_ID){
		printk("Gemini PWC Module Not Found!!\n");
		return -ENODEV;							// Storlink PWC not found!!
	}
	mdelay(1);
	printk("Register Gemini Power control\n");
	misc_register(&gminie_pwr_miscdev);
	
	// Clear INTERRUPT 
//	pwr_write_reg(PWR_CTRL_REG, BIT(2), BIT(2));
	PWR_CTRL_REG |= BIT(2);
	mdelay(1);

	init_waitqueue_head(&pwc_wait_q);
	
	gemini_pwr_init();
	config_gpio_pin();
		
	return 0;
}	

void __exit gemini_pwr_exit(void)
{
	free_irq(IRQ_PWC,NULL);
	misc_deregister(&gminie_pwr_miscdev);
}

module_init(gimini_pwr_init);
module_exit(gemini_pwr_exit);

MODULE_AUTHOR("Jason Lee <jason@storlink.com.tw>");
MODULE_DESCRIPTION("Gemini Power control driver");
MODULE_LICENSE("GPL");
