#ifndef __GEMINI_CRYPTO_H__
#define __GEMINI_CRYPTO_H__
#include <linux/ioctl.h>
#include <linux/types.h>
#include <asm/arch-sl2312/irqs.h>
#include <asm/arch-sl2312/sl2312_ipsec.h>

typedef __u16 UINT16;
typedef __u32 UINT32;
typedef __u8 UINT8;
typedef __u8 BOOL;

struct dev_rand {
	unsigned char *buf;
	int len;
};
/***************************************/
/* define GPIO module base address     */
/***************************************/

struct PACKET_SSL
{
    unsigned int    op_mode;            /* CIPHER_ENC(1),CIPHER_DEC(3),AUTH(4),ENC_AUTH(5),AUTH_DEC(7) */
    unsigned int    cipher_algorithm;   /* ECB_DES(0),ECB_3DES(1),ECB_AES(2),CBC_DES(4),CBC_3DES(5),CBC_AES(6) */
    unsigned int    auth_algorithm;     /* SHA1(0),MD5(1),HMAC_SHA1(2),HMAC_MD5(3),FCS(4) */
    unsigned int    auth_result_mode;   /* AUTH_APPEND(0),AUTH_CHKVAL(1) */
    unsigned int    process_id;         /* Used to identify the process */
    unsigned int    auth_header_len;    /* Header length to be skipped by the authenticator */
    unsigned int    auth_algorithm_len; /* Length of message body that is to be authenticated */
    unsigned int    cipher_header_len;  /* Header length to be skipped by the cipher */
    unsigned int    cipher_algorithm_len;   /* Length of message body to be encrypted or decrypted */
    unsigned char   iv[16];             /* Initial vector used for DES,3DES,AES */
    unsigned int    iv_size;            /* Initial vector size */
    unsigned char   auth_key[64];       /* authentication key */
    unsigned int    auth_key_size;      /* authentication key size */
    unsigned char   cipher_key[32];     /* cipher key */
    unsigned int    cipher_key_size;    /* cipher key size */
    //struct scatterlist *in_packet;         /* input_packet buffer pointer */
    unsigned char		*in_packet;         /* input_packet buffer pointer */
    unsigned int    pkt_len;            /* input total packet length */
    unsigned char   auth_checkval[20];  /* Authentication check value/FCS check value */
    struct IPSEC_PACKET_S *next,*prev;        /* pointer to next/previous operation to perform on buffer */
    void (*callback)(struct IPSEC_PACKET_S *); /* function to call when done authentication/cipher */ 
    unsigned char   *out_packet;        /* output_packet buffer pointer */
    //struct scatterlist *out_packet;        /* output_packet buffer pointer */
    unsigned int    out_pkt_len;        /* output total packet length */
    unsigned int    auth_cmp_result;    /* authentication compare result */
    unsigned int    checksum;           /* checksum value */
    unsigned int    status;             /* ipsec return status. 0:success, others:fail */
//#if (IPSEC_TEST == 1)          
//    unsigned char    *sw_packet;         /* for test only */
//    unsigned int    sw_pkt_len;         /* for test only */
//#endif    
} ;


#define DO_CRYPTO                 		_IOWR ('q', 0xC0, struct IPSEC_PACKET_S  *)
#define DO_GET_RAND32                 _IOWR ('q', 0xC1, struct dev_rand  *)

//#define DO_SETDATA                _IOW ('q', 0xC1, unsigned char  *)
//#define DO_GETDATA                _IOR ('q', 0xC1, unsigned char  *)
//#define DO_CRYPTO_SHA1                 _IOWR ('q', 0xC1, struct IPSEC_PACKET_S *)
//#define DO_CRYPTO                 _IOWR ('q', 0xC2, struct IPSEC_PACKET_S  *)

/*
#define SSP_GET_HOOK_STATUS			_IOR  ('q', 0xC0, int)
#define SSP_GET_LINEFEED			_IOR  ('q', 0xC1, int)
#define SSP_SET_LINEFEED			_IOW  ('q', 0xC2, int)
#define SSP_GET_REG                 _IOWR ('q', 0xC3, struct Ssp_reg *)
#define SSP_SET_REG                 _IOWR ('q', 0xC4, struct Ssp_reg *)
#define SSP_GEN_OFFHOOK_TONE		_IO   ('q', 0xC5)
#define SSP_GEN_BUSY_TONE			_IO   ('q', 0xC6)
#define SSP_GEN_RINGBACK_TONE		_IO   ('q', 0xC7)
#define SSP_GEN_CONGESTION_TONE		_IO   ('q', 0xC8)
#define SSP_DISABLE_DIALTONE		_IO   ('q', 0xC9)
#define SSP_PHONE_RING_START		_IO   ('q', 0xCA)
*/


#endif
