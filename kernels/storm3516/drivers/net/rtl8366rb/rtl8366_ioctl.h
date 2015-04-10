#ifndef __RTL8366_IOCTL_H
#define __RTL8366_IOCTL_H
#define INITVLAN			1
#define SETVLAN				2
#define SETVLANWITHFID		3
#define SETVLANPVID			4
#define SETPHYTESTMODE 		5
#define GETPHYLINKSTAT		6
#define SETETHERNETPHY		7	 
#define GETETHERNETPHY		8
#define GETPORTLINKSTATE 	9
#define SETRTCTTESTING		10
#define	GETRTCTRESULT		11
#define	SETGREENETHERNET	12
#define	GETMIBCOUNTER   	13

typedef struct setPhyTestMode_para {
	uint32	phy;
	uint32	mode;
} setPhyTestMode_t;	

typedef struct setPhyEthernetPhy_para {
	uint32	port;
	uint32  mode;/*0: auto-negotiation 1: 100Full. 2: 100Half. 3: 10Full. 4: 10Half. 5: 1000Full.6: 1000Half.*/
} setPhyEthernetPhy_t;

typedef struct getPortLinkState_para {
	uint32 port;
	uint32 speed;
	uint32 duplex;
	uint32 link;
	uint32 txPause;
	uint32 rxPause;
	uint32 nWay;
} getPortLinkState_t;

typedef struct setRtctTesting_para {
	enum PORTID port;
	uint32 enabled; 
} setRtctTesting_t;

typedef struct getRtctResult_para {
	enum PORTID port;
	enum CHANNELID channel;
	uint32 length;
	uint32 openSts;
	uint32 shortSts;
	uint32 impmis;
} getRtctResult_t;

typedef struct getMibCounter_para {
	enum PORTID port;
	uint64 TxOctets;
	uint64 RxOctets;
} getMibCounter_t;

/*
typedef struct getPhyLinkType_para {
	uint32	port;
	phyLinkType_t phyLinkType;
} getPhyLinkType_t;
*/
//typedef struct setEthernetPHY_para {
//	uint32 phy,

//} setEthernetPHY_t;



#endif
