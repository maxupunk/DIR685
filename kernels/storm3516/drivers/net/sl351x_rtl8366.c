/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright c 2003 Atheros Communications, Inc.,  All Rights Reserved.
 */

/*
 * All definitions in this file are operating system independent!
 *
 *	 07/17/2008  CH Hsu      Cortina Systems, Inc.   
 */
 
#include <linux/config.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/delay.h>
#include <asm/hardware.h>
#include <asm/io.h>

//#ifdef CONFIG_RTL8366SR_PHY
#include <asm/arch/sl351x_rt8366.h>

#define uint32_t unsigned int
#define uint16_t unsigned short
#define uint8_t unsigned char
#define uint64_t unsigned long long

typedef struct  VLANTABLE{
#if 1//def _LITTLE_ENDIAN
	uint16_t 	vid:12;
 	uint16_t 	reserved1:4;
	
 	uint16_t 	member:6;
 	uint16_t 	untag:6;
 	uint16_t 	fid:3;
	uint16_t 	reserved2:1;

#else
 	uint16_t 	reserved1:4;
	uint16_t 	vid:12;

	uint16_t 	reserved2:1;
 	uint16_t 	fid:3;
 	uint16_t 	untag:6;
 	uint16_t 	member:6;
	
#endif
}rtl8366s_vlan4kentry;

typedef struct  VLANCONFIG{
#if 1//def _LITTLE_ENDIAN
	uint16_t 	vid:12;
 	uint16_t 	priority:3;
 	uint16_t 	reserved1:1;

	uint16_t 	member:6;
 	uint16_t 	untag:6;
 	uint16_t 	fid:3;
	uint16_t 	reserved2:1;

#else
  	uint16_t 	reserved2:1;
	uint16_t 	priority:3;
	uint16_t 	vid:12;


	uint16_t 	reserved1:1;
 	uint16_t 	fid:3;
 	uint16_t 	untag:6;
 	uint16_t 	member:6;

#endif
}rtl8366s_vlanconfig;

typedef struct phyAbility_s
{
	uint16_t	AutoNegotiation:1;/*PHY register 0.12 setting for auto-negotiation process*/
	uint16_t	Half_10:1;		/*PHY register 4.5 setting for 10BASE-TX half duplex capable*/
	uint16_t	Full_10:1;		/*PHY register 4.6 setting for 10BASE-TX full duplex capable*/
	uint16_t	Half_100:1;		/*PHY register 4.7 setting for 100BASE-TX half duplex capable*/
	uint16_t	Full_100:1;		/*PHY register 4.8 setting for 100BASE-TX full duplex capable*/
	uint16_t	Full_1000:1;	/*PHY register 9.9 setting for 1000BASE-T full duplex capable*/
	uint16_t	FC:1;			/*PHY register 4.10 setting for flow control capability*/
	uint16_t	AsyFC:1;		/*PHY register 4.11 setting for  asymmetric flow control capability*/
} phyAbility_t;

#define GMAC_SPEED_10			0
#define GMAC_SPEED_100			1
#define GMAC_SPEED_1000			2

#define _1000BASET GMAC_SPEED_1000
#define _100BASET GMAC_SPEED_100
#define _10BASET GMAC_SPEED_10

#define GPIO1_BASE_ADDR  (IO_ADDRESS(SL2312_GPIO_BASE1))

#define GPIO_DATA_OUT 0x00
#define GPIO_DATA_IN  0x04
#define GPIO_PIN_DIR  0x08
#define GPIO_BY_PASS  0x0c
#define GPIO_DATA_SET 0x10
#define GPIO_DATA_CLEAR 0x14


#define readl(addr)								REG32(addr)
#define writel(value, addr)						REG32(addr) = value
//#define DEBUG_MSG 
#define DEBUG_MSG printk

extern char *wan_speed;
/* PHY selections and access functions */
//extern int autoNeg;
/*
 * Track per-PHY port information.
 */
typedef struct {    
	BOOL   isEnetPort;       /* normal enet port */
    BOOL   isPhyAlive;       /* last known state of link */
    int    ethUnit;          /* MAC associated with this phy port */    
} rtlPhyInfo_t;

/*
 * Per-PHY information, indexed by PHY unit number.
 */
static rtlPhyInfo_t rtlPhyInfo[] = {
    {TRUE,
     FALSE,   /* phy port 0 -- LAN port 0 or DMZ port */     
     0//LAN
    },
    {TRUE,
     FALSE,   /* phy port 1 -- LAN port 1 */     
     0
    },
    {TRUE,
     FALSE,   /* phy port 2 -- LAN port 2 */
     0
    },
    {TRUE,
     FALSE,   /* phy port 3 -- LAN port 3 */
     0
    },
    {TRUE,
     FALSE,   /* phy port 4 -- LAN port 4 */
     0    
    },    
    { FALSE,
      FALSE, /* phy port 5 -- CPU port (no RJ45 connector) */     
     2//cpu
    },
};

/* Convenience macros to access myPhyInfo */
#define RTL_IS_ENET_PORT(phyUnit) (rtlPhyInfo[phyUnit].isEnetPort)
#define RTL_IS_PHY_ALIVE(phyUnit) (rtlPhyInfo[phyUnit].isPhyAlive)
#define RTL_ETHUNIT(phyUnit) (rtlPhyInfo[phyUnit].ethUnit)

#define RTL_IS_ETHUNIT(phyUnit, ethUnit) \
            (RTL_IS_ENET_PORT(phyUnit) &&        \
            RTL_ETHUNIT(phyUnit) == (ethUnit))

#define I2CMASTER_SDA_PIN 29//gpio 29
#define I2CMASTER_SCL_PIN 28//gpio 28
//#define SWITCH_RESET 21//gpio 21

/*
 * set_data_in()
 */
static inline void set_data_in(void)
{
	//DEBUG_MSG("datain i=%x,g=%x\n",*(volatile int *)(0xb8040014),*(volatile int *)(0xb8040000));
	//DEBUG_MSG("datainv i=%x,g=%x\n",~(1<<I2CMASTER_SDA_PIN),~(1<<I2CMASTER_SDA_PIN));
	//*(volatile int *)(0xb8040014) &= ~(1<<I2CMASTER_SDA_PIN);//disable int
	*(volatile int *)(GPIO1_BASE_ADDR+GPIO_PIN_DIR) &= ~(1<<I2CMASTER_SDA_PIN);//change to input
	//DEBUG_MSG("datain2 i=%x,g=%x\n",*(volatile int *)(0xb8040014),*(volatile int *)(0xb8040000));
}

/*
 * set_data_out()
 */
static inline void set_data_out(void)
{
	//DEBUG_MSG("dataout i=%x,g=%x\n",*(volatile int *)(0xb8040014),*(volatile int *)(0xb8040000));
	//DEBUG_MSG("dataoutv i=%x,g=%x\n",~(1<<I2CMASTER_SDA_PIN),(1<<I2CMASTER_SDA_PIN));
	//*(volatile int *)(0xb8040014) &= ~(1<<I2CMASTER_SDA_PIN);//disable int
	*(volatile int *)(GPIO1_BASE_ADDR+GPIO_PIN_DIR) |= (1<<I2CMASTER_SDA_PIN);//change to output	
	//DEBUG_MSG("dataout2 i=%x,g=%x\n",*(volatile int *)(0xb8040014),*(volatile int *)(0xb8040000));
}

/*
 * set_clock_in()
 */
static inline void set_clock_in(void)
{
	//DEBUG_MSG("clockin i=%x,g=%x\n",*(volatile int *)(0xb8040014),*(volatile int *)(0xb8040000));
	//DEBUG_MSG("clockinv i=%x,g=%x\n",~(1<<I2CMASTER_SCL_PIN),~(1<<I2CMASTER_SCL_PIN));
	//*(volatile int *)(0xb8040014) &= ~(1<<I2CMASTER_SCL_PIN);//disable int
	*(volatile int *)(GPIO1_BASE_ADDR+GPIO_PIN_DIR) &= ~(1<<I2CMASTER_SCL_PIN);//change to input	
	//DEBUG_MSG("clockin2 i=%x,g=%x\n",*(volatile int *)(0xb8040014),*(volatile int *)(0xb8040000));		
}

/*
 * set_clock_out()
 */
static inline void set_clock_out(void)
{
	//DEBUG_MSG("clockout i=%x,g=%x\n",*(volatile int *)(0xb8040014),*(volatile int *)(0xb8040000));
	//DEBUG_MSG("clockoutv i=%x,g=%x\n",~(1<<I2CMASTER_SCL_PIN),(1<<I2CMASTER_SCL_PIN));
	//*(volatile int *)(0xb8040014) &= ~(1<<I2CMASTER_SCL_PIN);//disable int
	*(volatile int *)(GPIO1_BASE_ADDR+GPIO_PIN_DIR) |= (1<<I2CMASTER_SCL_PIN);//change to output	
	//DEBUG_MSG("clockout2 i=%x,g=%x\n",*(volatile int *)(0xb8040014),*(volatile int *)(0xb8040000));
}

/*
 * set_data_pin()
 */
static inline void set_data_pin(uint32_t v)
{		
#if 1
	if (v) {//high		
		*(volatile int *)(GPIO1_BASE_ADDR+GPIO_DATA_OUT) |= 1<<I2CMASTER_SDA_PIN;
	} else {//low	
		*(volatile int *)(GPIO1_BASE_ADDR+GPIO_DATA_OUT) &= ~(1<<I2CMASTER_SDA_PIN);		
	}
#else
	unsigned int addr;
	unsigned int value;
	if (v) {//high	
		addr =(GPIO1_BASE_ADDR + GPIO_DATA_SET);
		writel(1<<I2CMASTER_SDA_PIN,addr); // set to 1			
	} else {//low	
		addr =(GPIO1_BASE_ADDR + GPIO_DATA_CLEAR);
		writel(1<<I2CMASTER_SDA_PIN,addr); // set to 0			
	}
#endif	
}

/*
 * get_data_pin()
 */
static inline uint32_t get_data_pin(void)
{	
	 //DEBUG_MSG("v=%x,m=%x\n",(*(volatile unsigned long *)0xb8040004),(1<<I2CMASTER_SDA_PIN));
	 if((*(volatile unsigned long *)(GPIO1_BASE_ADDR+GPIO_DATA_IN)) & (1<<I2CMASTER_SDA_PIN))
	 	return 1;
	 else
	 	return 0;			
}

/*
 * set_clock_pin()
 */
static inline void set_clock_pin(uint32_t v)
{	
#if 1
	if (v) {//hifh		
		*(volatile int *)(GPIO1_BASE_ADDR+GPIO_DATA_OUT) |= 1<<I2CMASTER_SCL_PIN;
	} else {//low		
		*(volatile int *)(GPIO1_BASE_ADDR+GPIO_DATA_OUT) &= ~(1<<I2CMASTER_SCL_PIN);		
	}
#else
	unsigned int addr;
	unsigned int value;
	if (v) {//high	
		addr =(GPIO1_BASE_ADDR + GPIO_DATA_SET);
		writel(1<<I2CMASTER_SCL_PIN,addr); // set to 1			
	} else {//low	
		addr =(GPIO1_BASE_ADDR + GPIO_DATA_CLEAR);
		writel(1<<I2CMASTER_SCL_PIN,addr); // set to 0			
	}
#endif		
}

#define DELAY 2//us
#define ack_timer					5
#define max_register				0x018A 

uint32_t smi_init(void)
{
	//DEBUG_MSG("smi i=%x,g=%x\n",*(volatile int *)(0xb8040014),*(volatile int *)(0xb8040000));	
	/* change GPIO pin to Input only */
	set_data_in();
	set_clock_in();	
	
	//DEBUG_MSG("smi2 i=%x,g=%x\n",*(volatile int *)(0xb8040014),*(volatile int *)(0xb8040000));
	udelay(DELAY);		
	return 0;
}

void _smi_start(void)
{
	/* change GPIO pin to Output only */
	set_data_out();
	set_clock_out();	
	udelay(DELAY);
	/* Initial state: SCK:0,SDA:1 */
	set_clock_pin(0);
	set_data_pin(1);
	udelay(DELAY);

	/* SCK:0 -> 1 -> 0 */
	set_clock_pin(1);
	udelay(DELAY);
	set_clock_pin(0);
	udelay(DELAY);

	/* SCK:1,SDA:0->SCK:0,SDA:1 */
	set_clock_pin(1);
	udelay(DELAY);
	set_data_pin(0);
	udelay(DELAY);
	set_clock_pin(0);
	udelay(DELAY);
	set_data_pin(1);	
}

void _smi_stop(void)
{
	/* SCK:1,SDA:0->SCK:1,SDA:1->SCK:0->1 */
	udelay(DELAY);
	set_data_pin(0);	
	set_clock_pin(1);	
	udelay(DELAY);
	set_data_pin(1);	
	udelay(DELAY);
	set_clock_pin(1);
	udelay(DELAY);
	set_clock_pin(0);
	udelay(DELAY);
	set_clock_pin(1);

    /* SCK:0->1 */
	udelay(DELAY);
	set_clock_pin(0);
	udelay(DELAY);
	set_clock_pin(1);

	/* change GPIO pin to Output only */
	set_data_in();
	set_clock_in();

}

#if 0
uint32_t smi_reset(void)
{
	/* Initialize GPIO pin x as SMI RESET */	
	*(volatile int *)(0xb8040000) |= (1<<SWITCH_RESET);//change to output	
		
	*(volatile int *)(0xb8040008) &= ~(1<<SWITCH_RESET);//pin low
	udelay(1000000);
	*(volatile int *)(0xb8040008) |= 1<<I2CMASTER_SCL_PIN;//pin high
	udelay(1000000);
	*(volatile int *)(0xb8040008) &= ~(1<<SWITCH_RESET);//pin low
	
	/* change GPIO pin to Input only */
	*(volatile int *)(0xb8040000) &= ~(1<<SWITCH_RESET);//change to input

	return 0;
}
#endif

void _smi_writeBit(uint16_t signal, uint32_t bitLen)
{
	for( ; bitLen > 0; bitLen--)
	{
		udelay(DELAY);
		/* prepare data */
		if ( signal & (1<<(bitLen-1)) ) 
			set_data_pin(1);	
		else 
			set_data_pin(0);	
		udelay(DELAY);

		/* clocking */
		set_clock_pin(1);
		udelay(DELAY);
		set_clock_pin(0);
	}
}

void _smi_readBit(uint32_t bitLen, uint32_t *rData) 
{
	uint32_t u;

	/* change GPIO pin to Input only */
	set_data_in();
			
	for (*rData = 0; bitLen > 0; bitLen--)
	{
		udelay(DELAY);
		/* clocking */
		set_clock_pin(1);
		udelay(DELAY);		
		u = get_data_pin();
		//DEBUG_MSG("u=%x\n",u);
		set_clock_pin(0);
		*rData |= (u << (bitLen - 1));		
		//DEBUG_MSG("b=%d,*rData=%x\n",bitLen,*rData);		
	}

	/* change GPIO pin to Output only */
	set_data_out();
}

uint32_t smi_read(uint32_t mAddrs, uint32_t *rData)
{
	uint32_t rawData = 0, ACK;
	uint8_t  con;
	uint32_t ret = 0;
/*
	if ((mAddrs > max_register) || (rData == NULL))  return	1;
*/

	//DEBUG_MSG("smi read mAddrs=0x%x,rData=0x%x\n", mAddrs ,*rData);
	/*Disable CPU interrupt to ensure that the SMI operation is atomic. 
	  The API is based on RTL865X, rewrite the API if porting to other platform.*/
   	//rtlglue_drvMutexLock();

	_smi_start();								/* Start SMI */

	_smi_writeBit(0x0a, 4); 					/* CTRL code: 4'b1010 */

	_smi_writeBit(0x4, 3);						/* CTRL code: 3'b100 */

	_smi_writeBit(0x1, 1);						/* 1: issue READ command */

	con = 0;
	do {
		con++;
		_smi_readBit(1, &ACK);					/* ACK for issuing READ command*/
	} while ((ACK != 0) && (con < ack_timer));
	if (ACK != 0){
		//DEBUG_MSG("CTRL read fail\n");
		ret = 1;
	}
	//DEBUG_MSG("LSB addrs=0x%x\n",(mAddrs&0xff));
	_smi_writeBit((mAddrs&0xff), 8); 			/* Set reg_addr[7:0] */

	con = 0;
	do {
		con++;
		_smi_readBit(1, &ACK);					/* ACK for setting reg_addr[7:0] */	
	} while ((ACK != 0) && (con < ack_timer));
	if (ACK != 0){
		 //DEBUG_MSG("LSB addrs fail\n");
		 ret = 1;
	}	 
	//DEBUG_MSG("MSB addrs=0x%x\n",(mAddrs>>8));
	_smi_writeBit((mAddrs>>8), 8); 				/* Set reg_addr[15:8] */

	con = 0;
	do {
		con++;
		_smi_readBit(1, &ACK);					/* ACK by RTL8369 */
	} while ((ACK != 0) && (con < ack_timer));
	if (ACK != 0){
		 //DEBUG_MSG("MSB addrs fail\n");
		 ret = 1;
	}	 

	_smi_readBit(8, &rawData);					/* Read DATA [7:0] */
	//DEBUG_MSG("rLSB data=0x%x\n",rawData);
	*rData = rawData&0xff; 
	//DEBUG_MSG("*rData=0x%x\n",*rData);
	_smi_writeBit(0x00, 1);						/* ACK by CPU */

	_smi_readBit(8, &rawData);					/* Read DATA [15: 8] */
	//DEBUG_MSG("rMSB data=0x%x\n",rawData);
	_smi_writeBit(0x01, 1);						/* ACK by CPU */
	*rData |= (rawData<<8);
	//DEBUG_MSG("*rData=0x%x\n",*rData);

	_smi_stop();

	//rtlglue_drvMutexUnlock();/*enable CPU interrupt*/
	//DEBUG_MSG("*rData=0x%x\n",*rData);
	return ret;
}

uint32_t smi_write(uint32_t mAddrs, uint32_t rData)
{

	uint8_t con;
	uint32_t ACK;
	uint32_t ret = 0;	
	
/*
	if ((mAddrs > 0x018A) || (rData > 0xFFFF))  return	1;
*/
	//DEBUG_MSG("smi write mAddrs=0x%x,rData=0x%x\n", mAddrs ,rData);
	/*Disable CPU interrupt to ensure that the SMI operation is atomic. 
	  The API is based on RTL865X, rewrite the API if porting to other platform.*/
   	//rtlglue_drvMutexLock();

	_smi_start();								/* Start SMI */

	_smi_writeBit(0x0a, 4); 					/* CTRL code: 4'b1010 */

	_smi_writeBit(0x4, 3);						/* CTRL code: 3'b100 */

	_smi_writeBit(0x0, 1);						/* 0: issue WRITE command */

	con = 0;
	do {
		con++;
		_smi_readBit(1, &ACK);					/* ACK for issuing WRITE command*/
	} while ((ACK != 0) && (con < ack_timer));
	if (ACK != 0){ 
		//DEBUG_MSG("CTRL write fail\n");
		ret = 1;
	}	
	//DEBUG_MSG("LSB addrs=0x%x\n",(mAddrs&0xff));
	_smi_writeBit((mAddrs&0xff), 8); 			/* Set reg_addr[7:0] */

	con = 0;
	do {
		con++;
		_smi_readBit(1, &ACK);					/* ACK for setting reg_addr[7:0] */
	} while ((ACK != 0) && (con < ack_timer));
	if (ACK != 0){
		 //DEBUG_MSG("LSB addrs fail\n");
		 ret = 1;
	}	 
	//DEBUG_MSG("MSB addrs=0x%x\n",(mAddrs>>8));
	_smi_writeBit((mAddrs>>8), 8); 				/* Set reg_addr[15:8] */

	con = 0;
	do {
		con++;
		_smi_readBit(1, &ACK);					/* ACK for setting reg_addr[15:8] */
	} while ((ACK != 0) && (con < ack_timer));
	if (ACK != 0){
		 //DEBUG_MSG("MSB addrs fail\n");
		 ret = 1;
	}
	//DEBUG_MSG("LSB data=0x%x\n",(rData&0xff));
	_smi_writeBit((rData&0xff), 8);				/* Write Data [7:0] out */

	con = 0;
	do {
		con++;
		_smi_readBit(1, &ACK);					/* ACK for writting data [7:0] */
	} while ((ACK != 0) && (con < ack_timer));
	if (ACK != 0){
		 //DEBUG_MSG("LSB data fail\n");
		 ret = 1;
	}	 
	//DEBUG_MSG("MSB data=0x%x\n",(rData>>8));
	_smi_writeBit((rData>>8), 8);					/* Write Data [15:8] out */

	con = 0;
	do {
		con++;
		_smi_readBit(1, &ACK);						/* ACK for writting data [15:8] */
	} while ((ACK != 0) && (con < ack_timer));
	if (ACK != 0){
		//DEBUG_MSG("MSB data fail\n");
		ret = 1;
	}	

	_smi_stop();	

	//rtlglue_drvMutexUnlock();/*enable CPU interrupt*/
	
	return ret;
}

/****************************************************************************/
/****************************************************************************/
uint32_t switch_reg_read(uint32_t reg,uint32_t *value)
{    
    uint32_t regData=0;
	uint32_t retVal;
	if(*value)
		*value=0;
	//DEBUG_MSG("sw read reg=0x%x,data=0x%x\n", reg ,*value);
	retVal = smi_read(reg, &regData);
	if (retVal != 0){
		DEBUG_MSG("smi_read fail\n");
		return 1;
	}	
	*value = regData;    
	//DEBUG_MSG("sw read reg=0x%x,data=0x%x\n", reg ,*value);
    return 0;
}

void switch_reg_write(uint32_t reg, uint32_t data)
{
    uint32_t retVal;
	//DEBUG_MSG("sw write reg=0x%x,data=0x%x\n", reg ,data);
	retVal = smi_write(reg, data);
	if (retVal != 0) 
		DEBUG_MSG("smi_write fail\n");		

}

/*=======================================================================
 * 1. Asic read/write driver through SMI
 *========================================================================*/
/*
@func uint32_t | rtl8366s_getAsicReg | Get content of register.
@parm uint32_t | reg | Register's address.
@parm uint32_t* | value | Value of register.
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@comm
 	Value 0x0000 will be returned for ASIC un-mapping address.
	
*/
static uint32_t rtl8366s_getAsicReg(uint32_t reg, uint32_t *value)
{
    if (value==NULL){ 
    	DEBUG_MSG("getAsicReg val null\n");	
    	return FAILED;
    }	
    
    if(switch_reg_read(reg,value)){
    	DEBUG_MSG("switch_reg_read fail\n");
    	return FAILED;
    }
    else{    	
    	return SUCCESS;
    }	    
}


/*
@func uint32_t | rtl8366s_setAsicRegBit | Set a bit value of a specified register.
@parm uint32_t | reg | Register's address.
@parm uint32_t | bit | Bit location. For 16-bits register only. Maximun value is 15 for MSB location.
@parm uint32_t | value | Value to set. It can be value 0 or 1.
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@rvalue TBLDRV_EINVALIDINPUT | Invalid input parameter. 
@comm
	Set a bit of a specified register to 1 or 0. It is 16-bits system of RTL8366s chip.
	
*/
uint32_t rtl8366s_setAsicRegBit(uint32_t reg, uint32_t bit, uint32_t value)
{
	uint32_t regData;
	uint32_t retVal;
	
	if(bit>=16){
		DEBUG_MSG("rtl8366s_setAsicRegBit: bit fial\n");
		return 1;
	}	

	retVal = smi_read(reg, &regData);
	if (retVal != 0){
		DEBUG_MSG("rtl8366s_setAsicRegBit: smi_read fail\n");
		return 1;
	}	

	if (value) 
		regData = regData | (1<<bit);
	else
		regData = regData & (~(1<<bit));
	
	retVal = smi_write(reg, regData);
	if (retVal != 0){
		DEBUG_MSG("rtl8366s_setAsicRegBit: smi_write fail\n");
		return 1;
	}

	return SUCCESS;
}

/*
@func uint32_t | rtl8366s_setAsicRegBits | Set bits value of a specified register.
@parm uint32_t | reg | Register's address.
@parm uint32_t | bits | Bits mask for setting. 
@parm uint32_t | value | Bits value for setting. Value of bits will be set with mapping mask bit is 1.   
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@rvalue TBLDRV_EINVALIDINPUT | Invalid input parameter. 
@comm
	Set bits of a specified register to value. Both bits and value are be treated as bit-mask.
	
*/
static uint32_t rtl8366s_setAsicRegBits(uint32_t reg, uint32_t bits, uint32_t value)
{
	uint32_t regData;
	uint32_t retVal;
	
	if(bits>= (1<<16)){
		DEBUG_MSG("rtl8366s_setAsicRegBits: bit fial\n");
		return 1;
	}	

	retVal = smi_read(reg, &regData);
	if (retVal != 0){
		DEBUG_MSG("rtl8366s_setAsicRegBits: smi_read fail\n");
		return 1;
	}	

	regData = regData & (~bits);
	regData = regData | (value & bits);

	
	retVal = smi_write(reg, regData);
	if (retVal != 0){
		DEBUG_MSG("rtl8366s_setAsicRegBits: smi_write fail\n");
		return 1;
	}
		
	return SUCCESS;
}

/*
@func uint32_t | rtl8366s_setAsicReg | Set content of asic register.
@parm uint32_t | reg | Register's address.
@parm uint32_t | value | Value setting to register.
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@comm
	The value will be set to ASIC mapping address only and it is always return SUCCESS while setting un-mapping address registers.
	
*/
static uint32_t rtl8366s_setAsicReg(uint32_t reg, uint32_t value)
{
    switch_reg_write(reg, value);
    return SUCCESS;
}

/*
@func uint32_t | rtl8366s_getAsicPHYReg | Set PHY registers .
@parm uint32_t | phyNo | PHY number (0~4).
@parm uint32_t | page | PHY page (0~7).
@parm uint32_t | addr | PHY address (0~32).
@parm uint32_t* | data | Read data.
@rvalue SUCCESS | 
@rvalue FAILED | invalid parameter
@comm
 */
uint32_t rtl8366s_getAsicPHYRegs( uint32_t phyNo, uint32_t page, uint32_t addr, uint32_t *data )
{
	uint32_t retVal,phySmiAddr;	
	
	if(phyNo > RTL8366S_PHY_NO_MAX){
		DEBUG_MSG("rtl8366s_getAsicPHYRegs: phyNo fail\n");
		return FAILED;
	}	

	if(page > RTL8366S_PHY_PAGE_MAX){
		DEBUG_MSG("rtl8366s_getAsicPHYRegs: page fail\n");
		return FAILED;
	}	

	if(addr > RTL8366S_PHY_ADDR_MAX){
		DEBUG_MSG("rtl8366s_getAsicPHYRegs: addr fail\n");
		return FAILED;
	}	
	//DEBUG_MSG("rtl8366s_getAsicPHYRegs: phyNo=%x,page=%x ,addr=%x\n",phyNo,page,addr);
	retVal = rtl8366s_setAsicReg(RTL8366S_PHY_ACCESS_CTRL_REG, RTL8366S_PHY_CTRL_READ);
	if (retVal !=  SUCCESS) {
		DEBUG_MSG("rtl8366s_getAsicPHYRegs: rtl8366s_setAsicReg cma fail\n");
		return retVal;
	}	

	phySmiAddr = 0x8000 | (1<<(phyNo +RTL8366S_PHY_NO_OFFSET)) | 
			//(addr &RTL8366S_PHY_REG_MASK);
			((page <<RTL8366S_PHY_PAGE_OFFSET)&RTL8366S_PHY_PAGE_MASK) | (addr &RTL8366S_PHY_REG_MASK);
	
	retVal = rtl8366s_setAsicReg(phySmiAddr, 0);
	if (retVal !=  SUCCESS) {
		DEBUG_MSG("rtl8366s_getAsicPHYRegs: rtl8366s_setAsicReg addr fail\n");
		return retVal;
	}	
	
	retVal = rtl8366s_getAsicReg(RTL8366S_PHY_ACCESS_DATA_REG,data);
	if(retVal !=  SUCCESS){
		DEBUG_MSG("rtl8366s_getAsicPHYRegs: rtl8366s_getAsicReg fail\n");
		return retVal;
	}	

	return SUCCESS;	
}

/*
@func uint32_t | rtl8366s_setAsicPHYReg | Set PHY registers .
@parm uint32_t | phyNo | PHY number (0~4).
@parm uint32_t | page | PHY page (0~7).
@parm uint32_t | addr | PHY address (0~32).
@parm uint32_t | data | Writing data.
@rvalue SUCCESS | 
@rvalue FAILED | invalid parameter
@comm
 */
uint32_t rtl8366s_setAsicPHYRegs( uint32_t phyNo, uint32_t page, uint32_t addr, uint32_t data )
{
	uint32_t retVal,phySmiAddr;
		
	if(phyNo > RTL8366S_PHY_NO_MAX){
		DEBUG_MSG("rtl8366s_setAsicPHYRegs: phyNo fail\n");
		return FAILED;
	}	

	if(page > RTL8366S_PHY_PAGE_MAX){
		DEBUG_MSG("rtl8366s_setAsicPHYRegs: page fail\n");
		return FAILED;
	}	

	if(addr > RTL8366S_PHY_ADDR_MAX){
		DEBUG_MSG("rtl8366s_setAsicPHYRegs: addr fail\n");
		return FAILED;
	}	

	retVal = rtl8366s_setAsicReg(RTL8366S_PHY_ACCESS_CTRL_REG, RTL8366S_PHY_CTRL_WRITE);
	if (retVal !=  SUCCESS) {
		DEBUG_MSG("rtl8366s_setAsicPHYRegs: rtl8366s_setAsicReg cmd fail\n");
		return retVal;
	}	

	phySmiAddr = 0x8000 | (1<<(phyNo +RTL8366S_PHY_NO_OFFSET)) | 
			//(addr &RTL8366S_PHY_REG_MASK);
			((page <<RTL8366S_PHY_PAGE_OFFSET)&RTL8366S_PHY_PAGE_MASK) | (addr &RTL8366S_PHY_REG_MASK);
	
	retVal = rtl8366s_setAsicReg(phySmiAddr, data);
	if (retVal !=  SUCCESS) {
		DEBUG_MSG("rtl8366s_setAsicPHYRegs: rtl8366s_setAsicReg addr fail\n");
		return retVal;
	}	

	return SUCCESS;	
}

/*
@func uint32_t | rtl8366s_getEthernetPHY | Get PHY ability through PHY registers.
@parm uint32_t | phy | PHY number (0~4).
@parm phyAbility_t* | ability | Ability structure
@rvalue SUCCESS | Success.
@rvalue FAILED | Failure. 
@comm
	Get the capablity of specified PHY.
*/
uint32_t rtl8366s_getEthernetPHY(uint32_t phy, phyAbility_t* ability)
{
	uint32_t phyData0;
	uint32_t phyData4;
	uint32_t phyData9;	

	if(phy > RTL8366S_PHY_NO_MAX){
		DEBUG_MSG("rtl8366s_getEthernetPHY: phy fail\n");
		return FAILED;
	}	

	/*Control register setting and restart auto*/
	if(SUCCESS != rtl8366s_getAsicPHYRegs(phy,0,MII_CONTROL_REG,&phyData0)){
		DEBUG_MSG("rtl8366s_getEthernetPHY: ctrl rtl8366s_getAsicPHYRegs fail\n");
		return FAILED;
	}	

	/*Auto-Negotiation control register setting*/
	if(SUCCESS != rtl8366s_getAsicPHYRegs(phy,0,MII_LOCAL_CAP,&phyData4)){
		DEBUG_MSG("rtl8366s_getEthernetPHY: auto rtl8366s_getAsicPHYRegs fail\n");
		return FAILED;
	}	

	/*1000 BASE-T control register setting*/
	if(SUCCESS != rtl8366s_getAsicPHYRegs(phy,0,MII_GIGA_CONTROL,&phyData9)){
		DEBUG_MSG("rtl8366s_getEthernetPHY: 1000 rtl8366s_getAsicPHYRegs fail\n");
		return FAILED;
	}	

	if(phyData9 & (1<<9))
		ability->Full_1000 = 1;
	else
		ability->Full_1000 = 0;

	if(phyData4 & (1<<11))
		ability->AsyFC = 1;
	else
		ability->AsyFC = 0;

	if(phyData4 & (1<<10))
		ability->FC = 1;
	else
		ability->FC = 0;
	

	if(phyData4 & (1<<8))
		ability->Full_100= 1;
	else
		ability->Full_100= 0;
	
	if(phyData4 & (1<<7))
		ability->Half_100= 1;
	else
		ability->Half_100= 0;

	if(phyData4 & (1<<6))
		ability->Full_10= 1;
	else
		ability->Full_10= 0;
	
	if(phyData4 & (1<<5))
		ability->Half_10= 1;
	else
		ability->Half_10= 0;


	if(phyData0 & (1<<12))
		ability->AutoNegotiation= 1;
	else
		ability->AutoNegotiation= 0;

	return SUCCESS;
}

/*
@func uint32_t | rtl8366s_setEthernetPHY | Set ethernet PHY registers for desired ability.
@parm uint32_t | phy | PHY number (0~4).
@parm phyAbility_t | ability | Ability structure
@rvalue SUCCESS | Success.
@rvalue FAILED | Failure. 
@comm
	If Full_1000 bit is set to 1, the AutoNegotiation,Full_100 and Full_10 will be automatic set to 1. While both AutoNegotiation and Full_1000 are set to
	0, the PHY speed and duplex selection will be set as following 100F > 100H > 10F > 10H priority sequence.
*/
uint32_t rtl8366s_setEthernetPHY(uint32_t phy, phyAbility_t ability)
{
	uint32_t phyData;	
	uint32_t phyEnMsk0;
	uint32_t phyEnMsk4;
	uint32_t phyEnMsk9;
	
	//DEBUG_MSG("rtl8366s_setEthernetPHY:\n");
	
	if(phy > RTL8366S_PHY_NO_MAX){
		DEBUG_MSG("rtl8366s_setEthernetPHY: phy fail\n");
		return FAILED;
	}	

	phyEnMsk0 = 0;
	phyEnMsk4 = 0;
	phyEnMsk9 = 0;


	if(ability.Half_10 == 1)
	{
		//DEBUG_MSG("rtl8366s_setEthernetPHY:Half_10\n");
		/*10BASE-TX half duplex capable in reg 4.5*/
		phyEnMsk4 = phyEnMsk4 | (1<<5);

		/*Speed selection [1:0] */
		/* 11=Reserved*/
		/* 10= 1000Mpbs*/
		/* 01= 100Mpbs*/
		/* 00= 10Mpbs*/		
		phyEnMsk0 = phyEnMsk0 & (~(1<<6));
		phyEnMsk0 = phyEnMsk0 & (~(1<<13));
	}

	if(ability.Full_10 == 1)
	{
		//DEBUG_MSG("rtl8366s_setEthernetPHY:Full_10\n");
		/*10BASE-TX full duplex capable in reg 4.6*/
		phyEnMsk4 = phyEnMsk4 | (1<<6);
		/*Speed selection [1:0] */
		/* 11=Reserved*/
		/* 10= 1000Mpbs*/
		/* 01= 100Mpbs*/
		/* 00= 10Mpbs*/		
		phyEnMsk0 = phyEnMsk0 & (~(1<<6));
		phyEnMsk0 = phyEnMsk0 & (~(1<<13));

		/*Full duplex mode in reg 0.8*/
		phyEnMsk0 = phyEnMsk0 | (1<<8);
		
	}

	if(ability.Half_100 == 1)
	{
		//DEBUG_MSG("rtl8366s_setEthernetPHY:Half_100\n");
		/*100BASE-TX half duplex capable in reg 4.7*/
		phyEnMsk4 = phyEnMsk4 | (1<<7);
		/*Speed selection [1:0] */
		/* 11=Reserved*/
		/* 10= 1000Mpbs*/
		/* 01= 100Mpbs*/
		/* 00= 10Mpbs*/		
		phyEnMsk0 = phyEnMsk0 & (~(1<<6));
		phyEnMsk0 = phyEnMsk0 | (1<<13);
	}


	if(ability.Full_100 == 1)
	{
		//DEBUG_MSG("rtl8366s_setEthernetPHY:Full_100\n");
		/*100BASE-TX full duplex capable in reg 4.8*/
		phyEnMsk4 = phyEnMsk4 | (1<<8);
		/*Speed selection [1:0] */
		/* 11=Reserved*/
		/* 10= 1000Mpbs*/
		/* 01= 100Mpbs*/
		/* 00= 10Mpbs*/		
		phyEnMsk0 = phyEnMsk0 & (~(1<<6));
		phyEnMsk0 = phyEnMsk0 | (1<<13);
		/*Full duplex mode in reg 0.8*/
		phyEnMsk0 = phyEnMsk0 | (1<<8);
	}
	
	
	if(ability.Full_1000 == 1)
	{
		//DEBUG_MSG("rtl8366s_setEthernetPHY:Full_1000\n");
		/*1000 BASE-T FULL duplex capable setting in reg 9.9*/
		phyEnMsk9 = phyEnMsk9 | (1<<9);
		/*100BASE-TX full duplex capable in reg 4.8*/
		phyEnMsk4 = phyEnMsk4 | (1<<8);
		/*10BASE-TX full duplex capable in reg 4.6*/
		phyEnMsk4 = phyEnMsk4 | (1<<6);

		/*Speed selection [1:0] */
		/* 11=Reserved*/
		/* 10= 1000Mpbs*/
		/* 01= 100Mpbs*/
		/* 00= 10Mpbs*/		
		phyEnMsk0 = phyEnMsk0 | (1<<6);
		phyEnMsk0 = phyEnMsk0 & (~(1<<13));
	

		/*Force Auto-Negotiation setting in reg 0.12*/
		ability.AutoNegotiation = 1;

	}
	
	if(ability.AutoNegotiation == 1)
	{
		//DEBUG_MSG("rtl8366s_setEthernetPHY:AutoNegotiation\n");
		/*Auto-Negotiation setting in reg 0.12*/
		phyEnMsk0 = phyEnMsk0 | (1<<12);
	}

	if(ability.AsyFC == 1)
	{
		//DEBUG_MSG("rtl8366s_setEthernetPHY:AsyFC\n");
		/*Asymetric flow control in reg 4.11*/
		phyEnMsk4 = phyEnMsk4 | (1<<11);
	}
	if(ability.FC == 1)
	{
		//DEBUG_MSG("rtl8366s_setEthernetPHY:FC\n");
		/*Flow control in reg 4.10*/
		phyEnMsk4 = phyEnMsk4 | (1<<10);
	}

	
	/*1000 BASE-T control register setting*/
	if(SUCCESS != rtl8366s_getAsicPHYRegs(phy,0,MII_GIGA_CONTROL,&phyData)){
		DEBUG_MSG("rtl8366s_setEthernetPHY: 1000 rtl8366s_getAsicPHYRegs fail\n");
		return FAILED;
	}	

	phyData = (phyData & (~0x0200)) | phyEnMsk9 ;
		
	if(SUCCESS != rtl8366s_setAsicPHYRegs(phy,0,MII_GIGA_CONTROL,phyData)){
		DEBUG_MSG("rtl8366s_setEthernetPHY: 1000 rtl8366s_setAsicPHYRegs fail\n");
		return FAILED;
	}	

	/*Auto-Negotiation control register setting*/
	if(SUCCESS != rtl8366s_getAsicPHYRegs(phy,0,MII_LOCAL_CAP,&phyData)){
		DEBUG_MSG("rtl8366s_setEthernetPHY: auto rtl8366s_getAsicPHYRegs fail\n");
		return FAILED;
	}	

	phyData = (phyData & (~0x0DE0)) | phyEnMsk4;
		
	if(SUCCESS != rtl8366s_setAsicPHYRegs(phy,0,MII_LOCAL_CAP,phyData)){
		DEBUG_MSG("rtl8366s_setEthernetPHY: auto rtl8366s_setAsicPHYRegs fail\n");
		return FAILED;
	}	


	/*Control register setting and restart auto*/
	if(SUCCESS != rtl8366s_getAsicPHYRegs(phy,0,MII_CONTROL_REG,&phyData)){
		DEBUG_MSG("rtl8366s_setEthernetPHY: ctrl rtl8366s_getAsicPHYRegs fail\n");
		return FAILED;
	}	


	phyData = (phyData & (~0x3140)) | phyEnMsk0;
	/*If have auto-negotiation capable, then restart auto negotiation*/
	if(ability.AutoNegotiation ==1)
	{
		DEBUG_MSG("rtl8366s_setEthernetPHY:AutoNegotiation restart\n");
		phyData = phyData | (1 << 9);
	}
	
	if(SUCCESS != rtl8366s_setAsicPHYRegs(phy,0,MII_CONTROL_REG,phyData)){
		DEBUG_MSG("rtl8366s_setEthernetPHY: ctrl rtl8366s_setAsicPHYRegs fail\n");
		return FAILED;
	}	
	
	return SUCCESS;
}

#ifdef GET_INFO
/*
@func uint32_t | rtl8366s_getAsicPortLinkState | Get a specific port's link state.
@parm enum PORTID | port | Physical Port number.
@parm enum PORTLINKSPEED  * | speed | current link speed, 
	SPD_10M: 10Mbps,0 
	SPD_100M: 100Mbps,1
	SPD_1000M: 1000Mbps.2
@parm enum PORTLINKDUPLEXMODE * | duplex | current duplex status,
	FULL_DUPLEX: full duplex,1 
	HALF_DUPLEX: half duplex.0
@parm uint32_t  * | link | Link status, 1: link up, 0: link down.
@parm uint32_t  * | rxPause | The pause frame response ability, 1: active, 0: inactive.
@parm uint32_t  * | txPause | The pause frame transmit ability, 1: active, 0: inactive.
@parm uint32_t  * | nWay | N-way function, 1: enable, 0: disable.
@rvalue SUCCESS | Success.
@rvalue ERRNO_INVALIDINPUT | Invalid input parameter.
@comm
	The API can get a specific port's link state information including link up/down, 
	link speed, auto negotiation enabled/disabled, Tx in active/inactive and Rx in 
	active/inactive. 
*/
uint32_t rtl8366s_getAsicPortLinkState(enum PORTID port, enum PORTLINKSPEED *speed, enum PORTLINKDUPLEXMODE *duplex,uint32_t *link, uint32_t *txPause,uint32_t *rxPause,uint32_t *nWay)
{
	uint32_t retVal;
	uint32_t RegData;
	
	if(port <PORT0 || port >=PORT_MAX){
		DEBUG_MSG("rtl8366s_getAsicPortLinkState: port fail\n");
		return FAILED;
	}	

	retVal = rtl8366s_getAsicReg(RTL8366S_PORT_LINK_STATUS_BASE + (port >>1),&RegData);
	if(SUCCESS != retVal){
		DEBUG_MSG("rtl8366s_getAsicPortLinkState: rtl8366s_getAsicReg fail\n");	
		return FAILED;
	}	
	
	if(port&0x1)
	{
		RegData = RegData >> 8;
	}

	*speed = (RegData & RTL8366S_PORT_STATUS_SPEED_MSK)>>RTL8366S_PORT_STATUS_SPEED_BIT;
	DEBUG_MSG("port%d: *speed=%d\n",port,*speed);
	*duplex = (RegData & RTL8366S_PORT_STATUS_DUPLEX_MSK)>>RTL8366S_PORT_STATUS_DUPLEX_BIT;
	DEBUG_MSG("*duplex=%d\n",*duplex);
	*link = (RegData & RTL8366S_PORT_STATUS_LINK_MSK)>>RTL8366S_PORT_STATUS_LINK_BIT;
	DEBUG_MSG("*link=%d\n",*link);
	*txPause = (RegData & RTL8366S_PORT_STATUS_TXPAUSE_MSK)>>RTL8366S_PORT_STATUS_TXPAUSE_BIT;
	DEBUG_MSG("*txPause=%d\n",*txPause);
	*rxPause = (RegData & RTL8366S_PORT_STATUS_RXPAUSE_MSK)>>RTL8366S_PORT_STATUS_RXPAUSE_BIT;
	DEBUG_MSG("*rxPause=%d\n",*rxPause);
	*nWay = (RegData & RTL8366S_PORT_STATUS_AN_MSK)>>RTL8366S_PORT_STATUS_AN_BIT;
	DEBUG_MSG("*nWay=%d\n",*nWay);
	return SUCCESS;
}
#endif

/*
@func uint32_t | rtl8366s_setAsicMacForceLink | Set mac force linking configuration.
@parm enum PORTID | port | Port/MAC number (0~5).
@parm enum MACLINKMODE | force | Mac link mode 1:force mode 0:normal
@parm enum PORTLINKSPEED | speed | Speed of the port 0b00-10M, 0b01-100M,0b10-1000M, 0b11 reserved.
@parm enum PORTLINKDUPLEXMODE | duplex | Deuplex mode 0b0-half duplex 0b1-full duplex.
@parm uint32_t | link | Link status 0b0-link down b1-link up.
@parm uint32_t | txPause | Pause frame transmit ability of the port 0b0-inactive 0b1-active.
@parm uint32_t | rxPause | Pause frame response ability of the port 0b0-inactive 0b1-active.
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@rvalue FAILED | Invalid parameter.
@comm
  	This API can set Port/MAC force mode properties. 
 */
uint32_t rtl8366s_setAsicMacForceLink(enum PORTID port,enum MACLINKMODE force,enum PORTLINKSPEED speed,enum PORTLINKDUPLEXMODE duplex,uint32_t link,uint32_t txPause,uint32_t rxPause)
{
	uint32_t retVal;
	uint32_t macData;
	uint32_t regBits;
	uint32_t regAddr;
	uint32_t regData;
	
	/* Invalid input parameter */
	if(port >=PORT_MAX){
		DEBUG_MSG("rtl8366s_setAsicMacForceLink: port fail\n");
		return FAILED;
	}	

	/*not force mode*/
	if(MAC_NORMAL == force)
	{
		retVal = rtl8366s_getAsicReg(RTL8366S_MAC_FORCE_CTRL0_REG,&regData);
		if (retVal !=  SUCCESS){ 
			DEBUG_MSG("rtl8366s_setAsicMacForceLink: rtl8366s_getAsicReg fail\n");	
			return retVal;
		}	
		
		regData = regData & (~(1<<port));

		retVal = rtl8366s_setAsicReg(RTL8366S_MAC_FORCE_CTRL1_REG,regData);
		if (retVal !=  SUCCESS){ 
			DEBUG_MSG("rtl8366s_setAsicMacForceLink: rtl8366s_setAsicReg fail\n");	
			return retVal;
		}	

		return SUCCESS;
	}


	if(speed > SPD_1000M){
		DEBUG_MSG("rtl8366s_setAsicMacForceLink: spped fail\n");	
		return FAILED;
	}	

	/*prepare force status first*/
	macData = speed;

	if(duplex)
	{
		macData = macData | (duplex<<2);
	}

	if(link)
	{
		macData = macData | (link<<4);
	}

	if(txPause)
	{
		macData = macData | (txPause<<5);
	}
	
	if(rxPause)
	{
		macData = macData | (rxPause<<6);
	}
	
	regBits = 0xFF << (8*(port&0x01));
	macData = macData <<(8*(port&0x01));
	
	/* Set register value */
	regAddr = RTL8366S_PORT_ABILITY_BASE + (port>>1);


	retVal= rtl8366s_setAsicRegBits(regAddr,regBits,macData);
	if (retVal !=  SUCCESS) {
		DEBUG_MSG("rtl8366s_setAsicMacForceLink: rtl8366s_setAsicRegBits fail\n");	
		return retVal;
	}	


	/* Get register value */
	retVal = rtl8366s_getAsicReg(RTL8366S_MAC_FORCE_CTRL0_REG,&regData);
	if (retVal !=  SUCCESS) {
		DEBUG_MSG("rtl8366s_setAsicMacForceLink: rtl8366s_getAsicReg fail\n");
		return retVal;
	}	

	regData = regData | (1<<port);

	retVal = rtl8366s_setAsicReg(RTL8366S_MAC_FORCE_CTRL1_REG,regData);
	if (retVal !=  SUCCESS) {
		DEBUG_MSG("rtl8366s_setAsicMacForceLink: rtl8366s_setAsicRegBits fail\n");	
		return retVal;
	}	

	return SUCCESS;
}
	
/*
@func uint32_t | rtl8366s_setMac5ForceLink | Set Port/MAC 5 force linking configuration.
@parm enum PORTLINKSPEED | speed | Speed of the port 0b00-10M, 0b01-100M,0b10-1000M, 0b11 reserved.
@parm enum PORTLINKDUPLEXMODE | duplex | Deuplex mode 0b0-half duplex 0b1-full duplex.
@parm uint32_t | link | Link status 0b0-link down b1-link up.
@parm uint32_t | txPause | Pause frame transmit ability of the port 0b0-inactive 0b1-active.
@parm uint32_t | rxPause | Pause frame response ability of the port 0b0-inactive 0b1-active.
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@rvalue FAILED | Invalid parameter.
@comm
  	This API can set Port/MAC 5 properties in force mode. 
 */
uint32_t rtl8366s_setMac5ForceLink(enum PORTLINKSPEED speed,enum PORTLINKDUPLEXMODE duplex,uint32_t link,uint32_t txPause,uint32_t rxPause)
{
	if(speed > SPD_1000M){
		DEBUG_MSG("rtl8366s_setMac5ForceLink: speed fail\n");	
		return FAILED;
	}	

	if(SUCCESS != rtl8366s_setAsicMacForceLink(PORT5,1,speed,duplex,link,txPause,rxPause)){
		DEBUG_MSG("rtl8366s_setAsicMacForceLink fail\n");	
		return FAILED;
	}	

	return SUCCESS;
}	

#ifdef GET_INFO
/*
@func uint32_t | rtl8366s_getMac5ForceLink | Set Port/MAC 5 force linking configuration.
@parm enum PORTLINKSPEED* | speed | Speed of the port 0b00-10M, 0b01-100M,0b10-1000M, 0b11 reserved.
@parm enum PORTLINKDUPLEXMODE* | duplex | Deuplex mode 0b0-half duplex 0b1-full duplex.
@parm uint32_t* | link | Link status 0b0-link down b1-link up.
@parm uint32_t* | txPause | Pause frame transmit ability of the port 0b0-inactive 0b1-active.
@parm uint32_t* | rxPause | Pause frame response ability of the port 0b0-inactive 0b1-active.
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@rvalue FAILED | Invalid parameter.
@comm
  	This API can set Port/MAC 5 properties in force mode. 
 */
uint32_t rtl8366s_getMac5ForceLink(enum PORTLINKSPEED* speed,enum PORTLINKDUPLEXMODE* duplex,uint32_t* link,uint32_t* txPause,uint32_t* rxPause)
{
	uint32_t autoNegotiation;
	if(SUCCESS != rtl8366s_getAsicPortLinkState(PORT5,speed,duplex,link,txPause,rxPause,&autoNegotiation)){
		DEBUG_MSG("rtl8366s_getAsicPortLinkState fail\n");
		return FAILED;
	}		

	return SUCCESS;
}
#endif
/*
@func uint32_t | rtl8366s_getPHYLinkStatus | Get ethernet PHY linking status
@parm uint32_t | phy | PHY number (0~4).
@parm uint32_t* | linkStatus | PHY link status 1:link up 0:link down
@rvalue SUCCESS | Success.
@rvalue FAILED | Failure. 
@comm
	Output link status of bit 2 in PHY register 1. API will return status is link up under both auto negotiation complete and link status are set to 1.  
*/
uint32_t rtl8366s_getPHYLinkStatus(uint32_t phy, uint32_t *linkStatus)
{
	uint32_t phyData;

	if(phy > RTL8366S_PHY_NO_MAX){
		DEBUG_MSG("rtl8366s_getPHYLinkStatus: phy fail\n");
		return FAILED;
	}	

	/*Get PHY status register*/
	if(SUCCESS != rtl8366s_getAsicPHYRegs(phy,0,MII_STATUS_REG,&phyData)){
		DEBUG_MSG("rtl8366s_getPHYLinkStatus: rtl8366s_getAsicPHYRegs fail\n");
		return FAILED;
	}	

	/*check link status*/
	if(phyData & (1<<2))
	{
		*linkStatus = 1;
	}
	else
	{
		*linkStatus = 0;	
	}

	return SUCCESS;
}

#ifdef CPU_PORT//*********************************************
/*
@func uint32_t | rtl8366s_setAsicCpuPortMask| Configure cpu port
@parm enum PORTID | port | Physical port number.
@parm uint32_t | enabled | 0:disable 1:enable
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@rvalue ERRNO_INVALIDINPUT | Invalid Port Number.
@rvalue ERRNO_INVALIDINPUT | Invalid input parameter.
@comm
	The API can specify cpu port. All the frames send to cpu port will be
	inserted proprietary cpu tag 0x8899 if NOT disable insert CPU tag function.

*/
uint32_t rtl8366s_setAsicCpuPortMask(enum PORTID port, uint32_t enabled)
{
	uint32_t retVal;

	if(port >= PORT_MAX){
		DEBUG_MSG("rtl8366s_setAsicCpuPortMask: phy fail\n");
		return FAILED;
	}	

	retVal = rtl8366s_setAsicRegBit(RTL8366S_CPU_CTRL_REG,port,enabled);		

	return retVal;	
}

#ifdef GET_INFO
/*
@func uint32_t | rtl8366s_getAsicCpuPortMask| Get cpu port
@parm enum PORTID | port | Physical port number.
@parm uint32_t* | enabled | 0:disable 1:enable
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@rvalue ERRNO_INVALIDINPUT | Invalid Port Number.
@rvalue ERRNO_INVALIDINPUT | Invalid input parameter.
@comm
	The API can check if the specified port is a CPU port.

*/
uint32_t rtl8366s_getAsicCpuPortMask(enum PORTID port, uint32_t* enabled)
{
	uint32_t regData;
	uint32_t retVal;

	if(port >= PORT_MAX){
		DEBUG_MSG("rtl8366s_getAsicCpuPortMask: phy fail\n");
		return FAILED;
	}	

	retVal = rtl8366s_getAsicReg(RTL8366S_CPU_CTRL_REG, &regData);
	if(retVal !=  SUCCESS){
		DEBUG_MSG("rtl8366s_getAsicCpuPortMask: rtl8366s_getAsicReg fail\n");
		return retVal;
	}	

	if(regData & (1<<port))
		*enabled = 1;
	else
		*enabled = 0;

	return SUCCESS;
}
#endif
/*
@func uint32_t | rtl8366s_setAsicCpuDropUnda | Set CPU port drop unknown DA frame function
@parm uint32_t | enable | 0: disable, 1: enable.
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@rvalue ERRNO_INVALIDINPUT | Invalid input parameter.
@comm
	Enable the function to NOT FORWARD unknown DA frame to CPU port	or
	disable the function to FORWARD unknown DA frame to CPU port.	
	It can reduce CPU loading by not forwarding unknown DA frames to CPU port. 
	
*/
uint32_t rtl8366s_setAsicCpuDropUnda(uint32_t enable)
{
	uint32_t retVal;

	retVal = rtl8366s_setAsicRegBit(RTL8366S_CPU_CTRL_REG,RTL8366S_CPU_DRP_BIT,enable);

	return retVal;
}

#ifdef GET_INFO
/*
@func uint32_t | rtl8366s_getAsicCpuDropUnda | Get setting of CPU port drop unknown DA frame function
@parm uint32_t* | enable | 0: disable, 1: enable.
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@rvalue ERRNO_INVALIDINPUT | Invalid input parameter.
@comm
	The API can get the setting of CPU port drop unknown DA frame function.
	
*/
uint32_t rtl8366s_getAsicCpuDropUnda(uint32_t* enable)
{
	uint32_t regData;
	uint32_t retVal;

	retVal = rtl8366s_getAsicReg(RTL8366S_CPU_CTRL_REG, &regData);
	if(retVal !=  SUCCESS){
		DEBUG_MSG("rtl8366s_getAsicCpuDropUnda: rtl8366s_getAsicReg fail\n");
		return retVal;
	}
	
	if(regData & RTL8366S_CPU_DRP_MSK)
		*enable = 1;
	else
		*enable = 0;
	
	return SUCCESS;
}
#endif
/*
@func uint32_t | rtl8366s_setAsicCpuDisableInsTag | Set CPU port DISABLE insert tag function
@parm uint32_t | enable | 0: disable, 1: enable. 
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@rvalue ERRNO_INVALIDINPUT | Invalid input parameter.
@comm
	Enable the function to NOT insert proprietary CPU tag (Length/Type 0x8899) ahead vlan tag
	to the frame that transmitted to CPU port or disable the function to insert proprietary CPU tag.
	
*/
uint32_t rtl8366s_setAsicCpuDisableInsTag(uint32_t enable)
{
	uint32_t retVal;

	retVal = rtl8366s_setAsicRegBit(RTL8366S_CPU_CTRL_REG,RTL8366S_CPU_INSTAG_BIT,enable);

	return retVal;
}

#ifdef GET_INFO
/*
@func uint32_t | rtl8366s_getAsicCpuDisableInsTag | Get setting of CPU port DISABLE insert tag function
@parm uint32_t* | enable | 0: disable, 1: enable. 
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@rvalue ERRNO_INVALIDINPUT | Invalid input parameter.
@comm
	The API can get the setting of CPU port DISABLE insert tag function.
	
*/
uint32_t rtl8366s_getAsicCpuDisableInsTag(uint32_t* enable)
{
	uint32_t regData;
	uint32_t retVal;

	retVal = rtl8366s_getAsicReg(RTL8366S_CPU_CTRL_REG, &regData);
	if(retVal !=  SUCCESS){
		DEBUG_MSG("rtl8366s_getAsicCpuDisableInsTag: rtl8366s_getAsicReg fail\n");
		return retVal;
	}	

	if(regData & RTL8366S_CPU_INSTAG_MSK)
		*enable = 1;
	else
		*enable = 0;
	
	return SUCCESS;
}
#endif
/*
@func uint32_t | rtl8366s_setCPUPort | Set CPU port with/without inserting CPU tag.
@parm enum PORTID | port | Port number to be set as CPU port (0~5).
@parm uint32_t | noTag | NOT insert Realtek proprietary tag (ethernet length/type 0x8899) to frame 1:not insert 0:insert.
@parm uint32_t | dropUnda | NOT forward unknown DMAC frame to CPU port 1:drop 0:forward.
@rvalue ERRNO_API_INVALIDPARAM | invalid input parameters.
@rvalue SUCCESS | Success.
@rvalue FAILED | Failure.
@comm
	The API can set CPU port and enable/disable inserting proprietary CPU tag (Length/Type 0x8899)
	to the frame that transmitting to CPU port. It also can enable/disable forwarding unknown
	destination MAC address frames to CPU port. User can reduce CPU loading by not forwarding
	unknown DA frames to CPU port.
*/
uint32_t rtl8366s_setCPUPort(enum PORTID port, uint32_t noTag, uint32_t dropUnda)
{
	uint32_t i;
	
	if(port >= PORT_MAX){
		DEBUG_MSG("rtl8366s_setCPUPort: phy fail\n");
		return FAILED;
	}	

	/* clean CPU port first */
	for(i=0; i<PORT_MAX; i++)
	{
		if(rtl8366s_setAsicCpuPortMask(i, FALSE) != SUCCESS){
			DEBUG_MSG("rtl8366s_setCPUPort: rtl8366s_setAsicCpuPortMask fail\n");
			return FAILED;	
		}	
	}

	if(rtl8366s_setAsicCpuPortMask(port, TRUE) != SUCCESS){
		DEBUG_MSG("rtl8366s_setCPUPort: rtl8366s_setAsicCpuPortMask fail\n");
		return FAILED;		
	}	

	if(rtl8366s_setAsicCpuDisableInsTag(noTag) != SUCCESS){
		DEBUG_MSG("rtl8366s_setCPUPort: rtl8366s_setAsicCpuDisableInsTag fail\n");
		return FAILED;	
	}	

	if(rtl8366s_setAsicCpuDropUnda(dropUnda) != SUCCESS){
		DEBUG_MSG("rtl8366s_setCPUPort: rtl8366s_setAsicCpuDropUnda fail\n");
		return FAILED;	
	}	

	return SUCCESS;
}

#ifdef GET_INFO
/*
@func uint32_t | rtl8366s_getCPUPort | Get CPU port and its setting.
@parm enum PORTID* | port | returned CPU port (0~5).
@parm uint32_t* | noTag | returned CPU port with insert tag ability 1:not insert 0:insert.
@parm uint32_t* | dropUnda | returned CPU port with forward unknown DMAC frame ability 1:drop 0:forward.
@rvalue ERRNO_API_INVALIDPARAM | invalid input parameters.
@rvalue ERRNO_API_CPUNOTSET | No CPU port speicifed.
@rvalue SUCCESS | Success.
@rvalue FAILED | Failure.
@comm
	The API can get configured CPU port and its setting.
	Return ERRNO_API_CPUNOTSET if CPU port is not speicifed.
*/
uint32_t rtl8366s_getCPUPort(enum PORTID *port, uint32_t *noTag, uint32_t *dropUnda)
{
	uint32_t i;
	uint32_t enable = FALSE;	
	
	if(port == NULL || noTag == NULL || dropUnda == NULL){
		DEBUG_MSG("rtl8366s_getCPUPort: NULL fail\n");
		return FAILED;
	}	

	/* get configured CPU port */
	for(i=0; i<PORT_MAX; i++)
	{
		if(rtl8366s_getAsicCpuPortMask(i, &enable) != SUCCESS){
			DEBUG_MSG("rtl8366s_getCPUPort: rtl8366s_getAsicCpuPortMask fail\n");
			return FAILED;	
		}	

		if(enable == TRUE)
		{
			*port = i;
			if(rtl8366s_getAsicCpuDisableInsTag(noTag) != SUCCESS){
				DEBUG_MSG("rtl8366s_getCPUPort: rtl8366s_getAsicCpuDisableInsTag fail\n");
				return FAILED;				
			}	
			if(rtl8366s_getAsicCpuDropUnda(dropUnda) != SUCCESS){
				DEBUG_MSG("rtl8366s_getCPUPort: rtl8366s_getAsicCpuDropUnda fail\n");
				return FAILED;				
			}	
			
			DEBUG_MSG("CPUport=%d,noTag=%d,dropUnda=%d\n",*port,*noTag,*dropUnda);
			
			return SUCCESS;
		}
	}

	return FAILED;
}
#endif
#endif//CPU_PORT//*********************************************

#ifdef VLAN_SET//*********************************************
/*
@func uint32_t | rtl8366s_setAsicVlan | Set VLAN enable function.
@parm uint32_t | enabled | VLAN enable function usage 1: enabled, 0: disabled. 
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@rvalue ERRNO_INVALIDINPUT | Invalid input parameter.
@comm
	ASIC will parse frame type/length if VLAN function usage is enabled. In 802.1q spec. ,the Type/Length of C-tag is 0x8100. System will decide
	802.1q VID of received frame from C-tag, Protocol-and-Port based VLAN and Port based VLAN. This setting will impact on VLAN ingress, VLAN egress
	and 802.1q priority selection.
	
*/
uint32_t rtl8366s_setAsicVlan(uint32_t enabled)
{
	uint32_t retVal;

	retVal = rtl8366s_setAsicRegBit(RTL8366S_SWITCH_GLOBAL_CTRL_REG,RTL8366S_EN_VLAN_BIT,enabled);
	if(retVal !=  SUCCESS){
		DEBUG_MSG("%s: rtl8366s_setAsicRegBit fail\n",__func__);
		return FAILED;
	}	
	
	return SUCCESS;
}

/*
@func uint32_t | rtl8366s_getAsicVlan | Get VLAN enable function configuration.
@parm uint32_t* | enabled | VLAN enable function usage 1: enabled, 0: disabled. 
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@rvalue ERRNO_INVALIDINPUT | Invalid input parameter.
@comm
	The API can get usage of asic VLAN enable configuration. 
	
*/
uint32_t rtl8366s_getAsicVlan(uint32_t* enabled)
{
	uint32_t retVal;
	uint32_t regData;

	retVal = rtl8366s_getAsicReg(RTL8366S_SWITCH_GLOBAL_CTRL_REG,&regData);	
	if(retVal !=  SUCCESS){
		DEBUG_MSG("%s: rtl8366s_getAsicReg fail\n",__func__);
		return FAILED;
	}		

	regData = regData & (1<<RTL8366S_EN_VLAN_BIT);

	if(regData)
		*enabled = 1;
	else
		*enabled = 0;

	return SUCCESS;	
}

/*
@func uint32_t | rtl8366s_setAsicVlan4kTbUsage | Set 4k VLAN table usage configuration.
@parm uint32_t | enabled | 4k VLAN table usage 1: enabled, 0: disabled. 
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@rvalue ERRNO_INVALIDINPUT | Invalid input parameter.
@comm
	Each VLAN entry contains member port, untag set and FID (support 8 SVL/IVL filtering database) information. While VLAN function of system 
	is enabled and 4k VLAN table is enabled, system will decide each receiving frame's VID. VLAN ingress and VLAN egress function will 
	reference member port of mapped VID entry in 4k table. Without 4k VLAN table usage, there are 16 VLAN memeber configurations to	support
	VLAN enabled reference.
	 
*/
uint32_t rtl8366s_setAsicVlan4kTbUsage(uint32_t enabled)
{
	uint32_t retVal;

	retVal = rtl8366s_setAsicRegBit(RTL8366S_VLAN_TB_CTRL_REG,RTL8366S_VLAN_TB_BIT,enabled);
	if(retVal !=  SUCCESS){
		DEBUG_MSG("%s: rtl8366s_setAsicRegBit fail\n",__func__);
		return FAILED;
	}	
	
	return SUCCESS;
}

/*
@func uint32_t | rtl8366s_getAsicVlan4kTbUsage | Get 4k VLAN table usage configuration.
@parm uint32_t* | enabled | 4k VLAN table usage 1: enabled, 0: disabled. 
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@rvalue ERRNO_INVALIDINPUT | Invalid input parameter.
@comm
	The API can get 4K VLAN table usage.
	
*/
uint32_t rtl8366s_getAsicVlan4kTbUsage(uint32_t* enabled)
{
	uint32_t retVal;
	uint32_t regData;

	retVal = rtl8366s_getAsicReg(RTL8366S_VLAN_TB_CTRL_REG,&regData);
	if(retVal !=  SUCCESS){
		DEBUG_MSG("%s: rtl8366s_getAsicReg fail\n",__func__);
		return FAILED;
	}	

	regData = regData & RTL8366S_VLAN_TB_MSK;

	if(regData)
		*enabled = 1;
	else
		*enabled = 0;

	return SUCCESS;
}

/*
@func uint32_t | rtl8366s_setAsicVlanMemberConfig | Set 16 VLAN member configurations.
@parm uint32_t | index | VLAN member configuration index (0~15).
@parm rtl8366s_vlanconfig* | vlanmemberconf | VLAN member configuration. It contained VID, priority, member set, untag set and FID fields. 
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@rvalue ERRNO_INVALIDINPUT | Invalid input parameter.
@rvalue ERRNO_VLAN_INVALIDFID | Invalid FID (0~7).
@rvalue ERRNO_VLAN_INVALIDPRIORITY | Invalid VLAN priority (0~7).
@rvalue ERRNO_VLAN_INVALIDPORTMSK | Invalid port mask (0x00~0x3F).
@rvalue ERRNO_VLAN_INVALIDVID | Invalid VID parameter (0~4095).
@rvalue ERRNO_VLAN_INVALIDMBRCONFIDX | Invalid VLAN member configuration index (0~15).
@comm
	VLAN ingress and egress will reference these 16 configurations while system VLAN function is enabled without 4k VLAN table usage. Port based
	, Protocol-and-Port based VLAN and 802.1x guest VLAN functions retrieved VLAN information from these 16 member configurations too. Only
	VID will be referenced while 4k VLAN table is enabled. It means that member set, untag set and FID need to be retrieved from 4k mapped VID entry.
	
*/
uint32_t rtl8366s_setAsicVlanMemberConfig(uint32_t index,rtl8366s_vlanconfig *vlanmconf )
{
	uint32_t retVal;
	uint32_t regAddr;
	uint32_t regData;
	uint16_t* tableAddr;
	
	if(index > RTL8366S_VLANMCIDXMAX){
		DEBUG_MSG("%s: RTL8366S_VLANMCIDXMAX fail\n",__func__);
		return FAILED;
	}	

	if(vlanmconf->vid > RTL8366S_VIDMAX){
		DEBUG_MSG("%s: RTL8366S_VIDMAX fail\n",__func__);
		return FAILED;
	}	

	if(vlanmconf->priority> RTL8366S_PRIORITYMAX){
		DEBUG_MSG("%s: RTL8366S_PRIORITYMAX fail\n",__func__);
		return FAILED;
	}	

	if(vlanmconf->member > RTL8366S_PORTMASK){
		DEBUG_MSG("%s: member RTL8366S_PORTMASK fail\n",__func__);
		return FAILED;
	}	

	if(vlanmconf->untag> RTL8366S_PORTMASK){
		DEBUG_MSG("%s: untag RTL8366S_PORTMASK fail\n",__func__);
		return FAILED;
	}	

	if(vlanmconf->fid > RTL8366S_FIDMAX){
		DEBUG_MSG("%s: RTL8366S_FIDMAX fail\n",__func__);
		return FAILED;
	}	

	regAddr = RTL8366S_VLAN_MEMCONF_BASE + (index<<1);

	tableAddr = (uint16_t*)vlanmconf;
	regData = *tableAddr;

	retVal = rtl8366s_setAsicReg(regAddr,regData);
	if(retVal !=  SUCCESS){
		DEBUG_MSG("%s: rtl8366s_setAsicReg fail\n",__func__);
		return FAILED;
	}
	
	regAddr = RTL8366S_VLAN_MEMCONF_BASE + 1 + (index<<1);

	tableAddr ++;
	regData = *tableAddr;

	retVal = rtl8366s_setAsicReg(regAddr,regData);
	if(retVal !=  SUCCESS){
		DEBUG_MSG("%s: rtl8366s_setAsicReg2 fail\n",__func__);
		return FAILED;
	}	
	
	return SUCCESS;
}

/*
@func uint32_t | rtl8366s_getAsicVlanMemberConfig | Get 16 VLAN member configurations.
@parm uint32_t | index | VLAN member configuration index (0~15).
@parm rtl8366s_vlanconfig* | vlanmemberconf | VLAN member configuration. It contained VID, priority, member set, untag set and FID fields. 
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@rvalue ERRNO_INVALIDINPUT | Invalid input parameter.
@rvalue ERRNO_VLAN_INVALIDMBRCONFIDX | Invalid VLAN member configuration index (0~15).
@comm
	The API can get 16 VLAN member configuration.
	
*/
uint32_t rtl8366s_getAsicVlanMemberConfig(uint32_t index,rtl8366s_vlanconfig *vlanmconf )
{
	uint32_t retVal;
	uint32_t regAddr;
	uint32_t regData;
	uint16_t* tableAddr;

	if(index > RTL8366S_VLANMCIDXMAX){
		DEBUG_MSG("%s: RTL8366S_VLANMCIDXMAX fail\n",__func__);
		return FAILED;
	}	

	tableAddr = (uint16_t*)vlanmconf;
	
	regAddr = RTL8366S_VLAN_MEMCONF_BASE + (index<<1);

	retVal = rtl8366s_getAsicReg(regAddr,&regData);
	if(retVal !=  SUCCESS){
		DEBUG_MSG("%s: rtl8366s_getAsicReg fail\n",__func__);
		return FAILED;
	}	

	*tableAddr = regData;
	tableAddr ++;	
		
	regAddr = RTL8366S_VLAN_MEMCONF_BASE + 1 + (index<<1);

	retVal = rtl8366s_getAsicReg(regAddr,&regData);
	if(retVal !=  SUCCESS){
		DEBUG_MSG("%s: rtl8366s_getAsicReg2 fail\n",__func__);
		return FAILED;
	}	
	
	*tableAddr = regData;

	return SUCCESS;
}

/*
@func uint32_t | rtl8366s_setAsicVlan4kEntry | Set VID mapped entry to 4K VLAN table.
@parm rtl8366s_vlan4kentry* | vlan4kEntry | VLAN entry seting for 4K table. There is VID field in entry structure and  entry is directly mapping to 4K table location (1 to 1).
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@rvalue ERRNO_INVALIDINPUT | Invalid input parameter.
@rvalue ERRNO_VLAN_INVALIDFID | Invalid FID (0~7).
@rvalue ERRNO_VLAN_INVALIDPORTMSK | Invalid port mask (0x00~0x3F).
@rvalue ERRNO_VLAN_INVALIDVID | Invalid VID parameter (0~4095).
@comm
	VID field of C-tag is 12-bits and available VID range is 0~4095. In 802.1q spec. , null VID (0x000) means tag header contain priority information
	only and VID 0xFFF is reserved for implementtation usage. But ASIC still retrieved these VID entries in 4K VLAN table if VID is decided from 16
	member configurations. It has no available VID 0x000 and 0xFFF from C-tag. ASIC will retrieve these two non-standard VIDs (0x000 and 0xFFF) from 
	member configuration indirectly referenced by Port based, Protocol-and-Port based VLAN and 802.1x functions.
	
*/
uint32_t rtl8366s_setAsicVlan4kEntry(rtl8366s_vlan4kentry vlan4kEntry )
{
	uint32_t retVal;
	uint32_t regData;
	uint16_t* tableAddr;

	if(vlan4kEntry.vid > RTL8366S_VIDMAX){
		DEBUG_MSG("%s: RTL8366S_VIDMAX fail\n",__func__);
		return FAILED;
	}	

	if(vlan4kEntry.member > RTL8366S_PORTMASK){
		DEBUG_MSG("%s: member RTL8366S_PORTMASK fail\n",__func__);
		return FAILED;
	}	

	if(vlan4kEntry.untag> RTL8366S_PORTMASK){
		DEBUG_MSG("%s: untag RTL8366S_PORTMASK fail\n",__func__);
		return FAILED;
	}	

	if(vlan4kEntry.fid > RTL8366S_FIDMAX){
		DEBUG_MSG("%s: RTL8366S_FIDMAX fail\n",__func__);
		return FAILED;
	}	

	tableAddr = (uint16_t*)&vlan4kEntry;

	regData = *tableAddr;
	
	retVal = rtl8366s_setAsicReg(RTL8366S_VLAN_TABLE_WRITE_BASE,regData);
	if(retVal !=  SUCCESS){
		DEBUG_MSG("%s: rtl8366s_setAsicReg fail\n",__func__);
		return FAILED;
	}	

	tableAddr ++;

	regData = *tableAddr;
	
	retVal = rtl8366s_setAsicReg(RTL8366S_VLAN_TABLE_WRITE_BASE+1,regData);
	if(retVal !=  SUCCESS){
		DEBUG_MSG("%s: rtl8366s_setAsicReg2 fail\n",__func__);
		return FAILED;
	}	
	
	/*write table access Control word*/
	retVal = rtl8366s_setAsicReg(RTL8366S_TABLE_ACCESS_CTRL_REG,RTL8366S_TABLE_VLAN_WRITE_CTRL);
	if(retVal !=  SUCCESS){
		DEBUG_MSG("%s: rtl8366s_setAsicReg3 fail\n",__func__);
		return FAILED;
	}	

#ifdef CONFIG_RTL8366S_ASICDRV_TEST
	Rtl8366sVirtualVlanTable[vlan4kEntry.vid] = vlan4kEntry;
#endif
	return SUCCESS;
}

/*
@func uint32_t | rtl8366s_getAsicVlan4kEntry | Get VID mapped entry to 4K VLAN table. 
@parm rtl8366s_vlan4kentry* | vlan4kEntry | VLAN entry seting for 4K table. There is VID field in entry structure and  entry is directly mapping to 4K table location (1 to 1).
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@rvalue ERRNO_INVALIDINPUT | Invalid input parameter.
@rvalue ERRNO_VLAN_INVALIDVID | Invalid VID parameter (0~4095).
@comm
	The API can get entry of 4k VLAN table. Software must prepare the retrieving VID first at writing data and used control word to access desired VLAN entry.
	
*/
uint32_t rtl8366s_getAsicVlan4kEntry(rtl8366s_vlan4kentry *vlan4kEntry )
{
	uint32_t retVal;
	uint32_t regData;
	uint32_t vid;
	uint16_t* tableAddr;

	vid = vlan4kEntry->vid;
	
	if(vid > RTL8366S_VIDMAX){
		DEBUG_MSG("%s: RTL8366S_VIDMAX fail\n",__func__);
		return FAILED;
	}	

	tableAddr = (uint16_t*)vlan4kEntry;

	/*write VID first*/
	regData = *tableAddr;	
	retVal = rtl8366s_setAsicReg(RTL8366S_VLAN_TABLE_WRITE_BASE,regData);
	if(retVal !=  SUCCESS){
		DEBUG_MSG("%s: rtl8366s_setAsicReg fail\n",__func__);
		return FAILED;
	}	

	/*write table access Control word*/
	retVal = rtl8366s_setAsicReg(RTL8366S_TABLE_ACCESS_CTRL_REG,RTL8366S_TABLE_VLAN_READ_CTRL);
	if(retVal !=  SUCCESS){
		DEBUG_MSG("%s: rtl8366s_setAsicReg2 fail\n",__func__);
		return FAILED;
	}	

#ifdef CONFIG_RTL8366S_ASICDRV_TEST
	*(rtl8366s_vlan4kentry *)&Rtl8366sVirtualReg[RTL8366S_VLAN_TABLE_READ_BASE] = Rtl8366sVirtualVlanTable[vid];
#endif

	retVal = rtl8366s_getAsicReg(RTL8366S_VLAN_TABLE_READ_BASE,&regData);
	if(retVal !=  SUCCESS){
		DEBUG_MSG("%s: rtl8366s_getAsicReg fail\n",__func__);
		return FAILED;
	}	

	*tableAddr = regData;
	tableAddr ++;
	
	retVal = rtl8366s_getAsicReg(RTL8366S_VLAN_TABLE_READ_BASE+1,&regData);
	if(retVal !=  SUCCESS){
		DEBUG_MSG("%s: rtl8366s_getAsicReg2 fail\n",__func__);
		return FAILED;
	}	

	*tableAddr = regData;

	vlan4kEntry->vid = vid;
	
	return SUCCESS;
}

/*
@func uint32_t | rtl8366s_setAsicVlanPortBasedVID | Set port based VID which is indexed to 16 VLAN member configurations.
@parm enum PORTID | port | Physical port number (0~5).
@parm uint32 | index | Index to VLAN member configuration (0~15).
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@rvalue ERRNO_VLAN_INVALIDMBRCONFIDX | Invalid VLAN member configuration index (0~15).
@rvalue ERRNO_VLAN_INVALIDPORT | Invalid port number.
@comm
	In port based VLAN, untagged packets recieved by port N are forwarded to a VLAN according to the setting VID of port N. Usage of VLAN 4k table is enabled
	and there are only VID and 802.1q priority retrieved from 16 member configurations . Member set, untag set and FID of port based VLAN are be retrieved from 
	4K mapped VLAN entry.
	
*/
uint32_t rtl8366s_setAsicVlanPortBasedVID(enum PORTID port, uint32_t index)
{
	uint32_t retVal;
	uint32_t regAddr;
	uint32_t regData;
	uint32_t regBits;

	/* bits mapping to port vlan control register of port n */
	//const uint16_t bits[6]= { 0x000F,0x00F0,0x0F00,0xF000,0x000F,0x00F0 };
	static uint16_t bits[6]= { 0x000F,0x00F0,0x0F00,0xF000,0x000F,0x00F0 };
	/* bits offset to port vlan control register of port n */
	//const uint16_t bitOff[6] = { 0,4,8,12,0,4 };
	static uint16_t bitOff[6] = { 0,4,8,12,0,4 };
	/* address offset to port vlan control register of port n */
	//const uint16_t addrOff[6]= { 0,0,0,0,1,1 };
	static uint16_t addrOff[6]= { 0,0,0,0,1,1 };

	if(port >=PORT_MAX){
		DEBUG_MSG("%s: PORT_MAX fail\n",__func__);
		return FAILED;
	}	

	if(index > RTL8366S_VLANMCIDXMAX){
		DEBUG_MSG("%s: PORT_MAX fail\n",__func__);
		return FAILED;
	}	

	regAddr = RTL8366S_PORT_VLAN_CTRL_BASE + addrOff[port];

	regBits = bits[port];

	regData =  (index << bitOff[port]) & regBits;

	retVal = rtl8366s_setAsicRegBits(regAddr,regBits,regData);		
	if(retVal !=  SUCCESS){
		DEBUG_MSG("%s: rtl8366s_setAsicRegBits fail\n",__func__);
		return FAILED;
	}	
		
	return SUCCESS;
}

/*
@func uint32_t | rtl8366s_getAsicVlanPortBasedVID | Get port based VID which is indexed to 16 VLAN member configurations.
@parm enum PORTID | port | Physical port number (0~5).
@parm uint32* | index | Index to VLAN member configuration (0~15).
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@rvalue ERRNO_VLAN_INVALIDPORT | Invalid port number.
@comm
	The API can access port based VLAN index indirectly retrieving VID and priority from 16 member configuration for a specific port.
	
*/
uint32_t rtl8366s_getAsicVlanPortBasedVID(enum PORTID port, uint32_t* index)
{
	uint32_t retVal;
	uint32_t regAddr;
	uint32_t regData;

	/* bits mapping to port vlan control register of port n */
	//const uint16_t bits[6]= { 0x000F,0x00F0,0x0F00,0xF000,0x000F,0x00F0 };
	static uint16_t bits[6]= { 0x000F,0x00F0,0x0F00,0xF000,0x000F,0x00F0 };
	/* bits offset to port vlan control register of port n */
	//const uint16_t bitOff[6] = { 0,4,8,12,0,4 };
	static uint16_t bitOff[6] = { 0,4,8,12,0,4 };
	/* address offset to port vlan control register of port n */
	//const uint16_t addrOff[6]= { 0,0,0,0,1,1 };
	static uint16_t addrOff[6]= { 0,0,0,0,1,1 };


	if(port >=PORT_MAX){
		DEBUG_MSG("%s: PORT_MAX fail\n",__func__);
		return FAILED;
	}

	regAddr = RTL8366S_PORT_VLAN_CTRL_BASE + addrOff[port];

	retVal = rtl8366s_getAsicReg(regAddr,&regData);
	if(retVal != SUCCESS){
		DEBUG_MSG("%s: rtl8366s_getAsicReg fail\n",__func__);
		return FAILED;
	}	

	*index =  (regData & bits[port]) >> bitOff[port];
	return SUCCESS;
}

/*
@func uint32_t | rtl8366s_initVlan | Initialize VLAN.
@rvalue SUCCESS | Success.
@rvalue FAILED | Failure.
@comm
	VLAN is disabled by default. User has to call this API to enable VLAN before
	using it. And It will set a default VLAN(vid 1) including all ports and set 
	all ports PVID to the default VLAN.
*/
uint32_t rtl8366s_initVlan(void)
{
	uint32_t i;
	rtl8366s_vlan4kentry vlan4K;
	rtl8366s_vlanconfig vlanMC;
	
	/* clear 16 VLAN member configuration */
	for(i = 0; i <= RTL8366S_VLANMCIDXMAX; i++)
	{	
		vlanMC.vid = 0;
		vlanMC.priority = 0;
		vlanMC.member = 0;		
		vlanMC.untag = 0;			
		vlanMC.fid = 0;
		if(rtl8366s_setAsicVlanMemberConfig(i, &vlanMC) != SUCCESS){
			DEBUG_MSG("%s: rtl8366s_setAsicVlanMemberConfig fail\n",__func__);
			return FAILED;	
		}	
	}

	/* Set a default VLAN with vid 1 to 4K table for all ports */
   	vlan4K.vid = 1;
 	vlan4K.member = RTL8366S_PORTMASK;
 	vlan4K.untag = RTL8366S_PORTMASK;
 	vlan4K.fid = 0;	
	if(rtl8366s_setAsicVlan4kEntry(vlan4K) != SUCCESS){
		DEBUG_MSG("%s: rtl8366s_setAsicVlan4kEntry fail\n",__func__);
		return FAILED;		
	}	

	/* Also set the default VLAN to 16 member configuration index 0 */
	vlanMC.vid = 1;
	vlanMC.priority = 0;
	vlanMC.member = RTL8366S_PORTMASK;		
	vlanMC.untag = RTL8366S_PORTMASK;			
	vlanMC.fid = 0;
	if(rtl8366s_setAsicVlanMemberConfig(0, &vlanMC) != SUCCESS){
		DEBUG_MSG("%s: rtl8366s_setAsicVlanMemberConfig2 fail\n",__func__);
		return FAILED;		
	}	

	/* Set all ports PVID to default VLAN */	
	for(i = 0; i < PORT_MAX; i++)
	{	
		if(rtl8366s_setAsicVlanPortBasedVID(i, 0) != SUCCESS){
			DEBUG_MSG("%s: rtl8366s_setAsicVlanPortBasedVID fail\n",__func__);
			return FAILED;		
		}	
	}	

	/* enable VLAN and 4K VLAN */
	if(rtl8366s_setAsicVlan(TRUE)!= SUCCESS){
		DEBUG_MSG("%s: rtl8366s_setAsicVlan fail\n",__func__);
		return FAILED;	
	}	
	if(rtl8366s_setAsicVlan4kTbUsage(TRUE)!= SUCCESS){
		DEBUG_MSG("%s: rtl8366s_setAsicVlan4kTbUsage fail\n",__func__);
		return FAILED;
	}	
		
	return SUCCESS;
}

/*
@func uint32_t | rtl8366s_setVlan | Set a VLAN entry.
@parm uint32_t | vid | VLAN ID to configure (0~4095).
@parm uint32_t | mbrmsk | VLAN member set portmask (0~0x3F).
@parm uint32_t | untagmsk | VLAN untag set portmask (0~0x3F).
@rvalue ERRNO_API_INVALIDPARAM | invalid input parameters.
@rvalue SUCCESS | Success.
@rvalue FAILED | Failure.
@comm
	There are 4K VLAN entry supported. Member set and untag set	of 4K VLAN entry
	are all zero by default.	User could configure the member	set and untag set
	for specified vid through this API.	The portmask's bit N means port N.
	For example, mbrmask 23=0x17=010111 means port 0,1,2,4 in the member set.
*/
uint32_t rtl8366s_setVlan(uint32_t vid, uint32_t mbrmsk, uint32_t untagmsk)
{
	uint32_t i;
	rtl8366s_vlan4kentry vlan4K;
	rtl8366s_vlanconfig vlanMC;	
	
	/* vid must be 0~4095 */
	if(vid > RTL8366S_VIDMAX){
		DEBUG_MSG("%s: RTL8366S_VIDMAX fail\n",__func__);
		return FAILED;		
	}	

	if(mbrmsk > RTL8366S_PORTMASK){
		DEBUG_MSG("%s: RTL8366S_PORTMASK fail\n",__func__);
		return FAILED;
	}	

	if(untagmsk > RTL8366S_PORTMASK){
		DEBUG_MSG("%s: RTL8366S_PORTMASK fail\n",__func__);
		return FAILED;
	}	

	/* update 4K table */
   	vlan4K.vid = vid;			
 	vlan4K.member = mbrmsk;
 	vlan4K.untag = untagmsk;
 	vlan4K.fid = 0;	
	if(rtl8366s_setAsicVlan4kEntry(vlan4K) != SUCCESS){
		DEBUG_MSG("%s: rtl8366s_setAsicVlan4kEntry fail\n",__func__);
		return FAILED;
	}	
	
	/* 
		Since VLAN entry would be copied from 4K to 16 member configuration while
		setting Port-based VLAN. So also update the entry in 16 member configuration
		if it existed.
	*/
	for(i = 0; i <= RTL8366S_VLANMCIDXMAX; i++)
	{	
		if(rtl8366s_getAsicVlanMemberConfig(i, &vlanMC) != SUCCESS){
			DEBUG_MSG("%s: rtl8366s_getAsicVlanMemberConfig fail\n",__func__);
			return FAILED;	
		}	

		if(vid == vlanMC.vid)
		{
			vlanMC.member = mbrmsk;		
			vlanMC.untag = untagmsk;			
			if(rtl8366s_setAsicVlanMemberConfig(i, &vlanMC) != SUCCESS){
				DEBUG_MSG("%s: rtl8366s_setAsicVlanMemberConfig fail\n",__func__);
				return FAILED;	
			}	

			return SUCCESS;
		}	
	}
	
	return SUCCESS;
}

/*
@func uint32_t | rtl8366s_getVlan | Get a VLAN entry.
@parm uint32_t | vid | VLAN ID to get entry (0~4095).
@parm uint32_t* | mbrmsk | pointer to returned member set portmask.
@parm uint32_t* | untagmsk | pointer to returned untag set portmask.
@rvalue ERRNO_API_INVALIDPARAM | invalid input parameters.
@rvalue SUCCESS | Success.
@rvalue FAILED | Failure.
@comm
	The API can get the member set and untag set settings for specified vid.
*/
uint32_t rtl8366s_getVlan(uint32_t vid, uint32_t *mbrmsk, uint32_t *untagmsk)
{
	rtl8366s_vlan4kentry vlan4K;
	
	/* vid must be 0~4095 */
	if(vid > RTL8366S_VIDMAX){
		DEBUG_MSG("%s: RTL8366S_VIDMAX fail\n",__func__);
		return FAILED;	
	}	

	vlan4K.vid = vid;
	if(rtl8366s_getAsicVlan4kEntry(&vlan4K) != SUCCESS){
		DEBUG_MSG("%s: rtl8366s_getAsicVlan4kEntry fail\n",__func__);
		return FAILED;	
	}	

	*mbrmsk = vlan4K.member;
	*untagmsk = vlan4K.untag;	
	return SUCCESS;
}

/*
@func uint32_t | rtl8366s_setVlanPVID | Set port to specified VLAN ID(PVID).
@parm enum PORTID | port | Port number (0~5).
@parm uint32_t | vid | Specified VLAN ID (0~4095).
@parm uint32_t | priority | 802.1p priority for the PVID (0~7).
@rvalue ERRNO_API_INVALIDPARAM | invalid input parameters.
@rvalue SUCCESS | Success.
@rvalue FAILED | Failure.
@comm
	The API is used for Port-based VLAN. The untagged frame received from the
	port will be classified to the specified VLAN and assigned to the specified priority.
	Make sure you have configured the VLAN by 'rtl8366s_setVlan' before using the API.
*/
uint32_t rtl8366s_setVlanPVID(enum PORTID port, uint32_t vid, uint32_t priority)
{
	uint32_t i;
	uint32_t j;
	uint32_t index;	
	uint8_t  bUsed;	
	rtl8366s_vlan4kentry vlan4K;
	rtl8366s_vlanconfig vlanMC;	

	if(port >= PORT_MAX){
		DEBUG_MSG("%s: PORT_MAX fail\n",__func__);
		return FAILED;	
	}	
	
	/* vid must be 0~4095 */
	if(vid > RTL8366S_VIDMAX){
		DEBUG_MSG("%s: RTL8366S_VIDMAX fail\n",__func__);
		return FAILED;	
	}	

	/* priority must be 0~7 */
	if(priority > RTL8366S_PRIORITYMAX){
		DEBUG_MSG("%s: RTL8366S_PRIORITYMAX fail\n",__func__);
		return FAILED;	
	}	
	
	/* 
		Search 16 member configuration to see if the entry already existed.
		If existed, update the priority and assign the index to the port.
	*/
	for(i = 0; i <= RTL8366S_VLANMCIDXMAX; i++)
	{	
		if(rtl8366s_getAsicVlanMemberConfig(i, &vlanMC) != SUCCESS){
			DEBUG_MSG("%s: rtl8366s_getAsicVlanMemberConfig fail\n",__func__);
			return FAILED;	
		}	

		if(vid == vlanMC.vid)
		{
			vlanMC.priority = priority;		
			if(rtl8366s_setAsicVlanMemberConfig(i, &vlanMC) != SUCCESS){
				DEBUG_MSG("%s: rtl8366s_setAsicVlanMemberConfig fail\n",__func__);
				return FAILED;	
			}	
		
			if(rtl8366s_setAsicVlanPortBasedVID(port, i) != SUCCESS){
				DEBUG_MSG("%s: rtl8366s_setAsicVlanPortBasedVID fail\n",__func__);
				return FAILED;	
			}	

			return SUCCESS;
		}	
	}

	/*
		vid doesn't exist in 16 member configuration. Find an empty entry in 
		16 member configuration, then copy entry from 4K. If 16 member configuration
		are all full, then find an entry which not used by Port-based VLAN and 
		then replace it with 4K. Finally, assign the index to the port.
	*/
	for(i = 0; i <= RTL8366S_VLANMCIDXMAX; i++)
	{	
		if(rtl8366s_getAsicVlanMemberConfig(i, &vlanMC) != SUCCESS){
			DEBUG_MSG("%s: rtl8366s_getAsicVlanMemberConfig fail\n",__func__);
			return FAILED;	
		}	

		if(vlanMC.vid == 0 && vlanMC.member == 0)
		{
			vlan4K.vid = vid;
			if(rtl8366s_getAsicVlan4kEntry(&vlan4K) != SUCCESS){
				DEBUG_MSG("%s: rtl8366s_getAsicVlan4kEntry fail\n",__func__);
				return FAILED;
			}	

			vlanMC.vid = vid;
			vlanMC.priority = priority;
			vlanMC.member = vlan4K.member;		
			vlanMC.untag = vlan4K.untag;			
			vlanMC.fid = vlan4K.fid;
			if(rtl8366s_setAsicVlanMemberConfig(i, &vlanMC) != SUCCESS){
				DEBUG_MSG("%s: rtl8366s_setAsicVlanMemberConfig fail\n",__func__);
				return FAILED;	
			}				

			if(rtl8366s_setAsicVlanPortBasedVID(port, i) != SUCCESS){
				DEBUG_MSG("%s: rtl8366s_setAsicVlanPortBasedVID fail\n",__func__);
				return FAILED;	
			}	

			return SUCCESS;			
		}	
	}	

	/* 16 member configuration is full, found a unused entry to replace */
	for(i = 0; i <= RTL8366S_VLANMCIDXMAX; i++)
	{	
		bUsed = FALSE;	

		for(j = 0; j < PORT_MAX; j++)
		{	
			if(rtl8366s_getAsicVlanPortBasedVID(j, &index) != SUCCESS){
				DEBUG_MSG("%s: rtl8366s_getAsicVlanPortBasedVID fail\n",__func__);
				return FAILED;	
			}	

			if(i == index)/*index i is in use by port j*/
			{
				bUsed = TRUE;
				break;
			}	
		}

		if(bUsed == FALSE)/*found a unused index, replace it*/
		{
			vlan4K.vid = vid;
			if(rtl8366s_getAsicVlan4kEntry(&vlan4K) != SUCCESS){
				DEBUG_MSG("%s: rtl8366s_getAsicVlan4kEntry fail\n",__func__);
				return FAILED;
			}	

			vlanMC.vid = vid;
			vlanMC.priority = priority;
			vlanMC.member = vlan4K.member;		
			vlanMC.untag = vlan4K.untag;			
			vlanMC.fid = vlan4K.fid;
			if(rtl8366s_setAsicVlanMemberConfig(i, &vlanMC) != SUCCESS){
				DEBUG_MSG("%s: rtl8366s_setAsicVlanMemberConfig fail\n",__func__);
				return FAILED;	
			}	

			if(rtl8366s_setAsicVlanPortBasedVID(port, i) != SUCCESS){
				DEBUG_MSG("%s: rtl8366s_setAsicVlanPortBasedVID fail\n",__func__);
				return FAILED;	
			}				

			return SUCCESS;			
		}
	}	
	
	return FAILED;
}

/*
@func uint32_t | rtl8366s_getVlanPVID | Get VLAN ID(PVID) on specified port.
@parm enum PORTID | port | Port number (0~5).
@parm uint32* | vid | pointer to returned VLAN ID.
@parm uint32* | priority | pointer to returned 802.1p priority.
@rvalue ERRNO_API_INVALIDPARAM | invalid input parameters.
@rvalue SUCCESS | Success.
@rvalue FAILED | Failure.
@comm
	The API can get the PVID and 802.1p priority for the PVID of Port-based VLAN.
*/
uint32_t rtl8366s_getVlanPVID(enum PORTID port, uint32_t *vid, uint32_t *priority)
{
	uint32_t index;
	rtl8366s_vlanconfig vlanMC;	

	if(port >= PORT_MAX){
		DEBUG_MSG("%s: PORT_MAX fail\n",__func__);
		return FAILED;	
	}	
	
	if(rtl8366s_getAsicVlanPortBasedVID(port, &index) != SUCCESS){
		DEBUG_MSG("%s: rtl8366s_getAsicVlanPortBasedVID fail\n",__func__);
		return FAILED;			
	}	

	if(rtl8366s_getAsicVlanMemberConfig(index, &vlanMC) != SUCCESS){
		DEBUG_MSG("%s: rtl8366s_getAsicVlanMemberConfig fail\n",__func__);
		return FAILED;		
	}	

	*vid = vlanMC.vid;
	*priority = vlanMC.priority;	
	return SUCCESS;
}

#endif//*********************************************

#ifdef MIB_COUNTER//*********************************************
/*
@func uint32_t | rtl8366s_getAsicMIBsCounter | Get MIBs counter.
@parm enum PORTID | port | Physical port number (0~5).
@num RTL8366S_MIBCOUNTER | mibIdx | MIB counter index.
@parm uint64_t* | counter | MIB retrived counter.
@rvalue SUCCESS | Success.
@rvalue ERRNO_MIB_INVALIDPORT | Invalid port number
@rvalue ERRNO_MIB_INVALIDIDX | Invalid MIBs index.
@rvalue ERRNO_MIB_BUSY | MIB is busy at retrieving
@rvalue ERRNO_MIB_RESET | MIB is resetting.
@comm
 	Before MIBs counter retrieving, writting accessing address to ASIC at first and check the MIB control register status. If busy bit of MIB control is set, that
 	mean MIB counter have been waiting for preparing, then software must wait atfer this busy flag reset by ASIC. This driver did not recycle reading user desired
 	counter. Software must use driver again to get MIB counter if return value is not SUCCESS.

*/
uint32_t rtl8366s_getAsicMIBsCounter(enum PORTID port,enum RTL8366S_MIBCOUNTER mibIdx,uint64_t* counter)
{
	uint32_t retVal;
	uint32_t regAddr;
	uint32_t regData;
	uint32_t regOff;

	/* address offset to MIBs counter */
	//const uint16_t mibLength[RTL8366S_MIBS_NUMBER]= {4,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2};
	static uint16_t mibLength[RTL8366S_MIBS_NUMBER]= {4,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2};
	uint32_t i;
	uint64_t mibCounter;


	if(port >=PORT_MAX){
		DEBUG_MSG("rtl8366s_getAsicMIBsCounter: port fail\n");
		return FAILED;
	}		

	if(mibIdx>= RTL8366S_MIBS_NUMBER){
		DEBUG_MSG("rtl8366s_getAsicMIBsCounter: mibIdx fail\n");
		return FAILED;
	}	

	if(mibIdx == Dot1dTpLearnEntryDiscardFlag)
	{
		regAddr = RTL8366S_MIB_DOT1DTPLEARNDISCARD;
	}
	else if(mibIdx < Dot1dTpPortInDiscards)
	{
		i = 0;
		regOff = RTL8366S_MIB_COUTER_PORT_OFFSET*(port);

		while(i<mibIdx)
		{
			regOff += mibLength[i];
			i++;
		}		
		
		regAddr = RTL8366S_MIB_COUTER_BASE + regOff;
	}
	else
	{
		i = Dot1dTpPortInDiscards;
		regOff = RTL8366S_MIB_COUTER2_PORT_OFFSET*(port);;
		while(i<mibIdx)
		{
		 	regOff += mibLength[i];
			i++;
		}		

		regAddr = RTL8366S_MIB_COUTER_2_BASE + regOff;
	}

	/*writing access counter address first*/
	/*then ASIC will prepare 64bits counter wait for being retrived*/
	regData = 0;/*writing data will be discard by ASIC*/
	retVal = rtl8366s_setAsicReg(regAddr,regData);


	/*read MIB control register*/
	retVal = rtl8366s_getAsicReg(RTL8366S_MIB_CTRL_REG,&regData);

	if(regData & RTL8366S_MIB_CTRL_BUSY_MSK){
		DEBUG_MSG("rtl8366s_getAsicMIBsCounter: MIB_BUSY fail\n");
		return FAILED;
	}	

	if(regData & RTL8366S_MIB_CTRL_RESET_MSK){
		DEBUG_MSG("rtl8366s_getAsicMIBsCounter: MIB_RESET fail\n");
		return FAILED;		
	}	

	mibCounter = 0;
	regAddr = regAddr + mibLength[mibIdx]-1;
	i = mibLength[mibIdx];
	while(i)
	{
		retVal = rtl8366s_getAsicReg(regAddr,&regData);
		if(retVal != SUCCESS){
			DEBUG_MSG("rtl8366s_getAsicMIBsCounter: rtl8366s_getAsicReg fail\n");
			return retVal;
		}	

		mibCounter = (mibCounter<<16) | (regData & 0xFFFF);

		regAddr --;
		i --;
		
	}
	
	*counter = mibCounter;
	
	return SUCCESS;
}

/*
@func uint32_t | rtl8366s_getMIBCounter | Get MIB counter
@parm enum PORTID | port | Physical port number (0~5).
@num RTL8366S_MIBCOUNTER | mibIdx | MIB counter index.
@parm uint64_t* | counter | MIB retrived counter.
@rvalue SUCCESS | Success.
@rvalue FAILED | Failure. 
@comm
	Get MIB counter by index definition as following description. There are per port MIB counters from index 0 to 32 while index 33 
	is a system-wide counter.
	index	MIB counter												
	0 		IfInOctets
	1		EtherStatsOctets
	2		EtherStatsUnderSizePkts
	3		EtherFregament
	4		EtherStatsPkts64Octets
	5		EtherStatsPkts65to127Octets
	6		EtherStatsPkts128to255Octets
	7		EtherStatsPkts256to511Octets
	8		EtherStatsPkts512to1023Octets
	9		EtherStatsPkts1024to1518Octets
	10		EtherOversizeStats
	11		EtherStatsJabbers
	12		IfInUcastPkts
	13		EtherStatsMulticastPkts
	14		EtherStatsBroadcastPkts
	15		EtherStatsDropEvents
	16		Dot3StatsFCSErrors
	17		Dot3StatsSymbolErrors
	18		Dot3InPauseFrames
	19		Dot3ControlInUnknownOpcodes
	20		IfOutOctets
	21		Dot3StatsSingleCollisionFrames
	22		Dot3StatMultipleCollisionFrames
	23		Dot3sDeferredTransmissions
	24		Dot3StatsLateCollisions
	25		EtherStatsCollisions
	26		Dot3StatsExcessiveCollisions
	27		Dot3OutPauseFrames
	28		Dot1dBasePortDelayExceededDiscards
	29		Dot1dTpPortInDiscards
	30		IfOutUcastPkts
	31		IfOutMulticastPkts
	32		IfOutBroadcastPkts
	33		Dot1dTpLearnEntryDiscardFlag	
*/
uint32_t rtl8366s_getMIBCounter(enum PORTID port,enum RTL8366S_MIBCOUNTER mibIdx,uint64_t* counter)
{
	if(SUCCESS != rtl8366s_getAsicMIBsCounter(port,mibIdx,counter))	{	
		DEBUG_MSG("rtl8366s_getAsicMIBsCounter fail\n");
		return FAILED;
	}	
	DEBUG_MSG("port%x:mibIdx=%x counter=%x\n",port,mibIdx,*counter);
	return SUCCESS;
}

void rtl8366sr_show_counters(int phyunit,int input)
{
	uint64_t counter;	
	if(phyunit==PORT0){
		if(input)
			rtl8366s_getMIBCounter(PORT0,IfInOctets,&counter);
		else
			rtl8366s_getMIBCounter(PORT0,IfOutOctets,&counter);			
	}
	else if(phyunit==PORT1){			
		if(input)
			rtl8366s_getMIBCounter(PORT1,IfInOctets,&counter);
		else
			rtl8366s_getMIBCounter(PORT1,IfOutOctets,&counter);
	}
	else if(phyunit==PORT2){	
		if(input)
			rtl8366s_getMIBCounter(PORT2,IfInOctets,&counter);
		else
			rtl8366s_getMIBCounter(PORT2,IfOutOctets,&counter);
	}		
	else if(phyunit==PORT3){
		if(input)
			rtl8366s_getMIBCounter(PORT3,IfInOctets,&counter);
		else
			rtl8366s_getMIBCounter(PORT3,IfOutOctets,&counter);
	}			
	else if(phyunit==PORT4){
		if(input)
			rtl8366s_getMIBCounter(PORT4,IfInOctets,&counter);
		else
			rtl8366s_getMIBCounter(PORT4,IfOutOctets,&counter);	
	}
	else{					
        if(input)
			rtl8366s_getMIBCounter(PORT5,IfInOctets,&counter);
		else
			rtl8366s_getMIBCounter(PORT5,IfOutOctets,&counter);
    }    	
	
}	

#endif//MIB_COUNTER//*********************************************

#ifdef LED_SET//*********************************************
/*
@func uint32_t | rtl8366s_setAsicLedIndicateInfoConfig | Set Leds indicated information mode
@parm uint32_t | ledNo | LED group number. There are 1 to 1 led mapping to each port in each led group. 
@parm enum RTL8366S_LEDCONF | config | Support 16 types configuration.
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@comm
	The API can set LED indicated information configuration for each LED group with 1 to 1 led mapping to each port.
	Definition		LED Statuses			Description
	0000		LED_Off				LED pin Tri-State.
	0001		Dup/Col				Collision, Full duplex Indicator. Blinking every 43ms when collision happens. Low for full duplex, and high for half duplex mode.
	0010		Link/Act				Link, Activity Indicator. Low for link established. Link/Act Blinks every 43ms when the corresponding port is transmitting or receiving.
	0011		Spd1000				1000Mb/s Speed Indicator. Low for 1000Mb/s.
	0100		Spd100				100Mb/s Speed Indicator. Low for 100Mb/s.
	0101		Spd10				10Mb/s Speed Indicator. Low for 10Mb/s.
	0110		Spd1000/Act			1000Mb/s Speed/Activity Indicator. Low for 1000Mb/s. Blinks every 43ms when the corresponding port is transmitting or receiving.
	0111		Spd100/Act			100Mb/s Speed/Activity Indicator. Low for 100Mb/s. Blinks every 43ms when the corresponding port is transmitting or receiving.
	1000		Spd10/Act			10Mb/s Speed/Activity Indicator. Low for 10Mb/s. Blinks every 43ms when the corresponding port is transmitting or receiving.
	1001		Spd100 (10)/Act		10/100Mb/s Speed/Activity Indicator. Low for 10/100Mb/s. Blinks every 43ms when the corresponding port is transmitting or receiving.
	1010		Fiber				Fiber link Indicator. Low for Fiber.
	1011		Fault	Auto-negotiation 	Fault Indicator. Low for Fault.
	1100		Link/Rx				Link, Activity Indicator. Low for link established. Link/Rx Blinks every 43ms when the corresponding port is transmitting.
	1101		Link/Tx				Link, Activity Indicator. Low for link established. Link/Tx Blinks every 43ms when the corresponding port is receiving.
	1110		Master				Link on Master Indicator. Low for link Master established.
	1111		LED_Force			Force LED output, LED output value reference 
 */
uint32_t rtl8366s_setAsicLedIndicateInfoConfig(uint32_t ledNo, enum RTL8366S_LEDCONF config)
{
	uint32_t retVal, regValue;

	if(ledNo >=RTL8366S_LED_GROUP_MAX){
		DEBUG_MSG("rtl8366s_setAsicLedIndicateInfoConfig: group fail\n");
		return FAILED;
	}	

	if(config > LEDCONF_LEDFORCE){	
		DEBUG_MSG("rtl8366s_setAsicLedIndicateInfoConfig: config fail\n");
		return FAILED;
	}	


	/* Get register value */
	retVal = rtl8366s_getAsicReg(RTL8366S_LED_INDICATED_CONF_REG, &regValue); 	
	if (retVal !=  SUCCESS){
		DEBUG_MSG("rtl8366s_setAsicLedIndicateInfoConfig: rtl8366s_getAsicReg fail\n");
		return retVal;
	}	

	regValue =  (regValue & (~(0xF<<(ledNo*4)))) | (config<<(ledNo*4));

	
	retVal = rtl8366s_setAsicReg(RTL8366S_LED_INDICATED_CONF_REG, regValue); 	

	return retVal;
}

/*
@func uint32_t | rtl8366s_getAsicLedIndicateInfoConfig | Get Leds indicated information mode
@parm uint32_t | ledNo | LED group number. There are 1 to 1 led mapping to each port in each led group. 
@parm enum RTL8366S_LEDCONF* | config | Support 16 types configuration.
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@comm
	The API can get LED indicated information configuration for each LED group.
 */
uint32_t rtl8366s_getAsicLedIndicateInfoConfig(uint32_t ledNo, enum RTL8366S_LEDCONF* config)
{
	uint32_t retVal, regValue;

	if(ledNo >=RTL8366S_LED_GROUP_MAX){
		DEBUG_MSG("rtl8366s_getAsicLedIndicateInfoConfig: group fail\n");
		return FAILED;
	}	

	/* Get register value */
	retVal = rtl8366s_getAsicReg(RTL8366S_LED_INDICATED_CONF_REG, &regValue); 	
	if (retVal !=  SUCCESS) {
		DEBUG_MSG("rtl8366s_getAsicLedIndicateInfoConfig: rtl8366s_getAsicReg fail\n"); 
		return retVal;
	}
	
	*config = (regValue >> (ledNo*4)) & 0x000F;
		
	return SUCCESS;
}

/*
@func uint32_t | rtl8366s_setAsicForceLeds | Turn on/off Led of dedicated port
@parm uint32_t | ledG0Msk | Turn on or turn off Leds of group 0, 1:on 0:off.
@parm uint32_t | ledG1Msk | Turn on or turn off Leds of group 1, 1:on 0:off.
@parm uint32_t | ledG2Msk | Turn on or turn off Leds of group 2, 1:on 0:off.
@parm uint32_t | ledG3Msk | Turn on or turn off Leds of group 3, 1:on 0:off.
@rvalue SUCCESS | Success.
@rvalue ERRNO_SMIERROR | SMI access error.
@comm
	The API can turn on/off desired Led group of dedicated port while indicated information configuration of LED group is set to force mode.
 */
uint32_t rtl8366s_setAsicForceLeds(uint32_t ledG0Msk, uint32_t ledG1Msk, uint32_t ledG2Msk, uint32_t ledG3Msk)
{
	uint32_t retVal, regValue;

	regValue = (ledG0Msk & 0x3F) | (ledG1Msk&0x3F) << 6;

	retVal = rtl8366s_setAsicReg(RTL8366S_LED_0_1_FORCE_REG, regValue); 	
	if(retVal != SUCCESS){
		DEBUG_MSG("rtl8366s_setAsicForceLeds: rtl8366s_setAsicReg fail\n"); 
		return retVal;
	}	

	regValue = (ledG2Msk & 0x3F) | (ledG3Msk&0x3F) << 6;
	retVal = rtl8366s_setAsicReg(RTL8366S_LED_2_3_FORCE_REG, regValue); 	
	
	return retVal;
}
#endif//LED_SET//*********************************************

/*
@func uint32_t | rtl8366s_initChip | Set chip to default configuration enviroment
@rvalue SUCCESS | Success.
@rvalue FAILED | Failure.
@comm
	The API can set chip registers to default configuration for different release chip model.
*/
uint32_t rtl8366s_initChip(void)
{
	uint32_t index;
	uint32_t regData;
#ifdef LED_SET
	uint32_t ledGroup;
	enum RTL8366S_LEDCONF ledCfg[RTL8366S_LED_GROUP_MAX];
#endif	

	DEBUG_MSG("rtl8366s_initChip\n");
		
	//const uint32_t chipB[][2] = {{0x0000,	0x0038},{0x8100,	0x1B37},{0xBE2E,	0x7B9F},{0xBE2B,	0xA4C8},
	static uint32_t chipB[][2] = {{0x0000,	0x0038},{0x8100,	0x1B37},{0xBE2E,	0x7B9F},{0xBE2B,	0xA4C8},
							{0xBE74,	0xAD14},{0xBE2C,	0xDC00},{0xBE69,	0xD20F},{0xBE3B,	0xB414},
							{0xBE24,	0x0000},{0xBE23,	0x00A1},{0xBE22,	0x0008},{0xBE21,	0x0120},
							{0xBE20,	0x1000},{0xBE24,	0x0800},{0xBE24,	0x0000},{0xBE24,	0xF000},
							{0xBE23,	0xDF01},{0xBE22,	0xDF20},{0xBE21,	0x101A},{0xBE20,	0xA0FF},
							{0xBE24,	0xF800},{0xBE24,	0xF000},{0x0242,	0x02BF},{0x0245,	0x02BF},
							{0x0248,	0x02BF},{0x024B,	0x02BF},{0x024E,	0x02BF},{0x0251,	0x02BF},
							{0x0230,	0x0A32},{0x0233,	0x0A32},{0x0236,	0x0A32},{0x0239,	0x0A32},
							{0x023C,	0x0A32},{0x023F,	0x0A32},{0x0254,	0x0A3F},{0x0255,	0x0064},
							{0x0256,	0x0A3F},{0x0257,	0x0064},{0x0258,	0x0A3F},{0x0259,	0x0064},
							{0x025A,	0x0A3F},{0x025B,	0x0064},{0x025C,	0x0A3F},{0x025D,	0x0064},
							{0x025E,	0x0A3F},{0x025F,	0x0064},{0x0260,	0x0178},{0x0261,	0x01F4},
							{0x0262,	0x0320},{0x0263,	0x0014},{0x021D,	0x9249},{0x021E,	0x0000},
							{0x0100,	0x0004},{0xBE4A,	0xA0B4},{0xBE40,	0x9C00},{0xBE41,	0x501D},
							{0xBE48,	0x3602},{0xBE47,	0x8051},{0xBE4C,	0x6465},{0x8000,	0x1F00},
							{0x8001,	0x000C},{0x8008,	0x0000},{0x8007,	0x0000},{0x800C,	0x00A5},
							{0x8101,	0x02BC},{0xBE53,	0x0005},{0x8E45,	0xAFE8},{0x8013,	0x0005},
							{0xBE4B,	0x6700},{0x800B,	0x7000},{0xBE09,	0x0E00},
							{0xFFFF, 0xABCD}};
	/* Sample code start (fix to port 2-4 link issue from Realtek) */	
	//const uint32_t chipDefault[][2] = {{0x0242, 0x02BF},{0x0245, 0x02BF},{0x0248, 0x02BF},{0x024B, 0x02BF},	
	static uint32_t chipDefault[][2] = {{0x0242, 0x02BF},{0x0245, 0x02BF},{0x0248, 0x02BF},{0x024B, 0x02BF},
								{0x024E, 0x02BF},{0x0251, 0x02BF},
								{0x0254, 0x0A3F},{0x0256, 0x0A3F},{0x0258, 0x0A3F},{0x025A, 0x0A3F},
								{0x025C, 0x0A3F},{0x025E, 0x0A3F},
								{0x0263, 0x007C},{0x0100,	0x0004},									
								{0xBE5B, 0x3500},{0x800E, 0x200F},{0xBE1D, 0x0F00},{0x8001, 0x5011},
								{0x800A, 0xA2F4},{0x800B, 0x17A3},{0xBE4B, 0x17A3},{0xBE41, 0x5011},
								{0xBE17, 0x2100},{0x8000, 0x8304},{0xBE40, 0x8304},{0xBE4A, 0xA2F4},
								{0x800C, 0xA8D5},{0x8014, 0x5500},{0x8015, 0x0004},{0xBE4C, 0xA8D5},
								{0xBE59, 0x0008},{0xBE09, 0x0E00},{0xBE36, 0x1036},{0xBE37, 0x1036},
								{0x800D, 0x00FF},{0xBE4D, 0x00FF},
								{0xFFFF, 0xABCD}};	

#ifdef LED_SET
	DEBUG_MSG("rtl8366s_initChip Led setting\n");
	for(ledGroup= 0;ledGroup<RTL8366S_LED_GROUP_MAX;ledGroup++)
	{
		if(SUCCESS != rtl8366s_getAsicLedIndicateInfoConfig(ledGroup,&ledCfg[ledGroup])){
			DEBUG_MSG("rtl8366s_getAsicLedIndicateInfoConfig fail\n");
			return FAILED;
		}	

		if(SUCCESS != rtl8366s_setAsicLedIndicateInfoConfig(ledGroup,LEDCONF_LEDFORCE)){
			DEBUG_MSG("rtl8366s_setAsicLedIndicateInfoConfig fail\n");
			return FAILED;
		}	
	}

	if(SUCCESS != rtl8366s_setAsicForceLeds(0x3F,0x3F,0x3F,0x3F)){
		DEBUG_MSG("rtl8366s_setAsicForceLeds fail\n"); 
		return FAILED;
	}	
#endif
	/*resivion*/
	if(SUCCESS != rtl8366s_getAsicReg(0x5C,&regData)){
		DEBUG_MSG("rtl8366s_getAsicReg fail\n"); 
		return FAILED;
	}	

	index = 0;
	switch(regData)
	{
 	 case 0x0000:	
		DEBUG_MSG("0x0000\n");
		while(chipB[index][0] != 0xFFFF && chipB[index][1] != 0xABCD)
		{	
			/*PHY registers setting*/	
			if(0xBE00 == (chipB[index][0] & 0xBE00))
			{
				if(SUCCESS != rtl8366s_setAsicReg(RTL8366S_PHY_ACCESS_CTRL_REG, RTL8366S_PHY_CTRL_WRITE)){
					DEBUG_MSG("rtl8366s_setAsicReg fail\n");
					return FAILED;
				}	
			}

			if(SUCCESS != rtl8366s_setAsicReg(chipB[index][0],chipB[index][1])){
				DEBUG_MSG("rtl8366s_setAsicReg2 fail\n");
				return FAILED;
			}	
			
			index ++;	
		}			
		break;
 	 case 0x6027:	
 	 	DEBUG_MSG("0x6027\n");
		while(chipDefault[index][0] != 0xFFFF && chipDefault[index][1] != 0xABCD)
		{	
			/*PHY registers setting*/	
			if(0xBE00 == (chipDefault[index][0] & 0xBE00))
			{
				if(SUCCESS != rtl8366s_setAsicReg(RTL8366S_PHY_ACCESS_CTRL_REG, RTL8366S_PHY_CTRL_WRITE)){
					DEBUG_MSG("rtl8366s_setAsicReg fail\n");
					return FAILED;
				}	

			}

			if(SUCCESS != rtl8366s_setAsicReg(chipDefault[index][0],chipDefault[index][1])){
				DEBUG_MSG("rtl8366s_setAsicReg2 fail\n");
				return FAILED;
			}	
			
			index ++;	
		}			
		break;
	 default:
	 	DEBUG_MSG("unknow\n");
		return FAILED;
		break;
	}
	
	mdelay(1000);	
#ifdef LED_SET
	for(ledGroup= 0;ledGroup<RTL8366S_LED_GROUP_MAX;ledGroup++)
	{
		if(SUCCESS != rtl8366s_setAsicLedIndicateInfoConfig(ledGroup,ledCfg[ledGroup])){
			DEBUG_MSG("rtl8366s_setAsicLedIndicateInfoConfig2 fail\n");
			return FAILED;
		}	
			
	}
#endif
	return SUCCESS;
}

/****************************************************************************/
/******************************************************************************
*
* rtl8366sr_phy_is_link_alive - test to see if the specified link is alive
*
* RETURNS:
*    TRUE  --> link is alive
*    FALSE --> link is down
*/

BOOL rtl8366sr_phy_is_link_alive(int phyUnit)
{
    uint32_t regData;
    
	//DEBUG_MSG("rtl8366sr_phy_is_link_alive %d\n",phyUnit);
#if 0	
	rtl8366s_getPHYLinkStatus(phyUnit,&regData);
    	
    if(regData)
    	return TRUE;
    else
    	return FALSE;
#else
	return TRUE;
#endif    	
}

/******************************************************************************
*
* rtl8366sr_phy_setup - reset and setup the PHY associated with
* the specified MAC unit number.
*
* Resets the associated PHY port.
*
* RETURNS:
*    TRUE  --> associated PHY is alive
*    FALSE --> no LINKs on this ethernet unit
*/
/******************************************************************************/
static int init_first = 0;
int
rtl8366sr_phy_setup(int ethUnit)
{
    int     phyUnit;
    uint32_t  phyHwStatus;
    uint16_t  timeout;
    int     liveLinks = 0;    
    BOOL    foundPhy = FALSE;
    rtlPhyInfo_t *lastStatus;
    enum PORTLINKSPEED speed=0;
    enum PORTLINKDUPLEXMODE duplex=0;
    uint32_t link=0,txPause=0,rxPause=0,autoNegotiation=0; 
    phyAbility_t pability;
    
    /* See if there's any configuration data for this enet */
    /* start auto negogiation on each phy */
    printk("rtl8366sr_phy_setup  ethUnit=%x\n", ethUnit);     
    

#if 1//swith init    
    if(!init_first){
    	//smi_reset();
    	smi_init();
    
		switch_reg_read(RTL8366S_CHIP_ID_REG,&phyHwStatus);
		switch_reg_read(RTL8366S_CHIP_ID_REG,&phyHwStatus);
		DEBUG_MSG("Realtek 8366SR switch ID 0x%x\n", phyHwStatus);//0x8366
		if(phyHwStatus==0x8366)
			liveLinks++;
		
		rtl8366s_initChip();	
		mdelay(4000);

	
#ifdef CPU_PORT	//FOR VLAN MUST
	/* Set port 5 noTag and don't dropUnda */	
		rtl8366s_setCPUPort(PORT5, 1, 0);	
#ifdef GET_INFO
		rtl8366s_getCPUPort(&speed,&duplex,&link);
#endif		
#ifdef VLAN_SET
	printk("VLAN_SET\n",PORT0);
		rtl8366s_initVlan();
		// LAN - VLAN2 : port 1,2,3,4,5
		rtl8366s_setVlan(LAN_PORTID, 0x3e, 0x1e);
//		rtl8366s_setVlan(LAN_PORTID, 0x3f, 0x1f);//modify by CH
		// WAN(DMZ) - VLAN1 : port 0,5
		rtl8366s_setVlan(DMZ_PORTID, 0x21, 0x01);
//		rtl8366s_setVlan(DMZ_PORTID, 0x20, 0x01);//modify by CH
		//PVID 1 for Port 0, PVID 2 for Port 1~5 
		rtl8366s_setVlanPVID(0, DMZ_PORTID, 0);
//		rtl8366s_setVlanPVID(0, LAN_PORTID, 0);	//modify by CH
		rtl8366s_setVlanPVID(1, LAN_PORTID, 0); 
		rtl8366s_setVlanPVID(2, LAN_PORTID, 0); 
		rtl8366s_setVlanPVID(3, LAN_PORTID, 0);
		rtl8366s_setVlanPVID(4, LAN_PORTID, 0); 
		rtl8366s_setVlanPVID(5, LAN_PORTID, 0);
#endif

#if 0//USED_DMZ   
#if 0 
	printk("port%x USED_DMZ\n",PORT0);
    rtl8366s_setAsicMacForceLink(PORT0,1,SPD_1000M,FULL_DUPLEX,0,1,1);
#else
	printk("port1~4 USED_DMZ\n");
    rtl8366s_setAsicMacForceLink(PORT1,1,SPD_1000M,FULL_DUPLEX,0,1,1);
    rtl8366s_setAsicMacForceLink(PORT2,1,SPD_1000M,FULL_DUPLEX,0,1,1);
    rtl8366s_setAsicMacForceLink(PORT3,1,SPD_1000M,FULL_DUPLEX,0,1,1);
    rtl8366s_setAsicMacForceLink(PORT4,1,SPD_1000M,FULL_DUPLEX,0,1,1);
#endif    
#endif 

#endif//CPU_PORT		
	/* Enable CPU port - forced speed, full duplex and flow control */
#ifdef CFG_SP1000
		DEBUG_MSG("SP1000\n");	
		rtl8366s_setMac5ForceLink(SPD_1000M,FULL_DUPLEX,1,1,1);	
#ifdef GET_INFO
		rtl8366s_getMac5ForceLink(&speed,&duplex,&link,&txPause,&rxPause);	
#endif	
#else //100
		DEBUG_MSG("SP100\n");	
		rtl8366s_setMac5ForceLink(SPD_100M,FULL_DUPLEX,1,1,1);
#ifdef GET_INFO
		rtl8366s_getMac5ForceLink(&speed,&duplex,&link,&txPause,&rxPause);	
#endif	
#endif//CFG_SP1000	
		init_first =1;
	}
#endif//1

#if 0	
    for (phyUnit=0; phyUnit < REALTEK_MAX_PORT_ID; phyUnit++) {
        if (!RTL_IS_ETHUNIT(phyUnit, ethUnit)) {
            continue;
        } 
        
        foundPhy = TRUE;       
       
 		if (phyUnit != 4){//lan 
 			DEBUG_MSG("rtl8366sr_phy_setup: phyUnit=%x auto ability is all\n",phyUnit);      
#if 1
#if 0//lan			
 			pability.AutoNegotiation=1;
			pability.Half_10=1;		
			pability.Full_10=1;	
			pability.Half_100=1;		
			pability.Full_100=1;		
			pability.Full_1000=1;	
			pability.FC=1;			
			pability.AsyFC=1;
			//DEBUG_MSG("rtl8366sr_phy_setup: pability auto=%x,h10=%x,f10=%x,h100=%x,\n",pability.AutoNegotiation,pability.Half_10,pability.Full_10,pability.Half_100);
			//DEBUG_MSG("rtl8366sr_phy_setup: pability f100=%x,f1000=%x,fc=%x,asfc=%x\n",pability.Full_100,pability.Full_1000,pability.FC,pability.AsyFC); 	
			/* ability all */	
       		rtl8366s_setEthernetPHY(phyUnit,pability);
#else
			rtl8366s_setAsicPHYRegs(phyUnit,0, MII_CONTROL_REG, (1<<MII_CONTROL_RENEG)|(1<<MII_CONTROL_AUTONEG));
        	//rtl8366s_getAsicPHYRegs(phyUnit,0,MII_CONTROL_REG,&phyHwStatus);       
        	//while ( (phyHwStatus & (1<<MII_CONTROL_RESET)) || (!(phyHwStatus & (1<<5))) ) {}	   		     
#endif 
#endif      		 	
    	}else{
        	if(wan_speed == NULL  || !strcmp(wan_speed, "auto")){
	      		DEBUG_MSG("rtl8366sr_phy_setup: phyUnit=%x auto ability is all\n",phyUnit);
#if 1
#if 0//wan
        		pability.AutoNegotiation=1;
				pability.Half_10=1;		
				pability.Full_10=1;	
				pability.Half_100=1;		
				pability.Full_100=1;		
				pability.Full_1000=1;	
				pability.FC=1;			
				pability.AsyFC=1;
				//DEBUG_MSG("rtl8366sr_phy_setup: pability auto=%x,h10=%x,f10=%x,h100=%x,\n",pability.AutoNegotiation,pability.Half_10,pability.Full_10,pability.Half_100);
				//DEBUG_MSG("rtl8366sr_phy_setup: pability f100=%x,f1000=%x,fc=%x,asfc=%x\n",pability.Full_100,pability.Full_1000,pability.FC,pability.AsyFC); 		
				/* ability all */	
       			rtl8366s_setEthernetPHY(phyUnit,pability); 
#else       			
       			rtl8366s_setAsicPHYRegs(phyUnit,0, MII_CONTROL_REG, (1<<MII_CONTROL_RENEG)|(1<<MII_CONTROL_AUTONEG));
        		//rtl8366s_getAsicPHYRegs(phyUnit,0,MII_CONTROL_REG,&phyHwStatus);       
        		//while ( (phyHwStatus & (1<<MII_CONTROL_RESET)) || (!(phyHwStatus & (1<<5))) ) {}	   		
#endif       			
#endif
       		}else if(!strcmp(wan_speed, "giga")){
       			DEBUG_MSG("rtl8366sr_phy_setup: phyUnit=%x auto ability is 1000 full\n",phyUnit);
        	    pability.AutoNegotiation=1;
				pability.Half_10=0;		
				pability.Full_10=0;	
				pability.Half_100=0;		
				pability.Full_100=0;		
				pability.Full_1000=1;	
				pability.FC=1;			
				pability.AsyFC=1;
				//DEBUG_MSG("rtl8366sr_phy_setup: pability auto=%x,h10=%x,f10=%x,h100=%x,\n",pability.AutoNegotiation,pability.Half_10,pability.Full_10,pability.Half_100);
				//DEBUG_MSG("rtl8366sr_phy_setup: pability f100=%x,f1000=%x,fc=%x,asfc=%x\n",pability.Full_100,pability.Full_1000,pability.FC,pability.AsyFC); 						
       			rtl8366s_setEthernetPHY(phyUnit,pability);  	       		
       		}else if(!strcmp(wan_speed, "100full"))	{
       			DEBUG_MSG("rtl8366sr_phy_setup: phyUnit=%x auto ability is 100 full\n",phyUnit);
        	    pability.AutoNegotiation=1;
				pability.Half_10=0;		
				pability.Full_10=0;	
				pability.Half_100=0;		
				pability.Full_100=1;		
				pability.Full_1000=0;	
				pability.FC=1;			
				pability.AsyFC=1;	
				//DEBUG_MSG("rtl8366sr_phy_setup: pability auto=%x,h10=%x,f10=%x,h100=%x,\n",pability.AutoNegotiation,pability.Half_10,pability.Full_10,pability.Half_100);
				//DEBUG_MSG("rtl8366sr_phy_setup: pability f100=%x,f1000=%x,fc=%x,asfc=%x\n",pability.Full_100,pability.Full_1000,pability.FC,pability.AsyFC); 					
       			rtl8366s_setEthernetPHY(phyUnit,pability);   
        	}else if(!strcmp(wan_speed, "10full")) {
        		DEBUG_MSG("rtl8366sr_phy_setup: phyUnit=%x auto ability is 10 full\n",phyUnit);
       	   	   	pability.AutoNegotiation=1;
				pability.Half_10=0;		
				pability.Full_10=1;	
				pability.Half_100=0;		
				pability.Full_100=0;		
				pability.Full_1000=0;	
				pability.FC=1;			
				pability.AsyFC=1;
				//DEBUG_MSG("rtl8366sr_phy_setup: pability auto=%x,h10=%x,f10=%x,h100=%x,\n",pability.AutoNegotiation,pability.Half_10,pability.Full_10,pability.Half_100);
				//DEBUG_MSG("rtl8366sr_phy_setup: pability f100=%x,f1000=%x,fc=%x,asfc=%x\n",pability.Full_100,pability.Full_1000,pability.FC,pability.AsyFC); 						
       			rtl8366s_setEthernetPHY(phyUnit,pability);   
       	   	}
		}		
        /* Reset PHYs*/
		//rtl8366s_setAsicPHYRegs(phyUnit,0, MII_CONTROL_REG, (1<<MII_CONTROL_RESET)|(1<<MII_CONTROL_AUTONEG));
        //rtl8366s_getAsicPHYRegs(phyUnit,0,MII_CONTROL_REG,&phyHwStatus);       
        //while ( (phyHwStatus & (1<<MII_CONTROL_RESET)) || (!(phyHwStatus & (1<<5))) ) {}
    }//end for

    if (!foundPhy) {
    	DEBUG_MSG("rtl8366sr_phy_setup: no fhy find\n");
        return FALSE; /* No PHY's configured for this ethUnit */
    }
   
     /*
     * After the phy is reset, it takes a little while before
     * it can respond properly.
     */
    mdelay(3000); 
//#endif    
    
    /*
     * Wait up to 3 seconds for ALL associated PHYs to finish
     * autonegotiation.  The only way we get out of here sooner is
     * if ALL PHYs are connected AND finish autonegotiation.
     */
//#if 0     
    for (phyUnit=0; phyUnit < REALTEK_MAX_PORT_ID; phyUnit++) {
        if (!RTL_IS_ETHUNIT(phyUnit, ethUnit)) {
            continue;
        }        
 	
        timeout=20;
        for (;;) {
            rtl8366s_getAsicPHYRegs(phyUnit,0,MII_CONTROL_REG,&phyHwStatus);
            if (phyHwStatus & (1<<5) ) {
                DEBUG_MSG("rtl8366sr_phy_setup: phyUnit=%x auto Success\n",phyUnit);                
                break;
            }
            if (timeout == 0) {
                DEBUG_MSG("rtl8366sr_phy_setup: phyUnit=%x auto timeout\n",phyUnit);                         
                break;
            }
            if (--timeout == 0) {
                DEBUG_MSG("rtl8366sr_phy_setup: phyUnit=%x auto --timeout\n",phyUnit); 
                break;
            }
            mdelay(150);
        }
    }
    
	mdelay(2000);
#endif	
    /*
     * All PHYs have had adequate time to autonegotiate.
     * Now initialize software status.
     *
     * It's possible that some ports may take a bit longer
     * to autonegotiate; but we can't wait forever.  They'll
     * get noticed by mv_phyCheckStatusChange during regular
     * polling activities.
     */
    for (phyUnit=0; phyUnit < REALTEK_MAX_PORT_ID; phyUnit++) {
        if (!RTL_IS_ETHUNIT(phyUnit, ethUnit)) {
            continue;
        } 
        
		lastStatus = &rtlPhyInfo[phyUnit];
		
        if (rtl8366sr_phy_is_link_alive(phyUnit)) {
            liveLinks++;
            DEBUG_MSG("phyUnit=%x is link\n", phyUnit);
            lastStatus->isPhyAlive = TRUE;
        } else {
        	DEBUG_MSG("phyUnit=%x is lostlink\n", phyUnit);
            lastStatus->isPhyAlive = FALSE;
        }
#if 0        
		rtl8366s_getAsicPortLinkState(phyUnit,&speed,&duplex,&link,&txPause,&rxPause,&autoNegotiation);
        DEBUG_MSG("PHY port[%d] init state:", phyUnit);
        rtl8366s_getAsicPHYRegs(phyUnit,0,MII_CONTROL_REG,&phyHwStatus);
        DEBUG_MSG("\nBasic Control: REG[0] = 0x%hx",phyHwStatus);
        rtl8366s_getAsicPHYRegs(phyUnit,0,MII_STATUS_REG,&phyHwStatus);
        DEBUG_MSG("\nBasic Status:  REG[1] = 0x%hx",phyHwStatus);
        rtl8366s_getAsicPHYRegs(phyUnit,0,MII_PHY_ID0,&phyHwStatus);
        DEBUG_MSG("\nPHY ID  :      REG[2] = 0x%hx",phyHwStatus);
        rtl8366s_getAsicPHYRegs(phyUnit,0,MII_PHY_ID1,&phyHwStatus);
        DEBUG_MSG("\n               REG[3] = 0x%hx",phyHwStatus);
        rtl8366s_getAsicPHYRegs(phyUnit,0,MII_LOCAL_CAP,&phyHwStatus);
        DEBUG_MSG("\nAutoNeg Local: REG[4] = 0x%hx",phyHwStatus);
        rtl8366s_getAsicPHYRegs(phyUnit,0,MII_REMOTE_CAP,&phyHwStatus);
        DEBUG_MSG("\n       Remote: REG[5] = 0x%hx",phyHwStatus);
        rtl8366s_getAsicPHYRegs(phyUnit,0,MII_GIGA_CONTROL,&phyHwStatus);
        DEBUG_MSG("\nGiga Control:  REG[9] = 0x%hx",phyHwStatus);
        rtl8366s_getAsicPHYRegs(phyUnit,0,MII_GIGA_STATUS,&phyHwStatus);
        DEBUG_MSG("\n     Status:   REG[A] = 0x%hx\n",phyHwStatus);   
#endif
    }
	
#if 0//GET_INFO
    switch_reg_read(0x60,&phyHwStatus);
    DEBUG_MSG("0x60=0x%x\n", phyHwStatus);
    switch_reg_read(0x61,&phyHwStatus);
    DEBUG_MSG("0x61=0x%x\n", phyHwStatus);
    switch_reg_read(0x62,&phyHwStatus);
    DEBUG_MSG("0x62=0x%x\n", phyHwStatus);	
#endif 	
    return (liveLinks > 0);
}

void  rtl8366sr_phy_set(int phyUnit, uint16_t status)	
{
	uint32_t phyHwStatus;
	phyAbility_t pability;
		
	DEBUG_MSG("\n\nrtl8366sr_phy_set ethUnit=%x,status=%x\n\n", phyUnit, status);
	switch(status)
	{   	   
	   case 0x10: //VCTSETPORTSPEED_AUTO
	   		DEBUG_MSG("rtl8366sr_phy_set: phyUnit=%x auto ability is auto\n",phyUnit);
#if 1
	   		pability.AutoNegotiation=1;
			pability.Half_10=1;		
			pability.Full_10=1;	
			pability.Half_100=1;		
			pability.Full_100=1;		
			pability.Full_1000=1;	
			pability.FC=1;			
			pability.AsyFC=1;
			//DEBUG_MSG("rtl8366sr_phy_setup: pability auto=%x,h10=%x,f10=%x,h100=%x,\n",pability.AutoNegotiation,pability.Half_10,pability.Full_10,pability.Half_100);
			//DEBUG_MSG("rtl8366sr_phy_setup: pability f100=%x,f1000=%x,fc=%x,asfc=%x\n",pability.Full_100,pability.Full_1000,pability.FC,pability.AsyFC); 	
			/* ability all */	
       		rtl8366s_setEthernetPHY(phyUnit,pability);
#else
	   		rtl8366s_setAsicPHYRegs(phyUnit,0, MII_CONTROL_REG, (1<<MII_CONTROL_RENEG)|(1<<MII_CONTROL_AUTONEG));
        	//rtl8366s_getAsicPHYRegs(phyUnit,0,MII_CONTROL_REG,&phyHwStatus);       
        	//while ( (phyHwStatus & (1<<MII_CONTROL_RESET)) || (!(phyHwStatus & (1<<5))) ) {}	   		
#endif
	   break;
	   case 0x80: //VCTSETPORTSPEED_10HALF 
			DEBUG_MSG("rtl8366sr_phy_set: phyUnit=%x auto ability is 10 half\n",phyUnit);
       	   	pability.AutoNegotiation=1;
			pability.Half_10=1;		
			pability.Full_10=0;	
			pability.Half_100=0;		
			pability.Full_100=0;		
			pability.Full_1000=0;	
			pability.FC=1;			
			pability.AsyFC=1;					
       		rtl8366s_setEthernetPHY(phyUnit,pability);   			
	   break;
	   case 0x81: //VCTSETPORTSPEED_10FULL
			DEBUG_MSG("rtl8366sr_phy_set: phyUnit=%x auto ability is 10 full\n",phyUnit);
       	   	pability.AutoNegotiation=1;
			pability.Half_10=0;		
			pability.Full_10=1;	
			pability.Half_100=0;		
			pability.Full_100=0;		
			pability.Full_1000=0;	
			pability.FC=1;			
			pability.AsyFC=1;					
       		rtl8366s_setEthernetPHY(phyUnit,pability); 
       		//rtl8366s_setAsicPHYRegs(phyUnit,0, MII_CONTROL_REG, (1<<MII_CONTROL_RESET)|(1<<MII_CONTROL_AUTONEG));
        	//rtl8366s_getAsicPHYRegs(phyUnit,0,MII_CONTROL_REG,&phyHwStatus);       
        	//while ( (phyHwStatus & (1<<MII_CONTROL_RESET)) || (!(phyHwStatus & (1<<5))) ) {}  
	   break;
	   case 0xa0: //VCTSETPORTSPEED_100HALF
			DEBUG_MSG("rtl8366sr_phy_set: phyUnit=%x auto ability is 100 half\n",phyUnit);
       	   	pability.AutoNegotiation=1;
			pability.Half_10=0;		
			pability.Full_10=0;	
			pability.Half_100=1;		
			pability.Full_100=0;		
			pability.Full_1000=0;	
			pability.FC=1;			
			pability.AsyFC=1;					
       		rtl8366s_setEthernetPHY(phyUnit,pability);   	
	   break;
	   case 0xa1: //VCTSETPORTSPEED_100FULL
        	DEBUG_MSG("rtl8366sr_phy_set: phyUnit=%x auto ability is 100 full\n",phyUnit);
       	   	pability.AutoNegotiation=1;
			pability.Half_10=0;		
			pability.Full_10=0;	
			pability.Half_100=0;		
			pability.Full_100=1;		
			pability.Full_1000=0;	
			pability.FC=1;			
			pability.AsyFC=1;					
       		rtl8366s_setEthernetPHY(phyUnit,pability); 
       		//rtl8366s_setAsicPHYRegs(phyUnit,0, MII_CONTROL_REG, (1<<MII_CONTROL_RESET)|(1<<MII_CONTROL_AUTONEG));
        	//rtl8366s_getAsicPHYRegs(phyUnit,0,MII_CONTROL_REG,&phyHwStatus);       
        	//while ( (phyHwStatus & (1<<MII_CONTROL_RESET)) || (!(phyHwStatus & (1<<5))) ) {}  
	   break;
	   case 6: //VCTSETPORTSPEED_1000FULL
        	DEBUG_MSG("rtl8366sr_phy_set: phyUnit=%x auto ability is 100 full\n",phyUnit);
       	   	pability.AutoNegotiation=1;
			pability.Half_10=0;		
			pability.Full_10=0;	
			pability.Half_100=0;		
			pability.Full_100=0;		
			pability.Full_1000=1;	
			pability.FC=1;			
			pability.AsyFC=1;					
       		rtl8366s_setEthernetPHY(phyUnit,pability); 
       		//rtl8366s_setAsicPHYRegs(phyUnit,0, MII_CONTROL_REG, (1<<MII_CONTROL_RESET)|(1<<MII_CONTROL_AUTONEG));
        	//rtl8366s_getAsicPHYRegs(phyUnit,0,MII_CONTROL_REG,&phyHwStatus);       
        	//while ( (phyHwStatus & (1<<MII_CONTROL_RESET)) || (!(phyHwStatus & (1<<5))) ) {}  
	   break;
	   default:
	   	DEBUG_MSG("************************************wrong val =0x%x",status);
	   break;		   	   	   	
	}
    mdelay(3000);
}


/******************************************************************************
*
* rtl8366sr_phy_is_fdx - Determines whether the phy ports associated with the
* specified device are FULL or HALF duplex.
*
* RETURNS:
*    1  --> FULL
*    0 --> HALF
*/
int
rtl8366sr_phy_is_fdx(int ethUnit)
{
    int	phyUnit;  	    
    
    //DEBUG_MSG("rtl8366sr_phy_is_fdx ethUnit=%d\n",ethUnit);      
#ifdef CFG_SP1000
	if(!ethUnit)
		return TRUE;
		
	for (phyUnit=0; phyUnit < REALTEK_MAX_PORT_ID; phyUnit++) {
        if (!RTL_IS_ETHUNIT(phyUnit, ethUnit)) {
            continue;
        }  
        //DEBUG_MSG("rtl8366sr_phy_is_fdx phyUnit=%x\n",phyUnit);       
        if (rtl8366sr_phy_is_link_alive(phyUnit)) {
        	//DEBUG_MSG("phyUnit=%x is link\n",phyUnit);
			uint32_t link_status_giga;
			uint32_t local_cap,remote_cap,common_cap;
			
			rtl8366s_getAsicPHYRegs(phyUnit,0,MII_GIGA_STATUS,&link_status_giga);
			rtl8366s_getAsicPHYRegs(phyUnit,0,MII_LOCAL_CAP,&local_cap);
			rtl8366s_getAsicPHYRegs(phyUnit,0,MII_REMOTE_CAP,&remote_cap);
        	common_cap = (local_cap & remote_cap);
        	
        	if (link_status_giga & (1 << MII_GIGA_STATUS_FULL)) {//
            	return TRUE;
            	//link_speed = 1000;
        	} else if (link_status_giga & (1 << MII_GIGA_STATUS_HALF)) {
            	return FALSE;
            	//link_speed = 1000;
        	} else {
            	if (common_cap & (1 << MII_CAP_100BASE_TX_FULL)) {
                	return TRUE;
                	//link_speed = 100;
            	} else if (common_cap & (1 << MII_CAP_100BASE_TX)) {
                	return FALSE;
                	//link_speed = 100;
            	} else if (common_cap & (1 << MII_CAP_10BASE_TX_FULL)) {
                	return TRUE;
                	//link_speed = 10;
           	 	} else  {
                	return FALSE;
                	//link_speed = 10;
           		}
        	}
           
        }
        //else{
        	//DEBUG_MSG("phyUnit=%x is lostlink\n",phyUnit);
        //}	
    }
#else  	
   	if(!ethUnit)
		return TRUE;
    
    for (phyUnit=0; phyUnit < REALTEK_MAX_PORT_ID; phyUnit++) {
        if (!RTL_IS_ETHUNIT(phyUnit, ethUnit)) {
            continue;
        }  
               
        if (rtl8366sr_phy_is_link_alive(phyUnit)) {
        	//DEBUG_MSG("phyUnit=%x is link\n",phyUnit);
			uint32_t link_status_giga;
			uint32_t local_cap,remote_cap,common_cap;
			
			rtl8366s_getAsicPHYRegs(phyUnit,0,MII_GIGA_STATUS,&link_status_giga);
			rtl8366s_getAsicPHYRegs(phyUnit,0,MII_LOCAL_CAP,&local_cap);
			rtl8366s_getAsicPHYRegs(phyUnit,0,MII_REMOTE_CAP,&remote_cap);
        	common_cap = (local_cap & remote_cap);
        	
        	if (link_status_giga & (1 << MII_GIGA_STATUS_FULL)) {//
            	return TRUE;
            	//link_speed = 1000;
        	} else if (link_status_giga & (1 << MII_GIGA_STATUS_HALF)) {
            	return FALSE;
            	//link_speed = 1000;
        	} else {
            	if (common_cap & (1 << MII_CAP_100BASE_TX_FULL)) {
                	return TRUE;
                	//link_speed = 100;
            	} else if (common_cap & (1 << MII_CAP_100BASE_TX)) {
                	return FALSE;
                	//link_speed = 100;
            	} else if (common_cap & (1 << MII_CAP_10BASE_TX_FULL)) {
                	return TRUE;
                	//link_speed = 10;
           	 	} else  {
                	return FALSE;
                	//link_speed = 10;
           		}
        	}
           
        }
        //else{
        	//DEBUG_MSG("phyUnit=%x is lostlink\n",phyUnit);
        //}	
    }
#endif    
    return FALSE;
}

/******************************************************************************
*
* rtl8366sr_phy_is_fdx_ext - Determines whether the phy ports associated with the
* specified device are FULL or HALF duplex.
*
* RETURNS:
*    1  --> FULL
*    0 --> HALF
*/
int
rtl8366sr_phy_is_fdx_ext(int phyUnit)
{      	
    
    DEBUG_MSG("rtl8366sr_phy_is_fdx_ext phyUnit=%d\n",phyUnit);  	
    
    if (rtl8366sr_phy_is_link_alive(phyUnit)) {
    	DEBUG_MSG("phyUnit=%x is link\n",phyUnit);
		uint32_t link_status_giga;
		uint32_t local_cap,remote_cap,common_cap;
		
		rtl8366s_getAsicPHYRegs(phyUnit,0,MII_GIGA_STATUS,&link_status_giga);
		rtl8366s_getAsicPHYRegs(phyUnit,0,MII_LOCAL_CAP,&local_cap);
		rtl8366s_getAsicPHYRegs(phyUnit,0,MII_REMOTE_CAP,&remote_cap);
    	common_cap = (local_cap & remote_cap);
    	
    	if (link_status_giga & (1 << MII_GIGA_STATUS_FULL)) {//
        	return TRUE;
        	//link_speed = 1000;
    	} else if (link_status_giga & (1 << MII_GIGA_STATUS_HALF)) {
        	return FALSE;
        	//link_speed = 1000;
    	} else {
        	if (common_cap & (1 << MII_CAP_100BASE_TX_FULL)) {
            	return TRUE;
            	//link_speed = 100;
        	} else if (common_cap & (1 << MII_CAP_100BASE_TX)) {
            	return FALSE;
            	//link_speed = 100;
        	} else if (common_cap & (1 << MII_CAP_10BASE_TX_FULL)) {
            	return TRUE;
            	//link_speed = 10;
       	 	} else  {
            	return FALSE;
            	//link_speed = 10;
       		}
    	}
       
    }
    //else{
    	//DEBUG_MSG("phyUnit=%x is lostlink\n",phyUnit);
    //}	

    return FALSE;
}

/******************************************************************************
*
* rtl8366sr_phy_speed - Determines the speed of phy ports associated with the
* specified device.
*
* RETURNS:
*               AG7100_PHY_SPEED_10T, AG7100_PHY_SPEED_100TX;
*               AG7100_PHY_SPEED_1000T;
*/

int
rtl8366sr_phy_speed(int ethUnit)
{
   int	phyUnit;
   
   //DEBUG_MSG("rtl8366sr_phy_speed ethUnit=%d\n",ethUnit);  	
#ifdef CFG_SP1000
	if(!ethUnit)
		return _1000BASET;
		
	for (phyUnit=0; phyUnit < REALTEK_MAX_PORT_ID; phyUnit++) {
        if (!RTL_IS_ETHUNIT(phyUnit, ethUnit)) {
            continue;
        }  
        //DEBUG_MSG("rtl8366sr_phy_speed phyUnit=%x\n",phyUnit);      
        if (rtl8366sr_phy_is_link_alive(phyUnit)) {
        	//DEBUG_MSG("phyUnit=%x is link\n",phyUnit);
			uint32_t link_status_giga;			
			uint32_t local_cap,remote_cap,common_cap;
#if 0
			int link_control_giga,link_extstat_giga;
#endif			
			rtl8366s_getAsicPHYRegs(phyUnit,0,MII_GIGA_STATUS,&link_status_giga);
			rtl8366s_getAsicPHYRegs(phyUnit,0,MII_LOCAL_CAP,&local_cap);
			rtl8366s_getAsicPHYRegs(phyUnit,0,MII_REMOTE_CAP,&remote_cap);
#if 0			
			rtl8366s_getAsicPHYRegs(phyUnit,0,MII_GIGA_CONTROL,&link_control_giga);
			rtl8366s_getAsicPHYRegs(phyUnit,0,MII_EXT_STATUS_REG,&link_extstat_giga);
			//DEBUG_MSG("c=%x,g=%x,e=%x\n",link_control_giga,link_status_giga,link_extstat_giga);
#endif
        	common_cap = (local_cap & remote_cap);
        	
        	if (link_status_giga & (1 << MII_GIGA_STATUS_FULL)) {//
            	//full_duplex = TRUE;
            	return _1000BASET;
        	} else if (link_status_giga & (1 << MII_GIGA_STATUS_HALF)) {
            	//full_duplex = FALSE;
            	return _1000BASET;
        	} else {
            	if (common_cap & (1 << MII_CAP_100BASE_TX_FULL)) {
                	//full_duplex = TRUE;
                	return _100BASET;
            	} else if (common_cap & (1 << MII_CAP_100BASE_TX)) {
                	//full_duplex = FALSE;
                	return _100BASET;
            	} else if (common_cap & (1 << MII_CAP_10BASE_TX_FULL)) {
                	//full_duplex = TRUE;
                	return _10BASET;
           	 	} else  {
                	//full_duplex = FALSE;
                	return _10BASET;
           		}
        	}
           
        }
        //else{
        	//DEBUG_MSG("phyUnit=%x is lostlink\n",phyUnit);
        //}	
    }    
#else  	

   if(!ethUnit)
		return _100BASET;
		
   for (phyUnit=0; phyUnit < REALTEK_MAX_PORT_ID; phyUnit++) {
        if (!RTL_IS_ETHUNIT(phyUnit, ethUnit)) {
            continue;
        }  
              
        if (rtl8366sr_phy_is_link_alive(phyUnit)) {
        	//DEBUG_MSG("phyUnit=%x is link\n",phyUnit);
			uint32_t link_status_giga;
			uint32_t local_cap,remote_cap,common_cap;
			
			rtl8366s_getAsicPHYRegs(phyUnit,0,MII_GIGA_STATUS,&link_status_giga);
			rtl8366s_getAsicPHYRegs(phyUnit,0,MII_LOCAL_CAP,&local_cap);
			rtl8366s_getAsicPHYRegs(phyUnit,0,MII_REMOTE_CAP,&remote_cap);
        	common_cap = (local_cap & remote_cap);
        	
        	if (link_status_giga & (1 << MII_GIGA_STATUS_FULL)) {//
            	//full_duplex = TRUE;
            	return _1000BASET;
        	} else if (link_status_giga & (1 << MII_GIGA_STATUS_HALF)) {
            	//full_duplex = FALSE;
            	return _1000BASET;
        	} else {
            	if (common_cap & (1 << MII_CAP_100BASE_TX_FULL)) {
                	//full_duplex = TRUE;
                	return _100BASET;
            	} else if (common_cap & (1 << MII_CAP_100BASE_TX)) {
                	//full_duplex = FALSE;
                	return _100BASET;
            	} else if (common_cap & (1 << MII_CAP_10BASE_TX_FULL)) {
                	//full_duplex = TRUE;
                	return _10BASET;
           	 	} else  {
                	//full_duplex = FALSE;
                	return _10BASET;
           		}
        	}
           
        }
        //else{
        	//DEBUG_MSG("phyUnit=%x is lostlink\n",phyUnit);
        //}	
    }    
#endif  
    return _10BASET;
}

/******************************************************************************
*
* rtl8366sr_phy_speed_ext - Determines the speed of phy ports associated with the
* specified device.
*
* RETURNS:
*               AG7100_PHY_SPEED_10T, AG7100_PHY_SPEED_100TX;
*               AG7100_PHY_SPEED_1000T;
*/

int
rtl8366sr_phy_speed_ext(int phyUnit)
{
      
   DEBUG_MSG("rtl8366sr_phy_speed ext phyUnit=%d\n",phyUnit);  	
  	
    if (rtl8366sr_phy_is_link_alive(phyUnit)) {
    	DEBUG_MSG("phyUnit=%x is link\n",phyUnit);
		uint32_t link_status_giga;
		uint32_t local_cap,remote_cap,common_cap;
		
		rtl8366s_getAsicPHYRegs(phyUnit,0,MII_GIGA_STATUS,&link_status_giga);
		rtl8366s_getAsicPHYRegs(phyUnit,0,MII_LOCAL_CAP,&local_cap);
		rtl8366s_getAsicPHYRegs(phyUnit,0,MII_REMOTE_CAP,&remote_cap);
    	common_cap = (local_cap & remote_cap);
    	
    	if (link_status_giga & (1 << MII_GIGA_STATUS_FULL)) {//
        	//full_duplex = TRUE;
        	return _1000BASET;
    	} else if (link_status_giga & (1 << MII_GIGA_STATUS_HALF)) {
        	//full_duplex = FALSE;
        	return _1000BASET;
    	} else {
        	if (common_cap & (1 << MII_CAP_100BASE_TX_FULL)) {
            	//full_duplex = TRUE;
            	return _100BASET;
        	} else if (common_cap & (1 << MII_CAP_100BASE_TX)) {
            	//full_duplex = FALSE;
            	return _100BASET;
        	} else if (common_cap & (1 << MII_CAP_10BASE_TX_FULL)) {
            	//full_duplex = TRUE;
            	return _10BASET;
       	 	} else  {
            	//full_duplex = FALSE;
            	return _10BASET;
       		}
    	}
       
    }
    //else{
    	//DEBUG_MSG("phyUnit=%x is lostlink\n",phyUnit);
    //} 

    return _10BASET;
}

/*****************************************************************************
*
* rtl8366sr_phy_is_up -- checks for significant changes in PHY state.
*
* A "significant change" is:
*     dropped link (e.g. ethernet cable unplugged) OR
*     autonegotiation completed + link (e.g. ethernet cable plugged in)
*
* When a PHY is plugged in, phyLinkGained is called.
* When a PHY is unplugged, phyLinkLost is called.
*/

int
rtl8366sr_phy_is_up(int ethUnit)
{
    int           phyUnit;
    uint32_t      phyHwStatus, phyHwControl;
    rtlPhyInfo_t *lastStatus;
    int           linkCount   = 0;
    int           lostLinks   = 0;
    //int           gainedLinks = 0;    

	//DEBUG_MSG("rtl8366sr_phy_is_up  ethUnit=%x\n", ethUnit); 
#ifdef CFG_SP1000	
		
	for (phyUnit=0; phyUnit < REALTEK_MAX_PORT_ID; phyUnit++) {
        if (!RTL_IS_ETHUNIT(phyUnit, ethUnit)) {
            continue;
        }  
        //DEBUG_MSG("rtl8366sr_phy_is_up phyUnit=%x\n",phyUnit); 
        lastStatus = &rtlPhyInfo[phyUnit];

        if (lastStatus->isPhyAlive) { /* last known link status was ALIVE */
        	//DEBUG_MSG("rtl8366sr_phy_is_up: phyUnit=%x is alive\n", phyUnit);
        	rtl8366s_getAsicPHYRegs(phyUnit,0,MII_STATUS_REG,&phyHwStatus);
			
            /* See if we've lost link */
            if (phyHwStatus & (1<<2)) {
                linkCount++;
                //DEBUG_MSG("phyUnit=%x is link\n", phyUnit);
            } else {
                lostLinks++;
                //DEBUG_MSG("phyUnit=%x is lostlink\n", phyUnit); 
                lastStatus->isPhyAlive = FALSE;
            }
        } else { /* last known link status was DEAD */
            //DEBUG_MSG("rtl8366sr_phy_is_up: phyUnit=%x is dead\n", phyUnit);
            /* Check for reset complete */
            rtl8366s_getAsicPHYRegs(phyUnit,0,MII_CONTROL_REG,&phyHwControl);         
            if (phyHwControl & (1<<MII_CONTROL_RESET))
                continue;
            rtl8366s_getAsicPHYRegs(phyUnit,0,MII_STATUS_REG,&phyHwStatus);
//#if 1   
	  		//if(autoNeg)
	  		{
	  			//DEBUG_MSG("phyUnit=%x is auto\n", phyUnit);
	  			udelay(50);         
            	/* Check for AutoNegotiation complete */            
            	if (/* !(phyHwControl & (1<<12)) || */ (phyHwStatus & (1<<5)) ) {                	
                	rtl8366s_getAsicPHYRegs(phyUnit,0,MII_STATUS_REG,&phyHwStatus);
                	
                	if (phyHwStatus & (1<<2)) {
                		//gainedLinks++;
                		linkCount++;
                		//DEBUG_MSG("phyUnit=%x is link\n", phyUnit);
                		lastStatus->isPhyAlive = TRUE;
            		}
        		}
//#else
	   		}
	   		//else{
	   			//DEBUG_MSG("phyUnit=%x is notauto\n", phyUnit);
            //    rtl8366s_getAsicPHYRegs(phyUnit,0,MII_STATUS_REG,&phyHwStatus);

            //    if (phyHwStatus & (1<<2)) {
                	//gainedLinks++;
            //    	linkCount++;
                	//DEBUG_MSG("phyUnit=%x is link\n", phyUnit);                                               
            //    	lastStatus->isPhyAlive = TRUE;
            //	}
	   		//}//end autoNeg
//#endif        
    	}//lastStatus->isPhyAlive
    }//end for	
#else			
    
    for (phyUnit=0; phyUnit < REALTEK_MAX_PORT_ID; phyUnit++) {
        if (!RTL_IS_ETHUNIT(phyUnit, ethUnit)) {
            continue;
        }  
        
        lastStatus = &rtlPhyInfo[phyUnit];

        if (lastStatus->isPhyAlive) { /* last known link status was ALIVE */
        	//DEBUG_MSG("rtl8366sr_phy_is_up: phyUnit=%x is alive\n", phyUnit);
        	rtl8366s_getAsicPHYRegs(phyUnit,0,MII_STATUS_REG,&phyHwStatus);
			
            /* See if we've lost link */
            if (phyHwStatus & (1<<2)) {
                linkCount++;
                //DEBUG_MSG("phyUnit=%x is link\n", phyUnit);
            } else {
                lostLinks++;
                //DEBUG_MSG("phyUnit=%x is lostlink\n", phyUnit); 
                lastStatus->isPhyAlive = FALSE;
            }
        } else { /* last known link status was DEAD */
            //DEBUG_MSG("rtl8366sr_phy_is_up: phyUnit=%x is dead\n", phyUnit);
            /* Check for reset complete */
            rtl8366s_getAsicPHYRegs(phyUnit,0,MII_CONTROL_REG,&phyHwControl);         
            if (phyHwControl & (1<<MII_CONTROL_RESET))
                continue;
            rtl8366s_getAsicPHYRegs(phyUnit,0,MII_STATUS_REG,&phyHwStatus);
//#if 1   
	  		//if(autoNeg)
	  		{
	  			//DEBUG_MSG("phyUnit=%x is auto\n", phyUnit);
	  			udelay(50);         
            	/* Check for AutoNegotiation complete */            
            	if (/* !(phyHwControl & (1<<12)) || */ (phyHwStatus & (1<<5)) ) {                	
                	rtl8366s_getAsicPHYRegs(phyUnit,0,MII_STATUS_REG,&phyHwStatus);
                	
                	if (phyHwStatus & (1<<2)) {
                		//gainedLinks++;
                		linkCount++;
                		//DEBUG_MSG("phyUnit=%x is link\n", phyUnit);
                		lastStatus->isPhyAlive = TRUE;
            		}
        		}
//#else
	   		}
	   		//else{
	   			//DEBUG_MSG("phyUnit=%x is notauto\n", phyUnit);
            //    rtl8366s_getAsicPHYRegs(phyUnit,0,MII_STATUS_REG,&phyHwStatus);

            //    if (phyHwStatus & (1<<2)) {
                	//gainedLinks++;
            //    	linkCount++;
                	//DEBUG_MSG("phyUnit=%x is link\n", phyUnit);                                               
            //    	lastStatus->isPhyAlive = TRUE;
            //	}
	   		//}//end autoNeg
//#endif        
    	}//lastStatus->isPhyAlive
    }//end for
#endif
    return (linkCount);
    
}

#if 0/******************************************************************/
unsigned int mii_read(unsigned char phyad,unsigned char regad);
void mii_write(unsigned char phyad,unsigned char regad,unsigned int value);

extern void gmac_write_reg(unsigned int base, unsigned int offset,unsigned int data,unsigned int bit_mask);
extern void toe_gmac_disable_tx_rx(void);//(GMAC_INFO_T *tp);
extern void toe_gmac_enable_tx_rx(void);//(GMAC_INFO_T *tp);

extern unsigned int gmac_read_reg(unsigned int base, unsigned int offset);
extern void gmac_write_reg(unsigned int base, unsigned int offset,unsigned int data,unsigned int bit_mask);

extern gmac_num;

void rtl_gmac_get_phy_status(GMAC_INFO_T *tp)
{
	GMAC_CONFIG0_T	config0,config0_mask;
    GMAC_STATUS_T   status, old_status;
    unsigned int    reg_val,ability;
    unsigned int    dev_index,rcv_mask,mac_config,speed_fdx_mode,link_mode=0;
	int i;
	
	DEBUG_MSG("rtl_gmac_get_phy_status\n");
	if(!gmac_num)
	{		
		DEBUG_MSG("gmac_num=0\n");
		/* GMAC0 connects to a switch chip, not PHY */			
		old_status.bits32 = status.bits32 = gmac_read_reg(tp->base_addr, GMAC_STATUS);
		DEBUG_MSG("old_status.bits32=%x\n",old_status.bits32);
		status.bits.mii_rmii = 3;//RGMII_1000
    	status.bits.duplex = 1;//duplex
    	status.bits.speed = 2;//1000
    	status.bits.link = LINK_UP; /* link up */
    	if (tp->flow_control_enable == 0)
    	{
    	     config0.bits32 = 0;
    	     config0_mask.bits32 = 0;
    	     config0.bits.tx_fc_en = 1; /* enable tx flow control */
    	     config0.bits.rx_fc_en = 1; /* enable rx flow control */
    	     config0_mask.bits.tx_fc_en = 1;
    	     config0_mask.bits.rx_fc_en = 1;
    	     gmac_write_reg(tp->base_addr, GMAC_CONFIG0,config0.bits32,config0_mask.bits32);
    	     DEBUG_MSG("flow control enable\n");
    	}
    	tp->flow_control_enable = 1;		
		tp->full_duplex_status = status.bits.duplex;
		tp->speed_status = status.bits.speed;		
    	tp->pre_phy_status = status.bits.link;
		if (status.bits32 != old_status.bits32){ 
			DEBUG_MSG("status.bits32=%x\n",status.bits32);
    		gmac_write_reg(tp->base_addr, GMAC_STATUS, status.bits32, 0x0000007f);
    	}	
    }	
	else //if(gmac_num)
	{
		DEBUG_MSG("%s:gmac_num=1\n",__func__);	
    	/* GMAC0 connects to a PHY */
		status.bits32 = old_status.bits32 = gmac_read_reg(tp->base_addr, GMAC_STATUS);
    	DEBUG_MSG("old_status.bits32=%x\n",old_status.bits32);
    	/* read PHY status register */
    	reg_val = mii_read(tp->phy_addr,0x01);//BMSR
    	if ((reg_val & 0x0024) == 0x0024) /* link is established and auto_negotiate process completed */
    	{
    	    DEBUG_MSG("link is established\n");
    	    /* read PHY Auto-Negotiation Link Partner Ability Register */
    	    reg_val = mii_read(tp->phy_addr,0x0a);
    	    if ((reg_val & 0x0800) == 0x0800)//1000 full duplex
    	    {
    	    	DEBUG_MSG("1000 full duplex\n");
    	    	status.bits.mii_rmii = 3;
    	        status.bits.duplex = 1;
    	        status.bits.speed = 2;
    	        reg_val = (mii_read(tp->phy_addr,0x05) & 0x05E0) >> 5;/* 0101 1110 0000*/
    	    }
    	    else if ((reg_val & 0x0400) == 0x0400)//1000 half duplex
    	    { 
    	    	DEBUG_MSG("1000 half duplex\n");
    	    	status.bits.mii_rmii = 3;
    	        status.bits.duplex = 0;
    	        status.bits.speed = 2;
    	        reg_val = (mii_read(tp->phy_addr,0x05) & 0x05E0) >> 5;/* 0101 1110 0000*/
    	    }
    	    else
    	    { //100 
    	    	status.bits.mii_rmii = 2;
    	    	reg_val = (mii_read(tp->phy_addr,0x05) & 0x05E0) >> 5;
    	    	if ((reg_val & 0x08)==0x08) /* 100M full duplex */
    	    	{
    	    		DEBUG_MSG("100M full duplex\n");
    	    	        status.bits.duplex = 1;
    	    	        status.bits.speed = 1;
    	    	}
    	    	else if ((reg_val & 0x04)==0x04) /* 100M half duplex */
    	    	{
    	    		DEBUG_MSG("100M half duplex\n");
    	    	        status.bits.duplex = 0;
    	    	        status.bits.speed = 1;
    	    	}
    	    	else if ((reg_val & 0x02)==0x02) /* 10M full duplex */
    	    	{
    	    	    DEBUG_MSG("10M full duplex\n");
    	    	        status.bits.duplex = 1;
    	    	        status.bits.speed = 0;
    	    	}
    	    	else if ((reg_val & 0x01)==0x01) /* 10M half duplex */
    	    	{
    	    	    DEBUG_MSG("10M half duplex\n");
    	    	        status.bits.duplex = 0;
    	    	        status.bits.speed = 0;
    	    	}
    	    	else{
    	    		DEBUG_MSG("default 100M full duplex\n");
    	    		status.bits.duplex = 1;
    	    		status.bits.speed = 1;
    	    	}	
    	    }
    	    status.bits.link = LINK_UP; /* link up */
    	
    	    if ((reg_val & 0x20)==0x20)/* 10 0000 pause */
    	    {
    	        DEBUG_MSG("support pause\n");
    	        if (tp->flow_control_enable == 0)
    	        {
    	            config0.bits32 = 0;
    	            config0_mask.bits32 = 0;
    	            config0.bits.tx_fc_en = 1; /* enable tx flow control */
    	            config0.bits.rx_fc_en = 1; /* enable rx flow control */
    	            config0_mask.bits.tx_fc_en = 1;
    	            config0_mask.bits.rx_fc_en = 1;
    	            gmac_write_reg(tp->base_addr, GMAC_CONFIG0,config0.bits32,config0_mask.bits32);
    	            DEBUG_MSG("flow control enable.\n");
    	            DEBUG_MSG("tp->base_addr=%x, GMAC_CONFIG0=%x\n",tp->base_addr,gmac_read_reg(tp->base_addr, GMAC_CONFIG0)); 
    	        }
    	        tp->flow_control_enable = 1;
    	    }
    	    else
    	    {
    	        DEBUG_MSG("no support pause\n");
    	        if (tp->flow_control_enable == 1)
    	        {
    	            config0.bits32 = 0;
    	            config0_mask.bits32 = 0;
    	            config0.bits.tx_fc_en = 0; /* disable tx flow control */
    	            config0.bits.rx_fc_en = 0; /* disable rx flow control */
    	            config0_mask.bits.tx_fc_en = 1;
    	            config0_mask.bits.rx_fc_en = 1;
    	            gmac_write_reg(tp->base_addr, GMAC_CONFIG0,config0.bits32,config0_mask.bits32);
    	            DEBUG_MSG("flow control disable.\n");
    	            DEBUG_MSG("tp->base_addr=%x, GMAC_CONFIG0=%x\n",tp->base_addr,gmac_read_reg(tp->base_addr, GMAC_CONFIG0)); 
    	        }
    	        tp->flow_control_enable = 0;
    	    }
    	
    	    if (tp->pre_phy_status == LINK_DOWN)
    	    {
    	        toe_gmac_enable_tx_rx();
    	        tp->pre_phy_status = LINK_UP;    	        
    	        DEBUG_MSG("enable tx rx\n");    	        
    	    }
    	}
    	else
    	{/* Not link is established and auto_negotiate process completed */
    	    DEBUG_MSG("link isn't established\n");
    	    status.bits.link = LINK_DOWN; /* link down */
    	    if (tp->pre_phy_status == LINK_UP)
    	    {
    	        toe_gmac_disable_tx_rx();
    	        tp->pre_phy_status = LINK_DOWN;    	        
    	        DEBUG_MSG("disable tx rx\n");    	        
    	    }
    	}
    	tp->full_duplex_status = status.bits.duplex;
		tp->speed_status = status.bits.speed;
		if (!tp->auto_nego_cfg)
		{
			DEBUG_MSG("tp->auto_nego_cfg\n");
			status.bits.duplex = tp->full_duplex_cfg;
			status.bits.speed = tp->speed_cfg;
		}    	
		//DEBUG_MSG("status.bits32=%x,old_status.bits32=%x\n",status.bits32,old_status.bits32);	
		if (status.bits32 != old_status.bits32){ 
			DEBUG_MSG("status.bits32=%x\n",status.bits32);
    		gmac_write_reg(tp->base_addr, GMAC_STATUS, status.bits32, 0x0000007f);
    	}	
    }
}

void rtl_gmac_set_phy_status(GMAC_INFO_T *tp)
{
	
	GMAC_STATUS_T   status;
	unsigned int    reg_val;
	unsigned int    i;
	DEBUG_MSG("rtl_gmac_set_phy_status\n");
	if(!gmac_num)
	{
		DEBUG_MSG("gmac_num=0\n");
		/* GMAC0 connects to a switch chip, not PHY */			
		gmac_write_reg(tp->base_addr, GMAC_STATUS, 0x7d, 0x0000007f);		
	}
	else
	{
		DEBUG_MSG("gmac_num=1\n");
	    /* GMAC1 connects to a PHY */	   
	    //for(i=0; i<100;i++){
	    	reg_val=(mii_read(tp->phy_addr,0x02) << 16) + mii_read(tp->phy_addr,0x03);
	    	DEBUG_MSG("PHY %d Addr %d Vendor ID: 0x%08x\n", tp->phy_id, tp->phy_addr, reg_val);
	    	//if(reg_val)
	    		//break;
	    //}	
		//phy seeting
		//mii_write(tp->phy_addr,0x04,0x05e1);//ANAR 
		//mii_write(tp->phy_addr,0x09,0x0300);//GBCR
	    //mii_write(tp->phy_addr,0x00,0x1200);//BMCR
		// pry reset + enable and restart Auto-Negotiation
		//reg_val = 0x1200 | (1 << 15);
		//mii_write(tp->phy_addr,0x00,reg_val);
		//reg_val &= ~(1 << 15);
		//mii_write(tp->phy_addr, 0x00, reg_val);
		//hal_delay_us(100000);
	}
	rtl_gmac_get_phy_status(tp);
}


/***************************************/
/* define GPIO module base address     */
/***************************************/
#define GPIO_BASE_ADDR  (IO_ADDRESS(SL2312_GPIO_BASE))

/* define GPIO pin for MDC/MDIO */
#define G_MDC_PIN           22
//#define G_MDC_PIN           0
#define G_MDIO_PIN          21

static unsigned int GPIO_MDC = 0;
static unsigned int GPIO_MDIO = 0;
static unsigned int GPIO_MDC_PIN = 0;
static unsigned int GPIO_MDIO_PIN = 0;

/***********************/
/*    MDC : GPIO[22]   */
/*    MDIO: GPIO[21]   */
/***********************/

/***************************************************
* All the commands should have the frame structure:
*<PRE><ST><OP><PHYAD><REGAD><TA><DATA><IDLE>
****************************************************/

/*****************************************************************
* Inject a bit to NWay register through CSR9_MDC,MDIO
*******************************************************************/
void mii_serial_write(char bit_MDO) // write data into mii PHY
{
    unsigned int addr;
    unsigned int value;

    /* set MDC/MDIO Pin to output */
    addr = GPIO_BASE_ADDR + GPIO_PIN_DIR;
    value = readl(addr) | GPIO_MDC | GPIO_MDIO; 
    writel(value,addr);
    if(bit_MDO)
    {
        addr = (GPIO_BASE_ADDR + GPIO_DATA_SET);
        writel(GPIO_MDIO,addr); /* set MDIO to 1 */
        addr = (GPIO_BASE_ADDR + GPIO_DATA_SET);
        writel(GPIO_MDC,addr); /* set MDC to 1 */
        addr = (GPIO_BASE_ADDR + GPIO_DATA_CLEAR);
        writel(GPIO_MDC,addr); /* set MDC to 0 */
    }
    else
    {
        addr = (GPIO_BASE_ADDR + GPIO_DATA_CLEAR);
        writel(GPIO_MDIO,addr); /* set MDIO to 0 */
        addr = (GPIO_BASE_ADDR + GPIO_DATA_SET);
        writel(GPIO_MDC,addr); /* set MDC to 1 */
        addr = (GPIO_BASE_ADDR + GPIO_DATA_CLEAR);
        writel(GPIO_MDC,addr); /* set MDC to 0 */
    }
}

/**********************************************************************
* read a bit from NWay register through CSR9_MDC,MDIO
***********************************************************************/
unsigned int mii_serial_read(void) // read data from mii PHY
{
    unsigned int *addr;
    unsigned int value;

    addr = (unsigned int *)(GPIO_BASE_ADDR + GPIO_PIN_DIR);
    /* set MDC to output and MDIO to input */
    value = readl(addr) & ~GPIO_MDIO; //0xffbfffff;
    writel(value,addr);

    addr = (unsigned int *)(GPIO_BASE_ADDR + GPIO_DATA_SET);
    writel(GPIO_MDC,addr); /* set MDC to 1 */
    addr = (unsigned int *)(GPIO_BASE_ADDR + GPIO_DATA_CLEAR);
    writel(GPIO_MDC,addr); /* set MDC to 0 */

    addr = (unsigned int *)(GPIO_BASE_ADDR + GPIO_DATA_IN);
    value = readl(addr);
    value = (value & (1<<GPIO_MDIO_PIN)) >> GPIO_MDIO_PIN;
    return(value);

}

/***************************************
* preamble + ST
***************************************/
void mii_pre_st(void)
{
    unsigned char i;

    for(i=0;i<32;i++) // PREAMBLE
        mii_serial_write(1);
    mii_serial_write(0); // ST
    mii_serial_write(1);
}


/******************************************
* Read MII register
* phyad -> physical address
* regad -> register address
***************************************** */
unsigned int mii_read(unsigned char phyad,unsigned char regad)
{
    unsigned int i,value=0;
    char bit;
    
	//DEBUG_MSG("%s:phy_addr=0x%x,reg_addr=0x%x\n",__func__,phyad,regad);
    GPIO_MDC_PIN = G_MDC_PIN;   /* assigned MDC pin for giga PHY */
    GPIO_MDIO_PIN = G_MDIO_PIN; /* assigned MDIO pin for giga PHY */
    
    //DEBUG_MSG("%s:GPIO_MDC_PIN=%d,GPIO_MDIO_PIN=%d\n",__func__,GPIO_MDC_PIN,GPIO_MDIO_PIN);
    GPIO_MDC = (1<<GPIO_MDC_PIN);   
    GPIO_MDIO = (1<<GPIO_MDIO_PIN); 

    mii_pre_st(); // PRE+ST
    mii_serial_write(1); // OP
    mii_serial_write(0);

    for (i=0;i<5;i++) { // PHYAD
        bit= ((phyad>>(4-i)) & 0x01) ? 1 :0 ;
        mii_serial_write(bit);
    }

    for (i=0;i<5;i++) { // REGAD
        bit= ((regad>>(4-i)) & 0x01) ? 1 :0 ;
        mii_serial_write(bit);
    }

    mii_serial_read(); // TA_Z   
    
    for (i=0;i<16;i++) { // READ DATA
        bit=mii_serial_read();
        value += (bit<<(15-i)) ;
    }

    mii_serial_write(0); // dumy clock
    mii_serial_write(0); // dumy clock
	
	DEBUG_MSG("%s: phy_addr=0x%x,reg_addr=0x%x,value=0x%x\n",__func__,phyad,regad,value);
    return(value);
}

/******************************************
* Write MII register
* phyad -> physical address
* regad -> register address
* value -> value to be write
***************************************** */
void mii_write(unsigned char phyad,unsigned char regad,unsigned int value)
{
    unsigned int i;
    char bit;

	DEBUG_MSG("%s:phy_addr=0x%x,reg_addr=0x%x,value=0x%x\n",__func__,phyad,regad,value);
    GPIO_MDC_PIN = G_MDC_PIN;   /* assigned MDC pin for giga PHY */
    GPIO_MDIO_PIN = G_MDIO_PIN; /* assigned MDIO pin for giga PHY */
    
    //DEBUG_MSG("%s:GPIO_MDC_PIN=%d,GPIO_MDIO_PIN=%d\n",__func__,GPIO_MDC_PIN,GPIO_MDIO_PIN);
    GPIO_MDC = (1<<GPIO_MDC_PIN);   
    GPIO_MDIO = (1<<GPIO_MDIO_PIN); 

    mii_pre_st(); // PRE+ST
    mii_serial_write(0); // OP
    mii_serial_write(1);
    for (i=0;i<5;i++) { // PHYAD
        bit= ((phyad>>(4-i)) & 0x01) ? 1 :0 ;
        mii_serial_write(bit);
    }

    for (i=0;i<5;i++) { // REGAD
        bit= ((regad>>(4-i)) & 0x01) ? 1 :0 ;
        mii_serial_write(bit);
    }
    mii_serial_write(1); // TA_1
    mii_serial_write(0); // TA_0

    for (i=0;i<16;i++) { // OUT DATA
        bit= ((value>>(15-i)) & 0x01) ? 1 : 0 ;
        mii_serial_write(bit);
    }
    mii_serial_write(0); // dumy clock
    mii_serial_write(0); // dumy clock
}
#endif//0
//#endif //CONFIG_RTL8366SR_PHY

