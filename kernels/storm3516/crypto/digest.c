/*
 * Cryptographic API.
 *
 * Digest operations.
 *
 * Copyright (c) 2002 James Morris <jmorris@intercode.com.au>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option) 
 * any later version.
 *
 */
#include <linux/crypto.h>
#include <linux/mm.h>
#include <linux/errno.h>
#include <linux/highmem.h>
#include <asm/scatterlist.h>
#include "internal.h"

#ifdef CONFIG_SL2312_IPSEC
#include <linux/dma-mapping.h>
#include <asm/arch/sl2312_ipsec.h>
#include <linux/sysctl_storlink.h>

#define     IPSEC_TEXT_LEN    32768 //2048
#define	DSG_NUMBER	32
unsigned char di_packet[IPSEC_TEXT_LEN];

struct scatterlist dsg[DSG_NUMBER];
///////////

extern unsigned long crypto_flags;
extern  spinlock_t crypto_done_lock;
extern  unsigned int crp_done,crypto_go ;
//extern  struct IPSEC_PACKET_S digest_op;
struct IPSEC_PACKET_S digest_op;

extern  void crypto_callback(struct IPSEC_PACKET_S *op_info);

#endif

static void init(struct crypto_tfm *tfm)
{
	tfm->__crt_alg->cra_digest.dia_init(crypto_tfm_ctx(tfm));
#ifdef CONFIG_SL2312_IPSEC
	memset(&dsg,0x00,DSG_NUMBER*sizeof(struct scatterlist));
	memset(&digest_op, 0x0, sizeof(struct IPSEC_PACKET_S));
#endif	
}

static void update(struct crypto_tfm *tfm,
                   struct scatterlist *sg, unsigned int nsg)
{
	unsigned int i;

#ifdef CONFIG_SL2312_IPSEC
	if (storlink_ctl.hw_crypto == 1)
	{

	unsigned int plen=0;
	unsigned char *in_packet;


//		if(crypto_go == 0)
//			printk("%s: crypto_go = %x\n",__func__,crypto_go);
		crypto_go = 0;
		

	
		for(i=0;i<nsg;i++)
		{
				plen += sg[i].length;	
	
				in_packet = kmap(sg[i].page) + sg[i].offset;
				

				if(digest_op.pkt_len==0)
				{

					digest_op.pkt_len = sg[i].length;
					digest_op.auth_algorithm_len = sg[i].length;
				}
				else
				{

					digest_op.pkt_len += sg[i].length;
					digest_op.auth_algorithm_len += sg[i].length;
				}
		
		}
		for(i=0;i<DSG_NUMBER;i++)
		{
			if(dsg[i].length==0)
			{
				memcpy(&dsg[i],sg,nsg*sizeof(struct scatterlist));
				break;
			}
		}
		
  
		digest_op.op_mode = AUTH;
		digest_op.auth_algorithm = ipsec_get_auth_algorithm((unsigned char *)tfm->__crt_alg->cra_name,0); //(0) AUTH; (1) HMAC
//		digest_op.callback = crypto_callback;
		digest_op.callback = NULL;
		digest_op.auth_header_len = 0;

	}
	else
#endif
	{
	for (i = 0; i < nsg; i++) {

		struct page *pg = sg[i].page;
		unsigned int offset = sg[i].offset;
		unsigned int l = sg[i].length;

		do {
			unsigned int bytes_from_page = min(l, ((unsigned int)
							   (PAGE_SIZE)) - 
							   offset);
			char *p = crypto_kmap(pg, 0) + offset;

			tfm->__crt_alg->cra_digest.dia_update
					(crypto_tfm_ctx(tfm), p,
					 bytes_from_page);
			crypto_kunmap(p, 0);
			crypto_yield(tfm);
			offset = 0;
			pg++;
			l -= bytes_from_page;
		} while (l > 0);
	}
	}
}

static void
hexdump(unsigned char *buf, unsigned int len)
{
	while (len--)
		printk("%02x", *buf++);

	printk("\n");
}

static void final(struct crypto_tfm *tfm, u8 *out)
{
#ifdef CONFIG_SL2312_IPSEC
	if (storlink_ctl.hw_crypto == 1)
	{

	if(digest_op.pkt_len > IPSEC_TEXT_LEN)
	{
		printk("%s :length too long !!\n",__func__);
		return;
	}
	digest_op.in_packet = &dsg;
	digest_op.out_packet = (u8 *)&di_packet;
	digest_op.out_buffer_len = IPSEC_TEXT_LEN;

	
	ipsec_crypto_hw_process(&digest_op);	
 
	//memcpy(out, (u8 *)(digest_op.out_packet+digest_op.pkt_len),crypto_tfm_alg_digestsize(tfm));
	memcpy(out, &di_packet[digest_op.pkt_len],crypto_tfm_alg_digestsize(tfm));

	
	}
	else
#endif  	
		tfm->__crt_alg->cra_digest.dia_final(crypto_tfm_ctx(tfm), out);
}

static int setkey(struct crypto_tfm *tfm, const u8 *key, unsigned int keylen)
{
#ifdef CONFIG_SL2312_IPSEC
	if (storlink_ctl.hw_crypto == 1)
    {
        digest_op.auth_key_size = keylen;
        memcpy(digest_op.auth_key,key,keylen);
        return 0;
    } 
	else
#endif
	{
	u32 flags;
	if (tfm->__crt_alg->cra_digest.dia_setkey == NULL)
		return -ENOSYS;
	return tfm->__crt_alg->cra_digest.dia_setkey(crypto_tfm_ctx(tfm),
						     key, keylen, &flags);
	}
}

static void digest(struct crypto_tfm *tfm,
                   struct scatterlist *sg, unsigned int nsg, u8 *out)
{
//	

	tfm->crt_digest.dit_init(tfm);
#ifdef CONFIG_SL2312_IPSEC
	if (storlink_ctl.hw_crypto == 1)
	{
	update(tfm,sg,nsg);
	final(tfm,out);
	}
	else
#endif
	{
		unsigned int i;
	for (i = 0; i < nsg; i++) {
		char *p = crypto_kmap(sg[i].page, 0) + sg[i].offset;
		tfm->__crt_alg->cra_digest.dia_update(crypto_tfm_ctx(tfm),
		                                      p, sg[i].length);
		crypto_kunmap(p, 0);
		crypto_yield(tfm);
	}
	crypto_digest_final(tfm, out);
	}
}

int crypto_init_digest_flags(struct crypto_tfm *tfm, u32 flags)
{
	return flags ? -EINVAL : 0;
}

int crypto_init_digest_ops(struct crypto_tfm *tfm)
{
	struct digest_tfm *ops = &tfm->crt_digest;
	
	ops->dit_init	= init;
	ops->dit_update	= update;
	ops->dit_final	= final;
	ops->dit_digest	= digest;
	ops->dit_setkey	= setkey;
	
	return crypto_alloc_hmac_block(tfm);
}

void crypto_exit_digest_ops(struct crypto_tfm *tfm)
{
	crypto_free_hmac_block(tfm);
}
