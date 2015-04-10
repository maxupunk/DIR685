/* vi: set sw=4 ts=4: */
/*
 *	FV13XX Access driver.
 *
 *	This driver is used to access the linux kernel resource, mostly the GPIO.
 *	This driver works on FV13XX (kernel version 2.6.17)
 *
 *		David Hsieh <david_hsieh@alphanetworks.com>
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/reboot.h>
#include <asm/hardware.h>
#include <asm/io.h>

//#define MY_DEBUG	"david"
#define MODULE_NAME	"nas_gpio"



#ifdef MY_DEBUG
#define DPRINTK(fmt, args...)	printk("%s: " fmt, __FUNCTION__ , ## args)
#else
#define DPRINTK(fmt, args...)
#endif


/***************************************************************************/

#if 0
static u32 gpio_data_reg[4]		= {FV_GPIO_PADR, FV_GPIO_PBDR, FV_GPIO_PCDR, FV_GPIO_PDDR };
static u32 gpio_outen_reg[4]	= {FV_GPIO_PADIR,FV_GPIO_PBDIR,FV_GPIO_PCDIR,FV_GPIO_PDDIR};
#else 
//#define NO_OF_GPIO_OPEN 9//marco
//static int g_GPIO_USED[]={7,8,11,12,13,14,16,18,6};
#define NO_OF_GPIO_OPEN 8//marco
static int g_GPIO_USED[]={7,8,11,12,14,16,18,6};

#define GPIO_BASE_ADDR      (IO_ADDRESS(SL2312_GPIO_BASE))
enum GPIO_REG
{
    GPIO_DATA_OUT   = 0x00,
    GPIO_DATA_IN    = 0x04,
    GPIO_PIN_DIR    = 0x08,
    GPIO_BY_PASS    = 0x0c,
    GPIO_DATA_SET   = 0x10,
    GPIO_DATA_CLEAR = 0x14,
};
#define MIS_GP0DIR                  (IO_ADDRESS(SL2312_GPIO_BASE)+GPIO_PIN_DIR)
#define MIS_GP1DIR                  (IO_ADDRESS(SL2312_GPIO_BASE1)+GPIO_PIN_DIR)
#define MIS_GP0DATI                 (IO_ADDRESS(SL2312_GPIO_BASE)+GPIO_DATA_IN)
#define MIS_GP1DATI                 (IO_ADDRESS(SL2312_GPIO_BASE1)+GPIO_DATA_IN)
#define MIS_GP0DATO                 (IO_ADDRESS(SL2312_GPIO_BASE)+GPIO_DATA_OUT)
#define MIS_GP1DATO                 (IO_ADDRESS(SL2312_GPIO_BASE1)+GPIO_DATA_OUT)
static u32 gpio_outen_reg[2]		= {MIS_GP0DIR,MIS_GP1DIR };
static u32 gpio_data_reg[4]	= {MIS_GP0DATO,MIS_GP1DATO,MIS_GP0DATI,MIS_GP1DATI};
#endif
static inline u32 __set_reg_bit(u32 reg, int bit, int set)
{
	u32 data = __raw_readl(reg);
	if (set)	data |= ((u32)1 << bit);
	else		data &= ~((u32)1 << bit);
	__raw_writel(data, reg);
	DPRINTK("reg=0x%08x, bit=%d, data=0x%08x\n", (int)reg, bit, (int)data);
	return data;
}

static inline int __get_reg_bit(u32 reg, int bit)
{
	DPRINTK("reg=0x%08x, bit=%d, data=0x%08x\n", (int)reg, bit, (int)__raw_readl(reg));
	return (__raw_readl(reg) & ((u32)1 << bit)) ? 1 : 0;
}

#define GPIO_READ_DI(port,bit)			__get_reg_bit(gpio_data_reg[(port)%2+2], (bit))
#define GPIO_READ_DO(port,bit)			__get_reg_bit(gpio_data_reg[(port)%2], (bit))
#define GPIO_GET_OUTEN(port,bit)		__get_reg_bit(gpio_outen_reg[(port)%4], (bit))
#define GPIO_WRITE_DATA(port,bit,val)	__set_reg_bit(gpio_data_reg[(port)%2], (bit), (val)&1);
#define GPIO_SET_OUTEN(port,bit,outen)	__set_reg_bit(gpio_outen_reg[(port)%4], (bit), (outen))
/***************************************************************************/

#define GPIO_DIR	"gpio"
#define GPIO_OUTEN	"outen"
#define GPIO_DATA	"data"
#define GPIO_PORTS	2

struct gpio_entry
{
	struct proc_dir_entry * control;
	struct proc_dir_entry * data;
	int port;
	int line;
	int outen;
};

static struct proc_dir_entry * gpio_dir = NULL;
static spinlock_t gpio_lock;
//static int gpio_count[] = {8, 4, 0};
static int gpio_count[] = {NO_OF_GPIO_OPEN, NO_OF_GPIO_OPEN, 0};
static struct gpio_entry gpio_entries[2][NO_OF_GPIO_OPEN];


////////////////////////////////////////////////////////
//PIN a_13 using interrupt
/////////////////////////////////////////////////////////
#define GPIO_LEVEL_TRIG		1
#define GPIO_EDGE_TRIG		0
#define GPIO_LOW_ACTIVE		1
#define GPIO_HIGH_ACTIVE	0
#define GPIO_FALL_ACTIVE	1
#define GPIO_RISE_ACTIVE	0
#define GPIO_BOTH_EDGE		1
#define GPIO_SINGLE_EDGE	0 

#define GPIO_INTERRUPT_PIN  13
#define GPIO_READ_PROC_NAME "data_pa_13"
static int gpio13_interrupt_value = 0;
extern int request_gpio_irq(int bit,void (*handler)(int),char level,char high,char both);
extern int free_gpio_irq(int bit);
static void gpio_interrupt_handle(int unuse) 
{
	gpio13_interrupt_value = 1;
	
}
static int proc_read_gpio13(char * buf, char ** start, off_t offset, int len, int * eof, void * data)
{
	char * p = buf;
	p += sprintf(p, "%d\n",	gpio13_interrupt_value);
	*eof = 1;
	if(gpio13_interrupt_value) gpio13_interrupt_value = 0;//if read clear...
	
	return p - buf;
}

static int __init gpio_interrupt_init(struct proc_dir_entry * parent)
{
	static struct proc_dir_entry * proc_data_pa_13 = NULL;
	proc_data_pa_13 = create_proc_entry(GPIO_READ_PROC_NAME, 0644, parent);
	if (proc_data_pa_13)
	{
		proc_data_pa_13->read_proc	= proc_read_gpio13;
		proc_data_pa_13->owner		= THIS_MODULE;
		//regist the interrupt call back
		if(request_gpio_irq(GPIO_INTERRUPT_PIN,gpio_interrupt_handle,GPIO_EDGE_TRIG,GPIO_FALL_ACTIVE,GPIO_SINGLE_EDGE))
		{
			printk("regist gpio interrupt error\n");
			return -1;
		}
		return 0;
	}
	else
		return -ENOMEM;
}
static void __exit gpio_interrupt_exit(struct proc_dir_entry * parent)
{
	if (parent)
		remove_proc_entry(GPIO_READ_PROC_NAME, parent);
	free_gpio_irq(GPIO_INTERRUPT_PIN);
}
////////////////////////////////////////////////////////////////////////////////////
/***************************************************************************/

static int proc_read_gpio(char * buf, char ** start, off_t offset, int len, int * eof, void * data)
{
	struct gpio_entry * gpio = (struct gpio_entry *)data;
	char * p = buf;

	p += sprintf(p, "%d\n",
			gpio->outen ?
			GPIO_READ_DO(gpio->port, gpio->line) :
			GPIO_READ_DI(gpio->port, gpio->line)
			);
	*eof = 1;
	return p - buf;
}

static int proc_write_gpio(struct file * file, const char * buf, unsigned long count, void * data)
{
	struct gpio_entry * gpio = (struct gpio_entry *)data;
	if (gpio->outen)
	{
		GPIO_WRITE_DATA(gpio->port, gpio->line, (buf[0]=='0') ? 0 : 1);
	}
	return count;
}

static void create_data_proc(struct gpio_entry * gpio)
{
	char name[32];
	if (gpio->data == NULL && gpio_dir)
	{
		sprintf(name, "%s_p%c_%d", GPIO_DATA, gpio->port + 'a', gpio->line);
		gpio->data = create_proc_entry(name, 0644, gpio_dir);
		if (gpio->data)
		{
			gpio->data->data		= gpio;
			gpio->data->read_proc	= proc_read_gpio;
			gpio->data->write_proc	= proc_write_gpio;
			gpio->data->owner		= THIS_MODULE;
		}
	}
}

/* ------------------------------------------- */

static int proc_read_outen(char * buf, char ** start, off_t offset, int len, int * eof, void * data)
{
	struct gpio_entry * gpio = (struct gpio_entry *)data;
	char * p = buf;

	gpio->outen = GPIO_GET_OUTEN(gpio->port, gpio->line);
	p += sprintf(p, "%d\n", gpio->outen);
	*eof = 1;
	create_data_proc(gpio);
	return p - buf;
}

static int proc_write_outen(struct file * file, const char * buf, unsigned long count, void * data)
{
	struct gpio_entry * gpio = (struct gpio_entry *)data;

	if (buf[0] == '0')
	{
		if (gpio->outen == 1) GPIO_SET_OUTEN(gpio->port, gpio->line, 0);
	}
	else
	{
		if (gpio->outen == 0) GPIO_SET_OUTEN(gpio->port, gpio->line, 1);
	}
	gpio->outen = GPIO_GET_OUTEN(gpio->port, gpio->line);
	create_data_proc(gpio);
	return count;
}

/* ------------------------------------------- */

static void __exit gpio_exit(struct proc_dir_entry * parent)
{
	int port, line;
	char name[32];
	int i=0;
	if (gpio_dir)
	{
		for (port=0; gpio_count[port]; port++)
		{
			for(i=0; i<NO_OF_GPIO_OPEN;i++)//marco
			{
				line=g_GPIO_USED[i];
				if (gpio_entries[port][i].data)
				{
					sprintf(name, "%s_p%c_%d", GPIO_DATA, port+'a', line);
					DPRINTK("Removing entry: %s\n", name);
					remove_proc_entry(name, gpio_dir);
					gpio_entries[port][i].data = NULL;
				}
				if (gpio_entries[port][i].control)
				{
					sprintf(name, "%s_p%c_%d", GPIO_OUTEN, port+'a', line);
					DPRINTK("Removing entry: %s\n", name);
					remove_proc_entry(name, gpio_dir);
					gpio_entries[port][i].control = NULL;
				}
			}
		}
		gpio_interrupt_exit(gpio_dir);
		/* remove GPIO directory */
		DPRINTK("Remove entry [%s]\n",GPIO_DIR);
		remove_proc_entry(GPIO_DIR, parent);
		gpio_dir = NULL;
	}
}

static int __init gpio_init(struct proc_dir_entry * parent)
{
	int port, line;
	char name[32];
	int ret = 0;
	int i=0;
	/* initialize the GPIO spinlock */
	spin_lock_init(&gpio_lock);

	/* clear the entries */
	memset(gpio_entries, 0, sizeof(gpio_entries));

	/* create GPIO directory */
	DPRINTK("creating entry [%s]\n",GPIO_DIR);
	gpio_dir = proc_mkdir(GPIO_DIR, parent);
	if (gpio_dir)
	{
		/* Create GPIO Controls */
		for (port = 0; gpio_count[port] && ret==0; port++)
		{
			//for (line=0; line<gpio_count[port] && ret==0; line++)
			
			for(i=0; i<NO_OF_GPIO_OPEN;i++)//marco, create proc that we define at the beginning of the code only
			{
				line=g_GPIO_USED[i];
			
				sprintf(name, "%s_p%c_%d", GPIO_OUTEN, port+'a', line);
				DPRINTK("creating entry [%s]\n",name);
				gpio_entries[port][i].control = create_proc_entry(name, 0644, gpio_dir);
				if (gpio_entries[port][i].control)
				{

					gpio_entries[port][i].control->data		= &gpio_entries[port][i];
					gpio_entries[port][i].control->read_proc	= proc_read_outen;
					gpio_entries[port][i].control->write_proc= proc_write_outen;
					gpio_entries[port][i].control->owner		= THIS_MODULE;
					gpio_entries[port][i].port				= port;
					gpio_entries[port][i].line				= line;
					gpio_entries[port][i].outen				= GPIO_GET_OUTEN(port, line);
				}
				else
				{
					printk("%s: unable to create proc entry : %s !\n",__FUNCTION__, name);
					ret = -ENOMEM;
				}
			}
		}
		if (ret) gpio_exit(parent);
		
		ret = gpio_interrupt_init(gpio_dir);
		
		if (ret) gpio_exit(parent);
		
		return ret;
	}
	else
	{
		printk("%s: proc_mkdir return NULL!\n",__FUNCTION__);
		return -ENOMEM;
	}
}


static struct proc_dir_entry * root = NULL;

static int __init nas_gpio_init(void)
{
	printk("nas_gpio Access Init.\n");

	/* create directory */
	DPRINTK("creating entry [%s]\n", MODULE_NAME);
	root = proc_mkdir(MODULE_NAME, NULL);
	if (root == NULL)
	{
		printk("%s: proc_mkdir return NULL!\n",__FUNCTION__);
		return -ENOMEM;
	}
	
	gpio_init(root);
	
	return 0;
}
static void __exit nas_gpio_exit(void)
{
	printk("nas_gpio Access Exit.\n");

	
	gpio_exit(root);

	if (root)
	{
		DPRINTK("Removing entry [%s]\n",MODULE_NAME);
		remove_proc_entry(MODULE_NAME, NULL);
		root = NULL;
	}
}


module_init(nas_gpio_init);
module_exit(nas_gpio_exit);

MODULE_AUTHOR("David Hsieh <david_hsieh@alphanetworks.com>)");
MODULE_DESCRIPTION("Access driver for WRG-N15C");
MODULE_LICENSE("GPL");
