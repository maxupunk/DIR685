/*
 * An OCF module that uses the linux kernel cryptoapi, based on the
 * original crpstorm for BSD by Angelos D. Keromytis (angelos@cis.upenn.edu)
 * but is mostly unrecognisable,
 *
 * This code written by David McCullough <dmccullough@cyberguard.com>
 * Copyright (C) 2004-2005 David McCullough <dmccullough@cyberguard.com>
 * All rights reserved.
 *
 * Copyright (C) 2004-2005 Intel Corporation.  All Rights Reserved.
 *
 * LICENSE TERMS
 *
 * The free distribution and use of this software in both source and binary
 * form is allowed (with or without changes) provided that:
 *
 *   1. distributions of this source code include the above copyright
 *      notice, this list of conditions and the following disclaimer;
 *
 *   2. distributions in binary form include the above copyright
 *      notice, this list of conditions and the following disclaimer
 *      in the documentation and/or other associated materials;
 *
 *   3. the copyright holder's name is not used to endorse products
 *      built using this software without specific written permission.
 *
 * ALTERNATIVELY, provided that this notice is retained in full, this product
 * may be distributed under the terms of the GNU General Public License (GPL),
 * in which case the provisions of the GPL apply INSTEAD OF those given above.
 *
 * DISCLAIMER
 *
 * This software is provided 'as is' with no explicit or implied warranties
 * in respect of its properties, including, but not limited to, correctness
 * and/or fitness for purpose.
 * ---------------------------------------------------------------------------
 */

#include <linux/config.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/crypto.h>
#include <linux/mm.h>
#include <linux/skbuff.h>
#include <linux/random.h>
#include <asm/scatterlist.h>
 
#include <cryptodev.h>
#include <uio.h>
#include <crp_storm.h>

#ifdef CONFIG_OCF_STORM
#include <asm/arch/sl2312_ipsec.h>
//#include <linux/dma-mapping.h>
//#include <asm/hardware.h>
//#include <asm/io.h>
//#include <linux/sysctl_storlink.h>
#define     IPSEC_TEXT_LEN    32768 //2048
unsigned char pout[IPSEC_TEXT_LEN];
unsigned char *ppout;
#endif



#define offset_in_page(p) ((unsigned long)(p) & ~PAGE_MASK)

/* Software session entry */

#define SW_TYPE_CIPHER	0
#define SW_TYPE_HMAC	1
#define SW_TYPE_AUTH2	2
#define SW_TYPE_HASH	3
#define SW_TYPE_COMP	4

struct crpstorm_data {
	int					sw_type;
	int					sw_alg;
	int					sw_authlen;
	struct IPSEC_PACKET_S	*sw_op;
	struct crpstorm_data	*sw_next;
};

static int32_t crpstorm_id = -1;
static struct crpstorm_data **crpstorm_sessions = NULL;
static u_int32_t crpstorm_sesnum = 0;

static	int crpstorm_process(void *, struct cryptop *, int);
static	int crpstorm_newsession(void *, u_int32_t *, struct cryptoini *);
static	int crpstorm_freesession(void *, u_int64_t);


static int debug = 0;
MODULE_PARM(debug, "i");
MODULE_PARM_DESC(debug,
	   "Enable debug");

static void
skb_copy_bits_back(struct sk_buff *skb, int offset, caddr_t cp, int len)
{
	int i;
	if (offset < skb_headlen(skb)) {
		memcpy(skb->data + offset, cp, min_t(int, skb_headlen(skb), len));
		len -= skb_headlen(skb);
		cp += skb_headlen(skb);
	}
	offset -= skb_headlen(skb);
	for (i = 0; len > 0 && i < skb_shinfo(skb)->nr_frags; i++) {
		if (offset < skb_shinfo(skb)->frags[i].size) {
			memcpy(page_address(skb_shinfo(skb)->frags[i].page) +
					skb_shinfo(skb)->frags[i].page_offset,
					cp, min_t(int, skb_shinfo(skb)->frags[i].size, len));
			len -= skb_shinfo(skb)->frags[i].size;
			cp += skb_shinfo(skb)->frags[i].size;
		}
		offset -= skb_shinfo(skb)->frags[i].size;
	}
}

/*
 * Generate a new software session.
 */
static int
crpstorm_newsession(void *arg, u_int32_t *sid, struct cryptoini *cri)
{
	struct crpstorm_data **swd;
	u_int32_t i;
//	int error;
	char *algo;
	int mode, sw_type;

	//dprintk("        -->%s()\n", __FUNCTION__);
	if (sid == NULL || cri == NULL) {
		dprintk("        -->%s,%d - EINVAL\n", __FILE__, __LINE__);
		return EINVAL;
	}

	if (crpstorm_sessions) {
		for (i = 1; i < crpstorm_sesnum; i++)
			if (crpstorm_sessions[i] == NULL)
				break;
	} else
		i = 1;		/* NB: to silence compiler warning */

	if (crpstorm_sessions == NULL || i == crpstorm_sesnum) {
		if (crpstorm_sessions == NULL) {
			i = 1; /* We leave crpstorm_sessions[0] empty */
			crpstorm_sesnum = CRYPTO_SW_SESSIONS;
		} else
			crpstorm_sesnum *= 2;

		swd = kmalloc(crpstorm_sesnum * sizeof(struct crpstorm_data *), GFP_ATOMIC);
		if (swd == NULL) {
			/* Reset session number */
			if (crpstorm_sesnum == CRYPTO_SW_SESSIONS)
				crpstorm_sesnum = 0;
			else
				crpstorm_sesnum /= 2;
			dprintk("        -->%s,%d: ENOBUFS\n", __FILE__, __LINE__);
			return ENOBUFS;
		}
		memset(swd, 0, crpstorm_sesnum * sizeof(struct crpstorm_data *));

		/* Copy existing sessions */
		if (crpstorm_sessions) {
			memcpy(swd, crpstorm_sessions,
			    (crpstorm_sesnum / 2) * sizeof(struct crpstorm_data *));
			kfree(crpstorm_sessions);
		}

		crpstorm_sessions = swd;
	}

	swd = &crpstorm_sessions[i];
	*sid = i;

	while (cri) {
		*swd = (struct crpstorm_data *) kmalloc(sizeof(struct crpstorm_data),
				GFP_ATOMIC);
		if (*swd == NULL) {
			crpstorm_freesession(NULL, i);
			dprintk("        -->%s,%d: EINVAL\n", __FILE__, __LINE__);
			return ENOBUFS;
		}
		memset(*swd, 0, sizeof(struct crpstorm_data));
		
		(*swd)->sw_op = (struct IPSEC_PACKET_S *) kmalloc(sizeof(struct IPSEC_PACKET_S), GFP_ATOMIC);
		if (((*swd)->sw_op) == NULL) 
		{
			dprintk("        -->%s,%d: EINVAL\n", __FILE__, __LINE__);
			crpstorm_freesession(NULL, i);
			return ENOBUFS;
		}
		memset((*swd)->sw_op, 0, sizeof(struct IPSEC_PACKET_S));
		
		algo = NULL;
		mode = 0;
		sw_type = SW_TYPE_CIPHER;

		switch (cri->cri_alg) {
		case CRYPTO_DES_CBC:
			algo = "des";
			(*swd)->sw_op->cipher_algorithm = CBC_DES;
			(*swd)->sw_op->iv_size = 8;
			mode = CRYPTO_TFM_MODE_CBC;
			break;
		case CRYPTO_DES_ECB:
			algo = "des";
			(*swd)->sw_op->cipher_algorithm = ECB_DES;
			(*swd)->sw_op->iv_size = 0;
			mode = CRYPTO_TFM_MODE_ECB;
			break;
		case CRYPTO_3DES_ECB:
			algo = "des3_ede";
			(*swd)->sw_op->cipher_algorithm = ECB_3DES;
			(*swd)->sw_op->iv_size = 0;
			mode = CRYPTO_TFM_MODE_ECB;
			break;
		case CRYPTO_3DES_CBC:
			algo = "des3_ede";
			(*swd)->sw_op->cipher_algorithm = CBC_3DES;
			(*swd)->sw_op->iv_size = 8;
			mode = CRYPTO_TFM_MODE_CBC;
			break;
		//case CRYPTO_AES128_ECB:
		case CRYPTO_AES_ECB:
			algo = "aes";
			(*swd)->sw_op->cipher_algorithm = ECB_AES;
			(*swd)->sw_op->iv_size = 0;
			mode = CRYPTO_TFM_MODE_ECB;
			break;
		case CRYPTO_AES128_CBC:
			algo = "aes";
			(*swd)->sw_op->cipher_algorithm = CBC_AES;
			(*swd)->sw_op->iv_size = 16;
			mode = CRYPTO_TFM_MODE_CBC;
			break;
		case CRYPTO_AES192_ECB:
			algo = "aes";
			(*swd)->sw_op->cipher_algorithm = ECB_AES;
			(*swd)->sw_op->iv_size = 0;
			mode = CRYPTO_TFM_MODE_ECB;
			break;
		case CRYPTO_AES192_CBC:
			algo = "aes";
			(*swd)->sw_op->cipher_algorithm = CBC_AES;
			(*swd)->sw_op->iv_size = 16;
			mode = CRYPTO_TFM_MODE_CBC;
			break;
		case CRYPTO_AES256_ECB:
			algo = "aes";
			(*swd)->sw_op->cipher_algorithm = ECB_AES;
			(*swd)->sw_op->iv_size = 0;
			mode = CRYPTO_TFM_MODE_ECB;
			break;
		case CRYPTO_AES256_CBC:
			algo = "aes";
			(*swd)->sw_op->cipher_algorithm = CBC_AES;
			(*swd)->sw_op->iv_size = 16;
			mode = CRYPTO_TFM_MODE_CBC;
			break;


#if defined(CONFIG_CRYPTO_HMAC) || defined(CONFIG_CRYPTO_HMAC_MODULE)
		case CRYPTO_MD5_HMAC:
			algo = "md5";
			(*swd)->sw_op->auth_algorithm = HMAC_MD5;
			(*swd)->sw_op->op_mode = AUTH;
			(*swd)->sw_authlen = 16;//12;//
			sw_type = SW_TYPE_HMAC;
			//(*swd)->u.hmac.sw_authlen = 12;
			break;
		case CRYPTO_SHA1_HMAC:
			algo = "sha1";
			(*swd)->sw_op->auth_algorithm = HMAC_SHA1;
			(*swd)->sw_op->op_mode = AUTH;
			(*swd)->sw_authlen = 20;//12;//
			sw_type = SW_TYPE_HMAC;
			//(*swd)->u.hmac.sw_authlen = 12;
			break;
		case CRYPTO_MD5:
			algo = "md5";
			(*swd)->sw_op->auth_algorithm = MD5;
			(*swd)->sw_op->op_mode = AUTH;
			(*swd)->sw_authlen = 16;
			sw_type = SW_TYPE_HASH;
			//(*swd)->u.hmac.sw_authlen = 16;
			break;
		case CRYPTO_SHA1:
			algo = "sha1";
			(*swd)->sw_op->auth_algorithm = SHA1;
			(*swd)->sw_op->op_mode = AUTH;
			(*swd)->sw_authlen = 20;
			sw_type = SW_TYPE_HASH;
			//(*swd)->u.hmac.sw_authlen = 20;
			break;
#endif /* defined(CONFIG_CRYPTO_HMAC) || defined(CONFIG_CRYPTO_HMAC_MODULE) */

		default:
			break;
		}

		if (!algo || !*algo) {
			printk("crpstorm: Unknown algo 0x%x\n", cri->cri_alg);
			crpstorm_freesession(NULL, i);
			return EINVAL;
		}

		//dprintk("        -->%s crypto_alloc_tfm(%s, 0x%x)\n", __FUNCTION__, algo, mode);


		if (sw_type == SW_TYPE_CIPHER) {
			if (debug) {
				dprintk("        -->%s key:", __FUNCTION__);
				for (i = 0; i < (cri->cri_klen + 7) / 8; i++)
					dprintk("%s0x%x", (i % 8) ? " " : "\n    ",cri->cri_key[i]);
				dprintk("\n");
			}

				(*swd)->sw_op->cipher_key_size = ((cri->cri_klen + 7) / 8);
				memcpy((*swd)->sw_op->cipher_key, cri->cri_key, (cri->cri_klen + 7) / 8);
			
		} else if (sw_type == SW_TYPE_HMAC || sw_type == SW_TYPE_HASH) {
			(*swd)->sw_op->auth_key_size = (cri->cri_klen + 7) / 8;
			if (HMAC_BLOCK_LEN < (*swd)->sw_op->auth_key_size)
				printk("%s,%d: ERROR ERROR ERROR\n", __FILE__, __LINE__);
			memcpy((*swd)->sw_op->auth_key, cri->cri_key, (*swd)->sw_op->auth_key_size);
			
		} else {
			printk("crpstorm: Unhandled sw_type %d\n", sw_type);
			crpstorm_freesession(NULL, i);
			return EINVAL;
		}

		(*swd)->sw_alg = cri->cri_alg;
		(*swd)->sw_type = sw_type;

		cri = cri->cri_next;
		swd = &((*swd)->sw_next);
	}
	return 0;
}

/*
 * Free a session.
 */
static int
crpstorm_freesession(void *arg, u_int64_t tid)
{
	struct crpstorm_data *swd;
	u_int32_t sid = CRYPTO_SESID2LID(tid);

	dprintk("        -->%s()\n", __FUNCTION__);
	if (sid > crpstorm_sesnum || crpstorm_sessions == NULL ||
			crpstorm_sessions[sid] == NULL) {
		dprintk("        -->%s,%d: EINVAL\n", __FILE__, __LINE__);
		return(EINVAL);
	}

	/* Silently accept and return */
	if (sid == 0)
		return(0);

	while ((swd = crpstorm_sessions[sid]) != NULL) {
		crpstorm_sessions[sid] = swd->sw_next;
		if (swd->sw_op == NULL)
			kfree(swd->sw_op);
		kfree(swd);
	}
	return 0;
}

/*
 * Process a software request.
 */
static int
crpstorm_process(void *arg, struct cryptop *crp, int hint)
{
	struct cryptodesc *crd;
	struct crpstorm_data *sw;
	u_int32_t lid;
	int type,i;
#define SCATTERLIST_MAX 16
	struct scatterlist sg[SCATTERLIST_MAX];
	int sg_num, sg_len, alen, skip;
	struct sk_buff *skb = NULL;
	struct uio *uiop = NULL;
	

	dprintk("        -->%s()\n", __FUNCTION__);
	/* Sanity check */
	if (crp == NULL) {
		dprintk("        -->%s,%d: EINVAL\n", __FILE__, __LINE__);
		return EINVAL;
	}

	crp->crp_etype = 0;

	if (crp->crp_desc == NULL || crp->crp_buf == NULL) {
		dprintk("        -->%s,%d: EINVAL\n", __FILE__, __LINE__);
		crp->crp_etype = EINVAL;
		goto done;
	}

	lid = crp->crp_sid & 0xffffffff;
	if (lid >= crpstorm_sesnum || lid == 0 || crpstorm_sessions == NULL ||
			crpstorm_sessions[lid] == NULL) {
		crp->crp_etype = ENOENT;
		dprintk("        -->%s,%d: ENOENT\n", __FILE__, __LINE__);
		goto done;
	}

	/*
	 * do some error checking outside of the loop for SKB and IOV processing
	 * this leaves us with valid skb or uiop pointers for later
	 */
	if (crp->crp_flags & CRYPTO_F_SKBUF) {
		skb = (struct sk_buff *) crp->crp_buf;
		if (skb_shinfo(skb)->nr_frags >= SCATTERLIST_MAX) {
			printk("%s,%d: %d nr_frags > SCATTERLIST_MAX", __FILE__, __LINE__,
					skb_shinfo(skb)->nr_frags);
			goto done;
		}
	} else if (crp->crp_flags & CRYPTO_F_IOV) {
		uiop = (struct uio *) crp->crp_buf;
		if (uiop->uio_iovcnt > SCATTERLIST_MAX) {
			printk("%s,%d: %d uio_iovcnt > SCATTERLIST_MAX", __FILE__, __LINE__,
					uiop->uio_iovcnt);
			goto done;
		}
	}

	/* Go through crypto descriptors, processing as we go */
	for (crd = crp->crp_desc; crd; crd = crd->crd_next) {
		/*
		 * Find the crypto context.
		 *
		 * XXX Note that the logic here prevents us from having
		 * XXX the same algorithm multiple times in a session
		 * XXX (or rather, we can but it won't give us the right
		 * XXX results). To do that, we'd need some way of differentiating
		 * XXX between the various instances of an algorithm (so we can
		 * XXX locate the correct crypto context).
		 */
		for (sw = crpstorm_sessions[lid]; sw && sw->sw_alg != crd->crd_alg;
				sw = sw->sw_next)
			;

		/* No such context ? */
		if (sw == NULL) {
			crp->crp_etype = EINVAL;
			dprintk("        -->%s,%d: EINVAL\n", __FILE__, __LINE__);
			goto done;
		}

		skip = crd->crd_skip;

		/*
		 * setup the SG list skip from the start of the buffer
		 */
		memset(sg, 0, sizeof(sg));
		if (crp->crp_flags & CRYPTO_F_SKBUF) {
			int i, len;

			type = CRYPTO_BUF_SKBUF;

			sg_num = 0;
			sg_len = 0;

			if (skip < skb_headlen(skb)) {
				sg[sg_num].page   = virt_to_page(skb->data + skip);
				sg[sg_num].offset = offset_in_page(skb->data + skip);
				len = skb_headlen(skb) - skip;
				if (len + sg_len > crd->crd_len)
					len = crd->crd_len - sg_len;
				sg[sg_num].length = len;
				sg_len += sg[sg_num].length;
				sg_num++;
				skip = 0;
			} else
				skip -= skb_headlen(skb);

			for (i = 0; sg_len < crd->crd_len &&
						i < skb_shinfo(skb)->nr_frags &&
						sg_num < SCATTERLIST_MAX; i++) {
				if (skip < skb_shinfo(skb)->frags[i].size) {
					sg[sg_num].page   = skb_shinfo(skb)->frags[i].page;
					sg[sg_num].offset = skb_shinfo(skb)->frags[i].page_offset +
							skip;
					len = skb_shinfo(skb)->frags[i].size - skip;
					if (len + sg_len > crd->crd_len)
						len = crd->crd_len - sg_len;
					sg[sg_num].length = len;
					sg_len += sg[sg_num].length;
					sg_num++;
					skip = 0;
				} else
					skip -= skb_shinfo(skb)->frags[i].size;
			}
		} else if (crp->crp_flags & CRYPTO_F_IOV) {
			int len;

			type = CRYPTO_BUF_IOV;

			sg_len = 0;
			for (sg_num = 0; sg_len < crd->crd_len &&
					sg_num < uiop->uio_iovcnt &&
					sg_num < SCATTERLIST_MAX; sg_num++) {
				if (skip < uiop->uio_iov[sg_num].iov_len) {
					sg[sg_num].page   =
							virt_to_page(uiop->uio_iov[sg_num].iov_base+skip);
					sg[sg_num].offset =
							offset_in_page(uiop->uio_iov[sg_num].iov_base+skip);
					len = uiop->uio_iov[sg_num].iov_len - skip;
					if (len + sg_len > crd->crd_len)
						len = crd->crd_len - sg_len;
					sg[sg_num].length = len;
					sg_len += sg[sg_num].length;
					skip = 0;
				} else 
					skip -= uiop->uio_iov[sg_num].iov_len;
			}
		} else {
			type = CRYPTO_BUF_CONTIG;
			sg[0].page   = virt_to_page(crp->crp_buf + skip);
			sg[0].offset = offset_in_page(crp->crp_buf + skip);
			sg_len = (crp->crp_ilen - skip);
			if (sg_len > crd->crd_len)
				sg_len = crd->crd_len;
			sg[0].length = sg_len;
			sg_num = 1;
		}


		//if (sg_len < crypto_tfm_alg_blocksize(sw->sw_op)) {
		//	crp->crp_etype = EINVAL;
		//	dprintk("        -->%s,%d: EINVAL len %d < %d\n", __FILE__, __LINE__,
		//			sg_len, crypto_tfm_alg_blocksize(sw->sw_op));
		//	goto done;
		//}

		switch (sw->sw_type) {
		case SW_TYPE_CIPHER: {
			unsigned char iv[64/*FIXME*/];
			unsigned char *ivp = iv;
			int ivsize = sw->sw_op->iv_size;//crypto_tfm_alg_ivsize(sw->sw_op);

			if (ivsize > sizeof(iv)) {
				crp->crp_etype = EINVAL;
				dprintk("        -->%s,%d: EINVAL\n", __FILE__, __LINE__);
				goto done;
			}

			if (crd->crd_flags & CRD_F_ENCRYPT) { /* encrypt */

				if (crd->crd_flags & CRD_F_IV_EXPLICIT) {
					ivp = crd->crd_iv;
				} else {
					get_random_bytes(ivp, ivsize);
				}
				/*
				 * do we have to copy the IV back to the buffer ?
				 */
				if ((crd->crd_flags & CRD_F_IV_PRESENT) == 0) {
					if (type == CRYPTO_BUF_CONTIG)
						memcpy(crp->crp_buf + crd->crd_inject, ivp, ivsize);
					else if (type == CRYPTO_BUF_SKBUF)
						skb_copy_bits_back(skb, crd->crd_inject, ivp, ivsize);
					else if (type == CRYPTO_BUF_IOV)
						cuio_copyback(uiop,crd->crd_inject,ivsize,(caddr_t)ivp);
				}
				
				memcpy(sw->sw_op->iv, crd->crd_iv, sw->sw_op->iv_size); 
 				sw->sw_op->op_mode = CIPHER_ENC;
				sw->sw_op->in_packet = sg;
  			sw->sw_op->pkt_len = sg_len; 
  			ppout = kmap(sg[0].page) + sg[0].offset;
  			sw->sw_op->out_packet = ppout;//&pout[0];//kmap(sg[0].page) + sg[0].offset;
  			sw->sw_op->cipher_header_len = 0;
  			sw->sw_op->cipher_algorithm_len = sg_len;
  			sw->sw_op->callback = NULL;
  			if (debug) {
						dprintk("        -->%s enc input(%d):\n", __FUNCTION__,sw->sw_op->pkt_len);
						for (i = 0; i < sw->sw_op->pkt_len; i++)
						{
							dprintk("[%02x]",*(ppout+i));
							if((i%8)==7)
							{
									dprintk("\n");
							}
						}
						dprintk("\n");
				}
  			ipsec_crypto_hw_process(sw->sw_op);
  			if (debug) {
						dprintk("        -->%s enc output(%d):\n", __FUNCTION__,sw->sw_op->out_pkt_len);
						for (i = 0; i < sw->sw_op->out_pkt_len; i++)
						{
							dprintk("[%02x]",*(sw->sw_op->out_packet+i));
							if((i%8)==7)
							{
									dprintk("\n");
							}
						}
						dprintk("\n");
				}
				//crypto_cipher_encrypt_iv(sw->sw_op, sg, sg, sg_len, ivp);
				//return tfm->crt_cipher.cit_encrypt_iv(tfm, dst, src, nbytes, iv);

			} else { /*decrypt */

				if (crd->crd_flags & CRD_F_IV_EXPLICIT) {
					ivp = crd->crd_iv;
				} else {
					if (type == CRYPTO_BUF_CONTIG)
						memcpy(ivp, crp->crp_buf + crd->crd_inject, ivsize);
					else if (type == CRYPTO_BUF_SKBUF)
						skb_copy_bits(skb, crd->crd_inject, ivp, ivsize);
					else if (type == CRYPTO_BUF_IOV)
						cuio_copydata(uiop,crd->crd_inject,ivsize,(caddr_t)ivp);
				}
				
				memcpy(sw->sw_op->iv, crd->crd_iv, sw->sw_op->iv_size); 
				sw->sw_op->op_mode = CIPHER_DEC;
				sw->sw_op->in_packet = sg;
  			sw->sw_op->pkt_len = sg_len; 
  			ppout = kmap(sg[0].page) + sg[0].offset;
  			sw->sw_op->out_packet = ppout;//&pout[0];//kmap(sg[0].page) + sg[0].offset;
  			sw->sw_op->cipher_header_len = 0;
  			sw->sw_op->cipher_algorithm_len = sg_len;
  			sw->sw_op->callback = NULL;
  			if (debug) {
						dprintk("        -->%s dec input(%d):\n", __FUNCTION__,sw->sw_op->pkt_len);
						for (i = 0; i < sw->sw_op->pkt_len; i++)
						{
							dprintk("[%02x]",*(ppout+i));
							if((i%8)==7)
							{
									dprintk("\n");
							}
						}
						dprintk("\n");
				}
  			ipsec_crypto_hw_process(sw->sw_op);
  			if (debug) {
						dprintk("        -->%s dec output(%d):\n", __FUNCTION__,sw->sw_op->out_pkt_len);
						for (i = 0; i < sw->sw_op->out_pkt_len; i++)
						{
							dprintk("[%02x]",*(sw->sw_op->out_packet+i));
							if((i%8)==7)
							{
									dprintk("\n");
							}
						}
						dprintk("\n");
				}
  			//crypto_cipher_decrypt_iv(sw->sw_op, sg, sg, sg_len, ivp);
				//return tfm->crt_cipher.cit_decrypt_iv(tfm, dst, src, nbytes, iv);
			}
			} break;
		case SW_TYPE_HMAC:
		case SW_TYPE_HASH: {
#if defined(CONFIG_CRYPTO_HMAC) || defined(CONFIG_CRYPTO_HMAC_MODULE)

			unsigned char result[AALG_MAX_RESULT_LEN];
			
			/*
			 * if the authlen is set,  use it,  otherwise use the
			 * digest size.
			 */
			
			if (sw->sw_authlen)
				alen = sw->sw_authlen;
			//else
			//	alen = crypto_tfm_alg_digestsize(sw->sw_op);
				
			//if (crp->crp_ilen - crd->crd_inject < alen) {
			//	dprintk("        -->crpstorm: EINVAL len=%d, inject=%d digestsize=%d\n",
			//			crd->crd_skip + sg_len, crd->crd_inject, alen);
			//	crp->crp_etype = EINVAL;
			//	goto done;
			//}
			memset(result, 0, sizeof(result));

				
				sw->sw_op->in_packet = sg;
  			sw->sw_op->pkt_len = sg_len; 
  			ppout = kmap(sg[0].page) + sg[0].offset;
  			sw->sw_op->out_packet = &pout;//&result; //&result[0]; 
  			sw->sw_op->auth_algorithm_len = sg_len; 
				sw->sw_op->auth_header_len = 0;
  			sw->sw_op->callback = NULL;
  			if (debug) {
						dprintk("        -->%s digest input(%d):\n", __FUNCTION__,sw->sw_op->pkt_len);
						for (i = 0; i < sw->sw_op->pkt_len; i++)
						{
							dprintk("[%02x]",*(ppout+i));
							if((i%8)==7)
							{
									dprintk("\n");
							}
						}
						dprintk("\n");
				}
				
  			ipsec_crypto_hw_process(sw->sw_op);
  			
  			if (debug) {
						dprintk("        -->%s digest output(%d):\n", __FUNCTION__,sw->sw_op->out_pkt_len);
						for (i = 0; i < sw->sw_op->out_pkt_len; i++)
						{
							dprintk("[%02x]",*(sw->sw_op->out_packet+i));
							if((i%8)==7)
							{
									dprintk("\n");
							}
						}
						dprintk("\n");
				}
				memcpy(sw->sw_op->out_packet, result, sw->sw_op->out_pkt_len - sw->sw_op->pkt_len);

			if (type == CRYPTO_BUF_CONTIG) {
				memcpy(crp->crp_buf + crd->crd_inject, result, alen);
			} else if (type == CRYPTO_BUF_IOV) {
				if (crp->crp_mac) {
					memcpy(crp->crp_mac, result, alen);
				} else {
					cuio_copyback(uiop, crd->crd_inject, alen, result);
				}
			} else if (type == CRYPTO_BUF_SKBUF) {
				skb_copy_bits_back(skb, crd->crd_inject, result, alen);
			} else
				printk("crpstorm: unknown buffer type 0x%x\n", type);
				
			memset(&pout, 0, sw->sw_op->out_pkt_len);
			}
#else
			crp->crp_etype = EINVAL;
			goto done;
#endif
			break;

		default:
			/* Unknown/unsupported algorithm */
			dprintk("        -->%s,%d: EINVAL\n", __FILE__, __LINE__);
			crp->crp_etype = EINVAL;
			goto done;
		}
	}

done:
	crypto_done(crp);
	return 0;
}

static int
crpstorm_init(void)
{
	dprintk("        -->%s(%p)\n", __FUNCTION__, crpstorm_init);
	crpstorm_id = crypto_get_driverid(0);
	if (crpstorm_id < 0)
		panic("Storm crypto device cannot initialize!");
	crypto_register(crpstorm_id, CRYPTO_DES_CBC,
	    0, 0, crpstorm_newsession, crpstorm_freesession, crpstorm_process, NULL);
	crypto_register(crpstorm_id, CRYPTO_DES_ECB,
	    0, 0, crpstorm_newsession, crpstorm_freesession, crpstorm_process, NULL);
	crypto_register(crpstorm_id, CRYPTO_3DES_CBC,
	    0, 0, crpstorm_newsession, crpstorm_freesession, crpstorm_process, NULL);
	crypto_register(crpstorm_id, CRYPTO_3DES_ECB,
	    0, 0, crpstorm_newsession, crpstorm_freesession, crpstorm_process, NULL);
	crypto_register(crpstorm_id, CRYPTO_AES_CBC,
	    0, 0, crpstorm_newsession, crpstorm_freesession, crpstorm_process, NULL);
	crypto_register(crpstorm_id, CRYPTO_AES_ECB,
	    0, 0, crpstorm_newsession, crpstorm_freesession, crpstorm_process, NULL);
	crypto_register(crpstorm_id, CRYPTO_AES192_CBC,
	    0, 0, crpstorm_newsession, crpstorm_freesession, crpstorm_process, NULL);
	crypto_register(crpstorm_id, CRYPTO_AES192_ECB,
	    0, 0, crpstorm_newsession, crpstorm_freesession, crpstorm_process, NULL);
	crypto_register(crpstorm_id, CRYPTO_AES256_CBC,
	    0, 0, crpstorm_newsession, crpstorm_freesession, crpstorm_process, NULL);
	crypto_register(crpstorm_id, CRYPTO_AES256_ECB,
	    0, 0, crpstorm_newsession, crpstorm_freesession, crpstorm_process, NULL);
	crypto_register(crpstorm_id, CRYPTO_MD5,
	    0, 0, crpstorm_newsession, crpstorm_freesession, crpstorm_process, NULL);
	crypto_register(crpstorm_id, CRYPTO_SHA1,
	    0, 0, crpstorm_newsession, crpstorm_freesession, crpstorm_process, NULL);
	crypto_register(crpstorm_id, CRYPTO_MD5_HMAC,
	    0, 0, crpstorm_newsession, crpstorm_freesession, crpstorm_process, NULL);
		crypto_register(crpstorm_id, CRYPTO_SHA1_HMAC,
	    0, 0, crpstorm_newsession, crpstorm_freesession, crpstorm_process, NULL);	    	    

	return(0);
}

static void
crpstorm_exit(void)
{
	dprintk("        -->%s()\n", __FUNCTION__);
	crypto_unregister_all(crpstorm_id);
	crpstorm_id = -1;
}

module_init(crpstorm_init);
module_exit(crpstorm_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("David McCullough <dmccullough@cyberguard.com>");
MODULE_DESCRIPTION("crpstorm (OCF module for kernel crypto)");
