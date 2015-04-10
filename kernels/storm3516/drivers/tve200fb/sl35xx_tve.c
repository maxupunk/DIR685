#include <asm/hardware.h>
#include <asm/io.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include "debug.h"
#include <asm/arch/sl2312.h>

#define TVE_BASE_ADDR       (IO_ADDRESS(SL2312_TVE_BASE))
#define GPIO_BASE_ADDR      (IO_ADDRESS(SL2312_GPIO_BASE))
#define GLOBAL_BASE_ADDR    (IO_ADDRESS(SL2312_GLOBAL_BASE))

#define GPIO_BASE_ADDR1  	(IO_ADDRESS(SL2312_GPIO_BASE1))

/***************************************/
/* define GPIO pin for SPI protocol    */
/***************************************/
#define GPIO_PIN_EECS	 20		/*   EECS: GPIO0[20]   */
#define GPIO_PIN_MOSI	  7     /*   EEDO: GPIO1[7]   */
#define GPIO_PIN_MISO	  8     /*   EEDI: GPIO1[8]   */
#define GPIO_PIN_EECK	  5     /*   EECK: GPIO1[5]   */

#define GPIO_EECS	     (1<<GPIO_PIN_EECS)		/*   EECS: GPIO0[20]   */
#define GPIO_MOSI	     (1<<GPIO_PIN_MOSI)     /*   EEDO: GPIO1[7]   */
#define GPIO_MISO	     (1<<GPIO_PIN_MISO)     /*   EEDI: GPIO1[8]   */
#define GPIO_EECK	     (1<<GPIO_PIN_EECK)     /*   EECK: GPIO1[5]   */

/*****************************************
* SPI protocol 
******************************************/
#define SPI_ADD_LEN	     7			// bits of Address
#define SPI_DAT_LEN	     8			// bits of Data

enum GPIO_REG
{
    GPIO_DATA_OUT   = 0x00,
    GPIO_DATA_IN    = 0x04,
    GPIO_PIN_DIR    = 0x08,
    GPIO_BY_PASS    = 0x0c,
    GPIO_DATA_SET   = 0x10,
    GPIO_DATA_CLEAR = 0x14,
};



#define CIF		0
#define VGA		1
#define D1		2
#define YUV		3

//#define	BUF_NO		2
//static unsigned char *cif_buf[BUF_NO];	/* max. frame size->RGB888,351x240 -> 351*240*4 =  337920 bytes */
//static unsigned char *d1_buf[BUF_NO];	/* max. frame size->RGB888,720x480 -> 720*480*4 = 1382400 bytes */
//static unsigned char *vga_buf[BUF_NO];	/* max. frame size->RGB888,640x480 -> 640*480*4 = 1228800 bytes */
//static unsigned char *y_buf[BUF_NO];	/* max. frame size->YUV420(Y) -> 720x480* 1  = 345600 bytes */
//static unsigned char *u_buf[BUF_NO];	/* max. frame size->YUV420(U) -> 720x480*1/2 = 172800 bytes */
//static unsigned char *v_buf[BUF_NO];	/* max. frame size->YUV420(V) -> 720x480*1/2 = 172800 bytes */
#if 0 //marco, this is not used in our driver, but the frame biffer will affect our kenel when built-in
static unsigned int	frame_type=0;
static unsigned char frame_buffer[1536000];


void cs4954_init(void);
void ILI9322_init(void);

static int gemini_tve_open(struct inode *inode, struct file *file)
{
//	unsigned int 	value;

	printk("%s......\n",__func__);	
	writel(0x3f00,GPIO_BASE_ADDR+0x0c);
	
	/* enable VGA PADs function */
//	value = readl(GLOBAL_BASE_ADDR+0x30);
//	value = value | 0x200;
//	writel(value,GLOBAL_BASE_ADDR+0x30);

//	cs4954_init();
	ILI9322_init();
	return 0;
}

static ssize_t gemini_tve_write(struct file *file_p, const char *buf, size_t count, loff_t *ppos)
{
	unsigned int	i,value;
	
	printk("%s......%x\n",__func__,buf);	
	memcpy(frame_buffer,buf,count);
	writel((unsigned int)__pa(frame_buffer),TVE_BASE_ADDR + 0x00);
	
	for (i=0; i<9; i++)
	{
		value = readl(TVE_BASE_ADDR + i*4);
		printk("address=%x value=%x \n",i*4,value);
	}	
	return 0;
}

static int gemini_tve_ioctl(struct inode *inode, struct file *file,unsigned int cmd, unsigned long arg)
{
	printk("%s......\n",__func__);	
	switch(cmd) 
	{
    	case 0:		/* CIF */
			writel((unsigned int)0x1301820b,TVE_BASE_ADDR + 0x18);
			break;
		
		case 1:		/* VGA */
			writel((unsigned int)0x13018603,TVE_BASE_ADDR + 0x18);
			break;
				
		case 2:		/* D1 */
			writel((unsigned int)0x13010a03,TVE_BASE_ADDR + 0x18);
			break;
				
		case 3:		/* YUV */
//			writel((unsigned int)0x2008000,TVE_BASE_ADDR + 0x00);
//			writel((unsigned int)0x205c600,TVE_BASE_ADDR + 0x04);
//			writel((unsigned int)0x2071780,TVE_BASE_ADDR + 0x08);
			writel((unsigned int)0x93010a01,TVE_BASE_ADDR + 0x18);
			break;
			
		default:
			break;
	}
	return (0);			
}

static struct file_operations gemini_tve_fops = {
	.owner	=	THIS_MODULE,
	.ioctl	=	gemini_tve_ioctl,
	.open	=	gemini_tve_open,
	.release=	NULL,
	.write	=	gemini_tve_write,
};

#ifndef STORLINK_TVE
#define STORLINK_TVE	243		/* Documents/devices.txt suggest to use 240~255 for local driver!! */
#endif

static struct miscdevice gemini_tve_miscdev =
{
	.minor 	=	STORLINK_TVE,
	.name	=	"TV_Encoder",
	.fops 	= 	&gemini_tve_fops,
};

int __init sl35xx_tve_init(void)
{

	printk("Gemini TVE Driver Initialization...\n");
	
	misc_register(&gemini_tve_miscdev);
		
	return 0;
}	

void __exit sl35xx_tve_exit(void)
{

}

#ifdef SL351X_TVE
module_init(sl35xx_tve_init);
module_exit(sl35xx_tve_exit);

MODULE_AUTHOR("Amos Lee <amos_lee@storlinksemi.com>");
MODULE_DESCRIPTION("Storlink TVE driver");
MODULE_LICENSE("GPL");
#endif

#define GPIO_SDA_PIN				14
#define GPIO_SCL_PIN				15
#define GPIO_SDA					(1<<GPIO_SDA_PIN)	
#define GPIO_SCL					(1<<GPIO_SCL_PIN)	

/*================================================================*/
#define CLOCK_LOW_TIME              8
#define CLOCK_HIGH_TIME             8
#define START_CONDITION_HOLD_TIME   8
#define STOP_CONDITION_HOLD_TIME    8
#define I2C_CLOCK_HIGH              1
#define I2C_CLOCK_LOW               0
#define I2C_DATA_HIGH               1
#define I2C_DATA_LOW                0


//#define readl(addr)         (*(unsigned int *)addr)
//#define writel(val,addr)    (*(unsigned int *)addr = val)

static void i2c_clk(char x)
{
    unsigned int addr;
    unsigned int value;

    addr = GPIO_BASE_ADDR + GPIO_PIN_DIR;
    if(x)
    {
    	value = readl(addr) & ~GPIO_SCL; /* set SCL Pin to input */
   		writel(value,addr);
    }
    else
    {
    	value = readl(addr) | GPIO_SCL; /* set SCL Pin to output */
   		writel(value,addr);
    }   
}

static void i2c_data(char x)
{
    unsigned int addr;
    unsigned int value;

    addr = GPIO_BASE_ADDR + GPIO_PIN_DIR;
    if(x)
    {
    	value = readl(addr) & ~GPIO_SDA; /* set SDA Pin to input */
    	writel(value,addr);
    }
    else
    {
      	value = readl(addr) | GPIO_SDA; /* set SDA Pin to output */
    	writel(value,addr);
    }       
}

static void i2c_delay(unsigned int delay)
{
	unsigned int	i;
	
	for (i=0;i<delay;i++)
	{
		i = i * (i + 3);
	}	   
}

static int i2c_getbit(void)
{
    unsigned int addr;
    unsigned int value;

    addr = GPIO_BASE_ADDR + GPIO_PIN_DIR;
    value = readl(addr) & ~GPIO_SDA; /* set SDA Pin to input */
    writel(value,addr);

    addr = (unsigned int)(GPIO_BASE_ADDR + GPIO_DATA_IN);
    value = readl(addr);
    value = (value & GPIO_SDA) >> GPIO_SDA_PIN;
	return value;
}
           
/* generate i2c start condition */
static void i2c_start(void)
{
	/* SCL=1 SDA=1 */
	i2c_data(I2C_DATA_HIGH);
	i2c_clk(I2C_CLOCK_HIGH);
	i2c_delay(CLOCK_HIGH_TIME);
	
	/* SCL=1 SDA=0 */
	i2c_data(I2C_DATA_LOW);
	i2c_delay(START_CONDITION_HOLD_TIME);

	/* SCL=0 SDA=0 */
	i2c_clk(I2C_CLOCK_LOW);
	i2c_delay(CLOCK_LOW_TIME);
}

/* generate i2c stop condition */
static void i2c_stop(void)
{
	/* SCL=0 SDA=0 */
	i2c_clk(I2C_CLOCK_LOW);
	i2c_data(I2C_DATA_LOW);
	i2c_delay(CLOCK_LOW_TIME*2);
	
	/* SCL=1 SDA=0 */
	i2c_clk(I2C_CLOCK_HIGH);
	i2c_delay(CLOCK_HIGH_TIME*2);
	
	/* SCL=1 SDA=1 */
	i2c_data(I2C_DATA_HIGH);
	i2c_delay(STOP_CONDITION_HOLD_TIME);
}

/* write a byte to the i2c interface */
static void i2c_outbyte(unsigned char x)
{
	int i;
	
	for (i = 0; i < 8; i++)
	{
		if (x & 0x80)
			i2c_data(I2C_DATA_HIGH);
		else
			i2c_data(I2C_DATA_LOW);
		
		i2c_delay(CLOCK_LOW_TIME/2);
		i2c_clk(I2C_CLOCK_HIGH);
		i2c_delay(CLOCK_HIGH_TIME);
		i2c_clk(I2C_CLOCK_LOW);
		i2c_delay(CLOCK_LOW_TIME/2);
		x <<= 1;
	}
	i2c_data(I2C_DATA_LOW);
	i2c_delay(CLOCK_LOW_TIME/2);
}

/* read a byte from the i2c interface */
static unsigned char i2c_inbyte(void)
{
	unsigned char aBitByte = 0;
	int i;
	int iaa;
	
	/* Release data bus by setting data high */
	i2c_data(I2C_DATA_HIGH);
		
	/* Use PORT PB instead of I2C for input. (I2C not working) */
	i2c_clk(1);
	i2c_data(1);

	/* get bits */
	for (i = 0; i < 8; i++)
	{
		i2c_delay(CLOCK_LOW_TIME/2);
		
		/* low clock period */
		i2c_clk(I2C_CLOCK_HIGH);
		
		/* switch off I2C */
		i2c_data(1);
		
		/* wait before getting bit */
		i2c_delay(CLOCK_HIGH_TIME/2);
		aBitByte = (aBitByte << 1);
		iaa = i2c_getbit();
		aBitByte = aBitByte | iaa ;
		
		/* wait */
		i2c_delay(CLOCK_HIGH_TIME/2);
		
		/* end clock pulse */
		i2c_clk(I2C_CLOCK_LOW);

		/* low clock period */
		i2c_delay(CLOCK_LOW_TIME/2);
	}
	return aBitByte;
}

/*#---------------------------------------------------------------------------
*#
*# FUNCTION NAME: i2c_getack
*#
*# DESCRIPTION  : checks if ack was received from ic2
*#
*#--------------------------------------------------------------------------*/
static int i2c_getack(void)
{
	int ack = 1;

	/* Release data bus by setting data high */
	i2c_data(I2C_DATA_HIGH);	
	i2c_delay(CLOCK_HIGH_TIME/4);

	/* generate ACK clock pulse */
	i2c_clk(I2C_CLOCK_HIGH);
	
	/* Use PORT PB instead of I2C for input. (I2C not working) */
	i2c_clk(1);
	i2c_data(1);
	
	/* switch off I2C */
	i2c_data(1);
	
	/* now wait for ack */
	i2c_delay(CLOCK_HIGH_TIME/2);
	
	/* check for ack */
	if(i2c_getbit())
		ack = 0;
	i2c_delay(CLOCK_HIGH_TIME/2);
	if(!ack){
		if(!i2c_getbit()) /* receiver pulld SDA low */
			ack = 1;
		i2c_delay(CLOCK_HIGH_TIME/2);
	}

	/* end clock pulse */
	i2c_clk(I2C_CLOCK_LOW);
	i2c_delay(CLOCK_HIGH_TIME/4);
	
	/* remove ACK clock pulse */
	i2c_data(I2C_DATA_HIGH);
	i2c_delay(CLOCK_LOW_TIME/2);
	return ack;
}

/*#---------------------------------------------------------------------------
*#
*# FUNCTION NAME: I2C::sendAck
*#
*# DESCRIPTION  : Send ACK on received data
*#
*#--------------------------------------------------------------------------*/
static void i2c_sendack(void)
{
	/* set ack pulse high */
	i2c_data(I2C_DATA_LOW);
	
	/* generate clock pulse */
	i2c_delay(CLOCK_HIGH_TIME/6);
	i2c_clk(I2C_CLOCK_HIGH);
	i2c_delay(CLOCK_HIGH_TIME);
	i2c_clk(I2C_CLOCK_LOW);
	i2c_delay(CLOCK_LOW_TIME/6);
	
	/* reset data out */
	i2c_data(I2C_DATA_HIGH);
	i2c_delay(CLOCK_LOW_TIME);	
}

/*#---------------------------------------------------------------------------
*#
*# FUNCTION NAME: i2c_writereg
*#
*# DESCRIPTION  : Writes a value to an I2C device
*#
*#--------------------------------------------------------------------------*/
static int i2c_writereg(unsigned char theSlave, unsigned char theReg,unsigned char theValue)
{
	int error, cntr = 3;
		
	do {
		error = 0;
		/* we don't like to be interrupted */

		i2c_start();
		/* send slave address */
		i2c_outbyte(theSlave);
		
		/* wait for ack */
		if(!i2c_getack())
			error = 1;
		/* now select register */
		i2c_outbyte(theReg);
		
		/* now it's time to wait for ack */
		if(!i2c_getack())
			error |= 2;
			
		/* send register register data */
		i2c_outbyte(theValue);
		
		/* now it's time to wait for ack */
		if(!i2c_getack())
			error |= 4;
			
		/* end byte stream */
		i2c_stop();
				
	} while(error && cntr--);
	
	i2c_delay(CLOCK_LOW_TIME);
	
	return -error;
}

/*#---------------------------------------------------------------------------
*#
*# FUNCTION NAME: i2c_readreg
*#
*# DESCRIPTION  : Reads a value from the decoder registers.
*#
*#--------------------------------------------------------------------------*/
static unsigned char i2c_readreg(unsigned char theSlave, unsigned char theReg)
{
	unsigned char b = 0;
	int error, cntr = 3;
			
	do {
		error = 0;
		/* we don't like to be interrupted */
   
		i2c_start();
   
		/* send slave address */
		i2c_outbyte((theSlave<<1) & 0xfe);
		/* wait for ack */
		if(!i2c_getack())
			error = 1;
			
		/* now select register */
		i2c_outbyte(theReg);

		/* now it's time to wait for ack */
		if(!i2c_getack())
			error = 1;
			
		/* repeat start condition */
		i2c_delay(CLOCK_LOW_TIME);
		i2c_start();
		
		/* send slave address */
		i2c_outbyte((theSlave<<1) | 0x01);
		
		/* wait for ack	 */
		if(!i2c_getack())
			error = 1;
			
		/* fetch register */
		b = i2c_inbyte();
		
		/* send Ack */
//		i2c_sendack();
		
		/* end sequence */
		i2c_stop();
				
	} while(error && cntr--);

	return b;
}

#define 	MAX_NUM		9
unsigned char cs4954_reg[MAX_NUM]={0x00,0x01,0x04,0x05,0x10,0x11,0x12,0x13,0x14};
unsigned char cs4954_val[MAX_NUM]={0x23,0x16,0x07,0x78,0x1c,0x3e,0xf8,0xe0,0x43};

unsigned char def_val[0x34]={0x03,0x02,0x00,0x00,0x3f,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x90,0xf4,0x00,
                             0x1c,0x3e,0xf8,0xe0,0x43,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                             0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0xa1,0x02,0x00,0x00,0x00,0x00,0x00,
                             0x00,0x00,0x00,0x00};

void cs4954_init(void)
{
	unsigned int 	i;
	unsigned char 	reg_val;
	unsigned int value;

	writel(0x3f00,GPIO_BASE_ADDR+0x0c);
        value = readl(GLOBAL_BASE_ADDR+0x30);
        value = value | 0x200;
        writel(value,GLOBAL_BASE_ADDR+0x30);

	printk("Set default value to CS4954 register......\n");	
	for (i=0;i<0x34;i++)
	{
		i2c_writereg(0x00,i,def_val[i]);
	}
	
	printk("Set NTSC-M RS170A......\n");	
	for (i=0;i<MAX_NUM;i++)
	{
		i2c_writereg(0x00,cs4954_reg[i],cs4954_val[i]);
	}
	reg_val = i2c_readreg(0x00,0x00);
	reg_val = reg_val | 0x08;
	i2c_writereg(0x00,0x00,reg_val);
	return;	
}	
#endif //marco
static void TVE_SPI_delay(unsigned int delay)
{
	unsigned int	i;
	
	for (i=0;i<delay;i++)
	{
		i = i * (i + 3);
	}	   
}

/**********************************************************************
* read a bit from ADM6996 register
***********************************************************************/
unsigned int TVE_SPI_read_bit(void) // read data from
{
	unsigned int addr;
	unsigned int value;

	addr = (GPIO_BASE_ADDR1 + GPIO_PIN_DIR);
	value = readl(addr) & (~GPIO_MISO);   // set EECK to output and MISO to input
	writel(value,addr);

	addr = (GPIO_BASE_ADDR1 + GPIO_DATA_CLEAR);
	writel(GPIO_EECK,addr); // set EECK to 0

	TVE_SPI_delay(2);
	
	addr =(GPIO_BASE_ADDR1 + GPIO_DATA_SET);
	writel(GPIO_EECK,addr); // set EECK to 1

	addr = (GPIO_BASE_ADDR1 + GPIO_DATA_IN);
	value = readl(addr) ;
		
	value = (value & (1<<GPIO_PIN_MISO)) >> GPIO_PIN_MISO;
	return value ;
}

/************************************
* TVE_SPI_write_bit
* bit_EEDO -> 1 or 0 to be written
************************************/
void TVE_SPI_write_bit(char bit_EEDO)
{
	unsigned int 	addr;
	unsigned int 	value;
//	unsigned int	i,j;

	addr = (GPIO_BASE_ADDR1 + GPIO_PIN_DIR);
	value = readl(addr) |GPIO_EECK |GPIO_MOSI ;   /* set EECK/MISO Pin to output */
	writel(value,addr);
	if(bit_EEDO)
	{
		addr = (GPIO_BASE_ADDR1 + GPIO_DATA_SET);
		writel(GPIO_MOSI,addr); /* set MISO to 1 */
		
	}
	else
	{
		addr = (GPIO_BASE_ADDR1 + GPIO_DATA_CLEAR);
		writel(GPIO_MOSI,addr); /* set MISO to 0 */
	}
	
	addr = (GPIO_BASE_ADDR1 + GPIO_DATA_CLEAR);
	writel(GPIO_EECK,addr); /* set EECK to 0 */
	addr = (GPIO_BASE_ADDR1 + GPIO_DATA_SET);
	writel(GPIO_EECK,addr); /* set EECK to 1 */
}
		
/***********************************************************
* TVE_SPI_CS_enable
* before access ,you have to enable Chip Select. (pull high)
* When fisish, you should pull low !!
*************************************************************/
void gpio0_16low()
{
	unsigned int addr,value;
	
	addr = (GPIO_BASE_ADDR + GPIO_PIN_DIR);
	value = readl(addr) | (1<<16);
	writel(value,addr);
	
	addr = (GPIO_BASE_ADDR + GPIO_DATA_OUT);
//	printk("@@==b4=in %s value %x \n",__FUNCTION__,readl(addr));
	value = readl(addr) & ~((unsigned int)(1<<16));
	writel(value,addr);
//	printk("@@===in %s value %x \n",__FUNCTION__,value);
}
void gpio0_16high()
{
	unsigned int addr,value;
	
	addr = (GPIO_BASE_ADDR + GPIO_PIN_DIR);
	value = readl(addr) | (1<<16);
	writel(value,addr);
	
	addr = (GPIO_BASE_ADDR + GPIO_DATA_OUT);
	value = readl(addr) | (1<<16);
	writel(value,addr);
//	printk("@@===in %s value %x \n",__FUNCTION__,value);
}
void TVE_SPI_CS_enable(unsigned char enable)
{

	unsigned int addr,value;

	addr = (GPIO_BASE_ADDR1 + GPIO_PIN_DIR);
//	value = readl(addr) |GPIO_EECS |GPIO_EECK;   /* set EECS/EECK Pin to output */
	value = readl(addr) | GPIO_EECK;
	writel(value,addr);
	addr = (GPIO_BASE_ADDR + GPIO_PIN_DIR);
	value = readl(addr) | GPIO_EECS;
	writel(value,addr);

	if(enable)
	{
		addr = (GPIO_BASE_ADDR + GPIO_DATA_CLEAR);
		writel(GPIO_EECS,addr); /* set EECS to 0 */
	}
	else
	{
		addr = (GPIO_BASE_ADDR + GPIO_DATA_SET);
		writel(GPIO_EECS,addr); /* set EECS to 1 */
	}
}

/************************************************
* TVE_SPI_read
* table -> which table to be read: 1/count  0/EEPROM
* addr  -> Address to be read
* return : Value of the register
*************************************************/
unsigned int TVE_SPI_read(unsigned char addr)
{
	int     i;
	char    bit;
	unsigned int value=0x00000000;

	TVE_SPI_CS_enable(1);
	
	//send read command 
	TVE_SPI_write_bit(1);
	
	// send address (MSB first, LSB last)
	for(i=SPI_ADD_LEN-1;i>=0;i--)
	{
		bit = (addr>>i)& 0x01;
		TVE_SPI_write_bit(bit);
	}
	
	// dummy read for chip ready
//	for(i=0;i<8;i++)
//		TVE_SPI_read_bit();
	
	// read 8 bits data (MSB first, LSB last)
	for(i=SPI_DAT_LEN-1;i>=0;i--)
	{
		bit = TVE_SPI_read_bit();
		value |= bit<<i;
	}

	TVE_SPI_CS_enable(0);	// CS low
	return(value);

}

void TVE_SPI_write(unsigned char addr,unsigned int value)
{
	int     i;
	char    bit;

	TVE_SPI_CS_enable(1);
	
	//send write command 
	TVE_SPI_write_bit(0);
	
	// send address (MSB first, LSB last)
	for(i=SPI_ADD_LEN-1;i>=0;i--)
	{
		bit = (addr>>i)& 0x01;
		TVE_SPI_write_bit(bit);
	}
	
	// send data (MSB first, LSB last)
	for(i=SPI_DAT_LEN-1;i>=0;i--)
	{
		bit = (value>>i)& 0x01;
		TVE_SPI_write_bit(bit);
	}

	TVE_SPI_CS_enable(0);	// CS low
}

void ILI9322_init(void)
{
	unsigned int	value;
	
	/* Disable VGA PADs function */
	value = readl(GLOBAL_BASE_ADDR+0x30);
	value = value & 0xfffffdff;
	writel(value,GLOBAL_BASE_ADDR+0x30);

	/* Disable IDE PADs function */
	value = readl(GLOBAL_BASE_ADDR+0x30);
	value = value & 0xffffffef;
	writel(value,GLOBAL_BASE_ADDR+0x30);

	/* Disable Parallel Flash function */
	value = readl(GLOBAL_BASE_ADDR+0x30);
	value = value | 0x00000002;
	writel(value,GLOBAL_BASE_ADDR+0x30);

#if 0
	TVE_SPI_CS_enable(0);

	value = readl(GLOBAL_BASE_ADDR+0x0c);
	value = value | 0x01000000;
	writel(value,GLOBAL_BASE_ADDR+0x0c);
	
	value = readl(GLOBAL_BASE_ADDR+0x0c);
	value = value & 0xfeffffff;
	writel(value,GLOBAL_BASE_ADDR+0x0c);
#endif
	
	printk("%s......\n",__func__);
#if 0	
//	TVE_SPI_write(0x15,0x55);
	value = TVE_SPI_read(0x00);
	printk("address = 0x00, value = %x \n",value);	
#else	 
	TVE_SPI_write(0x0b,0x01);
		
	TVE_SPI_write(0x03,0x0a);	
		
	TVE_SPI_write(0x10,0xa7);	
		
	TVE_SPI_write(0x11,0x57);	
		
	TVE_SPI_write(0x12,0x73);	
		
	TVE_SPI_write(0x13,0x72);	
		
	TVE_SPI_write(0x14,0x73);	
		
	TVE_SPI_write(0x15,0x55);	
		
	TVE_SPI_write(0x16,0x17);	
		
	TVE_SPI_write(0x17,0x62);	
		
	TVE_SPI_write(0x08,0x00);	
		
	TVE_SPI_write(0x0a,0x61);	
	
	TVE_SPI_write(0x06,0xbf);  /* 640Y 320 CbCr 27MHz */	

	value = TVE_SPI_read(0x0b);
	DBGPRINT(2,"address = 0x0b, value = %x \n",value);	
	value = TVE_SPI_read(0x03);
	DBGPRINT(2,"address = 0x03, value = %x \n",value);	
	value = TVE_SPI_read(0x10);
	DBGPRINT(2,"address = 0x10, value = %x \n",value);	
	value = TVE_SPI_read(0x11);
	DBGPRINT(2,"address = 0x11, value = %x \n",value);	
	value = TVE_SPI_read(0x12);
	DBGPRINT(2,"address = 0x12, value = %x \n",value);	
	value = TVE_SPI_read(0x13);
	DBGPRINT(2,"address = 0x13, value = %x \n",value);	
	value = TVE_SPI_read(0x14);
	DBGPRINT(2,"address = 0x14, value = %x \n",value);	
	value = TVE_SPI_read(0x15);
	DBGPRINT(2,"address = 0x15, value = %x \n",value);	
	value = TVE_SPI_read(0x16);
	DBGPRINT(2,"address = 0x16, value = %x \n",value);	
	value = TVE_SPI_read(0x17);
	DBGPRINT(2,"address = 0x17, value = %x \n",value);	
	value = TVE_SPI_read(0x08);
	DBGPRINT(2,"address = 0x08, value = %x \n",value);	
	value = TVE_SPI_read(0x0a);
	DBGPRINT(2,"address = 0x0a, value = %x \n",value);	
	value = TVE_SPI_read(0x06);
        DBGPRINT(2,"address = 0x06, value = %x \n",value);
#endif
	/* Enable VGA PADs function */
	value = readl(GLOBAL_BASE_ADDR+0x30);
	//value = value | 0x100200;             /* user internal clock */
	value = value | 0x200;			/* use external clock */
	writel(value,GLOBAL_BASE_ADDR+0x30);

	/* Enable Parallel Flash function */
	value = readl(GLOBAL_BASE_ADDR+0x30);
	value = value & ~0x00000002;
	writel(value,GLOBAL_BASE_ADDR+0x30);

	value = readl(GLOBAL_BASE_ADDR+0x34);
	value = value & 0xfeffffff;
	writel(value,GLOBAL_BASE_ADDR+0x34);

	value = TVE_SPI_read(0x00);
	DBGPRINT(2,"address = 0x00, value = %x \n",value);	
}	

