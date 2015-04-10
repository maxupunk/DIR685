/*
 * FILE NAME sl_cir.c
 *
 * BRIEF MODULE DESCRIPTION
 *  Driver for CIR device.
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
#include <asm/hardware.h>
#include <asm/io.h>
#include <asm/delay.h>
#include <linux/signal.h>
#include <asm/arch/gemini_cir.h>


//#define	DEBUT_CIR	1
#ifndef CIR_MINOR
#define CIR_MINOR	240		// Documents/devices.txt suggest to use 240~255 for local driver!!
#endif

#ifndef	IRQ_CIR
#define	IRQ_CIR		25
#endif


static int sl_cir_debug = 1 ;
#define DEB(x)  if(sl_cir_debug>=1) x

unsigned int data=0;
unsigned short data_ext=0;
wait_queue_head_t cir_wait_q;
extern void arch_power_off(char mode);

static unsigned int cir_read_reg(unsigned int offset)
{
    unsigned int    reg_val;

    reg_val = readl(CIR_BASE_ADDR + offset);
	return (reg_val);
}

static void cir_write_reg(unsigned int offset,unsigned int data,unsigned int bit_mask)
{
	unsigned int reg_val;
    unsigned int *addr;

	reg_val = ( cir_read_reg(offset) & (~bit_mask) ) | (data & bit_mask);
	addr = (unsigned int *)(CIR_BASE_ADDR + offset);
    writel(reg_val,addr);
	return;
}

// set: 1-5
// mode:0: input, 1: output
void set_sl_cir_set_baudrate(unsigned short baud)
{
	unsigned int tmp;
	tmp = CIR_CTR_REG & 0x0000FFFE ;
	tmp |= (baud*EXT_CLK)<<16;
//	CIR_CTR_REG = tmp |BIT(0);
}

void set_sl_cir_set_h_period(unsigned int period)
{
	unsigned int tmp;
	if(period>16)
		period = 16;
	
	tmp = CIR_CTR_REG & 0xFFFF0FFE ;
	tmp |= (period-1)<<12;
//	CIR_CTR_REG = tmp |BIT(0);
}

void set_sl_cir_set_l_period(unsigned int period)
{
	unsigned int tmp;
	if(period>16)
		period = 16;
	
	tmp = CIR_CTR_REG & 0xFFFFF0FE ;
	tmp |= (period-1)<<8;
//	CIR_CTR_REG = tmp |BIT(0);
}

void set_sl_cir_set_protocol(unsigned int protocol)
{
	unsigned int tmp;
	
	tmp = CIR_CTR_REG & ~(BIT(4)|BIT(1)) ;
	tmp |= protocol ? BIT(4):0;
//	CIR_CTR_REG = tmp |BIT(0);
}

void set_sl_cir_set_demodula(unsigned int enable)
{
	
//	cir_write_reg(CIR_STATUS_REG, enable?BIT(1):0, BIT(1));
}

void set_sl_cir_set_compare(unsigned int enable)
{
	
//	cir_write_reg(CIR_STATUS_REG, enable?BIT(23):0, BIT(23));
//	cir_write_reg(CIR_CTR_REG, BIT(0), BIT(0));
}

void set_sl_cir_set_powerkey(unsigned int key,unsigned int key_ext)
{
//	unsigned int reg_v;
#if 0	
	// clear initialize ok bit
	reg_v = cir_read_reg(CIR_CTR_REG);
	reg_v &= ~BIT(0);
	cir_write_reg(CIR_CTR_REG,reg_v,BIT(0));
	
	// set power key
	cir_write_reg(CIR_PWR_REG,key,0xFFFFFFFF);
	cir_write_reg(CIR_PWR_EXT_REG,key_ext,0x0000FFFF);
	
	// set initialize ok bit
	reg_v = cir_read_reg(CIR_CTR_REG);
	reg_v |= BIT(0);
	cir_write_reg(CIR_CTR_REG,reg_v,BIT(0));
#endif	
}

void cir_init(int mode)
{
	unsigned int baud;
	unsigned int reg_v;
	
	if(mode==VCC_PROTOCOL) {			// VCR-33
		/*=================== Set RX/TX baud rate ==================*/
		baud = VCC_BAUD*EXT_CLK ;
		CIR_CTR_REG &= 0x0000FFE8 ;
		CIR_CTR_REG |= (baud << 16) |BIT(4);
		CIR_TX_CTR_REG = 0x0 ;
		CIR_CTR_REG |= (baud << 16);
		
	
		/*=================== Set Power key ==================*/
		CIR_PWR_REG = VCR_KEY_POWER;
		CIR_PWR_EXT_REG = 0;
		
		/*=============== Set Carrier Frequency ==============*/
		CIR_TX_FEQ_REG = (unsigned int)(EXT_CLK/CARR_FREQ);
	
		CIR_CTR_REG &= 0xFFFF00FF;
		CIR_CTR_REG |= (VCC_H_ACT_PER<<12)|(VCC_L_ACT_PER<<8);
	
		CIR_STATUS_REG &= 0xFFC0FFFF;
		CIR_STATUS_REG |= VCC_DATA_LEN<<16 ;

		CIR_TX_CTR_REG &= 0xFFFF0000;					// Set TX para
		CIR_TX_CTR_REG |= (VCC_H_ACT_PER<<12)|(VCC_L_ACT_PER<<8)|(VCC_DATA_LEN);

		CIR_TX_FEQ_REG = (unsigned int)(EXT_CLK/CARR_FREQ);
	
	}
	else if(mode==TV1_PROTOCOL) {			// TV1-26
		/*=================== Set RX/TX baud rate ==================*/
		baud = TV1_BAUD*EXT_CLK ;
		CIR_CTR_REG &= 0x0000FFE8 ;
		CIR_CTR_REG |= (baud << 16) | BIT(4);
		CIR_TX_CTR_REG = 0x0 ;
		CIR_CTR_REG |= (baud << 16);
	
		/*=================== Set Power key ==================*/
		CIR_PWR_REG = TV1_KEY_POWER;
		CIR_PWR_EXT_REG = TV1_KEY_POWER_EXT;
	
		/*=============== Set Carrier Frequency ==============*/
		CIR_TX_FEQ_REG = (unsigned int)(EXT_CLK/CARR_FREQ);
	
		CIR_CTR_REG &= 0xFFFF00FF;
		CIR_CTR_REG |= (TV1_H_ACT_PER<<12)|(TV1_L_ACT_PER<<8);

		CIR_STATUS_REG &= 0xFFC0FFFF;
		CIR_STATUS_REG |= TV1_DATA_LEN<<16 ;

		CIR_TX_CTR_REG &= 0xFFFF0000;					// Set TX para
		CIR_TX_CTR_REG |= (TV1_H_ACT_PER<<12)|(TV1_L_ACT_PER<<8)|(TV1_DATA_LEN);

		CIR_TX_FEQ_REG = (unsigned int)(EXT_CLK/CARR_FREQ);
	}
	
	CIR_CTR_REG |= BIT(0);		// Initial complete
	CIR_STATUS_REG &= ~BIT(1);	// Clear Interrupt
	mdelay(10);
	
	reg_v = PWR_CTRL_REG ;
	mdelay(10);
	PWR_CTRL_REG = reg_v | BIT(2) |BIT(1);	// Clear cir interrupt;
	mdelay(10);
	reg_v &= ~BIT(1);
	reg_v |= BIT(0);
	PWR_CTRL_REG = reg_v|BIT(2);	// Power off machine because of first power on
	
	

}


static int sl_cir_open(struct inode *inode, struct file *file)
{
	//if (request_irq(IRQ_CIR, cir_interrupt, SA_INTERRUPT, "cir", NULL))
	//	printk("Error: Register IRQ for Storlink IR failed\n");
	
	return 0;
}


static int sl_cir_release(struct inode *inode, struct file *file)
{
	//free_irq(IRQ_CIR,NULL);
	return 0;
}

static irqreturn_t cir_interrupt(int irq, void *dev_instance, struct pt_regs *regs)
{
	unsigned int addr,reg_v;
//	unsigned int reg_v;
	// Programming sequence:
	// 如果接收長度大於32bit,則先讀EXTEND register,再取DATA register
	// 只要讀DATA register,interrupt 就被清除
	DEB(printk("CIR RX:0x"));
	if(((CIR_STATUS_REG>>16)&0x00003F)>32) {
		data_ext = CIR_RX_EXT_REG;
		data = CIR_RX_REG;
		DEB(printk("%08x%04x\n",data,data_ext));
	}
	else {
		data = CIR_RX_REG;
		DEB(printk("%08x\n",data));
	}
	//mdelay(10);
	CIR_STATUS_REG &= ~BIT(1);
	addr = IO_ADDRESS(SL2312_INTERRUPT_BASE);
	reg_v = readl(addr+0x08);
	reg_v |= BIT(IRQ_CIR);
	writel(reg_v,addr+0x08);
	wake_up_interruptible(&cir_wait_q);
	
	return IRQ_RETVAL(IRQ_HANDLED);
}


int sl_cir_int_wait (__u32 *data1,__u32 *data2,__u32 timeout)
{
	int ret=0;

	ret = interruptible_sleep_on_timeout(&cir_wait_q, timeout*HZ);
	if(ret > 0){
		*data1 = data;
		*data2 = data_ext;
	}
	else{
		*data1 = 0;
		*data2 = 0;
	}
	return ret;
}

static int sl_cir_ioctl(struct inode *inode, struct file *file,
	unsigned int cmd, unsigned long arg)
{
	int ret = 0;
	struct cir_ioctl_data para;
	struct cir_ioctl_data48 data48;
	
	DEB(printk("cir ioctl successly\n"));

	switch(cmd) {
		case CIR_SET_BAUDRATE:
			if (copy_from_user(&para, (struct cir_ioctl_data *)arg, sizeof(para)))
				return -EFAULT;
			set_sl_cir_set_baudrate(para.data);
			break;
		case CIR_SET_HIGH_PERIOD:
			if (copy_from_user(&para, (struct cir_ioctl_data *)arg, sizeof(para)))
				return -EFAULT;
			set_sl_cir_set_h_period(para.data);
			
			break;
		case CIR_SET_LOW_PERIOD:
			if (copy_from_user(&para, (struct cir_ioctl_data *)arg, sizeof(para)))
				return -EFAULT;
			set_sl_cir_set_l_period(para.data);
			break;
		case CIR_SET_PROTOCOL:
			if (copy_from_user(&para, (struct cir_ioctl_data *)arg, sizeof(para)))
				return -EFAULT;
			set_sl_cir_set_protocol(para.data);
			break;
		case CIR_SET_ENABLE_COMPARE:
			if (copy_from_user(&para, (struct cir_ioctl_data *)arg, sizeof(para)))
				return -EFAULT;
			set_sl_cir_set_compare(para.data);
			break;
		case CIR_SET_ENABLE_DEMOD:
			if (copy_from_user(&para, (struct cir_ioctl_data *)arg, sizeof(para)))
				return -EFAULT;
			set_sl_cir_set_demodula(para.data);
			break;
		case CIR_SET_POWER_KEY:
			if (copy_from_user(&data48, (struct cir_ioctl_data48 *)arg, sizeof(data48)))
				return -EFAULT;
			
			set_sl_cir_set_powerkey(data48.data,data48.data_ext);
			break;
		case CIR_GET_ENABLE_DEMOD:
			
			break;
		case CIR_GET_DATA:
			if (copy_from_user(&data48, (struct cir_ioctl_data48 *)arg, sizeof(data48)))
				return -EFAULT;
			data48.ret = OLD_DATA;
			data48.data = data;
			data48.data_ext = data_ext;
			if (copy_to_user((struct cir_ioctl_data48 *)arg, &data48, sizeof(data48)))
				return -EFAULT;
			break;
		case CIR_WAIT_INT_DATA:
			if (copy_from_user(&data48, (struct cir_ioctl_data48 *)arg, sizeof(data48)))
				return -EFAULT;
			ret = sl_cir_int_wait(&data48.data,&data48.data_ext,data48.timeout);
			data48.ret = (ret>0) ? NEW_RECEIVE:OLD_DATA;				
			if (copy_to_user((struct cir_ioctl_data48 *)arg, &data48, sizeof(data48)))
				return -EFAULT;
			break;
		default:
			return -1;
	}
	return 0;
}


static struct file_operations sl_cir_fops =
{
	.owner		=	THIS_MODULE,
	.ioctl		=	sl_cir_ioctl,
	.open		=	sl_cir_open,
	.release	=	sl_cir_release,
};

/* include/linux/miscdevice.h */
static struct miscdevice sl_cir_miscdev =
{
	CIR_MINOR,
	"sl_cir",
	&sl_cir_fops
};

int __init sl_cir_init(void)
{
//	unsigned int reg_v;
	
//	reg_v = cir_read_reg(CIR_IP_ID);
	if((CIR_IP_ID&0xFFFFFF00)!=STORLINK_CIR_ID){
		printk("Storlink IR Module Not Found!!\n");
		return -ENODEV;							// Storlink CIR not found!!
	}
	
	misc_register(&sl_cir_miscdev);
	printk("Storlink CIR Initialization\n");

	if(CIR_STATUS_REG&BIT(2))		// First Power On
	{
		printk("Please reboot now.");
		cir_init(TV1_PROTOCOL);
	}

	// Clear INTERRUPT before request_irq
//	reg_v = cir_read_reg(CIR_STATUS_REG);
//	reg_v &= ~(BIT(0)|BIT(1));
//	cir_write_reg(CIR_STATUS_REG, reg_v, BIT(0)|BIT(1) );
	CIR_STATUS_REG &= ~(BIT(0)|BIT(1));
	
	if (request_irq(IRQ_CIR, cir_interrupt, SA_INTERRUPT, "cir", NULL))
		printk("Error: Register IRQ for Storlink IR failed\n");
	
	init_waitqueue_head(&cir_wait_q);
	
	return 0;
}	

void __exit sl_cir_exit(void)
{
	free_irq(IRQ_CIR,NULL);
	misc_deregister(&sl_cir_miscdev);
}

module_init(sl_cir_init);
module_exit(sl_cir_exit);

MODULE_AUTHOR("Jason Lee <jason@storlink.com.tw>");
MODULE_DESCRIPTION("Gemini CIR driver");
MODULE_LICENSE("GPL");
