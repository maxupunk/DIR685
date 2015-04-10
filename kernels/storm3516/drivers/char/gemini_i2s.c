/*
 * FILE NAME gemini_i2s.c
 *
 * BRIEF MODULE DESCRIPTION
 *  Driver for CIR device.
 *
 *  Author: StorLink, Corp.
 *          Middle Huang
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
#include <linux/pci.h> 
#include <asm/hardware.h>
#include <asm/io.h>
#include <asm/delay.h>
#include <linux/signal.h>
#include <asm/arch/gemini_i2s.h>
#include <asm/arch/gemini_gpio.h>

//IRQ_DMA_OFFSET  -> int_ctrl.h
// mknod /dev/sspi2s c 10 244

#ifndef I2S_MINOR
#define I2S_MINOR	244		// Documents/devices.txt suggest to use 240~255 for local driver!!
#endif

//wait_queue_head_t ssp_wait_q;
//#ifdef MIDWAY_DIAG
//#define DMA_CONTROL_SSP_BASE  SL2312_SSP_CTRL_BASE
#define LLP_SIZE   60//1536
#define SBUF_SIZE  2048//1024 
#define TBUF_SIZE  (LLP_SIZE)*SBUF_SIZE
#define I2S_CPU	0
#define I2S_DMA 1

//#define IRQ_DMA_OFFSET (1<<IRQ_DMA)
#define	DEF_16_BIT	1

typedef struct {
	unsigned int tol_size, wt_size, rm_size;
	UINT32 *LinkAddrT;
  DMA_LLP_t *LLPT;
  UINT32 *WtAddrT;
  IOCTL_LLP_t *WLLPT;
  unsigned int wt_curr,tx_curr;
  unsigned int in_curr, in_cont, in_bufok;
  char  *tbuf, *wbuf;
  unsigned char  *in_ptr;
  unsigned int file_len;
	
}SSP_I2S;

static SSP_I2S ssp_i2s;
static int gemini_i2s_dma(void);
int __init ssp_i2s_init(void);

int ssp_i2s_alloc(void);

#ifdef CONFIG_SL3516_ASIC
unsigned int GPIO_EECK;	    
unsigned int GPIO_EECS;    
unsigned int GPIO_MISO;	                             
unsigned int GPIO_MOSI;	                         
unsigned int GPIO_MISO_BIT;	
#endif

static void gemini_slic_i2s_isr (int irq)
{

}

void i2s_init(void)
{
	
		UINT32 addr,value, j;
	//unsigned int *base;
    unsigned int data=0,tmp;
#ifdef CONFIG_SL3516_ASIC
		data = READ_GLOBAL_REG(0x0);
		if((data&0x00FFFF00)==0x351600)
		{
				GPIO_EECK	 =    0x80000000;         /*   SCK: GPIO1[31]   */
				GPIO_EECS	 =    0x40000000;			/*   SCS: GPIO1[30]   */
				GPIO_MISO	 =    0x20000000;         /*   SDO: GPIO1[29]   receive from 6996*/                         
				GPIO_MOSI	 =    0x10000000;         /*   SDI: GPIO1[28]   send to 6996*/                          
				GPIO_MISO_BIT	= 29;	
		}
		else
		{
				GPIO_EECK	 =    0x00000100;         /*   SCK: GPIO1[08]   */
				GPIO_EECS	 =    0x08000000;			/*   SCS: GPIO1[27]   */
				GPIO_MISO	 =    0x00000080;         /*   SDO: GPIO1[07]   receive from 6996*/                         
				GPIO_MOSI	 =    0x00000200;        /*   SDI: GPIO1[09]   send to 6996*/                          
				GPIO_MISO_BIT	= 7	;
	}
    	
			data = READ_GLOBAL_REG(0x0C);
    	data|=0x80000;
    	WRITE_GLOBAL_REG(0x0C,data);
		
    	data = READ_GLOBAL_REG(0x30);
    
    	data|=0x100;
    	tmp = READ_GLOBAL_REG(0x0);
			if((tmp&0x00FFFF00)==0x351600)
    			data&=0xfffeffbf;//for 3516
    	else
    			data&=0xfffeffaf;//for 3512 //need to disable IDE pad
    	WRITE_GLOBAL_REG(0x30,data);
    
    	
   	addr = (unsigned int )(GPIO_BASE_ADDR1 + GPIO_DATA_OUT);
	value = GPIO_EECS |GPIO_EECK|GPIO_MOSI;;
	/////////*addr = value ;
	writel(value,addr);	
	addr = (unsigned int )(GPIO_BASE_ADDR1 + GPIO_PIN_DIR);
	value = readl(addr);
	//*addr = value ;
	//writel(value,addr);	
	value |= GPIO_EECS |GPIO_EECK|GPIO_MOSI;//(~GPIO_MISO);//|(~SSP_GPIO_INT_BIT) ;   // set EECS/EECK Pin to output 
	//*addr = value ;
	writel(value,addr);		
	
	WRITE_SSP_REG(SSP_FRAME_CTRL, 0x25020003 ); //0x04010030//ext clk : bit17
  	WRITE_SSP_REG(SSP_BAUD_RATE, 0x01000100);
#else
	addr = (unsigned int )(GPIO_BASE_ADDR + GPIO_DATA_OUT);
	value = 0xFFFFFFFF;
	//*addr = value ;
	writel(value,addr);	
	addr = (unsigned int )(GPIO_BASE_ADDR + GPIO_PIN_DIR);
	value = 0x0;
	//*addr = value ;
	writel(value,addr);	
	value = GPIO_EECS |GPIO_EECK|GPIO_MOSI;//(~GPIO_MISO);//|(~SSP_GPIO_INT_BIT) ;   // set EECS/EECK Pin to output 
	//*addr = value ;
	writel(value,addr);		
	
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
  				WRITE_SSP_REG(SSP_CTRL_STATUS, 0x1F100000);//0x9F100000
  				mdelay(250);
  				WRITE_SSP_REG(SSP_CTRL_STATUS, 0x00100000);//0x80100000

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
			for(j=0;j<LLP_SIZE;j++)//Tx
  		{
  			ssp_i2s.LLPT[j].src_addr = __pa((UINT32)ssp_i2s.tbuf + ((j%LLP_SIZE) * SBUF_SIZE));	
  			ssp_i2s.LLPT[j].dst_addr = SL2312_SSP_CTRL_BASE+SSP_WRITE_PORT;
  			ssp_i2s.LLPT[j].llp = __pa(((UINT32)&ssp_i2s.LLPT[((j+1)%LLP_SIZE)]))|0x1;
#if (DEF_16_BIT==1)		  			
  			ssp_i2s.LLPT[j].ctrl_size = (SBUF_SIZE/4)|0x040a<<16;//0x140a<<16;    //tx:100a rx:1021
#else
				ssp_i2s.LLPT[j].ctrl_size = ((SBUF_SIZE/4)/2)|0x040a<<16;//0x140a<<16;    //tx:100a rx:1021
#endif  
  		}
  		
  			for(j=0;j<LLP_SIZE;j++)//Tx
  			{
  				ssp_i2s.WLLPT[j].owner = I2S_CPU;
  				ssp_i2s.WLLPT[j].src_addr = __pa((UINT32)ssp_i2s.wbuf + ((j%LLP_SIZE) * SBUF_SIZE));	
  				//ssp_i2s.WLLPT[j].ctrl_size = (SBUF_SIZE/4);//|0x040a<<16;//0x140a<<16;    //tx:100a rx:1021
  			}

}

static int ssp_i2s_open(struct inode *inode, struct file *file)
{

				
				WRITE_DMA_REG(DMA_CFG, 0x0); //disable DMA
				WRITE_DMA_REG(DMA_INT_TC_CLR, 0x4);
	return 0;
}


static int ssp_i2s_release(struct inode *inode, struct file *file)
{
				*((volatile unsigned int *)IRQ_MASK(IO_ADDRESS(SL2312_INTERRUPT_BASE))) &= ~(IRQ_DMA_OFFSET);
				
				
				WRITE_DMA_REG(DMA_CFG, 0x0); //disable DMA
				WRITE_DMA_REG(DMA_INT_TC_CLR, 0x4);
				
	return 0;
}

static irqreturn_t ssp_i2s_interrupt(int irq, void *dev_instance, struct pt_regs *regs)
{
	int                     tmp, j;
	unsigned char *tp, *tmp_ptr;
	unsigned int opcode, old_opcode;
	
	disable_irq(irq);   /* disable  interrupt */
	tmp=READ_DMA_REG(DMA_INT_TC); 
			if((tmp&0x04)==0x04)//tc
			{
				ssp_i2s.tx_curr ++ ;
				ssp_i2s.wt_curr = ((ssp_i2s.tx_curr - 1)%LLP_SIZE);
#if (DEF_16_BIT==1)		  							
				//memcpy(__va(ssp_i2s.LLPT[ssp_i2s.wt_curr].src_addr), (ssp_i2s.wbuf+((ssp_i2s.wt_curr%LLP_SIZE) * SBUF_SIZE)), SBUF_SIZE);	
				memcpy(__va(ssp_i2s.LLPT[ssp_i2s.wt_curr].src_addr), __va(ssp_i2s.WLLPT[ssp_i2s.wt_curr].src_addr), SBUF_SIZE);	
				consistent_sync(__va(ssp_i2s.LLPT[ssp_i2s.wt_curr].src_addr),SBUF_SIZE, DMA_BIDIRECTIONAL);				
				
				if(ssp_i2s.WLLPT[ssp_i2s.wt_curr].ctrl_size < SBUF_SIZE)
					ssp_i2s.LLPT[ssp_i2s.wt_curr].llp = 0; 
#else
						//tp = __va(ssp_i2s.WLLPT[ssp_i2s.wt_curr].src_addr);	
						//tmp_ptr = __va(ssp_i2s.LLPT[ssp_i2s.wt_curr].src_addr);
						//memset(tmp_ptr, 0 ,SBUF_SIZE);
						//for(j=0;j<(SBUF_SIZE/2);j++)
						//{                                     
						//	if(((*(tp+(2*j)+1))&0x01)==0x01)
						//		*(tmp_ptr+j) = ((*(tp+(2*j)+1))&0xFE);
						//	else                                    
						//		*(tmp_ptr+j) = ((*(tp+(2*j)+1))|0x01);
						//}
				memcpy(__va(ssp_i2s.LLPT[ssp_i2s.wt_curr].src_addr), __va(ssp_i2s.WLLPT[ssp_i2s.wt_curr].src_addr), SBUF_SIZE);	
				consistent_sync(__va(ssp_i2s.LLPT[ssp_i2s.wt_curr].src_addr),SBUF_SIZE, DMA_BIDIRECTIONAL);				
				
				if(ssp_i2s.WLLPT[ssp_i2s.wt_curr].ctrl_size < SBUF_SIZE)
					ssp_i2s.LLPT[ssp_i2s.wt_curr].llp = 0; 
#endif				
				opcode=READ_DMA_REG(DMA_CH2_CFG);
				opcode>>=16;
				//printk(" [%d] - cnt: %x ",ssp_i2s.in_cont,opcode);
				ssp_i2s.in_cont--;
				if(ssp_i2s.in_cont < 0)
					ssp_i2s.in_cont =0;
			}
	WRITE_DMA_REG(DMA_INT_TC_CLR, (tmp&0x04));		
	enable_irq(irq);
	
		opcode = *((volatile unsigned int *)(IO_ADDRESS(SL2312_INTERRUPT_BASE+0x04)));
        if((opcode&0x00c40000)==0x00c40000)
        	 		old_opcode = opcode;
        else
        	*((volatile unsigned int *)(IO_ADDRESS(SL2312_INTERRUPT_BASE+0x04))) = old_opcode;
	//wake_up_interruptible(&ssp_wait_q);
	return IRQ_RETVAL(IRQ_HANDLED);
}

static ssize_t ssp_i2s_write(struct file *file_p, const char __user *buf, size_t count, loff_t * ppos)
{
	int ofs=0, written = 0, i=0, len=0, j=0;
	unsigned char tmp[SBUF_SIZE], *tmp_ptr;
	
			written = count / SBUF_SIZE;
			ofs = count % SBUF_SIZE;
//			typedef struct {
//	unsigned int tol_size, wt_size, rm_size;
//	UINT32 *LinkAddrT;
//  DMA_LLP_t *LLPT;
//  int wt_curr,tx_curr;
//  int in_curr;
//    char  *tbuf, *wbuf;
//    unsigned char  *in_ptr;
//	
//}SSP_I2S;
//ssp_i2s.WLLPT[j].owner = I2S_CPU;
//  				ssp_i2s.WLLPT[j].src_addr = (UINT32)ssp_i2s.wbuf + (((j)%LLP_SIZE) * SBUF_SIZE);
  				
		if(ssp_i2s.in_bufok == 0)
		{
#if (DEF_16_BIT==1)					
				for(i=0;i<written;i++)
				{
						copy_from_user(tmp, (buf+i*SBUF_SIZE), SBUF_SIZE);
						tmp_ptr = __va(ssp_i2s.WLLPT[ssp_i2s.in_curr].src_addr); //(ssp_i2s.wbuf+((ssp_i2s.in_curr%LLP_SIZE) * SBUF_SIZE));
						for(j=0;j<SBUF_SIZE;j+=2)
						{
							*(tmp_ptr+j) = *(tmp+j+1);
							*(tmp_ptr+j+1) = *(tmp+j);
						}
						//ssp_i2s.WLLPT[ssp_i2s.in_curr].owner = I2S_DMA;
						ssp_i2s.WLLPT[ssp_i2s.in_curr].ctrl_size = SBUF_SIZE;
						len+=SBUF_SIZE;
						ssp_i2s.in_curr++;
						ssp_i2s.in_cont++;
				}	
				if(ofs)
				{
						memset((ssp_i2s.wbuf+((ssp_i2s.in_curr%LLP_SIZE) * SBUF_SIZE)), 0x0, SBUF_SIZE);
						copy_from_user(tmp, (buf+i*SBUF_SIZE), ofs);
						tmp_ptr = __va(ssp_i2s.WLLPT[ssp_i2s.in_curr].src_addr); //(ssp_i2s.wbuf+((ssp_i2s.in_curr%LLP_SIZE) * SBUF_SIZE));
						for(j=0;j<ofs;j+=2)
						{
							*(tmp_ptr+j) = *(tmp+j+1);
							*(tmp_ptr+j+1) = *(tmp+j);
						}
						//ssp_i2s.WLLPT[ssp_i2s.in_curr].owner = I2S_DMA;
						ssp_i2s.WLLPT[ssp_i2s.in_curr].ctrl_size = ofs;
						len+=ofs;
						ssp_i2s.in_curr++;
						ssp_i2s.in_cont++;
				}
#else
				for(i=0;i<written;i++)
				{
						copy_from_user(tmp, (buf+i*SBUF_SIZE), SBUF_SIZE);
						tmp_ptr = __va(ssp_i2s.WLLPT[ssp_i2s.in_curr].src_addr); //(ssp_i2s.wbuf+((ssp_i2s.in_curr%LLP_SIZE) * SBUF_SIZE));
						for(j=0;j<(SBUF_SIZE/2);j++)
						{
							*(tmp_ptr+j) = *(tmp+(2*j)+1);
						}
						//ssp_i2s.WLLPT[ssp_i2s.in_curr].owner = I2S_DMA;
						ssp_i2s.WLLPT[ssp_i2s.in_curr].ctrl_size = SBUF_SIZE;
						len+=SBUF_SIZE;
						ssp_i2s.in_curr++;
						ssp_i2s.in_cont++;
				}	
				if(ofs)
				{
						memset((ssp_i2s.wbuf+((ssp_i2s.in_curr%LLP_SIZE) * SBUF_SIZE)), 0x0, SBUF_SIZE);
						copy_from_user(tmp, (buf+i*SBUF_SIZE), ofs);
						tmp_ptr = __va(ssp_i2s.WLLPT[ssp_i2s.in_curr].src_addr); //(ssp_i2s.wbuf+((ssp_i2s.in_curr%LLP_SIZE) * SBUF_SIZE));
						for(j=0;j<((ofs+1)/2);j++)
						{
							*(tmp_ptr+j) = *(tmp+(2*j)+1);
						}
						//ssp_i2s.WLLPT[ssp_i2s.in_curr].owner = I2S_DMA;
						ssp_i2s.WLLPT[ssp_i2s.in_curr].ctrl_size = ofs;
						len+=ofs;
						ssp_i2s.in_curr++;
						ssp_i2s.in_cont++;
				}
							
#endif					
			if(ssp_i2s.in_curr == LLP_SIZE)
			{
					ssp_i2s.in_curr %= LLP_SIZE;
					ssp_i2s.in_bufok = 1;
					
					gemini_i2s_dma();
					printk("i2s Start DMA .......(%d)\n",ssp_i2s.in_curr);
			}
			
		}
		else
		{
			if(ssp_i2s.in_cont<LLP_SIZE)
			{
#if (DEF_16_BIT==1)					
				for(i=0;i<written;i++)
				{
						copy_from_user(tmp, (buf+i*SBUF_SIZE), SBUF_SIZE);
						tmp_ptr = __va(ssp_i2s.WLLPT[ssp_i2s.in_curr].src_addr); //(ssp_i2s.wbuf+((ssp_i2s.in_curr%LLP_SIZE) * SBUF_SIZE));
						for(j=0;j<SBUF_SIZE;j+=2)
						{
							*(tmp_ptr+j) = *(tmp+j+1);
							*(tmp_ptr+j+1) = *(tmp+j);
						}
						//ssp_i2s.WLLPT[ssp_i2s.in_curr].owner = I2S_DMA;
						ssp_i2s.WLLPT[ssp_i2s.in_curr].ctrl_size = SBUF_SIZE;
						len+=SBUF_SIZE;
						ssp_i2s.in_curr++;
						ssp_i2s.in_curr %= LLP_SIZE;
						ssp_i2s.in_cont++;
				}	
				if(ofs)
				{
						memset((ssp_i2s.wbuf+((ssp_i2s.in_curr%LLP_SIZE) * SBUF_SIZE)), 0x0, SBUF_SIZE);
						copy_from_user(tmp, (buf+i*SBUF_SIZE), ofs);
						tmp_ptr = __va(ssp_i2s.WLLPT[ssp_i2s.in_curr].src_addr); //(ssp_i2s.wbuf+((ssp_i2s.in_curr%LLP_SIZE) * SBUF_SIZE));
						for(j=0;j<ofs;j+=2)
						{
							*(tmp_ptr+j) = *(tmp+j+1);
							*(tmp_ptr+j+1) = *(tmp+j);
						}
						//ssp_i2s.WLLPT[ssp_i2s.in_curr].owner = I2S_DMA;
						ssp_i2s.WLLPT[ssp_i2s.in_curr].ctrl_size = ofs;
						len+=ofs;
						ssp_i2s.in_curr++;
						ssp_i2s.in_curr %= LLP_SIZE;
						ssp_i2s.in_cont++;
				}
			
#else

				for(i=0;i<written;i++)
				{
						copy_from_user(tmp, (buf+i*SBUF_SIZE), SBUF_SIZE);
						tmp_ptr = __va(ssp_i2s.WLLPT[ssp_i2s.in_curr].src_addr); //(ssp_i2s.wbuf+((ssp_i2s.in_curr%LLP_SIZE) * SBUF_SIZE));
						for(j=0;j<(SBUF_SIZE/2);j++)
						{
							*(tmp_ptr+j) = *(tmp+(2*j)+1);
							
						}
						//ssp_i2s.WLLPT[ssp_i2s.in_curr].owner = I2S_DMA;
						ssp_i2s.WLLPT[ssp_i2s.in_curr].ctrl_size = SBUF_SIZE;
						len+=SBUF_SIZE;
						ssp_i2s.in_curr++;
						ssp_i2s.in_curr %= LLP_SIZE;
						ssp_i2s.in_cont++;
				}	
				if(ofs)
				{
						memset((ssp_i2s.wbuf+((ssp_i2s.in_curr%LLP_SIZE) * SBUF_SIZE)), 0x0, SBUF_SIZE);
						copy_from_user(tmp, (buf+i*SBUF_SIZE), ofs);
						tmp_ptr = __va(ssp_i2s.WLLPT[ssp_i2s.in_curr].src_addr); //(ssp_i2s.wbuf+((ssp_i2s.in_curr%LLP_SIZE) * SBUF_SIZE));
						for(j=0;j<((ofs+1)/2);j++)
						{
							*(tmp_ptr+j) = *(tmp+(2*j)+1);
						}
						//ssp_i2s.WLLPT[ssp_i2s.in_curr].owner = I2S_DMA;
						ssp_i2s.WLLPT[ssp_i2s.in_curr].ctrl_size = ofs;
						len+=ofs;
						ssp_i2s.in_curr++;
						ssp_i2s.in_curr %= LLP_SIZE;
						ssp_i2s.in_cont++;
				}
			
#endif				
			}//if(ssp_i2s.in_cont<LLP_SIZE)
		}//else
			return len;
}

static int ssp_i2s_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
{
	int ret = 0, value, j;
		unsigned int data;

	switch(cmd) {
		case SSP_I2S_INIT_BUF:
				i2s_init();
			memset(ssp_i2s.tbuf, 0x00, TBUF_SIZE);
			memset(ssp_i2s.wbuf, 0x00, TBUF_SIZE);
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
		default:
			return -1;
	}
	return ret; 
}

static int gemini_i2s_dma(void)
{
	
	int  written = 0;//, opcode, j=0,i;
		
	*((volatile unsigned int *)IRQ_MASK(IO_ADDRESS(SL2312_INTERRUPT_BASE))) |= (unsigned int)(IRQ_DMA_OFFSET);
		WRITE_DMA_REG(DMA_INT_TC_CLR, 0x4);

		WRITE_DMA_REG(DMA_CFG, 0x1); //enable DMA
	WRITE_DMA_REG(DMA_SYNC, 0x4);
	

				
			
			
			//DMA Channel 2 & 3 int mask
				WRITE_DMA_REG(DMA_CH2_CFG, 0);
			
		    	
			//DMA Channel 2 for transmit
			WRITE_DMA_REG(DMA_CH2_SRC_ADDR, __pa(ssp_i2s.tbuf));//dbuf); //src_address
			WRITE_DMA_REG(DMA_CH2_DST_ADDR, SL2312_SSP_CTRL_BASE+SSP_WRITE_PORT); //dest_address
			//WRITE_DMA_REG(DMA_CH2_LLP, (((UINT32)&ssp_i2s.desc_tx[i].LLPT[0]))|0x1); //LLP
			WRITE_DMA_REG(DMA_CH2_LLP, __pa(((UINT32)&ssp_i2s.LLPT[0]))|0x1); //LLP
			WRITE_DMA_REG(DMA_CH2_SIZE, SBUF_SIZE/4); //size 32bit DMA

			WRITE_DMA_REG(DMA_CH2_CSR, 0x00001095); //CSR
			WRITE_SSP_REG(SSP_CTRL_STATUS,0x1FF);		
			WRITE_SSP_REG(SSP_CTRL_STATUS,0xC0100000);
	printk("%s :<--\n",__func__);
	return written;

				
}

static struct file_operations ssp_i2s_fops =
{
	.owner		=	THIS_MODULE,
	.ioctl		=	ssp_i2s_ioctl,
	.open		=	ssp_i2s_open,
	.release	=	ssp_i2s_release,
	.write	= ssp_i2s_write,
};

/* include/linux/miscdevice.h */
static struct miscdevice ssp_i2s_miscdev =
{
	I2S_MINOR,
	"ssp_i2s",
	&ssp_i2s_fops
};

int ssp_i2s_alloc(void)
{
	int  j;
	
	printk("Buffer allocation for SSP!\n");
	

		ssp_i2s.tbuf = kmalloc(TBUF_SIZE, GFP_ATOMIC);
		ssp_i2s.wbuf = kmalloc(TBUF_SIZE, GFP_ATOMIC);

		if (!ssp_i2s.tbuf||!ssp_i2s.wbuf) {
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
  			ssp_i2s.LLPT[j].ctrl_size = (SBUF_SIZE/4)|0x040a<<16;//0x140a<<16;    //tx:100a rx:1021
#else
				ssp_i2s.LLPT[j].ctrl_size = ((SBUF_SIZE/4)/2)|0x040a<<16;//0x140a<<16;    //tx:100a rx:1021
#endif  			
  		}
  		//printk("\n");
			//	for(j=0;j<LLP_SIZE;j++)//Tx
			//	{
			//		printk("ssp_i2s.LLPT[%d].src_addr: %x %x %x %x \n",j,ssp_i2s.LLPT[j].src_addr,ssp_i2s.LLPT[j].dst_addr,ssp_i2s.LLPT[j].llp,ssp_i2s.LLPT[j].ctrl_size);
			//	}
			
			ssp_i2s.WtAddrT = (UINT32 *)kmalloc(sizeof(IOCTL_LLP_t) * LLP_SIZE, GFP_ATOMIC);
		
			if (!ssp_i2s.WtAddrT) {
				printk("%s : Tx Buffer Desc allocation for failed!\n",__func__);
				return -1;
			}
			ssp_i2s.WLLPT = (IOCTL_LLP_t *)ssp_i2s.WtAddrT;
				for(j=0;j<LLP_SIZE;j++)//Tx
  			{
  				ssp_i2s.WLLPT[j].owner = I2S_CPU;
  				ssp_i2s.WLLPT[j].src_addr = __pa((UINT32)ssp_i2s.wbuf + ((j%LLP_SIZE) * SBUF_SIZE));	
  				//ssp_i2s.WLLPT[j].ctrl_size = (SBUF_SIZE/4);//|0x040a<<16;//0x140a<<16;    //tx:100a rx:1021
  			}
				//printk("\n");
				//for(j=0;j<LLP_SIZE;j++)//Tx
				//{
				//	printk("ssp_i2s.WLLPT[%d].src_addr: %x %x \n",j,ssp_i2s.WLLPT[j].src_addr,ssp_i2s.WLLPT[j].ctrl_size);
				//}

  		return 0;
}

int __init ssp_i2s_init(void)
{
//	unsigned int reg_v;
	
	UINT32  retval;
	UINT32  regs;		
	misc_register(&ssp_i2s_miscdev);
	printk("Storlink I2S of SSP Initialization\n");
	
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

	
#ifdef CONFIG_SL3516_ASIC
	retval = request_gpio_irq(0,gemini_slic_i2s_isr,1,1,0);//SSP_GPIO_INT_BIT = 0x400 -> bit 10
#else	
	retval = request_gpio_irq(10,gemini_slic_i2s_isr,1,1,0);//SSP_GPIO_INT_BIT = 0x400 -> bit 10
#endif	
	if (retval)
		printk("SSP interrupt init error.\n");
        
	//init_waitqueue_head(&ssp_wait_q);
	
	return 0;
}	

void __exit ssp_i2s_exit(void)
{
	free_irq(IRQ_DMA_OFFSET,NULL);
	misc_deregister(&ssp_i2s_miscdev);
}

module_init(ssp_i2s_init);
module_exit(ssp_i2s_exit);

MODULE_AUTHOR("Middle Huang <middle@storlinksemi.com>");
MODULE_DESCRIPTION("Gemini i2s of ssp driver");
MODULE_LICENSE("GPL");
