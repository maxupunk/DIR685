#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/string.h>
#include <linux/timer.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/i2c.h>
#include <linux/workqueue.h>
#include <linux/kfifo.h>
#include <linux/err.h>
#include <linux/poll.h>
#include <linux/cdev.h>
#include <linux/devfs_fs_kernel.h>
#include <asm/irq.h>
#include <linux/signal.h>
#include <linux/interrupt.h>
#include <asm/semaphore.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/proc_fs.h> 
//#include "venus_gpio.h"
#include "i2c_alpha.h"
//#define DEBUG_I2C 0x1

//#define MIS_PSELL       ((volatile unsigned int *)0xb801b004)
//#define MIS_PSELH       ((volatile unsigned int *)0xb801b000)
extern int pkbd_dev_init(void);
extern void key_handler(unsigned int key);
//storm related
#include <linux/config.h>
#include <linux/types.h>
#include <linux/miscdevice.h>
#include <linux/ioport.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>
#include <asm/hardware.h>
#include <asm/io.h>
#include <asm/arch/sl2312.h>
#include <asm/arch/irqs.h>
#include <asm/arch/gemini_gpio.h> 
#include <asm/arch/sl2312.h>

#define INTERRUPT_MODE 1 //marco use interrupt mode or polling mode
#define GPIO_CLK	6
#define GPIO_SDA	5

#define GPIO_I2C_INTERRUPT_PIN		17
#define GPIO_I2C_INTERRUPT			(1<<GPIO_I2C_INTERRUPT_PIN)
#define GPIO_LEVEL_TRIG		1
#define GPIO_EDGE_TRIG		0
#define GPIO_LOW_ACTIVE		1
#define GPIO_HIGH_ACTIVE	0
#define GPIO_FALL_ACTIVE	1
#define GPIO_RISE_ACTIVE	0
#define GPIO_BOTH_EDGE		1
#define GPIO_SINGLE_EDGE	0 


#define GPIO_SDA_BIT				(1<<GPIO_SDA)	/* GPIO0 bit-5 */
#define GPIO_SCL_BIT				(1<<GPIO_CLK)	/* GPIO0 bit-6 */

enum GPIO_REG
{
    GPIO_DATA_OUT   = 0x00,
    GPIO_DATA_IN    = 0x04,
    GPIO_PIN_DIR    = 0x08,
    GPIO_BY_PASS    = 0x0c,
    GPIO_DATA_SET   = 0x10,
    GPIO_DATA_CLEAR = 0x14
};


#define MIS_GP0DIR                  (IO_ADDRESS(SL2312_GPIO_BASE)+GPIO_PIN_DIR)
#define MIS_GP1DIR                  (IO_ADDRESS(SL2312_GPIO_BASE1)+GPIO_PIN_DIR)


#define MIS_GP0DATI                 (IO_ADDRESS(SL2312_GPIO_BASE)+GPIO_DATA_IN)
#define MIS_GP1DATI                 (IO_ADDRESS(SL2312_GPIO_BASE1)+GPIO_DATA_IN)

#define MIS_GP0DATO                 (IO_ADDRESS(SL2312_GPIO_BASE)+GPIO_DATA_OUT)
#define MIS_GP1DATO                 (IO_ADDRESS(SL2312_GPIO_BASE1)+GPIO_DATA_OUT)

#ifndef INTERRUPT_MODE	
static struct timer_list key_autorepeat_timer ;
#endif

static void interrupt_handler(void);

static void gpio_handle(void) 
{
	
	interrupt_handler();
#ifndef INTERRUPT_MODE	
	printk("polling \n");
	key_autorepeat_timer.expires=jiffies+50;
	key_autorepeat_timer.function=&gpio_handle;
	mod_timer(&key_autorepeat_timer,jiffies + 50);
#endif	
		
}
void register_interrupt(void)
{
	printk(KERN_EMERG"test_interrupt interrupt\n");	
	pkbd_dev_init();		
#ifdef INTERRUPT_MODE	
	request_gpio_irq(GPIO_I2C_INTERRUPT_PIN,gpio_handle,GPIO_EDGE_TRIG,GPIO_FALL_ACTIVE,GPIO_SINGLE_EDGE); 		
#endif		
}


//touch pad io releated
unsigned int tp_reg_read(void)
{
	unsigned char buf[6];
	int i = 0;
	int rc;
	
	memset(buf , 0x0, 0x6);
//	rc = I2C_Read_NoSubAddress(0x40, buf, 6); 
	rc = I2C_Read_NoSubAddress(0x4D, buf, 6); 
//	printk("\nbuf[0] = 0x%x; buf[1] = 0x%x; buf[3] = 0x%x; buf[4] = 0x%x; buf[5] = 0x%x**",buf[0], buf[1], buf[3], buf[4], buf[5] );
	
//marco	i =(int)(buf[3] << 8 | buf[4]); 
	i =(int)(buf[4] << 8 | buf[5]); 
	if (rc < 0)
		return -1;
	else
		return i;
}

static void interrupt_handler(void)
{
    unsigned int key, i, tmp = 0;
	
	key = tp_reg_read(); 
	if (key == 0xfe)//error read -1
		return;

	for(i = 0; i < 16; i++){
		if(key & (0x1 << i)){
			tmp++;
			if(tmp > 1)	return;
		}
	}

//	unsigned char data[]={0xA7,0x40};
//	unsigned char read_data[5];
//	int err=0;
//	printk("**key  = %x\n", key);

	key_handler(key);
		
}
int touchpad_data_read_proc(char *buffer, char **buffer_location,off_t offset, int buffer_length, int *eof, void *data)
{
	int ret;
	if (offset > 0) {
		/* we have finished to read, return 0 */
		ret  = 0;
	} else {
		unsigned char buf[6];
		int rc;
	
		memset(buf , 0x0, 0x6);
		rc = I2C_Read_NoSubAddress(0x4D, buf, 6);
		if(rc < 0)
			ret = sprintf(buffer,"fail");
		else
			ret = sprintf(buffer,"%02x %02x %02x %02x %02x %02x",buf[0], buf[1],buf[2], buf[3], buf[4], buf[5] );
	}
	return ret;
}

/////////////////////////////////////////////////////////

#define I2C_ALPHA_DEVICE_FILE	"i2c_alpha"
#define I2C_ALPHA_MAJOR 100
#define I2C_ALPHA_MINOR_RP 1

MODULE_AUTHOR("Steven Wang <Steven_Wang@alphanetworks.com>");
MODULE_DESCRIPTION("I2C protocol implement by GPIO");
MODULE_LICENSE("GPL");

static DECLARE_MUTEX(lock);
static struct cdev *i2c_alpha_cdev = NULL;
static int i2c_enable = 1;

void gpio_setdirection(int gpio, int dir)
{
	unsigned int regValue, bitOffset;
	
	if(gpio <= 31) {
		bitOffset = gpio;
		regValue = readl(MIS_GP0DIR);
		
		if(dir)
			// Set Direction to Output
			regValue = regValue | (0x01 << bitOffset);
		else
			// Set Direction to Input
			regValue = regValue & (~(0x01 << bitOffset));
		writel(regValue, MIS_GP0DIR);

	} else if(gpio > 31 && gpio <=35) {
		bitOffset = gpio - 32;
		regValue = readl(MIS_GP1DIR);
		if(dir)
			// Set Direction to Output
			regValue = regValue | (0x01 << bitOffset);
		else
			// Set Direction to Input
			regValue = regValue & (~(0x01 << bitOffset));
		writel(regValue, MIS_GP1DIR);
	} else
		printk("No such GPIO pin!\n");
}

int gpio_read(int gpio)
{
	unsigned int regValue, bitOffset;

	if(gpio <= 31) {
		bitOffset = gpio;
		regValue = readl(MIS_GP0DATI); 
	//	printk("regValue %x MIS_GP0DATI %x %x",regValue,MIS_GP0DATI,regValue & (0x01 << bitOffset));
                if(regValue & (0x01 << bitOffset))
                        return 1;
                else
                        return 0;

	} else if(gpio > 31 && gpio <=41) {
		bitOffset = gpio - 32;
		regValue = readl(MIS_GP1DATI); 
                if(regValue & (0x01 << bitOffset))
                        return 1;
                else
                        return 0;
	} else
		printk("No such GPIO pin!\n");

	return 0;
}

void gpio_write(int gpio, int data)
{
	unsigned int regValue, bitOffset;
       
	if(gpio <= 31) {
		bitOffset = gpio;
		regValue = readl(MIS_GP0DATO);
		if(data)
			// Set GPIO high
			regValue = regValue | (0x01 << bitOffset);
		else
			// Set GPIO low 
			regValue = regValue & (~(0x01 << bitOffset));
		writel(regValue, MIS_GP0DATO);
	} else if(gpio > 31 && gpio <=41) {
		bitOffset = gpio - 32;
		regValue = readl(MIS_GP1DATO);
		if(data)
			// Set GPIO high
			regValue = regValue | (0x01 << bitOffset);
		else
			// Set GPIO low 
			regValue = regValue & (~(0x01 << bitOffset));
		writel(regValue, MIS_GP1DATO);
	} else
		printk("No such GPIO pin!\n");
}

static int I2C_Clock(int clock)
{
	gpio_setdirection(GPIO_CLK, 1);
	if (clock) {  // read from clock line, wait until high
		gpio_write(GPIO_CLK, 1);
	} else {  // write low to clock line
		gpio_write(GPIO_CLK, 0);
	}
	udelay(12);
	return 0;
}

static int I2C_Data(int data)
{
	gpio_setdirection(GPIO_SDA, 1);
	if (data) {  // read from data line, wait until high
		gpio_write(GPIO_SDA, 1);
	} else {  // write low to data line
		gpio_write(GPIO_SDA, 0);
	}
	udelay(10);

	return 0;
}

// --- bit level functions
// all operations, except Stop, end with Clock==low, blocking the bus for other masters

static int I2C_WrBit(int data)
{
// send one bit
//        _
// Ck   _| |_
//       ___
// Data X___X
	int err;
	
	if ((err = I2C_Data(data)) < 0) return -1;
	if ((err = I2C_Clock(1)) < 0) return -1;
	if ((err = I2C_Clock(0)) < 0) return -1;
	
	return 0;
}

static int I2C_RdBit(int *data)
{
// read one bit
//        _
// Ck   _| |_
//       ___
// Data X___X
	int err;
	// Read data
	gpio_setdirection(GPIO_SDA, 0);
		
	if ((err = I2C_Clock(1)) < 0) return -1;
	udelay(2);
	*data = gpio_read(GPIO_SDA); 
	udelay(4); /*joey added it*/
	
	if ((err = I2C_Clock(0)) < 0) return -1;
	return 0;
}

static int I2C_Start(void)
{
// Data goes high-to-low while Ck is high
//        ___
// Ck   _|   |_
//      ___
// Data    |___
	int err;
	
	if (!i2c_enable)
		return -1;
	// start sequence
	if ((err = I2C_Data(1)) < 0) return -1;
	if ((err = I2C_Clock(1)) < 0) return -1;
	if ((err = I2C_Data(0)) < 0) return -1;
	if ((err = I2C_Clock(0)) < 0) return -1;
	
	return 0;
}

static int I2C_Stop(void)
{
// Data goes low-to-high while Ck is high
//        __
// Ck   _|
//         _
// Data __|
	int err;
	
	// stop sequence
	if ((err = I2C_Data(0)) < 0) return -1;
	if ((err = I2C_Clock(1)) < 0) return -1;
	if ((err = I2C_Clock(1)) < 0) return -1;
	if ((err = I2C_Data(1)) < 0) return -1;
	
	return 0;
}

static int I2C_SendNack(void)
{
// Not-Acknowledge from master
//        _
// Ck   _| |_
//      _____
// Data 
	return I2C_WrBit(1);
}

static int I2C_SendAck(void)
{
// Acknowledge from master
//        _
// Ck   _| |_
//      
// Data _____
	return I2C_WrBit(0);
}

static int I2C_WaitAck(void)
{
//        __
// Ck   _|  |_
//      
// Data XX____
	int err;
	unsigned int lastRecvMs;
	
	
	gpio_setdirection(GPIO_SDA, 0);
		
	if ((err = I2C_Clock(1)) < 0) return -1;
	udelay(6);

	lastRecvMs = jiffies_to_msecs(jiffies);

	
	while(gpio_read(GPIO_SDA)&1){
	//printk("msecs %d lastRecvMs %d jif_to_ms-lastRecvMs %d ",jiffies_to_msecs(jiffies),lastRecvMs,jiffies_to_msecs(jiffies) - lastRecvMs);	
		if((jiffies_to_msecs(jiffies) - lastRecvMs) > 0) {
			// timeout
#ifdef DEBUG_I2C
 			printk("No ACK ");
#endif
			return -1;
		}
	}
	if ((err = I2C_Clock(0)) < 0) return -1;

	return 0;
}

// --- byte level functions

static int I2C_WrByte(unsigned char ByteIn)
{
//        _   _   _   _   _   _   _   _
// Ck   _| |_| |_| |_| |_| |_| |_| |_| |_
//       ___ ___ ___ ___ ___ ___ ___ ___ 
// Data X___X___X___X___X___X___X___X___
	unsigned int i;
	int err;
	
	for (i = 0; i < 8; i++) {
		if ((err = I2C_WrBit(ByteIn & 0x80)) < 0) return -1;
		ByteIn <<= 1;
	}

	return 0;
}

static int I2C_RdByte(unsigned char *data)
{
//        _   _   _   _   _   _   _   _
// Ck   _| |_| |_| |_| |_| |_| |_| |_| |_
//       ___ ___ ___ ___ ___ ___ ___ ___ 
// Data X___X___X___X___X___X___X___X___
	unsigned int i;
	int bit;
	int err;
	
	for (i = 0; i < 8; i++) {
		if ((err = I2C_RdBit(&bit)) < 0) return -1;
		*data = (*data << 1) | (bit ? 1 : 0);
	}
	udelay(20);
#ifdef DEBUG_I2C
	printk("data[%x]\n", *data);
#endif
	return 0;
}

int I2C_Write(unsigned char SlaveAddress, unsigned char SubAddress, unsigned char *data, unsigned int n)
{
	unsigned int i;
	int err;

	down(&lock);
        // Start,WrByte(WrAddress),WaitAck,WrByte(SubAddress),WaitAck,
        if ((err = I2C_Start()) < 0) {up(&lock); return -1;}
        if ((err = I2C_WrByte(SlaveAddress|0x0)) < 0) {up(&lock); return -1;}
        if ((err = I2C_WaitAck()) < 0) {up(&lock); return -1;}
        if ((err = I2C_WrByte(SubAddress)) < 0) {up(&lock); return -1;}
        if ((err = I2C_WaitAck()) < 0) {up(&lock); return -1;}

        // if not last byte repeat(WrByte,WaitAck),Stop
        for (i = 0; i < n; i++) {
                if ((err = I2C_WrByte(data[i])) < 0) {up(&lock); return -1;}
                if ((err = I2C_WaitAck()) < 0) {up(&lock); return -1;}
        }
        if ((err = I2C_Stop()) < 0) {up(&lock); return -1;}
	up(&lock);
        return 0;
}

int I2C_Read(unsigned char SlaveAddress, unsigned char SubAddress, unsigned char *data, unsigned int n)
{
	unsigned int i;
	int err;
	
	down(&lock);
	if (n < 1) {up(&lock); return -1;}
	
	// Start,WrByte(WrAddress),WaitAck,WrByte(SubAddress),WaitAck,
	if ((err = I2C_Start()) < 0) {up(&lock); return -1;}
	if ((err = I2C_WrByte(SlaveAddress|0x0)) < 0) {up(&lock); return -1;}
	if ((err = I2C_WaitAck()) < 0) {up(&lock); return -1;}
	if ((err = I2C_WrByte(SubAddress)) < 0) {up(&lock); return -1;}
	if ((err = I2C_WaitAck()) < 0) {up(&lock); return -1;}
	
	// Start,WrByte(RdAddress),WaitAck,
	if ((err = I2C_Start()) < 0) {up(&lock); return -1;}
	if ((err = I2C_WrByte(SlaveAddress|0x1)) < 0) {up(&lock); return -1;}
	if ((err = I2C_WaitAck()) < 0) {up(&lock); return -1;}
	
	// if not last byte repeat(RdByte,Ack),RdByte(last),Nack,Stop
	for (i = 0; i < n; i++) {
		if ((err = I2C_RdByte(&(data[i]))) < 0) {up(&lock); return -1;}
		if (i == (n - 1)) {
			if ((err = I2C_SendNack()) < 0) {up(&lock); return -1;}
		} else {
			if ((err = I2C_SendAck()) < 0) {up(&lock); return -1;}
		}
	}
	
	if ((err = I2C_Stop()) < 0) {up(&lock); return -1;}
	up(&lock);
	
	return 0;
}

int I2C_Write_NoSubAddress(unsigned char SlaveAddress, unsigned char *data, unsigned int n)
{
	unsigned int i;
	int err;
	
	down(&lock);
	if ((err = I2C_Start()) < 0) {up(&lock); return -1;}
	if ((err = I2C_WrByte(SlaveAddress|0x0)) < 0) {up(&lock); return -1;}
	if ((err = I2C_WaitAck()) < 0) {up(&lock); return -1;}
	
	for (i = 0; i < n; i++) {
		if ((err = I2C_WrByte(data[i])) < 0) {up(&lock); return -1;}
		if ((err = I2C_WaitAck()) < 0) {up(&lock); return -1;}
	}
	if ((err = I2C_Stop()) < 0) {up(&lock); return -1;}
	up(&lock);
	
	return 0;
}

int I2C_Read_NoSubAddress(unsigned char SlaveAddress, unsigned char *data, unsigned int n)
{
	unsigned int i;
	int err;

	down(&lock);
	if (n < 1) return -1;
			
	if ((err = I2C_Start()) < 0) {up(&lock); return -1;}
	if ((err = I2C_WrByte(SlaveAddress|0x1)) < 0) {up(&lock); return -1;}
	
//    udelay(80); 
	if ((err = I2C_WaitAck()) < 0) {up(&lock); return -1;}
    udelay(20);    
	
	for (i = 0; i < n; i++) {
		if ((err = I2C_RdByte(&(data[i]))) < 0) {up(&lock); return -1;}
		if (i == (n - 1)) {
			if ((err = I2C_SendNack()) < 0) {up(&lock); return -1;}
		} else {
			if ((err = I2C_SendAck()) < 0) {up(&lock); return -1;}
		}
//		udelay(40);
		udelay(10);
	}
	if ((err = I2C_Stop()) < 0) {up(&lock); return -1;}
	up(&lock);
	
	return 0;
}

int I2C_Device_Detect(unsigned char SlaveAddress)
{
	int err;

	// Start,WrByte(WrAddress),WaitAck,WrByte(SubAddress),WaitAck,
	if ((err = I2C_Start()) < 0){ return -1;}
	if ((err = I2C_WrByte(SlaveAddress|0x0)) < 0) { return -1;}
	if ((err = I2C_WaitAck()) < 0){ return -1;}
	if ((err = I2C_Stop()) < 0){ return -1;}

	return 0;
}

static int i2c_alpha_open(struct inode *inode, struct file *filp)
{
	return 0;
}

static int i2c_alpha_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	int err = 0;
	int retval = 0;
	struct i2c alpha_i2c;

	if (_IOC_TYPE(cmd) != I2C_ALPHA_IOC_MAGIC) return -ENOTTY;
	if (_IOC_NR(cmd) > I2C_ALPHA_IOC_MAXNR) return -ENOTTY;

	if (_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err =  !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));

	if (err) 
		return -EFAULT;

	if (!capable (CAP_SYS_ADMIN))
		return -EPERM;

	switch(cmd) {
		case I2C_ALPHA_WRITE:
			if (copy_from_user(&alpha_i2c, (void *)arg, sizeof(alpha_i2c))) { 
				retval = -EFAULT;
				break;
			}
#ifdef DEBUG_I2C
{
			int i;
			printk("%x %x ", alpha_i2c.SlaveAddress, alpha_i2c.SubAddress);
			for (i = 0; i < alpha_i2c.n; i++) {
				printk("%x ", alpha_i2c.Data[i]);
			}
			printk("\n");
}
#endif // DEBUG_I2C
			if ((err = I2C_Write(alpha_i2c.SlaveAddress, alpha_i2c.SubAddress, 
				alpha_i2c.Data, alpha_i2c.n)) < 0) retval = -EFAULT;
			break;
		case I2C_ALPHA_READ:
			if (copy_from_user(&alpha_i2c, (void *)arg, sizeof(alpha_i2c))) { 
				retval = -EFAULT;
				break;
			}
			if ((err = I2C_Read(alpha_i2c.SlaveAddress, alpha_i2c.SubAddress, 
				alpha_i2c.Data, alpha_i2c.n)) < 0) retval = -EFAULT;
			if (copy_to_user((void *)arg, &alpha_i2c, sizeof(alpha_i2c))) { 
				retval = -EFAULT;
				break;
			}
			break;
		case I2C_ALPHA_WRITE_NO_SUBADDR:
			if (copy_from_user(&alpha_i2c, (void *)arg, sizeof(alpha_i2c))) { 
				retval = -EFAULT;
				break;
			}
			if ((err = I2C_Write_NoSubAddress(alpha_i2c.SlaveAddress, alpha_i2c.Data, 
				alpha_i2c.n)) < 0) retval = -EFAULT;
			break;
		case I2C_ALPHA_READ_NO_SUBADDR:
			if (copy_from_user(&alpha_i2c, (void *)arg, sizeof(alpha_i2c))) { 
				retval = -EFAULT;
				break;
			}
			if ((err = I2C_Read_NoSubAddress(alpha_i2c.SlaveAddress, alpha_i2c.Data, 
				alpha_i2c.n)) < 0) retval = -EFAULT;
			if (copy_to_user((void *)arg, &alpha_i2c, sizeof(alpha_i2c))) { 
				retval = -EFAULT;
				break;
			}
			break;
		case I2C_ALPHA_ENABLE:
			
			i2c_enable = 1;
			break;
		case I2C_ALPHA_DISABLE:
			
			i2c_enable = 0;
			gpio_setdirection(GPIO_CLK, 0);
			gpio_setdirection(GPIO_SDA, 0);
			break;
		default:
			retval = -ENOIOCTLCMD;
			break;
	}

	return retval;
}
int create_proc(void)
{
//marco , add proc directory to set the brightness of monitor
	struct proc_dir_entry * i2c_proc = NULL;   
	struct proc_dir_entry * lcd_proc = NULL;   
	struct proc_dir_entry * touchpad_proc = NULL;   
	extern int lcd_write_proc(struct file *file, const char __user *buffer, unsigned long count, void *read_data) ;
	extern int i2c_write_proc(struct file *file, const char __user *buffer, unsigned long count, void *data)  ;
    i2c_proc = create_proc_entry("brightness", 0, NULL);     
    lcd_proc = create_proc_entry("lcd", 0, NULL);     
    touchpad_proc = create_proc_entry("touchpad", 0, NULL);
    
    if(i2c_proc) {         
      i2c_proc->write_proc = (write_proc_t *)i2c_write_proc;   
    }  
    else {  
      printk ("Can't create proc entry for pkbd driver.\n");       
      return -EBUSY;    
    }
    if(lcd_proc) {         
      lcd_proc->write_proc = (write_proc_t *)lcd_write_proc;   
    }  
    else {  
      printk ("Can't create proc entry for pkbd driver.\n");       
      return -EBUSY;    
    }
    
    if(touchpad_proc) {         
      touchpad_proc->read_proc = (read_proc_t *)touchpad_data_read_proc;   
    }  
    else {  
      printk ("Can't create proc entry for pkbd driver.\n");       
      return -EBUSY;    
    }    
    return 0;
}

static struct file_operations i2c_alpha_fops = {
	.owner	= THIS_MODULE,
	.open	= i2c_alpha_open,
	.ioctl	= i2c_alpha_ioctl,
};

 int __init i2c_alpha_init(void)
{
	/* Set I2C_CLK, I2C_SDA to be GPIO */
	/* Set [8:9] = 0x0, [10:11] = 0x0; */
//	writel((readl(MIS_PSELL) & 0xfffff0ff), MIS_PSELL);
	/* Set TX/RX_LED, LINK_LED to be GPIO */
	/* Set [16:17] = 0x2, [20:21] = 0x0; */
	//writel((readl(MIS_PSELL) & 0xffceffff), MIS_PSELL);
	//writel((readl(MIS_PSELL) | 0x00020000), MIS_PSELL);	
	register_interrupt();
#ifdef DEBUG_I2C
{
	int i;
	printk("Found I2C devices:");
	for(i = 0x0; i <= 0xff; i++) {
		if(!I2C_Device_Detect(i))
			printk("[%x] \n", i);
		
	}
}
#endif
	create_proc();
	/* Char Device Registration */
	i2c_alpha_cdev = cdev_alloc();
	i2c_alpha_cdev->ops = &i2c_alpha_fops;

	if(cdev_add(i2c_alpha_cdev, MKDEV(I2C_ALPHA_MAJOR, I2C_ALPHA_MINOR_RP), 1))
		printk("I2C-Alpha: can't add character device for i2c_alpha");

	/* use devfs to create device file */
	devfs_mk_cdev(MKDEV(I2C_ALPHA_MAJOR, I2C_ALPHA_MINOR_RP), S_IFCHR|S_IRUSR|S_IWUSR, I2C_ALPHA_DEVICE_FILE);

#ifndef INTERRUPT_MODE	
	init_timer(&key_autorepeat_timer);
	key_autorepeat_timer.expires=jiffies+50;
	key_autorepeat_timer.function=&gpio_handle;
	add_timer(&key_autorepeat_timer);
#endif	
	return 0;
}

static void __exit i2c_alpha_exit(void)
{
        /* remove device file by devfs */
        devfs_remove(I2C_ALPHA_DEVICE_FILE);

        /* Release Character Device Driver */
        cdev_del(i2c_alpha_cdev);
        
        free_gpio_irq(GPIO_I2C_INTERRUPT_PIN);
#ifndef INTERRUPT_MODE	        
 		del_timer(&key_autorepeat_timer);
#endif 		
		remove_proc_entry("brightness", NULL); 
                remove_proc_entry("lcd", NULL);  
}

EXPORT_SYMBOL(gpio_setdirection);
EXPORT_SYMBOL(gpio_read);
EXPORT_SYMBOL(gpio_write);
EXPORT_SYMBOL(I2C_Write);
EXPORT_SYMBOL(I2C_Read);
EXPORT_SYMBOL(I2C_Write_NoSubAddress);
EXPORT_SYMBOL(I2C_Read_NoSubAddress);
EXPORT_SYMBOL(I2C_Device_Detect);

module_init(i2c_alpha_init);
module_exit(i2c_alpha_exit);
