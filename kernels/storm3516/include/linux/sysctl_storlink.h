#ifndef _SYSCTL_STORLINK
#define _SYSCTL_STORLINK

/*added by beckerh */
struct storlink_sysctl
{
	int sendfile;
	int recvfile;
	int mpages;
	int ackcnt;
	int var1;
	int var2;
	int link[2];
	//debug_Aaron on 10/25/2006 for iSCSI TX/RX acceleration
	int iscsi_tx_acc;
	int iscsi_rx_acc;
	int napi;
	int fast_net;
	int hw_vpn;
	int hw_crypto;
};

extern struct storlink_sysctl storlink_ctl;
/**/

#ifdef CONFIG_STOR_PRINTK

extern asmlinkage int _stor_printk(const char * fmt,...);

/* note: prints function name for you */
//#define STOR_PRINTK(fmt, args...) _stor_printk("[%d]" fmt, stor_printk_index++ , ## args)
#define STOR_PRINTK(fmt, args...) _stor_printk(fmt, ## args)

#define SYSCTL_STORLINK_DEBUG_BUFFER_SIZE               			(1024*16)
#define SYSCTL_STORLINK_DEBUG_BUFFER_LOG_ADDR_SIZE 		10
#define SYSCTL_STORLINK_DEBUG_BUFFER_PHY_ADDR_SIZE 		10


/*added by beckerh */
struct sysctl_storlink
{
	int sendfile;
	int recvfile;
	int numpages;
	char debug_buffer[SYSCTL_STORLINK_DEBUG_BUFFER_SIZE];
	char debug_buffer_phy_addr[SYSCTL_STORLINK_DEBUG_BUFFER_PHY_ADDR_SIZE];
	char debug_buffer_log_addr[SYSCTL_STORLINK_DEBUG_BUFFER_LOG_ADDR_SIZE];
};

extern struct sysctl_storlink sysctl_storlink;
extern int stor_printk_index;

#else
#define STOR_PRINTK(fmt, args...)

#endif /*CONFIG_STOR_PRINTK*/
/**/


#endif

