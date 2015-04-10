/******************************************************************************
 *    gemini_ssp.h
 *
 *
 *****************************************************************************/

#include <linux/types.h>
#include <asm/arch-sl2312/irqs.h>
#include <linux/phonedev.h>
#include <linux/telephony.h>
#include "proslic.h"

typedef __u16 UINT16;
typedef __u32 UINT32;
typedef __u8 UINT8;
typedef __u8 BOOL;

#define TRUE 1
#define FALSE 0

/***************************************/
/* define GPIO module base address     */
/***************************************/
#define DMA_CONTROL_PHY_BASE  (IO_ADDRESS(SL2312_GENERAL_DMA_BASE))
#define DMA_CONTROL_SSP_BASE  (IO_ADDRESS(SL2312_SSP_CTRL_BASE))
#define SSP_INT				IRQ_SSP   
#define GPIO_BASE_ADDR      (IO_ADDRESS(SL2312_GPIO_BASE))
#define GPIO_BASE_ADDR1      (IO_ADDRESS(SL2312_GPIO_BASE1))
#define GLOBAL_BASE      (IO_ADDRESS(SL2312_GLOBAL_BASE))

/* define read/write register utility */
#define FLASH_READ_SSP_REG(offset)			(__raw_readl(offset+DMA_CONTROL_SSP_BASE))
#define FLASH_WRITE_SSP_REG(offset,val) 	(__raw_writel(val,offset+DMA_CONTROL_SSP_BASE))

#define FLASH_READ_GPIO_REG(offset)			(__raw_readl(offset+GPIO_BASE_ADDR))
#define FLASH_WRITE_GPIO_REG(offset,val) 	(__raw_writel(val,offset+GPIO_BASE_ADDR))

#define FLASH_READ_GPIO1_REG(offset)			(__raw_readl(offset+GPIO_BASE_ADDR1))
#define FLASH_WRITE_GPIO1_REG(offset,val) 	(__raw_writel(val,offset+GPIO_BASE_ADDR1))

#define READ_DMA_REG(offset)			(__raw_readl(offset+DMA_CONTROL_PHY_BASE))
#define WRITE_DMA_REG(offset,val) 	(__raw_writel(val,offset+DMA_CONTROL_PHY_BASE))

#define READ_GLOBAL_REG(offset)			(__raw_readl(offset+GLOBAL_BASE))
#define WRITE_GLOBAL_REG(offset,val) 	(__raw_writel(val,offset+GLOBAL_BASE))


#define SSP_GPIO_INT       	IRQ_GPIO

#ifndef CONFIG_SL3516_ASIC
#define SSP_GPIO_INT_BIT    0x00000400				//GPIO[10] : SLIC interrupt pin

#define GPIO_EECK	     0x00000040         /*   SCK: GPIO[06]   */
#define GPIO_EECS	     0x00000080			/*   SCS: GPIO[07]   */
#define GPIO_MISO	     0x00000200         /*   SDO: GPIO[09]   receive from 6996*/                         
#define GPIO_MOSI	     0x00000100         /*   SDI: GPIO[08]   send to 6996*/                          
#define GPIO_MISO_BIT	 9
#else
#define SSP_GPIO_INT_BIT    0x00000001				//GPIO[0] : SLIC interrupt pin

//#if 0
//#define GPIO_EECK	     0x80000000         /*   SCK: GPIO1[31]   */
//#define GPIO_EECS	     0x40000000			/*   SCS: GPIO1[30]   */
//#define GPIO_MISO	     0x20000000         /*   SDO: GPIO1[29]   receive from 6996*/                         
//#define GPIO_MOSI	     0x10000000         /*   SDI: GPIO1[28]   send to 6996*/                          
//#define GPIO_MISO_BIT	29	
//#else
//#define GPIO_EECK	     0x00000100         /*   SCK: GPIO1[08]   */
//#define GPIO_EECS	     0x08000000			/*   SCS: GPIO1[27]   */
//#define GPIO_MISO	     0x00000080         /*   SDO: GPIO1[07]   receive from 6996*/                         
//#define GPIO_MOSI	     0x00000200         /*   SDI: GPIO1[09]   send to 6996*/                          
//#define GPIO_MISO_BIT	7	
//#endif
#endif


enum GPIO_REG
{
	GPIO_DATA_OUT   	= 0x00,
	GPIO_DATA_IN    	= 0x04,
	GPIO_PIN_DIR    	= 0x08,
	GPIO_BY_PASS    	= 0x0c,
	GPIO_DATA_SET   	= 0x10,
	GPIO_DATA_CLEAR 	= 0x14,
	GPIO_INT_ENABLE     = 0x20,
	GPIO_INT_RAWSTATE   = 0x24,
	GPIO_INT_MASKSTATE  = 0x28,
	GPIO_INT_MASK       = 0x2C,
	GPIO_INT_CLEAR      = 0x30,
	GPIO_INT_TRIGGER    = 0x34,
	GPIO_INT_BOTH       = 0x38,
	GPIO_INT_POLARITY   = 0x3C
};


#define SPI_ADD_LEN	     7			// bits of Address
#define SPI_DAT_LEN	     8			// bits of Data



//#ifdef MIDWAY_DIAG

#define LLP_SIZE   16
#define SBUF_SIZE  512 //0xff0 //2560
#define TBUF_SIZE  (LLP_SIZE)*SBUF_SIZE
#define DESC_NUM   1
#define DTMF_NUM   20

/* define owner bit of SSP */
//data into SSP and transfer to AP==> SSP_Rx
//data out of SSP and transfer to SLIC==> SSP_Tx
#define CPU		0
#define DMA		1

#define DMA_DEMO   1
#define DMA_NDEMO  2
#define DMA_NONE   3



typedef struct
{
	UINT32 src_addr;
	UINT32 dst_addr;
	UINT32 llp;
	UINT32 ctrl_size;
}DMA_LLP_t;

typedef struct {
	unsigned int own ;
	char  *tbuf;
	//UINT32 *LinkAddrT;
	DMA_LLP_t LLPT[LLP_SIZE];	
}DMA_Tx_t;

typedef struct {
	unsigned int own ;
	char  *rbuf;
	//UINT32 *LinkAddrR;
	DMA_LLP_t LLPR[LLP_SIZE];	
}DMA_Rx_t;

//typedef struct {
//	//UINT32 init_stat;
//	struct chipStruct chipData ; /* Represents a proslics state, cached information, and timers */
//	struct phone_device p;
//	
//	
//}SSP_SLIC;



/* DMA Registers */
#define	DMA_INT 		   		0x00000000
#define	DMA_INT_TC 		   		0x00000004
#define	DMA_CFG 		   		0x00000024
#define	DMA_INT_TC_CLR				0x00000008
#define	DMA_TC						0x00000014
#define	DMA_CSR						0x00000024
#define	DMA_SYNC					0x00000028

#define	DMA_CH2_CSR    				0x00000140
#define	DMA_CH2_CFG    				0x00000144
#define	DMA_CH2_SRC_ADDR    		0x00000148
#define	DMA_CH2_DST_ADDR    		0x0000014c
#define	DMA_CH2_LLP    				0x00000150
#define	DMA_CH2_SIZE    			0x00000154

#define	DMA_CH3_CSR    				0x00000160
#define	DMA_CH3_CFG    				0x00000164
#define	DMA_CH3_SRC_ADDR    		0x00000168
#define	DMA_CH3_DST_ADDR    		0x0000016c
#define	DMA_CH3_LLP    				0x00000170
#define	DMA_CH3_SIZE    			0x00000174

#define    SSP_DEVICE_ID   			0x00
#define    SSP_CTRL_STATUS 			0x04
#define	   SSP_FRAME_CTRL           0x08
#define    SSP_BAUD_RATE            0x0c
#define    SSP_FRAME_CTRL2          0x10
#define    SSP_FIFO_CTRL            0x14
#define    SSP_TX_SLOT_VALID0       0x18
#define    SSP_TX_SLOT_VALID1       0x1c
#define    SSP_TX_SLOT_VALID2       0x20
#define    SSP_TX_SLOT_VALID3       0x24
#define    SSP_RX_SLOT_VALID0       0x28
#define    SSP_RX_SLOT_VALID1       0x2c
#define    SSP_RX_SLOT_VALID2       0x30
#define    SSP_RX_SLOT_VALID3       0x34
#define    SSP_SLOT_SIZE0           0x38
#define    SSP_SLOT_SIZE1           0x3c
#define    SSP_SLOT_SIZE2           0x40
#define    SSP_SLOT_SIZE3           0x44
#define    SSP_READ_PORT            0x48
#define    SSP_WRITE_PORT           0x4c


void printFreq_Revision(void);
void SLIC_SPI_write(UINT8 ,UINT8);
UINT8 SLIC_SPI_read(UINT8);
void SLIC_SPI_write_bit(char);
void SLIC_SPI_ind_write(UINT8, UINT16);
UINT16 SLIC_SPI_ind_read(UINT8);
void SLIC_SPI_CS_enable(UINT8);
unsigned int SLIC_SPI_read_bit(void);
void SLIC_SPI_pre_st(void);
UINT32 ssp_init(void);
UINT16 SLIC_SPI_get_identifier(void);
int selfTest(void);
void exception (enum exceptions e);
int SLIC_init(void);
UINT8 version(void);
UINT8 chipType (void);
void SLIC_init_ind_reg_set(void);
UINT8 powerUp(void);
UINT8 powerLeakTest(void);
void SLIC_init_reg_set(void);
int calibrate(void);
void goActive(void);
void clearInterrupts(void);
void setState(int);
UINT8 loopStatus(void);
int verifyIndirectRegisters(void);
int verifyIndirectReg(UINT8 , UINT16);
void sendProSLICID(void);
void disableOscillators(void);
UINT8 checkSum( char * string );
void fskInitialization (void);
void fskByte(UINT8 c);
void waitForInterrupt (void);
//void findNumber(void);
UINT8 dtmfAction(void);
UINT8 digit(void);
void interrupt_init(void);
static void gemini_slic_isr (int );
int groundShort(void);
void clearAlarmBits(void);
void stopRinging(void);
void activateRinging(void);
void initializeLoopDebounceReg(void);
void busyJapan(void) ;
void ringBackJapan(void) ;
void stateMachine(void);

