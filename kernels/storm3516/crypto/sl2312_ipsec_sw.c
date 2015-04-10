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
#include <asm/arch/sl2312_ipsec.h>

#if 0
/* define cipher algorithm */
enum CIPHER {
	DES_ECB_E	=20,
	DES_ECB_D	=21,
	DES_CBC_E	=22,
	DES_CBC_D	=23,
	TDES_ECB_E	=24,
	TDES_ECB_D	=25,
	TDES_CBC_E	=26,
	TDES_CBC_D	=27,
	AES_ECB_E	=28,
	AES_ECB_D	=29,
	AES_CBC_E	=30,
	AES_CBC_D	=31,
	A_SHA1      =12,
	A_HMAC_SHA1 =13,
	A_MD5       =14,
	A_HMAC_MD5  =15,
};
#endif

/**********************************************
  Basic data struct in DES
**********************************************/
typedef struct
{
	BYTE byte[8];
} KEY_STRUCT;
typedef struct 
{
	BYTE byte[8];
} DES_DATA;
/**********************************************
  Basic data struct in AES
**********************************************/
typedef union
{
	struct
	{
		BYTE byte3,byte2,byte1,byte0;
	} bytes;
	UINT word32;
} AES_STATE_STRUCT;
typedef struct
{
	AES_STATE_STRUCT state[4];
} AES_STATE;
typedef struct
{
	BYTE byte[16]; // support 128 bit block size
} AES_DATA;
/**************
  Support up to 256 bits key
**************/
typedef struct
{
	BYTE byte[32];
	UINT Nk;
} AES_KEY_STRUCT;

enum 
{
	AES_128=0,
	AES_192,
	AES_256
} ;
/**********************************************
  Basic Data Struct for AH
*********************************************/
typedef struct
{
	UINT word32[16];
} SHA_BLOCK_STRUCT;
//===Authentication Head 160 bits
typedef struct
{
	BYTE byte[20];
} SHA_HEAD_STRUCT;

/**********************************************
  Coommon functions for all modules
**********************************************/
//void FAKE_GenKey(BYTE * pKey);
//void GenRandBytes(BYTE * pByte,UINT nLength);
/**********************************************
  All prototypes in implementation of DES
***********************************************/
void DES_KeyCheckSum(KEY_STRUCT * pKey);
void DES_IP(DES_DATA * pData);
void DES_IP_R(DES_DATA * pData);
void DES_LRSplit(DES_DATA * pData, UINT *pL, UINT *pR);
void DES_LRCombine(DES_DATA * pData, UINT L, UINT R);
void DES_E( UINT R, UINT * pEh32, UINT * pEl16);
void DES_SSplit( UINT h32, UINT l16, UINT * S);
void DES_SCombine(UINT * S,UINT * pP);
void DES_P(UINT * pP);
void DES_S(UINT * S);
void DES_KS_LShift(UINT n,UINT * pReg);
void DES_KeyCombine(UINT * K,UINT * Kh32, UINT * Kl16);
void DES_KS(KEY_STRUCT Key, int * Kh32, int * Kl16);
UINT DES_F(UINT R, UINT Kh32, UINT Kl16);
void DES_Cipher(UINT * Kh32, UINT * Kl16, DES_DATA * pData);
void DES_Decipher(UINT * Kh32,UINT * Kl16,DES_DATA * pData);
void DES_ECB_Cipher(DES_DATA * pData,UINT nLength,KEY_STRUCT Key);
void TDES_ECB_Cipher(DES_DATA * pData,UINT nLength,KEY_STRUCT Key1,KEY_STRUCT Key2,KEY_STRUCT Key3);
void DES_ECB_Decipher(DES_DATA * pData,UINT nLength,KEY_STRUCT Key);
void TDES_ECB_Decipher(DES_DATA * pData,UINT nLength,KEY_STRUCT Key1,KEY_STRUCT Key2,KEY_STRUCT Key3);
void DES_CBC_Cipher(DES_DATA * pData,UINT nLength,DES_DATA IV,KEY_STRUCT Key);
void TDES_CBC_Cipher(DES_DATA * pData,UINT nLength,DES_DATA IV,KEY_STRUCT Key1,KEY_STRUCT Key2,KEY_STRUCT Key3);
void DES_CBC_Decipher(DES_DATA * pData,UINT nLength,DES_DATA IV,KEY_STRUCT Key);
void TDES_CBC_Decipher(DES_DATA * pData,UINT nLength,DES_DATA IV,KEY_STRUCT Key1,KEY_STRUCT Key2,KEY_STRUCT Key3);
#if DEBUG_DES
UINT DES_IsEqual(DES_DATA data1,DES_DATA data2);
#endif //DEBUG_DES
/**********************************************
  All prototypes in implementation of AES
***********************************************/
void AES_DATA2STATE(AES_DATA * pData,AES_STATE * pState);
void AES_STATE2DATA(AES_DATA * pData,AES_STATE * pState);
BYTE AES_SubByte(BYTE iByte);
BYTE AES_InvSubByte(BYTE iByte);
UINT AES_SubWord(UINT wWord);
UINT AES_InvSubWord(UINT wWord);
UINT AES_RotWord(UINT wWord);
void AES_ShiftRowLeft(int no,BYTE * pByte0,BYTE * pByte1,BYTE * pByte2,BYTE * pByte3);
void AES_ShiftRowRight(int no,BYTE * pByte0,BYTE * pByte1,BYTE * pByte2,BYTE * pByte3);
void AES_MixColumns(AES_STATE_STRUCT * pAES_State_Column);
void AES_InvMixColumns(AES_STATE_STRUCT * pAES_State_Column);
void AES_AddRoundKey(AES_STATE * pAES_State,UINT * wKey);
void AES_KeyExpansion(AES_KEY_STRUCT Key,UINT * w);
void AES_SubBytesState(AES_STATE * state);
void AES_ShiftRowsState(AES_STATE * pAES_State);
void AES_MixColumnsState(AES_STATE * pAES_State);
void AES_InvSubBytesState(AES_STATE * state);
void AES_InvShiftRowsState(AES_STATE * pAES_State);
void AES_InvMixColumnsState(AES_STATE * pAES_State);
void AES_Cipher(AES_DATA * pData,UINT * w,UINT AES_Type );
void AES_Decipher(AES_DATA * pData,UINT * w,UINT AES_Type);
void AES_ECB_Cipher(AES_DATA * Data,UINT nLength,AES_KEY_STRUCT Key);
void AES_ECB_Decipher(AES_DATA * Data,UINT nLength,AES_KEY_STRUCT Key);
void AES_CBC_Cipher(AES_DATA * Data,UINT nLength,AES_KEY_STRUCT Key,AES_DATA IV);
void AES_CBC_Decipher(AES_DATA * Data,UINT nLength,AES_KEY_STRUCT Key,AES_DATA IV);
#if DEBUG_AES
int AES_IsEqual(AES_DATA data1,AES_DATA data2);
#endif //DEBUG_AES
/*********************************************************
  All prototypes in implementation SHA-1
*********************************************************/
UINT SHA_BuildBlock512(BYTE * iBytes,UINT nLength,SHA_BLOCK_STRUCT * Blocks);
void SHA_Process(SHA_BLOCK_STRUCT * pBlock,UINT nBlockNo,SHA_HEAD_STRUCT * pHeader);
#ifdef DEBUG_SHA
int SHA_IsEqual(BYTE * b1,BYTE * b2);
#endif //DEBUG_SHA
/******************************
  Data Structure for MD5
*******************************/
typedef struct
{
	BYTE byte[16];
}MD5_HEAD_STRUCT;
/******************************
  Prototypes for MD5
******************************/
UINT MD5_BuildBlock512(BYTE * iBytes,UINT nLength,SHA_BLOCK_STRUCT * Blocks);
void MD5_Process(SHA_BLOCK_STRUCT * pBlock,UINT nBlockNo,MD5_HEAD_STRUCT * pHeader);
#if DEBUG_MD5
UINT MD5_IsEqual(BYTE * b1,BYTE * b2);
#endif //DEBUG_MD5

void HMAC_MD5_Process(BYTE * Key,UINT nKeyLength,BYTE * Text,UINT nTextLength,MD5_HEAD_STRUCT * pHead);
void HMAC_SHA_Process(BYTE * Key,UINT nKeyLength,BYTE * Text,UINT nTextLength,SHA_HEAD_STRUCT * pHead);

/*****************************************************
  Same definition as simdefs.h in verilog environment
******************************************************/
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

// authMode
#define AUTH_APPEND  0
#define AUTH_CHKVAL  1

void ipsec_sw_authentication(char *data,unsigned int data_len,char *authkey,char authAlgorithm,char *auth_result)
{
	static SHA_BLOCK_STRUCT    Block[200];
	SHA_HEAD_STRUCT     SHA_Header;
	MD5_HEAD_STRUCT     MD5_Header;
	unsigned char       *pByte=0;
	unsigned int        Blockno;
	unsigned int        count=0;

	switch(authAlgorithm)
	{
	case A_SHA1:
	case SHA1:
		Blockno=SHA_BuildBlock512(data,data_len*8,Block);
		SHA_Process(Block,Blockno,&SHA_Header);
		count=20;
		pByte=SHA_Header.byte;
		break;
	case A_HMAC_SHA1:
	case HMAC_SHA1:
		HMAC_SHA_Process(authkey,64,data,data_len,&SHA_Header);
		count=20;
		pByte=SHA_Header.byte;
		break;
	case A_MD5:
	case MD5:
		Blockno=MD5_BuildBlock512(data,data_len*8,Block);
		MD5_Process(Block,Blockno,&MD5_Header);
		count=16;
		pByte=MD5_Header.byte;
		break;
	case A_HMAC_MD5:
	case HMAC_MD5:
		HMAC_MD5_Process(authkey,64,data,data_len,&MD5_Header);
		count=16;
		pByte=MD5_Header.byte;
		break;
	}
	memcpy(auth_result,pByte,count);
	auth_result[count] = 0x00;
}


void ipsec_sw_cipher(unsigned char *pt,unsigned int pt_len, unsigned char *cipher_key, unsigned int key_size,
                            unsigned char *iv,unsigned int cipherAlgorithm,unsigned char *ct)
{
	static DES_DATA DES_data[1600];
	static AES_DATA AES_data[1600];
	DES_DATA        DES_iv;
	AES_DATA        AES_iv;
	KEY_STRUCT      DES_key0,DES_key1,DES_key2;
	AES_KEY_STRUCT  AES_key;
	BYTE            *pByte;
	unsigned int    DES_count,AES_count;
	unsigned int	i,j;

    DES_count = pt_len/8;
    AES_count = pt_len/16;
    pByte=&pt[0];
    for (i=0;i<DES_count;i++)
    {
	    for (j=0;j<8;j++)
	    {
		    DES_data[i].byte[j]=*pByte++;
	    }
    }
    
    pByte=&pt[0];
    for (i=0;i<AES_count;i++)
    {
	    for (j=0;j<16;j++)
	    {
		    AES_data[i].byte[j]=*pByte++;
	    }
    }
    
	switch(cipherAlgorithm)
	{
    	case DES_CBC_E:
    	    memcpy(DES_key0.byte,cipher_key,8);
    	    memcpy(DES_iv.byte,iv,8);
			DES_CBC_Cipher(DES_data,DES_count,DES_iv,DES_key0);
			memcpy(&ct[0],&(DES_data[0].byte[0]),DES_count*8);
			break;
			
        case DES_ECB_E:
    	    memcpy(DES_key0.byte,cipher_key,8);
			DES_ECB_Cipher(DES_data,DES_count,DES_key0);
			memcpy(&ct[0],&(DES_data[0].byte[0]),DES_count*8);
			break;
			
        case TDES_CBC_E:
    	    memcpy(DES_key0.byte,cipher_key,8);
            memcpy(DES_key1.byte,&cipher_key[8],8);
            memcpy(DES_key2.byte,&cipher_key[16],8);
	        memcpy(DES_iv.byte,iv,8);
			TDES_CBC_Cipher(DES_data,DES_count,DES_iv,DES_key0,DES_key1,DES_key2);
			memcpy(&ct[0],&(DES_data[0].byte[0]),DES_count*8);
			break;
			
        case TDES_ECB_E:
    	    memcpy(DES_key0.byte,cipher_key,8);
            memcpy(DES_key1.byte,&cipher_key[8],8);
            memcpy(DES_key2.byte,&cipher_key[16],8);
			TDES_ECB_Cipher(DES_data,DES_count,DES_key0,DES_key1,DES_key2);
			memcpy(&ct[0],&(DES_data[0].byte[0]),DES_count*8);
			break;
			
        case AES_CBC_E:
    	    memcpy(AES_key.byte,cipher_key,key_size);
            AES_key.Nk = key_size/4;
    	    memcpy(AES_iv.byte,iv,16);
			AES_CBC_Cipher(AES_data,AES_count,AES_key,AES_iv);
			memcpy(&ct[0],&(AES_data[0].byte[0]),AES_count*16);
			break;
			
        case AES_ECB_E:
    	    memcpy(AES_key.byte,cipher_key,key_size);
            AES_key.Nk = key_size/4;
			AES_ECB_Cipher(AES_data,AES_count,AES_key);
			memcpy(&ct[0],&(AES_data[0].byte[0]),AES_count*16);
			break;
			
    	case DES_CBC_D:
    	    memcpy(DES_key0.byte,cipher_key,8);
    	    memcpy(DES_iv.byte,iv,8);
			DES_CBC_Decipher(DES_data,DES_count,DES_iv,DES_key0);
			memcpy(&ct[0],&(DES_data[0].byte[0]),DES_count*8);
			break;
			
        case DES_ECB_D:
    	    memcpy(DES_key0.byte,cipher_key,8);
			DES_ECB_Decipher(DES_data,DES_count,DES_key0);
			memcpy(&ct[0],&(DES_data[0].byte[0]),DES_count*8);
			break;
			
        case TDES_CBC_D:
    	    memcpy(DES_key0.byte,cipher_key,8);
            memcpy(DES_key1.byte,&cipher_key[8],8);
            memcpy(DES_key2.byte,&cipher_key[16],8);
	        memcpy(DES_iv.byte,iv,8);
			TDES_CBC_Decipher(DES_data,DES_count,DES_iv,DES_key0,DES_key1,DES_key2);
			memcpy(&ct[0],&(DES_data[0].byte[0]),DES_count*8);
			break;
			
        case TDES_ECB_D:
    	    memcpy(DES_key0.byte,cipher_key,8);
            memcpy(DES_key1.byte,&cipher_key[8],8);
            memcpy(DES_key2.byte,&cipher_key[16],8);
			TDES_ECB_Decipher(DES_data,DES_count,DES_key0,DES_key1,DES_key2);
			memcpy(&ct[0],&(DES_data[0].byte[0]),DES_count*8);
			break;
			
        case AES_CBC_D:
    	    memcpy(AES_key.byte,cipher_key,key_size);
            AES_key.Nk = key_size/4;
    	    memcpy(AES_iv.byte,iv,16);
			AES_CBC_Decipher(AES_data,AES_count,AES_key,AES_iv);
			memcpy(&ct[0],&(AES_data[0].byte[0]),AES_count*16);
			break;
			
        case AES_ECB_D:
    	    memcpy(AES_key.byte,cipher_key,key_size);
            AES_key.Nk = key_size/4;
			AES_ECB_Decipher(AES_data,AES_count,AES_key);
			memcpy(&ct[0],&(AES_data[0].byte[0]),AES_count*16);
			break;
	}
}

void ipsec_sw_auth_cipher(unsigned int op_mode,char *data,unsigned int data_len,
                                BYTE *auth_key,char authAlgorithm,char *auth_result,
                                char *pt, unsigned int pt_len,char *cipher_key, int key_size, 
                                char *iv, char cipherAlgorithm,char *ct)
{
	static DES_DATA DES_data[1600];
	static AES_DATA AES_data[1600];
	DES_DATA        DES_iv;
	AES_DATA        AES_iv;
	KEY_STRUCT      DES_key0,DES_key1,DES_key2;
	AES_KEY_STRUCT  AES_key;
	SHA_HEAD_STRUCT SHA_Header;
	MD5_HEAD_STRUCT MD5_Header;
	BYTE            *pByte;
	static BYTE     byte[2048];
	static SHA_BLOCK_STRUCT Block[200];
	unsigned int    DES_count,AES_count,count=0;
	unsigned int    Blockno;
    unsigned int    i,j;

    memcpy(byte,data,data_len);
    memcpy(pt,data,pt_len);    
   	switch(op_mode)
	{
	    case ENC_AUTH:
		    DES_count = pt_len/8;
		    AES_count = pt_len/16;
		    pByte=&byte[0];
		    for (i=0;i<DES_count;i++)
		    {
			    for (j=0;j<8;j++)
			    {
				    DES_data[i].byte[j]=*pByte++;
			    }
		    }
		    
		    pByte=&byte[0];
		    for (i=0;i<AES_count;i++)
		    {
			    for (j=0;j<16;j++)
			    {
				    AES_data[i].byte[j]=*pByte++;
			    }
		    }
    	    
    		switch(cipherAlgorithm)
    		{
            	case DES_CBC_E:
            	case CBC_DES:
            	    memcpy(DES_key0.byte,cipher_key,8);
            	    memcpy(DES_iv.byte,iv,8);
        			DES_CBC_Cipher(DES_data,DES_count,DES_iv,DES_key0);
        			memcpy(&byte[0],&(DES_data[0].byte[0]),DES_count*8);
        			break;
        			
	            case DES_ECB_E:
	            case ECB_DES:
            	    memcpy(DES_key0.byte,cipher_key,8);
        			DES_ECB_Cipher(DES_data,DES_count,DES_key0);
        			memcpy(&byte[0],&(DES_data[0].byte[0]),DES_count*8);
        			break;
        			
    	        case TDES_CBC_E:
	            case CBC_3DES:
            	    memcpy(DES_key0.byte,cipher_key,8);
    	            memcpy(DES_key1.byte,&cipher_key[8],8);
    	            memcpy(DES_key2.byte,&cipher_key[16],8);
        	        memcpy(DES_iv.byte,iv,8);
        			TDES_CBC_Cipher(DES_data,DES_count,DES_iv,DES_key0,DES_key1,DES_key2);
        			memcpy(&byte[0],&(DES_data[0].byte[0]),DES_count*8);
        			break;
        			
	            case TDES_ECB_E:
	            case ECB_3DES:
            	    memcpy(DES_key0.byte,cipher_key,8);
    	            memcpy(DES_key1.byte,&cipher_key[8],8);
    	            memcpy(DES_key2.byte,&cipher_key[16],8);
        			TDES_ECB_Cipher(DES_data,DES_count,DES_key0,DES_key1,DES_key2);
        			memcpy(&byte[0],&(DES_data[0].byte[0]),DES_count*8);
        			break;
        			
	            case AES_CBC_E:
	            case CBC_AES:
            	    memcpy(AES_key.byte,cipher_key,key_size);
	                AES_key.Nk = key_size/4;
            	    memcpy(AES_iv.byte,iv,16);
        			AES_CBC_Cipher(AES_data,AES_count,AES_key,AES_iv);
        			memcpy(&byte[0],&(AES_data[0].byte[0]),AES_count*16);
        			break;
        			
	            case AES_ECB_E:
	            case ECB_AES:
            	    memcpy(AES_key.byte,cipher_key,key_size);
	                AES_key.Nk = key_size/4;
        			AES_ECB_Cipher(AES_data,AES_count,AES_key);
        			memcpy(&byte[0],&(AES_data[0].byte[0]),AES_count*16);
        			break;
    		}
            memcpy(ct,byte,pt_len);
//    		for (i=0;i<pt_len;i++)
//    		{
//                ipsec_result.sw_cipher[i] = byte[i];
//    		}
    		
    		switch(authAlgorithm)
    		{
        		case A_SHA1:
        		case SHA1:
        			Blockno=SHA_BuildBlock512(&byte[0],data_len*8,Block);
        			SHA_Process(Block,Blockno,&SHA_Header);
        			pByte=SHA_Header.byte;
        			count=20;
        			break;
        		case A_MD5:
        		case MD5:
        			Blockno=MD5_BuildBlock512(&byte[0],data_len*8,Block);
        			MD5_Process(Block,Blockno,&MD5_Header);
        			count=16;
        			pByte=MD5_Header.byte;
        			break;
        		case A_HMAC_SHA1:
        		case HMAC_SHA1:
        			HMAC_SHA_Process(auth_key,64,&byte[0],data_len,&SHA_Header);
        			count=20;
        			pByte=SHA_Header.byte;
        			break;
        		case A_HMAC_MD5:
        		case HMAC_MD5:
        			HMAC_MD5_Process(auth_key,64,&byte[0],data_len,&MD5_Header);
        			count=16;
        			pByte=MD5_Header.byte;
        			break;
    		}
            memcpy(auth_result,pByte,count);
//    		for (i=0;i<count;i++)
//    		{
//                ipsec_result.sw_cipher[i+pt_len] = pByte[i];
//    		}
//    		ipsec_result.sw_pkt_len = pt_len + count;
	        break;
	        
     	case AUTH_DEC:
		    DES_count = pt_len/8;
		    AES_count = pt_len/16;
		    pByte=(BYTE *)&pt[0];
    		for (i=0;i<DES_count;i++)
    		{
    			for (j=0;j<8;j++)
    			{
    				DES_data[i].byte[j]=*pByte++;
    			}
    		}
    		pByte=&byte[0];
    		for (i=0;i<AES_count;i++)
    		{
    			for (j=0;j<16;j++)
    			{
    				AES_data[i].byte[j]=*pByte++;
    			}
    		}
		    
    		switch(authAlgorithm)
    		{
        		case A_SHA1:
        		case SHA1:
        			Blockno=SHA_BuildBlock512(&byte[0],data_len*8,Block);
        			SHA_Process(Block,Blockno,&SHA_Header);
                    memcpy(auth_result,SHA_Header.byte,20);
        			break;
        		case A_MD5:
        		case MD5:
        			Blockno=MD5_BuildBlock512(&byte[0],data_len*8,Block);
        			MD5_Process(Block,Blockno,&MD5_Header);
        			memcpy(auth_result,MD5_Header.byte,16);
        			break;
        		case A_HMAC_SHA1:
        		case HMAC_SHA1:
        			HMAC_SHA_Process(auth_key,64,&byte[0],data_len,&SHA_Header);
                    memcpy(auth_result,SHA_Header.byte,20);
        			break;
        		case A_HMAC_MD5:
        		case HMAC_MD5:
        			HMAC_MD5_Process(auth_key,64,&byte[0],data_len,&MD5_Header);
        			memcpy(auth_result,MD5_Header.byte,16);
        			break;
    		}
    		
    		switch(cipherAlgorithm)
    		{
            	case DES_CBC_D:
            	case CBC_DES:
            	    memcpy(DES_key0.byte,cipher_key,8);
            	    memcpy(DES_iv.byte,iv,8);
        			DES_CBC_Decipher(DES_data,DES_count,DES_iv,DES_key0);
        			memcpy(&byte[0],&(DES_data[0].byte[0]),DES_count*8);
        			break;
        			
	            case DES_ECB_D:
	            case ECB_DES:
            	    memcpy(DES_key0.byte,cipher_key,8);
        			DES_ECB_Decipher(DES_data,DES_count,DES_key0);
        			memcpy(&byte[0],&(DES_data[0].byte[0]),DES_count*8);
        			break;
        			
    	        case TDES_CBC_D:
    	        case CBC_3DES:
            	    memcpy(DES_key0.byte,cipher_key,8);
    	            memcpy(DES_key1.byte,&cipher_key[8],8);
    	            memcpy(DES_key2.byte,&cipher_key[16],8);
        	        memcpy(DES_iv.byte,iv,8);
        			TDES_CBC_Decipher(DES_data,DES_count,DES_iv,DES_key0,DES_key1,DES_key2);
        			memcpy(&byte[0],&(DES_data[0].byte[0]),DES_count*8);
        			break;
        			
	            case TDES_ECB_D:
    	        case ECB_3DES:
            	    memcpy(DES_key0.byte,cipher_key,8);
    	            memcpy(DES_key1.byte,&cipher_key[8],8);
    	            memcpy(DES_key2.byte,&cipher_key[16],8);
        			TDES_ECB_Decipher(DES_data,DES_count,DES_key0,DES_key1,DES_key2);
        			memcpy(&byte[0],&(DES_data[0].byte[0]),DES_count*8);
        			break;
        			
	            case AES_CBC_D:
	            case CBC_AES:
            	    memcpy(AES_key.byte,cipher_key,key_size);
	                AES_key.Nk = key_size/4;
            	    memcpy(AES_iv.byte,iv,16);
        			AES_CBC_Decipher(AES_data,AES_count,AES_key,AES_iv);
        			memcpy(&byte[0],&(AES_data[0].byte[0]),AES_count*16);
        			break;
        			
	            case AES_ECB_D:
	            case ECB_AES:
            	    memcpy(AES_key.byte,cipher_key,key_size);
	                AES_key.Nk = key_size/4;
        			AES_ECB_Decipher(AES_data,AES_count,AES_key);
        			memcpy(&byte[0],&(AES_data[0].byte[0]),AES_count*16);
        			break;
    		}     	
            memcpy(ct,byte,pt_len);
     	    break;
    } 	    
}



/*****************************************************
  Transfer all the bytes into word format, add padding and generate
  512 bits blocks
  nLength is in the unit of bits, return in the unit of block (512 bits)
*************************************************/
UINT MD5_BuildBlock512(BYTE * iBytes,UINT nLength,SHA_BLOCK_STRUCT * Blocks)
{
	UINT residue_length;
	UINT orig_blocks;
	BYTE * p;
	SHA_BLOCK_STRUCT * pBlock;
	UINT WordIndex;
	UINT i,j,t;
	orig_blocks=nLength/512;
	pBlock=Blocks;
	p=iBytes;
	for (i=0;i<orig_blocks;i++)
	{
		for (j=0;j<16;j++)
		{
			pBlock->word32[j]=(UINT)((p[3]<<24)|(p[2]<<16)|(p[1]<<8)|p[0]);
			p+=4;
		}
		pBlock++;
	}
	residue_length=(nLength-orig_blocks*512)/8;
	
	WordIndex=0;
	while(residue_length>=4)
	{
		pBlock->word32[WordIndex++]=(UINT)((p[3]<<24)|(p[2]<<16)|(p[1]<<8)|p[0]);
		p+=4;
		residue_length-=4;
	}
	switch(residue_length)
	{
	case 0:
		pBlock->word32[WordIndex++]=0x00000080;
		break;
	case 1:
		pBlock->word32[WordIndex++]=(UINT)(p[0]|0x00008000);
		break;
	case 2:
		pBlock->word32[WordIndex++]=(UINT)(p[0]|(p[1]<<8)|0x00800000);
		break;
	case 3:
		pBlock->word32[WordIndex++]=(UINT)(p[0]|(p[1]<<8)|(p[2]<<16)|0x80000000);
		break;
	}
	if (WordIndex>16) printk("Should not happen!!!\n");
	if (WordIndex==16)
	{
		pBlock++;
		WordIndex=0;
	}
	if (WordIndex==15)
	{
		pBlock->word32[WordIndex]=0x0;
		pBlock++;
		WordIndex=0;
	}
	for (i=0;i<(14-WordIndex);i++)
	{
		pBlock->word32[i+WordIndex]=0x0;
	}
	pBlock->word32[14]=nLength;
	pBlock->word32[15]=0;
	pBlock++;
	t=pBlock-Blocks;
	return(t);
}
/**********************************************************************
  The following codes are mainly "Copy&Paste" from RFC1321 Sample Code
***********************************************************************/
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
/* ROTATE_LEFT rotates x left n bits.*/
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))
/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
Rotation is separate from addition to prevent recomputation.
*/

#define FF(a, b, c, d, x, s, ac) { \
(a) += F ((b), (c), (d)) + (x) + (ac); \
(a) = ROTATE_LEFT ((a), (s)); \
(a) += (b); \
}
#define GG(a, b, c, d, x, s, ac) { \
(a) += G ((b), (c), (d)) + (x) + (ac); \
(a) = ROTATE_LEFT ((a), (s)); \
(a) += (b); \
}
#define HH(a, b, c, d, x, s, ac) { \
(a) += H ((b), (c), (d)) + (x) + (ac); \
(a) = ROTATE_LEFT ((a), (s)); \
(a) += (b); \
}
#define II(a, b, c, d, x, s, ac) { \
(a) += I ((b), (c), (d)) + (x) + (ac); \
(a) = ROTATE_LEFT ((a), (s)); \
(a) += (b); \
}
void MD5_Process(SHA_BLOCK_STRUCT * pBlock,UINT nBlockNo,MD5_HEAD_STRUCT * pHeader)
{
	UINT a,b,c,d;
	UINT aa,bb,cc,dd;
	UINT * x;
	UINT i;
	a=0x67452301;
	b=0xefcdab89;
	c=0x98badcfe;
	d=0x10325476;
	for (i=0;i<nBlockNo;i++)
	{
		aa=a;
		bb=b;
		cc=c;
		dd=d;
		x=pBlock[i].word32;
		/* Round 1 */
		FF (a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
		FF (d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
		FF (c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
		FF (b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
		FF (a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
		FF (d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
		FF (c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
		FF (b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
		FF (a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
		FF (d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
		FF (c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
		FF (b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
		FF (a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
		FF (d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
		FF (c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
		FF (b, c, d, a, x[15], S14, 0x49b40821); /* 16 */
		/* Round 2 */
		GG (a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
		GG (d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
		GG (c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
		GG (b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
		GG (a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
		GG (d, a, b, c, x[10], S22, 0x2441453); /* 22 */
		GG (c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
		GG (b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
		GG (a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
		GG (d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
		GG (c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
		GG (b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
		GG (a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
		GG (d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
		GG (c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
		GG (b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */
		/* Round 3 */
		HH (a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
		HH (d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */
		HH (c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
		HH (b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
		HH (a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
		HH (d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */
		HH (c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
		HH (b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
		HH (a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
		HH (d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */
		HH (c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
		HH (b, c, d, a, x[ 6], S34, 0x4881d05); /* 44 */
		HH (a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
		HH (d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
		HH (c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
		HH (b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */
		/* Round 4 */
		II (a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
		II (d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
		II (c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
		II (b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
		II (a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
		II (d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
		II (c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
		II (b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
		II (a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
		II (d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
		II (c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
		II (b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
		II (a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
		II (d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
		II (c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
		II (b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */
		a+=aa;
		b+=bb;
		c+=cc;
		d+=dd;
	}
	pHeader->byte[0]=a&0xff;
	pHeader->byte[1]=(a>>8)&0xff;
	pHeader->byte[2]=(a>>16)&0xff;
	pHeader->byte[3]=(a>>24)&0xff;
	pHeader->byte[4]=b&0xff;
	pHeader->byte[5]=(b>>8)&0xff;
	pHeader->byte[6]=(b>>16)&0xff;
	pHeader->byte[7]=(b>>24)&0xff;
	pHeader->byte[8]=c&0xff;
	pHeader->byte[9]=(c>>8)&0xff;
	pHeader->byte[10]=(c>>16)&0xff;
	pHeader->byte[11]=(c>>24)&0xff;
	pHeader->byte[12]=d&0xff;
	pHeader->byte[13]=(d>>8)&0xff;
	pHeader->byte[14]=(d>>16)&0xff;
	pHeader->byte[15]=(d>>24)&0xff;
}


unsigned long _lrotl( unsigned long value, int shift )
{
    unsigned int i;
    
    for (i=0;i<shift;i++)
    {
        if ((value & 0x80000000) == 0x80000000)
        {
            value = (value << 1) + 1;
        }
        else
        {
            value = value << 1;
        }
    }
    return (value);
}                

/*****************************************************
  Transfer all the bytes into word format, add padding and generate
  512 bits blocks
  nLength is in the unit of bits, return in the unit of block (512 bits)
*************************************************/
UINT SHA_BuildBlock512(BYTE * iBytes,UINT nLength,SHA_BLOCK_STRUCT * Blocks)
{
	UINT residue_length;
	UINT orig_blocks;
	BYTE * p;
	SHA_BLOCK_STRUCT * pBlock;
	UINT WordIndex;
	UINT i,j,t;
	orig_blocks=nLength/512;
	pBlock=Blocks;
	p=iBytes;
	for (i=0;i<orig_blocks;i++)
	{
		for (j=0;j<16;j++)
		{
			pBlock->word32[j]=(UINT)((p[0]<<24)|(p[1]<<16)|(p[2]<<8)|p[3]);
			p+=4;
		}
		pBlock++;
	}
	residue_length=(nLength-orig_blocks*512)/8;
	
	WordIndex=0;
	while(residue_length>=4)
	{
		pBlock->word32[WordIndex++]=(UINT)((p[0]<<24)|(p[1]<<16)|(p[2]<<8)|p[3]);
		p+=4;
		residue_length-=4;
	}
	switch(residue_length)
	{
	case 0:
		pBlock->word32[WordIndex++]=0x80000000;
		break;
	case 1:
		pBlock->word32[WordIndex++]=(UINT)((p[0]<<24)|0x00800000);
		break;
	case 2:
		pBlock->word32[WordIndex++]=(UINT)((p[0]<<24)|(p[1]<<16)|0x00008000);
		break;
	case 3:
		pBlock->word32[WordIndex++]=(UINT)((p[0]<<24)|(p[1]<<16)|(p[2]<<8)|0x80);
		break;
	}
	if (WordIndex>16) printk("Should not happen!!!\n");
	if (WordIndex==16)
	{
		pBlock++;
		WordIndex=0;
	}

	if (WordIndex==15)
	{
		pBlock->word32[WordIndex]=0x0;
		pBlock++;
		WordIndex=0;
	}
	for (i=0;i<(14-WordIndex);i++)
	{
		pBlock->word32[i+WordIndex]=0x0;
	}
	pBlock->word32[14]=0x0;
	pBlock->word32[15]=nLength;
	pBlock++;
	t=pBlock-Blocks;
	return(t);
}
//========== 0<=t<=19
UINT f0(UINT B,UINT C,UINT D)
{
	UINT t;
	t=(B & C)|((~B) & D);
	return(t);
}
//======20<=t<=39; 60<=t<=79
UINT f1(UINT B,UINT C,UINT D)
{
	UINT t;
	t=B ^ C ^ D;
	return(t);
}
//== 40<=t<=59
UINT f2(UINT B,UINT C,UINT D)
{
	UINT t;
	t=(B & C)|(B & D)|(C & D);
	return(t);
}
#define K0 0x5a827999
#define K1 0x6ed9eba1
#define K2 0x8f1bbcdc
#define K3 0xca62c1d6
void SHA_Process(SHA_BLOCK_STRUCT * pBlock,UINT nBlockNo,SHA_HEAD_STRUCT * pHeader)
{
	UINT H0,H1,H2,H3,H4,A,B,C,D,E,TEMP;
	UINT W[80];
	UINT i,j;
	H0=0x67452301;
	H1=0xefcdab89;
	H2=0x98badcfe;
	H3=0x10325476;
	H4=0xc3d2e1f0;
	for (i=0;i<nBlockNo;i++)
	{
		for (j=0;j<16;j++)
		{
			W[j]=pBlock[i].word32[j];
		}
		for (j=16;j<80;j++)
		{
			W[j]=W[j-3]^W[j-8]^W[j-14]^W[j-16];
			W[j]=_lrotl(W[j],1);
		}
		A=H0;
		B=H1;
		C=H2;
		D=H3;
		E=H4;
		for (j=0;j<80;j++)
		{
			if (j<20)
				TEMP=f0(B,C,D)+K0;
			else if (j<40)
				TEMP=f1(B,C,D)+K1;
			else if (j<60)
				TEMP=f2(B,C,D)+K2;
			else
				TEMP=f1(B,C,D)+K3;
			TEMP+=_lrotl(A,5)+E+W[j];
			E=D;
			D=C;
			C=_lrotl(B,30);
			B=A;
			A=TEMP;
		}
		H0+=A;
		H1+=B;
		H2+=C;
		H3+=D;
		H4+=E;
	}
	pHeader->byte[0]=(H0>>24)&0xff;
	pHeader->byte[1]=(H0>>16)&0xff;
	pHeader->byte[2]=(H0>>8) &0xff;
	pHeader->byte[3]=H0      &0xff;
	pHeader->byte[4]=(H1>>24)&0xff;
	pHeader->byte[5]=(H1>>16)&0xff;
	pHeader->byte[6]=(H1>>8) &0xff;
	pHeader->byte[7]=H1      &0xff;
	pHeader->byte[8]=(H2>>24)&0xff;
	pHeader->byte[9]=(H2>>16)&0xff;
	pHeader->byte[10]=(H2>>8) &0xff;
	pHeader->byte[11]=H2      &0xff;
	pHeader->byte[12]=(H3>>24)&0xff;
	pHeader->byte[13]=(H3>>16)&0xff;
	pHeader->byte[14]=(H3>>8) &0xff;
	pHeader->byte[15]=H3      &0xff;
	pHeader->byte[16]=(H4>>24)&0xff;
	pHeader->byte[17]=(H4>>16)&0xff;
	pHeader->byte[18]=(H4>>8) &0xff;
	pHeader->byte[19]=H4      &0xff;
}

#define IPAD  0x36
#define OPAD  0x5c

/*****************************
  nKeyLength should be less than 64 bytes, greater than 128 bytes, nTextLength should be less than
  6336 bytes
*****************************/
void HMAC_MD5_Process(BYTE * Key,UINT nKeyLength,BYTE * Text,UINT nTextLength,MD5_HEAD_STRUCT * pHead)
{
	static SHA_BLOCK_STRUCT Blocks[100]; // Support up to 100*64 =6400 bytes
	static BYTE tByte[6400];
	MD5_HEAD_STRUCT tHead;
	UINT nByte ;
	UINT nBlock;
	UINT i;
	nByte=0;
	for (i=0;i<nKeyLength;i++)
	{
		tByte[i]=Key[i]^IPAD;
		nByte++;
	}
	for (;i<64;i++)
	{
		tByte[i]=IPAD;
		nByte++;
	}
	memcpy(&tByte[64],Text,nTextLength);
	nByte+=nTextLength;
	nBlock=MD5_BuildBlock512(tByte,nByte*8,Blocks);
	MD5_Process(Blocks,nBlock,&tHead);
	nByte=0;
	for (i=0;i<nKeyLength;i++)
	{
		tByte[i]=Key[i]^OPAD;
		nByte++;
	}
	for (;i<64;i++)
	{
		tByte[i]=OPAD;
		nByte++;
	}
	memcpy(&tByte[64],tHead.byte,16);
	nByte+=16;
	nBlock=MD5_BuildBlock512(tByte,nByte*8,Blocks);
	MD5_Process(Blocks,nBlock,pHead);
}
void HMAC_SHA_Process(BYTE * Key,UINT nKeyLength,BYTE * Text,UINT nTextLength,SHA_HEAD_STRUCT * pHead)
{
	static SHA_BLOCK_STRUCT Blocks[100]; // Support up to 100*64 =6400 bytes
	static BYTE tByte[6400];
	SHA_HEAD_STRUCT tHead;
	UINT nByte ;
	UINT nBlock;
	UINT i;
	nByte=0;
	for (i=0;i<nKeyLength;i++)
	{
		tByte[i]=Key[i]^IPAD;
		nByte++;
	}
	for (;i<64;i++)
	{
		tByte[i]=IPAD;
		nByte++;
	}
	memcpy(&tByte[64],Text,nTextLength);
	nByte+=nTextLength;
	nBlock=SHA_BuildBlock512(tByte,nByte*8,Blocks);
	SHA_Process(Blocks,nBlock,&tHead);
	nByte=0;
	for (i=0;i<nKeyLength;i++)
	{
		tByte[i]=Key[i]^OPAD;
		nByte++;
	}
	for (;i<64;i++)
	{
		tByte[i]=OPAD;
		nByte++;
	}
	memcpy(&tByte[64],tHead.byte,20);
	nByte+=20;
	nBlock=SHA_BuildBlock512(tByte,nByte*8,Blocks);
	SHA_Process(Blocks,nBlock,pHead);
}


/******************************************
    GF(2^8) calculation
	polynomial is g(x)=x^8+x^4+x^3+x+1
******************************************/

BYTE Log[256] = 
{
	  0,   0,  25,   1,  50,   2,  26, 198,  75, 199,  27, 104,  51, 238, 223,   3, 
	100,   4, 224,  14,  52, 141, 129, 239,  76, 113,   8, 200, 248, 105,  28, 193, 
	125, 194,  29, 181, 249, 185,  39, 106,  77, 228, 166, 114, 154, 201,   9, 120, 
	101,  47, 138,   5,  33,  15, 225,  36,  18, 240, 130,  69,  53, 147, 218, 142, 
	150, 143, 219, 189,  54, 208, 206, 148,  19,  92, 210, 241,  64,  70, 131,  56, 
	102, 221, 253,  48, 191,   6, 139,  98, 179,  37, 226, 152,  34, 136, 145,  16, 
	126, 110,  72, 195, 163, 182,  30,  66,  58, 107,  40,  84, 250, 133,  61, 186, 
	 43, 121,  10,  21, 155, 159,  94, 202,  78, 212, 172, 229, 243, 115, 167,  87, 
	175,  88, 168,  80, 244, 234, 214, 116,  79, 174, 233, 213, 231, 230, 173, 232, 
	 44, 215, 117, 122, 235,  22,  11, 245,  89, 203,  95, 176, 156, 169,  81, 160, 
	127,  12, 246, 111,  23, 196,  73, 236, 216,  67,  31,  45, 164, 118, 123, 183, 
	204, 187,  62,  90, 251,  96, 177, 134,  59,  82, 161, 108, 170,  85,  41, 157, 
	151, 178, 135, 144,  97, 190, 220, 252, 188, 149, 207, 205,  55,  63,  91, 209, 
	 83,  57, 132,  60,  65, 162, 109,  71,  20,  42, 158,  93,  86, 242, 211, 171, 
	 68,  17, 146, 217,  35,  32,  46, 137, 180, 124, 184,  38, 119, 153, 227, 165, 
	103,  74, 237, 222, 197,  49, 254,  24,  13,  99, 140, 128, 192, 247, 112,   7, 
};

BYTE Exp[256] = 
{
	  1,   3,   5,  15,  17,  51,  85, 255,  26,  46, 114, 150, 161, 248,  19,  53, 
	 95, 225,  56,  72, 216, 115, 149, 164, 247,   2,   6,  10,  30,  34, 102, 170, 
	229,  52,  92, 228,  55,  89, 235,  38, 106, 190, 217, 112, 144, 171, 230,  49, 
	 83, 245,   4,  12,  20,  60,  68, 204,  79, 209, 104, 184, 211, 110, 178, 205, 
	 76, 212, 103, 169, 224,  59,  77, 215,  98, 166, 241,   8,  24,  40, 120, 136, 
	131, 158, 185, 208, 107, 189, 220, 127, 129, 152, 179, 206,  73, 219, 118, 154, 
	181, 196,  87, 249,  16,  48,  80, 240,  11,  29,  39, 105, 187, 214,  97, 163, 
	254,  25,  43, 125, 135, 146, 173, 236,  47, 113, 147, 174, 233,  32,  96, 160, 
	251,  22,  58,  78, 210, 109, 183, 194,  93, 231,  50,  86, 250,  21,  63,  65, 
	195,  94, 226,  61,  71, 201,  64, 192,  91, 237,  44, 116, 156, 191, 218, 117, 
	159, 186, 213, 100, 172, 239,  42, 126, 130, 157, 188, 223, 122, 142, 137, 128, 
	155, 182, 193,  88, 232,  35, 101, 175, 234,  37, 111, 177, 200,  67, 197,  84, 
	252,  31,  33,  99, 165, 244,   7,   9,  27,  45, 119, 153, 176, 203,  70, 202, 
	 69, 207,  74, 222, 121, 139, 134, 145, 168, 227,  62,  66, 198,  81, 243,  14, 
	 18,  54,  90, 238,  41, 123, 141, 140, 143, 138, 133, 148, 167, 242,  13,  23, 
	 57,  75, 221, 124, 132, 151, 162, 253,  28,  36, 108, 180, 199,  82, 246,   1, 
};
void AES_DATA2STATE(AES_DATA * pData,AES_STATE * pState)
{
	UINT i;
	for (i=0;i<4;i++)
	{
		pState->state[i].bytes.byte0=pData->byte[4*i];
		pState->state[i].bytes.byte1=pData->byte[4*i+1];
		pState->state[i].bytes.byte2=pData->byte[4*i+2];
		pState->state[i].bytes.byte3=pData->byte[4*i+3];
	}
}
void AES_STATE2DATA(AES_DATA * pData,AES_STATE * pState)
{
	UINT i;
	for (i=0;i<4;i++)
	{
		pData->byte[4*i]=pState->state[i].bytes.byte0;
		pData->byte[4*i+1]=pState->state[i].bytes.byte1;
		pData->byte[4*i+2]=pState->state[i].bytes.byte2;
		pData->byte[4*i+3]=pState->state[i].bytes.byte3;
	}
}

BYTE Mul(BYTE a,BYTE b)
{
	BYTE c,d;
	if (a && b)
	{
		c=Log[a];
		d=Log[b];
		c=(c+d)%255;
		c=Exp[c];
	}
	else
		c=0;
	return(c);
}
BYTE Mul_Inv(BYTE a)
{
	BYTE b;
	if (a)
	{
		b=Log[a];
		b=255-b;
		b=Exp[b];
		return(b);
	}
	else
		return(a);
}
BYTE AES_SubByte(BYTE iByte)
{
	static BYTE SubByte_Table[256]=
	{
		 99,124,119,123,242,107,111,197, 48,  1,103, 43,254,215,171,118,
		202,130,201,125,250, 89, 71,240,173,212,162,175,156,164,114,192,
		183,253,147, 38, 54, 63,247,204, 52,165,229,241,113,216, 49, 21,
		  4,199, 35,195, 24,150,  5,154,  7, 18,128,226,235, 39,178,117,
		  9,131, 44, 26, 27,110, 90,160, 82, 59,214,179, 41,227, 47,132,
		 83,209,  0,237, 32,252,177, 91,106,203,190, 57, 74, 76, 88,207,
		208,239,170,251, 67, 77, 51,133, 69,249,  2,127, 80, 60,159,168,
		 81,163, 64,143,146,157, 56,245,188,182,218, 33, 16,255,243,210,
		205, 12, 19,236, 95,151, 68, 23,196,167,126, 61,100, 93, 25,115,
		 96,129, 79,220, 34, 42,144,136, 70,238,184, 20,222, 94, 11,219,
		224, 50, 58, 10, 73,  6, 36, 92,194,211,172, 98,145,149,228,121,
		231,200, 55,109,141,213, 78,169,108, 86,244,234,101,122,174,  8,
		186,120, 37, 46, 28,166,180,198,232,221,116, 31, 75,189,139,138,
		112, 62,181,102, 72,  3,246, 14, 97, 53, 87,185,134,193, 29,158,
		225,248,152, 17,105,217,142,148,155, 30,135,233,206, 85, 40,223,
		140,161,137, 13,191,230, 66,104, 65,153, 45, 15,176, 84,187, 22,
	};
	return(SubByte_Table[iByte]);
}
BYTE AES_InvSubByte(BYTE iByte)
{
	static BYTE InvSubByte_Table[256]=
	{
		 82,  9,106,213, 48, 54,165, 56,191, 64,163,158,129,243,215,251,
		124,227, 57,130,155, 47,255,135, 52,142, 67, 68,196,222,233,203,
		 84,123,148, 50,166,194, 35, 61,238, 76,149, 11, 66,250,195, 78,
		  8, 46,161,102, 40,217, 36,178,118, 91,162, 73,109,139,209, 37,
		114,248,246,100,134,104,152, 22,212,164, 92,204, 93,101,182,146,
		108,112, 72, 80,253,237,185,218, 94, 21, 70, 87,167,141,157,132,
		144,216,171,  0,140,188,211, 10,247,228, 88,  5,184,179, 69,  6,
		208, 44, 30,143,202, 63, 15,  2,193,175,189,  3,  1, 19,138,107,
		 58,145, 17, 65, 79,103,220,234,151,242,207,206,240,180,230,115,
		150,172,116, 34,231,173, 53,133,226,249, 55,232, 28,117,223,110,
		 71,241, 26,113, 29, 41,197,137,111,183, 98, 14,170, 24,190, 27,
		252, 86, 62, 75,198,210,121, 32,154,219,192,254,120,205, 90,244,
		 31,221,168, 51,136,  7,199, 49,177, 18, 16, 89, 39,128,236, 95,
		 96, 81,127,169, 25,181, 74, 13, 45,229,122,159,147,201,156,239,
		160,224, 59, 77,174, 42,245,176,200,235,187, 60,131, 83,153, 97,
		 23, 43,  4,126,186,119,214, 38,225,105, 20, 99, 85, 33, 12,125,
	};
	return(InvSubByte_Table[iByte]);
}


UINT AES_SubWord(UINT wWord)
{
	UINT t;
	UINT w;
	w=0;
	t=(wWord & 0xff000000)>>24;
	t=AES_SubByte((BYTE)t);
	w|=(t<<24);
	t=(wWord & 0xff0000)>>16;
	t=AES_SubByte((BYTE)t);
	w|=(t<<16);
	t=(wWord & 0xff00)>>8;
	t=AES_SubByte((BYTE)t);
	w|=(t<<8);
	t=(wWord & 0xff);
	t=AES_SubByte((BYTE)t);
	w|=t;
	return(w);
}
UINT AES_InvSubWord(UINT wWord)
{
	UINT t;
	UINT w;
	w=0;
	t=(wWord & 0xff000000)>>24;
	t=AES_InvSubByte((BYTE)t);
	w|=(t<<24);
	t=(wWord & 0xff0000)>>16;
	t=AES_InvSubByte((BYTE)t);
	w|=(t<<16);
	t=(wWord & 0xff00)>>8;
	t=AES_InvSubByte((BYTE)t);
	w|=(t<<8);
	t=(wWord & 0xff);
	t=AES_InvSubByte((BYTE)t);
	w|=t;
	return(w);
}


UINT AES_RotWord(UINT wWord)
{
	UINT t;
	UINT w;
	w=0;
	t=(wWord&0xff000000)>>24;
	w|=t;
	t=(wWord&0xff0000)>>16;
	w|=(t<<24);
	t=(wWord&0xff00)>>8;
	w|=(t<<16);
	t=(wWord&0xff);
	w|=(t<<8);
	return(w);
}
/*********************************
  support only 1,2,3 left shift
*********************************/
void AES_ShiftRowLeft(int no,BYTE * pByte0,BYTE * pByte1,BYTE * pByte2,BYTE * pByte3)
{
	BYTE b0,b1,b2,b3;
	b0=*pByte0;
	b1=*pByte1;
	b2=*pByte2;
	b3=*pByte3;
	switch(no)
	{
	case 1:
		*pByte0=b1;
		*pByte1=b2;
		*pByte2=b3;
		*pByte3=b0;
		break;
	case 2:
		*pByte0=b2;
		*pByte1=b3;
		*pByte2=b0;
		*pByte3=b1;
		break;
	case 3:
		*pByte0=b3;
		*pByte1=b0;
		*pByte2=b1;
		*pByte3=b2;
		break;
	}
}
void AES_ShiftRowRight(int no,BYTE * pByte0,BYTE * pByte1,BYTE * pByte2,BYTE * pByte3)
{
	BYTE b0,b1,b2,b3;
	b0=*pByte0;
	b1=*pByte1;
	b2=*pByte2;
	b3=*pByte3;
	switch(no)
	{
	case 1:
		*pByte0=b3;
		*pByte1=b0;
		*pByte2=b1;
		*pByte3=b2;
		break;
	case 2:
		*pByte0=b2;
		*pByte1=b3;
		*pByte2=b0;
		*pByte3=b1;
		break;
	case 3:
		*pByte0=b1;
		*pByte1=b2;
		*pByte2=b3;
		*pByte3=b0;
		break;
	}
}

void AES_MixColumns(AES_STATE_STRUCT * pAES_State_Column)
{
	AES_STATE_STRUCT Column;
	Column.bytes.byte0=Mul(0x02,pAES_State_Column->bytes.byte0)^
		               Mul(0x03,pAES_State_Column->bytes.byte1)^
					   pAES_State_Column->bytes.byte2^
					   pAES_State_Column->bytes.byte3;
	Column.bytes.byte1=pAES_State_Column->bytes.byte0^
		               Mul(0x02,pAES_State_Column->bytes.byte1)^
					   Mul(0x03,pAES_State_Column->bytes.byte2)^
					   pAES_State_Column->bytes.byte3;
	Column.bytes.byte2=pAES_State_Column->bytes.byte0^
		               pAES_State_Column->bytes.byte1^
					   Mul(0x02,pAES_State_Column->bytes.byte2)^
					   Mul(0x03,pAES_State_Column->bytes.byte3);
	Column.bytes.byte3=Mul(0x03,pAES_State_Column->bytes.byte0)^
		               pAES_State_Column->bytes.byte1^
					   pAES_State_Column->bytes.byte2^
					   Mul(0x02,pAES_State_Column->bytes.byte3);
	*pAES_State_Column=Column;
}
void AES_InvMixColumns(AES_STATE_STRUCT * pAES_State_Column)
{
	AES_STATE_STRUCT Column;
	Column.bytes.byte0=Mul(0x0e,pAES_State_Column->bytes.byte0)^
		               Mul(0x0b,pAES_State_Column->bytes.byte1)^
					   Mul(0x0d,pAES_State_Column->bytes.byte2)^
					   Mul(0x09,pAES_State_Column->bytes.byte3);
	Column.bytes.byte1=Mul(0x09,pAES_State_Column->bytes.byte0)^
		               Mul(0x0e,pAES_State_Column->bytes.byte1)^
					   Mul(0x0b,pAES_State_Column->bytes.byte2)^
					   Mul(0x0d,pAES_State_Column->bytes.byte3);
	Column.bytes.byte2=Mul(0x0d,pAES_State_Column->bytes.byte0)^
		               Mul(0x09,pAES_State_Column->bytes.byte1)^
					   Mul(0x0e,pAES_State_Column->bytes.byte2)^
					   Mul(0x0b,pAES_State_Column->bytes.byte3);
	Column.bytes.byte3=Mul(0x0b,pAES_State_Column->bytes.byte0)^
		               Mul(0x0d,pAES_State_Column->bytes.byte1)^
					   Mul(0x09,pAES_State_Column->bytes.byte2)^
					   Mul(0x0e,pAES_State_Column->bytes.byte3);
	*pAES_State_Column=Column;
}
void AES_AddRoundKey(AES_STATE * pAES_State,UINT * wKey)
{
	UINT i;
	UINT t;
	for (i=0;i<4;i++)
	{
		t=(pAES_State->state[i].word32 ^ wKey[i]);
		pAES_State->state[i].word32 = t;
	}
}
/****************************************************
  Gernerate 4*(Nr+1) key words
****************************************************/
void AES_KeyExpansion(AES_KEY_STRUCT Key,UINT * w)
{
	UINT Nk,Nr=0;
	UINT t=0,i;
	static UINT Rcon[31]=
	{ 
		0x00000000, 0x01000000, 0x02000000, 0x04000000, 0x08000000, 
		0x10000000, 0x20000000, 0x40000000, 0x80000000,	0x1b000000, 
		0x36000000, 0x6c000000, 0xd8000000, 0xab000000, 0x4d000000,
		0x9a000000, 0x2f000000, 0x5e000000, 0xbc000000, 0x63000000, 
		0xc6000000, 0x97000000, 0x35000000, 0x6a000000, 0xd4000000, 
		0xb3000000, 0x7d000000, 0xfa000000, 0xef000000,	0xc5000000,
		0x91000000
	};

	Nk=Key.Nk;
	switch(Nk)
	{
	case 4:
		Nr=10;
		break;
	case 6:
		Nr=12;
		break;
	case 8:
		Nr=14;
		break;
	}
	for (i=0;i<Nk;i++)
	{
		t=(Key.byte[4*i]<<24)|(Key.byte[4*i+1]<<16)|(Key.byte[4*i+2]<<8)|(Key.byte[4*i+3]);
		w[i]=t;
	}
	for (i=Nk;i<4*(Nr+1);i++)
	{
		if ((i%Nk)==0)
			t=AES_SubWord(AES_RotWord(t))^Rcon[i/Nk];
		else if ((Nk>6)&&((i%Nk)==4))
			t=AES_SubWord(t);
		t^=w[i-Nk];
		w[i]=t;
	}
}
void AES_SubBytesState(AES_STATE * state)
{
	UINT i;
	for (i=0;i<4;i++)
	{
		state->state[i].word32=AES_SubWord(state->state[i].word32);
	}
}
void AES_ShiftRowsState(AES_STATE * pAES_State)
{
	AES_ShiftRowLeft(1,&(pAES_State->state[0].bytes.byte1),&(pAES_State->state[1].bytes.byte1),
		               &(pAES_State->state[2].bytes.byte1),&(pAES_State->state[3].bytes.byte1));
	AES_ShiftRowLeft(2,&(pAES_State->state[0].bytes.byte2),&(pAES_State->state[1].bytes.byte2),
		               &(pAES_State->state[2].bytes.byte2),&(pAES_State->state[3].bytes.byte2));
	AES_ShiftRowLeft(3,&(pAES_State->state[0].bytes.byte3),&(pAES_State->state[1].bytes.byte3),
		               &(pAES_State->state[2].bytes.byte3),&(pAES_State->state[3].bytes.byte3));
}
void AES_MixColumnsState(AES_STATE * pAES_State)
{
	UINT i;
	for (i=0;i<4;i++)
	{
		AES_MixColumns(&pAES_State->state[i]);
	}
}
void AES_InvSubBytesState(AES_STATE * state)
{
	UINT i;
	for (i=0;i<4;i++)
	{
		state->state[i].word32=AES_InvSubWord(state->state[i].word32);
	}
}
void AES_InvShiftRowsState(AES_STATE * pAES_State)
{
	AES_ShiftRowRight(1,&(pAES_State->state[0].bytes.byte1),&(pAES_State->state[1].bytes.byte1),
		               &(pAES_State->state[2].bytes.byte1),&(pAES_State->state[3].bytes.byte1));
	AES_ShiftRowRight(2,&(pAES_State->state[0].bytes.byte2),&(pAES_State->state[1].bytes.byte2),
		               &(pAES_State->state[2].bytes.byte2),&(pAES_State->state[3].bytes.byte2));
	AES_ShiftRowRight(3,&(pAES_State->state[0].bytes.byte3),&(pAES_State->state[1].bytes.byte3),
		               &(pAES_State->state[2].bytes.byte3),&(pAES_State->state[3].bytes.byte3));
}
void AES_InvMixColumnsState(AES_STATE * pAES_State)
{
	UINT i;
	for (i=0;i<4;i++)
	{
		AES_InvMixColumns(&pAES_State->state[i]);
	}
}

void AES_Cipher(AES_DATA * pData,UINT * w,UINT AES_Type )
{
	UINT Nr;
	UINT i;
	AES_STATE State;
	switch(AES_Type)
	{
	default:
	case AES_128:
		Nr=10;
		break;
	case AES_192:
		Nr=12;
		break;
	case AES_256:
		Nr=14;
		break;
	}
	AES_DATA2STATE(pData,&State);
	AES_AddRoundKey(&State,w);
	for (i=1;i<Nr;i++)
	{
		AES_SubBytesState(&State);
		AES_ShiftRowsState(&State);
		AES_MixColumnsState(&State);
		AES_AddRoundKey(&State,&w[4*i]);
	}
	AES_SubBytesState(&State);
	AES_ShiftRowsState(&State);
	AES_AddRoundKey(&State,&w[4*Nr]);
	AES_STATE2DATA(pData,&State);
}
void AES_Decipher(AES_DATA * pData,UINT * w,UINT AES_Type)
{
	UINT Nr;
	UINT i;
	AES_STATE State;
	switch(AES_Type)
	{
	default:
	case AES_128:
		Nr=10;
		break;
	case AES_192:
		Nr=12;
		break;
	case AES_256:
		Nr=14;
		break;
	}
	AES_DATA2STATE(pData,&State);
	AES_AddRoundKey(&State,&w[4*Nr]);
	AES_InvShiftRowsState(&State);
	AES_InvSubBytesState(&State);
	for (i=Nr-1;i>=1;i--)
	{
		AES_AddRoundKey(&State,&w[4*i]);
		AES_InvMixColumnsState(&State);
		AES_InvShiftRowsState(&State);
		AES_InvSubBytesState(&State);
	}
	AES_AddRoundKey(&State,w);
	AES_STATE2DATA(pData,&State);
}
void AES_ECB_Cipher(AES_DATA * Data,UINT nLength,AES_KEY_STRUCT Key)
{
	UINT w[60];
	UINT AES_Type=0;
	UINT i;
	switch(Key.Nk)
	{
	case 4:
		AES_Type=AES_128;
		break;
	case 6:
		AES_Type=AES_192;
		break;
	case 8:
		AES_Type=AES_256;
		break;
	}
	AES_KeyExpansion(Key,w);
	for (i=0;i<nLength;i++)
	{
		AES_Cipher(&Data[i],w,AES_Type);
	}
}
void AES_ECB_Decipher(AES_DATA * Data,UINT nLength,AES_KEY_STRUCT Key)
{
	UINT w[60];
	UINT AES_Type=0;
	UINT i;
	switch(Key.Nk)
	{
	case 4:
		AES_Type=AES_128;
		break;
	case 6:
		AES_Type=AES_192;
		break;
	case 8:
		AES_Type=AES_256;
		break;
	}
	AES_KeyExpansion(Key,w);
	for (i=0;i<nLength;i++)
	{
		AES_Decipher(&Data[i],w,AES_Type);
	}
}
void AES_CBC_Cipher(AES_DATA * Data,UINT nLength,AES_KEY_STRUCT Key,AES_DATA IV)
{
	AES_DATA t;
	UINT w[60];
	UINT AES_Type=0;
	UINT i,j;
	switch(Key.Nk)
	{
	case 4:
		AES_Type=AES_128;
		break;
	case 6:
		AES_Type=AES_192;
		break;
	case 8:
		AES_Type=AES_256;
		break;
	}
	AES_KeyExpansion(Key,w);
	t=IV;
	for (i=0;i<nLength;i++)
	{
		for (j=0;j<16;j++)
		{
			Data[i].byte[j]^=t.byte[j];
		}
		AES_Cipher(&Data[i],w,AES_Type);
		t=Data[i];
	}
}
void AES_CBC_Decipher(AES_DATA * Data,UINT nLength,AES_KEY_STRUCT Key,AES_DATA IV)
{
	AES_DATA t1,t2;
	UINT w[60];
	UINT AES_Type=0;
	UINT i,j;
	switch(Key.Nk)
	{
	case 4:
		AES_Type=AES_128;
		break;
	case 6:
		AES_Type=AES_192;
		break;
	case 8:
		AES_Type=AES_256;
		break;
	}
	AES_KeyExpansion(Key,w);
	t1=IV;
	for (i=0;i<nLength;i++)
	{
		t2=Data[i];
		AES_Decipher(&Data[i],w,AES_Type);
		for (j=0;j<16;j++)
		{
			Data[i].byte[j]^=t1.byte[j];
		}
		t1=t2;
	}
}

#if 0
void GenRandBytes(BYTE * pByte,UINT nLength)
{
	UINT i;
	//srand((unsigned int)time(0));
	for (i=0;i<nLength;i++)
	{
		pByte[i]=rand() & 0xff;
	}
}
#endif

//  DES_KeyCheckSum is used to make sure the KEY is in the right format: the LSB of every BYTE is the
//  odd checksum for the byte
void DES_KeyCheckSum( KEY_STRUCT * pKey)
{
	UINT i;
	UINT j;
	BYTE chksum;
	for (i=0;i<8;i++)
	{
		chksum=1;
		for (j=1;j<8;j++)
		{
			chksum^=((pKey->byte[i]>>j)&0x1);
		}
		pKey->byte[i]&=0xfe;
		pKey->byte[i]|=chksum;
	}
}
/**************************
Generate 64 bits random data, these data is output to 8 bytes
**************************/
#if 0
void FAKE_GenKey(BYTE * bytes)
{
	UINT i;
	//srand((unsigned)time(0));
	for (i=0;i<8;i++)
		bytes[i]=rand() &  0xff;
}
#endif

void DES_IP(DES_DATA * pData)
{
	static UINT IP_Sequence[64]= 
	{   57,49,41,33,25,17, 9, 1,
		59,51,43,35,27,19,11, 3,
		61,53,45,37,29,21,13, 5,
		63,55,47,39,31,23,15, 7,
		56,48,40,32,24,16, 8, 0,
		58,50,42,34,26,18,10, 2,
		60,52,44,36,28,20,12, 4,
		62,54,46,38,30,22,14, 6,
	};
	UINT D1[64],D2[64];
	UINT i,j;
	BYTE t;
	for (i=0;i<8;i++)
	{
		for (j=0;j<8;j++)
		{
			D1[i*8+j]=(pData->byte[i]>>(7-j))&0x1;
		}
	}
	for (i=0;i<64;i++)
	{
		D2[i]=D1[IP_Sequence[i]];
	}
	for (i=0;i<8;i++)
	{
		t=0;
		for (j=0;j<8;j++)
		{
			t=t|(D2[8*i+j]<<(7-j));
		}
		pData->byte[i]=t;
	}
}
void DES_IP_R(DES_DATA * pData)
{
	static UINT IP_Sequence_R[64]= 
	{   39, 7,47,15,55,23,63,31,
		38, 6,46,14,54,22,62,30,
		37, 5,45,13,53,21,61,29,
		36, 4,44,12,52,20,60,28,
		35, 3,43,11,51,19,59,27,
		34, 2,42,10,50,18,58,26,
		33, 1,41, 9,49,17,57,25,
		32, 0,40, 8,48,16,56,24,
	};
	UINT D1[64],D2[64];
	UINT i,j;
	BYTE t;
	for (i=0;i<8;i++)
	{
		for (j=0;j<8;j++)
		{
			D1[i*8+j]=(pData->byte[i]>>(7-j))&0x1;
		}
	}
	for (i=0;i<64;i++)
	{
		D2[i]=D1[IP_Sequence_R[i]];
	}
	for (i=0;i<8;i++)
	{
		t=0;
		for (j=0;j<8;j++)
		{
			t=t|(D2[8*i+j]<<(7-j));
		}
		pData->byte[i]=t;
	}
}
void DES_LRSplit(DES_DATA * pData, UINT *pL, UINT *pR)
{
	*pL = (pData->byte[0]<<24)+(pData->byte[1]<<16)+(pData->byte[2]<<8)+pData->byte[3];
	*pR = (pData->byte[4]<<24)+(pData->byte[5]<<16)+(pData->byte[6]<<8)+pData->byte[7];
}
void DES_LRCombine(DES_DATA * pData, UINT L, UINT R)
{
	pData->byte[0]=(L & 0xff000000)>>24;
	pData->byte[1]=(L & 0x00ff0000)>>16;
	pData->byte[2]=(L & 0x0000ff00)>>8;
	pData->byte[3]=(L & 0x000000ff);
	pData->byte[4]=(R & 0xff000000)>>24;
	pData->byte[5]=(R & 0x00ff0000)>>16;
	pData->byte[6]=(R & 0x0000ff00)>>8;
	pData->byte[7]=(R & 0x000000ff);
}
void DES_E( UINT R, UINT * pEh32, UINT * pEl16)
{
	static UINT E_Sequence[48]=
	{	31, 0, 1, 2, 3, 4, 3, 4,
		 5, 6, 7, 8, 7, 8, 9,10,
		11,12,11,12,13,14,15,16,
		15,16,17,18,19,20,19,20,
		21,22,23,24,23,24,25,26,
		27,28,27,28,29,30,31, 0,

	};
	UINT D1[32],D2[48];
	UINT i,t;
	for (i=0;i<32;i++)
	{
		D1[i]=(R >> (31-i))&0x1;
	}
	for (i=0;i<48;i++)
	{
		D2[i]=D1[E_Sequence[i]];
	}
	t=0;
	for (i=0;i<32;i++)
	{
		t=t|(D2[i]<<(31-i));
	}
	*pEh32=t;
	t=0;
	for (i=0;i<16;i++)
	{
		t=t|(D2[i+32]<<(15-i));
	}
	*pEl16=t;
}
void DES_SSplit( UINT h32, UINT l16, UINT * S)
{
	S[0]=(h32&0xfc000000)>>26;
	S[1]=(h32&0x03f00000)>>20;
	S[2]=(h32&0x000fc000)>>14;
	S[3]=(h32&0x00003f00)>>8;
	S[4]=(h32&0x000000fc)>>2;
	S[5]=((h32&0x3)<<4)+((l16&0xf000)>>12);
	S[6]=(l16&0x0fc0)>>6;
	S[7]=(l16&0x003f);
}
void DES_SCombine(UINT * S,UINT * pP)
{
	UINT i;
	*pP=0;
	for (i=0;i<8;i++)
	{
		*pP|=(S[i]<<(28-4*i));
	}
}
void DES_P(UINT * pP)
{
	static UINT P_Sequence[32]=
	{
		15, 6,19,20,28,11,27,16,
		 0,14,22,25, 4,17,30, 9,
		 1, 7,23,13,31,26, 2, 8,
		18,12,29, 5,21,10, 3,24,
	};
	UINT D1[32],D2[32];
	UINT i,t;
	for (i=0;i<32;i++)
	{
		D1[i]=((*pP)>>(31-i))&0x1;
	}
	for (i=0;i<32;i++)
	{
		D2[i]=D1[P_Sequence[i]];
	}
	t=0;
	for (i=0;i<32;i++)
	{
		t|=(D2[i]<<(31-i));
	}
	*pP = t;
}
void DES_S(UINT * S)
{
	UINT i,t;
	static UINT S_Sequence[8][64]=
	{
		{
			14, 0, 4,15,13, 7, 1, 4,
			 2,14,15, 2,11,13, 8, 1,
			 3,10,10, 6, 6,12,12,11,
			 5, 9, 9, 5, 0, 3, 7, 8,
			 4,15, 1,12,14, 8, 8, 2,
			13, 4, 6, 9, 2, 1,11, 7,
			15, 5,12,11, 9, 3, 7,14,
			 3,10,10, 0, 5, 6, 0,13
		},
		{
			15, 3, 1,13, 8, 4,14, 7,
			 6,15,11, 2, 3, 8, 4,14,
			 9,12, 7, 0, 2, 1,13,10,
			12, 6, 0, 9, 5,11,10, 5,
			 0,13,14, 8, 7,10,11, 1,
			10, 3, 4,15,13, 4, 1, 2,
			 5,11, 8, 6,12, 7, 6,12,
			 9, 0, 3, 5, 2,14,15, 9
		},
		{
			10,13, 0, 7, 9, 0,14, 9,
			 6, 3, 3, 4,15, 6, 5,10,
			 1, 2,13, 8,12, 5, 7,14,
			11,12, 4,11, 2,15, 8, 1,
			13, 1, 6,10, 4,13, 9, 0,
			 8, 6,15, 9, 3, 8, 0, 7,
			11, 4, 1,15, 2,14,12, 3,
			 5,11,10, 5,14, 2, 7,12
		},
		{
			 7,13,13, 8,14,11, 3, 5,
			 0, 6, 6,15, 9, 0,10, 3,
			 1, 4, 2, 7, 8, 2, 5,12,
			11, 1,12,10, 4,14,15, 9,
			10, 3, 6,15, 9, 0, 0, 6,
			12,10,11, 1, 7,13,13, 8,
			15, 9, 1, 4, 3, 5,14,11,
			 5,12, 2, 7, 8, 2, 4,14
		},
		{
			 2,14,12,11, 4, 2, 1,12,
			 7, 4,10, 7,11,13, 6, 1,
			 8, 5, 5, 0, 3,15,15,10,
			13, 3, 0, 9,14, 8, 9, 6,
			 4,11, 2, 8, 1,12,11, 7,
			10, 1,13,14, 7, 2, 8,13,
			15, 6, 9,15,12, 0, 5, 9,
			 6,10, 3, 4, 0, 5,14, 3
		},
		{
			12,10, 1,15,10, 4,15, 2,
			 9, 7, 2,12, 6, 9, 8, 5,
			 0, 6,13, 1, 3,13, 4,14,
			14, 0, 7,11, 5, 3,11, 8,
			 9, 4,14, 3,15, 2, 5,12,
			 2, 9, 8, 5,12,15, 3,10,
			 7,11, 0,14, 4, 1,10, 7,
			 1, 6,13, 0,11, 8, 6,13
		},
		{
			 4,13,11, 0, 2,11,14, 7,
			15, 4, 0, 9, 8, 1,13,10,
			 3,14,12, 3, 9, 5, 7,12,
			 5, 2,10,15, 6, 8, 1, 6,
			 1, 6, 4,11,11,13,13, 8,
			12, 1, 3, 4, 7,10,14, 7,
			10, 9,15, 5, 6, 0, 8,15,
			 0,14, 5, 2, 9, 3, 2,12
		},
		{
			13, 1, 2,15, 8,13, 4, 8,
			 6,10,15, 3,11, 7, 1, 4,
			10,12, 9, 5, 3, 6,14,11,
			 5, 0, 0,14,12, 9, 7, 2,
			 7, 2,11, 1, 4,14, 1, 7,
			 9, 4,12,10,14, 8, 2,13,
			 0,15, 6,12,10, 9,13, 0,
			15, 3, 3, 5, 5, 6, 8,11
		}
	};
	for (i=0;i<8;i++)
	{
		t=S[i];
		S[i]=S_Sequence[i][t];
	}
}
void DES_KS_LShift(UINT n,UINT * pReg) // pReg is 28 bit long,n is 1 or 2
{
	UINT Reg_Tmp1,Reg_Tmp2;
	UINT i;
	switch (n)
	{
	default:
	case 1:
		Reg_Tmp1=pReg[0];
		for (i=0;i<27;i++)
		{
			pReg[i]=pReg[i+1];
		}
		pReg[27]=Reg_Tmp1;
		break;
	case 2:
		Reg_Tmp1=pReg[0];
		Reg_Tmp2=pReg[1];
		for (i=0;i<26;i++)
		{
			pReg[i]=pReg[i+2];
		}
		pReg[26]=Reg_Tmp1;
		pReg[27]=Reg_Tmp2;
		break;
	}
	
}
void DES_KeyCombine(UINT * K,UINT * Kh32, UINT * Kl16)
{
	UINT i;
	UINT t;
	t=0;
	for (i=0;i<32;i++)
	{
		t=t|(K[i]<<(31-i));
	}
	* Kh32= t;
	t=0;
	for (i=0;i<16;i++)
	{
		t=t|(K[i+32]<<(15-i));
	}
	* Kl16= t;
} 





void DES_KS(KEY_STRUCT Key, int * Kh32, int * Kl16)
{
	static UINT PC1_CSequence[28]=
	{
		56,48,40,32,24,16, 8, 
		0, 57,49,41,33,25,17,
		9,  1,58,50,42,34,26,
		18,10, 2,59,51,43,35,
	};
	static UINT PC1_DSequence[28]=
	{
		62,54,46,38,30,22,14,
		6, 61,53,45,37,29,21,
		13, 5,60,52,44,36,28,
		20,12, 4,27,19,11, 3,
	};
	static UINT ShiftTable[16]=
	{
		1,1,2,2,2,2,2,2,
		1,2,2,2,2,2,2,1
	};
	static UINT PC2_Sequence[48]=
	{
		13,16,10,23, 0, 4, 2,27,
		14, 5,20, 9,22,18,11, 3,
		25, 7,15, 6,26,19,12, 1,
		40,51,30,36,46,54,29,39,
		50,44,32,47,43,48,38,55,
		33,52,45,41,49,35,28,31,
	};

	UINT C[28],D[28];
	UINT D1[64];
	UINT i,j,n1,n2;
	for (i=0;i<8;i++)
	{
		for (j=0;j<8;j++)
		{
			D1[i*8+j]=(Key.byte[i]>>(7-j))&0x1;
		}
	}
	for (i=0;i<28;i++)
	{
		C[i]=D1[PC1_CSequence[i]];
		D[i]=D1[PC1_DSequence[i]];
	}
	for (i=0;i<16;i++)
	{
		n1=ShiftTable[i];
		DES_KS_LShift(n1,C);
		DES_KS_LShift(n1,D);
		for (j=0;j<48;j++)
		{
			n2=PC2_Sequence[j];
			if (n2<=27)
			{
				D1[j]=C[n2];
			}
			else
			{
				n2-=28;
				D1[j]=D[n2];
			}
		}
		DES_KeyCombine(D1,(UINT *)&Kh32[i],(UINT *)&Kl16[i]);
	}
}
UINT DES_F(UINT R, UINT Kh32, UINT Kl16)
{
	UINT Eh32,El16;
	UINT S[8],P;
	DES_E(R,&Eh32,&El16);
	Eh32^=Kh32;
	El16^=Kl16;
	DES_SSplit(Eh32,El16,S);
	DES_S(S);
	DES_SCombine(S,&P);
	DES_P(&P);
	return(P);
}
void DES_Cipher(UINT * Kh32, UINT * Kl16, DES_DATA * pData)
{
	UINT L0,R0,L,R;
	UINT i;

	DES_IP(pData);
	DES_LRSplit(pData,&L0,&R0);
	for (i=0;i<16;i++)
	{
		L=R0;
		R=DES_F(R0,Kh32[i],Kl16[i]);
		R=L0^R;
		L0=L;
		R0=R;
	}
	L=R0;
	R=L0;
	DES_LRCombine(pData,L,R);
	DES_IP_R(pData);
}
void DES_Decipher(UINT * Kh32,UINT * Kl16,DES_DATA * pData)
{
	UINT L0,R0,L,R;
	UINT i;

	DES_IP(pData);
	DES_LRSplit(pData,&L,&R);
	L0=R;
	R0=L;
	for (i=0;i<16;i++)
	{
		R=L0;
		L=R0^DES_F(L0,Kh32[15-i],Kl16[15-i]);
		L0=L;
		R0=R;
	}
	DES_LRCombine(pData,L0,R0);
	DES_IP_R(pData);
}
/*****************************
    Tripple DES is a evolution of single DES with three 64 bits keys K1,K2,K3
	3DES.Cipher:=DES.Cipher(K3,DES.Decipher(K2,DES.Cipher(K1,input)));
	3DES.Decipher:=DES.Decipher(K1,DES.Cipher(K2,DES.Desipher(K3,input)));
*****************************/
void TDES_Cipher(UINT * K1h32,UINT * K1l16,
				 UINT * K2h32,UINT * K2l16,
				 UINT * K3h32,UINT * K3l16,
				 DES_DATA * pData)
{
	DES_Cipher(K1h32,K1l16,pData);
	DES_Decipher(K2h32,K2l16,pData);
	DES_Cipher(K3h32,K3l16,pData);
}
void TDES_Decipher(UINT * K1h32,UINT * K1l16,
				 UINT * K2h32,UINT * K2l16,
				 UINT * K3h32,UINT * K3l16,
				 DES_DATA * pData)
{
	DES_Decipher(K3h32,K3l16,pData);
	DES_Cipher(K2h32,K2l16,pData);
	DES_Decipher(K1h32,K1l16,pData);
}
/**********************
   ECB mode 
**********************/
void DES_ECB_Cipher(DES_DATA * pData,UINT nLength,KEY_STRUCT Key)
{
	UINT Kh32[16],Kl16[16];
	UINT i;
	DES_KS(Key,(int *)Kh32,(int *)Kl16);
	for (i=0;i<nLength;i++)
	{
		DES_Cipher(Kh32,Kl16,&pData[i]);
	}
}
void TDES_ECB_Cipher(DES_DATA * pData,UINT nLength,KEY_STRUCT Key1,KEY_STRUCT Key2,KEY_STRUCT Key3)
{
	UINT K1h32[16],K1l16[16],K2h32[16],K2l16[16],K3h32[16],K3l16[16];
	UINT i;
	DES_KS(Key1,(int *)K1h32,(int *)K1l16);
	DES_KS(Key2,(int *)K2h32,(int *)K2l16);
	DES_KS(Key3,(int *)K3h32,(int *)K3l16);
	for (i=0;i<nLength;i++)
	{
		TDES_Cipher(K1h32,K1l16,K2h32,K2l16,K3h32,K3l16,&pData[i]);
	}
}
void DES_ECB_Decipher(DES_DATA * pData,UINT nLength,KEY_STRUCT Key)
{
	UINT Kh32[16],Kl16[16];
	UINT i;
	DES_KS(Key,(int *)Kh32,(int *)Kl16);
	for (i=0;i<nLength;i++)
	{
		DES_Decipher(Kh32,Kl16,&pData[i]);
	}
}
void TDES_ECB_Decipher(DES_DATA * pData,UINT nLength,KEY_STRUCT Key1,KEY_STRUCT Key2,KEY_STRUCT Key3)
{
	UINT K1h32[16],K1l16[16],K2h32[16],K2l16[16],K3h32[16],K3l16[16];
	UINT i;
	DES_KS(Key1,(int *)K1h32,(int *)K1l16);
	DES_KS(Key2,(int *)K2h32,(int *)K2l16);
	DES_KS(Key3,(int *)K3h32,(int *)K3l16);
	for (i=0;i<nLength;i++)
	{
		TDES_Decipher(K1h32,K1l16,K2h32,K2l16,K3h32,K3l16,&pData[i]);
	}
}
/************************
  CBC mode
************************/
void DES_CBC_Cipher(DES_DATA * pData,UINT nLength,DES_DATA IV,KEY_STRUCT Key)
{
	UINT Kh32[16],Kl16[16];
	UINT i,j;
	DES_DATA Data_Tmp;
	DES_KS(Key,(int *)Kh32,(int *)Kl16);
	Data_Tmp=IV;
	for (i=0;i<nLength;i++)
	{
		for (j=0;j<8;j++)
		{
			pData[i].byte[j]^=Data_Tmp.byte[j];
		}
		DES_Cipher(Kh32,Kl16,&pData[i]);
		Data_Tmp=pData[i];
	}
}
void TDES_CBC_Cipher(DES_DATA * pData,UINT nLength,DES_DATA IV,KEY_STRUCT Key1,KEY_STRUCT Key2,KEY_STRUCT Key3)
{
	UINT K1h32[16],K1l16[16],K2h32[16],K2l16[16],K3h32[16],K3l16[16];
	UINT i,j;
	DES_DATA Data_Tmp;
	DES_KS(Key1,(int *)K1h32,(int *)K1l16);
	DES_KS(Key2,(int *)K2h32,(int *)K2l16);
	DES_KS(Key3,(int *)K3h32,(int *)K3l16);
	Data_Tmp=IV;
	for (i=0;i<nLength;i++)
	{
		for (j=0;j<8;j++)
		{
			pData[i].byte[j]^=Data_Tmp.byte[j];
		}
		TDES_Cipher(K1h32,K1l16,K2h32,K2l16,K3h32,K3l16,&pData[i]);
		Data_Tmp=pData[i];
	}
}
void DES_CBC_Decipher(DES_DATA * pData,UINT nLength,DES_DATA IV,KEY_STRUCT Key)
{
	UINT Kh32[16],Kl16[16];
	UINT i,j;
	DES_DATA Data_Tmp1,Data_Tmp2;
	DES_KS(Key,(int *)Kh32,(int *)Kl16);
	Data_Tmp1=IV;
	for (i=0;i<nLength;i++)
	{
		Data_Tmp2=pData[i];
		DES_Decipher(Kh32,Kl16,&pData[i]);
		for (j=0;j<8;j++)
		{
			pData[i].byte[j]^=Data_Tmp1.byte[j];
		}
		Data_Tmp1=Data_Tmp2;
	}
}
void TDES_CBC_Decipher(DES_DATA * pData,UINT nLength,DES_DATA IV,KEY_STRUCT Key1,KEY_STRUCT Key2,KEY_STRUCT Key3)
{
	UINT K1h32[16],K1l16[16],K2h32[16],K2l16[16],K3h32[16],K3l16[16];
	UINT i,j;
	DES_DATA Data_Tmp1,Data_Tmp2;
	DES_KS(Key1,(int *)K1h32,(int *)K1l16);
	DES_KS(Key2,(int *)K2h32,(int *)K2l16);
	DES_KS(Key3,(int *)K3h32,(int *)K3l16);
	Data_Tmp1=IV;

	for (i=0;i<nLength;i++)
	{
		Data_Tmp2=pData[i];
		TDES_Decipher(K1h32,K1l16,K2h32,K2l16,K3h32,K3l16,&pData[i]);
		for (j=0;j<8;j++)
		{
			pData[i].byte[j]^=Data_Tmp1.byte[j];
		}
		Data_Tmp1=Data_Tmp2;
	}
}

