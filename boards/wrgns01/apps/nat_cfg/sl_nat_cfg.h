/*-----------------------------------------------------------------------------------
*	sl_nat_cfg.h
*
*	Description:
*		- Define the Device Control Commands for NAT Configuration
*	
*	History:
*
*	4/28/2006	Gary Chen	Create
*
*-------------------------------------------------------------------------------------*/
#ifndef _SL_NAT_CFG_H_
#define _SL_NAT_CFG_H_	1

#include <sys/types.h>
#include <unistd.h>
#include <string.h>

/*----------------------------------------------------------------------
* Confiuration
*----------------------------------------------------------------------*/
#ifdef CONFIG_IP_NF_NAT
#define CONFIG_SL_LEPUS_NAT			1
#endif
#define CONFIG_NAT_MAX_IP_NUM		4	// per device (eth0 or eth1)
#define CONFIG_NAT_MAX_XPORT		64
#define CONFIG_NAT_MAX_WRULE		16	// per Queue
#define CONFIG_NAT_TXQ_NUM			4
/*----------------------------------------------------------------------
* Command set
*----------------------------------------------------------------------*/
#define SIOCDEVLEPUS	SIOCDEVPRIVATE	// 0x89F0
#define NATSSTATUS		0
#define NATGSTATUS		1
#define NATSETPORT		2
#define NATGETPORT		3
#define NATADDIP		4
#define NATDELIP		5
#define NATGETIP		6
#define NATAXPORT		7
#define NATDXPORT		8
#define NATGXPORT		9
#define NATSWEIGHT		10
#define NATGWEIGHT		11
#define NATAWRULE		12
#define NATDWRULE		13
#define NATGWRULE		14
#define NATSDEFQ		15
#define NATGDEFQ		16
#define NATRMIPCFG		17
#define NATTESTENTRY	18
#define NATSETMEM		19
#define NATSHOWMEM		20

/*----------------------------------------------------------------------
* Command Structure
*----------------------------------------------------------------------*/
// Common Header
typedef struct {
	u_int16_t		cmd;	// command ID
	u_int16_t		len;	// data length, excluding this header
} NATCMD_HDR_T;

// NATSSTATUS & NATGSTATUS commands
typedef struct {
	u_int16_t		cmd;	// command ID
	u_int16_t		len;	// data length, excluding this header
	u_int8_t		enable;
} NAT_STATUS_T;	

// NATSETPORT & NATGETPORT commands
typedef struct {
	u_int16_t		cmd;	// command ID
	u_int16_t		len;	// data length, excluding this header
	u_int8_t		portmap;
} NAT_PORTCFG_T;

typedef struct {
	u_int32_t		ipaddr;
	u_int32_t		netmask;
} NAT_IP_ENTRY_T;

// NATADDIP & NATDELIP commands
typedef struct {
	u_int16_t		cmd;	// command ID
	u_int16_t		len;	// data length, excluding this header
	NAT_IP_ENTRY_T		entry;
} NAT_IPCFG_T;

// NATGETIP command
typedef struct {
	u_int16_t		cmd;	// command ID
	u_int16_t		len;	// data length, excluding this header
	u_int32_t		total;
	NAT_IP_ENTRY_T		entry[CONFIG_NAT_MAX_IP_NUM];
} NAT_IPCFG_ALL_T;

typedef struct {
	u_int32_t		protocol;
	u_int16_t		sport_start;
	u_int16_t		sport_end;
	u_int16_t		dport_start;
	u_int16_t		dport_end;
} NAT_XPORT_ENTRY_T;

// NATAXPORT & NATDXPORT Commands
typedef struct {
	u_int16_t		cmd;	// command ID
	u_int16_t		len;	// data length, excluding this header
	NAT_XPORT_ENTRY_T	entry;
} NAT_XPORT_T;

// NATGXPORT Command
typedef struct {
	u_int16_t		cmd;	// command ID
	u_int16_t		len;	// data length, excluding this header
	u_int32_t		total;
	NAT_XPORT_ENTRY_T	entry[CONFIG_NAT_MAX_XPORT];
} NAT_XPORT_ALL_T;

// NATSWEIGHT & NATGWEIGHT Commands
typedef struct {
	u_int16_t		cmd;	// command ID
	u_int16_t		len;	// data length, excluding this header
	u_int8_t		weight[CONFIG_NAT_TXQ_NUM];
} NAT_WEIGHT_T;

typedef struct {
	u_int32_t		protocol;
	u_int32_t		sip_start;
	u_int32_t		sip_end;
	u_int32_t		dip_start;
	u_int32_t		dip_end;
	u_int16_t		sport_start;
	u_int16_t		sport_end;
	u_int16_t		dport_start;
	u_int16_t		dport_end;
} NAT_WRULE_ENTRY_T;	

// NATAWRULE & NATDWRULE Commands
typedef struct {
	u_int16_t		cmd;	// command ID
	u_int16_t		len;	// data length, excluding this header
	u_int32_t		qid;
	NAT_WRULE_ENTRY_T	entry;
} NAT_WRULE_T;

// NATGWRULE Command
typedef struct {
	u_int16_t		cmd;	// command ID
	u_int16_t		len;	// data length, excluding this header
	u_int32_t		total;
	NAT_WRULE_ENTRY_T	entry[CONFIG_NAT_MAX_WRULE];
} NAT_WRULE_ALL_T;

// NATSDEFQ & NATGDEFQ commands
typedef struct {
	u_int16_t		cmd;	// command ID
	u_int16_t		len;	// data length, excluding this header
	u_int32_t		qid;
} NAT_QUEUE_T;	

// NATTESTENTRY 
typedef struct {
	u_int16_t		cmd;	// command ID
	u_int16_t		len;	// data length, excluding this header
	u_int8_t		init_enable;
} NAT_TESTENTRY_T;		

typedef union
{
	NAT_STATUS_T	status;
	NAT_PORTCFG_T	portcfg;
	NAT_IPCFG_T		ipcfg;
	NAT_XPORT_T		xport;
	NAT_WEIGHT_T	weight;
	NAT_WRULE_T		wrule;
	NAT_QUEUE_T		queue;
	NAT_TESTENTRY_T init_entry;
} NAT_REQ_E;


	
/*----------------------------------------------------------------------
* NAT Configuration
*	- Used by driver only
*----------------------------------------------------------------------*/
typedef struct {
	u_int32_t		enabled;
	u_int32_t		match_rule;
	u_int32_t		lan_port;
	u_int32_t		wan_port;
	u_int32_t		default_hw_txq;
	u_int32_t		init_enabled;
	NAT_IPCFG_ALL_T		ipcfg[2];	// LAN/WAN port
	NAT_XPORT_ALL_T		xport;
	NAT_WEIGHT_T		weight;
	NAT_WRULE_ALL_T		wrule[CONFIG_NAT_TXQ_NUM];
} NAT_CFG_T;

/*----------------------------------------------------------------------
* NAT Control Block
*	- Used by driver only
*	- Stores LAN-IN or WAN-IN information
*	- WAN-OUT and LAN-OUT driver use them to build up a hash entry
*	- NOTES: To update this data structure, MUST take care of alignment issue
*   -		 MUST make sure that the size of skbuff structure must 
*            be larger than (40 + sizof(NAT_CB_T))
*----------------------------------------------------------------------*/
typedef struct {
	u_int16_t		tag;
	u_int8_t		sa[6];
	u_int32_t		sip;
	u_int32_t		dip;
	u_int16_t		sport;
	u_int16_t		dport;
	u_int8_t		pppoe_frame;
	u_int8_t		reserved[3];
} NAT_CB_T;

#define NAT_CB_TAG		0x4C53	// "SL"
#define NAT_CB_SIZE		sizeof(NAT_CB_T)
// #define NAT_SKB_CB(skb)	(NAT_CB_T *)(((u_int32_t)&((skb)->cb[40]) + 3) & ~3)  // for align 4
#define NAT_SKB_CB(skb)	(NAT_CB_T *)&((skb)->cb[40])  // for align 4

#endif // _SL_NAT_CFG_H_



