/*
* 	drivers/sound/storm_ssp.c 

* Storm audio driver
*
* Copyright (c) 2000 Middle Huang
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License.
*
* History:
*

*/

#include <linux/config.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <linux/sound.h>
#include <linux/soundcard.h>
#include <linux/pm.h>

#include <asm/semaphore.h>
#include <asm/mach-types.h>
#include <asm/uaccess.h>
#include <asm/hardware.h>
#include <asm/dma.h>

#include "storm_ssp.h"
//#include <asm/arch/gemini_i2s.h>
#include <asm/arch/gemini_gpio.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>

#include <linux/pci.h> 
#include <asm/io.h>
#include <asm/delay.h>
#include <linux/signal.h>

static int __init init_storm_ssp(void);

#define PFX "storm: "
#define SSP_VERSION "V0.1"

#undef DEBUG
#ifdef DEBUG
# define DPRINTK printk 
#else
# define DPRINTK(x,...)
#endif

//mknod /dev/dsp c 14 3 mknod /dev/mixer c 14 0 

#define MAX_BUFS 64		/* maximum number of rotating buffers */
#define SSP_BUF_SIZE 2048 /* needs to be a multiple of PAGE_SIZE (4096)! */

#define CNTL_C		0x80000000
#define	CNTL_ST		0x00000020
#define CNTL_44100	0x00000015	/* SSP_SR_44KHZ */
#define CNTL_8000	0x00000008	/* SSP_SR_8KHZ */

#define GAINCTL_HE	0x08000000
#define GAINCTL_LE	0x04000000
#define GAINCTL_SE	0x02000000

#define DSTATUS_PN	0x00000200
#define DSTATUS_RN	0x00000002

#define DSTATUS_IE	0x80000000

#define SSP_DF_16BITB_LINEAR	0
#define SSP_DF_8BIT_ULAW	1
#define SSP_DF_8BIT_ALAW	2
#define SSP_DF_16BITL_LINEAR	3
#define SSP_DF_16BITUB_LINEAR	4
#define SSP_DF_16BITUL_LINEAR	5

#define SSP_SS_MONO		0
#define SSP_SS_STEREO	1

#define SSP_SR_8KHZ		0x08
#define SSP_SR_16KHZ	0x09
#define SSP_SR_27KHZ	0x0A
#define SSP_SR_32KHZ	0x0B
#define SSP_SR_48KHZ	0x0E
#define SSP_SR_9KHZ		0x0F
#define SSP_SR_5KHZ		0x10
#define SSP_SR_11KHZ	0x11
#define SSP_SR_18KHZ	0x12
#define SSP_SR_22KHZ	0x13
#define SSP_SR_37KHZ	0x14
#define SSP_SR_44KHZ	0x15
#define SSP_SR_33KHZ	0x16
#define SSP_SR_6KHZ		0x17
#define SSP_SR_24KHZ	0x18


/*
 * Some magics numbers used to auto-detect file formats
 */

#define SSP_MAGIC_8B_ULAW	1
#define SSP_MAGIC_8B_ALAW	27
#define SSP_MAGIC_16B_LINEAR 3
#define SSP_MAGIC_MONO	1
#define SSP_MAGIC_STEREO	2


static int audio_dev_id, mixer_dev_id;

#define LLP_SIZE   MAX_BUFS //120//1536
#define SBUF_SIZE  SSP_BUF_SIZE //2048//1024 
#define TBUF_SIZE  (LLP_SIZE)*SBUF_SIZE
#define I2S_CPU	0
#define I2S_DMA 1

//#define IRQ_DMA_OFFSET (1<<IRQ_DMA)
#define	DEF_16_BIT	1

typedef struct {
	unsigned int tol_size, wt_size, rm_size;
	UINT32 *LinkAddrT;
  DMA_LLP_t *LLPT;
  unsigned int wt_curr,tx_curr,tx_start;
  unsigned int in_curr, in_cont, in_bufok;
  char  *tbuf, *wbuf;
  unsigned char  *in_ptr;
  unsigned int file_len;
  UINT32 current_gain;
	UINT32 dac_rate;		/* 8000 ... 48000 (Hz) */
	UINT8 data_format;		/* HARMONY_DF_xx_BIT_xxx */
	UINT8 sample_rate;		/* HARMONY_SR_xx_KHZ */
	UINT8 stereo_select;	/* HARMONY_SS_MONO or HARMONY_SS_STEREO */
	UINT32 level;
}SSP_I2S;

static SSP_I2S ssp_i2s;
static int gemini_i2s_dma(void);
int __init ssp_i2s_init(void);

int ssp_i2s_alloc(void);

#ifdef CONFIG_SL3516_ASIC                             
	#if 1
		static unsigned int	GPIO_SDA_PIN=0;
		static unsigned int	GPIO_SCL_PIN=0;
		static unsigned int	GPIO_SCS_PIN=0;
		static unsigned int	GPIO_SDA=0;
		static unsigned int	GPIO_SCL=0;
		static unsigned int	GPIO_SCS=0;
	#else
		#define GPIO_SDA_PIN				9
		#define GPIO_SCL_PIN				8
		#define GPIO_SCS_PIN				27
		#define GPIO_SDA					(1<<GPIO_SDA_PIN)	
		#define GPIO_SCL					(1<<GPIO_SCL_PIN)	
		#define GPIO_SCS					(1<<GPIO_SCS_PIN)	
	#endif
		#define	IS_SPI_MODE	0
		#define	HAVE_CS4341	1
#endif

static int ttt=0;
static DECLARE_WAIT_QUEUE_HEAD(ssp_wait_q);
//wait_queue_head_t ssp_wait_q;
static spinlock_t ssp_lock = SPIN_LOCK_UNLOCKED;	


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

    addr = GPIO_BASE_ADDR1 + GPIO_PIN_DIR;
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

    addr = GPIO_BASE_ADDR1 + GPIO_PIN_DIR;
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
	
		udelay(delay);
	//for (i=0;i<delay;i++)
	//{
	//	i = i * (i + 3);
	//}	   
}

static int i2c_getbit(void)
{
    unsigned int addr;
    unsigned int value;

    addr = GPIO_BASE_ADDR1 + GPIO_PIN_DIR;
    value = readl(addr) & ~GPIO_SDA; /* set SDA Pin to input */
    writel(value,addr);

    addr = (unsigned int)(GPIO_BASE_ADDR1 + GPIO_DATA_IN);
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
		i2c_outbyte((theSlave & 0xfe));
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
		i2c_outbyte(theSlave);
		
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

/***********************************************************
* SLIC_SPI_CS_enable
* before access ,you have to enable Chip Select. (pull high)
* When fisish, you should pull low !!
*************************************************************/
void SLIC_SPI_CS_enable(UINT8 enable)
{
	unsigned int addr;


#ifdef CONFIG_SL3516_ASIC
	if(enable)
	{
		addr = (unsigned int )(GPIO_BASE_ADDR1 + GPIO_DATA_SET);
		//*addr = GPIO_SCS; // set EECS to 1 
		writel(GPIO_SCS,addr);
		
	}
	else
	{
		addr = (unsigned int )(GPIO_BASE_ADDR1 + GPIO_DATA_CLEAR);
		//*addr = GPIO_SCS; // set EECS to 0 
		writel(GPIO_SCS,addr);
	}
#endif	
}

/************************************
* SLIC_SPI_write_bit
* bit_EEDO -> 1 or 0 to be written
************************************/
void SLIC_SPI_write_bit(char bit_EEDO)
{
	unsigned int addr;
	//unsigned int value;

#ifdef CONFIG_SL3516_ASIC
	if(bit_EEDO)
	{
		addr = (unsigned int )(GPIO_BASE_ADDR1 + GPIO_DATA_SET);
		writel(GPIO_SDA,addr);
		addr = (unsigned int )(GPIO_BASE_ADDR1 + GPIO_DATA_CLEAR);
		//*addr = GPIO_SCL; // set EECK to 0 
		writel(GPIO_SCL,addr);
		addr = (unsigned int )(GPIO_BASE_ADDR1 + GPIO_DATA_SET);
		//*addr = GPIO_SCL; // set EECK to 1 
		writel(GPIO_SCL,addr);
		
	}
	else
	{
		addr = (unsigned int )(GPIO_BASE_ADDR1 + GPIO_DATA_CLEAR);
		//*addr = GPIO_MOSI; // set MISO to 0 
		writel(GPIO_SDA,addr);
		addr = (unsigned int )(GPIO_BASE_ADDR1 + GPIO_DATA_CLEAR);
		//*addr = GPIO_SCL; // set EECK to 0 
		writel(GPIO_SCL,addr);
		addr = (unsigned int )(GPIO_BASE_ADDR1 + GPIO_DATA_SET);
		//*addr = GPIO_SCL; // set EECK to 1 
		writel(GPIO_SCL,addr);
		
	}
#endif
}


/////////////////////////
#if (IS_SPI_MODE==1)	
static void spi_write(UINT8 addr,UINT8 value)
{
	unsigned int  ad1;
	int i;
	char bit;//,status;


#ifdef CONFIG_SL3516_ASIC
	ad1 = (unsigned int)(GPIO_BASE_ADDR1 + GPIO_DATA_SET);
#else
	ad1 = (unsigned int)(GPIO_BASE_ADDR1 + GPIO_DATA_SET);
#endif	
	writel(GPIO_SCL,ad1);

#ifdef CONFIG_SL3516_ASIC
	ad1 = (unsigned int)(GPIO_BASE_ADDR1 + GPIO_DATA_CLEAR);
#else
	ad1 = (unsigned int)(GPIO_BASE_ADDR1 + GPIO_DATA_CLEAR);
#endif	
	writel(GPIO_SCL,ad1);
	
	udelay(1);
	SLIC_SPI_CS_enable(0);
	udelay(1);
	

	
	
	//write 00100000 cmd
	SLIC_SPI_write_bit(0);
	SLIC_SPI_write_bit(0);
	SLIC_SPI_write_bit(1);
	SLIC_SPI_write_bit(0);
	SLIC_SPI_write_bit(0);
	SLIC_SPI_write_bit(0);
	SLIC_SPI_write_bit(0);
	SLIC_SPI_write_bit(0);
	

#if 0
	// send 7 bits address 
	for(i=7;i>=0;i--)
	{
		bit = (addr>>i) & 0x01;
		SLIC_SPI_write_bit(bit);
	}

	
	// send 8 bits data
	for(i=0;i>8;i++)
	{
		bit = (value>>i)& 0x01;
		SLIC_SPI_write_bit(bit);
	}
#else		
	// send 7 bits address 
	for(i=7;i>=0;i--)
	{
		bit = (addr>>i) & 0x01;
		SLIC_SPI_write_bit(bit);
	}

	
	// send 8 bits data
	for(i=7;i>=0;i--)
	{
		bit = (value>>i)& 0x01;
		SLIC_SPI_write_bit(bit);
	}
#endif
	SLIC_SPI_CS_enable(1);	// CS high

}
#endif

static UINT16 cs4341_setlevel( UINT8 left, UINT8 right)
{
	//printk("%s : val %x %x",__func__,left,right);
#if (IS_SPI_MODE==1)		
	spi_write( 0x03, left > 94 ? 94 : left);
	spi_write( 0x04, right > 94 ? 94 : right);
#else
	i2c_writereg(0x22,0x03,left);//left > 94 ? 94 : left);
	//printk("\nvol L(%x)",i2c_readreg(0x23, 0x03));
	i2c_writereg(0x22,0x04,right);//right > 94 ? 94 : right);
	//printk("R(%x)\n",i2c_readreg(0x23, 0x04));
#endif	
	return 0;
}

void cs4341_init(void)
{
	unsigned int tmp;
		UINT32 addr,value;
		
		printk("cs4341_init...");
		

#if (IS_SPI_MODE==1)		 
	//init gpio 
	addr = (unsigned int )(GPIO_BASE_ADDR1 + GPIO_PIN_DIR);
	value = readl(addr);
	value |= (GPIO_SCS |GPIO_SCL|GPIO_SDA);
	writel(value,addr);	
	
	addr = (unsigned int )(GPIO_BASE_ADDR1 + GPIO_DATA_SET);
	value = (GPIO_SCS |GPIO_SCL|GPIO_SDA);
	writel(value,addr);		
	
		
	/* auto mute off, power on, no de-emphasis */
		/* I2S data up to 16 bits data 32Fs Internal SCLK internal SCLK */
	for (tmp = 0; tmp < 200; tmp++) {
			spi_write(0x01, 0x13);
			/* ATAPI mixer settings */
			spi_write(0x02, 0x09);
			/* attenuation left 3db */
			spi_write(0x03, 0x00);
			/* attenuation right 3db */
			spi_write(0x04, 0x00);
			spi_write(0x01, 0x12);
	}
#else

	//init gpio 
	addr = (unsigned int )(GPIO_BASE_ADDR1 + GPIO_PIN_DIR);
	value = readl(addr);
	value &= ~(GPIO_SCL|GPIO_SDA);
	writel(value,addr);	
	//
	addr = (unsigned int )(GPIO_BASE_ADDR1 + GPIO_DATA_OUT);
	value &= ~(GPIO_SCL|GPIO_SDA);
	writel(value,addr);		
	
	for (tmp = 0; tmp < 200; tmp++) {
			i2c_writereg(0x22,0x01,0x11);
			i2c_writereg(0x22,0x02,0x49);
			//ssp_i2s.level = 0x0b0b;
			//i2c_writereg(0x22,0x03,0x0b);
			//i2c_writereg(0x22,0x04,0x0b);
			ssp_i2s.level = 0x0;
			i2c_writereg(0x22,0x03,0x0);
			i2c_writereg(0x22,0x04,0x0);
			i2c_writereg(0x22,0x01,0x10);
			printk("(%x)",i2c_readreg(0x23, 0x00));
			printk("(%x)",i2c_readreg(0x23, 0x01));
			printk("(%x)",i2c_readreg(0x23, 0x02));
			printk("(%x)",i2c_readreg(0x23, 0x03));
			printk("(%x)",i2c_readreg(0x23, 0x04));
			if (i2c_readreg(0x23, 0x02) == 0x49)
			{
				printk("OK(%d)\n",tmp);
					break;
			}
	}
#endif
	
}

void i2s_init(void)
{
	
		UINT32 j;
	//unsigned int *base;
    unsigned int data=0,tmp;

#ifdef CONFIG_SL3516_ASIC
    	data = READ_GLOBAL_REG(0x04);
    	tmp = READ_GLOBAL_REG(0x0);
    	
    	printk("4(%x) 0(%x)\n",data,tmp);
    	if((data&0x40000000)&&((tmp&0xff)==0xc3))//check global
    	{
    		printk("RG board\n");
    		GPIO_SDA_PIN=7;
				GPIO_SCL_PIN=5;
				//GPIO_SCS_PIN=27;
				GPIO_SDA = (1<<GPIO_SDA_PIN);	
				GPIO_SCL = (1<<GPIO_SCL_PIN);	
				//GPIO_SCS = (1<<GPIO_SCS_PIN);	
    	}
    	else
    	{
    		printk("Other board\n");
    		GPIO_SDA_PIN=9;
				GPIO_SCL_PIN=8;
				GPIO_SCS_PIN=27;
				GPIO_SDA = (1<<GPIO_SDA_PIN);	
				GPIO_SCL = (1<<GPIO_SCL_PIN);	
				GPIO_SCS = (1<<GPIO_SCS_PIN);	
    	}
    	
			data = READ_GLOBAL_REG(0x0C);
    	data|=0x80000;
    	WRITE_GLOBAL_REG(0x0C,data);
		
    	data = READ_GLOBAL_REG(0x30);
    
    	data|=0x100;
    	tmp = READ_GLOBAL_REG(0x0);
			if((tmp&0x00FFFF00)==0x351600)
    			//data&=0xfffeffbf;//for 3516
    			data&=0xfffeffaf;//for 3516
    	else
    			data&=0xfffeffaf;//for 3512 //need to disable IDE pad
    	WRITE_GLOBAL_REG(0x30,data);
    

	
	WRITE_SSP_REG(SSP_FRAME_CTRL, 0x25020003 ); //0x04010030//ext clk : bit17
  	WRITE_SSP_REG(SSP_BAUD_RATE, 0x01000100);
#else

	
	WRITE_SSP_REG(SSP_FRAME_CTRL, 0x04010030 ); //0x04010030//ext clk : bit17
  	WRITE_SSP_REG(SSP_BAUD_RATE, 0x1F020502);

 #endif 			

  				WRITE_SSP_REG(SSP_FRAME_CTRL2, 0x1003700F);//0x0003800f
  				WRITE_SSP_REG(SSP_FIFO_CTRL, 0x00003414);
#if (DEF_16_BIT==1)		  				
  				WRITE_SSP_REG(SSP_TX_SLOT_VALID0, 0x0000000F);
#else  		
					WRITE_SSP_REG(SSP_TX_SLOT_VALID0, 0x00000005);		
#endif  				
  				WRITE_SSP_REG(SSP_TX_SLOT_VALID1, 0x00000000);
  				WRITE_SSP_REG(SSP_TX_SLOT_VALID2, 0x00000000);
  				WRITE_SSP_REG(SSP_TX_SLOT_VALID3, 0x00000000);
#if (DEF_16_BIT==1)		  				
  				WRITE_SSP_REG(SSP_RX_SLOT_VALID0, 0x0000000F);
#else  		
					WRITE_SSP_REG(SSP_RX_SLOT_VALID0, 0x00000005);		
#endif  				
  				WRITE_SSP_REG(SSP_RX_SLOT_VALID1, 0x00000000);
  				WRITE_SSP_REG(SSP_RX_SLOT_VALID2, 0x00000000);
  				WRITE_SSP_REG(SSP_RX_SLOT_VALID3, 0x00000000);
  				WRITE_SSP_REG(SSP_SLOT_SIZE0, 0xffffffff);
  				WRITE_SSP_REG(SSP_SLOT_SIZE1, 0xffffffff);
  				WRITE_SSP_REG(SSP_SLOT_SIZE2, 0xffffffff);
  				WRITE_SSP_REG(SSP_SLOT_SIZE3, 0xffffffff);
  				//WRITE_SSP_REG(SSP_CTRL_STATUS, 0x1F100000);//0x9F100000
  				//mdelay(250);
  				//WRITE_SSP_REG(SSP_CTRL_STATUS, 0x00100000);//0x80100000
  				WRITE_SSP_REG(SSP_CTRL_STATUS, 0xCF0081FF);//0x9F100000
  				mdelay(250);
  				WRITE_SSP_REG(SSP_CTRL_STATUS, 0xC0008000);//0x80100000
					
			

	mdelay(500);
		ssp_i2s.tol_size = 0; 
		ssp_i2s.wt_size = 0; 
		ssp_i2s.rm_size = 0; 
		ssp_i2s.wt_curr = 0; 
		ssp_i2s.in_curr = 0; 
		ssp_i2s.in_cont = 0;
		ssp_i2s.tx_curr = 0; 
		ssp_i2s.in_bufok = 0;
		ssp_i2s.file_len = 0;
		ssp_i2s.level = 0;
		
		
#if (HAVE_CS4341==1)		
		cs4341_init();
		//cs4341_setlevel(0, 0);
		
#endif		
		
			for(j=0;j<LLP_SIZE;j++)//Tx
  		{
  			ssp_i2s.LLPT[j].src_addr = __pa((UINT32)ssp_i2s.tbuf + ((j%LLP_SIZE) * SBUF_SIZE));	
  			ssp_i2s.LLPT[j].dst_addr = SL2312_SSP_CTRL_BASE+SSP_WRITE_PORT;
  			ssp_i2s.LLPT[j].llp = __pa(((UINT32)&ssp_i2s.LLPT[((j+1)%LLP_SIZE)]))|0x1;
#if (DEF_16_BIT==1)		  			
  			ssp_i2s.LLPT[j].ctrl_size = ((SBUF_SIZE/4)|(0x040a<<16));//0x140a<<16;    //tx:100a rx:1021
#else
				ssp_i2s.LLPT[j].ctrl_size = (((SBUF_SIZE/4)/2)|(0x040a<<16));//0x140a<<16;    //tx:100a rx:1021
#endif  
  		}
  		
  		
}

static int ssp_i2s_mixer_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
{
	
	int val;
	int ret;
	
printk("ssp_i2s_mixer_ioctl\n");
	if (cmd == SOUND_MIXER_INFO) {
		mixer_info info;
		return 0;
	}
	
	if (cmd == OSS_GETVERSION)
		return put_user(SOUND_VERSION, (int *)arg);

	/* read */
	val = 0;
	if (_SIOC_DIR(cmd) & _SIOC_WRITE)
		if (get_user(val, (int *)arg))
			return -EFAULT;
			
printk("%s : **************** ssp_i2s_mixer_ioctl\n",__func__);
	switch (cmd) {
	case MIXER_READ(SOUND_MIXER_CAPS):
		printk("%s : SOUND_MIXER_CAPS\n",__func__);
		ret = SOUND_CAP_EXCL_INPUT;
		break;
	case MIXER_READ(SOUND_MIXER_STEREODEVS):
		printk("%s : SOUND_MIXER_STEREODEVS\n",__func__);
		ret = SOUND_MASK_VOLUME | SOUND_MASK_PCM;
		break;
		
	case MIXER_READ(SOUND_MIXER_RECMASK):
		ret = 0;//SOUND_MASK_MIC | SOUND_MASK_LINE;
		printk("%s : SOUND_MIXER_RECMASK\n",__func__);
		break;
	
	case MIXER_READ(SOUND_MIXER_DEVMASK):
		printk("%s : SOUND_MIXER_DEVMASK\n",__func__);
		ret = SOUND_MASK_VOLUME | SOUND_MASK_PCM;// | SOUND_MASK_IGAIN | SOUND_MASK_MONITOR;
		break;
		
	case MIXER_READ(SOUND_MIXER_OUTMASK):
		printk("%s : SOUND_MIXER_OUTMASK\n",__func__);
		ret = 0;//MASK_INTERNAL | MASK_LINEOUT | MASK_HEADPHONES;
		break;
		
	case MIXER_WRITE(SOUND_MIXER_RECSRC):
		printk("%s : SOUND_MIXER_RECSRC\n",__func__);
		ret = 0;//harmony_mixer_set_recmask(val);
		break;
		
	case MIXER_READ(SOUND_MIXER_RECSRC):
		printk("%s : SOUND_MIXER_RECSRC\n",__func__);
		ret = 0;//harmony_mixer_get_recmask();
		break;
	      
	case MIXER_WRITE(SOUND_MIXER_OUTSRC):
		printk("%s : SOUND_MIXER_OUTSRC\n",__func__);
		ret = 0;//val & (MASK_INTERNAL | MASK_LINEOUT | MASK_HEADPHONES);
		break;
		
	case MIXER_READ(SOUND_MIXER_OUTSRC):
		printk("%s : SOUND_MIXER_OUTSRC\n",__func__);
		ret = 0;//(MASK_INTERNAL | MASK_LINEOUT | MASK_HEADPHONES);
		break;
	
	case MIXER_WRITE(SOUND_MIXER_VOLUME):
	//case MIXER_WRITE(SOUND_MIXER_IGAIN):
	//case MIXER_WRITE(SOUND_MIXER_MONITOR):
	case MIXER_WRITE(SOUND_MIXER_PCM):

#if (HAVE_CS4341==1)		
		ret = cs4341_setlevel(val>>0x08, val&0xff);
		ssp_i2s.level = val;
#endif		
		break;

	case MIXER_READ(SOUND_MIXER_VOLUME):
	//case MIXER_READ(SOUND_MIXER_IGAIN):
	//case MIXER_READ(SOUND_MIXER_MONITOR):
	case MIXER_READ(SOUND_MIXER_PCM):
		ret = ssp_i2s.level;
		break;

	default:
		return -EINVAL;
	}

	if (put_user(ret, (int *)arg))
		return -EFAULT;
	return 0; 
}

static int ssp_i2s_mixer_open(struct inode *inode, struct file *file)
{
	printk("ssp_i2s_mixer_open\n");
	//cs4341_init();
		
	return 0;
}

static int ssp_i2s_mixer_release(struct inode *inode, struct file *file)
{
		//i2c_writereg(0x22,0x01,0x11);
				printk("ssp_i2s_mixer_release\n");
	return 0;
}

//static ssize_t ssp_i2s_mixer_write(struct file *file_p, const char __user *buf, size_t count, loff_t * ppos)
//{
//		//printk("ssp_i2s_mixer_write\n");
//	return 0;
//}



static int ssp_i2s_dsp_open(struct inode *inode, struct file *file)
{

				
				WRITE_DMA_REG(DMA_CFG, 0x0); //disable DMA
				WRITE_DMA_REG(DMA_INT_TC_CLR, 0x4);
	return 0;
}


static int ssp_i2s_dsp_release(struct inode *inode, struct file *file)
{
				*((volatile unsigned int *)IRQ_MASK(IO_ADDRESS(SL2312_INTERRUPT_BASE))) &= ~(IRQ_DMA_OFFSET);
				printk("Stoem I2S of SSP release(dsp)\n");
				
				WRITE_DMA_REG(DMA_CFG, 0x0); //disable DMA
				WRITE_DMA_REG(DMA_INT_TC_CLR, 0x4);
					
	return 0;
}


static irqreturn_t ssp_interrupt(int irq, void *dev_instance, struct pt_regs *regs)
{
	int                     tmp;
	unsigned int opcode, old_opcode=0;
	
	disable_irq(irq);   /* disable  interrupt */
		
        opcode = (IRQ_SSP_MASK);
        *((volatile unsigned int *)IRQ_CLEAR(IO_ADDRESS(SL2312_INTERRUPT_BASE))) = opcode;
        	
	opcode = READ_SSP_REG(SSP_CTRL_STATUS);//0x9F100000
	//printk("ssp int status : %x\n",opcode);
	WRITE_SSP_REG(SSP_CTRL_STATUS,opcode);
	
	enable_irq(irq);
	printk("ssp int status : %x\n",opcode);
		opcode = *((volatile unsigned int *)(IO_ADDRESS(SL2312_INTERRUPT_BASE+0x04)));
        if((opcode&0x00c40000)==0x00c40000)
        	 		old_opcode = opcode;
        else
        	*((volatile unsigned int *)(IO_ADDRESS(SL2312_INTERRUPT_BASE+0x04))) = old_opcode;
	
	return IRQ_RETVAL(IRQ_HANDLED);
}

static irqreturn_t ssp_i2s_interrupt(int irq, void *dev_instance, struct pt_regs *regs)
{
	int                     tmp;
	unsigned int opcode=0, old_opcode=0, w_start=0, w_end=0, i, sizeb=0;
	unsigned char *tmp_ptr;
	
	disable_irq(irq);   /* disable  interrupt */
	tmp=READ_DMA_REG(DMA_INT_TC); 
			if((tmp&0x04)==0x04)//tc
			{				
				opcode = READ_DMA_REG(DMA_CH2_SRC_ADDR);
				opcode -= (opcode%SBUF_SIZE);
				old_opcode = opcode;
				//old_opcode = (old_opcode - ssp_i2s.tx_curr)/SBUF_SIZE;
				
				if(old_opcode >= ssp_i2s.tx_curr)
						old_opcode -= ssp_i2s.tx_curr;
				else
					old_opcode = old_opcode + TBUF_SIZE - ssp_i2s.tx_curr;
				
				old_opcode = (old_opcode/SBUF_SIZE);
				
				w_start = ((ssp_i2s.tx_curr-ssp_i2s.tx_start)/SBUF_SIZE);
				ssp_i2s.tx_curr = opcode;
				w_end = ((ssp_i2s.tx_curr-ssp_i2s.tx_start)/SBUF_SIZE);
				if(w_end < w_start)
						w_end += LLP_SIZE;
				

				//printk("*%d*",((ssp_i2s.tx_curr-ssp_i2s.LLPT[0].src_addr)/SBUF_SIZE));
				if(ssp_i2s.in_cont>=old_opcode)
				{					
										for(i=w_start;i<(w_end-1);i++)
					{
						//printk("[%x]",(i%LLP_SIZE));
						tmp_ptr = __va(ssp_i2s.LLPT[i%LLP_SIZE].src_addr);
						sizeb = ((ssp_i2s.LLPT[i%LLP_SIZE].ctrl_size>>16)*4);
#if (DEF_16_BIT==1)			
						ssp_i2s.tol_size += sizeb;
						memset(tmp_ptr, 0, SBUF_SIZE);
						//consistent_sync(tmp_ptr, SBUF_SIZE, DMA_BIDIRECTIONAL);
		
#else
						sizeb = ((ssp_i2s.LLPT[i%LLP_SIZE].ctrl_size>>16)*8);
						ssp_i2s.tol_size += sizeb;
						memset(tmp_ptr, 0, SBUF_SIZE);
						//consistent_sync(tmp_ptr, SBUF_SIZE, DMA_BIDIRECTIONAL);
#endif						
					}
						
					ssp_i2s.in_cont-=old_opcode;
				}
				else
				{
					for(i=w_start;i<(w_end-1);i++)
					{
						//printk("[%x]",(i%LLP_SIZE));
						tmp_ptr = __va(ssp_i2s.LLPT[i%LLP_SIZE].src_addr);
						memset(tmp_ptr, 0, SBUF_SIZE);
									
					}
						
				
					ssp_i2s.in_cont = 0;

				}
				
				wake_up_interruptible(&ssp_wait_q);
			}
	WRITE_DMA_REG(DMA_INT_TC_CLR, (tmp&0x04));		
	enable_irq(irq);

	return IRQ_RETVAL(IRQ_HANDLED);
}

static ssize_t ssp_i2s_dsp_write(struct file *file_p, const char __user *buf, size_t count, loff_t * ppos)
{
	
	DECLARE_WAITQUEUE(wait, current);
	int ofs=0, written = 0, i=0, len=0, j=0,proc_w=0;
	unsigned char tmp[SBUF_SIZE], *tmp_ptr;
	//struct task_struct *tsk = current;
	unsigned long flags;
	
	
	
			add_wait_queue(&ssp_wait_q, &wait);
			set_current_state(TASK_INTERRUPTIBLE);//TASK_INTERRUPTIBLE); //TASK_UNINTERRUPTIBLE
//			mb();

			//if need one time copy from user by write function
			//if(count>TBUF_SIZE)
			//	count = TBUF_SIZE;
			//copy_from_user(ssp_i2s.wbuf, buf, count);
			
			proc_w = count;
			written = count / SBUF_SIZE;
			ofs = count % SBUF_SIZE;
			if(ofs > 0)
				written++;


		
		while(proc_w)
		{
			spin_lock_irqsave(&ssp_lock,flags);
			
			if((ssp_i2s.in_cont>(LLP_SIZE-3)))//||(((ssp_i2s.wt_curr+1)%LLP_SIZE) == ((ssp_i2s.tx_curr-ssp_i2s.LLPT[0].src_addr)/SBUF_SIZE)))
			{
				spin_unlock_irqrestore(&ssp_lock, flags);
				interruptible_sleep_on(&ssp_wait_q);
				//schedule();
			}
			//if(ssp_i2s.in_cont<LLP_SIZE)
			else
	//		if(ssp_i2s.in_cont<LLP_SIZE)
			{
				spin_unlock_irqrestore(&ssp_lock, flags);
				
#if (DEF_16_BIT==1)					
				//for(i=0;i<written;i++)
				{		
					spin_lock_irqsave(&ssp_lock,flags);
					if((LLP_SIZE - ssp_i2s.in_cont)>0)
					{
						spin_unlock_irqrestore(&ssp_lock, flags);
						if(proc_w >= SBUF_SIZE)
						{
								copy_from_user(tmp, (buf+(len/SBUF_SIZE)*SBUF_SIZE), SBUF_SIZE);
								//consistent_sync(tmp,SBUF_SIZE, DMA_BIDIRECTIONAL);
								tmp_ptr = __va(ssp_i2s.LLPT[ssp_i2s.wt_curr].src_addr); //(ssp_i2s.wbuf+((ssp_i2s.in_curr%LLP_SIZE) * SBUF_SIZE));
								if(ssp_i2s.data_format ==SSP_DF_16BITL_LINEAR || ssp_i2s.data_format == SSP_DF_16BITUL_LINEAR)
								{
										for(j=0;j<SBUF_SIZE;j+=2)
										{
											*(tmp_ptr+j) = *(tmp+j+1);
											*(tmp_ptr+j+1) = *(tmp+j);
										}
								}
								else
								{
									memcpy(tmp_ptr, tmp, SBUF_SIZE);
								}
								//ssp_i2s.LLPT[ssp_i2s.wt_curr].owner = I2S_DMA;
								//consistent_sync(tmp_ptr,SBUF_SIZE, DMA_BIDIRECTIONAL);				
								ssp_i2s.LLPT[ssp_i2s.wt_curr].ctrl_size = (SBUF_SIZE/4)|0x040a<<16;
								len+=SBUF_SIZE;
								//ssp_i2s.tol_size += SBUF_SIZE;
								proc_w -= SBUF_SIZE;
						}
						else if((proc_w < SBUF_SIZE)&&(proc_w > 0))
						{
							spin_unlock_irqrestore(&ssp_lock, flags);
							//memset((ssp_i2s.tbuf+((ssp_i2s.wt_curr%LLP_SIZE) * SBUF_SIZE)), 0x0, SBUF_SIZE);
							copy_from_user(tmp, (buf+(len/SBUF_SIZE)*SBUF_SIZE), proc_w);
							//consistent_sync(tmp,proc_w, DMA_BIDIRECTIONAL);
							tmp_ptr = __va(ssp_i2s.LLPT[ssp_i2s.wt_curr].src_addr); //(ssp_i2s.wbuf+((ssp_i2s.wt_curr%LLP_SIZE) * SBUF_SIZE));
								if(ssp_i2s.data_format ==SSP_DF_16BITL_LINEAR || ssp_i2s.data_format == SSP_DF_16BITUL_LINEAR)
								{
										for(j=0;j<proc_w;j+=2)
										{
											*(tmp_ptr+j) = *(tmp+j+1);
											*(tmp_ptr+j+1) = *(tmp+j);
										}
								}
								else
								{
									memcpy(tmp_ptr, tmp, SBUF_SIZE);
								}
							//consistent_sync(tmp_ptr,ofs, DMA_BIDIRECTIONAL);
							//ssp_i2s.LLPT[ssp_i2s.wt_curr].owner = I2S_DMA;
							ssp_i2s.LLPT[ssp_i2s.wt_curr].ctrl_size = (proc_w/4)|0x040a<<16;
							len+=ofs;
							//ssp_i2s.tol_size += ofs;
							proc_w -= proc_w;
							
						}
					
						
						ssp_i2s.in_curr++;
						ssp_i2s.wt_curr++;
						
						spin_lock_irqsave(&ssp_lock,flags);
						//printk(" [-%d %p- %d %d %d] ",count,buf,ssp_i2s.wt_curr, ssp_i2s.in_cont, ((ssp_i2s.tx_curr-ssp_i2s.LLPT[0].src_addr)/SBUF_SIZE));
						ssp_i2s.in_cont++;
						if(ssp_i2s.in_cont>LLP_SIZE)
							ssp_i2s.in_cont = LLP_SIZE;
							spin_unlock_irqrestore(&ssp_lock, flags);
						//if((ssp_i2s.wt_curr == LLP_SIZE)&&(ssp_i2s.in_bufok == 0))
						if((ssp_i2s.wt_curr > (LLP_SIZE/32))&&(ssp_i2s.in_bufok == 0))
						{
								ssp_i2s.in_bufok = 1;
								ssp_i2s.in_curr %= LLP_SIZE;
								ssp_i2s.wt_curr %= LLP_SIZE;
								gemini_i2s_dma();
								printk("i2s Start DMA .......(%d)\n",ssp_i2s.in_curr);
						}
						

						ssp_i2s.in_curr %= LLP_SIZE;
						ssp_i2s.wt_curr %= LLP_SIZE;
					}
				}	
				
			
#else

				//for(i=0;i<written;i++)
				{
					spin_lock_irqsave(&ssp_lock,flags);
					if((LLP_SIZE - ssp_i2s.in_cont)>0)
					{
						spin_unlock_irqrestore(&ssp_lock, flags);
						if(proc_w >= SBUF_SIZE)
						{
								copy_from_user(tmp, (buf+(len/SBUF_SIZE)*SBUF_SIZE), SBUF_SIZE);
								//consistent_sync(tmp,SBUF_SIZE, DMA_BIDIRECTIONAL);
								tmp_ptr = __va(ssp_i2s.LLPT[ssp_i2s.wt_curr].src_addr); //(ssp_i2s.wbuf+((ssp_i2s.wt_curr%LLP_SIZE) * SBUF_SIZE));
								for(j=0;j<(SBUF_SIZE/2);j++)
								{
									*(tmp_ptr+j) = *(tmp+(2*j)+1);
									
								}
								//ssp_i2s.LLPT[ssp_i2s.wt_curr].owner = I2S_DMA;
								//consistent_sync(tmp_ptr,SBUF_SIZE, DMA_BIDIRECTIONAL);
								ssp_i2s.LLPT[ssp_i2s.wt_curr].ctrl_size = (SBUF_SIZE/4)/2)|0x040a<<16;
								len+=SBUF_SIZE;
								//ssp_i2s.tol_size += SBUF_SIZE;
								proc_w -= SBUF_SIZE;
						}
						else
						{
							spin_unlock_irqrestore(&ssp_lock, flags)
								//memset((ssp_i2s.tbuf+((ssp_i2s.wt_curr%LLP_SIZE) * SBUF_SIZE)), 0x0, SBUF_SIZE);
								copy_from_user(tmp, (buf+(len/SBUF_SIZE)*SBUF_SIZE), proc_w);
								//consistent_sync(tmp,proc_w, DMA_BIDIRECTIONAL);
								tmp_ptr = __va(ssp_i2s.LLPT[ssp_i2s.wt_curr].src_addr); //(ssp_i2s.wbuf+((ssp_i2s.wt_curr%LLP_SIZE) * SBUF_SIZE));
								for(j=0;j<((proc_w+1)/2);j++)
								{
									*(tmp_ptr+j) = *(tmp+(2*j)+1);
								}
								//ssp_i2s.LLPT[ssp_i2s.wt_curr].owner = I2S_DMA;
								//consistent_sync(tmp_ptr.src_addr),ofs, DMA_BIDIRECTIONAL);
								ssp_i2s.LLPT[ssp_i2s.wt_curr].ctrl_size = (proc_w/4)/2)|0x040a<<16;
								len+=ofs;
								//ssp_i2s.tol_size += ofs;
								proc_w -= proc_w;
						}

						
						ssp_i2s.in_curr++;
						ssp_i2s.wt_curr++;
						if((ssp_i2s.in_curr == LLP_SIZE)&&(ssp_i2s.in_bufok == 0))
						{
								ssp_i2s.in_bufok = 1;
								
								gemini_i2s_dma();
								printk("i2s Start DMA .......(%d)\n",ssp_i2s.in_curr);
						}
						ssp_i2s.in_curr %= LLP_SIZE;
						ssp_i2s.wt_curr %= LLP_SIZE;
						spin_lock_irqsave(&ssp_lock,flags);
						ssp_i2s.in_cont++;
						
						if(ssp_i2s.in_cont>LLP_SIZE)
							ssp_i2s.in_cont = LLP_SIZE;
							spin_unlock_irqrestore(&ssp_lock, flags)
					}

				}	
							
#endif	

//					tsk->state = TASK_RUNNING;
						
			}//if(ssp_i2s.in_cont<LLP_SIZE)
		}//else
		
		set_current_state(TASK_RUNNING);
			remove_wait_queue(&ssp_wait_q, &wait);
			return len;		
		//	return len;
}

static int ssp_i2s_dsp_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
{
	int value;
		unsigned int data;
	count_info inf;
	switch(cmd) {
	int ival, new_format;
	int frag_size, frag_buf;
	struct audio_buf_info info;
	
	case SSP_I2S_INIT_BUF:
				i2s_init();
			memset(ssp_i2s.tbuf, 0x00, TBUF_SIZE);
			//memset(ssp_i2s.tbuf, 0x00, TBUF_SIZE);
			ssp_i2s.tol_size = 0; 
			ssp_i2s.wt_size = 0; 
			ssp_i2s.rm_size = 0; 
			ssp_i2s.wt_curr = 0; 
			ssp_i2s.in_curr = 0; 
			ssp_i2s.in_cont = 0;
			ssp_i2s.tx_curr = 0; 
			ssp_i2s.file_len = 0;
			ssp_i2s.in_bufok = 0;
			//value = gemini_i2s_dma();
			printk("SSP_I2S_DMA SSP_I2S_INIT_BUF \n");
			break;
		case SSP_I2S_STOP_DMA:
			//reset ssp 
			data = READ_GLOBAL_REG(0x0C);
    	data|=0x80000;
    	WRITE_GLOBAL_REG(0x0C,data);
    	//disable dma int
				*((volatile unsigned int *)IRQ_MASK(IO_ADDRESS(SL2312_INTERRUPT_BASE))) &= ~(IRQ_DMA_OFFSET);
				
				WRITE_DMA_REG(DMA_CFG, 0x0); //disable DMA
				WRITE_DMA_REG(DMA_INT_TC_CLR, 0x4);
			break;
			
		case SSP_I2S_FILE_LEN:
				if(arg) 
					copy_from_user(&value, (int *)arg, sizeof(value));

				ssp_i2s.file_len = value;
				printk("ssp_i2s.file_len : %d\n",ssp_i2s.file_len);
			break;
			
		case SSP_I2S_INIT_MIXER:
#if (HAVE_CS4341==1)			
				//cs4341_init();
#endif				
			break;
			
		case SSP_I2S_INC_LEVEL:
#if (HAVE_CS4341==1)					
				ssp_i2s.level += 0x0101;
				if(ssp_i2s.level > 0x5e5e)
					ssp_i2s.level = 0x5e5e;
				
				cs4341_setlevel(ssp_i2s.level>>0x08, ssp_i2s.level&0xff);
				value = ssp_i2s.level;
				//printk("SSP_I2S_INC_LEVEL ssp_i2s.level : %x\n",ssp_i2s.level);
#endif
			break;
			
		case SSP_I2S_DEC_LEVEL:
#if (HAVE_CS4341==1)					
				if(ssp_i2s.level<0x0101)
					ssp_i2s.level -= 0;
				else
					ssp_i2s.level -= 0x0101;
				
				value = ssp_i2s.level;
				cs4341_setlevel(ssp_i2s.level>>0x08, ssp_i2s.level&0xff);
#endif				
				//printk("SSP_I2S_DEC_LEVEL ssp_i2s.level : %x\n",ssp_i2s.level);
			break;
	
	case SSP_I2S_SETFMT:
				if(arg) 
					copy_from_user(&value, (int *)arg, sizeof(value));

				ssp_i2s.data_format = value;
				printk("data_format : %d\n",ssp_i2s.data_format);
			break;
	
	case SSP_I2S_STEREO:
				if(arg) 
					copy_from_user(&value, (int *)arg, sizeof(value));

				ssp_i2s.stereo_select  = value;
				printk("stereo_select : %d\n",ssp_i2s.stereo_select);
			break;		
	
	case SSP_I2S_SETSPEED:
				if(arg) 
					copy_from_user(&value, (int *)arg, sizeof(value));
				
									switch (value) {
											case 0:	ssp_i2s.dac_rate = 44100;	break;
											case 1:	ssp_i2s.dac_rate = 22050;	break; 
											case 2:	ssp_i2s.dac_rate = 48000;	break; 
											case 3:	ssp_i2s.dac_rate = 24000;	break; 
											default:	
												ssp_i2s.dac_rate = 44100; 
												break;
									} 
				ssp_i2s.sample_rate = ssp_i2s.dac_rate;
				printk("speed : %d\n",ssp_i2s.dac_rate);
			break;
	
	case SSP_I2S_SETCHANNELS:
				if(arg) 
					copy_from_user(&value, (int *)arg, sizeof(value));

				ssp_i2s.stereo_select = value-1;
				printk("channel : %d\n",ssp_i2s.stereo_select);
			break;
			/////////////			
	case OSS_GETVERSION:
		printk("%s : OSS_GETVERSION\n",__func__);
		return put_user(SOUND_VERSION, (int *) arg);

	case SNDCTL_DSP_GETCAPS:
		ival = DSP_CAP_BATCH;
		printk("%s : SNDCTL_DSP_GETCAPS\n",__func__);
		return put_user(ival, (int *) arg);

	case SNDCTL_DSP_GETFMTS:
		ival = (AFMT_S16_BE | AFMT_S16_LE );//| AFMT_MU_LAW | AFMT_A_LAW ); //AFMT_S16_BE
		printk("%s : SNDCTL_DSP_GETFMTS\n",__func__);
		return put_user(ival, (int *) arg);
	
	case SNDCTL_DSP_SETFMT:
	printk("%s : SNDCTL_DSP_SETFMT\n",__func__);
					
		if (get_user(ival, (int *) arg)) 
			return -EFAULT;
			
			printk("SSP_I2S_DMA SSP_I2S_INIT_BUF(%x) \n",ival);
		if (ival != AFMT_QUERY) {
			switch (ival) {
			//case AFMT_MU_LAW:	new_format = SSP_DF_8BIT_ULAW; break;
			//case AFMT_A_LAW:	new_format = SSP_DF_8BIT_ALAW; break;
			case AFMT_S16_BE:	new_format = SSP_DF_16BITB_LINEAR; break;
			case AFMT_S16_LE:	new_format = SSP_DF_16BITL_LINEAR; break;
			case AFMT_U16_BE:	new_format = SSP_DF_16BITUB_LINEAR; break;
			case AFMT_U16_LE:	new_format = SSP_DF_16BITUL_LINEAR; break;
			default: {
				DPRINTK(KERN_WARNING PFX 
					"unsupported sound format 0x%04x requested.\n",
					ival);
				ival = AFMT_S16_BE;
				return put_user(ival, (int *) arg);
			}
			}
				ssp_i2s.data_format = new_format;
				i2s_init();
				//memset(ssp_i2s.tbuf, 0x00, TBUF_SIZE);
				memset(ssp_i2s.tbuf, 0x00, TBUF_SIZE);
				ssp_i2s.tol_size = 0; 
				ssp_i2s.wt_size = 0; 
				ssp_i2s.rm_size = 0; 
				ssp_i2s.wt_curr = 0; 
				ssp_i2s.in_curr = 0; 
				ssp_i2s.in_cont = 0;
				ssp_i2s.tx_curr = 0; 
				ssp_i2s.file_len = 0;
				ssp_i2s.in_bufok = 0;
				//value = gemini_i2s_dma();
			return 0;
		} else {
			switch (ssp_i2s.data_format) {
			//case SSP_DF_8BIT_ULAW:	ival = AFMT_MU_LAW; break;
			//case SSP_DF_8BIT_ALAW:	ival = AFMT_A_LAW;  break;
			//case SSP_DF_16BIT_LINEAR:	ival = AFMT_U16_BE; break;//AFMT_S16_BE
			case SSP_DF_16BITB_LINEAR:	ival = AFMT_S16_BE; break;//AFMT_S16_BE
			case SSP_DF_16BITL_LINEAR:	ival = AFMT_S16_LE; break;//AFMT_S16_BE
			case SSP_DF_16BITUB_LINEAR:	ival = AFMT_U16_BE; break;//AFMT_S16_BE
			case SSP_DF_16BITUL_LINEAR:	ival = AFMT_U16_LE; break;//AFMT_S16_BE
			default: ival = 0;
			}
			
			
			return put_user(ival, (int *) arg);
		}

	case SOUND_PCM_READ_RATE:
			if (get_user(ival, (int *) arg)) 
					return -EFAULT;
	printk("%s : SOUND_PCM_READ_RATE(%d)\n",__func__,ival);
			ssp_i2s.dac_rate = 44100;
			ival = ssp_i2s.dac_rate;
		return put_user(ival, (int *) arg);

	case SNDCTL_DSP_SPEED:
	
		if (get_user(ival, (int *) arg))
			return -EFAULT;
		printk("%s : SNDCTL_DSP_SPEED(%d)\n",__func__,ival);
		//if (ival < 8000) ival = 8000;
		//if (ival > 44100) ival = 44100;
		ival = 44100;
		ssp_i2s.dac_rate = 44100;
		return put_user(ival, (int*) arg);

	case SNDCTL_DSP_STEREO:
	
		if (get_user(ival, (int *) arg))
			return -EFAULT;
		printk("%s : SNDCTL_DSP_STEREO(%d)\n",__func__,ival);
		if (ival != 0 && ival != 1)
			return -EINVAL;
		
		ssp_i2s.stereo_select = ival;
 		return 0;
 
 	case SNDCTL_DSP_CHANNELS:
 	
 		if (get_user(ival, (int *) arg))
 			return -EFAULT;
 		
 		printk("%s : SNDCTL_DSP_CHANNELS(%d)\n",__func__,ival);
 		if (ival != 1 && ival != 2) {
 			ival = ssp_i2s.stereo_select == SSP_SS_MONO ? 1 : 2;
 			return put_user(ival, (int *) arg);
 		}
 		ssp_i2s.stereo_select = ival-1;
 		return 0;
 		
	case SOUND_PCM_READ_CHANNELS:
	printk("%s : SOUND_PCM_READ_CHANNELS\n",__func__);
				ival = ssp_i2s.stereo_select+1 ;
 			return put_user(ival, (int *) arg);
		return 0;
		
	case SNDCTL_DSP_GETBLKSIZE:
	
		ival = SSP_BUF_SIZE;
		printk("%s : SNDCTL_DSP_GETBLKSIZE(0x%x)\n",__func__,ival);
		return put_user(ival, (int *) arg);
		
  case SNDCTL_DSP_NONBLOCK:
  printk("%s : SNDCTL_DSP_NONBLOCK\n",__func__);
                file->f_flags |= O_NONBLOCK;
                return 0;

  case SNDCTL_DSP_RESET:
  printk("%s : SNDCTL_DSP_RESET\n",__func__);
		if (file->f_mode & FMODE_READ) {
				//audio_reset_buf(is);
		}
		data = READ_GLOBAL_REG(0x0C);
    	data|=0x80000;
    	WRITE_GLOBAL_REG(0x0C,data);
    	//disable dma int
				*((volatile unsigned int *)IRQ_MASK(IO_ADDRESS(SL2312_INTERRUPT_BASE))) &= ~(IRQ_DMA_OFFSET);
				
				WRITE_DMA_REG(DMA_CFG, 0x0); //disable DMA
				WRITE_DMA_REG(DMA_INT_TC_CLR, 0x4);
				
		if (file->f_mode & FMODE_WRITE) {
				i2s_init();
			memset(ssp_i2s.tbuf, 0x00, TBUF_SIZE);
			//memset(ssp_i2s.tbuf, 0x00, TBUF_SIZE);
			ssp_i2s.tol_size = 0; 
			ssp_i2s.wt_size = 0; 
			ssp_i2s.rm_size = 0; 
			ssp_i2s.wt_curr = 0; 
			ssp_i2s.in_curr = 0; 
			ssp_i2s.in_cont = 0;
			ssp_i2s.tx_curr = 0; 
			ssp_i2s.file_len = 0;
			ssp_i2s.in_bufok = 0;
		}
		return 0;

	case SNDCTL_DSP_SETFRAGMENT:
	printk("%s : SNDCTL_DSP_SETFRAGMENT\n",__func__);
		if (get_user(ival, (int *)arg))
			return -EFAULT;
		frag_size = ival & 0xffff;
		frag_buf = (ival>>16) & 0xffff;
		/* TODO: We use hardcoded fragment sizes and numbers for now */
		frag_size = 11;  /* 4096 == 2^12 *///SBUF_SIZE
		frag_buf  = MAX_BUFS;
		ival = (frag_buf << 16) + frag_size;
		return put_user(ival, (int *) arg);
		
	case SNDCTL_DSP_GETOSPACE:
	//printk("%s : SNDCTL_DSP_GETOSPACE \n",__func__);
		if (!(file->f_mode & FMODE_WRITE))
			return -EINVAL;
								info.fragstotal = MAX_BUFS;
                info.fragments = (MAX_BUFS - ssp_i2s.in_cont);
								info.fragsize = SSP_BUF_SIZE;
                info.bytes = info.fragments * info.fragsize;
    //            printk("[%x-%x-%x]\n",info.bytes,info.fragments,ssp_i2s.in_cont);
		return copy_to_user((void *)arg, &info, sizeof(info)) ? -EFAULT : 0;
		//return 0;
		
	case SNDCTL_DSP_GETISPACE:
	printk("%s : SNDCTL_DSP_GETISPACE\n",__func__);
		if (!(file->f_mode & FMODE_READ))
			return -EINVAL;
								info.fragstotal = MAX_BUFS;
                info.fragments = 20;// ssp_i2s.nb_filled_record; /*MAX_BUFS-*/
								info.fragsize = SSP_BUF_SIZE;
                info.bytes = info.fragments * info.fragsize;
		return 0;//copy_to_user((void *)arg, &info, sizeof(info)) ? -EFAULT : 0;
	
	case SNDCTL_DSP_SYNC:
	printk("%s : SNDCTL_DSP_SYNC\n",__func__);
			data = READ_GLOBAL_REG(0x0C);
    	data|=0x80000;
    	WRITE_GLOBAL_REG(0x0C,data);
    	//disable dma int
				*((volatile unsigned int *)IRQ_MASK(IO_ADDRESS(SL2312_INTERRUPT_BASE))) &= ~(IRQ_DMA_OFFSET);
				
				WRITE_DMA_REG(DMA_CFG, 0x0); //disable DMA
				WRITE_DMA_REG(DMA_INT_TC_CLR, 0x4);
		return 0;
	
	case SNDCTL_DSP_SETDUPLEX:
	printk("%s : SNDCTL_DSP_SETDUPLEX\n",__func__);
		return 0;

	case SNDCTL_DSP_POST:
	printk("%s : SNDCTL_DSP_POST\n",__func__);
		return 0;
	
	case SNDCTL_DSP_GETTRIGGER:
	printk("%s : SNDCTL_DSP_GETTRIGGER\n",__func__);
			//PCM_ENABLE_INPUT
			//PCM_ENABLE_OUTPUT
		return 0;
		
	case SNDCTL_DSP_GETOPTR:
	printk("%s : SNDCTL_DSP_GETOPTR \n",__func__);
	
	//int bytecount, offset, flags;
	
	if (!(file->f_mode & FMODE_READ))
			return -EINVAL;
	
			inf.blocks = SSP_BUF_SIZE;
			inf.bytes = ssp_i2s.tol_size;

	return copy_to_user((void *)arg, &inf, sizeof(inf));
	
	case SNDCTL_DSP_GETIPTR:
	printk("%s : SNDCTL_DSP_GETIPTR \n",__func__);
	//count_info inf = { 0, };

	//int bytecount, offset, flags;
	
	if (!(file->f_mode & FMODE_READ))
			return -EINVAL;
	
			inf.blocks = SSP_BUF_SIZE;
			inf.bytes = ssp_i2s.tol_size;
	return copy_to_user((void *)arg, &inf, sizeof(inf));
			
	case SOUND_PCM_READ_BITS:
	printk("%s : SOUND_PCM_READ_BITS\n",__func__);
		return 0;
		
	case SOUND_PCM_READ_FILTER:
	printk("%s : SOUND_PCM_READ_FILTER\n",__func__);
		return 0;
		
	case SNDCTL_DSP_SUBDIVIDE:
	printk("%s : SNDCTL_DSP_SUBDIVIDE\n",__func__);
		return 0;
		
	case SNDCTL_DSP_SETTRIGGER:
	printk("%s : SNDCTL_DSP_SETTRIGGER\n",__func__);
		return 0;
		
	case SNDCTL_DSP_SETSYNCRO:
	printk("%s : SNDCTL_DSP_SETSYNCRO\n",__func__);
		return 0;
		
	case SNDCTL_DSP_MAPINBUF:
	printk("%s : SNDCTL_DSP_MAPINBUF\n",__func__);
		return 0;
		
	case SNDCTL_DSP_MAPOUTBUF:
	printk("%s : SNDCTL_DSP_MAPOUTBUF\n",__func__);
		return 0;
		
	}
	
	return -EINVAL;
}

static int gemini_i2s_dma(void)
{
	
	int  written = 0;//, opcode, j=0,i;
		
	
	*((volatile unsigned int *)IRQ_MASK(IO_ADDRESS(SL2312_INTERRUPT_BASE))) |= (unsigned int)(IRQ_DMA_OFFSET);
		WRITE_DMA_REG(DMA_INT_TC_CLR, 0x4);

		WRITE_DMA_REG(DMA_CFG, 0x1); //enable DMA
	WRITE_DMA_REG(DMA_SYNC, 0x4);
	

				printk("play(FMT(%d) stereo(%d) speed(%d) \n",ssp_i2s.data_format,ssp_i2s.stereo_select,ssp_i2s.sample_rate);
			
			
			//DMA Channel 2 & 3 int mask
				WRITE_DMA_REG(DMA_CH2_CFG, 0);
			
		    	
			//DMA Channel 2 for transmit
			WRITE_DMA_REG(DMA_CH2_SRC_ADDR, __pa(ssp_i2s.tbuf));//dbuf); //src_address
			WRITE_DMA_REG(DMA_CH2_DST_ADDR, SL2312_SSP_CTRL_BASE+SSP_WRITE_PORT); //dest_address
			//WRITE_DMA_REG(DMA_CH2_LLP, (((UINT32)&ssp_i2s.desc_tx[i].LLPT[0]))|0x1); //LLP
			WRITE_DMA_REG(DMA_CH2_LLP, __pa(((UINT32)&ssp_i2s.LLPT[0]))|0x1); //LLP
			//WRITE_DMA_REG(DMA_CH2_SIZE, SBUF_SIZE/4); //size 32bit DMA
			WRITE_DMA_REG(DMA_CH2_SIZE, (ssp_i2s.LLPT[0].ctrl_size&0xffff)); //size 32bit DMA
			ssp_i2s.tx_curr = ssp_i2s.LLPT[0].src_addr;
			ssp_i2s.tx_start = ssp_i2s.LLPT[0].src_addr;
			WRITE_DMA_REG(DMA_CH2_CSR, 0x00001095); //CSR
			//WRITE_SSP_REG(SSP_CTRL_STATUS,0x1FF);		
			//WRITE_SSP_REG(SSP_CTRL_STATUS,0xC0100000);
	printk("%s :<--\n",__func__);
	//cs4341_init();
	//cs4341_setlevel(ssp_i2s.level>>0x08, ssp_i2s.level&0xff);
	return written;

				
}

int ssp_i2s_alloc(void)
{
	int  j;
	
	printk("Buffer allocation for SSP!\n");
	

		ssp_i2s.tbuf = kmalloc(TBUF_SIZE, GFP_ATOMIC|GFP_DMA);
	  

		if (!ssp_i2s.tbuf) {
			printk("Buffer allocation for failed!\n");
			return -ENOMEM;
		}
			ssp_i2s.LinkAddrT = (UINT32 *)kmalloc(sizeof(DMA_LLP_t) * LLP_SIZE, GFP_ATOMIC);
  		ssp_i2s.LLPT = (DMA_LLP_t *)ssp_i2s.LinkAddrT;
  		
  		for(j=0;j<LLP_SIZE;j++)//Tx
  		{
  			ssp_i2s.LLPT[j].src_addr = __pa((UINT32)ssp_i2s.tbuf + ((j%LLP_SIZE) * SBUF_SIZE));	
  			ssp_i2s.LLPT[j].dst_addr = SL2312_SSP_CTRL_BASE+SSP_WRITE_PORT;
  			ssp_i2s.LLPT[j].llp = __pa(((UINT32)&ssp_i2s.LLPT[((j+1)%LLP_SIZE)]))|0x1;
#if (DEF_16_BIT==1)		  			
  			ssp_i2s.LLPT[j].ctrl_size = ((SBUF_SIZE/4)|(0x040a<<16));//0x140a<<16;    //tx:100a rx:1021
#else
				ssp_i2s.LLPT[j].ctrl_size = (((SBUF_SIZE/4)/2)|(0x040a<<16));//0x140a<<16;    //tx:100a rx:1021
#endif  			
  		}
			//if need one time copy from user by write function
			//ssp_i2s.wbuf = kmalloc(TBUF_SIZE, GFP_ATOMIC);
			//if (!ssp_i2s.wbuf) {
			//printk("Buffer(wbuf) allocation for failed!\n");
			//return -ENOMEM;
			//}

  		return 0;
}



static struct file_operations ssp_i2s_dsp_fops =
{
	.owner		=	THIS_MODULE,
	.ioctl		=	ssp_i2s_dsp_ioctl,
	.open		=	ssp_i2s_dsp_open,
	.release	=	ssp_i2s_dsp_release,
	.write	= ssp_i2s_dsp_write,
};

static struct file_operations ssp_i2s_mixer_fops =
{
	.owner		=	THIS_MODULE,
	.ioctl		=	ssp_i2s_mixer_ioctl,
	.open		=	ssp_i2s_mixer_open,
	.release	=	ssp_i2s_mixer_release,
	//.write	= ssp_i2s_mixer_write,
};



int __init init_storm_ssp(void)
{
	
	UINT32  retval;
	UINT32  regs;		

	/* register devices */
	audio_dev_id = register_sound_dsp(&ssp_i2s_dsp_fops, -1);
	mixer_dev_id = register_sound_mixer(&ssp_i2s_mixer_fops, -1);

	printk("Stoem I2S of SSP Initialization(dsp)\n");
	
	ssp_i2s_alloc();
	i2s_init();
	
	
	retval = request_irq(IRQ_DMA_OFFSET, ssp_i2s_interrupt, SA_INTERRUPT, "dma", NULL);
	if (retval)
	{
		printk (KERN_CRIT "Wow!  Can't register IRQ for DMA\n");
		//return retval;
	}
        /* setup interrupt controller  */ 
        regs = *((volatile unsigned int *)IRQ_TMODE(IO_ADDRESS(SL2312_INTERRUPT_BASE)));
        regs &= ~(IRQ_DMA_OFFSET);
        *((volatile unsigned int *)IRQ_TMODE(IO_ADDRESS(SL2312_INTERRUPT_BASE))) = regs;
        regs = *((volatile unsigned int *)IRQ_TLEVEL(IO_ADDRESS(SL2312_INTERRUPT_BASE)));
        regs &= ~(IRQ_DMA_OFFSET);
        *((volatile unsigned int *)IRQ_TLEVEL(IO_ADDRESS(SL2312_INTERRUPT_BASE))) = regs;
        //*((volatile unsigned int *)IRQ_MASK(IO_ADDRESS(SL2312_INTERRUPT_BASE))) |= (unsigned int)(IRQ_DMA_OFFSET);

#if 0
		retval = request_irq(IRQ_SSP_OFFSET, ssp_interrupt, SA_INTERRUPT, "ssp", NULL);
	if (retval)
	{
		printk (KERN_CRIT "Wow!  Can't register IRQ for SSP\n");
		//return retval;
	}
				// init ssp int 			
				regs = *((volatile unsigned int *)IRQ_TMODE(IO_ADDRESS(SL2312_INTERRUPT_BASE)));
        regs &= ~(IRQ_SSP_OFFSET);
        *((volatile unsigned int *)IRQ_TMODE(IO_ADDRESS(SL2312_INTERRUPT_BASE))) = regs;
        regs = *((volatile unsigned int *)IRQ_TLEVEL(IO_ADDRESS(SL2312_INTERRUPT_BASE)));
        regs &= ~(IRQ_SSP_OFFSET);
        *((volatile unsigned int *)IRQ_TLEVEL(IO_ADDRESS(SL2312_INTERRUPT_BASE))) = regs;
#endif
	
#ifdef CONFIG_SL3516_ASIC
	//retval = request_gpio_irq(0,gemini_slic_i2s_isr,1,1,0);//SSP_GPIO_INT_BIT = 0x400 -> bit 10
#else	
	//retval = request_gpio_irq(10,gemini_slic_i2s_isr,1,1,0);//SSP_GPIO_INT_BIT = 0x400 -> bit 10
#endif	
	if (retval)
		printk("SSP interrupt init error.\n");
        

	return 0;
		
}

void __exit cleanup_storm_ssp(void)
{
printk("Stoem I2S of SSP cleanup(dsp)\n");
	unregister_sound_dsp(audio_dev_id);
	unregister_sound_mixer(mixer_dev_id);

		WRITE_DMA_REG(DMA_CFG, 0x0); //disable DMA
				WRITE_DMA_REG(DMA_INT_TC_CLR, 0x4);
				
		*((volatile unsigned int *)IRQ_MASK(IO_ADDRESS(SL2312_INTERRUPT_BASE))) &= ~(IRQ_DMA_OFFSET);
				
				free_irq(IRQ_DMA_OFFSET, NULL);
								
				if(ssp_i2s.tbuf)
					kfree(ssp_i2s.tbuf);
				if(ssp_i2s.LinkAddrT)
				{
					kfree(ssp_i2s.LinkAddrT);
					ssp_i2s.LLPT = 0;
				}	
				//if need one time copy from user by write function
				//if(ssp_i2s.tbuf)
				//	kfree(ssp_i2s.wbuf);
				
	return;
}   
 
module_init(init_storm_ssp);
module_exit(cleanup_storm_ssp);

MODULE_AUTHOR("Middle Huang <middle@stormsemi.com>");
MODULE_DESCRIPTION("Storm ssp i2s driver");
MODULE_LICENSE("GPL");


