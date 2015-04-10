
#ifndef _CRP_STORM_H_
#define _CRP_STORM_H_

//des_ecb      key=8    iv=0
//des_cbc      key=8    iv=8
//des3_ede_ecb key=24   iv=0
//des3_ede_cbc key=24   iv=8
//aes128_ecb   key=16   iv=0
//aes128_cbc   key=16   iv=8
//aes192_ecb   key=24   iv=0
//aes192_cbc   key=24   iv=8
//aes256_ecb   key=32   iv=0
//aes256_cbc   key=32   iv=8

#define MD5_DIGEST_LENGTH 16
#define SHA_DIGEST_LENGTH 20
#define EVP_MD_FLAG_ONESHOT	0x0001 /* digest can only handle a single */

#if 0

// define cipher algorithm 
enum CIPHER {
	DES_ECB_E	=20,
	TDES_ECB_E	=21,
	AES_ECB_E	=22,
	DES_CBC_E	=24,
	TDES_CBC_E	=25,
	AES_CBC_E	=26,
	
	DES_ECB_D	=27,
	TDES_ECB_D	=28,
	AES_ECB_D	=29,
	DES_CBC_D	=31,
	TDES_CBC_D	=32,
	AES_CBC_D	=33,
	A_SHA1      =12,
	A_HMAC_SHA1 =13,
	A_MD5       =14,
	A_HMAC_MD5  =15,
};

// opMode
#define CIPHER_ENC    0x1
#define CIPHER_DEC    0x3
#define AUTH          0x4
#define ENC_AUTH      0x5
#define AUTH_DEC      0x7

// cipherAlgorithm
#define CBC_DES       0x4
#define CBC_3DES      0x5
#define CBC_AES       0x6
#define ECB_DES       0x0
#define ECB_3DES      0x1
#define ECB_AES       0x2

// authAlgorithm
#define SHA1         0
#define MD5          1 
#define HMAC_SHA1    2 
#define HMAC_MD5     3
#define FCS          4

//cipher mode
#define ECB          0
#define CBC          1

// authMode
#define AUTH_APPEND  0
#define AUTH_CHKVAL  1

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
    void (*callback)(struct PACKET_SSL *); /* function to call when done authentication/cipher */ 
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

struct dev_crypto_state {
	struct PACKET_SSL op;
	int d_fd;
};

struct dev_rand {
	unsigned char *buf;
	int len;
};


#define DO_CRYPTO                 		_IOWR ('q', 0xC0, struct IPSEC_PACKET_S  *)
#define DO_GET_RAND32                 _IOWR ('q', 0xC1, struct dev_rand  *)

#endif
#endif /* __CRP_STORM_H__ */
