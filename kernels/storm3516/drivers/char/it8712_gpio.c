/*
 * FILE NAME it8712_gpio.c
 *
 * BRIEF MODULE DESCRIPTION
 *  API for it8712 GPIO device.
 *  Driver for it8712 GPIO device.
 *
 *  Author: StorLink, Corp.
 *          Andy Chang
 *
 * Copyright 2003 StorLink, Corp.
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
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/sched.h>
#include <linux/kdev_t.h>
#include <asm/io.h>
#include <asm/arch/it8712.h>
#include <asm/hardware.h>

#define IT8712_SET_GPIO_PIN_IN		1
#define IT8712_SET_GPIO_PIN_OUT		2
#define IT8712_SET_GPIO_PIN_STATUS_LOW	3
#define IT8712_SET_GPIO_PIN_STATUS_HIGH	4
#define IT8712_GET_GPIO_PIN_STATUS 	5
#define LPC_BASE_ADDR			IO_ADDRESS(IT8712_IO_BASE)

extern int it8712_exist;

#define MAX_GPIO_LINE	40
#define inb_gpio(x)			inb(LPC_BASE_ADDR + IT8712_GPIO_BASE + x)
#define outb_gpio(x, y)		outb(y, LPC_BASE_ADDR + IT8712_GPIO_BASE + x)

wait_queue_head_t it8712_gpio_wait[MAX_GPIO_LINE];

//static int it8712_gpio_debug=0;
//#define DEB(x)  if (it8712_gpio_debug>=1) x

// set: 1-5
// mode:0: input, 1: output
void set_it8712_gpio_io_mode(unsigned char pin, unsigned char mode)
{
	unsigned char iomode;
	unsigned char set = pin / 8;		// each GPIO set has 8 pins
	
	iomode = LPCGetConfig(LDN_GPIO, 0xc8 + set);
	iomode &= ~(1 << (pin % 8));
	iomode |= (mode << (pin % 8));
	LPCSetConfig(LDN_GPIO, 0xc8 + set, iomode);
}

// set: 1-5
// high: 1:high, 0:low
void set_it8712_gpio_pin_status(unsigned char pin, unsigned char high)
{
	unsigned char status;
	unsigned char set = pin / 8;		// each GPIO set has 8 pins
	
	status = inb_gpio(set);
	status &= ~(1 << (pin % 8));
	status |= (high << (pin % 8));
	outb_gpio(set, status);
}

// set: 1-5
// return: 1:high, 0:low
int get_it8712_gpio_pin_status(unsigned char pin)
{
	unsigned char status;
	unsigned char set = pin / 8;		// each GPIO set has 8 pins
	
	status = inb_gpio(set);
	if (status & (1 << (pin % 8)))
		return 1;
	return 0;
}

static int it8712_gpio_open(struct inode *inode, struct file *file)
{
	unsigned int minor;
	
	minor = MINOR(inode->i_rdev); 
	if (minor != GPIO_MINOR)
		return -ENODEV;
	printk("it8712_gpio open\n");

#ifdef MODULE
	MOD_INC_USE_COUNT;
#endif

	return 0;
}


static int it8712_gpio_release(struct inode *inode, struct file *file)
{

#ifdef MODULE
	MOD_DEC_USE_COUNT;
#endif
	printk("it8712_gpio release\n");
	return 0;
}


static int it8712_gpio_ioctl(struct inode *inode, struct file *file,
	unsigned int cmd, unsigned long arg)
{
	unsigned char pin = (unsigned char) arg;

	if (pin >= MAX_GPIO_LINE) 	
	{
		printk("it8712_gpio ioctl fail\n");
		return -EFAULT;
	}
	printk("it8712_gpio ioctl successly\n");

	switch(cmd) {
		case IT8712_SET_GPIO_PIN_IN:
			set_it8712_gpio_io_mode(pin, 0);
			break;

		case IT8712_SET_GPIO_PIN_OUT:
			set_it8712_gpio_io_mode(pin, 1);
			break;

		case IT8712_SET_GPIO_PIN_STATUS_LOW:
			set_it8712_gpio_pin_status(pin, 0);
			break;

		case IT8712_SET_GPIO_PIN_STATUS_HIGH:
			set_it8712_gpio_pin_status(pin, 1);
			break;
		
		case IT8712_GET_GPIO_PIN_STATUS:
			return get_it8712_gpio_pin_status(pin);
			break;

		default:
			return -ENOIOCTLCMD;

	}
	return 0;
}


static struct file_operations it8712_gpio_fops =
{
	owner:		THIS_MODULE,
	ioctl:		it8712_gpio_ioctl,
	open:		it8712_gpio_open,
	release:	it8712_gpio_release,
};

/* GPIO_MINOR in include/linux/miscdevice.h */
static struct miscdevice it8712_gpio_miscdev =
{
	GPIO_MINOR,
	"it8712_gpio",
	&it8712_gpio_fops
};

int __init it8712_gpio_init(void)
{
	int i;

	misc_register(&it8712_gpio_miscdev);
	
	if (!it8712_exist) {
		return -ENODEV;
	}
	printk("it8712_gpio init\n");
	
	/* initialize registers */
	// switch all multi-function pins to GPIO
	LPCSetConfig(LDN_GPIO, 0x25, 0xff);
	LPCSetConfig(LDN_GPIO, 0x26, 0xff);
	LPCSetConfig(LDN_GPIO, 0x27, 0xff);
	LPCSetConfig(LDN_GPIO, 0x28, 0xff);
	LPCSetConfig(LDN_GPIO, 0x29, 0xff);

	// set simple I/O base address
	LPCSetConfig(LDN_GPIO, 0x62, IT8712_GPIO_BASE >> 8);
	LPCSetConfig(LDN_GPIO, 0x63, (unsigned char) IT8712_GPIO_BASE >> 8);
	
	// select GPIO to simple I/O
	LPCSetConfig(LDN_GPIO, 0xc0, 0xff);
	LPCSetConfig(LDN_GPIO, 0xc1, 0xff);
	LPCSetConfig(LDN_GPIO, 0xc2, 0xff);
	LPCSetConfig(LDN_GPIO, 0xc3, 0xff);
	LPCSetConfig(LDN_GPIO, 0xc4, 0xff);

	// enable internal pull-up
	LPCSetConfig(LDN_GPIO, 0xb8, 0xff);
	LPCSetConfig(LDN_GPIO, 0xb9, 0xff);
	LPCSetConfig(LDN_GPIO, 0xba, 0xff);
	LPCSetConfig(LDN_GPIO, 0xbb, 0xff);
	LPCSetConfig(LDN_GPIO, 0xbc, 0xff);
	
	// set polarity to inverting
//	LPCSetConfig(LDN_GPIO, 0xb0, 0xff);

	for (i = 0; i < MAX_GPIO_LINE; i++) {
		init_waitqueue_head(&it8712_gpio_wait[i]);
	}
	return 0;
}	

void __exit it8712_gpio_exit(void)
{
	misc_deregister(&it8712_gpio_miscdev);
}

module_init(it8712_gpio_init);
module_exit(it8712_gpio_exit);

MODULE_LICENSE("GPL");
