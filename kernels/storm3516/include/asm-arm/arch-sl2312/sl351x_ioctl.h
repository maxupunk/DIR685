/**************************************************************************
* Copyright 2007 STORM Semiconductors, Inc.  All rights reserved.                
*--------------------------------------------------------------------------
*	sl351x_ioctl.h
*
*	Description:
*		- Define the IOCTL Control Commands 
*	
*	History:
*
*   5/01/2007   CH HSU 		Create
*-----------------------------------------------------------------------------*/
#ifndef _SL351x_IOCTL_H_
#define _SL351x_IOCTL_H_	1

/*----------------------------------------------------------------------
* Command set
*----------------------------------------------------------------------*/
#define SIOCDEVSL351x	SIOCDEVPRIVATE	// 0x89F0
#define	GMIIREG			21
#define SMIIREG			22
#define SWITCHMIB		23
#define	DUMPRX			24
#define	DUMPTX			25
#define	REGREAD			26
#define	REGWRITE		27
/*----------------------------------------------------------------------
* Command Structure
*----------------------------------------------------------------------*/
// Common Header
typedef struct {
	unsigned short		cmd;	// command ID
	unsigned short		len;	// data length, excluding this header
} GMACCMD_HDR_T;

//GMIIREG
typedef	struct{
	unsigned short		phy_addr;
	unsigned short		phy_reg;
	unsigned short		phy_len;
} NAT_GMIIREG_T;

//SMIIREG
typedef	struct{
	unsigned short		phy_addr;
	unsigned short		phy_reg;
	unsigned int		phy_data;
} NAT_SMIIREG_T;
	
//DUMPRX
typedef struct {
	unsigned char		enable;
} NAT_DUMP_RX;	

//DUMPTX
typedef struct {
	unsigned char		enable;
} NAT_DUMP_TX;
	
//REGREAD
typedef struct {
	unsigned int		location;
	unsigned int		length;
	unsigned int		size;
} NAT_REGREAD;

//REGWRITE
typedef struct {
	unsigned int		location;
	unsigned int		data;
	unsigned int		size;
} NAT_REGWRITE;
	
typedef union
{
	NAT_GMIIREG_T		get_mii_reg;
	NAT_SMIIREG_T		set_mii_reg;
	NAT_DUMP_RX			dump_rx_packet;
	NAT_DUMP_TX			dump_tx_packet;
	NAT_REGREAD			reg_read;
	NAT_REGWRITE		reg_write;
} GMAC_REQ_E;

#endif // _SL351x_IOCTL_H_



