

#include <linux/module.h>

#include <linux/init.h>
#include <linux/sched.h>
#include <linux/kernel.h>	/* printk() */
#include <linux/fs.h>		/* everything... */
#include <linux/errno.h>	/* error codes */
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/ioport.h>
#include <linux/interrupt.h>
//#include <linux/tqueue.h>
#include <linux/proc_fs.h>
#include <linux/poll.h>
#include <linux/timer.h>
#include <linux/delay.h>
#include <asm/irq.h>
#include <linux/pci.h>  
#include <linux/telephony.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <asm/segment.h>
#include <asm/uaccess.h>

#include "proslic.h"
//#include "gemini_ssp.h"
#include <asm/arch/gemini_ssp.h>
#include <asm/arch/gemini_gpio.h>

// mknod /dev/phone0 c 100 0
#define TYPE(dev) (MINOR(dev) >> 4)
#define NUM(dev) (MINOR(dev) & 0xf)
static unsigned int     next_tick =  20;//1 * HZ; //HZ/3;
static void gemini_slic_isr (int irq);
int daisyChain=0;


char  *tbuf, *rbuf;
UINT32 *LinkAddrT,*LinkAddrR;
DMA_LLP_t *LLPT,*LLPR;
int desc_ptrr,desc_ptrt;
int dma_link_on;
pid_t	thr_pid;
wait_queue_head_t   thr_wait;
int time_to_die;
//spinlock_t *ssp_mutex;
static spinlock_t ssp_mutex = SPIN_LOCK_UNLOCKED;	
unsigned long ssp_flags;

typedef struct {
	unsigned int board;
	int readers, writers;
	//char *write_buf, *read_buf;

    wait_queue_head_t poll_q;
    wait_queue_head_t write_q,read_q;
	
	int dma_stop;
	int read_buffer_ready, dtmf_state;
	int read_wait, write_wait;
//	UINT32 *LinkAddrT,*LinkAddrR;
 //   DMA_LLP_t *LLPT,*LLPR;
    int rd_curr, wt_curr, tx_curr, rx_curr, din,dout;
    //char  *tbuf, *rbuf, *cw2tbuf, *cr2rbuf;
    char  *cw2tbuf, *cr2rbuf;

	chipStruct chipData ; /* Represents a proslics state, cached information, and timers */
	Ssp_reg  ssp_reg;
	struct phone_device p;
	//	pid_t	thr_pid;
	//wait_queue_head_t   thr_wait;
	//int time_to_die;
	int link_on;
//	int desc_ptrr,desc_ptrt;
	int wt_buf_ok;
	int tx_rate;
}SSP_SLIC;
static SSP_SLIC ssp_slic[NUMBER_OF_CHAN];
unsigned char init ;// this will indicate if there is a missed interrupt
int dma_demo = DMA_NDEMO;
unsigned char silent[DBUF_SIZE],wtmp[DBUF_SIZE];
unsigned int dp=0; 
unsigned long wT=0, rT=0;
//extern void free_gpio_irq(int bit);
//extern int request_gpio_irq(int bit,void (*handler)(int),char level,char high,char both);
static int gemini_slic_thread (void);//(SSP_SLIC *ssp_slic); 
int gemini_ssp_hookstate(int num);
static int gemini_ssp_dma(void);


#ifdef CONFIG_SL3516_ASIC
unsigned int GPIO_EECK;	    
unsigned int GPIO_EECS;    
unsigned int GPIO_MISO;	                             
unsigned int GPIO_MOSI;	                         
unsigned int GPIO_MISO_BIT;	
#endif

void clearAlarmBits(int num)
{
	
	//printk("\n*****************>  clearAlarmBits\n");
	SLIC_SPI_write(num, PROSLIC_INT2_STATUS_REG,0xFC); //Clear Alarm bits
	//printk("\n<*****************  clearAlarmBits\n");

}

int groundShort(int num)
{ 
	int rc;

	rc= ( (SLIC_SPI_read(num, PROSLIC_TIP_VOLTAGE_SENSE_REG) < 2) || SLIC_SPI_read(num, PROSLIC_RING_VOLTAGE_SENSE_REG) < 2);
		
		if (rc) 
		//printk("\n exception->TIPoRrINGgROUNDsHORT \n");
		exception(num, TIPoRrINGgROUNDsHORT);
		return rc;
}

void callerid( int num)
{
	UINT32 opcode;
	//printk("\n*****************>  callerid\n");
	spin_lock_irqsave(&ssp_mutex, ssp_flags);
	SLIC_SPI_write(num, PROSLIC_INT3_MASK_REG, 0);      //reg 23
	opcode = SLIC_SPI_read(num, PROSLIC_INT3_STATUS_REG);
	SLIC_SPI_write(num, PROSLIC_INT3_STATUS_REG, opcode); //0xff);
//reg 20
	SLIC_SPI_write(num, PROSLIC_INT2_MASK_REG, 0);
     //reg 22
     opcode = SLIC_SPI_read(num, PROSLIC_INT2_STATUS_REG);
	SLIC_SPI_write(num, PROSLIC_INT2_STATUS_REG, opcode);
//reg 19
	SLIC_SPI_write(num, PROSLIC_INT1_MASK_REG, 0);
     //reg 21
     opcode = SLIC_SPI_read(num, PROSLIC_INT1_STATUS_REG);
	SLIC_SPI_write(num, PROSLIC_INT1_STATUS_REG,opcode);
 //reg 18
	   spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
	//sleep (250);  // 250 millisecond spacing between the ringing and the caller id
	mdelay(250);
	//disableOscillators(num);
	
	//if (_winmajor <5) // check for windows NT
	//{
	////	_asm { cli }
	//	sendProSLICID(num);
	////	_asm { sti }
	//}
	
	//else
		sendProSLICID(num);
	
	
 disableOscillators(num);
	   spin_lock_irqsave(&ssp_mutex, ssp_flags);
	//SLIC_SPI_write(num, PROSLIC_INT3_MASK_REG, 0xff);
	SLIC_SPI_write(num, PROSLIC_INT3_MASK_REG, 0x05);
	opcode = SLIC_SPI_read(num, PROSLIC_INT3_STATUS_REG);
	SLIC_SPI_write(num, PROSLIC_INT3_STATUS_REG, opcode);
	
	SLIC_SPI_write(num, PROSLIC_INT2_MASK_REG, 0xff);
	opcode = SLIC_SPI_read(num, PROSLIC_INT2_STATUS_REG);
	SLIC_SPI_write(num, PROSLIC_INT2_STATUS_REG, opcode);
	
	SLIC_SPI_write(num, PROSLIC_INT1_MASK_REG, 0xff);//0x10);//0xff);
	opcode = SLIC_SPI_read(num, PROSLIC_INT1_STATUS_REG);
	SLIC_SPI_write(num, PROSLIC_INT1_STATUS_REG,opcode);
	spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
	//printk("\n<*****************  callerid\n");
}

//Sends the ¨PROSLIC CALLING〃 caller ID to the phone

void sendProSLICID(int num)
{   
	
	static char c ='0', modulo=0;
	
	int i; 
	unsigned char sum;
	//time_t curtime_a;
	char  sztime[10];
	spin_lock_irqsave(&ssp_mutex, ssp_flags);
	memcpy((SSPID2+4),&sztime,8);
	memset (&SSPID2[14], c+(modulo++%10),10);

	
	sum= checkSum(num, SSPID2);
	// printk("sum=%x",sum);
	fskInitialization (num);
	
	//Starting the frame with ¨U〃 0x55 and not sending characters for as many
	//bits as the spacing specification requires will achieve this.
	for ( i=0 ; i<30; i++) fskByte(num,'U'); //'U' = 0x55
	
	//  Wait for an interrupt, then write the next bit.
	for ( i=0 ; i<150 ; i++ ) waitForInterrupt(num);  // wait 180 bits worth
	i=0;
	while  (SSPID2[i] != 0) fskByte(num,SSPID2[i++]);
	fskByte(num, sum);
	spin_unlock_irqrestore(&ssp_mutex, ssp_flags);

}

void ringBackJapan(int num) 
{
				setState(num, MAKErINGbACKjAPAN);
				
}

void busyJapan(int num) 
{
				setState(num, MAKEbUSYjAPAN);
				
}

void setupNeon(int num)
{
	spin_lock_irqsave(&ssp_mutex, ssp_flags);
	//while (SLIC_SPI_read(num, PROSLIC_VBAT_HIGH_SENSE_REG) < (60/1.5 - 3));  //reg 82
	while (SLIC_SPI_read(num, PROSLIC_VBAT_HIGH_SENSE_REG) < (600/15 - 3));  //reg 82
	SLIC_SPI_write(num, PROSLIC_ONHOOK_VOLTAGE_REG,0x3F);//  High Neon //reg 72
	spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
}

void initializeLoopDebounceReg(int num)
{
	spin_lock_irqsave(&ssp_mutex, ssp_flags);
		SLIC_SPI_write(num, PROSLIC_LOOP_CLOSURE_DEBOUNCE_REG,10);   // Loop Debounce Register  = initial value
		spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
}

//Checks the loop transition situation for off-hook or on-hook event. 
//Once this is determined, it executes state transition corresponding 
//to the events and the current state.
void loopAction(int num)
{ 
	int i;

//printf("\n*****************>  loopAction\n");
	//printLoopState();
	spin_lock_irqsave(&ssp_mutex, ssp_flags);
		if ( (ssp_slic[num].chipData.state != MAKEoFFHOOK) && (loopStatus(num)) ) //Checking for offhook with debounce
		{
			 if (ssp_slic[num].chipData.version <=2 )  // if REVISION B  set to active.
			{
		
			goActive(num);  // Rev B fix not needed 
	    
			}
			setState(num, MAKEoFFHOOK);
			ssp_slic[num].chipData.Off_Hook_time = jiffies;//clock();
			//printf("\n<*****************  loopAction clock\n");
			return;		
		}
	
		if ((ssp_slic[num].chipData.state != ONHOOK) && (loopStatus(num))==0 )//Checking for onHook with debounce
		{		
	
			for(i=0;i<ssp_slic[num].chipData.digit_count;i++)
						ssp_slic[num].chipData.DTMF_digits[i]= 0x0;
					ssp_slic[num].chipData.dtmf_wait = 0;
					ssp_slic[num].chipData.digit_count=0;
			setState(num, ONHOOK);
			ssp_slic[num].chipData.On_Hook_time = jiffies;//clock();
		
	//	if ((ssp_slic[num].chipData.On_Hook_time - ssp_slic[num].chipData.Off_Hook_time  ) < 2000 )
	//	{
	//		setState(num, CALLBACK);
	//	//	printf("\n<*****************  loopAction setState(num, CALLBACK)\n");
	//		return;
	//	}
	
	
	
				setState(num, ONHOOK); 	
				ssp_slic[num].chipData.On_Hook_time = jiffies;//clock();
				spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
				disableOscillators(num);
	//	printf("\n<*****************  loopAction\n");
			return;
		}

}

UINT8 checkSum(int num, char * string )
{
	int i =0;
	
	UINT8 sum=0;
	
	while (string[i] !=0)
	{
		sum += string[i++];
	}
	
	return -sum ;
}

void fskInitialization (int num)

{
	init =0 ;  // gloabal variable used to detect critical timing violation
	           // if init =2 => more than 1/1200th second passed between interrupt
	//SLIC_SPI_write(num,  REVC,0x40); // set to revision C FSK mode on  Now this is done ealier
	SLIC_SPI_write(num, PROSLIC_OSC1_ACTTIME_LOW_REG,19);  //reg 36 -> 19 is twenty ticks  20/24000 sec = 1/1200 sec
	SLIC_SPI_write(num, PROSLIC_OSC1_ACTTIME_HIGH_REG,0x0); //reg 37 -> 0 is zero MSB of timer
	
	
	
	SLIC_SPI_write(num, PROSLIC_FSK_DATA,1);  /*reg -> 52 Mark is the default value */
	SLIC_SPI_write(num, PROSLIC_FSK_DATA,1);  /*reg -> 52 Mark is the default value */
	/* writen twice to fill double buffer which has logic to detect
	   bit transition
	*/
	
	SLIC_SPI_write(num, PROSLIC_INT1_MASK_REG,0xff);;//0x01); /*reg 21 ->  Mask Register #1  Active Interrupt*/
	
	/*
	
	INFO: case0 = 0.997673,case1 = 0.998714,case2 = 1.001328,case3 = 1.002373
	case1 < case0
	
	INFO: Settings for  2200 as initial frequency are - OSCn = 0x6b60, OSCnX = 0x01b4
	INFO: Settings for  1200 as initial frequency are - OSCn = 0x79c0, OSCnX = 0x00e9
	INFO: Settings for  2200 to  1200  transition are - OSCn = 0x79c0, OSCnX = 0x1110
	INFO: Settings for  1200 to  2200  transition are - OSCn = 0x6b60, OSCnX = 0x3c00
	INFO: Compound gain variation                          = 0.999756
	
	
	*/
	
	SLIC_SPI_ind_write(num, PROSLIC_IND_FSK_X_0,0x01b4); //reg 99 ->  See above
	SLIC_SPI_ind_write(num, PROSLIC_IND_FSK_COEFF_0	,0x6b60); // reg 100 -> 
	SLIC_SPI_ind_write(num, PROSLIC_IND_FSK_X_1,0x00e9); // reg 101 -> 
	SLIC_SPI_ind_write(num, PROSLIC_IND_FSK_COEFF_1	,0x79c0); // reg 102 -> 
	SLIC_SPI_ind_write(num, PROSLIC_IND_FSK_X_01,0x1110); // reg 103 -> 
	SLIC_SPI_ind_write(num, PROSLIC_IND_FSK_X_10,0x3c00); // reg 104 -> 
	SLIC_SPI_write(num, PROSLIC_OSC1_CTRL_REG,0x56);  // reg 32 -> FSK mode receiver
}

static irqreturn_t dma_int (int irq, void *dev_instance, struct pt_regs *regs)
{
	//struct SSP_SLIC       *ssp_slic = (struct SSP_SLIC *)dev_instance;

	int                     handled = 0, tmp, i, num=0;//, read_status=0
	unsigned char *tmp_ptr;
	handled = 1;
//	unsigned int opcode, old_opcode;
 
	disable_irq(irq);   /* disable  interrupt */
	tmp=READ_DMA_REG(DMA_INT_TC);
	//WRITE_DMA_REG(DMA_INT_TC_CLR, 0xc);
	tmp=READ_DMA_REG(DMA_INT_TC);

	//if((dp%200)==0)
	//	printk("tmp : %x\n",tmp);
		//dp++;
	//if(dma_demo == DMA_DEMO)
	{ 

		if(dma_link_on==1)
		{
			
			
#if 1			
			if((tmp&0x08)==0x08) //recv
			{
				consistent_sync(__va(LLPR[desc_ptrr].dst_addr),DBUF_SIZE, DMA_BIDIRECTIONAL);				
				tmp_ptr = __va(LLPR[desc_ptrr].dst_addr);
					//for(i=0; i<((DBUF_SIZE/2)*NUMBER_OF_CHAN) ;i+=NUMBER_OF_CHAN)
					for(i=0; i<DBUF_SIZE ;i+=(2*NUMBER_OF_CHAN))
					{
						for(num=0;num<NUMBER_OF_CHAN;num++)
						{
							if(ssp_slic[num].link_on)
							{
								//if(NUMBER_OF_CHAN==1)
								{
									ssp_slic[num].cr2rbuf[(desc_ptrr * SBUF_SIZE)+((i/NUMBER_OF_CHAN))] =*(tmp_ptr+i+(2*num)+1);//
									ssp_slic[num].cr2rbuf[(desc_ptrr * SBUF_SIZE)+((i/NUMBER_OF_CHAN))+1] = *(tmp_ptr+i+(2*num));//((*(tmp_ptr+i))&0xfe);//*(wtmp+i); //
								}
								//case2
								//else
								//{
								//	ssp_slic[num].cr2rbuf[(desc_ptrr * SBUF_SIZE)+((i/NUMBER_OF_CHAN))] = *(tmp_ptr+i+(2*num));
								//	ssp_slic[num].cr2rbuf[(desc_ptrr * SBUF_SIZE)+((i/NUMBER_OF_CHAN))+1] = *(tmp_ptr+i+(2*num)+1);
								//}
							}
							else
							{
								ssp_slic[num].cr2rbuf[(desc_ptrr * SBUF_SIZE)+((i/NUMBER_OF_CHAN))] = 0x0;
								ssp_slic[num].cr2rbuf[(desc_ptrr * SBUF_SIZE)+((i/NUMBER_OF_CHAN))+1] = 0x0;
							}
						}
					}
					//////////////////////
					if((ssp_slic[0].dma_stop==1)&&(ssp_slic[1].dma_stop==1))
					{
							LLPT[desc_ptrr].llp = 0;
							LLPR[desc_ptrr].llp = 0;
					}
					//////////////////////
				desc_ptrr++;
				desc_ptrr %= LLP_SIZE;

					for(num=0;num<NUMBER_OF_CHAN;num++)
					{
						if(ssp_slic[num].link_on)
						{
							ssp_slic[num].dout ++;
							if(ssp_slic[num].dout > LLP_SIZE)
								ssp_slic[num].dout = LLP_SIZE;
						}
					}
			}//if((tmp&0x08)==0x08) //recv
			
			if((tmp&0x04)==0x04)//tc
			{
					tmp_ptr = __va(LLPT[desc_ptrt].src_addr);

						for(i=0; i<DBUF_SIZE ;i+=(2*NUMBER_OF_CHAN))
						{
							for(num=0;num<NUMBER_OF_CHAN;num++)
							{
									if(ssp_slic[num].din > 0)
									{
										if(ssp_slic[num].link_on)
										{
											//case1
											*(tmp_ptr+i+(2*num)) = ssp_slic[num].cw2tbuf[(desc_ptrt * SBUF_SIZE)+((i/NUMBER_OF_CHAN))+1];
											*(tmp_ptr+i+(2*num)+1) = ssp_slic[num].cw2tbuf[((desc_ptrt * SBUF_SIZE)+(i/NUMBER_OF_CHAN))];
											//case2
											//*(tmp_ptr+i+(2*num)) = ssp_slic[num].cw2tbuf[((desc_ptrt * SBUF_SIZE)+(i/NUMBER_OF_CHAN))];
											//*(tmp_ptr+i+(2*num)+1) = ssp_slic[num].cw2tbuf[(desc_ptrt * SBUF_SIZE)+((i/NUMBER_OF_CHAN))+1];
										}
										else
										{
											*(tmp_ptr+i+(2*num)) = 0x0;
											*(tmp_ptr+i+(2*num)+1) = 0x0;
										}									
									}
										//*(tmp_ptr+i+num) = *(ssp_slic[num].cw2tbuf+(desc_ptrt * DBUF_SIZE)+(2*(i/NUMBER_OF_CHAN))+1);
									else
									{
											*(tmp_ptr+i+(2*num)) = 0x0;
											*(tmp_ptr+i+(2*num)+1) = 0x0;
									}
										//*(tmp_ptr+i+num) = 0x0;;
							}
						}
						consistent_sync(__va(LLPT[desc_ptrt].src_addr),DBUF_SIZE, DMA_BIDIRECTIONAL);	
						//////////////////////
						if((ssp_slic[0].dma_stop==1)&&(ssp_slic[1].dma_stop==1))
						{	
								LLPT[desc_ptrt].llp = 0;
								LLPR[desc_ptrt].llp = 0;
						}
					  //////////////////////			
						desc_ptrt++;
						desc_ptrt %= LLP_SIZE;
							//ssp_slic[num].din = 0; 
						for(num=0;num<NUMBER_OF_CHAN;num++)
						{	
							if(ssp_slic[num].din > 0)
								ssp_slic[num].din--;
							if(ssp_slic[num].din<0)
							{
								ssp_slic[num].din=0;
								printk("No data to play\n");
							}
						}


			}//if((tmp&0x04)==0x04)//tc
#else
		unsigned char *ptr;
			if((tmp&0x04)==0x04) //recv
			{
				consistent_sync(__va(LLPR[desc_ptrr].dst_addr),DBUF_SIZE, DMA_BIDIRECTIONAL);				
				tmp_ptr = __va(LLPR[desc_ptrr].dst_addr);
				ptr = __va(LLPT[desc_ptrt].src_addr);

					for(i=0;i<DBUF_SIZE;i+=2)
					{
						 *(ptr+i) = *(tmp_ptr+i+1);
						 *(ptr+i+1) = *(tmp_ptr+i);
					}
				desc_ptrr++;
				desc_ptrr %= LLP_SIZE;
				consistent_sync(__va(LLPT[desc_ptrt].src_addr),DBUF_SIZE, DMA_BIDIRECTIONAL);				
				desc_ptrt++;
				desc_ptrt %= LLP_SIZE;
					
			}//if((tmp&0x08)==0x08) //recv
#endif				
		}//if(ssp_slic[num].link_on==1) ////if(dma_link_on==1)
		else   ////if(dma_link_on==1)
		{
						//////////////////////
						if((ssp_slic[0].dma_stop==1)&&(ssp_slic[1].dma_stop==1))
						{	
								LLPT[desc_ptrt].llp = 0;
								LLPR[desc_ptrt].llp = 0;
								LLPT[desc_ptrt].llp = 0;
								LLPR[desc_ptrt].llp = 0;
						}
					  //////////////////////
		}

	} //if(dma_demo == 1)

		WRITE_DMA_REG(DMA_INT_TC_CLR, (tmp&0x0c));
    /* enable  interrupt */
	enable_irq(irq);
				
	
	return IRQ_RETVAL(handled);
}

void fskByte(int num,UINT8 c)
{

	unsigned int i;
	
	SLIC_SPI_write(num, PROSLIC_FSK_DATA,0); // Send Stop bit
	
	waitForInterrupt(num) ;    // start bit  STARTS
	
	for (i=0;i<8;i++){
	
		SLIC_SPI_write(num, PROSLIC_FSK_DATA,c);
		
		c>>=1;
		
		waitForInterrupt(num);
	
	} // for
	
	SLIC_SPI_write(num, PROSLIC_FSK_DATA,1);
	
	waitForInterrupt(num);
	
	//SLIC_SPI_write(num, PROSLIC_FSK_DATA,1);
	
	//waitForInterrupt(num);

}// fskByte()

void waitForInterrupt (int num)
{
	/* Wait for an Interrupt from the ProSLIC => oscillator loaded */
	if (ssp_slic[num].chipData.osc1_event && init !=0){
	
			 //printk(" %1.1x",init) ;
			 init = 2;
	
	}
		 if (init == 0) init=1; /* init has 3 states 0 => fsk initialized
								                     1 => fsk did first interrupt
													 2 => got premature interrupt
								*/
	ssp_slic[num].chipData.osc1_event = 0;							
	while (!ssp_slic[num].chipData.osc1_event) ;
		SLIC_SPI_write(num, 18,0x01); /*  Status Register #1  clear interrupt*/
}

UINT8 digit(int num)
{
	int opcode;
	//spin_lock_irqsave(&ssp_mutex, ssp_flags);
	opcode = SLIC_SPI_read(num, PROSLIC_DTMF_REG) & 0x0f;
	//spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
	return opcode;  //ref 24
}

//Collects one DTMF digit after a DTMF interrupts.
UINT8 dtmfAction_test(int num)
{  

	char rawDigit,asciiChar;
	setState(num, DIGITDECODING);
	if(gemini_ssp_hookstate(num)) // (1):On hook
	{
			printk("Please off-hook !!\n");
	}
	
	else
	{
		printk("Please push phone number keys.(#20)\n");
		do{
		   
		  	if(ssp_slic[num].chipData.interrupt&0x10000) 
		  	{
		  		spin_lock_irqsave(&ssp_mutex, ssp_flags);
				rawDigit=digit(num);
				spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
				//printk("				-->  dtmfAction ");
				//asciiChar= '0' + digit;
				switch (rawDigit){
				case 0xA :
						asciiChar = '0';
						break;
				case 0xB:
						asciiChar = '*';
						break;
				case 0xC:
						asciiChar = '#';
						break;
    			
				default:
					asciiChar = '0' + rawDigit;
					break;
				}
				ssp_slic[num].chipData.interrupt=0;
					 if (ssp_slic[num].chipData.digit_count < DTMF_NUM)
					 {
						ssp_slic[num].chipData.DTMF_digits[ssp_slic[num].chipData.digit_count] = asciiChar; 
						ssp_slic[num].chipData.digit_count++;
						ssp_slic[num].chipData.DTMF_digits[ssp_slic[num].chipData.digit_count]= 0;
						
						printk("\nValue= 0x%02x  String collected \"%s\" ", digit, &(ssp_slic[num].chipData.DTMF_digits) );	
					 }
			}
			schedule();
		}while(ssp_slic[num].chipData.digit_count < DTMF_NUM);
	}
	ssp_slic[num].chipData.digit_count = 0;
	return 0;
}

//Collects one DTMF digit after a DTMF interrupts.
UINT8 dtmfAction(int num)
{  

	char rawDigit,asciiChar;
	setState(num, DIGITDECODING);
	spin_lock_irqsave(&ssp_mutex, ssp_flags);
	rawDigit=digit(num);
	spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
	//printk("				-->  dtmfAction ");
	//asciiChar= '0' + digit;
	switch (rawDigit){
	case 0xA :
			asciiChar = '0';
			break;
	case 0xB:
			asciiChar = '*';
			break;
	case 0xC:
			asciiChar = '#';
			break;

	default:
		asciiChar = '0' + rawDigit;
		break;
	}
		 if (ssp_slic[num].chipData.digit_count < DTMF_NUM)
		 {
			ssp_slic[num].chipData.DTMF_digits[ssp_slic[num].chipData.digit_count] = asciiChar; 
			ssp_slic[num].chipData.digit_count++;
			ssp_slic[num].chipData.DTMF_digits[ssp_slic[num].chipData.digit_count]= 0;
			
			//printk("\nValue= 0x%02x  String collected \"%s\" ", digit, &ssp_slic[num].chipData.DTMF_digits );	
		 }
		 return 0;
}

void interrupt_init(void)
{
	UINT32  retval;
	UINT32  regs;


	
	/////////////////////////////////////////////
//	//SLIC_GPIO bit trigger = High_level
//	opcode = READ_GPIO_REG(GPIO_INT_POLARITY);
//	WRITE_GPIO_REG(GPIO_INT_POLARITY,(SSP_GPIO_INT_BIT|opcode));
//	//SLIC_GPIO bit level trigger 
//	opcode = READ_GPIO_REG(GPIO_INT_TRIGGER);
//	WRITE_GPIO_REG(GPIO_INT_TRIGGER,(SSP_GPIO_INT_BIT|opcode));
//	//UN_mask SLIC_GPIO bit
//	opcode = READ_GPIO_REG(GPIO_INT_MASK);
//	WRITE_GPIO_REG(GPIO_INT_MASK,((~SSP_GPIO_INT_BIT)&opcode));
//	//enable SLIC_GPIO_int
//	opcode = READ_GPIO_REG(GPIO_INT_ENABLE);
//	WRITE_GPIO_REG(GPIO_INT_ENABLE,(SSP_GPIO_INT_BIT|opcode));
//	
//	
//	retval = request_irq(SSP_GPIO_INT, gemini_slic_isr, SA_INTERRUPT, "GEMINI_SLIC", NULL);
//	if (retval)
//		printk("SSP interrupt init error.\n");
	
	retval = request_irq(IRQ_DMA_OFFSET, dma_int, SA_INTERRUPT, "dma", NULL);
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
	retval = request_gpio_irq(0,gemini_slic_isr,1,1,0);//SSP_GPIO_INT_BIT = 0x400 -> bit 10
#else	
	retval = request_gpio_irq(10,gemini_slic_isr,1,1,0);//SSP_GPIO_INT_BIT = 0x400 -> bit 10
#endif	
	if (retval)
		printk("SSP interrupt init error.\n");
	
}


static void gemini_slic_isr (int irq)
{
	char rawDigit,asciiChar;
	UINT32 opcode, num;
	union {
		UINT8 reg_data[3];
		long interrupt_bits;
	} u ;
	
	///////
#if 0
		unsigned long shiftMask=1;
	 enum              // Declare enum type Days
	{
		OSC1_T1=0,  
		OSC1_T2=1,
		OSC2_T1=2,
		OSC2_T2=3,
		RING_T1=4,
		RING_T2=5,
		PULSE_T1=6,
		PULSE_T2=7,
		RING_TRIP=8,
		LOOP__STAT=9,
		PQ1=10,
		PQ2=11,
		PQ3=12,
		PQ4=13,
		PQ5=14,
		PQ6=15,
		DTMF=16, /* DTMF detected */
		INDIRECT=17, /* Indirect Reg Access ready */
		CAL_CM_BAL=18 /* Common Mode Calibration Error */
	} interruptCause;                // Variable today has type Days
#endif	
	//allow_signal(SIGTERM);
	///////
	//printk("-->\n");
	opcode = READ_GPIO_REG(GPIO_INT_RAWSTATE);
	
	if((opcode&SSP_GPIO_INT_BIT))//&&(chipData.int_init==0))
	{
		for(num=0;num<NUMBER_OF_CHAN;num++)
		{
				//printk("\n--> int\n");
				 //mask SLIC_GPIO bit
				 ssp_slic[num].chipData.int_init=1;
    		
				u.reg_data[0] = 0x0;
				u.reg_data[1] = 0x0;
				u.reg_data[2] = 0x0;
		
		
				//Gathers up the interrupt(s) from the ProSLIC and clears
				//them for future events.
				//ssp_slic[num].chipData.interrupt=0;
				u.reg_data[0] = SLIC_SPI_read(num, PROSLIC_INT1_STATUS_REG);
				SLIC_SPI_write(num, PROSLIC_INT1_STATUS_REG,u.reg_data[0]);
				ssp_slic[num].chipData.interrupt |= u.reg_data[0];
				
				u.reg_data[1] = SLIC_SPI_read(num, PROSLIC_INT2_STATUS_REG);
				SLIC_SPI_write(num, PROSLIC_INT2_STATUS_REG,u.reg_data[1] );
				ssp_slic[num].chipData.interrupt |= u.reg_data[1]<<8;
				
				u.reg_data[2] = SLIC_SPI_read(num, PROSLIC_INT3_STATUS_REG);
				///////////////
				if((u.reg_data[2]&0x01)&&(dma_demo != DMA_DEMO))
				{
					
						//setState(num, DIGITDECODING);
						rawDigit=digit(num);
						switch (rawDigit){
							case 0xA :
									asciiChar = '0';
									break;
							case 0xB:
									asciiChar = '*';
									break;
							case 0xC:
									asciiChar = '#';
									break;
  						
							default:
								asciiChar = '0' + rawDigit;
								break;
						}
						if (ssp_slic[num].chipData.digit_count < DTMF_NUM)
		 				{
		 					ssp_slic[num].chipData.dtmf_wait = 0;
							ssp_slic[num].chipData.DTMF_digits[ssp_slic[num].chipData.digit_count] = asciiChar; 
							printk(" [%c] ",(ssp_slic[num].chipData.DTMF_digits[ssp_slic[num].chipData.digit_count]) );	
							ssp_slic[num].chipData.digit_count++;
							ssp_slic[num].chipData.DTMF_digits[ssp_slic[num].chipData.digit_count]= 0;
							
		 				}
				}
				///////////////
				SLIC_SPI_write(num,  PROSLIC_INT3_STATUS_REG,u.reg_data[2]);
				ssp_slic[num].chipData.interrupt |= (u.reg_data[2]&0x07)<<16;
				//////////////////////////////////////////////////////////////////////////
#if 0
					ssp_slic[num].chipData.inwt = 0;
					shiftMask = 1;
				//////////////////////////////////////////////////////////////////	
						
					
						if(ssp_slic[num].chipData.interrupt)
						{
							for ( interruptCause=OSC1_T1 ; interruptCause <= CAL_CM_BAL ; interruptCause++)
							{
								if (shiftMask & ssp_slic[num].chipData.interrupt)
								{
									
									
									ssp_slic[num].chipData.interrupt &= ~shiftMask;   // clear interrupt cause
									                                 
									//printk((( interruptCause >=10) && (interruptCause<=11))?"\n %s":"\n(%s)  ", icause[interruptCause]);
									switch (interruptCause) {
										// Figure out what todo based on which one occured
										case OSC1_T1:
											ssp_slic[num].chipData.osc1_event = 1;
										//	printk("\n OSC1_T1 \n");
											break;
										case OSC1_T2:
										//	printk("\n OSC1_T2 \n");
											break;
										case OSC2_T1:
										//	printk("\n OSC2_T1 \n");
											break;
										case OSC2_T2:
										//	printk("\n OSC2_T2 \n");
											break;
										case RING_T1:
										//printk("\n RING_T1 \n");
											ssp_slic[num].chipData.ringCount++;
											//printk("\n RING_T1  : %d\n",ssp_slic[num].chipData.ringCount);
											if (ssp_slic[num].chipData.state==FIRSTrING)
											{ 
												ssp_slic[num].chipData.ringCount=1;
											//printk("\n RING_T1  	 --->   FIRSTrING\n");
												if (ssp_slic[num].chipData.version >2)
													setState(num, CALLERiD);
												else
													setState(num, RINGING);
											}
												
										break;
										case RING_T2:
								    	
												
											break;
										case PULSE_T1:
											break;
										case PULSE_T2:
											break;
										
								    	
										
										case RING_TRIP:
											//printk("\n RING_TRIP \n");
											if (ssp_slic[num].chipData.version <=2 )  // if REVISION B  set to active.
											{
												spin_lock_irqsave(&ssp_mutex, ssp_flags);
												goActive(num); // Rev B fix not needed 
								    		spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
											}
										case LOOP__STAT:
												//printk("\n LOOP__STAT \n");
												spin_lock_irqsave(&ssp_mutex, ssp_flags);
											groundShort(num); /* Check for grounded Tip or Ring Leads*/
											spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
											setState(num, LOOPtRANSITION);
											
											break;
								    	
								    	
										case PQ1:
										case PQ2:
										case PQ3:
										case PQ4:
										case PQ5:
										case PQ6:
											//printk("\n PQ6 \n");
											{	static unsigned long lastEventNumber =1;
												if (lastEventNumber != ssp_slic[num].chipData.eventNumber)  /*  We allow only one alarm per alarm event */
												{
													int i = interruptCause - PQ1;
													lastEventNumber = ssp_slic[num].chipData.eventNumber;
													powerLeakTest(num);
													powerUp(num);
												//	printk( "  %d time",ssp_slic[num].chipData.qLog[i]);
													if (ssp_slic[num].chipData.qLog[i]++>2)    
														//printk("\n exception(num, POWERaLARMQ1+i) \n");
														exception(num, POWERaLARMQ1+i);
													if(ssp_slic[num].chipData.qLog[i] >1) 
														printk( "s");
														
													clearAlarmBits(num);
													spin_lock_irqsave(&ssp_mutex, ssp_flags);
													goActive(num);
													spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
													setState(num, ONHOOK);
												}
													 
											}
								    	
											break;
										case DTMF:
											//printk("\n DTMF \n");
											setState(num, DTMFtRANISTION); 
												break;
								    	
										
										case INDIRECT:
											break;
										case CAL_CM_BAL:
											break;
									
								
									} //switch
								
									
								} //if
							  shiftMask<<=1;
							} //for
						}//if(ssp_slic[num].chipData.interrupt)
						ssp_slic[num].chipData.interrupt = 0;
#endif						
	/////////////////////////////////////////////////////////

//				printk("\n--> int   %x\n",ssp_slic[num].chipData.interrupt);
		} //for(i=0;i<NUMBER_OF_CHAN;i++)
	}	//if((opcode&SSP_GPIO_INT_BIT))
	
	//printk("<--\n");
}

//Sets Direct Register 64 = 1. Stops the attached phone from ringing.
void stopRinging(int num)
{
	spin_lock_irqsave(&ssp_mutex, ssp_flags);
	 if ((0xf & SLIC_SPI_read(num, 0))<=2 )  // if REVISION B  
	 	SLIC_SPI_write(num, 69,10);   // Loop Debounce Register  = initial value
    
	goActive(num);

	spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
}

//This starts the phone ringing by setting Register 64 to 4. 
//This is the ringing mode for the ProSLIC.
void activateRinging(int num)
{
	unsigned int opcode;
	spin_lock_irqsave(&ssp_mutex, ssp_flags);
	SLIC_SPI_write(num,  PROSLIC_LINEFEED_CTRL_REG, 0x44); // REG 64,4	
	opcode = SLIC_SPI_read(num,  PROSLIC_LINEFEED_CTRL_REG); // REG 64,4
	
	mdelay(20);
	spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
}

//Set the ProSLIC to standard two second on, four second off ringing.
void standardRinging(int num) { 	
	// Enables ringing mode on ProSlic for standard North American ring
	//	RING_ON__LO	48
	//	RING_ON_HI	49
	//	RING_OFF_LO	50
	//	RING_OFF_HI	51
	// Active Timer
spin_lock_irqsave(&ssp_mutex, ssp_flags);
	SLIC_SPI_write(num,  PROSLIC_RING_OSC_ACTIVE_TIMERL, 0x80); // low reg 48
	SLIC_SPI_write(num,  PROSLIC_RING_OSC_ACTIVE_TIMERH, 0x3E); // hi reg 49
	// Inactive Timer
	SLIC_SPI_write(num,  PROSLIC_RING_OSC_INACTIVE_TIMERL, 0x00); // low reg 50
	SLIC_SPI_write(num,  PROSLIC_RING_OSC_INACTIVE_TIMERH, 0x7D); // hi reg 51
	// Enable timers for ringing oscillator
	SLIC_SPI_write(num,  PROSLIC_RING_OSC_CTRL_REG, 0x18);  //reg 34
	spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
}

void disableOscillators(int num) { 
	// Turns of OSC1 and OSC2
	unsigned char data;
	//unsigned int opcode;
	spin_lock_irqsave(&ssp_mutex, ssp_flags);
	//printk("Disabling Oscillators!!!\n");
	//for ( i=32; i<=45; i++) 
	//{
	//	mdelay(20);
	//	if (i !=34)  // Don't write to the ringing oscillator control
	//	SLIC_SPI_write(num, i,0);
	//}
	data = SLIC_SPI_read(num,  PROSLIC_OSC1_CTRL_REG); // REG 64,4
	data &= ~(0x1C);
	SLIC_SPI_write(num, PROSLIC_OSC1_CTRL_REG, data);
	data = SLIC_SPI_read(num,  PROSLIC_OSC2_CTRL_REG); // REG 64,4
	data &= ~(0x1C);
	SLIC_SPI_write(num, PROSLIC_OSC2_CTRL_REG, data);
	spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
}

void dialTone(int num)
{
	//UINT32 opcode;
	spin_lock_irqsave(&ssp_mutex, ssp_flags);
	//opcode = SLIC_SPI_read(num, PROSLIC_SPI_MODE_SEL_REG);
  SLIC_SPI_ind_write(num, PROSLIC_IND_OSC1_FREQ_COEFF_REG,0x7B30);  //IND REG 13
  //opcode = SLIC_SPI_read(num, PROSLIC_SPI_MODE_SEL_REG);
  SLIC_SPI_ind_write(num, PROSLIC_IND_OSC1_INIT1_REG,0x0063);
      //ind REG 14
  SLIC_SPI_ind_write(num, PROSLIC_IND_OSC2_FREQ_COEFF_REG,0x7870);
 //REG 16
  SLIC_SPI_ind_write(num, PROSLIC_IND_OSC2_INIT1_REG,0x007d);
      //REG 17
  SLIC_SPI_write(num, PROSLIC_OSC1_ACTTIME_LOW_REG,  0x0);
         //REG 36
  SLIC_SPI_write(num, PROSLIC_OSC1_ACTTIME_HIGH_REG,  0x0);
        //REG 37
  SLIC_SPI_write(num, PROSLIC_OSC1_INACTTIME_LOW_REG,  0x0);
       //REG 38
  SLIC_SPI_write(num, PROSLIC_OSC1_INACTTIME_HIGH_REG,  0x0);
      //REG 39
  SLIC_SPI_write(num, PROSLIC_OSC2_ACTTIME_LOW_REG,  0x0);
         //REG 40
  SLIC_SPI_write(num, PROSLIC_OSC2_ACTTIME_HIGH_REG,  0x0);
        //REG 41
  SLIC_SPI_write(num, PROSLIC_OSC2_INACTTIME_LOW_REG,  0x0);
       //REG 42
  SLIC_SPI_write(num, PROSLIC_OSC2_INACTTIME_HIGH_REG,  0x0);
      //REG 43
//opcode = SLIC_SPI_read(num, PROSLIC_SPI_MODE_SEL_REG);
                                              
  SLIC_SPI_write(num, PROSLIC_OSC1_CTRL_REG,  0x06);
               //REG 32
  SLIC_SPI_write(num, PROSLIC_OSC2_CTRL_REG,  0x06);
  //opcode = SLIC_SPI_read(num, PROSLIC_SPI_MODE_SEL_REG);
               //REG 33
               spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
}

void ringBackTone(int num)
{
	spin_lock_irqsave(&ssp_mutex, ssp_flags);
  SLIC_SPI_ind_write(num, PROSLIC_IND_OSC1_FREQ_COEFF_REG,RINGBACKTONE_IR13);  //ind reg 13
  SLIC_SPI_ind_write(num, PROSLIC_IND_OSC1_INIT1_REG,RINGBACKTONE_IR14);
 //ind reg 14
  SLIC_SPI_ind_write(num, PROSLIC_IND_OSC2_FREQ_COEFF_REG,RINGBACKTONE_IR16);
 //ind reg 16
  SLIC_SPI_ind_write(num, PROSLIC_IND_OSC2_INIT1_REG,RINGBACKTONE_IR17);
 //ind reg 17
  SLIC_SPI_write(num, PROSLIC_OSC1_ACTTIME_LOW_REG,  RINGBACKTONE_DR36);
   //reg 36
  SLIC_SPI_write(num, PROSLIC_OSC1_ACTTIME_HIGH_REG,  RINGBACKTONE_DR37);
   //reg 37
  SLIC_SPI_write(num, PROSLIC_OSC1_INACTTIME_LOW_REG,  RINGBACKTONE_DR38);
   //reg 38
  SLIC_SPI_write(num, PROSLIC_OSC1_INACTTIME_HIGH_REG,  RINGBACKTONE_DR39);
   //reg 39
  SLIC_SPI_write(num, PROSLIC_OSC2_ACTTIME_LOW_REG,  RINGBACKTONE_DR40);
   //reg 40
  SLIC_SPI_write(num, PROSLIC_OSC2_ACTTIME_HIGH_REG,  RINGBACKTONE_DR41);
   //reg 41
  SLIC_SPI_write(num, PROSLIC_OSC2_INACTTIME_LOW_REG,  RINGBACKTONE_DR42);
   //reg 42
  SLIC_SPI_write(num, PROSLIC_OSC2_INACTTIME_HIGH_REG,  RINGBACKTONE_DR43);
   //reg 43
  
                                      
  SLIC_SPI_write(num, PROSLIC_OSC1_CTRL_REG,  RINGBACKTONE_DR32);
   //reg 32
  SLIC_SPI_write(num, PROSLIC_OSC2_CTRL_REG,  RINGBACKTONE_DR33);
   //reg 33
 spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
}

void reorderTone(int num)
{
spin_lock_irqsave(&ssp_mutex, ssp_flags);
  SLIC_SPI_ind_write(num, PROSLIC_IND_OSC1_FREQ_COEFF_REG,REORDERTONE_IR13);  //ind reg 13
  SLIC_SPI_ind_write(num, PROSLIC_IND_OSC1_INIT1_REG,REORDERTONE_IR14);
 //ind reg 14
  SLIC_SPI_ind_write(num, PROSLIC_IND_OSC2_FREQ_COEFF_REG,REORDERTONE_IR16);
 //ind reg 16
  SLIC_SPI_ind_write(num, PROSLIC_IND_OSC2_INIT1_REG,REORDERTONE_IR17);
 //ind reg 17
  SLIC_SPI_write(num, PROSLIC_OSC1_ACTTIME_LOW_REG,  REORDERTONE_DR36);
   //reg 36
  SLIC_SPI_write(num, PROSLIC_OSC1_ACTTIME_HIGH_REG,  REORDERTONE_DR37);
   //reg 37
  SLIC_SPI_write(num, PROSLIC_OSC1_INACTTIME_LOW_REG,  REORDERTONE_DR38);
   //reg 38
  SLIC_SPI_write(num, PROSLIC_OSC1_INACTTIME_HIGH_REG,  REORDERTONE_DR39);
   //reg 39
  SLIC_SPI_write(num, PROSLIC_OSC2_ACTTIME_LOW_REG,  REORDERTONE_DR40);
   //reg 40
  SLIC_SPI_write(num, PROSLIC_OSC2_ACTTIME_HIGH_REG,  REORDERTONE_DR41);
   //reg 41
  SLIC_SPI_write(num, PROSLIC_OSC2_INACTTIME_LOW_REG,  REORDERTONE_DR42);
   //reg 42
  SLIC_SPI_write(num, PROSLIC_OSC2_INACTTIME_HIGH_REG,  REORDERTONE_DR43);
   //reg 43
  
                                      
  SLIC_SPI_write(num, PROSLIC_OSC1_CTRL_REG,  REORDERTONE_DR32);
   //reg 32
  SLIC_SPI_write(num, PROSLIC_OSC2_CTRL_REG,  REORDERTONE_DR33);
   //reg 33

 spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
}

void congestionTone(int num)
{
spin_lock_irqsave(&ssp_mutex, ssp_flags);
  SLIC_SPI_ind_write(num, PROSLIC_IND_OSC1_FREQ_COEFF_REG, CONGESTIONTONE_IR13);  //ind reg 13
  SLIC_SPI_ind_write(num, PROSLIC_IND_OSC1_INIT1_REG, CONGESTIONTONE_IR14);
 //ind reg 14
  SLIC_SPI_ind_write(num, PROSLIC_IND_OSC2_FREQ_COEFF_REG, CONGESTIONTONE_IR16);
 //ind reg 16
  SLIC_SPI_ind_write(num, PROSLIC_IND_OSC2_INIT1_REG, CONGESTIONTONE_IR17);
 //ind reg 17
  SLIC_SPI_write(num, PROSLIC_OSC1_ACTTIME_LOW_REG,  CONGESTIONTONE_DR36);
   //reg 36
  SLIC_SPI_write(num, PROSLIC_OSC1_ACTTIME_HIGH_REG,  CONGESTIONTONE_DR37);
   //reg 37
  SLIC_SPI_write(num, PROSLIC_OSC1_INACTTIME_LOW_REG,  CONGESTIONTONE_DR38);
   //reg 38
  SLIC_SPI_write(num, PROSLIC_OSC1_INACTTIME_HIGH_REG,  CONGESTIONTONE_DR39);
   //reg 39
  SLIC_SPI_write(num, PROSLIC_OSC2_ACTTIME_LOW_REG,  CONGESTIONTONE_DR40);
   //reg 40
  SLIC_SPI_write(num, PROSLIC_OSC2_ACTTIME_HIGH_REG,  CONGESTIONTONE_DR41);
   //reg 41
  SLIC_SPI_write(num, PROSLIC_OSC2_INACTTIME_LOW_REG,  CONGESTIONTONE_DR42);
   //reg 42
  SLIC_SPI_write(num, PROSLIC_OSC2_INACTTIME_HIGH_REG,  CONGESTIONTONE_DR43);
   //reg 43
  
                                      
  SLIC_SPI_write(num, PROSLIC_OSC1_CTRL_REG,  CONGESTIONTONE_DR32);
   //reg 32
  SLIC_SPI_write(num, PROSLIC_OSC2_CTRL_REG,  CONGESTIONTONE_DR33);
   //reg 33
 spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
}

void ringbackPbxTone(int num)
{
	spin_lock_irqsave(&ssp_mutex, ssp_flags);
  SLIC_SPI_ind_write(num, PROSLIC_IND_OSC1_FREQ_COEFF_REG,RINGBACKPBXTONE_IR13);  //ind reg 13
  SLIC_SPI_ind_write(num, PROSLIC_IND_OSC1_INIT1_REG,RINGBACKPBXTONE_IR14);
 //ind reg 14
  SLIC_SPI_ind_write(num, PROSLIC_IND_OSC2_FREQ_COEFF_REG,RINGBACKPBXTONE_IR16);
 //ind reg 16
  SLIC_SPI_ind_write(num, PROSLIC_IND_OSC2_INIT1_REG,RINGBACKPBXTONE_IR17);
 //ind reg 17
  SLIC_SPI_write(num, PROSLIC_OSC1_ACTTIME_LOW_REG,  RINGBACKPBXTONE_DR36);
   //reg 36
  SLIC_SPI_write(num, PROSLIC_OSC1_ACTTIME_HIGH_REG,  RINGBACKPBXTONE_DR37);
   //reg 37
  SLIC_SPI_write(num, PROSLIC_OSC1_INACTTIME_LOW_REG,  RINGBACKPBXTONE_DR38);
   //reg 38
  SLIC_SPI_write(num, PROSLIC_OSC1_INACTTIME_HIGH_REG,  RINGBACKPBXTONE_DR39);
   //reg 39
  SLIC_SPI_write(num, PROSLIC_OSC2_ACTTIME_LOW_REG,  RINGBACKPBXTONE_DR40);
   //reg 40
  SLIC_SPI_write(num, PROSLIC_OSC2_ACTTIME_HIGH_REG,  RINGBACKPBXTONE_DR41);
   //reg 41
  SLIC_SPI_write(num, PROSLIC_OSC2_INACTTIME_LOW_REG,  RINGBACKPBXTONE_DR42);
   //reg 42
  SLIC_SPI_write(num, PROSLIC_OSC2_INACTTIME_HIGH_REG,  RINGBACKPBXTONE_DR43);
   //reg 43
  
                                      
  SLIC_SPI_write(num, PROSLIC_OSC1_CTRL_REG,  RINGBACKPBXTONE_DR32);
   //reg 32
  SLIC_SPI_write(num, PROSLIC_OSC2_CTRL_REG,  RINGBACKPBXTONE_DR33);
   //reg 33
spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
}

void busyTone(int num)
{
 spin_lock_irqsave(&ssp_mutex, ssp_flags);
  SLIC_SPI_ind_write(num, PROSLIC_IND_OSC1_FREQ_COEFF_REG,BUSYTONE_IR13);  //ind reg 13
  SLIC_SPI_ind_write(num, PROSLIC_IND_OSC1_INIT1_REG,BUSYTONE_IR14);
 //ind reg 14
  SLIC_SPI_ind_write(num, PROSLIC_IND_OSC2_FREQ_COEFF_REG,BUSYTONE_IR16);
 //ind reg 16
  SLIC_SPI_ind_write(num, PROSLIC_IND_OSC2_INIT1_REG,BUSYTONE_IR17);
 //ind reg 17
  SLIC_SPI_write(num, PROSLIC_OSC1_ACTTIME_LOW_REG,  BUSYTONE_DR36);
   //reg 36
  SLIC_SPI_write(num, PROSLIC_OSC1_ACTTIME_HIGH_REG,  BUSYTONE_DR37);
   //reg 37
  SLIC_SPI_write(num, PROSLIC_OSC1_INACTTIME_LOW_REG,  BUSYTONE_DR38);
   //reg 38
  SLIC_SPI_write(num, PROSLIC_OSC1_INACTTIME_HIGH_REG,  BUSYTONE_DR39);
   //reg 39
  SLIC_SPI_write(num, PROSLIC_OSC2_ACTTIME_LOW_REG,  BUSYTONE_DR40);
   //reg 40
  SLIC_SPI_write(num, PROSLIC_OSC2_ACTTIME_HIGH_REG,  BUSYTONE_DR41);
   //reg 41
  SLIC_SPI_write(num, PROSLIC_OSC2_INACTTIME_LOW_REG,  BUSYTONE_DR42);
   //reg 42
  SLIC_SPI_write(num, PROSLIC_OSC2_INACTTIME_HIGH_REG,  BUSYTONE_DR43);
   //reg 43
  
                                      
  SLIC_SPI_write(num, PROSLIC_OSC1_CTRL_REG,  BUSYTONE_DR32);
   //reg 32
  SLIC_SPI_write(num, PROSLIC_OSC2_CTRL_REG,  BUSYTONE_DR33);
   //reg 33
   spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
}

//Runs the state-machine. Sees if there is something for the current state 
//to do including advancing to a new state.
void stateMachine(int num){
	//static int ringCount=0;
//	UINT32 opcode;
	int i=0;
	
	//opcode = SLIC_SPI_read(num, PROSLIC_INT3_MASK_REG);
	//opcode = SLIC_SPI_read(num, PROSLIC_INT3_STATUS_REG);
	//printf("\n						-->%s\n",stt[chipData.state]); 
	switch (ssp_slic[num].chipData.state)
	{


			//  Below are only the meta/transient states (transitions).
			//The actual precursor states are changed durring the event/interrupt handler.
			//I know this is unconventional but it does shrink down the code considerably.  	
			//Latter when I fold in the wait states and the delays I will put the stable states back here.	
			//	
			
  		
			case STATEcHANGE:
				//printf("\n-->STATEcHANGE");
				 ssp_slic[num].chipData.state=ssp_slic[num].chipData.newState;
					break; 
			case CALLBACK :
				//printf("\n-->CALLBACK");
  		
				ssp_slic[num].chipData.state = FIRSTrING;
				break; 
  		
			case CALLBACKpROGRAMMED:
				//printf("\n-->CALLBACKpROGRAMMED");
			
 				activateRinging(num);
				ssp_slic[num].chipData.state = PROGRAMMEDrING;
				//printf("\n						-->PROGRAMMEDrING\n");
				break; 
  		
  		//case OFFHOOK:
			case MAKEoFFHOOK: // Make dialtone 
				//if(dma_demo == DMA_DEMO)
				{
						setState(num, DIALtONE);
						for(i=0;i<ssp_slic[num].chipData.digit_count;i++)
							ssp_slic[num].chipData.DTMF_digits[i]= 0x0;
						ssp_slic[num].chipData.dtmf_wait = 0;
						ssp_slic[num].chipData.digit_count=0;
				}
				break;
			case LOOPtRANSITION:
				//printf("\n-->LOOPtRANSITION");			
					if (ssp_slic[num].chipData.version <= 2)
						initializeLoopDebounceReg(num);
					
						switch (ssp_slic[num].chipData.previousState){
														
								case RINGING:
								case FIRSTrING:
									setState(num, OFFHOOK);
									//printf("\n		stat			-->OFFHOOK\n");
						 			break;
								case DEFEREDcALLBACKpROGRAMMED:
									setState (num, CALLBACKpROGRAMMED);
									//printf("\n						-->CALLBACKpROGRAMMED\n");
								break;
  		
								case PRENEON:
									setupNeon(num);
									setState(num, NEON);
								break;
								default:
									loopAction(num);
						}
				break;
			case DTMFtRANISTION:

					switch (ssp_slic[num].chipData.previousState){
								case OFFHOOK:
								case BUSY:
								case RINGbACK:
								break;
								//case DTMFtRANISTION:
								case DIALtONE:
				//				printf("\n-->DIALtONE   disableOscillators");
									disableOscillators(num);
									setState(num, DIGITDECODING);

									break;
								case DIGITDECODING:
						//		printf("\n-->DTMFtRANISTION");
									setState(num, DIGITDECODING);
						//			dtmfAction(num);
									break;
								default:
									//loopAction(num);
									break;
					}
				break;
  		case ONlINE:
  			if(ssp_slic[num].chipData.previousState==ONlINE)
  				if(ssp_slic[num].link_on==0)
  				{
  					setState(num, BUSY);
  					busyTone(num);
  				}
  		
  			break;
			case CALLERiD:
				//printf("\n-->CALLERiD");
				//callerid(num);
				setState(num, RINGING);
				//printf("\n						-->RINGING\n");
				break;
  		
			
  		
			case RINGING:
				
				//printf("\n-->RINGING");
				if (ssp_slic[num].chipData.ringCount>20){
					
				//	stopRinging(num);
					ssp_slic[num].chipData.ringCount=0;
  		
				setState(num, ONHOOK);
				//printf("\n						-->ONHOOK\n");
				}
				break;
  		
			case MAKEbUSY:
				//printf("\n-->MAKEbUSY");
				//disableOscillators(num);
				busyTone(num);
				setState(num, BUSY);
					//printf("\n						-->BUSY\n");
				ssp_slic[num].chipData.digit_count=0;
				break;
			case BUSY:
				loopAction(num);
				break;
			case MAKErINGbACK:
			//printf("\n-->MAKErINGbACK");
			//disableOscillators(num);
				ringBackTone(num);
				setState(num, RINGbACK);
			//	printf("\n						-->RINGbACK\n");
				ssp_slic[num].chipData.digit_count=0;
				break;
  		
  		
			case MAKEbUSYjAPAN:
				busyJapan(num);
				setState(num, RINGbACKjAPAN);
				ssp_slic[num].chipData.digit_count=0;
				break;
  		  case MAKErINGbACKjAPAN:
				ringBackJapan(num);
				setState(num, RINGbACKjAPAN);
				ssp_slic[num].chipData.digit_count=0;
				break;
			case MAKErEORDER:
			//printf("\n-->MAKErEORDER");
				reorderTone(num);
				setState(num, REORDER);
				//printf("\n						-->REORDER\n");
				ssp_slic[num].chipData.digit_count=0;
				break;
			case MAKEcONGESTION:
			//printf("\n-->MAKEcONGESTION");
				congestionTone(num);
				setState(num, CONGESTION);
				//printf("\n						-->CONGESTION\n");
				ssp_slic[num].chipData.digit_count=0;
				break;
			default:
				break;
	}

}
/*
void stateMachine(int num){
	//static int ringCount=0;
//	UINT32 opcode;
	int i=0;
	
	//opcode = SLIC_SPI_read(num, PROSLIC_INT3_MASK_REG);
	//opcode = SLIC_SPI_read(num, PROSLIC_INT3_STATUS_REG);
	//printf("\n						-->%s\n",stt[chipData.state]); 
	switch (ssp_slic[num].chipData.state)
	{


			//  Below are only the meta/transient states (transitions).
			//The actual precursor states are changed durring the event/interrupt handler.
			//I know this is unconventional but it does shrink down the code considerably.  	
			//Latter when I fold in the wait states and the delays I will put the stable states back here.	
			//	
			
  		
			case STATEcHANGE:
				//printf("\n-->STATEcHANGE");
				 ssp_slic[num].chipData.state=ssp_slic[num].chipData.newState;
					break; 
			case CALLBACK :
				//printf("\n-->CALLBACK");
  		
				ssp_slic[num].chipData.state = FIRSTrING;
				break; 
  		
			case CALLBACKpROGRAMMED:
				//printf("\n-->CALLBACKpROGRAMMED");
			
 				activateRinging(num);
				ssp_slic[num].chipData.state = PROGRAMMEDrING;
				//printf("\n						-->PROGRAMMEDrING\n");
				break; 
  		
  		//case OFFHOOK:
			case MAKEoFFHOOK: // Make dialtone 
				if(dma_demo != DMA_DEMO)
				{
					if(!gemini_ssp_hookstate(num)&&(ssp_slic[num].link_on==0)){
						//printf("\n-->MAKEoFFHOOK");
						dialTone(num);
						setState(num, DIALtONE);
						for(i=0;i<ssp_slic[num].chipData.digit_count;i++)
							ssp_slic[num].chipData.DTMF_digits[i]= 0x0;
						ssp_slic[num].chipData.dtmf_wait = 0;
						ssp_slic[num].chipData.digit_count=0;
					}
				}
				break;
			case LOOPtRANSITION:
				//printf("\n-->LOOPtRANSITION");			
					if (ssp_slic[num].chipData.version <= 2)
						initializeLoopDebounceReg(num);
					
						switch (ssp_slic[num].chipData.previousState){
														
								case RINGING:
								case FIRSTrING:
									setState(num, OFFHOOK);
									//printf("\n		stat			-->OFFHOOK\n");
						 			break;
								case DEFEREDcALLBACKpROGRAMMED:
									setState (num, CALLBACKpROGRAMMED);
									//printf("\n						-->CALLBACKpROGRAMMED\n");
								break;
  		
								case PRENEON:
									setupNeon(num);
									setState(num, NEON);
								break;
								default:
									loopAction(num);
						}
				break;
			case DTMFtRANISTION:
			//	printf("\n-->DTMFtRANISTION");
					//if(SLIC_SPI_read(num, PROSLIC_OFF_HOOK_STATUS_REG)&4)
					//{
					//	setState(num, ONHOOK);
					//	loopAction(num);
					//}
					switch (ssp_slic[num].chipData.previousState){
								case OFFHOOK:
								case BUSY:
								case RINGbACK:
									//SdisableOscillators(num);
								break;
								//case DTMFtRANISTION:
								case DIALtONE:
				//				printf("\n-->DIALtONE   disableOscillators");
									disableOscillators(num);
									setState(num, DIGITDECODING);
					//			printf("\n-->DIALtONE	dtmfAction");
					//				dtmfAction(num);
									break;
								case DIGITDECODING:
						//		printf("\n-->DTMFtRANISTION");
						//			dtmfAction(num);
									break;
								default:
									//loopAction(num);
									break;
					}
				break;
  		case ONlINE:
  			if(ssp_slic[num].chipData.previousState==ONlINE)
  				if(ssp_slic[num].link_on==0)
  				{
  					setState(num, BUSY);
  					busyTone(num);
  				}
  		
  			break;
			case CALLERiD:
				//printf("\n-->CALLERiD");
				//callerid(num);
				setState(num, RINGING);
				//printf("\n						-->RINGING\n");
				break;
  		
			
  		
			case RINGING:
				
				//printf("\n-->RINGING");
				if (ssp_slic[num].chipData.ringCount>20){
					//printf("\nring count > 6\n");
					stopRinging(num);
					ssp_slic[num].chipData.ringCount=0;
  		
				setState(num, ONHOOK);
				//printf("\n						-->ONHOOK\n");
				}
				break;
  		
			case MAKEbUSY:
				//printf("\n-->MAKEbUSY");
				//disableOscillators(num);
				busyTone(num);
				setState(num, BUSY);
					//printf("\n						-->BUSY\n");
				ssp_slic[num].chipData.digit_count=0;
				break;
			case BUSY:
				loopAction(num);
				break;
			case MAKErINGbACK:
			//printf("\n-->MAKErINGbACK");
			//disableOscillators(num);
				ringBackTone(num);
				setState(num, RINGbACK);
			//	printf("\n						-->RINGbACK\n");
				ssp_slic[num].chipData.digit_count=0;
				break;
  		
  		
			case MAKEbUSYjAPAN:
				busyJapan(num);
				setState(num, RINGbACKjAPAN);
				ssp_slic[num].chipData.digit_count=0;
				break;
  		  case MAKErINGbACKjAPAN:
				ringBackJapan(num);
				setState(num, RINGbACKjAPAN);
				ssp_slic[num].chipData.digit_count=0;
				break;
			case MAKErEORDER:
			//printf("\n-->MAKErEORDER");
				reorderTone(num);
				setState(num, REORDER);
				//printf("\n						-->REORDER\n");
				ssp_slic[num].chipData.digit_count=0;
				break;
			case MAKEcONGESTION:
			//printf("\n-->MAKEcONGESTION");
				congestionTone(num);
				setState(num, CONGESTION);
				//printf("\n						-->CONGESTION\n");
				ssp_slic[num].chipData.digit_count=0;
				break;
			default:
				break;
	}

}
*/
//static int gemini_slic_thread (SSP_SLIC *ssp_slic)
static int gemini_slic_thread (void)
{
	
	//SSP_SLIC *ssp_tmp = file_p->private_data;
	//unsigned int opcode=0;
	unsigned long  original_vec;
	int num;
#if 1	
	unsigned long shiftMask=1;
	 enum              // Declare enum type Days
	{
		OSC1_T1=0,  
		OSC1_T2=1,
		OSC2_T1=2,
		OSC2_T2=3,
		RING_T1=4,
		RING_T2=5,
		PULSE_T1=6,
		PULSE_T2=7,
		RING_TRIP=8,
		LOOP__STAT=9,
		PQ1=10,
		PQ2=11,
		PQ3=12,
		PQ4=13,
		PQ5=14,
		PQ6=15,
		DTMF=16, /* DTMF detected */
		INDIRECT=17, /* Indirect Reg Access ready */
		CAL_CM_BAL=18 /* Common Mode Calibration Error */
	} interruptCause;                // Variable today has type Days
#endif	 
	unsigned long       timeout;

	allow_signal(SIGTERM);
	 
	// num = ssp_slic->p.board;
	 for(num=0;num<NUMBER_OF_CHAN;num++)
	 {
			ssp_slic[num].chipData.eventNumber++;
			original_vec = ssp_slic[num].chipData.interrupt;
		}

	while(1)
	{
		

		
		 timeout = next_tick;
		do
		{
			timeout = interruptible_sleep_on_timeout (&thr_wait, timeout);
		} while (!signal_pending (current) && (timeout > 0));

		if (signal_pending (current))
		{
//			spin_lock_irq(&current->sigmask_lock);
			flush_signals(current);
//			spin_unlock_irq(&current->sigmask_lock);
		}

		if (time_to_die)
			break;
	//	rtnl_lock ();
		for(num=0;num<NUMBER_OF_CHAN;num++)
		{
				//////////////////////////////////////////////////////////////////
				
#if 1			
					ssp_slic[num].chipData.inwt = 0;
					shiftMask = 1;
				//////////////////////////////////////////////////////////////////	
						
					
						if(ssp_slic[num].chipData.interrupt)
						{
							for ( interruptCause=OSC1_T1 ; interruptCause <= CAL_CM_BAL ; interruptCause++)
							{
								if (shiftMask & ssp_slic[num].chipData.interrupt)
								{
									
									
									ssp_slic[num].chipData.interrupt &= ~shiftMask;   // clear interrupt cause
									                                 
									//printk((( interruptCause >=10) && (interruptCause<=11))?"\n %s":"\n(%s)  ", icause[interruptCause]);
									switch (interruptCause) {
										// Figure out what todo based on which one occured
										case OSC1_T1:
											ssp_slic[num].chipData.osc1_event = 1;
										//	printk("\n OSC1_T1 \n");
											break;
										case OSC1_T2:
										//	printk("\n OSC1_T2 \n");
											break;
										case OSC2_T1:
										//	printk("\n OSC2_T1 \n");
											break;
										case OSC2_T2:
										//	printk("\n OSC2_T2 \n");
											break;
										case RING_T1:
										//printk("\n RING_T1 \n");
											ssp_slic[num].chipData.ringCount++;
											//printk("\n RING_T1  : %d\n",ssp_slic[num].chipData.ringCount);
											if (ssp_slic[num].chipData.state==FIRSTrING)
											{ 
												ssp_slic[num].chipData.ringCount=1;
											//printk("\n RING_T1  	 --->   FIRSTrING\n");
												if (ssp_slic[num].chipData.version >2)
													setState(num, CALLERiD);
												else
													setState(num, RINGING);
											}
												
										break;
										case RING_T2:
								    	
												
											break;
										case PULSE_T1:
											break;
										case PULSE_T2:
											break;
										
								    	
										
										case RING_TRIP:
											//printk("\n RING_TRIP \n");
											if (ssp_slic[num].chipData.version <=2 )  // if REVISION B  set to active.
											{
												spin_lock_irqsave(&ssp_mutex, ssp_flags);
												goActive(num); // Rev B fix not needed 
								    		spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
											}
										case LOOP__STAT:
												//printk("\n LOOP__STAT \n");
												spin_lock_irqsave(&ssp_mutex, ssp_flags);
											groundShort(num); /* Check for grounded Tip or Ring Leads*/
											spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
											setState(num, LOOPtRANSITION);
											
											break;
								    	
								    	
										case PQ1:
										case PQ2:
										case PQ3:
										case PQ4:
										case PQ5:
										case PQ6:
											//printk("\n PQ6 \n");
											{	static unsigned long lastEventNumber =1;
												if (lastEventNumber != ssp_slic[num].chipData.eventNumber)  /*  We allow only one alarm per alarm event */
												{
													int i = interruptCause - PQ1;
													lastEventNumber = ssp_slic[num].chipData.eventNumber;
													powerLeakTest(num);
													powerUp(num);
												//	printk( "  %d time",ssp_slic[num].chipData.qLog[i]);
													if (ssp_slic[num].chipData.qLog[i]++>2)    
														//printk("\n exception(num, POWERaLARMQ1+i) \n");
														exception(num, POWERaLARMQ1+i);
													if(ssp_slic[num].chipData.qLog[i] >1) 
														printk( "s");
														
													clearAlarmBits(num);
													spin_lock_irqsave(&ssp_mutex, ssp_flags);
													goActive(num);
													spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
													setState(num, ONHOOK);
												}
													 
											}
								    	
											break;
										case DTMF:
											//printk("\n DTMF \n");
											setState(num, DTMFtRANISTION); 
												break;
								    	
										
										case INDIRECT:
											break;
										case CAL_CM_BAL:
											break;
									
								
									} //switch
								
									
								} //if
							  shiftMask<<=1;
							} //for
						}//if(ssp_slic[num].chipData.interrupt)
						ssp_slic[num].chipData.interrupt = 0;
						if(ssp_slic[num].chipData.state == CONVERSATION){
							
						}
						else{
						}
						//rtnl_unlock ();
						stateMachine(num);
						if((ssp_slic[num].link_on==0)&&(dma_demo != DMA_DEMO))
						{
							if(ssp_slic[num].chipData.digit_count>0)
							{
								ssp_slic[num].chipData.dtmf_wait++;
								if(ssp_slic[num].chipData.dtmf_wait > ((10*HZ)/next_tick))
								{
									if(ssp_slic[num].chipData.state!=MAKEbUSY)
									{
										setState(num, MAKEbUSY);
										printk("Wrong number !!\n");
									}
								}
							}
						}
#else
			stateMachine(num);
#endif						
			}//for(num=0;num<NUMBER_OF_CHAN;num++)			
	}//while(1)
	
	return 0;
}

static int gemini_ssp_set_linefeed(int num, int data)
{
	spin_lock_irqsave(&ssp_mutex, ssp_flags);
	SLIC_SPI_write(num, PROSLIC_LINEFEED_CTRL_REG, data);
	spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
	return 0;
}

int gemini_ssp_hookstate(int num)
{
	int opcode;
	spin_lock_irqsave(&ssp_mutex, ssp_flags);
	opcode = SLIC_SPI_read(num, PROSLIC_OFF_HOOK_STATUS_REG)&4?1:0;   //old
	//opcode = SLIC_SPI_read(num, PROSLIC_OFF_HOOK_STATUS_REG)&1?0:1;
	//if(opcode)
	//	setState(num, ONHOOK);
	//else
	//	setState(num, OFFHOOK);
	spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
	return opcode;
	// (1):On hook    (0):Off hook
}

static int gemini_ssp_get_linefeed(int num)
{
	int opcode;
	spin_lock_irqsave(&ssp_mutex, ssp_flags);
	opcode = SLIC_SPI_read(num, PROSLIC_LINEFEED_CTRL_REG);
	spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
	return opcode;
	
	//0x00	Open
	//0x11	Forward active
	//0x22	Forward on-hook transmission
	//0x33	TIP open
	//0x44	Ringing
	//0x55	Reverse active
	//0x66	Reverse on-hook transmission
	//0x77	RING open
}


static int gemini_ssp_alloc_dmabuf(void)
{
	int  j;
	printk("Buffer allocation for SSP DMA!\n");
	

		tbuf = kmalloc(TBUF_SIZE, GFP_ATOMIC);
		rbuf = kmalloc(TBUF_SIZE, GFP_ATOMIC);

		if (!tbuf||!rbuf) {
			printk("Buffer allocation for failed!\n");
			return -ENOMEM;
		}
		LinkAddrT = (UINT32 *)kmalloc(sizeof(DMA_LLP_t) * LLP_SIZE, GFP_ATOMIC);
  		LLPT = (DMA_LLP_t *)LinkAddrT;
  		LinkAddrR = (UINT32 *)kmalloc(sizeof(DMA_LLP_t) * LLP_SIZE, GFP_ATOMIC);
  		LLPR = (DMA_LLP_t *)LinkAddrR;
  		
  		for(j=0;j<LLP_SIZE;j++)//Tx
  		{
  			LLPT[j].src_addr = __pa((UINT32)tbuf + (((j)%LLP_SIZE) * DBUF_SIZE));	
  			LLPT[j].dst_addr = SL2312_SSP_CTRL_BASE+SSP_WRITE_PORT;
  			LLPT[j].llp = __pa(((UINT32)&LLPT[((j+1)%LLP_SIZE)]))|0x1;
  			LLPT[j].ctrl_size = (DBUF_SIZE/4)|0x040a<<16;
  		}
  		
  		for(j=0;j<LLP_SIZE;j++)//Rx
  		{
  			LLPR[j].src_addr = SL2312_SSP_CTRL_BASE+SSP_READ_PORT;
  			LLPR[j].dst_addr = __pa((UINT32)rbuf + (((j)%LLP_SIZE) * DBUF_SIZE));	
  			LLPR[j].llp = __pa(((UINT32)&LLPR[((j+1)%LLP_SIZE)]))|0x1;
  			LLPR[j].ctrl_size = (DBUF_SIZE)|0x00A1<<16;//0x10A1<<16;    //tx:100a rx:1021
  		}

}

static int gemini_ssp_alloc(int num)
{


	printk("Buffer allocation for phone%d !\n",num);
	
	if(ssp_slic[num].chipData.in_release == 0)
	{
		ssp_slic[num].cw2tbuf = kmalloc((TBUF_SIZE/NUMBER_OF_CHAN), GFP_ATOMIC);
		ssp_slic[num].cr2rbuf = kmalloc((TBUF_SIZE/NUMBER_OF_CHAN), GFP_ATOMIC);
		if (!ssp_slic[num].cw2tbuf||!ssp_slic[num].cr2rbuf) {
			printk("Buffer allocation for failed!\n");
			return -ENOMEM;
		}
	}
	/*
	printk("Buffer allocation for SSP!\n");
	
	if(ssp_slic[num].chipData.in_release == 0)
	{
		ssp_slic->tbuf = kmalloc(TBUF_SIZE, GFP_ATOMIC);
		ssp_slic->rbuf = kmalloc(TBUF_SIZE, GFP_ATOMIC);
		ssp_slic->cw2tbuf = kmalloc(TBUF_SIZE, GFP_ATOMIC);
		ssp_slic->cr2rbuf = kmalloc(TBUF_SIZE, GFP_ATOMIC);
		if (!ssp_slic->tbuf||!ssp_slic->rbuf||!ssp_slic->cw2tbuf||!ssp_slic->cr2rbuf) {
			printk("Buffer allocation for failed!\n");
			return -ENOMEM;
		}
		LinkAddrT = (UINT32 *)kmalloc(sizeof(DMA_LLP_t) * LLP_SIZE, GFP_ATOMIC);
  		LLPT = (DMA_LLP_t *)LinkAddrT;
  		LinkAddrR = (UINT32 *)kmalloc(sizeof(DMA_LLP_t) * LLP_SIZE, GFP_ATOMIC);
  		LLPR = (DMA_LLP_t *)LinkAddrR;
  		
  		for(j=0;j<LLP_SIZE;j++)//Tx
  		{
  			LLPT[j].src_addr = __pa((UINT32)ssp_slic->tbuf + (((j)%LLP_SIZE) * DBUF_SIZE));	
  			LLPT[j].dst_addr = SL2312_SSP_CTRL_BASE+SSP_WRITE_PORT;
  			LLPT[j].llp = __pa(((UINT32)&LLPT[((j+1)%LLP_SIZE)]))|0x1;
  			LLPT[j].ctrl_size = (DBUF_SIZE/4)|0x040a<<16;
  		}
  		
  		for(j=0;j<LLP_SIZE;j++)//Rx
  		{
  			LLPR[j].src_addr = SL2312_SSP_CTRL_BASE+SSP_READ_PORT;
  			LLPR[j].dst_addr = __pa((UINT32)ssp_slic->rbuf + (((j)%LLP_SIZE) * DBUF_SIZE));	
  			LLPR[j].llp = __pa(((UINT32)&LLPR[((j+1)%LLP_SIZE)]))|0x1;
  			LLPR[j].ctrl_size = (DBUF_SIZE)|0x00A1<<16;//0x10A1<<16;    //tx:100a rx:1021
  		}

	}
	*/
	return 0;
}

static int gemini_ssp_open(struct phone_device *p, struct file *file_p)
{
	//printk("%s : start !!\n",__func__);
	int num;
	
	num=p->board;
//
//	file_p->private_data = j;
	file_p->private_data = &ssp_slic[num];

        if (file_p->f_mode & FMODE_READ) {
		if(!ssp_slic[num].readers) {
	                ssp_slic[num].readers++;
        	} else {
                	return -EBUSY;
		}
        }

	if (file_p->f_mode & FMODE_WRITE) {
		if(!ssp_slic[num].writers) {
			ssp_slic[num].writers++;
		} else {
			if (file_p->f_mode & FMODE_READ){
				ssp_slic[num].readers--;
			}
			return -EBUSY;
		}
	}
	
	//if(gemini_ssp_alloc(num))
	//	return -1;


//	MOD_INC_USE_COUNT;

	return 0;
}

int verifyIndirectReg(int num,UINT8 address, UINT16 should_be_value)
{ 
	int error_flag ;
	unsigned short value;
		value = SLIC_SPI_ind_read(num, address);
		error_flag = (should_be_value != value);
		
		if ( error_flag )
		{
			printk("\n   iREG %d = %X  should be %X ",address,value,should_be_value );			
		}	
		return error_flag;
}	

//Checks that the indirect registers are properly set to their default values. 
//Discontinues execution if they are not.
int verifyIndirectRegisters(int num)										
{		
	int error=0;

	error |= verifyIndirectReg(num, 	0	,	0x55C2		);	//	0x55C2	DTMF_ROW_0_PEAK
	error |= verifyIndirectReg(num, 	1	,	0x51E6		);	//	0x51E6	DTMF_ROW_1_PEAK
	error |= verifyIndirectReg(num, 	2	,	0x4B85		);	//	0x4B85	DTMF_ROW2_PEAK
	error |= verifyIndirectReg(num, 	3	,	0x4937		);	//	0x4937	DTMF_ROW3_PEAK
	error |= verifyIndirectReg(num, 	4	,	0x3333		);	//	0x3333	DTMF_COL1_PEAK
	error |= verifyIndirectReg(num, 	5	,	0x0202		);	//	0x0202	DTMF_FWD_TWIST
	error |= verifyIndirectReg(num, 	6	,	0x0202		);	//	0x0202	DTMF_RVS_TWIST
	error |= verifyIndirectReg(num, 	7	,	0x0198		);	//	0x0198	DTMF_ROW_RATIO
	error |= verifyIndirectReg(num, 	8	,	0x0198		);	//	0x0198	DTMF_COL_RATIO
	error |= verifyIndirectReg(num, 	9	,	0x0611		);	//	0x0611	DTMF_ROW_2ND_ARM
	error |= verifyIndirectReg(num, 	10	,	0x0202		);	//	0x0202	DTMF_COL_2ND_ARM
	error |= verifyIndirectReg(num, 	11	,	0x00E5		);	//	0x00E5	DTMF_PWR_MIN_
	error |= verifyIndirectReg(num, 	12	,	0x0A1C		);	//	0x0A1C	DTMF_OT_LIM_TRES
	error |= verifyIndirectReg(num, 	13	,	0x7b30		);	//	0x7b30	OSC1_COEF
	error |= verifyIndirectReg(num, 	14	,	0x0063		);	//	0x0063	OSC1X
	error |= verifyIndirectReg(num, 	15	,	0x0000		);	//	0x0000	OSC1Y
	error |= verifyIndirectReg(num, 	16	,	0x7870		);	//	0x7870	OSC2_COEF
	error |= verifyIndirectReg(num, 	17	,	0x007d		);	//	0x007d	OSC2X
	error |= verifyIndirectReg(num, 	18	,	0x0000		);	//	0x0000	OSC2Y
	error |= verifyIndirectReg(num, 	19	,	0x0000		);	//	0x0000	RING_V_OFF
	error |= verifyIndirectReg(num, 	20	,	0x7EF0		);	//	0x7EF0	RING_OSC
	error |= verifyIndirectReg(num, 	21	,	0x0160		);	//	0x0160	RING_X
	error |= verifyIndirectReg(num, 	22	,	0x0000		);	//	0x0000	RING_Y
	error |= verifyIndirectReg(num, 	23	,	0x2000		);	//	0x2000	PULSE_ENVEL
	error |= verifyIndirectReg(num, 	24	,	0x2000		);	//	0x2000	PULSE_X
	error |= verifyIndirectReg(num, 	25	,	0x0000		);	//	0x0000	PULSE_Y
	error |= verifyIndirectReg(num, 	26	,	0x4000		);	//	0x4000	RECV_DIGITAL_GAIN
	error |= verifyIndirectReg(num, 	27	,	0x4000		);	//	0x4000	XMIT_DIGITAL_GAIN
	error |= verifyIndirectReg(num, 	28	,	0x1000		);	//	0x1000	LOOP_CLOSE_TRES
	error |= verifyIndirectReg(num, 	29	,	0x3600		);	//	0x3600	RING_TRIP_TRES
	error |= verifyIndirectReg(num, 	30	,	0x1000		);	//	0x1000	COMMON_MIN_TRES
	error |= verifyIndirectReg(num, 	31	,	0x0200		);	//	0x0200	COMMON_MAX_TRES
	error |= verifyIndirectReg(num, 	32	,	0x7c0		);	//	0x7c0  	PWR_ALARM_Q1Q2
	error |= verifyIndirectReg(num, 	33	,	0x376f		);	//	0x2600	PWR_ALARM_Q3Q4
	error |= verifyIndirectReg(num, 	34	,	0x1B80		);	//	0x1B80	PWR_ALARM_Q5Q6
	error |= verifyIndirectReg(num, 	35	,	0x8000		);	//	0x8000	LOOP_CLSRE_FlTER
	error |= verifyIndirectReg(num, 	36	,	0x0320		);	//	0x0320	RING_TRIP_FILTER
	error |= verifyIndirectReg(num, 	37	,	0x08c		);	//	0x08c	TERM_LP_POLE_Q1Q2
	error |= verifyIndirectReg(num, 	38	,	0x0100		);	//	0x0100	TERM_LP_POLE_Q3Q4
	error |= verifyIndirectReg(num, 	39	,	0x0010		);	//	0x0010	TERM_LP_POLE_Q5Q6
	error |= verifyIndirectReg(num, 	40	,	0x0C00		);	//	0x0C00	CM_BIAS_RINGING
	error |= verifyIndirectReg(num, 	41	,	0x0C00		);	//	0x0C00	DCDC_MIN_V
	error |= verifyIndirectReg(num, 	43	,	0x00DA		);	//	0x1000	LOOP_CLOSE_TRES Low
	error |= verifyIndirectReg(num, 	99	,	0x00DA		);	//	0x00DA	FSK 0 FREQ PARAM
	error |= verifyIndirectReg(num, 	100	,	0x6B60		);	//	0x6B60	FSK 0 AMPL PARAM
	error |= verifyIndirectReg(num, 	101	,	0x0074		);	//	0x0074	FSK 1 FREQ PARAM
	error |= verifyIndirectReg(num, 	102	,	0x79C0		);	//	0x79C0	FSK 1 AMPl PARAM
	error |= verifyIndirectReg(num, 	103	,	0x1120		);	//	0x1120	FSK 0to1 SCALER
	error |= verifyIndirectReg(num, 	104	,	0x3BE0		);	//	0x3BE0	FSK 1to0 SCALER
	
	return error;
}

void printkreq_Revision(int num)
{

	int freq;

	char* freqs[ ] = {"8192","4028","2048","1024","512","256","1536","768","32768"};

// Turn on all interrupts
	freq=SLIC_SPI_read(num, 13)>>4;  /* Read the frequency */
	printk("Phone%d PCM clock =  %s KHz   Rev %c \n",num,   freqs[freq], 'A'-1 + version(num)); 
}

UINT8 loopStatus(int num)
{
	
	//if((SLIC_SPI_read(num, PROSLIC_OFF_HOOK_STATUS_REG) & 0x01))
	//	setState(num, OFFHOOK);
	//else
	//	setState(num, ONHOOK);
 return (SLIC_SPI_read(num, PROSLIC_OFF_HOOK_STATUS_REG) & 0x03);//0x3);  //68

}

//Sets the state-machine future state of the software to a new state.
//This setting of the state will occur the next time the state-machine executes.
void setState(int num,int newState)
{
	ssp_slic[num].chipData.previousState=ssp_slic[num].chipData.state;
	ssp_slic[num].chipData.newState= newState;
	//ssp_slic[num].chipData.state = newState;

	ssp_slic[num].chipData.state=STATEcHANGE;
	switch (newState){
  
			 case CALLERiD:
				 //ssp_slic[num].chipData.eventEnable=0;
				 break;
			 case RINGING:
				 ssp_slic[num].chipData.eventEnable=1;
				 break;
			 
  
	}
	
}

void clearInterrupts(int num)
{
	UINT32 opcode;
	spin_lock_irqsave(&ssp_mutex, ssp_flags);
	//SLIC_SPI_write(num, 	PROSLIC_INT1_STATUS_REG	,	0xff	);//0xff	Normal Oper. Interrupt Register 1 (clear with 0xFF)
	//SLIC_SPI_write(num, 	PROSLIC_INT2_STATUS_REG	,	0xff	);//0xff	Normal Oper. Interrupt Register 2 (clear with 0xFF)
	//SLIC_SPI_write(num, 	PROSLIC_INT3_STATUS_REG	,	0xff	);//0xff	Normal Oper. Interrupt Register 3 (clear with 0xFF)
	opcode = SLIC_SPI_read(num, PROSLIC_INT1_STATUS_REG);
	SLIC_SPI_write(num, 	PROSLIC_INT1_STATUS_REG	,	opcode	);//0xff	Normal Oper. Interrupt Register 1 (clear with 0xFF)
	opcode = SLIC_SPI_read(num, PROSLIC_INT2_STATUS_REG);
	SLIC_SPI_write(num, 	PROSLIC_INT2_STATUS_REG	,	opcode	);//0xff	Normal Oper. Interrupt Register 2 (clear with 0xFF)
	opcode = SLIC_SPI_read(num, PROSLIC_INT3_STATUS_REG);
	SLIC_SPI_write(num, 	PROSLIC_INT3_STATUS_REG	,	opcode	);//0xff	Normal Oper. Interrupt Register 3 (clear with 0xFF)
	spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
}

//Sets direct Register 64 to 1 which makes the ProSLIC power the phone line 
//forward active.
void goActive(int num)

{
	unsigned int opcode;
	
	SLIC_SPI_write(num, PROSLIC_LINEFEED_CTRL_REG,1);	/* LOOP STATE REGISTER SET TO ACTIVE */
							/* Active works for on-hook and off-hook see spec. */
							/* The phone hook-switch sets the off-hook and on-hook substate*/
	opcode = SLIC_SPI_read(num, PROSLIC_LINEFEED_CTRL_REG);
	
	//sleep(100);
//	mdelay(100);
// temp	if ((SLIC_SPI_read(num, 80) < 2) || SLIC_SPI_read(num, 81) < 2) exception(num, TIPoRrINGgROUNDsHORT); /* Check for grounded Tip or Ring Leads*/

}

int calibrate(int num)
{ 
	unsigned char x,y,i=0,progress=0; // progress contains individual bits for the Tip and Ring Calibrations

	unsigned char   DRvalue, data;
	int timeOut,nCalComplete;

/* Do Flush durring powerUp and calibrate */
    //printk("\n*****************>  calibrate\n");


			SLIC_SPI_write(num, PROSLIC_INT1_MASK_REG,0);//(0)  Disable all interupts in DR21
	        SLIC_SPI_write(num, PROSLIC_INT2_MASK_REG,0);//(0)	Disable all interupts in DR21
	        SLIC_SPI_write(num, PROSLIC_INT3_MASK_REG,0);//(0)	Disabel all interupts in DR21
	        SLIC_SPI_write(num, PROSLIC_LINEFEED_CTRL_REG,0);//(0)

	   
			SLIC_SPI_write(num, PROSLIC_CALIBRATION2_REG,0x1E); //(0x18)Calibrations without the ADC and DAC offset and without common mode calibration.
			SLIC_SPI_write(num, PROSLIC_CALIBRATION1_REG,0x47); //(0x47)	Calibrate common mode and differential DAC mode DAC + ILIM

	   
 
       	do 
		{
        	DRvalue = SLIC_SPI_read(num, PROSLIC_CALIBRATION1_REG);
            //nCalComplete = DRvalue==0;// (0)  When Calibration completes DR 96 will be zero
			//nCalComplete = DRvalue ? 0 : 1;
			nCalComplete = (DRvalue != 0);
			//timeOut= i++> 800;// (800) MS
			timeOut= i++> 800;//timeOut = i++ > (800 ? 1 : 0);
			//delay(1);
			mdelay(10);
			schedule();
		}
		while (nCalComplete&&!timeOut);
	   
		if (timeOut)
		{
			SLIC_SPI_write(num, PROSLIC_INT1_MASK_REG,0xff);//0x10);//0xff);
    		SLIC_SPI_write(num, PROSLIC_INT2_MASK_REG,0xff);
    		//SLIC_SPI_write(num, PROSLIC_INT3_MASK_REG,0xff);
    		SLIC_SPI_write(num, PROSLIC_INT3_MASK_REG,0x05);
			return (int)-1;
    	}       
        
    
//Initialized DR 98 and 99 to get consistant results.
// 98 and 99 are the results registers and the search should have same intial conditions.



/*******************************The following is the manual gain mismatch calibration****************************/
/*******************************This is also available as a function *******************************************/
	//delay(10);
	mdelay(10);
	/*
	SLIC_SPI_ind_write(num, 88,0);
	SLIC_SPI_ind_write(num, 89,0);
	SLIC_SPI_ind_write(num, 90,0);
	SLIC_SPI_ind_write(num, 91,0);
	SLIC_SPI_ind_write(num, 92,0);
	SLIC_SPI_ind_write(num, 93,0);
	*/

	//SLIC_SPI_write(num, PROSLIC_RING_GAIN_MIS_CALIB_REG,0x10); // This is necessary if the calibration occurs other than at reset time
	SLIC_SPI_write(num, PROSLIC_TIP_GAIN_MIS_CALIB_REG,0x10);
	
	for ( i=0x1f; i>0; i--)
	{
		SLIC_SPI_write(num, PROSLIC_RING_GAIN_MIS_CALIB_REG	,i);  //98
		//delay(40);
		mdelay(40);
		if((SLIC_SPI_read(num, PROSLIC_IQ5_REG)) == 0) //88
		{	progress|=1;
		x=i;
		break;
		}
	} // for



	for ( i=0x1f; i>0; i--)
	{
		SLIC_SPI_write(num, PROSLIC_TIP_GAIN_MIS_CALIB_REG,i); //99
		//delay(40);
		mdelay(40);
		if((SLIC_SPI_read(num, PROSLIC_IQ6_REG)) == 0){  //89
			progress|=2;
			y=i;
		break;
		}
	
	}//for
	//------------------------------
	// STEP 17-19:  Long Balance Cal
	//------------------------------
	data = (1<<2);//ENB2_DR23
		SLIC_SPI_write(num,PROSLIC_INT3_MASK_REG,data);// enable interrupt for the balance Cal
/*******************************The preceding is the manual gain mismatch calibration****************************/
/**********************************The following is the longitudinal Balance Cal***********************************/

	goActive(num);
  	if(loopStatus(num) & 1)//4)
  	{
  			printk("Calibration failure due to off-hook phone\n");
  		//	SLIC_SPI_write(num, PROSLIC_INT1_MASK_REG,0xff);
    	//	SLIC_SPI_write(num, PROSLIC_INT2_MASK_REG,0xff);
    	//	//SLIC_SPI_write(num, PROSLIC_INT3_MASK_REG,0xff);
    	//	SLIC_SPI_write(num, PROSLIC_INT3_MASK_REG,0x05);
		  return ERRORCODE_LONGBALCAL ;
	}

	SLIC_SPI_write(num, PROSLIC_LINEFEED_CTRL_REG,0);
	

	//SLIC_SPI_write(num, PROSLIC_INT3_MASK_REG,1<<2);  // enable interrupt for the balance Cal
	SLIC_SPI_write(num, PROSLIC_CALIBRATION2_REG,0x01); // this is a singular calibration bit for longitudinal calibration
	SLIC_SPI_write(num, PROSLIC_CALIBRATION1_REG,0x40);
	data = SLIC_SPI_read(num, PROSLIC_CALIBRATION1_REG);
	do{
		data = SLIC_SPI_read(num, PROSLIC_CALIBRATION1_REG);
	} while(data != 0 );

      //   (SLIC_SPI_read(num, PROSLIC_CALIBRATION1_REG) != 0 );
    data = SLIC_SPI_read(num, PROSLIC_INT3_STATUS_REG);
	if (data&0x4)
		return CM_CAL_ERR;
	
   	SLIC_SPI_write(num, PROSLIC_INT1_MASK_REG,0xff);//0x10);//0xff);
    SLIC_SPI_write(num, PROSLIC_INT2_MASK_REG,0xff);
    //SLIC_SPI_write(num, PROSLIC_INT3_MASK_REG,0xff);
    SLIC_SPI_write(num, PROSLIC_INT3_MASK_REG,0x05);


/**********************************The preceding is the longitudinal Balance Cal***********************************/
	//printk("\n<*****************  calibrate\n");
	return(0);

}// End of calibration

void SLIC_init_reg_set(int num)
{
	
	int i;
	
	
	SLIC_SPI_write(num, 0,	INIT_DR0	);//0X00	Serial Interface
SLIC_SPI_write(num, 1,	0x3c);//INIT_DR1	);//0X28	PCM Mode
i = SLIC_SPI_read(num, 1);
SLIC_SPI_write(num, 2,	INIT_DR2	);//0X00	PCM TX Clock Slot Low UINT8 (1 PCLK cycle/LSB)
SLIC_SPI_write(num, 3,	INIT_DR3	);//0x00	PCM TX Clock Slot High UINT8
SLIC_SPI_write(num, 4,	INIT_DR4	);//0x00	PCM RX Clock Slot Low UINT8 (1 PCLK cycle/LSB)
SLIC_SPI_write(num, 5,	INIT_DR5	);//0x00	PCM RX Clock Slot High UINT8
SLIC_SPI_write(num, 8,	INIT_DR8	);//0X00	Loopbacks (digital loopback default)
SLIC_SPI_write(num, 9,	INIT_DR9_MUTE	);//0x00	Transmit and receive path gain and control
SLIC_SPI_write(num, 10,	INIT_DR10	);//0X28	Initialization Two-wire impedance (600  and enabled)
SLIC_SPI_write(num, 11,	INIT_DR11	);//0x33	Transhybrid Balance/Four-wire Return Loss
SLIC_SPI_write(num, 18,	INIT_DR18	);//0xff	Normal Oper. Interrupt Register 1 (clear with 0xFF)
SLIC_SPI_write(num, 19,	INIT_DR19	);//0xff	Normal Oper. Interrupt Register 2 (clear with 0xFF)
SLIC_SPI_write(num, 20,	INIT_DR20	);//0xff	Normal Oper. Interrupt Register 3 (clear with 0xFF)
SLIC_SPI_write(num, 21,	INIT_DR21	);//0xff	Interrupt Mask 1
SLIC_SPI_write(num, 22,	INIT_DR22	);//0xff	Initialization Interrupt Mask 2
SLIC_SPI_write(num, 23,	INIT_DR23	);//0xff	 Initialization Interrupt Mask 3
SLIC_SPI_write(num, 32,	INIT_DR32	);//0x00	Oper. Oscillator 1 Controltone generation
SLIC_SPI_write(num, 33,	INIT_DR33	);//0x00	Oper. Oscillator 2 Controltone generation
SLIC_SPI_write(num, 34,	INIT_DR34	);//0X18	34 0x22 0x00 Initialization Ringing Oscillator Control
SLIC_SPI_write(num, 35,	INIT_DR35	);//0x00	Oper. Pulse Metering Oscillator Control
SLIC_SPI_write(num, 36,	INIT_DR36	);//0x00	36 0x24 0x00 Initialization OSC1 Active Low UINT8 (125 탎/LSB)
SLIC_SPI_write(num, 37,	INIT_DR37	);//0x00	37 0x25 0x00 Initialization OSC1 Active High UINT8 (125 탎/LSB)
SLIC_SPI_write(num, 38,	INIT_DR38	);//0x00	38 0x26 0x00 Initialization OSC1 Inactive Low UINT8 (125 탎/LSB)
SLIC_SPI_write(num, 39,	INIT_DR39	);//0x00	39 0x27 0x00 Initialization OSC1 Inactive High UINT8 (125 탎/LSB)
SLIC_SPI_write(num, 40,	INIT_DR40	);//0x00	40 0x28 0x00 Initialization OSC2 Active Low UINT8 (125 탎/LSB)
SLIC_SPI_write(num, 41,	INIT_DR41	);//0x00	41 0x29 0x00 Initialization OSC2 Active High UINT8 (125 탎/LSB)
SLIC_SPI_write(num, 42,	INIT_DR42	);//0x00	42 0x2A 0x00 Initialization OSC2 Inactive Low UINT8 (125 탎/LSB)
SLIC_SPI_write(num, 43,	INIT_DR43	);//0x00	43 0x2B 0x00 Initialization OSC2 Inactive High UINT8 (125 탎/LSB)
SLIC_SPI_write(num, 44,	INIT_DR44	);//0x00	44 0x2C 0x00 Initialization Pulse Metering Active Low UINT8 (125 탎/LSB)
SLIC_SPI_write(num, 45,	INIT_DR45	);//0x00	45 0x2D 0x00 Initialization Pulse Metering Active High UINT8 (125 탎/LSB)
SLIC_SPI_write(num, 46,	INIT_DR46	);//0x00	46 0x2E 0x00 Initialization Pulse Metering Inactive Low UINT8 (125 탎/LSB)
SLIC_SPI_write(num, 47,	INIT_DR47	);//0x00	47 0x2F 0x00 Initialization Pulse Metering Inactive High UINT8 (125 탎/LSB)
SLIC_SPI_write(num, 48,	INIT_DR48	);//0X80	48 0x30 0x00 0x80 Initialization Ringing Osc. Active Timer Low UINT8 (2 s,125 탎/LSB)
SLIC_SPI_write(num, 49,	INIT_DR49	);//0X3E	49 0x31 0x00 0x3E Initialization Ringing Osc. Active Timer High UINT8 (2 s,125 탎/LSB)
SLIC_SPI_write(num, 50,	INIT_DR50	);//0X00	50 0x32 0x00 0x00 Initialization Ringing Osc. Inactive Timer Low UINT8 (4 s, 125 탎/LSB)
SLIC_SPI_write(num, 51,	INIT_DR51	);//0X7D	51 0x33 0x00 0x7D Initialization Ringing Osc. Inactive Timer High UINT8 (4 s, 125 탎/LSB)
SLIC_SPI_write(num, 52,	INIT_DR52	);//0X00	52 0x34 0x00 Normal Oper. FSK Data Bit
SLIC_SPI_write(num, 63,	INIT_DR63	);//0X54	63 0x3F 0x54 Initialization Ringing Mode Loop Closure Debounce Interval
SLIC_SPI_write(num, 64,	INIT_DR64	);//0x00	64 0x40 0x00 Normal Oper. Mode UINT8뾭rimary control
SLIC_SPI_write(num, 65,	INIT_DR65	);//0X61	65 0x41 0x61 Initialization External Bipolar Transistor Settings
SLIC_SPI_write(num, 66,	INIT_DR66	);//0X03	66 0x42 0x03 Initialization Battery Control
SLIC_SPI_write(num, 67,	INIT_DR67	);//0X1F	67 0x43 0x1F Initialization Automatic/Manual Control
SLIC_SPI_write(num, 69,	INIT_DR69	);//0X0C	69 0x45 0x0A 0x0C Initialization Loop Closure Debounce Interval (1.25 ms/LSB)
SLIC_SPI_write(num, 70,	INIT_DR70	);//0X0A	70 0x46 0x0A Initialization Ring Trip Debounce Interval (1.25 ms/LSB)
SLIC_SPI_write(num, 71,	INIT_DR71	);//0X01	71 0x47 0x00 0x01 Initialization Off-Hook Loop Current Limit (20 mA + 3 mA/LSB)
SLIC_SPI_write(num, 72,	INIT_DR72	);//0X20	72 0x48 0x20 Initialization On-Hook Voltage (open circuit voltage) = 48 V(1.5 V/LSB)
SLIC_SPI_write(num, 73,	INIT_DR73	);//0X02	73 0x49 0x02 Initialization Common Mode VoltageVCM = 3 V(1.5 V/LSB)
SLIC_SPI_write(num, 74,	INIT_DR74	);//0X32	74 0x4A 0x32 Initialization VBATH (ringing) = 75 V (1.5 V/LSB)
SLIC_SPI_write(num, 75,	INIT_DR75	);//0X10	75 0x4B 0x10 Initialization VBATL (off-hook) = 24 V (TRACK = 0)(1.5 V/LSB)
if (chipType(num) != 3)
SLIC_SPI_write(num, 92,	INIT_DR92	);//0x7f	92 0x5C 0xFF 7F Initialization DCDC Converter PWM Period (61.035 ns/LSB)
else
SLIC_SPI_write(num, 92,	INIT_SI3210M_DR92	);//0x7f	92 0x5C 0xFF 7F Initialization DCDC Converter PWM Period (61.035 ns/LSB)

SLIC_SPI_write(num, 93,	INIT_DR93	);//0x14	93 0x5D 0x14 0x19 Initialization DCDC Converter Min. Off Time (61.035 ns/LSB)
SLIC_SPI_write(num, 96,	INIT_DR96	);//0x00	96 0x60 0x1F Initialization Calibration Control Register 1(written second and starts calibration)
SLIC_SPI_write(num, 97,	INIT_DR97	);//0X1F	97 0x61 0x1F Initialization Calibration Control Register 2(written before Register 96)
SLIC_SPI_write(num, 98,	INIT_DR98	);//0X10	98 0x62 0x10 Informative Calibration result (see data sheet)
SLIC_SPI_write(num, 99,	INIT_DR99	);//0X10	99 0x63 0x10 Informative Calibration result (see data sheet)
SLIC_SPI_write(num, 100,	INIT_DR100	);//0X11	100 0x64 0x11 Informative Calibration result (see data sheet)
SLIC_SPI_write(num, 101,	INIT_DR101	);//0X11	101 0x65 0x11 Informative Calibration result (see data sheet)
SLIC_SPI_write(num, 102,	INIT_DR102	);//0x08	102 0x66 0x08 Informative Calibration result (see data sheet)
SLIC_SPI_write(num, 103,	INIT_DR103	);//0x88	103 0x67 0x88 Informative Calibration result (see data sheet)
SLIC_SPI_write(num, 104,	INIT_DR104	);//0x00	104 0x68 0x00 Informative Calibration result (see data sheet)
SLIC_SPI_write(num, 105,	INIT_DR105	);//0x00	105 0x69 0x00 Informative Calibration result (see data sheet)
SLIC_SPI_write(num, 106,	INIT_DR106	);//0x20	106 0x6A 0x20 Informative Calibration result (see data sheet)
SLIC_SPI_write(num, 107,	INIT_DR107	);//0x08	107 0x6B 0x08 Informative Calibration result (see data sheet)
SLIC_SPI_write(num, 108,	INIT_DR108	);//0xEB	108 0x63 0x00 0xEB Initialization Feature enhancement register

	
}

UINT8 powerLeakTest(int num)
{ 
	unsigned char vBat; //int i=0 ;
	spin_lock_irqsave(&ssp_mutex, ssp_flags);
	SLIC_SPI_write(num, PROSLIC_LINEFEED_CTRL_REG,0);
	
	SLIC_SPI_write(num, PROSLIC_POWER_DOWN1_CTRL_REG, 0x10); 
	mdelay(1000);  // one second
	//sleep (1000);  // one second
	vBat=SLIC_SPI_read(num, PROSLIC_VBAT_HIGH_SENSE_REG);
	if (vBat < 0x4)  // 6 volts
	 	printk("\n execption -> POWERlEAK \n");  //POWERlEAK
	 spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
	return vBat;
}

//This function powers up the ProSLIC and monitors its progress.
UINT8 powerUp(int num)
{ 
	unsigned char vBat, vBatTarget, data,vBatProg, opcode; 
	int i=0, initialTime, powerTime=0;
	spin_lock_irqsave(&ssp_mutex, ssp_flags);

	if (chipType(num) == 3)  // M version correction
	{
		SLIC_SPI_write(num, PROSLIC_DC_TO_DC_PERIOD_REG, 0x60);// M version
		SLIC_SPI_write(num, PROSLIC_DC_TO_DC_SWITCH_REG, 0x38);// M version
	}
	else	
	{
		SLIC_SPI_write(num, PROSLIC_DC_TO_DC_SWITCH_REG, 0x12);//0x19); 
		SLIC_SPI_write(num, PROSLIC_DC_TO_DC_PERIOD_REG, 0xff); /* set the period of the DC-DC converter to 1/64 kHz  START OUT SLOW*/
	}
	mdelay(100);
	initialTime= jiffies;//clock();
	SLIC_SPI_write(num, PROSLIC_POWER_DOWN1_CTRL_REG, 0); /* Engage the DC-DC converter */
	  
	 mdelay(500);
	//0xc0 = 12 * 16 * 0.375 =96 * 0.75 = 72 V.  
	vBatProg = SLIC_SPI_read(num, PROSLIC_VBAT_HIGH_REG);
	vBatTarget = ((short)vBatProg*15)/10;  //target in volts
	vBatTarget = ((vBatTarget-6)*200)/75;
	vBat=SLIC_SPI_read(num, PROSLIC_VBAT_HIGH_SENSE_REG);
	spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
	while (vBat < vBatTarget) 
	{ 
		schedule();
		//delay(1);
		mdelay(10);
		spin_lock_irqsave(&ssp_mutex, ssp_flags);
		vBat=SLIC_SPI_read(num, PROSLIC_VBAT_HIGH_SENSE_REG);
		spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
		++i;
		if (i > 300) 
		{
			exception(num, TIMEoUTpOWERuP);
			break;
		}
	}
	spin_lock_irqsave(&ssp_mutex, ssp_flags);
	// Program desired PWM rate and start calibraton
	if (chipType(num) == 3){  // M version correction
		data = INIT_SI3210M_DR92;
		SLIC_SPI_write(num,PROSLIC_DC_TO_DC_PERIOD_REG, data);
		data = INIT_SI3210M_DR93;
		SLIC_SPI_write(num,PROSLIC_DC_TO_DC_SWITCH_REG, data);
		mdelay(30);
		data = 0x80|INIT_SI3210M_DR93;
		SLIC_SPI_write(num,PROSLIC_DC_TO_DC_SWITCH_REG, data);
	}
	else{
		data = INIT_DR92;
		SLIC_SPI_write(num,PROSLIC_DC_TO_DC_PERIOD_REG, data);
		data = INIT_DR93;
		SLIC_SPI_write(num,PROSLIC_DC_TO_DC_SWITCH_REG, data);
		mdelay(30);
		SLIC_SPI_write(num,PROSLIC_DC_TO_DC_SWITCH_REG, data);

	}
	spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
	//a very
	//slow power-up of the dc-dc converter indicates that too
	//much power is being consumed by a short circuit or a
	//malfunction, this exception powers down the device and
	//terminates the program.
	
	//powerTime= clock() - initialTime;
	powerTime= jiffies - initialTime;
	if (i>500) 	printk("\nPower Up took %i milliseconds.\n",powerTime); 
   	
	
	//if (chipType(num) == 3)  // M version correction
	//{
	//	SLIC_SPI_write(num, PROSLIC_DC_TO_DC_PERIOD_REG,0x80 + 0x60);// M version
	//	
	//}
	//else
	//	SLIC_SPI_write(num, PROSLIC_DC_TO_DC_SWITCH_REG, 0x99);  /* DC-DC Calibration  */
	spin_lock_irqsave(&ssp_mutex, ssp_flags);
	opcode = SLIC_SPI_read(num, PROSLIC_DC_TO_DC_SWITCH_REG);
	spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
	while(0x80&opcode);  // Wait for DC-DC Calibration to complete
	{
		spin_lock_irqsave(&ssp_mutex, ssp_flags);
		opcode = SLIC_SPI_read(num, PROSLIC_DC_TO_DC_SWITCH_REG);
		spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
		}

	return vBat;
}

/************************************************
* SLIC_SPI_read
* table -> which table to be read: 0/count // 1/EEPROM
* addr  -> Address to be read
* return : Value of the register
*************************************************/
UINT8 SLIC_SPI_read(int num, UINT8 addr)
{
	UINT8 value=0;
	int i ;
	unsigned int ad1;
	unsigned int bit;//,iomode;//status,
	
	if(dp==1)
		printk("SLIC_SPI_read : only one at the same time!!\n");
	dp = 1;

#ifdef CONFIG_SL3516_ASIC
	ad1 = (unsigned int)(GPIO_BASE_ADDR1 + GPIO_DATA_SET);
#else	
	ad1 = (unsigned int)(GPIO_BASE_ADDR + GPIO_DATA_SET);
#endif	
	writel(GPIO_EECK,ad1);
	
	if(daisyChain==1)
	{
	
			SLIC_SPI_CS_enable(0);
		// send chain bits address 
		for(i=SPI_DAT_LEN-1;i>=0;i--)
		{
			if(i==num)
				SLIC_SPI_write_bit(1);
			else 
				SLIC_SPI_write_bit(0);
		}
		SLIC_SPI_CS_enable(1);
	}

	SLIC_SPI_CS_enable(0);
	


	//write read cmd
	SLIC_SPI_write_bit(1);
	// send 7 bits address to be read
	for (i=6;i>=0;i--) {
		bit= ((addr>>i) & 0x01) ? 1 :0 ;
		SLIC_SPI_write_bit(bit);
	}


	// turn around
	//SLIC_SPI_read_bit(); // TA_Z
	//SLIC_SPI_CS_enable(1);
	SLIC_SPI_CS_enable(1);
	SLIC_SPI_CS_enable(0);

	value=0;
	for (i=7;i>=0;i--) { // READ 8'b DATA
		bit=SLIC_SPI_read_bit();
		value |= bit << i ;
	}

    
	
	SLIC_SPI_CS_enable(1);
	
	dp = 0;
	return(value);

}

/**********************************************************************
* read a bit from  register
***********************************************************************/
unsigned int SLIC_SPI_read_bit(void) // read data from
{
	unsigned int addr;
	unsigned int value;


#ifdef CONFIG_SL3516_ASIC
	addr = (unsigned int )(GPIO_BASE_ADDR1 + GPIO_DATA_CLEAR);
	writel(GPIO_EECK,addr);
	//*addr = GPIO_EECK; // set EECK to 0

	//value = *(unsigned int *)(GPIO_BASE_ADDR1 + GPIO_DATA_IN);
	value = readl(GPIO_BASE_ADDR1 + GPIO_DATA_IN);
	value = (value & GPIO_MISO) ;
	value = value >> (GPIO_MISO_BIT); // 7 = pin of data in
	
	addr = (unsigned int )(GPIO_BASE_ADDR1 + GPIO_DATA_SET);
	writel(GPIO_EECK,addr);
	//*addr = GPIO_EECK; // set EECK to 1
#else
	addr = (unsigned int )(GPIO_BASE_ADDR + GPIO_DATA_CLEAR);
	writel(GPIO_EECK,addr);
	//*addr = GPIO_EECK; // set EECK to 0

	//value = *(unsigned int *)(GPIO_BASE_ADDR + GPIO_DATA_IN);
	value = readl(GPIO_BASE_ADDR + GPIO_DATA_IN);
	value = (value & GPIO_MISO) ;
	value = value >> (GPIO_MISO_BIT); // 7 = pin of data in
	
	addr = (unsigned int )(GPIO_BASE_ADDR + GPIO_DATA_SET);
	writel(GPIO_EECK,addr);
	//*addr = GPIO_EECK; // set EECK to 1
#endif	
	return value ;


}


/******************************************
* SLIC_SPI_write
* addr -> Write Address
* value -> value to be write
***************************************** */
void SLIC_SPI_write(int num, UINT8 addr,UINT8 value)
{
	unsigned int  ad1;
	int i;
	char bit;//,status;

	if(dp==1)
		printk("SLIC_SPI_write : only one at the same time!!\n");
	dp = 1;
	
#ifdef CONFIG_SL3516_ASIC
	ad1 = (unsigned int)(GPIO_BASE_ADDR1 + GPIO_DATA_SET);
#else
	ad1 = (unsigned int)(GPIO_BASE_ADDR + GPIO_DATA_SET);
#endif	
	writel(GPIO_EECK,ad1);
	//*ad1 = GPIO_EECK; // set EECK to 1 

	if(daisyChain==1)
	{
	
			SLIC_SPI_CS_enable(0);
		// send chain bits address 
		for(i=SPI_DAT_LEN-1;i>=0;i--)
		{
			if(i==num)
				SLIC_SPI_write_bit(1);
			else 
				SLIC_SPI_write_bit(0);
		}
		SLIC_SPI_CS_enable(1);
	}

	SLIC_SPI_CS_enable(0);
	
	//SLIC_SPI_write_bit(0);       //dummy clock
	
	
	//write cmd
	SLIC_SPI_write_bit(0);
	// send 7 bits address 
	for(i=SPI_ADD_LEN-1;i>=0;i--)
	{
		bit = (addr>>i) & 0x01;
		SLIC_SPI_write_bit(bit);
	}
	
	//
	SLIC_SPI_CS_enable(1);
	SLIC_SPI_CS_enable(0);
	
	// send 8 bits data
	for(i=SPI_DAT_LEN-1;i>=0;i--)
	{
		bit = (value>>i)& 0x01;
		SLIC_SPI_write_bit(bit);
	}

	SLIC_SPI_CS_enable(1);	// CS high


	dp = 0;
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
		//*addr = GPIO_MOSI; // set MOSI to 1 
		writel(GPIO_MOSI,addr);
		addr = (unsigned int )(GPIO_BASE_ADDR1 + GPIO_DATA_CLEAR);
		//*addr = GPIO_EECK; // set EECK to 0 
		writel(GPIO_EECK,addr);
		addr = (unsigned int )(GPIO_BASE_ADDR1 + GPIO_DATA_SET);
		//*addr = GPIO_EECK; // set EECK to 1 
		writel(GPIO_EECK,addr);
		
	}
	else
	{
		addr = (unsigned int )(GPIO_BASE_ADDR1 + GPIO_DATA_CLEAR);
		//*addr = GPIO_MOSI; // set MISO to 0 
		writel(GPIO_MOSI,addr);
		addr = (unsigned int )(GPIO_BASE_ADDR1 + GPIO_DATA_CLEAR);
		//*addr = GPIO_EECK; // set EECK to 0 
		writel(GPIO_EECK,addr);
		addr = (unsigned int )(GPIO_BASE_ADDR1 + GPIO_DATA_SET);
		//*addr = GPIO_EECK; // set EECK to 1 
		writel(GPIO_EECK,addr);
		
	}
#else
	if(bit_EEDO)
	{
		addr = (unsigned int )(GPIO_BASE_ADDR + GPIO_DATA_SET);
		//*addr = GPIO_MOSI; // set MOSI to 1 
		writel(GPIO_MOSI,addr);
		addr = (unsigned int )(GPIO_BASE_ADDR + GPIO_DATA_CLEAR);
		//*addr = GPIO_EECK; // set EECK to 0 
		writel(GPIO_EECK,addr);
		addr = (unsigned int )(GPIO_BASE_ADDR + GPIO_DATA_SET);
		//*addr = GPIO_EECK; // set EECK to 1 
		writel(GPIO_EECK,addr);
		
	}
	else
	{
		addr = (unsigned int )(GPIO_BASE_ADDR + GPIO_DATA_CLEAR);
		//*addr = GPIO_MOSI; // set MISO to 0 
		writel(GPIO_MOSI,addr);
		addr = (unsigned int )(GPIO_BASE_ADDR + GPIO_DATA_CLEAR);
		//*addr = GPIO_EECK; // set EECK to 0 
		writel(GPIO_EECK,addr);
		addr = (unsigned int )(GPIO_BASE_ADDR + GPIO_DATA_SET);
		//*addr = GPIO_EECK; // set EECK to 1 
		writel(GPIO_EECK,addr);
		
	}
#endif
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
		//*addr = GPIO_EECS; // set EECS to 1 
		writel(GPIO_EECS,addr);
		
	}
	else
	{
		addr = (unsigned int )(GPIO_BASE_ADDR1 + GPIO_DATA_CLEAR);
		//*addr = GPIO_EECS; // set EECS to 0 
		writel(GPIO_EECS,addr);
	}
#else
	if(enable)
	{
		addr = (unsigned int )(GPIO_BASE_ADDR + GPIO_DATA_SET);
		//*addr = GPIO_EECS; // set EECS to 1 
		writel(GPIO_EECS,addr);
		
	}
	else
	{
		addr = (unsigned int )(GPIO_BASE_ADDR + GPIO_DATA_CLEAR);
		//*addr = GPIO_EECS; // set EECS to 0 
		writel(GPIO_EECS,addr);
	}
#endif	
}

void SLIC_SPI_ind_write(int num, UINT8 addr, UINT16 data)
{
	UINT16 status=0;
	
	
	status = SLIC_SPI_read(num, PROSLIC_IND_STATUS_REG); //indirect status 31
	while(status)
	{
		status = SLIC_SPI_read(num, PROSLIC_IND_STATUS_REG); //indirect status
		mdelay(10);
		schedule();
	}
	
	SLIC_SPI_write(num, PROSLIC_IND_DATA_LOW_REG,data&0xff); //reg 28 Low byte
	SLIC_SPI_write(num, PROSLIC_IND_DATA_HIGH_REG,(data&0xff00)>>8); //reg 29 High byte
	SLIC_SPI_write(num, PROSLIC_IND_ADDR_REG,addr); //reg 29 Low byte
	
	status = SLIC_SPI_read(num, PROSLIC_IND_STATUS_REG); //indirect status 31
	while(status)
	{
		status = SLIC_SPI_read(num, PROSLIC_IND_STATUS_REG); //indirect status
		mdelay(10);
		schedule();
	}
	
}

UINT16 SLIC_SPI_ind_read(int num, UINT8 addr)
{
	UINT16 status=0,data;
	
	
	status = SLIC_SPI_read(num, PROSLIC_IND_STATUS_REG); //indirect status 31
	while(status)
	{
		status = SLIC_SPI_read(num, PROSLIC_IND_STATUS_REG); //indirect status
		mdelay(10);
		schedule();
	}
	
	
	SLIC_SPI_write(num, PROSLIC_IND_ADDR_REG,addr); //reg 29 Low byte
	
	
	status = SLIC_SPI_read(num, PROSLIC_IND_STATUS_REG); //indirect status 31
	while(status)
	{
		status = SLIC_SPI_read(num, PROSLIC_IND_STATUS_REG); //indirect status
		mdelay(10);
		schedule();
	}
	
	data = SLIC_SPI_read(num, PROSLIC_IND_DATA_LOW_REG); //reg 28 Low byte
	data |= (SLIC_SPI_read(num, PROSLIC_IND_DATA_HIGH_REG)<<8); //reg 29 High byte
	
	return data;
}

/*****************************************************
* SLIC_SPI_pre_st
* preambler: 32 bits '1'   start bit: '01'
*****************************************************/
void SLIC_SPI_pre_st(void)
{
	int i;

	for(i=0;i<32;i++) // PREAMBLE
		SLIC_SPI_write_bit(1);
	SLIC_SPI_write_bit(0); // ST
	SLIC_SPI_write_bit(1);
}

void SLIC_init_ind_reg_set(int num)
{
	int i;
	
	
	i = 0;
	while ((SLIC_ind_reg_def[i] != 0 ) || (SLIC_ind_reg_def[i+1] != 0 ) )
	{
		SLIC_SPI_ind_write(num, SLIC_ind_reg_def[i],SLIC_ind_reg_def[i+1]);
		i += 2;
		schedule();
	}
}

UINT8 version(int num)
{
	return 0xf & SLIC_SPI_read(num, PROSLIC_SPI_MODE_SEL_REG); 
}

UINT8 chipType (int num)
{
	return (0x30 & SLIC_SPI_read(num, PROSLIC_SPI_MODE_SEL_REG)) >> 4; 
}

void exception (int num, enum exceptions e)
/* This is where an embedded system would call its exception handler */
/* This code runs a print out routine */
{
	printk( "\n                 E X C E P T I O N: %s\n",exceptionStrings[e] );
	printk( " Terminating the program\n");
	ssp_slic[num].chipData.exce_occ=1;
	//exitProgram();
}

int selfTest(int num)
{

	/*  Begin Sanity check  Optional */
	if (SLIC_SPI_read(num, PROSLIC_LOOPBACK_REG) !=2) 
	{
		exception(num, PROSLICiNSANE);
		return -1;
	}
		//printk("\nREG 8 : not full analog loopback mode !!");
	if (SLIC_SPI_read(num, PROSLIC_LINEFEED_CTRL_REG) !=0) 
	{
		exception(num, PROSLICiNSANE);
		return -1;
	}
		//printk("\nREG 64 : Linefeed status != Open !!");
	if (SLIC_SPI_read(num, PROSLIC_HYBRID_CTRL_REG) !=0x33) 
	{
		exception(num, PROSLICiNSANE);
		return -1;
	}	
	//	SLIC_SPI_write(num, PROSLIC_PCM_MODE_SEL_REG,0x28);
	//if (SLIC_SPI_read(num, PROSLIC_PCM_MODE_SEL_REG) !=0x28) 
	//{
	//	exception(num, PROSLICiNSANE);
	//	return -1;
	//}	
		SLIC_SPI_write(num, PROSLIC_IMPEDANCE_REG,0x28);
	if (SLIC_SPI_read(num, PROSLIC_IMPEDANCE_REG) !=0x28) 
	{
		exception(num, PROSLICiNSANE);
		return -1;
	}
	/* End Sanity check */
	return 0;
}

int SLIC_init(int num)
{
	//byte tmp=0;
	UINT8 t,v,data;
	

	
	//Before writing the indirect registers, a few direct registers are read 
	//to confirm they are set to their reset value.
	//If they are set to the reset value the communication is working.
	if(selfTest(num))
		return -1;
		
	v = version(num);
	t = chipType(num);
	

	      SLIC_init_ind_reg_set(num);
	      
	      SLIC_SPI_write(num,PROSLIC_LOOPBACK_REG,0x00);	//turn off loopback).
	      SLIC_SPI_write(num,PROSLIC_LOOPBACK_REG,0x00);	//turn off loopback).
	      SLIC_SPI_write(num,PROSLIC_REV_C_ENH_REG, 0xEB);              //Enhancement Enable
	      
	      if ( t ==0 ) // Si3210 not the Si3211 or Si3212	
		  {
				SLIC_SPI_write(num, PROSLIC_AUTO_MANUAL_CTRL_REG,0x17); // Make VBat switch not automatic 
			// The above is a saftey measure to prevent Q7 from accidentaly turning on and burning out.
			//  It works in combination with the statement below.  Pin 34 DCDRV which is used for the battery switch on the
			//  Si3211 & Si3212 
			
			SLIC_SPI_write(num, PROSLIC_BATT_FEED_CTRL_REG,1);  //    Q7 should be set to OFF for si3210
		  }

			if (v <=2 )  //  REVISION B   
				SLIC_SPI_write(num, PROSLIC_ACTIVE_VOLTAGE_REG,4);  // set common mode voltage to 6 volts
	
		/* Do Flush durring powerUp and calibrate */
		powerUp(num);  // Turn on the DC-DC converter and verify voltage.
		//if (t == 0 || t==3) //  Si3210
	  //
		//{
		//	powerUp(num);  // Turn on the DC-DC converter and verify voltage.
		//	powerLeakTest(num); // Check for power leaks
		//	powerUp(num); // Turn on the DC-DC converter again
		//}
	      
	      //initialize Direct Registers
	      SLIC_SPI_write(num,PROSLIC_LINEFEED_CTRL_REG,0);
		  //SLIC_init_reg_set(num);
		  
		  data = calibrate(num);
			if (data){
				printk("Calibration failure\n");
			}
			
			 //----------------------------
			 // STEP 20: Flush Accumulators
			 //----------------------------
			 SLIC_SPI_ind_write(num,  88, 0);
			 SLIC_SPI_ind_write(num,  89, 0);
			 SLIC_SPI_ind_write(num,  90, 0);
			 SLIC_SPI_ind_write(num,  91, 0);
			 SLIC_SPI_ind_write(num,  92, 0);
			 SLIC_SPI_ind_write(num,  93, 0);
			 SLIC_SPI_ind_write(num,  94, 0);
			 SLIC_SPI_ind_write(num,  95, 0);
			 SLIC_SPI_ind_write(num,  97, 0);
			 SLIC_SPI_ind_write(num,  193, 0);
			 SLIC_SPI_ind_write(num,  194, 0);
			 SLIC_SPI_ind_write(num,  195, 0);
			 SLIC_SPI_ind_write(num,  196, 0);
			 SLIC_SPI_ind_write(num,  197, 0);
			 SLIC_SPI_ind_write(num,  198, 0);
			 SLIC_SPI_ind_write(num,  199, 0);
			 SLIC_SPI_ind_write(num,  200, 0);
			 SLIC_SPI_ind_write(num,  201, 0);
			 SLIC_SPI_ind_write(num,  202, 0);
			 SLIC_SPI_ind_write(num,  203, 0);
			 SLIC_SPI_ind_write(num,  204, 0);
			 SLIC_SPI_ind_write(num,  205, 0);
			 SLIC_SPI_ind_write(num,  206, 0);
			 SLIC_SPI_ind_write(num,  207, 0);
			 SLIC_SPI_ind_write(num,  208, 0);
			 SLIC_SPI_ind_write(num,  209, 0);
 			 SLIC_SPI_ind_write(num,  210, 0); 
			 SLIC_SPI_ind_write(num,  211, 0);
			
		clearInterrupts(num);
				SLIC_SPI_ind_write(num,  35, 0x8000); //LOOP_CLSRE_FlTER
				SLIC_SPI_ind_write(num,  36, 0x0320);	//RING_TRIP_FILTER
				SLIC_SPI_ind_write(num,  37, 0x08c);		//TERM_LP_POLE_Q1Q2
				SLIC_SPI_ind_write(num,  38, 0x0100);	//TERM_LP_POLE_Q3Q4
				SLIC_SPI_ind_write(num,  39, 0x0010);	//TERM_LP_POLE_Q5Q6

#if (DAISY_MODE==1)	
			if((daisyChain==1)&&(NUMBER_OF_CHAN > 1))
			{
				data =SLIC_SPI_read(num, 0);
				SLIC_SPI_write(num,0,(data|0x80));
			}
		//	else
		//	{
		//		data =SLIC_SPI_read(num, 0);
		//		SLIC_SPI_write(num,0,(data&0x7F));
		//	}
#endif				
				SLIC_SPI_write(num,1,0x3c);//INIT_DR1);
				SLIC_SPI_write(num,34,INIT_DR34);
				SLIC_SPI_write(num,48,INIT_DR48);
				SLIC_SPI_write(num,49,INIT_DR49);
				SLIC_SPI_write(num,50,INIT_DR50);
				SLIC_SPI_write(num,51,INIT_DR51);
				SLIC_SPI_write(num,65,0x60);//INIT_DR65);
				SLIC_SPI_write(num,71,INIT_DR71);
				
				
				SLIC_SPI_write(num,PROSLIC_INT1_MASK_REG,0xff);//0x10);//0xff);
    		SLIC_SPI_write(num,PROSLIC_INT2_MASK_REG,0xff);
    		//SLIC_SPI_write(num,PROSLIC_INT3_MASK_REG,0xff);
    		SLIC_SPI_write(num,PROSLIC_INT3_MASK_REG,0x05);
				
		goActive(num);
		
		  
	return 0;
}

UINT16 SLIC_SPI_get_identifier(int num)
{
	unsigned int flag=0,rev=0x40;
	
	flag = SLIC_SPI_read(num, PROSLIC_SPI_MODE_SEL_REG);

	if ((flag & 0x30) == 0x00)
	{
		rev |=(flag&0x0f) ;
		
			printk("Phone%d Si3210, Rev = %c\n",num,rev);
		return 0;
	}
	else if ((flag & 0x30) == 0x10)
	{
		rev |=(flag&0x0f) ;
		
			printk("Phone%d Si3211, Rev = %c\n",num,rev);
		return 1;
	}
	else if ((flag & 0x30) == 0x30)
	{
		rev |=(flag&0x0f) ;
		
			printk("Phone%d Si3210M, Rev = %c\n",num,rev);
		return 2;
	}
	else
	{
		printk("Device Undefine !!  PROSLIC_SPI_MODE_SEL_REG = %02x \n",(flag&0xff));
		return 3;
	}
}

static int gemini_ssp_ioctl(struct inode *inode, struct file *file_p, unsigned int cmd, unsigned long arg)
{
	
	//unsigned int raise, mant;
	unsigned int num,i,linstat;
	int retval = 0, value;
//	unsigned int minor = MINOR(inode->i_rdev);
	//int board = NUM(inode->i_rdev);
	SSP_SLIC *ssp_tmp = file_p->private_data;
	num = ssp_tmp->p.board;
	
	/*
	 *    Check ioctls only root can use.
	 */
	
	switch (cmd) {
		case SSP_GET_HOOK_STATUS: 
			value = gemini_ssp_hookstate(num);
			if(copy_to_user((int *)arg, &value, sizeof(value))) 
				retval = -EFAULT;
			break;
		case SSP_GET_LINEFEED:
			value = gemini_ssp_get_linefeed(num);
			printk("SSP_GET_LINEFEED :%x\n",value);
			if(copy_to_user((int *)arg, &value, sizeof(value))) 
				retval = -EFAULT;
			break;
		case SSP_SET_LINEFEED:
			if(arg) 
				copy_from_user(&value, (int *)arg, sizeof(value));		
			gemini_ssp_set_linefeed(num, value);
			break;
		case SSP_GET_REG:
			if(arg) 
				copy_from_user(&ssp_slic[num].ssp_reg, (Ssp_reg *)arg, sizeof(Ssp_reg));
			
			if(ssp_slic[num].ssp_reg.reg_type==0) // 0: SSP Control
				ssp_slic[num].ssp_reg.data = READ_SSP_REG(ssp_slic[num].ssp_reg.addr);
			else if(ssp_slic[num].ssp_reg.reg_type==1) // 1: Slic Direct
			{
				spin_lock_irqsave(&ssp_mutex, ssp_flags);
				ssp_slic[num].ssp_reg.data = (UINT8)SLIC_SPI_read(num, (UINT8)ssp_slic[num].ssp_reg.addr);
				spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
			}
			else if(ssp_slic[num].ssp_reg.reg_type==2) // 2: Slic Indirect Register
			{
				spin_lock_irqsave(&ssp_mutex, ssp_flags);
				ssp_slic[num].ssp_reg.data = (UINT16)SLIC_SPI_ind_read(num, (UINT8)ssp_slic[num].ssp_reg.addr);	
				spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
			}
			if (copy_to_user((Ssp_reg *)arg, &ssp_slic[num].ssp_reg, sizeof(Ssp_reg))) 
				retval = -EFAULT;
				
			retval = 0;
			break;
		case SSP_SET_REG:
			if(arg) 
				copy_from_user(&ssp_slic[num].ssp_reg, (Ssp_reg *)arg, sizeof(Ssp_reg));
			
			if(ssp_slic[num].ssp_reg.reg_type==0) // 0: SSP Control
				WRITE_SSP_REG(ssp_slic[num].ssp_reg.addr,ssp_slic[num].ssp_reg.data);
			else if(ssp_slic[num].ssp_reg.reg_type==1) // 1: Slic Direct
			{
				spin_lock_irqsave(&ssp_mutex, ssp_flags);
				SLIC_SPI_write(num, (UINT8)ssp_slic[num].ssp_reg.addr,(UINT8)ssp_slic[num].ssp_reg.data);
				spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
			}
			else if(ssp_slic[num].ssp_reg.reg_type==2) // 2: Slic Indirect Register
			{
				spin_lock_irqsave(&ssp_mutex, ssp_flags);
				SLIC_SPI_ind_write(num, (UINT8)ssp_slic[num].ssp_reg.addr,(UINT16)ssp_slic[num].ssp_reg.data);	
				spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
			}
			if (copy_to_user((Ssp_reg *)arg, &ssp_slic[num].ssp_reg, sizeof(Ssp_reg))) 
				retval = -EFAULT;
				
			retval = 0;
			break;
			
		case SSP_GEN_OFFHOOK_TONE:

			if(!gemini_ssp_hookstate(num)) // (1):On hook 
			 if(ssp_slic[num].link_on==0)
			 {
					dialTone(num);
					setState(num, DIALtONE);
			 }
				retval = 0;
			break;
		case SSP_GEN_BUSY_TONE:

			if(!gemini_ssp_hookstate(num)&&(ssp_slic[num].link_on==0)) // (1):On hook 
			{

				busyTone(num);
				setState(num, BUSY);
			}	
				retval = 0;
			break;
		case SSP_GEN_RINGBACK_TONE:

			if(!gemini_ssp_hookstate(num)&&(ssp_slic[num].link_on==0)) // (1):On hook 
			{
				disableOscillators(num);
				ringBackTone(num);
				setState(num, RINGbACK);
			}
			
			retval = 0;
			break;
		case SSP_GEN_CONGESTION_TONE:

			if(!gemini_ssp_hookstate(num)&&(ssp_slic[num].link_on==0)) // (1):On hook 
			{
				disableOscillators(num);
				congestionTone(num);
				setState(num, CONGESTION);
			}
				
				retval = 0;
			break;
		case SSP_DISABLE_DIALTONE:
			//if(!gemini_ssp_hookstate(num)) // (1):On hook 
				disableOscillators(num);
				//printk("SSP_DISABLE_DIALTONE \n");                          
			break;
		case SSP_PHONE_RING_START:
				disableOscillators(num);
			if(ssp_slic[num].chipData.ring_type)
			{
					standardRinging(num);
					activateRinging(num);
					setState(num, RINGING);
			}
			else
			{
					ringBackTone(num);
					setState(num, RINGbACK);
			}
				//ssp_slic[num].link_on=0;
				retval = 0;
				printk("SSP_PHONE_RING_START \n");
			break;
		case SSP_PHONE_RING_STOP:
			if(ssp_slic[num].chipData.ring_type)
				stopRinging(num);
			else
				disableOscillators(num);
				//ssp_slic[num].link_on=1;
				retval = 0;
				printk("SSP_PHONE_RING_STOP \n");
			break;
		case SSP_PHONE_RINGING:
				setState(num, RINGING);
			break;
		case SSP_GET_PHONE_STATE:
			value = ssp_slic[num].chipData.state;
			if (copy_to_user((int *)arg, &value, sizeof(value))) 
				retval = -EFAULT;
				
			break;
		case SSP_SET_PHONE_STATE:
			if(arg) 
				copy_from_user(&value, (int*)arg, sizeof(value));
			//ssp_slic[num].chipData.state = value;
			setState(num, value);
							
			break;
		case SSP_SLIC_GOACTIVE:
			spin_lock_irqsave(&ssp_mutex, ssp_flags);
			goActive(num);
			spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
			break;	
		case SSP_SLIC_GROUNDSHORT:
			spin_lock_irqsave(&ssp_mutex, ssp_flags);
			groundShort(num); /* Check for grounded Tip or Ring Leads*/
			spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
			break;
		case SSP_SLIC_POWERLEAKTEST:
			spin_lock_irqsave(&ssp_mutex, ssp_flags);
			powerLeakTest(num);
			spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
			break;
		case SSP_SLIC_POWERUP:
			powerUp(num);
			break;
		case SSP_SLIC_EXCEPTION:
			if(arg) 
				copy_from_user(&value, (int*)arg, sizeof(value));
			exception(num, value);
			break;
		case SSP_SLIC_CLEARALARMBITS:
			spin_lock_irqsave(&ssp_mutex, ssp_flags);
			clearAlarmBits(num);
			spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
			break;		
		case SSP_SLIC_DTMFACTION:
			dtmfAction(num);
			break;
		case SSP_SLIC_CLEAN_DTMF:
			ssp_slic[num].chipData.DTMF_digits[0]= 0;
			ssp_slic[num].chipData.digit_count = 0;
			
			
			break;
		case SSP_SLIC_DTMFACTION_TEST:
			ssp_slic[num].chipData.digit_count = 0;
			dtmfAction_test(num);
			break;
		case SSP_SLIC_DMA_TEST:
					linstat = 0;
					for(i=0;i<NUMBER_OF_CHAN;i++)
						linstat += ssp_slic[i].link_on;
					//	disableOscillators(num);
				//linstat = READ_DMA_REG(DMA_CFG); //enable DMA
				if(linstat == 1)//if(linstat==1)
				{
					if(dma_link_on==1)
					{
						WRITE_DMA_REG(DMA_CH3_CSR, 0x0); //CSR
						WRITE_DMA_REG(DMA_CH2_CSR, 0x0); //CSR
						//dma_demo = DMA_DEMO;
						//ssp_slic[num].link_on=1; 
						desc_ptrr=0;
						desc_ptrt=0;
						//ssp_slic[num].wt_buf_ok = 0;
						//dp=0;
						for(i=0;i<NUMBER_OF_CHAN;i++)
						{
							ssp_slic[i].rd_curr=0;
							ssp_slic[i].wt_curr=0;
							ssp_slic[i].wt_buf_ok=1;
						}
						spin_lock_irqsave(&ssp_mutex, ssp_flags);
						value = gemini_ssp_dma();
						spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
						printk("SSP_SLIC_DMA_TEST \n");
					}
				}
			break;
		case SSP_SLIC_STOP_DMA:
					linstat = 0;
					for(i=0;i<NUMBER_OF_CHAN;i++)
						linstat |= ssp_slic[i].link_on;
					
					ssp_slic[num].dma_stop = 1;
					ssp_slic[i].wt_buf_ok=0;
					ssp_slic[num].link_on=0;
					if(linstat==0)
					{
						dma_link_on = 0;
						spin_lock_irqsave(&ssp_mutex, ssp_flags);
						SLIC_SPI_write(num,  PROSLIC_LINEFEED_CTRL_REG, 0x11); // REG 64,4
						spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
					}
				//if(linstat==0)
				//{	
				//	dma_link_on = 0;
				//	*((volatile unsigned int *)IRQ_MASK(IO_ADDRESS(SL2312_INTERRUPT_BASE))) &= ~(IRQ_DMA_OFFSET);
				//	WRITE_DMA_REG(DMA_CH3_CSR, 0x0); //CSR
				//	WRITE_DMA_REG(DMA_CH2_CSR, 0x0); //CSR
				//	for(i=0;i<NUMBER_OF_CHAN;i++)
				//	{
				//		ssp_slic[i].wt_buf_ok=0;
				//		ssp_slic[num].link_on=0;
				//	}
				//	dma_link_on = 0;
				//	WRITE_DMA_REG(DMA_CFG, 0x0); //disable DMA
				//	WRITE_DMA_REG(DMA_INT_TC_CLR, 0xc);
				//	
				//	spin_lock_irqsave(&ssp_mutex, ssp_flags);
				//	SLIC_SPI_write(num,  PROSLIC_LINEFEED_CTRL_REG, 0x11); // REG 64,4
				//	spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
				//}
				//else
				//{
				//	ssp_slic[num].link_on=0;
				//	spin_lock_irqsave(&ssp_mutex, ssp_flags);
				//	SLIC_SPI_write(num,  PROSLIC_LINEFEED_CTRL_REG, 0x11); // REG 64,4
				//	spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
				//}
			break; 
		case SSP_SLIC_GET_LINKSTATE:
				value = ssp_slic[num].link_on;
				if(copy_to_user((int *)arg, &value, sizeof(value))) 
				retval = -EFAULT;
			break;
		case SSP_SLIC_SET_LINKSTATE:
				if(arg) 
					copy_from_user(&value, (int *)arg, sizeof(value));		
					ssp_slic[num].link_on = value;
					printk("Phone%d SSP_SLIC_SET_LINKSTATE : %x, value:%x\n",num,ssp_slic[num].link_on,value);
					if(ssp_slic[num].link_on == 1)
						setState(num, ONlINE);
						linstat = 0;
					for(i=0;i<NUMBER_OF_CHAN;i++)
					{
						linstat |= ssp_slic[i].link_on;
						if(linstat==0)
							dma_link_on = 0;
						else
							dma_link_on = 1;
					}
			break;
		case SSP_SLIC_GET_RDOK:  
				value = ssp_slic[num].dout;
				if(copy_to_user((int *)arg, &value, sizeof(value))) 
				retval = -EFAULT;
			break;
		case SSP_SLIC_GET_WTOK:
				value = ssp_slic[num].din;
				if(copy_to_user((int *)arg, &value, sizeof(value))) 
				retval = -EFAULT;
			break;
		case SSP_SLIC_SET_TXRATE:
				if(arg) 
					copy_from_user(&value, (int *)arg, sizeof(value));		
					if(value > 8192)
					
						ssp_slic[num].tx_rate = 16384;
					else
						ssp_slic[num].tx_rate = 8192;
					//printk("SSP_SLIC_SET_TXRATE : %d, value:%d\n",ssp_slic[num].tx_rate, value);
			break;	
		case SSP_SLIC_SET_RINGTYPE:
				if(arg) 
				{
					copy_from_user(&value, (int *)arg, sizeof(value));		
					ssp_slic[num].chipData.ring_type = value;
					printk("SSP_SLIC_SET_RINGTYPE : %x, \n",ssp_slic[num].chipData.ring_type);
				}
			break;	
		case SSP_SLIC_GET_DTMF:
			//printk("SSP_SLIC_GET_DTMF \n");
			if (copy_to_user((char *)arg, &ssp_slic[num].chipData.DTMF_digits[0], DTMF_NUM*sizeof(char))) 
				retval = -EFAULT;
			break;	
		case SSP_SLIC_GET_DTMF_CNT: 
			value = ssp_slic[num].chipData.digit_count;
			//printk("SSP_SLIC_GET_DTMF_CNT: value %d \n",value);
			if (copy_to_user((int *)arg, &value, sizeof(value))) 
				retval = -EFAULT;
			break;	
		case SSP_SLIC_SET_MODE: 
				if(arg) 
				{
					copy_from_user(&value, (int *)arg, sizeof(value));		
					dma_demo = value;
				}
			break;	
		//case :
		//	break;	
		//case :
		//	break;	
		//case :
		//	break;	
		default:
	
			retval = 0xff;
	}
	
	return retval;
}

static int gemini_ssp_dma(void)//, char *buf, size_t count, loff_t * ppos)
{
	
//	unsigned long i = *ppos;
	int  written = 0, opcode, j=0,i;
	//SSP_SLIC * ssp_slic = NUM(file_p->f_dentry->d_inode->i_rdev);
	//SSP_SLIC *ssp_tmp = file_p->private_data;
	
	//printk("%s -->\n",__func__);
	if(NUMBER_OF_CHAN==1)
	{
		if(ssp_slic[0].chipData.in_release)
			return 0;
	}
	else if(NUMBER_OF_CHAN==2)
	{
		if((ssp_slic[0].chipData.in_release) && (ssp_slic[1].chipData.in_release))
			return 0;
	}
	
	///////////////////////////////////////////////////////////////
					WRITE_DMA_REG(DMA_CFG, 0x0); //disable DMA
					WRITE_DMA_REG(DMA_INT_TC_CLR, 0xc);
	
			for(i=0;i<NUMBER_OF_CHAN;i++)
						ssp_slic[i].dma_stop = 0;
			//init dma ring 
			for(j=0;j<LLP_SIZE;j++)//Tx
  		{
  			LLPT[j].llp = __pa(((UINT32)&LLPT[((j+1)%LLP_SIZE)]))|0x1;
  			LLPR[j].llp = __pa(((UINT32)&LLPR[((j+1)%LLP_SIZE)]))|0x1;
  		}
  		
	///////////////////////////////////////////////////////////////

	*((volatile unsigned int *)IRQ_MASK(IO_ADDRESS(SL2312_INTERRUPT_BASE))) |= (unsigned int)(IRQ_DMA_OFFSET);
		WRITE_DMA_REG(DMA_INT_TC_CLR, 0xc);

	WRITE_SSP_REG(SSP_CTRL_STATUS, 0x20000000);//force TC signal, terminate transfer
		WRITE_DMA_REG(DMA_CFG, 0x1); //enable DMA
	WRITE_DMA_REG(DMA_SYNC, 0xc);
	for(i=0;i<NUMBER_OF_CHAN;i++)
	{
		SLIC_SPI_write(i, 9,	INIT_DR9	);//0x00	Transmit and receive path gain and control
  	SLIC_SPI_write(i,  PROSLIC_LINEFEED_CTRL_REG, 0x11); // REG 64,4
  	opcode = SLIC_SPI_read(i,  PROSLIC_LINEFEED_CTRL_REG); // REG 64,4
  }

		

		memset(tbuf, 0x00, TBUF_SIZE);
		memset(rbuf, 0x00, TBUF_SIZE);
		for(i=0;i<NUMBER_OF_CHAN;i++)
		{
			memset(ssp_slic[i].cw2tbuf, 0x00, (TBUF_SIZE/NUMBER_OF_CHAN));
			memset(ssp_slic[i].cr2rbuf, 0x00, (TBUF_SIZE/NUMBER_OF_CHAN));
			ssp_slic[i].din = LLP_SIZE;
			ssp_slic[i].dout = 0;			
		}

	//	for(j=0;j<LLP_SIZE;j++)
	//	{
	//		for(i=0; i<DBUF_SIZE ;i+=2)
	//		{
	//				*(ssp_slic->tbuf+(j*DBUF_SIZE)+i+1)= *(wtmp+i);
	//				*(ssp_slic->tbuf+(j*DBUF_SIZE)+i)= *(wtmp+i+1);
	//				*(ssp_slic->rbuf+(j*DBUF_SIZE)+i+1)= *(wtmp+i);
	//				*(ssp_slic->rbuf+(j*DBUF_SIZE)+i)= *(wtmp+i+1);
	//				*(ssp_slic->cw2tbuf+(j*DBUF_SIZE)+i+1)= *(wtmp+i);
	//				*(ssp_slic->cw2tbuf+(j*DBUF_SIZE)+i)= *(wtmp+i+1);
	//				*(ssp_slic->cr2rbuf+(j*DBUF_SIZE)+i+1)= *(wtmp+i);
	//				*(ssp_slic->cr2rbuf+(j*DBUF_SIZE)+i)= *(wtmp+i+1);
	//		}
	//	}	
		
		j=0;
				
			WRITE_SSP_REG(SSP_CTRL_STATUS,0x1FF);		
			//WRITE_SSP_REG(SSP_CTRL_STATUS,0xC0100000);
			
			//DMA Channel 2 & 3 int mask
				WRITE_DMA_REG(DMA_CH2_CFG, 0);
				WRITE_DMA_REG(DMA_CH3_CFG, 0);
			
			// DMA Channel 3 for receive
			WRITE_DMA_REG(DMA_CH3_SRC_ADDR, SL2312_SSP_CTRL_BASE+SSP_READ_PORT); //src_address
			
			WRITE_DMA_REG(DMA_CH3_DST_ADDR, __pa(rbuf));//sbuf); //dest_address
			
			WRITE_DMA_REG(DMA_CH3_LLP, __pa(((UINT32)&LLPR[0]))|0x1); //LLP
			WRITE_DMA_REG(DMA_CH3_SIZE, DBUF_SIZE); //size
			/////////////////////////////////////////////////
			
			///////////////////////////////////////////////////
		    	
			//DMA Channel 2 for transmit
			WRITE_DMA_REG(DMA_CH2_SRC_ADDR, __pa(tbuf));//dbuf); //src_address
			WRITE_DMA_REG(DMA_CH2_DST_ADDR, SL2312_SSP_CTRL_BASE+SSP_WRITE_PORT); //dest_address
			//WRITE_DMA_REG(DMA_CH2_LLP, (((UINT32)&LLPT[0]))|0x1); //LLP
			WRITE_DMA_REG(DMA_CH2_LLP, __pa(((UINT32)&LLPT[0]))|0x1); //LLP
			WRITE_DMA_REG(DMA_CH2_SIZE, DBUF_SIZE/4); //size 32bit DMA
			WRITE_SSP_REG(SSP_CTRL_STATUS,0xC0100000);
			WRITE_DMA_REG(DMA_CH3_CSR, 0x000102c3); //CSR
			WRITE_DMA_REG(DMA_CH2_CSR, 0x00001095); //CSR

	printk("%s :<--\n",__func__);
	return written;
}

static ssize_t gemini_ssp_write(struct file *file_p, const char __user *buf, size_t count, loff_t * ppos)
{
	//unsigned long i = *ppos;
//	unsigned long wTime ;
	int ofs=0, written = 0, i=0, len=0, num;//, opcode, j=0;
	int value;
	//SSP_SLIC *ssp_slic = NUM(file_p->f_dentry->d_inode->i_rdev);
	SSP_SLIC *ssp_tmp = file_p->private_data;
	num = ssp_tmp->p.board;
	
	ssp_slic[num].chipData.inwt = 1;

	
	if(ssp_slic[num].chipData.in_release)
		return 0;
					
			
			written = count / SBUF_SIZE;
			ofs = count % SBUF_SIZE;
				

		if(ssp_slic[num].link_on==1){			
			//printk("-->link on: %x\n",wTime);
			if(ssp_slic[num].wt_buf_ok==0)
			{
				//if((((ssp_slic[num].wt_curr+1)%LLP_SIZE)!=ssp_slic[num].desc_ptrt) && (ssp_slic[num].wt_curr < LLP_SIZE)){
						for(i=0;i<written;i++)
						{
								copy_from_user((ssp_slic[num].cw2tbuf+(ssp_slic[num].wt_curr * SBUF_SIZE)), (buf+i*SBUF_SIZE), SBUF_SIZE);
								len+=SBUF_SIZE;
								ssp_slic[num].wt_curr++;
						}	
						if(ofs)
						{
							copy_from_user((ssp_slic[num].cw2tbuf+(ssp_slic[num].wt_curr * SBUF_SIZE)), (buf+(written-1)*SBUF_SIZE), ofs);
							len+=ofs;
							ssp_slic[num].wt_curr++;
						}
							
				//}
				//else
				if(ssp_slic[num].wt_curr == LLP_SIZE)
				{
					ssp_slic[num].din = LLP_SIZE;
					ssp_slic[num].wt_curr %= LLP_SIZE;
					ssp_slic[num].wt_buf_ok=1;
					spin_lock_irqsave(&ssp_mutex, ssp_flags);
					value = gemini_ssp_dma();
					spin_unlock_irqrestore(&ssp_mutex, ssp_flags);
					printk("Start DMA .......\n");
				}
			}
			else{
//				if(((ssp_slic[num].wt_curr)%LLP_SIZE)!=ssp_slic[num].desc_ptrt){
					//printk("wt -->\n");
						for(i=0;i<written;i++)
						{
								copy_from_user((ssp_slic[num].cw2tbuf+(ssp_slic[num].wt_curr * SBUF_SIZE)), (buf+i*SBUF_SIZE), SBUF_SIZE);
								len+=SBUF_SIZE;
								ssp_slic[num].wt_curr++;
								ssp_slic[num].wt_curr %= LLP_SIZE;
								ssp_slic[num].din++;
						}	
						if(ofs)
						{
							copy_from_user((ssp_slic[num].cw2tbuf+(ssp_slic[num].wt_curr * SBUF_SIZE)), (buf+written*SBUF_SIZE), ofs);
							len+=ofs;
							ssp_slic[num].wt_curr++;
								ssp_slic[num].wt_curr %= LLP_SIZE;
								ssp_slic[num].din++;
						}

				//ssp_slic[num].din = 1;
			}
	
		}//if(ssp_slic[num].link_on==1)	
		else
			printk("%s : not link !!\n",__func__);
		
	ssp_slic[num].chipData.inwt = 0;
	////////////////////////////////////////////
	//printk("gemini_ssp_write : %x\n",len);
	//wT = jiffies;
	return len;
}


static ssize_t gemini_ssp_read(struct file * file_p, char __user *buf, size_t length, loff_t * ppos)
{
	int ofs=0, readp=0, i=0, len=0, num;
	SSP_SLIC *ssp_tmp = file_p->private_data;
	num = ssp_tmp->p.board;
	
	ssp_slic[num].chipData.inrd = 0;

	
	
	if(ssp_slic[num].chipData.in_release)
		return 0;
		
	if(ssp_slic[num].link_on==1){				
				
					readp = length / SBUF_SIZE;
					ofs = length % SBUF_SIZE;
					
					
				if(ssp_slic[num].wt_buf_ok==0)
				{
						
						//if((((ssp_slic[num].rd_curr+1)%LLP_SIZE)!=ssp_slic[num].desc_ptrr) && (ssp_slic[num].rd_curr < LLP_SIZE))
						{
								
								for(i=0;i<readp;i++)
							{
									//memcpy((buf+i*DBUF_SIZE), ((ssp_slic[num].cr2rbuf+(((ssp_slic[num].desc_ptrr+LLP_SIZE-1)%LLP_SIZE) * DBUF_SIZE))), DBUF_SIZE);
									copy_to_user((buf+i*SBUF_SIZE), silent, SBUF_SIZE);
									len+=SBUF_SIZE;
							}
							if(ofs)
							{
								//memcpy((buf+i*DBUF_SIZE), ((ssp_slic[num].cr2rbuf+(((ssp_slic[num].desc_ptrr+LLP_SIZE-1)%LLP_SIZE) * DBUF_SIZE))), ofs);
								copy_to_user((buf+readp*SBUF_SIZE), silent, ofs);
								len+=ofs;
							}	
							ssp_slic[num].rd_curr++;
							ssp_slic[num].rd_curr %= LLP_SIZE;
						}	
			
				}
				else{
						if(ssp_slic[num].dout >0)
						{
							//printk("rd -->\n");
							if(((ssp_slic[num].rd_curr)%LLP_SIZE)!=desc_ptrr)
							{
									for(i=0;i<readp;i++)
									{
											copy_to_user((buf+i*SBUF_SIZE), (ssp_slic[num].cr2rbuf+(ssp_slic[num].rd_curr * SBUF_SIZE)), SBUF_SIZE);
											len+=SBUF_SIZE;
											ssp_slic[num].rd_curr++;
											ssp_slic[num].rd_curr %= LLP_SIZE;
									}
									if(ofs)
									{
										copy_to_user((buf+readp*SBUF_SIZE), (ssp_slic[num].cr2rbuf+(ssp_slic[num].rd_curr * SBUF_SIZE)), ofs);
										len+=ofs;
										ssp_slic[num].rd_curr++;
										ssp_slic[num].rd_curr %= LLP_SIZE;
									}	
							}
							else
							{
								//printk("rd : %d\n",ssp_slic[num].rd_curr);
									mdelay(ssp_slic[num].tx_rate/DBUF_SIZE);
									//mdelay(10);
									for(i=0;i<readp;i++)
									{
											copy_to_user((buf+i*SBUF_SIZE), (ssp_slic[num].cr2rbuf+(ssp_slic[num].rd_curr * SBUF_SIZE)), SBUF_SIZE);
											len+=SBUF_SIZE;
											ssp_slic[num].rd_curr++;
											ssp_slic[num].rd_curr %= LLP_SIZE;
									}
									if(ofs)
									{
										copy_to_user((buf+readp*SBUF_SIZE), (ssp_slic[num].cr2rbuf+(ssp_slic[num].rd_curr * SBUF_SIZE)), ofs);
										len+=ofs;
										ssp_slic[num].rd_curr++;
										ssp_slic[num].rd_curr %= LLP_SIZE;
									}	
							}
							ssp_slic[num].dout --;
							if(ssp_slic[num].dout<0)
								ssp_slic[num].dout=0;
						}
				}

			}//if(ssp_slic[num].link_on==1)
		ssp_slic[num].chipData.inrd = 0;
		//printk("gemini_ssp_read : %x\n",len);
	//ssp_slic[num].dout = 0;
	
	return len;//min(length, DBUF_SIZE);
    
}

static int gemini_ssp_get_status_proc(char *buf)
{
	int len;
	
	
	len = 0;
	len += sprintf(buf + len, "\n Storlink middle SSP test !!");
	//len += sprintf(buf + len, "%s", gemini_ssp_c_rcsid);
	//len += sprintf(buf + len, "\n%s", gemini_ssp_h_rcsid);
	//len += sprintf(buf + len, "\n%s", gemini_sspuser_h_rcsid);
	//len += sprintf(buf + len, "\nDriver version %i.%i.%i", gemini_ssp_VER_MAJOR, gemini_ssp_VER_MINOR, gemini_ssp_BLD_VER);
	//len += sprintf(buf + len, "\nsizeof gemini_ssp struct %d bytes", sizeof(gemini_ssp));
	//len += sprintf(buf + len, "\nsizeof DAA struct %d bytes", sizeof(DAA_REGS));
	//len += sprintf(buf + len, "\nUsing old telephony API");
	//len += sprintf(buf + len, "\nDebug Level %d\n", gemini_sspdebug);

	len += sprintf(buf + len, "\n");
	
	return len;
}

static int gemini_ssp_release(struct inode *inode, struct file *file_p)
{
	
	int num;
	SSP_SLIC *ssp_tmp = file_p->private_data;
	num = ssp_tmp->p.board;
	
	printk("Closing board %d\n", num);
	 
	ssp_slic[num].chipData.in_release = 1; 
	//while((!ssp_slic[num].chipData.inrd) || (!ssp_slic[num].chipData.inwt))
	while((ssp_slic[num].chipData.inrd) || (ssp_slic[num].chipData.inwt))
		mdelay(100);
				
				*((volatile unsigned int *)IRQ_MASK(IO_ADDRESS(SL2312_INTERRUPT_BASE))) &= ~(IRQ_DMA_OFFSET);
				ssp_slic[num].link_on=0;
				dma_demo = DMA_NDEMO;
				ssp_slic[num].wt_buf_ok = 0;
				WRITE_DMA_REG(DMA_CFG, 0x0); //disable DMA
				WRITE_DMA_REG(DMA_INT_TC_CLR, 0xc);
				dma_demo = DMA_NDEMO;

	ssp_slic[num].readers--;
	ssp_slic[num].writers--;
	file_p->private_data = NULL;
	ssp_slic[num].chipData.in_release = 0; 

//	MOD_DEC_USE_COUNT;
	return 0;
}

static int gemini_ssp_read_proc(char *page, char **start, off_t off,
                              int count, int *eof, void *data)
{
        int len = gemini_ssp_get_status_proc(page);
        if (len <= off+count) *eof = 1;
        *start = page + off;
        len -= off;
        if (len>count) len = count;
        if (len<0) len = 0;
        return len;
}

struct file_operations gemini_ssp_fops =
{
	    owner:          THIS_MODULE,
        read:           gemini_ssp_read,
        write:          gemini_ssp_write,
//        poll:           gemini_ssp_poll,
        //The poll method is the back end of two system calls, poll and select, both used
		//to inquire if a device is readable or writable or in some special state. Either
		//system call can block until a device becomes readable or writable. If a driver
		//doesn…t define its poll method, the device is assumed to be both readable and
		//writable, and in no special state. The return value is a bit mask describing the
		//status of	the device.
        ioctl:          gemini_ssp_ioctl,
        release:        gemini_ssp_release,
        //This operation is invoked when the file structure is being released. Like
		//open, release can be missing.
//		fasync:         gemini_ssp_fasync
		//This operation is used to notify the device of a change in its FASYNC flag.
		//The field can be NULL if the driver doesn…t support asynchronous notification.
};


static void cleanup(int num)
{
	//int cnt;


	printk(KERN_INFO "Gemini SSP: Removing phone%d\n",num);
	remove_proc_entry ("gemini_ssp", NULL);
}

UINT32 ssp_init(void)
{
	
	UINT32 addr,value;
//	unsigned int *base;
    unsigned int data=0,i,tmp;
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
    	


    	data = READ_GLOBAL_REG(0x30);// readl(IO_ADDRESS(SL2312_GLOBAL_BASE + 0x30));
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
									//not free run mode
	//WRITE_SSP_REG(SSP_FRAME_CTRL, 0x040100f3 ); //0x040100f3//0x04010030//ext clk : bit17
  //	WRITE_SSP_REG(SSP_BAUD_RATE, 0x3f020601);
  WRITE_SSP_REG(SSP_FRAME_CTRL, 0x04010079);  //0x0401007A ); //use 4channel for 2 channel to avoid Rx shift 1 byte
  	WRITE_SSP_REG(SSP_BAUD_RATE, 0x3f020D01);//for
  
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
										//not free run mode
	//	WRITE_SSP_REG(SSP_FRAME_CTRL, 0x04010030 ); //0x04010030//0x04010030//ext clk : bit17
  //	WRITE_SSP_REG(SSP_BAUD_RATE, 0x1F020502);
  //	WRITE_SSP_REG(SSP_FRAME_CTRL, 0x04010018 ); //0x04010030//ext clk : bit17
  //				WRITE_SSP_REG(SSP_BAUD_RATE, 0x1F020B02);//use 4channel for 2 channel to avoid Rx shift 1 byte
		WRITE_SSP_REG(SSP_FRAME_CTRL, 0x04010018 ); //0x04010030//ext clk : bit17
  	WRITE_SSP_REG(SSP_BAUD_RATE, 0x05020102);//use 4channel for 2 channel to avoid Rx shift 1 byte
 #endif 		
  			//	for(i=0;i<DBUF_SIZE;i++)
 				//			wtmp[i]=(0xff&i);	
 					if(NUMBER_OF_CHAN == 1)
  					WRITE_SSP_REG(SSP_FRAME_CTRL2, 0x00038007);//0x0003800f
  				else 
  					WRITE_SSP_REG(SSP_FRAME_CTRL2, 0x00078007);//0x0003800f
  					
  				WRITE_SSP_REG(SSP_FIFO_CTRL, 0x00004714); 
  				if(NUMBER_OF_CHAN==1)
  					WRITE_SSP_REG(SSP_TX_SLOT_VALID0, 0x00000003);//5);
  				else
  					WRITE_SSP_REG(SSP_TX_SLOT_VALID0, 0x0000000f);//5);
  				WRITE_SSP_REG(SSP_TX_SLOT_VALID1, 0x00000000);
  				WRITE_SSP_REG(SSP_TX_SLOT_VALID2, 0x00000000);
  				WRITE_SSP_REG(SSP_TX_SLOT_VALID3, 0x00000000);
  				if(NUMBER_OF_CHAN==1)
  					WRITE_SSP_REG(SSP_RX_SLOT_VALID0, 0x00000003);//5);
  				else
  					WRITE_SSP_REG(SSP_RX_SLOT_VALID0, 0x0000000f);//5);
  				WRITE_SSP_REG(SSP_RX_SLOT_VALID1, 0x00000000);
  				WRITE_SSP_REG(SSP_RX_SLOT_VALID2, 0x00000000);
  				WRITE_SSP_REG(SSP_RX_SLOT_VALID3, 0x00000000);
  				WRITE_SSP_REG(SSP_SLOT_SIZE0, 0xffffffff); 
  				WRITE_SSP_REG(SSP_SLOT_SIZE1, 0xffffffff);
  				WRITE_SSP_REG(SSP_SLOT_SIZE2, 0xffffffff);
  				WRITE_SSP_REG(SSP_SLOT_SIZE3, 0xffffffff);
  				WRITE_SSP_REG(SSP_CTRL_STATUS, 0x20000000);//force TC signal, terminate transfer
  				WRITE_SSP_REG(SSP_CTRL_STATUS, 0x1F100000);//0x9F100000
  				mdelay(250);
  				WRITE_SSP_REG(SSP_CTRL_STATUS, 0x00100000);//0x80100000

	mdelay(500);
	
	daisyChain=0;
		for(i=0;i<NUMBER_OF_CHAN;i++)
		{
			
#if (DAISY_MODE==1)	
			if((daisyChain==0))//&&(NUMBER_OF_CHAN > 1))
			{
					data =SLIC_SPI_read(0,0);
					SLIC_SPI_write(0,0,(data|0x80));
					daisyChain=1;
			}
					data =SLIC_SPI_read(i,0);
				
#endif		
			
				if(SLIC_SPI_get_identifier(i))
				{
					printk("Si3210 not found!!\n");
					return -1;
				}
				      SLIC_init(i);
				      
				      init_waitqueue_head (&thr_wait);
					  	time_to_die = 0;
				      ssp_slic[i].chipData.exce_occ=0;
				      ssp_slic[i].chipData.int_init=0;
				      ssp_slic[i].chipData.version =version(i); 	
				      ssp_slic[i].chipData.type =chipType(i); 
				      ssp_slic[i].chipData.osc1_event = 0;
				      ssp_slic[i].chipData.dtmf_wait = 0; 
				      ssp_slic[i].chipData.ring_type = 1;
				      ssp_slic[i].chipData.ringCount = 0;
				      ssp_slic[i].dma_stop = 0 ;
					      					 
				      goActive(i);  /* set register 64 to a value of 1 */
  			
					  setState(i, ONHOOK);  /* This state is assumed here but it will be tested later. */
					  
					  printkreq_Revision(i);
					  /* print out the PCM clock frequecy and the revision */
					
					//The first 40 indirect registers should be verified after
					//they have been written. This verification provides
					//additional communication confirmation and protects
					//against flaws in the software or the hardware that might
					//damage the circuit if it is powered up when the part is
					//not properly communicating.
					
					  if (verifyIndirectRegisters(i)) 
					  	return -1; //exit(-1);
					
					memset(silent, 0x0, DBUF_SIZE);
				WRITE_DMA_REG(DMA_INT_TC_CLR, 0xc);
				init_waitqueue_head(&ssp_slic[i].poll_q);
  			  init_waitqueue_head(&ssp_slic[i].write_q);
  			  init_waitqueue_head(&ssp_slic[i].read_q);
  			  ssp_slic[i].chipData.in_release = 0;
  			  //ssp_slic[i].desc_ptrr=0;
  			  //ssp_slic[i].desc_ptrt=0;
  			  ssp_slic[i].wt_buf_ok = 0;
  			  ssp_slic[i].tx_rate = 8192;//16384;
  			  
  			  if(gemini_ssp_alloc(i))
				 	return -1;
  			  
				
				/* Register with the Telephony for Linux subsystem */
				ssp_slic[i].board = i;
				ssp_slic[i].p.minor = i;
				ssp_slic[i].p.f_op = &gemini_ssp_fops;
				ssp_slic[i].p.open = gemini_ssp_open;
				ssp_slic[i].p.board = ssp_slic[i].board;
				ssp_slic[i].rx_curr = ssp_slic[i].rx_curr = 0;
				phone_register_device(&ssp_slic[i].p, PHONE_UNIT_ANY);
		}//for(i=0;i<NUMBER_OF_CHAN;i++)
#if (DAISY_MODE==1)		
	//for(i=1;i<NUMBER_OF_CHAN;i++)
	{
		//set phone1 Tx/Rx start count
		SLIC_SPI_write(0,2,0x0); //0bit
		SLIC_SPI_write(0,4,0x0);
		if(NUMBER_OF_CHAN == 2)
		{
			SLIC_SPI_write(1,2,0x10); //16bit
			SLIC_SPI_write(1,4,0x10);
		}
	}
#endif			
		desc_ptrr=0;
  	desc_ptrt=0;
		gemini_ssp_alloc_dmabuf();
//		interrupt_init();
		  return 0;
}

int __init gemini_ssp_init(void)
{
	int cnt = 0;
	int probe = 0;   
//	int i;

	cnt = 0;

	if((probe = ssp_init()) < 0)
		return probe;
		
		/*
			ssp_slic[i].thr_pid = kernel_thread (gemini_slic_thread, &ssp_slic[i], CLONE_FS | CLONE_FILES);
    	if (ssp_slic[i].thr_pid < 0)
    	{
    		printk (KERN_WARNING "SSP_SLIC: unable to start kernel thread\n");
    	}
    
    */
#if 1
    	thr_pid = kernel_thread (gemini_slic_thread, NULL, CLONE_FS | CLONE_FILES);
    	if (thr_pid < 0)
    	{
    		printk (KERN_WARNING "SSP_SLIC: unable to start kernel thread\n");
    	}
#endif    	
			interrupt_init();
	create_proc_read_entry ("gemini_ssp", 0, NULL, gemini_ssp_read_proc, NULL);
	return probe;
}


MODULE_DESCRIPTION("Storlink Synchronous Serial Interface module with PROSLIC - www.storlink.com.tw");
MODULE_AUTHOR(".....");
MODULE_LICENSE("GPL");

void gemini_ssp_exit(void)
{
	int ret, i;
		for(i=0;i<NUMBER_OF_CHAN;i++)
		{
        cleanup(i);
        if(ssp_slic[i].cw2tbuf != NULL)
					kfree(ssp_slic[i].cw2tbuf);
				if(ssp_slic[i].cr2rbuf != NULL)
					kfree(ssp_slic[i].cr2rbuf);
     }
        
    if(LinkAddrT != NULL)
			kfree(LinkAddrT);
		if(LinkAddrR != NULL)
			kfree(LinkAddrR);
			if(tbuf != NULL)
				kfree(tbuf);
				if(rbuf != NULL)
					kfree(rbuf);
				
        
        *((volatile unsigned int *)IRQ_MASK(IO_ADDRESS(SL2312_INTERRUPT_BASE))) &= ~(IRQ_DMA_OFFSET);;
#ifdef CONFIG_SL3516_ASIC
		free_gpio_irq(0); //SSP_GPIO_INT_BIT = 0x400 -> bit 10
#else
        free_gpio_irq(10); //SSP_GPIO_INT_BIT = 0x400 -> bit 10
#endif        
        free_irq(IRQ_DMA_OFFSET, NULL);
        

        /* setup interrupt controller  */ 

				ret = kill_proc (thr_pid, SIGTERM, 1);
    		if (ret)
    		{
    			printk (KERN_ERR "Sl2312_SSP : unable to signal thread.\n");
    			//return ret;
    			return ;
    		}
} 

module_init(gemini_ssp_init);
module_exit(gemini_ssp_exit);


