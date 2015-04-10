/***********************************************************************
* Name			: sl351x_ipsec.h
* Description	: 
*		Define for SL351x IPSEC functions, specifically for VPN application
*
* History
*
* 	Date	Writer		Description
*-----------------------------------------------------------------------
*		Feng Liu	Original Implementation
*		Wen Hsu		
***********************************************************************/

#ifndef _SL351x_IPSEC_H_
#define _SL351x_IPSEC_H_

#include <linux/interrupt.h>
#include <asm/arch/sl351x_gmac.h>

#define MAX_IPSEC_CONN                  32
#define MAX_IPSEC_TUNNEL				200
#define MAX_IPSEC_PKTS                  256 
#define CONFIG_SL351x_IPSEC_RULE_ID     0
#define MAX_SKB_SIZE					2048		// 1536 is a bit too small, sometimes causes problem
#define IPSEC_POLLING_NUM				1

#define SA_IDLE_TIME                    5000
#define SA_TIME_OUT						8000
#define SA_LIFE_TIME					90000

// cipher:	ECB_DES(0),ECB_3DES(1),ECB_AES(2),CBC_DES(4),CBC_3DES(5),CBC_AES(6)
// auth:	SHA1(0),MD5(1),HMAC_SHA1(2),HMAC_MD5(3),FCS(4)

// make sure outbound_qid is 1 smaller than inbound_qid
#define IPSEC_TEST_OUTBOUND_QID			0
#define IPSEC_TEST_INBOUND_QID			1

#define ERR_MATCH_RULE			-1

#define SA_DISABLE                      0
#define SA_ENABLE                       1
#define SA_TIMEOUT                      4		// did not use(?)
#define SA_KEEPALIVE                    8
#define SA_DELETE                       16		// did not use(?)
#define SA_IDLE                         32

//#ifdef CONFIG_CRYPTO_BATCH
#define CRYPTO_QUEUE_SIZE			64
//#endif

struct IPSEC_VPN_TUNNEL_CONFIG {
	unsigned int	tableID;			// it's also SA ID
	__u8		enable;				// whether this VPN is enabled or disabled
									// use to turn on/off hash (so this tunnel works or not)

	// connection info
	__u32		src_LAN;
	__u32		src_netmask;		// only allow netmask of 255.255.255.0 at this point
	__u32		src_LAN_GW;
	__u32		dst_LAN;
	__u32		dst_netmask;		// only allow netmask of 255.255.255.0 at this point
	__u32		src_WAN_IP;
	__u32		dst_WAN_IP;
	// Encryption / Authentication select
	// so far, for testing purpose, only support for 3DES / MD5 with ESP in Tunnel mode
	__u8		cipher_alg;
	__u8		auth_alg;
	__u8		protocol;		// IPPROTO_ESP or IPPROTO_AH
	__u8		mode;			// Encryption (0) or Decryption (1)

	unsigned char   auth_key[64];       /* authentication key */
    unsigned char   enc_key[32];     /* cipher key */
	unsigned char   enc_iv[16];             /* Initial vector used for DES,3DES,AES */
    
	__u32		auth_key_len;
	__u8		enc_key_len;
	__u8		enc_iv_len;
	__u32		spi;
	__u8		icv_full_len;
	__u8		icv_trunc_len;

    unsigned int current_sequence;	// keep track of the current sequence number	// hardcode for now
	struct pppox_sock *pppoe_sock;

	// Hash
	__u16		sa_hash_entry;
	__u8		sa_hash_flag;

	struct xfrm_state *xfrm;

	// Count
	unsigned int	connection_count;
};

struct IPSEC_VPN_IP_PAIR_CONFIG {
	__u8		enable;
	__u8		direction;		// 0: out, 1: in
	__u32		src_LAN;
	__u32		src_netmask;
	__u32		src_LAN_GW;
	__u32		dst_LAN;
	__u32		dst_netmask;
	__u32		src_WAN_IP;
	__u32		dst_WAN_IP;
};
#define IPSEC_CLASSIFICATION_QID(x)      (0x22 + x)

#endif
