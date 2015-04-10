/************************************************************************** 
* Copyright 2007 STORM Semiconductors, Inc.  All rights reserved.
*--------------------------------------------------------------------------
* Name			: sl351x_ioctl.c
* Description	: 
*		GMAC Ioctl handler
* History
*
*	Date		Writer		Description
*	-----------	-----------	-------------------------------------------------
*   28/12/2007  CH Hsu      Create and implement
*
****************************************************************************/
#include <linux/config.h>
#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/mii.h>
#include <asm/io.h>

#include <asm/arch/sl2312.h>
#include <asm/arch/sl351x_gmac.h>
#include <asm/arch/sl351x_ioctl.h>

#ifdef CONFIG_RTL8366SR_PHY 
#undef VITESSE_G5SWITCH
#else
#define VITESSE_G5SWITCH	1
#endif

#define MIN_READ					0xf6000000
#define MAX_READ					0xf7000000

/*----------------------------------------------------------------------
* Function declare
*----------------------------------------------------------------------*/
extern unsigned int mii_read(unsigned char phyad,unsigned char regad);
extern void mii_write(unsigned char phyad,unsigned char regad,unsigned int value);
extern void dm_long_1(u32 location, int length);
extern void dm_short(u32 location, int length);
extern void dm_byte(u32 location, int length);

/*************************************************************
 *         Global Variable
 *************************************************************/
extern int Giga_switch;
#ifdef GMAC_DEBUG_U	
extern int gmac_dump_rxpkt;
extern int gmac_dump_txpkt;
#endif
/*----------------------------------------------------------------------
* sl351x_gmac_ioctl
*----------------------------------------------------------------------*/
int sl351x_gmac_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	int 				i,err = 0;
#ifdef VITESSE_G5SWITCH	
	int ii,jj;
#endif	
    GMACCMD_HDR_T		gmac_hdr;
    GMAC_REQ_E			ctrl;
	unsigned char		*req_datap;
	unsigned int		phy_data_s = -1,location_r = -1,length_r = -1,location_w = -1,data_w = -1;
	unsigned int		size_r,size_w;
	unsigned short		phy_addr = -1,phy_reg = -1,phy_len = -1, phy_addr_s = 0, phy_reg_s = 0;
	
	if (copy_from_user((void *)&gmac_hdr, rq->ifr_data, sizeof(gmac_hdr)))
		return -EFAULT;
	req_datap = (unsigned char *)rq->ifr_data + sizeof(gmac_hdr);
	switch (gmac_hdr.cmd) {
	case GMIIREG:
		if (gmac_hdr.len != sizeof(NAT_GMIIREG_T))
			return -EPERM;
		if (copy_from_user((void *)&ctrl.get_mii_reg, req_datap, sizeof(ctrl.get_mii_reg)))
			return -EFAULT; //Invalid argument
		phy_addr = ctrl.get_mii_reg.phy_addr;
		phy_reg = ctrl.get_mii_reg.phy_reg;
		phy_len = ctrl.get_mii_reg.phy_len;
#ifdef VITESSE_G5SWITCH			
		if (Giga_switch == 1)
		{
			if (phy_addr == 2)
			{
				printk("\n");
				for(jj=0;jj<4;jj++)
				{
					unsigned int data_switch;
					for (ii=0; ii< phy_len ; ii++)
					{
						data_switch = phy_read(jj,phy_reg);
						printk("MII Switch Phy %d Port %d Reg %d Data = 0x%x\n", phy_addr, jj,phy_reg, data_switch);
						phy_reg++;
					}
					phy_reg = phy_reg - phy_len;
					printk("\n");
				}
			}
			else if (phy_addr == 1)
			{
				for (i=0; i< phy_len ; i++)
				{
					unsigned int data;
					data = mii_read(phy_addr,phy_reg); 
					printk("MII Phy %d Reg %d Data = 0x%x\n", phy_addr, phy_reg++, data);
				}
			}
			else
				err = 1;
		}
		else 
#endif			
		{
			if ((phy_addr == 1) || (phy_addr == 2))
			{
				for (i=0; i< phy_len ; i++)
				{
					unsigned int data;
					data = mii_read(phy_addr,phy_reg); 
					printk("MII Phy %d Reg %d Data = 0x%x\n", phy_addr, phy_reg++, data);
				}
			}
			else 
				err = 1;
		}
		
		if (err == 1)
		{
			printk("Syntax error!\n");
			printk("Syntax: MII read [-a phy addr] [-r phy reg] [-l length]\n");
			printk("Options:\n");
			printk("\t-a  Phy address\n");
			printk("\t-r  Phy registers\n");
			printk("\t-l  Display total registers\n");
			printk("MII Phy address -a %d error !! Phy address must be 1 or 2.\n", phy_addr);
		}
		break;
		
	case SMIIREG:
		if (gmac_hdr.len != sizeof(NAT_SMIIREG_T))
			return -EPERM;
		if (copy_from_user((void *)&ctrl.set_mii_reg, req_datap, sizeof(ctrl.set_mii_reg)))
			return -EFAULT;
		
		phy_addr_s = ctrl.set_mii_reg.phy_addr;
		phy_reg_s = ctrl.set_mii_reg.phy_reg;
		phy_data_s = ctrl.set_mii_reg.phy_data;
#ifdef VITESSE_G5SWITCH			
		if (Giga_switch == 1)
		{
			if (phy_addr_s == 2)
			{
				printk("\n");
				for(jj=0;jj<4;jj++)
				{
						phy_write(jj,phy_reg_s,phy_data_s);
						phy_write_masked(jj,phy_reg_s,phy_data_s,0xffff);
						printk("Write MII Switch Phy %d Port %d Reg %d Data = 0x%x\n", phy_addr_s, jj,phy_reg_s, phy_data_s);
				}
			}
			else if (phy_addr_s == 1)
			{
					mii_write(phy_addr_s,phy_reg_s,phy_data_s); 
					printk("Write MII Phy %d Reg %d Data = 0x%x\n", phy_addr_s, phy_reg_s, phy_data_s);
			}
			else
				err = 1;
		}
		else 
#endif		
		{
			if ((phy_addr_s == 1) || (phy_addr_s == 2))
			{
					mii_write(phy_addr_s,phy_reg_s,phy_data_s); 
					printk("Write MII Phy %d Reg %d Data = 0x%x\n", phy_addr_s, phy_reg_s, phy_data_s);
			}
			else 
				err = 1;
		}
		
		if (err == 1)
		{
			printk("Syntax error!\n");
			printk("Syntax: MII write [-a phy addr] [-r phy reg] [-d data]\n");
			printk("Options:\n");
			printk("\t-a  Phy address\n");
			printk("\t-r  Phy registers\n");
			printk("\t-d  date\n");
			printk("MII Phy address -a %d error !! Phy address must be 1 or 2.\n", phy_addr);
		}
		break;
#ifdef GMAC_DEBUG_U				
	case DUMPRX:	
		if (gmac_hdr.len != sizeof(NAT_DUMP_RX))
			return -EPERM;
		if (copy_from_user((void *)&ctrl.dump_rx_packet, req_datap, sizeof(ctrl.dump_rx_packet)))
			return -EFAULT;
		if (ctrl.dump_rx_packet.enable != 0 && ctrl.dump_rx_packet.enable != 1)
			return -EPERM;	
		gmac_dump_rxpkt	= ctrl.dump_rx_packet.enable;
		break;	
	case DUMPTX:	
		if (gmac_hdr.len != sizeof(NAT_DUMP_TX))
			return -EPERM;
		if (copy_from_user((void *)&ctrl.dump_tx_packet, req_datap, sizeof(ctrl.dump_tx_packet)))
			return -EFAULT;
		if (ctrl.dump_tx_packet.enable != 0 && ctrl.dump_tx_packet.enable != 1)
			return -EPERM;	
		gmac_dump_txpkt	= ctrl.dump_tx_packet.enable;
		break;	
#endif		
	case REGREAD:	
		if (gmac_hdr.len != sizeof(NAT_REGREAD))
			return -EPERM;
		if (copy_from_user((void *)&ctrl.reg_read, req_datap, sizeof(ctrl.reg_read)))
			return -EFAULT;
		location_r = ctrl.reg_read.location;
		length_r = ctrl.reg_read.length;
		size_r = ctrl.reg_read.size;
    	
    	if (size_r == 1 && ((MIN_READ <= location_r) && (location_r <= MAX_READ)))//IO MEM can not dump use dm_byte.
    		size_r = 4;
		if (size_r == 1)
			dm_byte(location_r, length_r);
		if (size_r == 2)
			dm_short(location_r, length_r);
		if (size_r == 4)
			dm_long_1(location_r, length_r);
		break;		
	case REGWRITE:	
		if (gmac_hdr.len != sizeof(NAT_REGWRITE))
			return -EPERM;
		if (copy_from_user((void *)&ctrl.reg_write, req_datap, sizeof(ctrl.reg_write)))
			return -EFAULT;
		location_w = ctrl.reg_write.location;
		data_w = ctrl.reg_write.data;
		size_w = ctrl.reg_write.size;
		if (size_w == 1)
		{
			if (data_w > 0xff)
				err = 1;
			else
			{	
				writeb(data_w,location_w);
				printk("Write Data 0x%X to Location 0x%X\n",(u32)data_w, location_w);
			}
		}
		if (size_w == 2)
		{
			if (data_w > 0xffff)
				err = 1;
			else
			{
				writew(data_w,location_w);
				printk("Write Data 0x%X to Location 0x%X\n",(u32)data_w, location_w);
			}
		}
		if (size_w == 4)
		{
			if (data_w > 0xffffffff)
				err = 1;
			else
			{	
				writel(data_w,location_w);
				printk("Write Data 0x%X to Location 0x%X\n",(u32)data_w, location_w);
			}
		}
		if (err == 1)
		{
			printk("Syntax:	gmac write mem [-b <location>] [-d <data>] [-1|2|4]\n");
			printk("Options:\n");
			printk("\t-b  Register Address\n");
			printk("\t-d  Data Vaule\n");
			if (size_w == 1)
				printk("\t-1  Data 0x%X < 0xFF\n",data_w);
			if (size_w == 2)	
				printk("\t-2  Data 0x%X < 0xFFFF\n",data_w);
			if (size_w == 4)	
				printk("\t-4  Data 0x%X < 0xFFFFFFFF\n",data_w);
		}
		break;
	default:
		return -EPERM;
	}
	
	return 0;
}


