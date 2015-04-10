/****************************************************************************
* Copyright 2006 StorLink Semiconductors, Inc.  All rights reserved.                
*----------------------------------------------------------------------------
* Name			: sl351x_bridge.c
* Description	: 
*		Handle Storlink SL351x Bridge Functions
*
*
* Packet Flow:
*
*            (xmit)+<--- SW Bridge -->+(xmit)
*                  |       ^^      |
*                  |       ||      |
*                  |       ||      |
*   Client <---> GMAC-x  HW-Bridge  GMAC-y  <---> Server
*
*
* History
*
*	Date		Writer		Description
*----------------------------------------------------------------------------
*	05/07/2007	CH HSU		Create and implement
*
*
****************************************************************************/
#include <linux/config.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/compiler.h>
#include <linux/pci.h>
#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/rtnetlink.h>
#include <linux/delay.h>
#include <linux/ethtool.h>
#include <linux/mii.h>
#include <linux/completion.h>
#include <asm/hardware.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <asm/semaphore.h>
#include <asm/arch/irqs.h>
#include <asm/arch/it8712.h>
#include <linux/mtd/kvctl.h>
#include <linux/skbuff.h>
#include <linux/if_ether.h>

#define	 MIDWAY 
#define	 SL_LEPUS

#include <asm/arch/sl2312.h>
#include <asm/arch/sl351x_gmac.h>
#include <asm/arch/sl351x_hash_cfg.h> 
#include <asm/arch/sl351x_nat_cfg.h>

//joel mark
//#define VITESSE_G5SWITCH	1
//#define CONFIG_SL351X_BR	1
#ifdef CONFIG_SL351X_BR

/*----------------------------------------------------------------------
* Definition
*----------------------------------------------------------------------*/
#ifdef CONFIG_SL3516_ASIC
#define CONFIG_SL351x_NAT_TCP_UDP
#define CONFIG_SL351x_TCP_UDP_RULE_ID	0
#else
#define CONFIG_SL351x_NAT_TCP_UDP
#define CONFIG_SL351x_TCP_UDP_RULE_ID	0
#endif

#define	nat_printf					printk

#define NAT_TCP_PORT_MAX			64
#define NAT_UDP_PORT_MAX			64

#ifdef VITESSE_G5SWITCH
extern int Giga_switch;
#endif

typedef struct
{
	u16		flags_ver;
	u16		protocol;
	u16		payload_length;
	u16		call_id;
	u32		seq;
	u32		ack;
} GRE_PKTHDR_T;
	
/*----------------------------------------------------------------------
* NAT Configuration
* 
* Note: Any change for network setting, the NAT configuration should 
*       be changed also.
*	cfg->lan_port	0 if GMAC-0, 1: if GMAC-1
*	cfg->wan_port	0 if GMAC-0, 1: if GMAC-1
*	cfg->lan_ipaddr, cfg->lan_gateway, cfg->lan_netmask
*	cfg->wan_ipaddr, cfg->wan_gateway, cfg->wan_netmask
*	
*----------------------------------------------------------------------*/
static int		br_initialized;
BR_CFG_T 		br_cfg;
HASH_ENTRY_T	br_hash_entry;
BR_ENTRY_T 		br_tables[HASH_TOTAL_ENTRIES];

/*----------------------------------------------------------------------
* Functions
*----------------------------------------------------------------------*/
//void sl351x_br_input(struct sk_buff *skb, int port)

extern int mac_set_rule_reg(int mac, int rule, int enabled, u32 reg0, u32 reg1, u32 reg2);
extern void hash_dump_entry(int index);
extern void mac_get_hw_tx_weight(struct net_device *dev, char *weight);
extern void mac_set_hw_tx_weight(struct net_device *dev, char *weight);
extern int net_get_mac_address(struct net_device *dev, void *addr);


/*----------------------------------------------------------------------
* sl351x_br_init
*	initialize a NAT matching rule
*	Called by SL351x Driver
*		key		: port, protocol, Sip, Dip, Sport, Dport
*		Action	: Srce Q: HW Free Queue,
*				  Dest Q: HW TxQ
*				  Change DA
*				  Change SA
*                 Change Sip or Dip
*    			  Change Sport or Dport
*----------------------------------------------------------------------*/
void sl351x_br_init(void)
{
	HASH_ENTRY_T		*hash_entry;
	int					rc;
	GMAC_MRxCR0_T		mrxcr0;
	GMAC_MRxCR1_T		mrxcr1;
	GMAC_MRxCR2_T		mrxcr2;
	BR_CFG_T			*cfg;
	
	if (br_initialized)
		return;
    
	br_initialized = 1;
		
	memset((void *)br_tables, 0, sizeof(BR_ENTRY_T));
	// Init Port-0 hash entry
	hash_entry = (HASH_ENTRY_T *)&br_hash_entry;
	memset((void *)hash_entry, 0, sizeof(HASH_ENTRY_T));
	hash_entry->rule = 0;
	hash_entry->key_present.port = 1;
	hash_entry->key_present.da = 1;
	hash_entry->action.srce_qid = TOE_HW_FREE_QID;
    
    cfg = (BR_CFG_T *)&br_cfg;
	memset((void *)cfg, 0, sizeof(BR_CFG_T)); 
	

//#ifdef VITESSE_G5SWITCH
//	if(Giga_switch)
	{
		cfg->enabled			= 1;
		cfg->tcp_udp_rule_id 	= CONFIG_SL351x_TCP_UDP_RULE_ID;
		cfg->lan_port			= 0;
		cfg->wan_port			= 1;
		cfg->default_hw_txq 	= 3;
		cfg->tcp_tmo_interval 	= 360;
	}
//	else
//	{
//		cfg->enabled			= 1;
//		cfg->tcp_udp_rule_id 	= CONFIG_SL351x_TCP_UDP_RULE_ID;
//		cfg->lan_port			= 0;
//		cfg->wan_port			= 1;
//		cfg->default_hw_txq 	= 3;
//		cfg->tcp_tmo_interval 	= 360;
//	}
//#endif

#ifdef CONFIG_SL351x_NAT_TCP_UDP 
	mrxcr0.bits32 = 0;
	mrxcr1.bits32 = 0;
	mrxcr2.bits32 = 0;
	mrxcr0.bits.port = 1;
	mrxcr0.bits.l2 = 1;
	mrxcr0.bits.da = 1;
	mrxcr0.bits.sprx = 0;
	
	rc = mac_set_rule_reg(cfg->lan_port, cfg->tcp_udp_rule_id, 1, mrxcr0.bits32, mrxcr1.bits32, mrxcr2.bits32);
	if (rc < 0)
	{
		nat_printf("NAT Failed to set MAC-%d Rule %d!\n", cfg->lan_port, cfg->tcp_udp_rule_id);
	}
		
	if (cfg->lan_port != cfg->wan_port)
	{
		rc = mac_set_rule_reg(cfg->wan_port, cfg->tcp_udp_rule_id, 1, mrxcr0.bits32, mrxcr1.bits32, mrxcr2.bits32);
		if (rc < 0)
		{
			nat_printf("NAT Failed to set MAC-%d Rule %d!\n", cfg->wan_port, cfg->tcp_udp_rule_id);
		}
	}
#endif
}


/*----------------------------------------------------------------------
* sl351x_br_input
*	Handle Bridge Bridge output frames
*   SA0 --> G0 <---> G1 <--- SA1
*	Handle BR input frames
*	return : Packet is handled by up layer
*
*   1. return , if bridge is not enable or incorrect frames
*	2. Learning MAC port id by Source MAC address
*   3. If Multicast or broadcast, forward to other port, and pass to upper layer
*   4. If DA is me, then pass to upper layer
*	5. If the DA is the other side, than add hash entry
*   6. Forward the unknown DA to the other port
*----------------------------------------------------------------------*/
int sl351x_br_input(struct sk_buff *skb, int port)
{
	int				pid;
	BR_CFG_T		*cfg;
	unsigned long	hash_key[HASH_MAX_DWORDS];
	HASH_ENTRY_T	*hash_entry;
	BR_ENTRY_T		*br_entry;
	
	cfg = (BR_CFG_T *)&br_cfg;
	
	if (!cfg->enabled)
		return ;
		
	pid = port;
	
	hash_entry = (HASH_ENTRY_T *)&br_hash_entry;
	hash_entry->key.port = (pid == cfg->lan_port) ? cfg->wan_port : cfg->lan_port;
	memcpy(hash_entry->key.da, skb->data+6, 6);
	if (hash_build_keys((unsigned long *)&hash_key, hash_entry) < 0)
	{
		printk("Failed to a build hash key!\n");
		return ;
	}
	
	br_entry = (BR_ENTRY_T *)&br_tables[hash_entry->index];
	if (!br_entry->active)
	{
		memcpy(br_entry->mac_addr, hash_entry->key.da, 6);
		br_entry->my_hash_index = hash_entry->index;
		br_entry->tmo.counter = br_entry->tmo.interval = cfg->tcp_tmo_interval;
		br_entry->portid = (pid == cfg->lan_port) ? cfg->wan_port : cfg->lan_port;
		br_entry->active = 1;
	}
	
	// multicast / broadcast
	if (skb->data[0] & 1)
	{
		return;
	}
//	else if (memcmp(skb->data, br_get_mac_addr(pid), 6) == 0) //DA is me
//	{
//		return 0; // return 0 to handle by upper layer
//	}
	else
	{
		// Check DA whether it is in other port or not
		hash_entry = (HASH_ENTRY_T *)&br_hash_entry;
		if (pid == cfg->lan_port)
		{
			pid = cfg->wan_port;
			hash_entry->action.dest_qid = TOE_GMAC1_HW_TXQ2_QID;
			hash_entry->tmo.counter = hash_entry->tmo.interval = cfg->tcp_tmo_interval;
			hash_entry->key.port= 0;
		}
		else
		{
			hash_entry->action.dest_qid = TOE_GMAC0_HW_TXQ2_QID;
			hash_entry->tmo.counter = hash_entry->tmo.interval = cfg->tcp_tmo_interval;
			hash_entry->key.port= 1;
			pid = cfg->lan_port;
		}
		memcpy(hash_entry->key.da, skb->data, 6);
				
		if (hash_build_keys((unsigned long *)&hash_key, hash_entry) < 0)
		{
			printk("Failed to a build hash key!\n");
		}
		else 
		{		
			br_entry = (BR_ENTRY_T *)&br_tables[hash_entry->index];
			if (br_entry->active && br_entry->portid == hash_entry->key.port &&
				memcmp(hash_entry->key.da, br_entry->mac_addr, 6)==0)
			{
				hash_write_entry(hash_entry, (unsigned char *)&hash_key[0]);
				hash_set_valid_flag(hash_entry->index, 1);
			//	nat_printf("pid= %d %lu Validate a LAN hash entry %d\n",pid, jiffies/HZ, hash_entry->index);
			//	hash_dump_entry(hash_entry->index);
			}
		}
		
		return ;
	}
}

#endif // CONFIG_SL351X_BR

