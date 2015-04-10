/*
 * Cryptographic API.
 *
 * HMAC: Keyed-Hashing for Message Authentication (RFC2104).
 *
 * Copyright (c) 2002 James Morris <jmorris@intercode.com.au>
 *
 * The HMAC implementation is derived from USAGI.
 * Copyright (c) 2002 Kazunori Miyazawa <miyazawa@linux-ipv6.org> / USAGI
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option) 
 * any later version.
 *
 */
#include <linux/crypto.h>
#include <linux/mm.h>
#include <linux/highmem.h>
#include <linux/slab.h>
#include <linux/scatterlist.h>
#include <linux/dma-mapping.h>
#include "internal.h"

#ifdef CONFIG_SL2312_IPSEC

#include <asm/arch/sl2312_ipsec.h>
#include <linux/sysctl_storlink.h>

#define     IPSEC_TEXT_LEN    32768 //2048 + 256
unsigned char packet[IPSEC_TEXT_LEN];
#define      HSG_NUMBER	32
struct scatterlist hsg[HSG_NUMBER];

extern unsigned long crypto_flags,crypto_go;
extern  spinlock_t crypto_done_lock;
extern  unsigned int crp_done ;
//extern  struct IPSEC_PACKET_S hmac_op;
struct IPSEC_PACKET_S hmac_op;

extern  void crypto_callback(struct IPSEC_PACKET_S *op_info);

#endif

static void hash_key(struct crypto_tfm *tfm, u8 *key, unsigned int keylen)
{
	struct scatterlist tmp;
	
	sg_set_buf(&tmp, key, keylen);
	crypto_digest_digest(tfm, &tmp, 1, key);
}

int crypto_alloc_hmac_block(struct crypto_tfm *tfm)
{
	int ret = 0;

	BUG_ON(!crypto_tfm_alg_blocksize(tfm));
	
	tfm->crt_digest.dit_hmac_block = kmalloc(crypto_tfm_alg_blocksize(tfm),
	                                         GFP_KERNEL);
	if (tfm->crt_digest.dit_hmac_block == NULL)
		ret = -ENOMEM;

	return ret;
		
}

void crypto_free_hmac_block(struct crypto_tfm *tfm)
{
	kfree(tfm->crt_digest.dit_hmac_block);
}

void crypto_hmac_init(struct crypto_tfm *tfm, u8 *key, unsigned int *keylen)
{
#ifdef CONFIG_SL2312_IPSEC
	if (storlink_ctl.hw_crypto == 1)
	{

	int error = 0;
	struct scatterlist tmpsc;
	
	
	crypto_digest_init(tfm);
	 
	if(*keylen > tfm->__crt_alg->cra_blocksize)
	{
		unsigned char *tk = kmalloc(tfm->__crt_alg->cra_blocksize, GFP_KERNEL);
		if (!tk) {
			printk(KERN_ERR "%s: tk is not allocated\n", __FUNCTION__);
			error = -ENOMEM;

		}
		
		memset(tk, 0, tfm->__crt_alg->cra_blocksize);

		tmpsc.page = virt_to_page(key);
		tmpsc.offset = offset_in_page(key);
		tmpsc.length = *keylen;

		
		tfm->crt_digest.dit_init(tfm);
		tfm->crt_digest.dit_update(tfm, &tmpsc, 1); //nsg);
		tfm->crt_digest.dit_final(tfm, tk);
		crypto_go = 1;
		memcpy(key,tk,tfm->__crt_alg->cra_blocksize);
		*keylen = tfm->__crt_alg->cra_blocksize;
   	
		kfree(tk);		
	}
	
	

//		if(crypto_go == 0)
//			printk("%s: crypto_go = %x\n",__func__,crypto_go);
	

	crypto_go = 0;


	memset(&hmac_op,0x00,sizeof(struct IPSEC_PACKET_S));
	memset(&packet,0x00,IPSEC_TEXT_LEN);
	memset(&hsg,0x00,HSG_NUMBER*sizeof(struct scatterlist));
	}
	else
#endif
	{
	unsigned int i;
	struct scatterlist tmp;
	char *ipad = tfm->crt_digest.dit_hmac_block;
	
	if (*keylen > crypto_tfm_alg_blocksize(tfm)) {
		hash_key(tfm, key, *keylen);
		*keylen = crypto_tfm_alg_digestsize(tfm);
	}

	memset(ipad, 0, crypto_tfm_alg_blocksize(tfm));
	memcpy(ipad, key, *keylen);

	for (i = 0; i < crypto_tfm_alg_blocksize(tfm); i++)
		ipad[i] ^= 0x36;

	sg_set_buf(&tmp, ipad, crypto_tfm_alg_blocksize(tfm));
	
	crypto_digest_init(tfm);
	crypto_digest_update(tfm, &tmp, 1);
	}	
}

void crypto_hmac_update(struct crypto_tfm *tfm,
                        struct scatterlist *sg, unsigned int nsg)
{
#ifdef CONFIG_SL2312_IPSEC
	if (storlink_ctl.hw_crypto == 1)
	{
	unsigned int plen=0,i;
	unsigned char *in_packet;
	
	for(i=0;i<nsg;i++)
	{
		plen += sg[i].length;	
	
		in_packet = kmap(sg[i].page) + sg[i].offset;
		

		if(hmac_op.pkt_len==0) 
		{

			hmac_op.pkt_len = sg[i].length;
			hmac_op.auth_algorithm_len = sg[i].length;
		}
		else
		{

			hmac_op.pkt_len += sg[i].length;
			hmac_op.auth_algorithm_len += sg[i].length;
		}
	}
	for(i=0;i<HSG_NUMBER;i++)
	{
		if(hsg[i].length==0)
		{
			memcpy(&hsg[i],sg,nsg*sizeof(struct scatterlist));
			break;
		}
	}
	}
	else
#endif
		crypto_digest_update(tfm, sg, nsg);
}

void crypto_hmac_final(struct crypto_tfm *tfm, u8 *key,
                       unsigned int *keylen, u8 *out)
{
#ifdef CONFIG_SL2312_IPSEC
	if (storlink_ctl.hw_crypto == 1)
	{
	hmac_op.op_mode = AUTH;
	hmac_op.auth_algorithm = ipsec_get_auth_algorithm((unsigned char *)tfm->__crt_alg->cra_name,1); //(0) AUTH; (1) HMAC
	hmac_op.auth_key_size = *keylen;
	memcpy(hmac_op.auth_key, key, *keylen);
	
	hmac_op.in_packet = &hsg;
	hmac_op.out_packet = (u8 *)&packet;
	hmac_op.out_buffer_len = IPSEC_TEXT_LEN;

//	hmac_op.callback = crypto_callback;
	hmac_op.callback = NULL;
	hmac_op.auth_header_len = 0;
	if(hmac_op.pkt_len > IPSEC_TEXT_LEN)
	{
		printk("%s :crp_done not ready !!\n",__func__);
		return;
	}

	ipsec_crypto_hw_process(&hmac_op);	
 
	//memcpy(out, (u8 *)(hmac_op.out_packet+hmac_op.pkt_len),crypto_tfm_alg_digestsize(tfm));
	memcpy(out, &packet[hmac_op.pkt_len],crypto_tfm_alg_digestsize(tfm));

	hmac_op.pkt_len =0;
	hmac_op.auth_algorithm_len =0;
	}
	else
#endif
	{
	unsigned int i;
	struct scatterlist tmp;
	char *opad = tfm->crt_digest.dit_hmac_block;
	
	if (*keylen > crypto_tfm_alg_blocksize(tfm)) {
		hash_key(tfm, key, *keylen);
		*keylen = crypto_tfm_alg_digestsize(tfm);
	}

	crypto_digest_final(tfm, out);

	memset(opad, 0, crypto_tfm_alg_blocksize(tfm));
	memcpy(opad, key, *keylen);
		
	for (i = 0; i < crypto_tfm_alg_blocksize(tfm); i++)
		opad[i] ^= 0x5c;

	sg_set_buf(&tmp, opad, crypto_tfm_alg_blocksize(tfm));

	crypto_digest_init(tfm);
	crypto_digest_update(tfm, &tmp, 1);
	
	sg_set_buf(&tmp, out, crypto_tfm_alg_digestsize(tfm));
	
	crypto_digest_update(tfm, &tmp, 1);
	crypto_digest_final(tfm, out);
	}
}

void crypto_hmac(struct crypto_tfm *tfm, u8 *key, unsigned int *keylen,
                 struct scatterlist *sg, unsigned int nsg, u8 *out)
{

	crypto_hmac_init(tfm, key, keylen);
	crypto_hmac_update(tfm, sg, nsg);
	crypto_hmac_final(tfm, key, keylen, out);

}

EXPORT_SYMBOL_GPL(crypto_hmac_init);
EXPORT_SYMBOL_GPL(crypto_hmac_update);
EXPORT_SYMBOL_GPL(crypto_hmac_final);
EXPORT_SYMBOL_GPL(crypto_hmac);

