/*
 * Quick & dirty crypto testing module.
 *
 * This will only exist until we have a better testing mechanism
 * (e.g. a char device).
 *
 * Copyright (c) 2002 James Morris <jmorris@intercode.com.au>
 * Copyright (c) 2002 Jean-Francois Dive <jef@linuxbe.org>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * 2004-08-09 Added cipher speed tests (Reyk Floeter <reyk@vantronix.net>)
 * 2003-09-14 Rewritten by Kartikey Mahendra Bhatt
 *
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/scatterlist.h>
#include <linux/string.h>
#include <linux/crypto.h>
#include <linux/highmem.h>
#include <linux/moduleparam.h>
#include <linux/jiffies.h>
#include <linux/timex.h>
#include <linux/interrupt.h>
#include "tcrypt.h"
#include <asm/arch/sl2312_ipsec.h>

#include <linux/pci.h>
#include <linux/delay.h>
#include <asm/arch/sl2312.h>
#include <asm/io.h>

/*
 * Need to kmalloc() memory for testing kmap().
 */
#define TVMEMSIZE	16384
#define XBUFSIZE	32768

/*
 * Indexes into the xbuf to simulate cross-page access.
 */
#define IDX1		37
#define IDX2		32400
#define IDX3		1
#define IDX4		8193
#define IDX5		22222
#define IDX6		17101
#define IDX7		27333
#define IDX8		3000

/*
* Used by test_cipher()
*/
#define ENCRYPT 1
#define DECRYPT 0
#define MODE_ECB 1
#define MODE_CBC 0

#ifdef CONFIG_SL2312_IPSEC
#define     IPSEC_MAX_PACKET_LEN    2048
static unsigned char *pkt;
#else
#define     IPSEC_MAX_PACKET_LEN    2048
static unsigned char *pkt;
#endif

static unsigned int IDX[8] = { IDX1, IDX2, IDX3, IDX4, IDX5, IDX6, IDX7, IDX8 };

/*
 * Used by test_cipher_speed()
 */
static unsigned int sec;
extern  unsigned int crp_done,crypto_go ;
static int mode;
static char *xbuf;
static char *tvmem;

static char *check[] = {
	"des", "md5", "des3_ede", "rot13", "sha1", "sha256", "blowfish",
	"twofish", "serpent", "sha384", "sha512", "md4", "aes", "cast6",
	"arc4", "michael_mic", "deflate", "crc32c", "tea", "xtea",
	"khazad", "wp512", "wp384", "wp256", "tnepres", "xeta", NULL
};
#if 0
void HW_memcpy(char *to,char *from,unsigned long n)
{
	unsigned int 	i;
	unsigned int	p_to = __pa(to);
	unsigned int    p_from = __pa(from);
	
    consistent_sync(to,n,DMA_BIDIRECTIONAL);
    consistent_sync(from,n,DMA_BIDIRECTIONAL);
    writel(p_from,IO_ADDRESS(SL2312_DRAM_CTRL_BASE)+0x24);  /* set source address */
    writel(p_to,IO_ADDRESS(SL2312_DRAM_CTRL_BASE)+0x28);    /* set destination address */
    writel(n,IO_ADDRESS(SL2312_DRAM_CTRL_BASE)+0x2c);     /* set byte count */
    writel(0x00000001,IO_ADDRESS(SL2312_DRAM_CTRL_BASE)+0x20);
	
	while (readl(IO_ADDRESS(SL2312_DRAM_CTRL_BASE)+0x20));
}    
#endif
void hexdump(unsigned char *buf, unsigned int len)
{
	while (len--)
		printk("%02x", *buf++);

	printk("\n");
}

void test_digest(void)
{
    unsigned char       alg[2][8] = {"md5","sha1"};
   // unsigned int        mode = 0;
    //unsigned char           auth_key[64];
    unsigned int        key_len=0 ;
    struct crypto_tfm *tfm;
	struct scatterlist  sg[8];
	char *packet,*auth_key; //*p,
    unsigned int        i,k=0,algorithm_len; //j
    char result[64], result_sw[64];
    
    
    
    packet = kmalloc(IPSEC_MAX_PACKET_LEN,GFP_ATOMIC);
    auth_key = kmalloc(64,GFP_ATOMIC);
    if ((packet == NULL)||(auth_key == NULL))
    {
       printk("memory allocation fail !\n");
    } 
    
    /* init packet */
    for (i=0;i<IPSEC_MAX_PACKET_LEN;i++)
    {
        packet[i] = i;
    }
    for (i=0;i<64;i++)
    {
        auth_key[i]=i;
    }    
    algorithm_len = 1536;

    //hash
    for(k=0;k<2;k++)
    {
    	tfm = crypto_alloc_tfm(&alg[k][0], 0);
		if (tfm == NULL) {
			printk("failed to load transform for %s\n", &alg[k][0]);
			return;
		}
		printk("\ntesting %s\n", &alg[k][0]);
		//p = kmalloc(IPSEC_MAX_PACKET_LEN,GFP_ATOMIC);
		//if (p == NULL) {
		//	printk("P failed to load transform.\n");
		//	return;
		//}
		for (i=1;i<=algorithm_len;i++)
    	{
    		//memset(p, 0, IPSEC_MAX_PACKET_LEN);
			memset(result, 0, sizeof (result));
			memset(result_sw, 0, sizeof (result_sw));
			
			//memcpy(p, packet, i);
			sg[0].page = virt_to_page(packet);
			sg[0].offset = offset_in_page(packet);
			sg[0].length = i;
			
			crypto_digest_init (tfm);
			if (tfm->crt_u.digest.dit_setkey) {
				crypto_digest_setkey (tfm, auth_key,
						      key_len);
			}
			crypto_digest_update (tfm, sg, 1);
			crypto_digest_final (tfm, result);
			crypto_go = 1;
			//printk("crypto : ");
			//hexdump (result, crypto_tfm_alg_digestsize (tfm));
			//printk("cryapi : ");
			//hexdump (hash_tv[i].digest, crypto_tfm_alg_digestsize (tfm));
			
			ipsec_sw_authentication(packet, i, auth_key, ipsec_get_auth_algorithm((unsigned char *)tfm->__crt_alg->cra_name,0), result_sw);
			//printk("test 0x%x : %s\n", i,
			//	memcmp(result, result_sw,
			//		crypto_tfm_alg_digestsize(tfm)) ? "fail" :
			//	"pass");
			if(memcmp(result, result_sw, crypto_tfm_alg_digestsize(tfm)))
			{
				printk("test 0x%x \n",i);
				printk("crypto : ");
				hexdump (result, crypto_tfm_alg_digestsize (tfm));
				printk("crypsw : ");
				hexdump (result_sw, crypto_tfm_alg_digestsize (tfm));
			}
			
		}
	}
	
	//hmac
	for(k=0;k<2;k++)
    {
    	tfm = crypto_alloc_tfm(&alg[k][0], 0);
		if (tfm == NULL) {
			printk("failed to load transform for %s\n", &alg[k][0]);
			return;
		}
		printk("\ntesting hmac_%s\n", &alg[k][0]);
		//p = kmalloc(IPSEC_MAX_PACKET_LEN,GFP_ATOMIC);
		//if (p == NULL) {
		//	printk("P failed to load transform.\n");
		//	return;
		//}
		for (i=1;i<=algorithm_len;i++)
    	{
    		//memset(p, 0, IPSEC_MAX_PACKET_LEN);
			memset(result, 0, sizeof (result));
			memset(result_sw, 0, sizeof (result_sw));
			
			//memcpy(p, packet, i);
			sg[0].page = virt_to_page(packet);
			sg[0].offset = offset_in_page(packet);
			sg[0].length = i;
			
			//for(j=0;j<64;j++)
			//{
				key_len = 64;
				crypto_hmac(tfm, auth_key, &key_len, sg, 1, result);
				crypto_go = 1;
				//printk("crypto : ");
				//hexdump (result, crypto_tfm_alg_digestsize (tfm));
				//printk("cryapi : ");
				//hexdump (hash_tv[i].digest, crypto_tfm_alg_digestsize (tfm));
				
				ipsec_sw_authentication(packet, i, auth_key, ipsec_get_auth_algorithm((unsigned char *)tfm->__crt_alg->cra_name,1), result_sw);
				//printk("test 0x%x : %s\n", i,
				//	memcmp(result, result_sw,
				//		crypto_tfm_alg_digestsize(tfm)) ? "fail" :
				//	"pass");
				if(memcmp(result, result_sw, crypto_tfm_alg_digestsize(tfm)))
				{
					printk("test hmac 0x%x \n",i);
					printk("crypto : ");
					hexdump (result, crypto_tfm_alg_digestsize (tfm));
					printk("crypsw : ");
					hexdump (result_sw, crypto_tfm_alg_digestsize (tfm));
				}
			//}
			
		}
	}
	
	//kfree(p);
	kfree(packet);
	kfree(auth_key);
	crypto_free_tfm (tfm);
}

void test_crypto_cipher(void)
{
    struct  crypto_tfm  *tfm;
    unsigned char       algo[20][9] = {"des", "des", "des3_ede" , "des3_ede", "aes","aes","aes","aes","aes","aes"
    							      ,"des","des","des3_ede","des3_ede","aes","aes","aes","aes","aes","aes"};
	unsigned int mode[20] ={MODE_ECB,MODE_CBC,MODE_ECB,MODE_CBC,MODE_ECB,MODE_CBC,MODE_ECB,MODE_CBC,MODE_ECB,MODE_CBC,
							MODE_ECB,MODE_CBC,MODE_ECB,MODE_CBC,MODE_ECB,MODE_CBC,MODE_ECB,MODE_CBC,MODE_ECB,MODE_CBC};
	//unsigned int mode[20] ={MODE_CBC,MODE_CBC,MODE_CBC,MODE_CBC,MODE_CBC,MODE_CBC,MODE_CBC,MODE_CBC,MODE_CBC,MODE_CBC,
	//						MODE_CBC,MODE_CBC,MODE_CBC,MODE_CBC,MODE_CBC,MODE_CBC,MODE_CBC,MODE_CBC,MODE_CBC,MODE_CBC};
	unsigned int enc[20] ={ENCRYPT,ENCRYPT,ENCRYPT,ENCRYPT,ENCRYPT,ENCRYPT,ENCRYPT,ENCRYPT,ENCRYPT,ENCRYPT,
						   DECRYPT,DECRYPT,DECRYPT,DECRYPT,DECRYPT,DECRYPT,DECRYPT,DECRYPT,DECRYPT,DECRYPT};		    							  		
	unsigned int key_len[20] = {8,8,24,24,16,16,24,24,32,32,8,8,24,24,16,16,24,24,32,32};
    unsigned int iv_len[20] = {0,8,0,8,0,16,0,16,0,16,0,8,0,8,0,16,0,16,0,16};
    
    unsigned char       key[32];
    //unsigned int        key_len = 16;
    unsigned char       iv[16];
    //unsigned char       iv_len = 16;
	struct scatterlist  sg[8];
	unsigned char       *q, *p;
    unsigned int        i,ret,j;
    char e[11], m[4];
   

    
    pkt = kmalloc(IPSEC_MAX_PACKET_LEN,GFP_ATOMIC);
    for (i=0;i<IPSEC_MAX_PACKET_LEN;i++)
    {
        pkt[i] = i % 256;
    }
    for (i=0;i<sizeof(key);i++)
    {
        key[i] = i;
    }
      
    for (i=0;i<sizeof(iv);i++)
    {
        iv[i] = i;
    }
    p = kmalloc(IPSEC_MAX_PACKET_LEN,GFP_DMA);//GFP_ATOMIC);
	if (p == NULL) {
		printk("P failed to load transform.\n");
		return;
	}
	for (i=0;i<10;i++)
	{
		if (enc[i] == ENCRYPT)
	        strncpy(e, "encryption", 11);
		else
    	    	strncpy(e, "decryption", 11);
		if (mode[i] == MODE_ECB)
    	    	strncpy(m, "ECB", 4);
		else
    	    	strncpy(m, "CBC", 4);
    	
		printk("\ntesting %s %s %s : key_len = %d, iv_len =%d\n", &algo[i][0], m, e,key_len[i],iv_len[i]);
	
		if (!mode[i]) 
			tfm = crypto_alloc_tfm (&algo[i][0], CRYPTO_TFM_MODE_CBC);
		else 
			tfm = crypto_alloc_tfm (&algo[i][0], 0);
			
		if (tfm == NULL) 
		{
					printk("failed to load transform for %s \n", &algo[i][0]);
		//	return 1;
		}
    	
    		ret = crypto_cipher_setkey(tfm, key, key_len[i]);
    	
		if (mode[i]) 
		{
			crypto_cipher_set_iv(tfm,iv,iv_len[i]);
		}
    	
		//printk("p = 0x%x\n",p);
    	for (j=1;j<IPSEC_MAX_PACKET_LEN;j++)
    	{
			
			memset (p, 0, IPSEC_MAX_PACKET_LEN);
			memcpy(p,pkt,j);
			sg[0].page = virt_to_page(p);
			sg[0].offset = offset_in_page(p);
			sg[0].length = j;
			sg[1].length = 0;
			//  	  printk("sg[0].page=%x sg[0].offset=%x sg[0].length=%x \n",sg[0].page,sg[0].offset,sg[0].length);
			//		printk("kmap(sg[0].page)=%x  \n",kmap(sg[0].page)+sg[0].offset);
    		
			//if (enc)
				ret = crypto_cipher_encrypt(tfm, sg, sg, sg[0].length);
				crypto_go = 1;
			//else
				ret = crypto_cipher_decrypt(tfm, sg, sg, sg[0].length);
    		crypto_go = 1;
					q = kmap(sg[0].page) + sg[0].offset;
					//hexdump(q, sg[0].length);
			if(memcmp(q, pkt, j))
			{
				printk("len = 0x%x \n",j);
				printk("crypto : ");
				hexdump (q, j);
			}
		}
		crypto_free_tfm(tfm);
	}
	kfree(p);
    //return (0); 
}

void test_hash(char *algo, struct hash_testvec *template,
		      unsigned int tcount)
{
	unsigned int i, j, k, temp;
	struct scatterlist sg[8];
	char result[64];
	struct crypto_tfm *tfm;
	struct hash_testvec *hash_tv;
	unsigned int tsize;
	char *p; 

	printk("\ntesting %s\n", algo);

	tsize = sizeof(struct hash_testvec);
	tsize *= tcount;

	if (tsize > TVMEMSIZE) {
		printk("template (%u) too big for tvmem (%u)\n", tsize, TVMEMSIZE);
		return;
	}

	memcpy(tvmem, template, tsize);
	hash_tv = (void *)tvmem;
	tfm = crypto_alloc_tfm(algo, 0);
	if (tfm == NULL) {
		printk("failed to load transform for %s\n", algo);
		return;
	}

	p = kmalloc(IPSEC_MAX_PACKET_LEN,GFP_ATOMIC);
	memset(&sg,0x00,8*sizeof(struct scatterlist));
	for (i = 0; i < tcount; i++) {
		printk("test %u:\n", i + 1);
		memset(result, 0, 64);
		memset(&sg,0x00,8*sizeof(struct scatterlist));
		//sg_set_buf(&sg[0], hash_tv[i].plaintext, hash_tv[i].psize);
		memcpy(p,hash_tv[i].plaintext,hash_tv[i].psize);
		//printk("p = %x\n",p);
		sg[0].page = virt_to_page (p);
		sg[0].offset = offset_in_page (p);
		sg[0].length = hash_tv[i].psize;


		crypto_digest_init(tfm);
		if (tfm->crt_u.digest.dit_setkey) {
			crypto_digest_setkey(tfm, hash_tv[i].key,
					     hash_tv[i].ksize);
		}
		crypto_digest_update(tfm, sg, 1);
		crypto_digest_final(tfm, result);
crypto_go = 1;
//		hexdump(result, crypto_tfm_alg_digestsize(tfm));
		printk("%s\n",
		       memcmp(result, hash_tv[i].digest,
			      crypto_tfm_alg_digestsize(tfm)) ?
		       "fail" : "pass");
	}

	printk("testing %s across pages\n", algo);

	/* setup the dummy buffer first */
	memset(xbuf, 0, XBUFSIZE);

	j = 0;
	for (i = 0; i < tcount; i++) {
		if (hash_tv[i].np) {
			j++;
			printk("test %u:\n", j);
			memset(result, 0, 64);
			memset(&sg,0x00,8*sizeof(struct scatterlist));
			memset(&sg,0x00,8*sizeof(struct scatterlist));
			temp = 0;
			for (k = 0; k < hash_tv[i].np; k++) {
				memcpy(&xbuf[IDX[k]],
				       hash_tv[i].plaintext + temp,
				       hash_tv[i].tap[k]);
				       
				memcpy(p+temp,&xbuf[IDX[k]],hash_tv[i].tap[k]);     
				temp += hash_tv[i].tap[k];
				sg[k].page = virt_to_page (p);
				sg[k].offset = offset_in_page (p);
				sg[k].length = hash_tv[i].tap[k];
				//sg_set_buf(&sg[k], &xbuf[IDX[k]],
				//	    hash_tv[i].tap[k]);
			}

			crypto_digest_digest(tfm, sg, hash_tv[i].np, result);
			crypto_go = 1;
//			hexdump(result, crypto_tfm_alg_digestsize(tfm));
			printk("%s\n",
			       memcmp(result, hash_tv[i].digest,
				      crypto_tfm_alg_digestsize(tfm)) ?
			       "fail" : "pass");
		}
	}
	kfree(p);
	crypto_free_tfm(tfm);
}


#ifdef CONFIG_CRYPTO_HMAC

void test_hmac(char *algo, struct hmac_testvec *template,
		      unsigned int tcount)
{
	char *p;
	unsigned int i, j, k, temp;
	struct scatterlist sg[8];
	char result[64];
	struct crypto_tfm *tfm;
	struct hmac_testvec *hmac_tv;
	unsigned int tsize, klen;

	tfm = crypto_alloc_tfm(algo, 0);
	if (tfm == NULL) {
		printk("failed to load transform for %s\n", algo);
		return;
	}

	printk("\ntesting hmac_%s\n", algo);
	p = kmalloc(IPSEC_MAX_PACKET_LEN,GFP_ATOMIC);
	if (p == NULL) {
		printk("P failed to load transform.\n");
		return;
	}
	printk("\ntesting hmac_%s\n", algo);
	

	tsize = sizeof(struct hmac_testvec);
	tsize *= tcount;
	if (tsize > TVMEMSIZE) {
		printk("template (%u) too big for tvmem (%u)\n", tsize,
		       TVMEMSIZE);
		goto out;
	}

	memcpy(tvmem, template, tsize);
	hmac_tv = (void *)tvmem;

	for (i = 0; i < tcount; i++) {
		printk("test %u:\n", i + 1);
		memset(result, 0, sizeof (result));
		memset(&sg,0x00,8*sizeof(struct scatterlist));
		//klen = hmac_tv[i].ksize;
		//sg_set_buf(&sg[0], hmac_tv[i].plaintext, hmac_tv[i].psize);
		//p = hmac_tv[i].plaintext;
		memcpy(p,hmac_tv[i].plaintext,hmac_tv[i].psize);
		//printk("p = %x\n",p);
		klen = hmac_tv[i].ksize;
		sg[0].page = virt_to_page(p);
		sg[0].offset = offset_in_page(p);
		sg[0].length = hmac_tv[i].psize;
		
		crypto_hmac(tfm, hmac_tv[i].key, &klen, sg, 1, result);
		crypto_go = 1;
		//hexdump(result, crypto_tfm_alg_digestsize(tfm));
		if(memcmp(result, hmac_tv[i].digest,crypto_tfm_alg_digestsize(tfm)))
		{
			printk("crypto : ");
			hexdump(result, crypto_tfm_alg_digestsize(tfm));
			printk("cryapi : ");
			hexdump (hmac_tv[i].digest, crypto_tfm_alg_digestsize (tfm));
		}
		printk("%s\n",
		       memcmp(result, hmac_tv[i].digest,
			      crypto_tfm_alg_digestsize(tfm)) ? "fail" :
		       "pass");
	}

	printk("\ntesting hmac_%s across pages\n", algo);

	memset(xbuf, 0, XBUFSIZE);
 
	j = 0;
	for (i = 0; i < tcount; i++) {
		if (hmac_tv[i].np) {
			j++;
			printk("test %u:\n",j);
			memset(result, 0, 64);
			memset(&sg,0x00,8*sizeof(struct scatterlist));
			temp = 0;
			klen = hmac_tv[i].ksize;
			for (k = 0; k < hmac_tv[i].np; k++) {
				memcpy(&xbuf[IDX[k]],
				       hmac_tv[i].plaintext + temp,
				       hmac_tv[i].tap[k]);
				//temp += hmac_tv[i].tap[k];
				//sg_set_buf(&sg[k], &xbuf[IDX[k]],
				//	    hmac_tv[i].tap[k]);
				memcpy(p+temp,&xbuf[IDX[k]],hmac_tv[i].tap[k]);
				
				sg[k].page = virt_to_page (p+temp);
				sg[k].offset = offset_in_page (p+temp);
				sg[k].length = hmac_tv[i].tap[k];		
				temp += hmac_tv[i].tap[k];		    
			}

			crypto_hmac(tfm, hmac_tv[i].key, &klen, sg,
				    hmac_tv[i].np, result);
				    crypto_go = 1;
				    printk("crypto : ");
				hexdump(result, crypto_tfm_alg_digestsize(tfm));
				printk("cryapi : ");
				hexdump (hmac_tv[i].digest, crypto_tfm_alg_digestsize (tfm));
			//hexdump(result, crypto_tfm_alg_digestsize(tfm));
			if(memcmp(result, hmac_tv[i].digest,crypto_tfm_alg_digestsize(tfm)))
			{					
				printk("crypto : ");
				hexdump(result, crypto_tfm_alg_digestsize(tfm));
				printk("cryapi : ");
				hexdump (hmac_tv[i].digest, crypto_tfm_alg_digestsize (tfm));
			}
			
			printk("%s\n",
			       memcmp(result, hmac_tv[i].digest,
				      crypto_tfm_alg_digestsize(tfm)) ?
			       "fail" : "pass");
		}
	}
out:
kfree(p);
	crypto_free_tfm(tfm);
}

#endif	/* CONFIG_CRYPTO_HMAC */

void test_cipher(char *algo, int mode, int enc,
			struct cipher_testvec *template, unsigned int tcount)
{
	unsigned int ret, i, j, k, temp;
	unsigned int tsize;
	char *p, *q;
	struct crypto_tfm *tfm;
	char *key;
	struct cipher_testvec *cipher_tv;
	struct scatterlist sg[8];
	//const char *e, *m;
	char e[11], m[4];

	if (enc == ENCRYPT)
	        strncpy(e, "encryption", 11);
	else
        	strncpy(e, "decryption", 11);
	if (mode == MODE_ECB)
        	strncpy(m, "ECB", 4);
	else
        	strncpy(m, "CBC", 4);

	printk("\ntesting %s %s %s\n", algo, m, e);

	tsize = sizeof (struct cipher_testvec);
	tsize *= tcount;

	if (tsize > TVMEMSIZE) {
		printk("template (%u) too big for tvmem (%u)\n", tsize,
		       TVMEMSIZE);
		return;
	}

	memcpy(tvmem, template, tsize);
	cipher_tv = (void *)tvmem;

	if (mode)
		tfm = crypto_alloc_tfm(algo, 0);
	else
		tfm = crypto_alloc_tfm(algo, CRYPTO_TFM_MODE_CBC);

	if (tfm == NULL) {
		printk("failed to load transform for %s %s\n", algo, m);
		return;
	}

	p = kmalloc(IPSEC_MAX_PACKET_LEN,GFP_DMA);//GFP_ATOMIC);
	if (p == NULL) {
		printk("P failed to load transform.\n");
		return;
	}
	
	j = 0;
	for (i = 0; i < tcount; i++) {
		if (!(cipher_tv[i].np)) {
			memset(p,0,256);
			j++;
			printk("test %u (%d bit key):\n",
			j, cipher_tv[i].klen * 8);

			tfm->crt_flags = 0;
			if (cipher_tv[i].wk)
				tfm->crt_flags |= CRYPTO_TFM_REQ_WEAK_KEY;
			key = cipher_tv[i].key;

			ret = crypto_cipher_setkey(tfm, key, cipher_tv[i].klen);
			if (ret) {
				printk("setkey() failed flags=%x\n", tfm->crt_flags);

				if (!cipher_tv[i].fail)
					goto out;
			}

			//sg_set_buf(&sg[0], cipher_tv[i].input,
			//	   cipher_tv[i].ilen);
			memcpy(p,cipher_tv[i].input,cipher_tv[i].ilen);
			sg[0].page = virt_to_page(p);
			sg[0].offset = offset_in_page(p);
			sg[0].length = cipher_tv[i].ilen;

			if (!mode) {
				crypto_cipher_set_iv(tfm, cipher_tv[i].iv,
					crypto_tfm_alg_ivsize(tfm));
			}

			if (enc)
			{
				
				ret = crypto_cipher_encrypt(tfm, sg, sg, cipher_tv[i].ilen);
				crypto_go = 1;
			}
			else
			{	
				ret = crypto_cipher_decrypt(tfm, sg, sg, cipher_tv[i].ilen);
				crypto_go = 1;	
			}

			if (ret) {
				printk("%s () failed flags=%x\n", e, tfm->crt_flags);
				goto out;
			}

			q = kmap(sg[0].page) + sg[0].offset;
			

			printk("%s\n",
			       memcmp(q, cipher_tv[i].result,
				      cipher_tv[i].rlen) ? "fail" : "pass");
		}
	}

	printk("\ntesting %s %s %s across pages (chunking)\n", algo, m, e);
	memset(xbuf, 0, XBUFSIZE);

	j = 0;
	for (i = 0; i < tcount; i++) {
		if (cipher_tv[i].np) {
			memset(p,0,256);
			j++;
			printk("test %u (%d bit key):\n",
			j, cipher_tv[i].klen * 8);

			tfm->crt_flags = 0;
			if (cipher_tv[i].wk)
				tfm->crt_flags |= CRYPTO_TFM_REQ_WEAK_KEY;
			key = cipher_tv[i].key;

			ret = crypto_cipher_setkey(tfm, key, cipher_tv[i].klen);
			if (ret) {
				printk("setkey() failed flags=%x\n", tfm->crt_flags);

				if (!cipher_tv[i].fail)
					goto out;
			}

			temp = 0;
			for (k = 0; k < cipher_tv[i].np; k++) {
				memcpy(&xbuf[IDX[k]],
				       cipher_tv[i].input + temp,
				       cipher_tv[i].tap[k]);
				
				memcpy((p+temp),&xbuf[IDX[k]],cipher_tv[i].tap[k]);							
				consistent_sync(&p, cipher_tv[i].rlen, DMA_BIDIRECTIONAL);
				printk("np %x : length : %x\n",k,cipher_tv[i].tap[k]);
				hexdump((p+temp), cipher_tv[i].tap[k]);
				//temp += cipher_tv[i].tap[k];
				//sg_set_buf(&sg[k], &xbuf[IDX[k]],
				//	   cipher_tv[i].tap[k]);
				sg[k].page = virt_to_page (p+temp);
				sg[k].offset = offset_in_page (p+temp);
				sg[k].length = cipher_tv[i].tap[k];	
				temp += cipher_tv[i].tap[k];		
			}

			if (!mode) {
				crypto_cipher_set_iv(tfm, cipher_tv[i].iv,
						crypto_tfm_alg_ivsize(tfm));
			}

			if (enc)
			{
				
				ret = crypto_cipher_encrypt(tfm, sg, sg, cipher_tv[i].ilen);
				crypto_go = 1;
			}
			else
			{
				
				ret = crypto_cipher_decrypt(tfm, sg, sg, cipher_tv[i].ilen);
				crypto_go = 1;
			}

			if (ret) {
				printk("%s () failed flags=%x\n", e, tfm->crt_flags);
				goto out;
			}

			temp = 0;
			for (k = 0; k < cipher_tv[i].np; k++) {
				printk("page %u\n", k);
				q = kmap(sg[k].page) + sg[k].offset;
				consistent_sync(&q, cipher_tv[i].rlen, DMA_BIDIRECTIONAL);
				printk("q : %x\n",q);
				hexdump(q, cipher_tv[i].rlen);
				hexdump(cipher_tv[i].result, cipher_tv[i].rlen);
				printk("%s\n",
					memcmp(q , cipher_tv[i].result + temp,
						cipher_tv[i].tap[k]) ? "fail" :
					"pass");
				//hexdump(cipher_tv[i].result + temp, cipher_tv[i].tap[k]);
				temp += cipher_tv[i].tap[k];
			}
		}
	}

out:
	kfree(p);
	crypto_free_tfm(tfm);
}

int test_cipher_jiffies(struct crypto_tfm *tfm, int enc, char *p,
			       int blen, int sec)
{
	struct scatterlist sg[1];
	unsigned long start, end;
	int bcount;
	int ret;

	sg_set_buf(sg, p, blen);

	for (start = jiffies, end = start + sec * HZ, bcount = 0;
	     time_before(jiffies, end); bcount++) {
		if (enc)
			ret = crypto_cipher_encrypt(tfm, sg, sg, blen);
		else
			ret = crypto_cipher_decrypt(tfm, sg, sg, blen);

		if (ret)
			return ret;
	}

	printk("%d operations in %d seconds (%ld bytes)\n",
	       bcount, sec, (long)bcount * blen);
	return 0;
}

int test_cipher_cycles(struct crypto_tfm *tfm, int enc, char *p,
			      int blen)
{
	struct scatterlist sg[1];
	unsigned long cycles = 0;
	int ret = 0;
	int i;

	sg_set_buf(sg, p, blen);

	local_bh_disable();
	local_irq_disable();

	/* Warm-up run. */
	for (i = 0; i < 4; i++) {
		if (enc)
			ret = crypto_cipher_encrypt(tfm, sg, sg, blen);
		else
			ret = crypto_cipher_decrypt(tfm, sg, sg, blen);

		if (ret)
			goto out;
	}

	/* The real thing. */
	for (i = 0; i < 8; i++) {
		cycles_t start, end;

		start = get_cycles();
		if (enc)
			ret = crypto_cipher_encrypt(tfm, sg, sg, blen);
		else
			ret = crypto_cipher_decrypt(tfm, sg, sg, blen);
		end = get_cycles();

		if (ret)
			goto out;

		cycles += end - start;
	}

out:
	local_irq_enable();
	local_bh_enable();

	if (ret == 0)
		printk("1 operation in %lu cycles (%d bytes)\n",
		       (cycles + 4) / 8, blen);

	return ret;
}

void test_cipher_speed(char *algo, int mode, int enc, unsigned int sec,
			      struct cipher_testvec *template,
			      unsigned int tcount, struct cipher_speed *speed)
{
	unsigned int ret, i, j, iv_len;
	unsigned char *key, *p, iv[128];
	struct crypto_tfm *tfm;
	const char *e, *m;

	if (enc == ENCRYPT)
	        e = "encryption";
	else
		e = "decryption";
	if (mode == MODE_ECB)
		m = "ECB";
	else
		m = "CBC";

	printk("\ntesting speed of %s %s %s\n", algo, m, e);

	if (mode)
		tfm = crypto_alloc_tfm(algo, 0);
	else
		tfm = crypto_alloc_tfm(algo, CRYPTO_TFM_MODE_CBC);

	if (tfm == NULL) {
		printk("failed to load transform for %s %s\n", algo, m);
		return;
	}

	for (i = 0; speed[i].klen != 0; i++) {
		if ((speed[i].blen + speed[i].klen) > TVMEMSIZE) {
			printk("template (%u) too big for tvmem (%u)\n",
			       speed[i].blen + speed[i].klen, TVMEMSIZE);
			goto out;
		}

		printk("test %u (%d bit key, %d byte blocks): ", i,
		       speed[i].klen * 8, speed[i].blen);

		memset(tvmem, 0xff, speed[i].klen + speed[i].blen);

		/* set key, plain text and IV */
		key = (unsigned char *)tvmem;
		for (j = 0; j < tcount; j++) {
			if (template[j].klen == speed[i].klen) {
				key = template[j].key;
				break;
			}
		}
		p = (unsigned char *)tvmem + speed[i].klen;

		ret = crypto_cipher_setkey(tfm, key, speed[i].klen);
		if (ret) {
			printk("setkey() failed flags=%x\n", tfm->crt_flags);
			goto out;
		}

		if (!mode) {
			iv_len = crypto_tfm_alg_ivsize(tfm);
			memset(&iv, 0xff, iv_len);
			crypto_cipher_set_iv(tfm, iv, iv_len);
		}

		if (sec)
			ret = test_cipher_jiffies(tfm, enc, p, speed[i].blen,
						  sec);
		else
			ret = test_cipher_cycles(tfm, enc, p, speed[i].blen);

		if (ret) {
			printk("%s() failed flags=%x\n", e, tfm->crt_flags);
			break;
		}
	}

out:
	crypto_free_tfm(tfm);
}

void test_deflate(void)
{
	unsigned int i;
	char result[COMP_BUF_SIZE];
	struct crypto_tfm *tfm;
	struct comp_testvec *tv;
	unsigned int tsize;

	printk("\ntesting deflate compression\n");

	tsize = sizeof (deflate_comp_tv_template);
	if (tsize > TVMEMSIZE) {
		printk("template (%u) too big for tvmem (%u)\n", tsize,
		       TVMEMSIZE);
		return;
	}

	memcpy(tvmem, deflate_comp_tv_template, tsize);
	tv = (void *)tvmem;

	tfm = crypto_alloc_tfm("deflate", 0);
	if (tfm == NULL) {
		printk("failed to load transform for deflate\n");
		return;
	}

	for (i = 0; i < DEFLATE_COMP_TEST_VECTORS; i++) {
		int ilen, ret, dlen = COMP_BUF_SIZE;

		printk("test %u:\n", i + 1);
		memset(result, 0, sizeof (result));

		ilen = tv[i].inlen;
		ret = crypto_comp_compress(tfm, tv[i].input,
		                           ilen, result, &dlen);
		if (ret) {
			printk("fail: ret=%d\n", ret);
			continue;
		}
		hexdump(result, dlen);
		printk("%s (ratio %d:%d)\n",
		       memcmp(result, tv[i].output, dlen) ? "fail" : "pass",
		       ilen, dlen);
	}

	printk("\ntesting deflate decompression\n");

	tsize = sizeof (deflate_decomp_tv_template);
	if (tsize > TVMEMSIZE) {
		printk("template (%u) too big for tvmem (%u)\n", tsize,
		       TVMEMSIZE);
		goto out;
	}

	memcpy(tvmem, deflate_decomp_tv_template, tsize);
	tv = (void *)tvmem;

	for (i = 0; i < DEFLATE_DECOMP_TEST_VECTORS; i++) {
		int ilen, ret, dlen = COMP_BUF_SIZE;

		printk("test %u:\n", i + 1);
		memset(result, 0, sizeof (result));

		ilen = tv[i].inlen;
		ret = crypto_comp_decompress(tfm, tv[i].input,
		                             ilen, result, &dlen);
		if (ret) {
			printk("fail: ret=%d\n", ret);
			continue;
		}
		hexdump(result, dlen);
		printk("%s (ratio %d:%d)\n",
		       memcmp(result, tv[i].output, dlen) ? "fail" : "pass",
		       ilen, dlen);
	}
out:
	crypto_free_tfm(tfm);
}

void test_crc32c(void)
{
#define NUMVEC 6
#define VECSIZE 40

	int i, j, pass;
	u32 crc;
	u8 b, test_vec[NUMVEC][VECSIZE];
	static u32 vec_results[NUMVEC] = {
		0x0e2c157f, 0xe980ebf6, 0xde74bded,
		0xd579c862, 0xba979ad0, 0x2b29d913
	};
	static u32 tot_vec_results = 0x24c5d375;

	struct scatterlist sg[NUMVEC];
	struct crypto_tfm *tfm;
	char *fmtdata = "testing crc32c initialized to %08x: %s\n";
#define SEEDTESTVAL 0xedcba987
	u32 seed;

	printk("\ntesting crc32c\n");

	tfm = crypto_alloc_tfm("crc32c", 0);
	if (tfm == NULL) {
		printk("failed to load transform for crc32c\n");
		return;
	}

	crypto_digest_init(tfm);
	crypto_digest_final(tfm, (u8*)&crc);
	printk(fmtdata, crc, (crc == 0) ? "pass" : "ERROR");

	/*
	 * stuff test_vec with known values, simple incrementing
	 * byte values.
	 */
	b = 0;
	for (i = 0; i < NUMVEC; i++) {
		for (j = 0; j < VECSIZE; j++)
			test_vec[i][j] = ++b;
		//sg_set_buf(&sg[i], test_vec[i], VECSIZE);
		sg[i].page = virt_to_page(test_vec[i]);
		sg[i].offset = offset_in_page(test_vec[i]);
		sg[i].length = VECSIZE;
	}

	seed = SEEDTESTVAL;
	(void)crypto_digest_setkey(tfm, (const u8*)&seed, sizeof(u32));
	crypto_digest_final(tfm, (u8*)&crc);
	printk("testing crc32c setkey returns %08x : %s\n", crc, (crc == (SEEDTESTVAL ^ ~(u32)0)) ?
	       "pass" : "ERROR");

	printk("testing crc32c using update/final:\n");

	pass = 1;		    /* assume all is well */

	for (i = 0; i < NUMVEC; i++) {
		seed = ~(u32)0;
		(void)crypto_digest_setkey(tfm, (const u8*)&seed, sizeof(u32));
		crypto_digest_update(tfm, &sg[i], 1);
		crypto_digest_final(tfm, (u8*)&crc);
		if (crc == vec_results[i]) {
			printk(" %08x:OK", crc);
		} else {
			printk(" %08x:BAD, wanted %08x\n", crc, vec_results[i]);
			pass = 0;
		}
	}

	printk("\ntesting crc32c using incremental accumulator:\n");
	crc = 0;
	for (i = 0; i < NUMVEC; i++) {
		seed = (crc ^ ~(u32)0);
		(void)crypto_digest_setkey(tfm, (const u8*)&seed, sizeof(u32));
		crypto_digest_update(tfm, &sg[i], 1);
		crypto_digest_final(tfm, (u8*)&crc);
	}
	if (crc == tot_vec_results) {
		printk(" %08x:OK", crc);
	} else {
		printk(" %08x:BAD, wanted %08x\n", crc, tot_vec_results);
		pass = 0;
	}

	printk("\ntesting crc32c using digest:\n");
	seed = ~(u32)0;
	(void)crypto_digest_setkey(tfm, (const u8*)&seed, sizeof(u32));
	crypto_digest_digest(tfm, sg, NUMVEC, (u8*)&crc);
	if (crc == tot_vec_results) {
		printk(" %08x:OK", crc);
	} else {
		printk(" %08x:BAD, wanted %08x\n", crc, tot_vec_results);
		pass = 0;
	}

	printk("\n%s\n", pass ? "pass" : "ERROR");

	crypto_free_tfm(tfm);
	printk("crc32c test complete\n");
}

void test_available(void)
{
	char **name = check;

	while (*name) {
		printk("alg %s ", *name);
		printk((crypto_alg_available(*name, 0)) ?
			"found\n" : "not found\n");
		name++;
	}
}

void do_test(void)
{
	mode = 997;
	switch (mode) {

	case 0:
		test_hash("md5", md5_tv_template, MD5_TEST_VECTORS);

		test_hash("sha1", sha1_tv_template, SHA1_TEST_VECTORS);

		//DES
		test_cipher ("des", MODE_ECB, ENCRYPT, des_enc_tv_template, DES_ENC_TEST_VECTORS);
		test_cipher ("des", MODE_ECB, DECRYPT, des_dec_tv_template, DES_DEC_TEST_VECTORS);
		test_cipher ("des", MODE_CBC, ENCRYPT, des_cbc_enc_tv_template, DES_CBC_ENC_TEST_VECTORS);
		test_cipher ("des", MODE_CBC, DECRYPT, des_cbc_dec_tv_template, DES_CBC_DEC_TEST_VECTORS);

		//DES3_EDE
		test_cipher ("des3_ede", MODE_ECB, ENCRYPT, des3_ede_enc_tv_template, DES3_EDE_ENC_TEST_VECTORS);
		test_cipher ("des3_ede", MODE_ECB, DECRYPT, des3_ede_dec_tv_template, DES3_EDE_DEC_TEST_VECTORS);

		test_hash("md4", md4_tv_template, MD4_TEST_VECTORS);

		test_hash("sha256", sha256_tv_template, SHA256_TEST_VECTORS);

		//BLOWFISH
		test_cipher ("blowfish", MODE_ECB, ENCRYPT, bf_enc_tv_template, BF_ENC_TEST_VECTORS);
		test_cipher ("blowfish", MODE_ECB, DECRYPT, bf_dec_tv_template, BF_DEC_TEST_VECTORS);
		test_cipher ("blowfish", MODE_CBC, ENCRYPT, bf_cbc_enc_tv_template, BF_CBC_ENC_TEST_VECTORS);
		test_cipher ("blowfish", MODE_CBC, DECRYPT, bf_cbc_dec_tv_template, BF_CBC_DEC_TEST_VECTORS);

		//TWOFISH
		test_cipher ("twofish", MODE_ECB, ENCRYPT, tf_enc_tv_template, TF_ENC_TEST_VECTORS);
		test_cipher ("twofish", MODE_ECB, DECRYPT, tf_dec_tv_template, TF_DEC_TEST_VECTORS);
		test_cipher ("twofish", MODE_CBC, ENCRYPT, tf_cbc_enc_tv_template, TF_CBC_ENC_TEST_VECTORS);
		test_cipher ("twofish", MODE_CBC, DECRYPT, tf_cbc_dec_tv_template, TF_CBC_DEC_TEST_VECTORS);

		//SERPENT
		test_cipher ("serpent", MODE_ECB, ENCRYPT, serpent_enc_tv_template, SERPENT_ENC_TEST_VECTORS);
		test_cipher ("serpent", MODE_ECB, DECRYPT, serpent_dec_tv_template, SERPENT_DEC_TEST_VECTORS);

		//TNEPRES
		test_cipher ("tnepres", MODE_ECB, ENCRYPT, tnepres_enc_tv_template, TNEPRES_ENC_TEST_VECTORS);
		test_cipher ("tnepres", MODE_ECB, DECRYPT, tnepres_dec_tv_template, TNEPRES_DEC_TEST_VECTORS);

		//AES
		test_cipher ("aes", MODE_ECB, ENCRYPT, aes_enc_tv_template, AES_ENC_TEST_VECTORS);
		test_cipher ("aes", MODE_ECB, DECRYPT, aes_dec_tv_template, AES_DEC_TEST_VECTORS);

		//CAST5
		test_cipher ("cast5", MODE_ECB, ENCRYPT, cast5_enc_tv_template, CAST5_ENC_TEST_VECTORS);
		test_cipher ("cast5", MODE_ECB, DECRYPT, cast5_dec_tv_template, CAST5_DEC_TEST_VECTORS);

		//CAST6
		test_cipher ("cast6", MODE_ECB, ENCRYPT, cast6_enc_tv_template, CAST6_ENC_TEST_VECTORS);
		test_cipher ("cast6", MODE_ECB, DECRYPT, cast6_dec_tv_template, CAST6_DEC_TEST_VECTORS);

		//ARC4
		test_cipher ("arc4", MODE_ECB, ENCRYPT, arc4_enc_tv_template, ARC4_ENC_TEST_VECTORS);
		test_cipher ("arc4", MODE_ECB, DECRYPT, arc4_dec_tv_template, ARC4_DEC_TEST_VECTORS);

		//TEA
		test_cipher ("tea", MODE_ECB, ENCRYPT, tea_enc_tv_template, TEA_ENC_TEST_VECTORS);
		test_cipher ("tea", MODE_ECB, DECRYPT, tea_dec_tv_template, TEA_DEC_TEST_VECTORS);


		//XTEA
		test_cipher ("xtea", MODE_ECB, ENCRYPT, xtea_enc_tv_template, XTEA_ENC_TEST_VECTORS);
		test_cipher ("xtea", MODE_ECB, DECRYPT, xtea_dec_tv_template, XTEA_DEC_TEST_VECTORS);

		//KHAZAD
		test_cipher ("khazad", MODE_ECB, ENCRYPT, khazad_enc_tv_template, KHAZAD_ENC_TEST_VECTORS);
		test_cipher ("khazad", MODE_ECB, DECRYPT, khazad_dec_tv_template, KHAZAD_DEC_TEST_VECTORS);

		//ANUBIS
		test_cipher ("anubis", MODE_ECB, ENCRYPT, anubis_enc_tv_template, ANUBIS_ENC_TEST_VECTORS);
		test_cipher ("anubis", MODE_ECB, DECRYPT, anubis_dec_tv_template, ANUBIS_DEC_TEST_VECTORS);
		test_cipher ("anubis", MODE_CBC, ENCRYPT, anubis_cbc_enc_tv_template, ANUBIS_CBC_ENC_TEST_VECTORS);
		test_cipher ("anubis", MODE_CBC, DECRYPT, anubis_cbc_dec_tv_template, ANUBIS_CBC_ENC_TEST_VECTORS);

		//XETA
		test_cipher ("xeta", MODE_ECB, ENCRYPT, xeta_enc_tv_template, XETA_ENC_TEST_VECTORS);
		test_cipher ("xeta", MODE_ECB, DECRYPT, xeta_dec_tv_template, XETA_DEC_TEST_VECTORS);

		test_hash("sha384", sha384_tv_template, SHA384_TEST_VECTORS);
		test_hash("sha512", sha512_tv_template, SHA512_TEST_VECTORS);
		test_hash("wp512", wp512_tv_template, WP512_TEST_VECTORS);
		test_hash("wp384", wp384_tv_template, WP384_TEST_VECTORS);
		test_hash("wp256", wp256_tv_template, WP256_TEST_VECTORS);
		test_hash("tgr192", tgr192_tv_template, TGR192_TEST_VECTORS);
		test_hash("tgr160", tgr160_tv_template, TGR160_TEST_VECTORS);
		test_hash("tgr128", tgr128_tv_template, TGR128_TEST_VECTORS);
		test_deflate();
		test_crc32c();
#ifdef CONFIG_CRYPTO_HMAC
		test_hmac("md5", hmac_md5_tv_template, HMAC_MD5_TEST_VECTORS);
		test_hmac("sha1", hmac_sha1_tv_template, HMAC_SHA1_TEST_VECTORS);
		test_hmac("sha256", hmac_sha256_tv_template, HMAC_SHA256_TEST_VECTORS);
#endif

		test_hash("michael_mic", michael_mic_tv_template, MICHAEL_MIC_TEST_VECTORS);
		break;

	case 1:
		test_crypto_cipher();
		//test_hash("md5", md5_tv_template, MD5_TEST_VECTORS);
		break;

	case 2:
		test_hash("sha1", sha1_tv_template, SHA1_TEST_VECTORS);
		break;

	case 3:
		test_cipher ("des", MODE_ECB, ENCRYPT, des_enc_tv_template, DES_ENC_TEST_VECTORS);
		test_cipher ("des", MODE_ECB, DECRYPT, des_dec_tv_template, DES_DEC_TEST_VECTORS);
		test_cipher ("des", MODE_CBC, ENCRYPT, des_cbc_enc_tv_template, DES_CBC_ENC_TEST_VECTORS);
		test_cipher ("des", MODE_CBC, DECRYPT, des_cbc_dec_tv_template, DES_CBC_DEC_TEST_VECTORS);
		break;

	case 4:
		test_cipher ("des3_ede", MODE_ECB, ENCRYPT, des3_ede_enc_tv_template, DES3_EDE_ENC_TEST_VECTORS);
		test_cipher ("des3_ede", MODE_ECB, DECRYPT, des3_ede_dec_tv_template, DES3_EDE_DEC_TEST_VECTORS);
		
		break;

	case 5:
		test_hash("md4", md4_tv_template, MD4_TEST_VECTORS);
		break;

	case 6:
		test_hash("sha256", sha256_tv_template, SHA256_TEST_VECTORS);
		break;

	case 7:
		test_cipher ("blowfish", MODE_ECB, ENCRYPT, bf_enc_tv_template, BF_ENC_TEST_VECTORS);
		test_cipher ("blowfish", MODE_ECB, DECRYPT, bf_dec_tv_template, BF_DEC_TEST_VECTORS);
		test_cipher ("blowfish", MODE_CBC, ENCRYPT, bf_cbc_enc_tv_template, BF_CBC_ENC_TEST_VECTORS);
		test_cipher ("blowfish", MODE_CBC, DECRYPT, bf_cbc_dec_tv_template, BF_CBC_DEC_TEST_VECTORS);
		break;

	case 8:
		test_cipher ("twofish", MODE_ECB, ENCRYPT, tf_enc_tv_template, TF_ENC_TEST_VECTORS);
		test_cipher ("twofish", MODE_ECB, DECRYPT, tf_dec_tv_template, TF_DEC_TEST_VECTORS);
		test_cipher ("twofish", MODE_CBC, ENCRYPT, tf_cbc_enc_tv_template, TF_CBC_ENC_TEST_VECTORS);
		test_cipher ("twofish", MODE_CBC, DECRYPT, tf_cbc_dec_tv_template, TF_CBC_DEC_TEST_VECTORS);
		break;

	case 9:
		test_cipher ("serpent", MODE_ECB, ENCRYPT, serpent_enc_tv_template, SERPENT_ENC_TEST_VECTORS);
		test_cipher ("serpent", MODE_ECB, DECRYPT, serpent_dec_tv_template, SERPENT_DEC_TEST_VECTORS);
		break;

	case 10:
		test_cipher ("aes", MODE_ECB, ENCRYPT, aes_enc_tv_template, AES_ENC_TEST_VECTORS);
		test_cipher ("aes", MODE_ECB, DECRYPT, aes_dec_tv_template, AES_DEC_TEST_VECTORS);
		break;

	case 11:
		test_hash("sha384", sha384_tv_template, SHA384_TEST_VECTORS);
		break;

	case 12:
		test_hash("sha512", sha512_tv_template, SHA512_TEST_VECTORS);
		break;

	case 13:
		test_deflate();
		break;

	case 14:
		test_cipher ("cast5", MODE_ECB, ENCRYPT, cast5_enc_tv_template, CAST5_ENC_TEST_VECTORS);
		test_cipher ("cast5", MODE_ECB, DECRYPT, cast5_dec_tv_template, CAST5_DEC_TEST_VECTORS);
		break;

	case 15:
		test_cipher ("cast6", MODE_ECB, ENCRYPT, cast6_enc_tv_template, CAST6_ENC_TEST_VECTORS);
		test_cipher ("cast6", MODE_ECB, DECRYPT, cast6_dec_tv_template, CAST6_DEC_TEST_VECTORS);
		break;

	case 16:
		test_cipher ("arc4", MODE_ECB, ENCRYPT, arc4_enc_tv_template, ARC4_ENC_TEST_VECTORS);
		test_cipher ("arc4", MODE_ECB, DECRYPT, arc4_dec_tv_template, ARC4_DEC_TEST_VECTORS);
		break;

	case 17:
		test_hash("michael_mic", michael_mic_tv_template, MICHAEL_MIC_TEST_VECTORS);
		break;

	case 18:
		test_crc32c();
		break;

	case 19:
		test_cipher ("tea", MODE_ECB, ENCRYPT, tea_enc_tv_template, TEA_ENC_TEST_VECTORS);
		test_cipher ("tea", MODE_ECB, DECRYPT, tea_dec_tv_template, TEA_DEC_TEST_VECTORS);
		break;

	case 20:
		test_cipher ("xtea", MODE_ECB, ENCRYPT, xtea_enc_tv_template, XTEA_ENC_TEST_VECTORS);
		test_cipher ("xtea", MODE_ECB, DECRYPT, xtea_dec_tv_template, XTEA_DEC_TEST_VECTORS);
		break;

	case 21:
		test_cipher ("khazad", MODE_ECB, ENCRYPT, khazad_enc_tv_template, KHAZAD_ENC_TEST_VECTORS);
		test_cipher ("khazad", MODE_ECB, DECRYPT, khazad_dec_tv_template, KHAZAD_DEC_TEST_VECTORS);
		break;

	case 22:
		test_hash("wp512", wp512_tv_template, WP512_TEST_VECTORS);
		break;

	case 23:
		test_hash("wp384", wp384_tv_template, WP384_TEST_VECTORS);
		break;

	case 24:
		test_hash("wp256", wp256_tv_template, WP256_TEST_VECTORS);
		break;

	case 25:
		test_cipher ("tnepres", MODE_ECB, ENCRYPT, tnepres_enc_tv_template, TNEPRES_ENC_TEST_VECTORS);
		test_cipher ("tnepres", MODE_ECB, DECRYPT, tnepres_dec_tv_template, TNEPRES_DEC_TEST_VECTORS);
		break;

	case 26:
		test_cipher ("anubis", MODE_ECB, ENCRYPT, anubis_enc_tv_template, ANUBIS_ENC_TEST_VECTORS);
		test_cipher ("anubis", MODE_ECB, DECRYPT, anubis_dec_tv_template, ANUBIS_DEC_TEST_VECTORS);
		test_cipher ("anubis", MODE_CBC, ENCRYPT, anubis_cbc_enc_tv_template, ANUBIS_CBC_ENC_TEST_VECTORS);
		test_cipher ("anubis", MODE_CBC, DECRYPT, anubis_cbc_dec_tv_template, ANUBIS_CBC_ENC_TEST_VECTORS);
		break;

	case 27:
		test_hash("tgr192", tgr192_tv_template, TGR192_TEST_VECTORS);
		break;

	case 28:

		test_hash("tgr160", tgr160_tv_template, TGR160_TEST_VECTORS);
		break;

	case 29:
		test_hash("tgr128", tgr128_tv_template, TGR128_TEST_VECTORS);
		break;
		
	case 30:
		test_cipher ("xeta", MODE_ECB, ENCRYPT, xeta_enc_tv_template, XETA_ENC_TEST_VECTORS);
		test_cipher ("xeta", MODE_ECB, DECRYPT, xeta_dec_tv_template, XETA_DEC_TEST_VECTORS);
		break;

#ifdef CONFIG_CRYPTO_HMAC
	case 100:
		test_hmac("md5", hmac_md5_tv_template, HMAC_MD5_TEST_VECTORS);
		break;

	case 101:
		test_hmac("sha1", hmac_sha1_tv_template, HMAC_SHA1_TEST_VECTORS);
		break;

	case 102:
		test_hmac("sha256", hmac_sha256_tv_template, HMAC_SHA256_TEST_VECTORS);
		break;

#endif

	case 200:
		test_cipher_speed("aes", MODE_ECB, ENCRYPT, sec, NULL, 0,
				  aes_speed_template);
		test_cipher_speed("aes", MODE_ECB, DECRYPT, sec, NULL, 0,
				  aes_speed_template);
		test_cipher_speed("aes", MODE_CBC, ENCRYPT, sec, NULL, 0,
				  aes_speed_template);
		test_cipher_speed("aes", MODE_CBC, DECRYPT, sec, NULL, 0,
				  aes_speed_template);
		break;

	case 201:
		test_cipher_speed("des3_ede", MODE_ECB, ENCRYPT, sec,
				  des3_ede_enc_tv_template,
				  DES3_EDE_ENC_TEST_VECTORS,
				  des3_ede_speed_template);
		test_cipher_speed("des3_ede", MODE_ECB, DECRYPT, sec,
				  des3_ede_dec_tv_template,
				  DES3_EDE_DEC_TEST_VECTORS,
				  des3_ede_speed_template);
		test_cipher_speed("des3_ede", MODE_CBC, ENCRYPT, sec,
				  des3_ede_enc_tv_template,
				  DES3_EDE_ENC_TEST_VECTORS,
				  des3_ede_speed_template);
		test_cipher_speed("des3_ede", MODE_CBC, DECRYPT, sec,
				  des3_ede_dec_tv_template,
				  DES3_EDE_DEC_TEST_VECTORS,
				  des3_ede_speed_template);
				  
		break;

	case 202:
		test_cipher_speed("twofish", MODE_ECB, ENCRYPT, sec, NULL, 0,
				  twofish_speed_template);
		test_cipher_speed("twofish", MODE_ECB, DECRYPT, sec, NULL, 0,
				  twofish_speed_template);
		test_cipher_speed("twofish", MODE_CBC, ENCRYPT, sec, NULL, 0,
				  twofish_speed_template);
		test_cipher_speed("twofish", MODE_CBC, DECRYPT, sec, NULL, 0,
				  twofish_speed_template);
		break;

	case 203:
		test_cipher_speed("blowfish", MODE_ECB, ENCRYPT, sec, NULL, 0,
				  blowfish_speed_template);
		test_cipher_speed("blowfish", MODE_ECB, DECRYPT, sec, NULL, 0,
				  blowfish_speed_template);
		test_cipher_speed("blowfish", MODE_CBC, ENCRYPT, sec, NULL, 0,
				  blowfish_speed_template);
		test_cipher_speed("blowfish", MODE_CBC, DECRYPT, sec, NULL, 0,
				  blowfish_speed_template);
		break;

	case 204:
		test_cipher_speed("des", MODE_ECB, ENCRYPT, sec, NULL, 0,
				  des_speed_template);
		test_cipher_speed("des", MODE_ECB, DECRYPT, sec, NULL, 0,
				  des_speed_template);
		test_cipher_speed("des", MODE_CBC, ENCRYPT, sec, NULL, 0,
				  des_speed_template);
		test_cipher_speed("des", MODE_CBC, DECRYPT, sec, NULL, 0,
				  des_speed_template);
		break;

	case 999:
		test_hash("md5", md5_tv_template, MD5_TEST_VECTORS);
		test_hash("sha1", sha1_tv_template, SHA1_TEST_VECTORS);
		test_hmac("md5", hmac_md5_tv_template, HMAC_MD5_TEST_VECTORS);
		test_hmac("sha1", hmac_sha1_tv_template, HMAC_SHA1_TEST_VECTORS);
		//DES
		test_cipher ("des", MODE_ECB, ENCRYPT, des_enc_tv_template, DES_ENC_TEST_VECTORS);
        test_cipher ("des", MODE_ECB, DECRYPT, des_dec_tv_template, DES_DEC_TEST_VECTORS);
        test_cipher ("des", MODE_CBC, ENCRYPT, des_cbc_enc_tv_template, DES_CBC_ENC_TEST_VECTORS);
        test_cipher ("des", MODE_CBC, DECRYPT, des_cbc_dec_tv_template, DES_CBC_DEC_TEST_VECTORS);
	
		//DES3_EDE
		test_cipher ("des3_ede", MODE_ECB, ENCRYPT, des3_ede_enc_tv_template, DES3_EDE_ENC_TEST_VECTORS);
        test_cipher ("des3_ede", MODE_ECB, DECRYPT, des3_ede_dec_tv_template, DES3_EDE_DEC_TEST_VECTORS);

		//AES
		test_cipher ("aes", MODE_ECB, ENCRYPT, aes_enc_tv_template, AES_ENC_TEST_VECTORS);
		test_cipher ("aes", MODE_ECB, DECRYPT, aes_dec_tv_template, AES_DEC_TEST_VECTORS);

		
		break;
	case 998:
		//test_hash("md5", md5_tv_template, MD5_TEST_VECTORS);
		//test_hash("sha1", sha1_tv_template, SHA1_TEST_VECTORS);
		test_hmac("md5", hmac_md5_tv_template, HMAC_MD5_TEST_VECTORS);
		test_hmac("sha1", hmac_sha1_tv_template, HMAC_SHA1_TEST_VECTORS);
		
		break;		
	
	case 997:
		test_digest();
		test_crypto_cipher();
		test_hash("md5", md5_tv_template, MD5_TEST_VECTORS);
		test_hash("sha1", sha1_tv_template, SHA1_TEST_VECTORS);
		test_hmac("md5", hmac_md5_tv_template, HMAC_MD5_TEST_VECTORS);
		test_hmac("sha1", hmac_sha1_tv_template, HMAC_SHA1_TEST_VECTORS);
		//DES
		//test_cipher ("des", MODE_ECB, ENCRYPT, des_enc_tv_template, DES_ENC_TEST_VECTORS);
    //    test_cipher ("des", MODE_ECB, DECRYPT, des_dec_tv_template, DES_DEC_TEST_VECTORS);
    //    test_cipher ("des", MODE_CBC, ENCRYPT, des_cbc_enc_tv_template, DES_CBC_ENC_TEST_VECTORS);
    //    test_cipher ("des", MODE_CBC, DECRYPT, des_cbc_dec_tv_template, DES_CBC_DEC_TEST_VECTORS);
	
		//DES3_EDE
		//test_cipher ("des3_ede", MODE_ECB, ENCRYPT, des3_ede_enc_tv_template, DES3_EDE_ENC_TEST_VECTORS);
    //    test_cipher ("des3_ede", MODE_ECB, DECRYPT, des3_ede_dec_tv_template, DES3_EDE_DEC_TEST_VECTORS);

		//AES
		//test_cipher ("aes", MODE_ECB, ENCRYPT, aes_enc_tv_template, AES_ENC_TEST_VECTORS);
		//test_cipher ("aes", MODE_ECB, DECRYPT, aes_dec_tv_template, AES_DEC_TEST_VECTORS);

		break;
		
	case 1000:
		test_available();
		break;

	default:
		/* useful for debugging */
		printk("not testing anything\n");
		break;
	}
}

int __init init(void)
{
	tvmem = kmalloc(TVMEMSIZE, GFP_KERNEL);
	if (tvmem == NULL)
		return -ENOMEM;

	xbuf = kmalloc(XBUFSIZE, GFP_KERNEL);
	if (xbuf == NULL) {
		kfree(tvmem);
		return -ENOMEM;
	}

	do_test();

	kfree(xbuf);
	kfree(tvmem);
	return 0;
}

/*
 * If an init function is provided, an exit function must also be provided
 * to allow module unload.
 */
static void __exit fini(void) { }

module_init(init);
module_exit(fini);

module_param(mode, int, 0);
module_param(sec, uint, 0);
MODULE_PARM_DESC(sec, "Length in seconds of speed tests "
		      "(defaults to zero which uses CPU cycles instead)");

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Quick & dirty crypto testing module");
MODULE_AUTHOR("James Morris <jmorris@intercode.com.au>");
