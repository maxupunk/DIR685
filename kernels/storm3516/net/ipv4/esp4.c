#include <linux/config.h>
#include <linux/module.h>
#include <net/ip.h>
#include <net/xfrm.h>
#include <net/esp.h>
#include <asm/scatterlist.h>
#include <linux/crypto.h>
#include <linux/kernel.h>
#include <linux/pfkeyv2.h>
#include <linux/random.h>
#include <net/icmp.h>
#include <net/udp.h>

#ifdef CONFIG_SL2312_IPSEC
extern unsigned long crypto_flags;
//extern unsigned long  crypto_go;
extern  spinlock_t crypto_done_lock;
extern  unsigned int crypto_done ;
extern int ipsec_get_cipher_algorithm(unsigned char *alg_name,unsigned int alg_mode);
extern int ipsec_get_auth_algorithm(unsigned char *alg_name,unsigned int alg_mode);
#endif

#ifdef CONFIG_SL351X_IPSEC
#include <asm/arch/sl351x_ipsec.h>
extern  struct IPSEC_VPN_TUNNEL_CONFIG ipsec_tunnel[MAX_IPSEC_TUNNEL];
extern	void ipsec_vpn_tunnel_start(void);
extern	int disable_vpn_hash(struct IPSEC_VPN_TUNNEL_CONFIG *tunnel_ptr);
#endif

/* decapsulation data for use when post-processing */
struct esp_decap_data {
	xfrm_address_t	saddr;
	__u16		sport;
	__u8		proto;
};

static int esp_output(struct xfrm_state *x, struct sk_buff *skb)
{
	int err;
	struct iphdr *top_iph;
	struct ip_esp_hdr *esph;
	struct crypto_tfm *tfm;
	struct esp_data *esp;
	struct sk_buff *trailer;
	int blksize;
	int clen;
	int alen;
	int nfrags;
	int ret;

	/* Strip IP+ESP header. */
	__skb_pull(skb, skb->h.raw - skb->data);
	/* Now skb is pure payload to encrypt */

	err = -ENOMEM;

	/* Round to block size */
	clen = skb->len;

	esp = x->data;
	alen = esp->auth.icv_trunc_len;
	tfm = esp->conf.tfm;
	blksize = ALIGN(crypto_tfm_alg_blocksize(tfm), 4);
	clen = ALIGN(clen + 2, blksize);
	if (esp->conf.padlen)
		clen = ALIGN(clen, esp->conf.padlen);

	if ((nfrags = skb_cow_data(skb, clen-skb->len+alen, &trailer)) < 0)
		goto error;

	/* Fill padding... */
	do {
		int i;
		for (i=0; i<clen-skb->len - 2; i++)
			*(u8*)(trailer->tail + i) = i+1;
	} while (0);
	*(u8*)(trailer->tail + clen-skb->len - 2) = (clen - skb->len)-2;
	pskb_put(skb, trailer, clen - skb->len);
	__skb_push(skb, skb->data - skb->nh.raw);
	top_iph = skb->nh.iph;
	esph = (struct ip_esp_hdr *)(skb->nh.raw + top_iph->ihl*4);
	top_iph->tot_len = htons(skb->len + alen);
	*(u8*)(trailer->tail - 1) = top_iph->protocol;

	/* this is non-NULL only with UDP Encapsulation */
	if (x->encap) {
		struct xfrm_encap_tmpl *encap = x->encap;
		struct udphdr *uh;
		u32 *udpdata32;

		uh = (struct udphdr *)esph;
		uh->source = encap->encap_sport;
		uh->dest = encap->encap_dport;
		uh->len = htons(skb->len + alen - top_iph->ihl*4);
		uh->check = 0;

		switch (encap->encap_type) {
		default:
		case UDP_ENCAP_ESPINUDP:
			esph = (struct ip_esp_hdr *)(uh + 1);
			break;
		case UDP_ENCAP_ESPINUDP_NON_IKE:
			udpdata32 = (u32 *)(uh + 1);
			udpdata32[0] = udpdata32[1] = 0;
			esph = (struct ip_esp_hdr *)(udpdata32 + 2);
			break;
		}

		top_iph->protocol = IPPROTO_UDP;
	} else
		top_iph->protocol = IPPROTO_ESP;

	esph->spi = x->id.spi;
//	printk("spi output:0x%02x%02x%02x%02x\n",(esph->spi&0x000000ff),((esph->spi&0x0000ff00)>>8),((esph->spi&0x00ff0000)>>16),((esph->spi&0xff000000)>>24));
	esph->seq_no = htonl(++x->replay.oseq);

	if (esp->conf.ivlen)
		crypto_cipher_set_iv(tfm, esp->conf.ivec, crypto_tfm_alg_ivsize(tfm));

	do {
		struct scatterlist *sg = &esp->sgbuf[0];
		//printk("%s :--> &esp->sgbuf[0]:0x%x \n",__func__,&esp->sgbuf[0]);
		if (unlikely(nfrags > ESP_NUM_FAST_SG)) {
			sg = kmalloc(sizeof(struct scatterlist)*nfrags, GFP_ATOMIC);
			if (!sg)
				goto error;
		}
		skb_to_sgvec(skb, sg, esph->enc_data+esp->conf.ivlen-skb->data, clen);

		//tfm->crt_u.cipher.key = esp->conf.key;
		//tfm->crt_u.cipher.keylen = esp->conf.key_len;
#ifdef CONFIG_SL2312_IPSEC		
		//while (1) {
		//if (crypto_go){
		//	break;
		//}
		//schedule();
		//};
		ret = -1;
//		printk("%s:(%x) -->key:",__func__,esp->conf.key_len);
//		int i;
//		for(i=0;i<esp->conf.key_len;i++)
//			printk("%02x",*(esp->conf.key+i));
//		printk("\n");
		crypto_cipher_setkey(esp->conf.tfm, esp->conf.key, esp->conf.key_len);
		//while (ret)
    {
    	//if(crypto_go == 1)
				ret = crypto_cipher_encrypt(tfm, sg, sg, clen);
			//if (ret)
			//	msleep(1);
		}
		
		if (unlikely(sg != &esp->sgbuf[0]))
		{
			//printk("sg:0x$x  &esp->sgbuf[0]:0x%x \n",sg,&esp->sgbuf[0]);
			kfree(sg);
		}	
	//	crypto_go = 1;
#else	
		//printk("33\n");
		crypto_cipher_setkey(esp->conf.tfm, esp->conf.key, esp->conf.key_len);
		crypto_cipher_encrypt(tfm, sg, sg, clen);
		if (unlikely(sg != &esp->sgbuf[0]))
		{
			//printk("%s :--> &esp->sgbuf[0]:0x%x   sg:0x%x\n",__func__,&esp->sgbuf[0],sg);
			kfree(sg);
		}
#endif			
	} while (0);
	//printk("44\n");

	if (esp->conf.ivlen) {
		memcpy(esph->enc_data, esp->conf.ivec, crypto_tfm_alg_ivsize(tfm));
		crypto_cipher_get_iv(tfm, esp->conf.ivec, crypto_tfm_alg_ivsize(tfm));
	}

	if (esp->auth.icv_full_len) {
#ifdef CONFIG_SL2312_IPSEC		
		//while (1) {
		//if (crypto_go){
		//	break;
		//}
		//schedule();
		//};
#endif		
		//printk("eocc\n");
		esp->auth.icv(esp, skb, (u8*)esph-skb->data,
		              sizeof(struct ip_esp_hdr) + esp->conf.ivlen+clen, trailer->tail);
		//printk("eodd\n");
	//	printk("%s::icv_full_len=%d,icv_trunc_len=%d\n",__func__,esp->auth.icv_full_len,esp->auth.icv_trunc_len);
#ifdef CONFIG_SL2312_IPSEC			
//		crypto_go = 1;
#endif	
		pskb_put(skb, trailer, alen);
	}

	ip_send_check(top_iph);

	err = 0;

error:
	return err;
}

/*
 * Note: detecting truncated vs. non-truncated authentication data is very
 * expensive, so we only support truncated data, which is the recommended
 * and common case.
 */
static int esp_input(struct xfrm_state *x, struct xfrm_decap_state *decap, struct sk_buff *skb)
{
	struct iphdr *iph;
	struct ip_esp_hdr *esph;
	struct esp_data *esp = x->data;
	struct sk_buff *trailer;
	int blksize = ALIGN(crypto_tfm_alg_blocksize(esp->conf.tfm), 4);
	int alen = esp->auth.icv_trunc_len;
	int elen = skb->len - sizeof(struct ip_esp_hdr) - esp->conf.ivlen - alen;
	int nfrags;
	int encap_len = 0;
	int ret;
	
//	printk("%s: -->\n",__func__);
	if (!pskb_may_pull(skb, sizeof(struct ip_esp_hdr)))
		goto out;

	if (elen <= 0 || (elen & (blksize-1)))
		goto out;

	/* If integrity check is required, do this. */
	if (esp->auth.icv_full_len) {
		u8 sum[esp->auth.icv_full_len];
		u8 sum1[alen];

#ifdef CONFIG_SL2312_IPSEC		
		//while (1) {
		//if (crypto_go){
		//	break;
		//}
		//schedule();
		//};

		//printk("eiaa\n");		
		esp->auth.icv(esp, skb, 0, skb->len-alen, sum);
		//printk("eibb\n");
			
//		crypto_go = 1;
#else
		esp->auth.icv(esp, skb, 0, skb->len-alen, sum);
#endif		
		if (skb_copy_bits(skb, skb->len-alen, sum1, alen))
			BUG();

		if (unlikely(memcmp(sum, sum1, alen))) {
			x->stats.integrity_failed++;
			goto out;
		}
	}

	if ((nfrags = skb_cow_data(skb, 0, &trailer)) < 0)
		goto out;

	skb->ip_summed = CHECKSUM_NONE;

	esph = (struct ip_esp_hdr*)skb->data;
	iph = skb->nh.iph;
//	printk("spi input:0x%02x%02x%02x%02x\n",(esph->spi&0x000000ff),((esph->spi&0x0000ff00)>>8),((esph->spi&0x00ff0000)>>16),((esph->spi&0xff000000)>>24));
	/* Get ivec. This can be wrong, check against another impls. */
	if (esp->conf.ivlen)
		crypto_cipher_set_iv(esp->conf.tfm, esph->enc_data, crypto_tfm_alg_ivsize(esp->conf.tfm));

        {
		u8 nexthdr[2];
		struct scatterlist *sg = &esp->sgbuf[0];
		u8 workbuf[60];
		int padlen;

		if (unlikely(nfrags > ESP_NUM_FAST_SG)) {
			sg = kmalloc(sizeof(struct scatterlist)*nfrags, GFP_ATOMIC);
			if (!sg)
				goto out;
		}
		skb_to_sgvec(skb, sg, sizeof(struct ip_esp_hdr) + esp->conf.ivlen, elen);
		
#ifdef CONFIG_SL2312_IPSEC
		//while (1) {
		//if (crypto_go){
		//	break;
		//}
		//schedule();
		//};		
		ret = -1;
//		printk("%s:(%x) -->key:",__func__,esp->conf.key_len);
//		int i;
//		for(i=0;i<esp->conf.key_len;i++)
//			printk("%02x",*(esp->conf.key+i));
//		printk("\n");
		crypto_cipher_setkey(esp->conf.tfm, esp->conf.key, esp->conf.key_len);

		
		//printk("11\n");
		//while (ret)
    {
    	//if(crypto_go == 1)
				ret = crypto_cipher_decrypt(esp->conf.tfm, sg, sg, elen);
			//if (ret)
			//	msleep(1);
		}
		if (unlikely(sg != &esp->sgbuf[0]))
			kfree(sg);
		//printk("22\n");

//		crypto_go = 1;
	
#else
		crypto_cipher_setkey(esp->conf.tfm, esp->conf.key, esp->conf.key_len);

		
		crypto_cipher_decrypt(esp->conf.tfm, sg, sg, elen);
		if (unlikely(sg != &esp->sgbuf[0]))
			kfree(sg);
#endif
		if (skb_copy_bits(skb, skb->len-alen-2, nexthdr, 2))
			BUG();

		padlen = nexthdr[0];
		if (padlen+2 >= elen)
			goto out;

		/* ... check padding bits here. Silly. :-) */ 

		if (x->encap && decap && decap->decap_type) {
			struct esp_decap_data *encap_data;
			struct udphdr *uh = (struct udphdr *) (iph+1);

			encap_data = (struct esp_decap_data *) (decap->decap_data);
			encap_data->proto = 0;

			switch (decap->decap_type) {
			case UDP_ENCAP_ESPINUDP:
			case UDP_ENCAP_ESPINUDP_NON_IKE:
				encap_data->proto = AF_INET;
				encap_data->saddr.a4 = iph->saddr;
				encap_data->sport = uh->source;
				encap_len = (void*)esph - (void*)uh;
				break;

			default:
				goto out;
			}
		}

		iph->protocol = nexthdr[1];
		pskb_trim(skb, skb->len - alen - padlen - 2);
		memcpy(workbuf, skb->nh.raw, iph->ihl*4);
		skb->h.raw = skb_pull(skb, sizeof(struct ip_esp_hdr) + esp->conf.ivlen);
		skb->nh.raw += encap_len + sizeof(struct ip_esp_hdr) + esp->conf.ivlen;
		memcpy(skb->nh.raw, workbuf, iph->ihl*4);
		skb->nh.iph->tot_len = htons(skb->len);
	}

	return 0;

out:
	return -EINVAL;
}

static int esp_post_input(struct xfrm_state *x, struct xfrm_decap_state *decap, struct sk_buff *skb)
{
	if (x->encap) {
		struct xfrm_encap_tmpl *encap;
		struct esp_decap_data *decap_data;

		encap = x->encap;
		decap_data = (struct esp_decap_data *)(decap->decap_data);

		/* first, make sure that the decap type == the encap type */
		if (encap->encap_type != decap->decap_type)
			return -EINVAL;

		switch (encap->encap_type) {
		default:
		case UDP_ENCAP_ESPINUDP:
		case UDP_ENCAP_ESPINUDP_NON_IKE:
			/*
			 * 1) if the NAT-T peer's IP or port changed then
			 *    advertize the change to the keying daemon.
			 *    This is an inbound SA, so just compare
			 *    SRC ports.
			 */
			if (decap_data->proto == AF_INET &&
			    (decap_data->saddr.a4 != x->props.saddr.a4 ||
			     decap_data->sport != encap->encap_sport)) {
				xfrm_address_t ipaddr;

				ipaddr.a4 = decap_data->saddr.a4;
				km_new_mapping(x, &ipaddr, decap_data->sport);
					
				/* XXX: perhaps add an extra
				 * policy check here, to see
				 * if we should allow or
				 * reject a packet from a
				 * different source
				 * address/port.
				 */
			}
		
			/*
			 * 2) ignore UDP/TCP checksums in case
			 *    of NAT-T in Transport Mode, or
			 *    perform other post-processing fixes
			 *    as per * draft-ietf-ipsec-udp-encaps-06,
			 *    section 3.1.2
			 */
			if (!x->props.mode)
				skb->ip_summed = CHECKSUM_UNNECESSARY;

			break;
		}
	}
	return 0;
}

static u32 esp4_get_max_size(struct xfrm_state *x, int mtu)
{
	struct esp_data *esp = x->data;
	u32 blksize = ALIGN(crypto_tfm_alg_blocksize(esp->conf.tfm), 4);

	if (x->props.mode) {
		mtu = ALIGN(mtu + 2, blksize);
	} else {
		/* The worst case. */
		mtu = ALIGN(mtu + 2, 4) + blksize - 4;
	}
	if (esp->conf.padlen)
		mtu = ALIGN(mtu, esp->conf.padlen);

	return mtu + x->props.header_len + esp->auth.icv_trunc_len;
}

static void esp4_err(struct sk_buff *skb, u32 info)
{
	struct iphdr *iph = (struct iphdr*)skb->data;
	struct ip_esp_hdr *esph = (struct ip_esp_hdr*)(skb->data+(iph->ihl<<2));
	struct xfrm_state *x;

	if (skb->h.icmph->type != ICMP_DEST_UNREACH ||
	    skb->h.icmph->code != ICMP_FRAG_NEEDED)
		return;
//	printk("%s: esph->spi:-->\n",__func__);
	x = xfrm_state_lookup((xfrm_address_t *)&iph->daddr, esph->spi, IPPROTO_ESP, AF_INET);
	if (!x)
		return;
	NETDEBUG(KERN_DEBUG "pmtu discovery on SA ESP/%08x/%08x\n",
		 ntohl(esph->spi), ntohl(iph->daddr));
	xfrm_state_put(x);
}

static void esp_destroy(struct xfrm_state *x)
{
	struct esp_data *esp = x->data;
	int i=0,count=0;
	if (!esp)
		return;
		
	printk("%s: -->\n",__func__);
		

#ifdef CONFIG_SL351X_IPSEC
	for(i=0;i<MAX_IPSEC_TUNNEL;i++)
	{
		if((ipsec_tunnel[i].src_WAN_IP==(ntohl((*(x)).props.saddr.a4)))
			&& (ipsec_tunnel[i].dst_WAN_IP==(ntohl((*(x)).id.daddr.a4)))
			&& (ipsec_tunnel[i].spi == x->id.spi))
		{
			printk("%s::disabling ipsec_tunnel[%d]\n",__func__,i);
			disable_vpn_hash(&ipsec_tunnel[i]);
			memset(&ipsec_tunnel[i],0x0,sizeof(struct IPSEC_VPN_TUNNEL_CONFIG));
			count++;
//			curr = i;
//			break;
		}	
	}
	printk("%s: remove %d item!\n",__func__,count);
//	if((curr==0)&&(i==MAX_IPSEC_TUNNEL))
//	{
//		printk("%s: item not found!!\n",__func__);
//	}
//	else
//	{
//		// stop the running hash.
//		disable_vpn_hash(&ipsec_tunnel[curr]);
//		memset(&ipsec_tunnel[curr],0x0,sizeof(struct IPSEC_VPN_TUNNEL_CONFIG));
//		printk("%s: remove %x item!\n",__func__,curr);
//	}
	
	printk("esp_destroy spi:0x%02x%02x%02x%02x\n",(x->id.spi&0x000000ff),((x->id.spi&0x0000ff00)>>8),((x->id.spi&0x00ff0000)>>16),((x->id.spi&0xff000000)>>24));
	printk("esp_destroy :src:%x, dst:%x\n",(*(x)).props.saddr.a4,(*(x)).id.daddr.a4);
#endif
	crypto_free_tfm(esp->conf.tfm);
	esp->conf.tfm = NULL;
	kfree(esp->conf.ivec);
	esp->conf.ivec = NULL;
	crypto_free_tfm(esp->auth.tfm);
	esp->auth.tfm = NULL;
	kfree(esp->auth.work_icv);
	esp->auth.work_icv = NULL;
	kfree(esp);
	printk("%s:<--\n",__func__);
}

static int esp_init_state(struct xfrm_state *x)
{
	struct esp_data *esp = NULL;
	int i=0,curr=-1;
	int sl351x_ipsec_able = 1;

//printk("%s: -->\n",__func__);
	/* null auth and encryption can have zero length keys */
	//iph->saddr;
#ifdef CONFIG_SL351X_IPSEC
	for(i=0;i<MAX_IPSEC_TUNNEL;i++)
	{
		if(((ipsec_tunnel[i].src_WAN_IP==(ntohl((*(x)).props.saddr.a4)))
			&& (ipsec_tunnel[i].dst_WAN_IP==(ntohl((*(x)).id.daddr.a4)))))
		{
			curr = i;		
			break;
		}		
	}
	if((curr==-1)&&(i==MAX_IPSEC_TUNNEL))
	{
		for(i=0;i<MAX_IPSEC_TUNNEL;i++)
		{
			if((ipsec_tunnel[i].src_WAN_IP==0)&&(ipsec_tunnel[i].dst_WAN_IP==0))
			{
				curr = i;	
				break;
			}	
		}
	}

	printk("esp_init_state spi:0x%02x%02x%02x%02x\n",(x->id.spi&0x000000ff),((x->id.spi&0x0000ff00)>>8),((x->id.spi&0x00ff0000)>>16),((x->id.spi&0xff000000)>>24));
	printk("esp_init_state:src:%x, dst:%x\n",(*(x)).props.saddr.a4,(*(x)).id.daddr.a4);
	if (sl351x_ipsec_able == 1) {

			ipsec_tunnel[curr].spi = x->id.spi;
			ipsec_tunnel[curr].protocol = x->id.proto;
			ipsec_tunnel[curr].src_WAN_IP = ntohl((*(x)).props.saddr.a4);
			ipsec_tunnel[curr].dst_WAN_IP = ntohl((*(x)).id.daddr.a4);
			ipsec_tunnel[curr].current_sequence = x->replay.oseq;	
	}
	else
		printk("%s::handle by software\n",__func__);
#endif	
		
	if (x->aalg) {
		if (x->aalg->alg_key_len > 512)
			goto error;
	}
	if (x->ealg == NULL)
		goto error;

	esp = kmalloc(sizeof(*esp), GFP_KERNEL);
	if (esp == NULL)
		return -ENOMEM;

	memset(esp, 0, sizeof(*esp));

	if (x->aalg) {
		struct xfrm_algo_desc *aalg_desc;

		esp->auth.key = x->aalg->alg_key;
		esp->auth.key_len = (x->aalg->alg_key_len+7)/8;
#ifdef CONFIG_SL351X_IPSEC		
		printk("%s:esp->auth.key(%x) -->key:",__func__,esp->auth.key_len);
		for(i=0;i<esp->auth.key_len;i++)
			printk("%02x",*(esp->auth.key+i));
		printk("\n");
		
		if (sl351x_ipsec_able == 1) {
			memcpy(&ipsec_tunnel[curr].auth_key, esp->auth.key, esp->auth.key_len);
			ipsec_tunnel[curr].auth_key_len = esp->auth.key_len;
		}
#endif		
		esp->auth.tfm = crypto_alloc_tfm(x->aalg->alg_name, 0);
#ifdef CONFIG_SL351X_IPSEC		
		if (sl351x_ipsec_able == 1)
			ipsec_tunnel[curr].auth_alg = ipsec_get_auth_algorithm(x->aalg->alg_name,1);
		printk("esp->auth.tfm: %s, #: %x\n", x->aalg->alg_name,ipsec_tunnel[curr].auth_alg);
#endif		
		if (esp->auth.tfm == NULL)
			goto error;
		esp->auth.icv = esp_hmac_digest;

		aalg_desc = xfrm_aalg_get_byname(x->aalg->alg_name, 0);
		BUG_ON(!aalg_desc);

		if (aalg_desc->uinfo.auth.icv_fullbits/8 !=
		    crypto_tfm_alg_digestsize(esp->auth.tfm)) {
			NETDEBUG(KERN_INFO "ESP: %s digestsize %u != %hu\n",
				 x->aalg->alg_name,
				 crypto_tfm_alg_digestsize(esp->auth.tfm),
				 aalg_desc->uinfo.auth.icv_fullbits/8);
			goto error;
		}

		esp->auth.icv_full_len = aalg_desc->uinfo.auth.icv_fullbits/8;
		esp->auth.icv_trunc_len = aalg_desc->uinfo.auth.icv_truncbits/8;

		esp->auth.work_icv = kmalloc(esp->auth.icv_full_len, GFP_KERNEL);
		if (!esp->auth.work_icv)
			goto error;
	}
	esp->conf.key = x->ealg->alg_key;
	esp->conf.key_len = (x->ealg->alg_key_len+7)/8;
#ifdef CONFIG_SL351X_IPSEC
	if (sl351x_ipsec_able == 1) {
		ipsec_tunnel[curr].icv_full_len = esp->auth.icv_full_len;
		ipsec_tunnel[curr].icv_trunc_len = esp->auth.icv_trunc_len;
	}
	printk("%s:esp->conf.key(%x) -->key:",__func__,esp->conf.key_len);
	
	for(i=0;i<esp->conf.key_len;i++)
		printk("%02x",*(esp->conf.key+i));
	printk("\n");
	
	if (sl351x_ipsec_able == 1) {
		memcpy(&ipsec_tunnel[curr].enc_key, esp->conf.key, esp->conf.key_len);
		ipsec_tunnel[curr].enc_key_len = esp->conf.key_len;
	}
#endif		
	if (x->props.ealgo == SADB_EALG_NULL)
	{
		esp->conf.tfm = crypto_alloc_tfm(x->ealg->alg_name, CRYPTO_TFM_MODE_ECB);
#ifdef CONFIG_SL351X_IPSEC		
		printk("esp->conf.tfm(ECB): %s\n", x->ealg->alg_name);
		if (sl351x_ipsec_able == 1)
			ipsec_tunnel[curr].cipher_alg = ipsec_get_cipher_algorithm(x->ealg->alg_name,0);
#endif		
	}
	else
	{
		esp->conf.tfm = crypto_alloc_tfm(x->ealg->alg_name, CRYPTO_TFM_MODE_CBC);
#ifdef CONFIG_SL351X_IPSEC		
		printk("esp->conf.tfm(CBC): %s\n", x->ealg->alg_name);
		if (sl351x_ipsec_able == 1)
			ipsec_tunnel[curr].cipher_alg = ipsec_get_cipher_algorithm(x->ealg->alg_name,1);
#endif		
	}
	if (esp->conf.tfm == NULL)
		goto error;
	esp->conf.ivlen = crypto_tfm_alg_ivsize(esp->conf.tfm);
	esp->conf.padlen = 0;
	if (esp->conf.ivlen) {
		esp->conf.ivec = kmalloc(esp->conf.ivlen, GFP_KERNEL);
		if (unlikely(esp->conf.ivec == NULL))
			goto error;
		get_random_bytes(esp->conf.ivec, esp->conf.ivlen);
	}
#ifdef CONFIG_SL351X_IPSEC		
	printk("%s:esp->conf.ivec(%x) -->key:",__func__,esp->conf.ivlen);
	for(i=0;i<esp->conf.ivlen;i++)
		printk("%02x",*(esp->conf.ivec+i));
	printk("\n");

	if (sl351x_ipsec_able == 1) {
		memcpy(&ipsec_tunnel[curr].enc_iv, esp->conf.ivec, esp->conf.ivlen);
		ipsec_tunnel[curr].enc_iv_len = esp->conf.ivlen;
	}
#endif		
	if (crypto_cipher_setkey(esp->conf.tfm, esp->conf.key, esp->conf.key_len))
		goto error;
	x->props.header_len = sizeof(struct ip_esp_hdr) + esp->conf.ivlen;
	if (x->props.mode)
		x->props.header_len += sizeof(struct iphdr);
	if (x->encap) {
		struct xfrm_encap_tmpl *encap = x->encap;

		switch (encap->encap_type) {
		default:
			goto error;
		case UDP_ENCAP_ESPINUDP:
			x->props.header_len += sizeof(struct udphdr);
			break;
		case UDP_ENCAP_ESPINUDP_NON_IKE:
			x->props.header_len += sizeof(struct udphdr) + 2 * sizeof(u32);
			break;
		}
	}
#ifdef CONFIG_SL351X_IPSEC
	// new checks.. to filter out IPSEC-VPN type that we can't support

	if ((x->encap) && ((x->encap->encap_type == UDP_ENCAP_ESPINUDP) || 
		(x->encap->encap_type == UDP_ENCAP_ESPINUDP_NON_IKE)))
	{
		sl351x_ipsec_able = 0;
	}

	if (x->props.mode == 0)	// if transport mode, disable hardware acceleration
	{
		sl351x_ipsec_able = 0;
	}
	// if need more check, just add below

	if (sl351x_ipsec_able == 1) {
			printk("ipsec_tunnel ipsec_tunnel[%x]:\n",curr);
			printk("ipsec_tunnel :spi:0x%02x%02x%02x%02x\n",(ipsec_tunnel[curr].spi&0x000000ff),((ipsec_tunnel[curr].spi&0x0000ff00)>>8),((ipsec_tunnel[curr].spi&0x00ff0000)>>16),((ipsec_tunnel[curr].spi&0xff000000)>>24));		
			printk("ipsec_tunnel :src: %x  dst:%x\n",ipsec_tunnel[curr].src_WAN_IP,ipsec_tunnel[curr].dst_WAN_IP);
			printk("ipsec_tunnel :auth_key(%x) :",ipsec_tunnel[curr].auth_key_len);
			for(i=0;i<ipsec_tunnel[curr].auth_key_len;i++)
				printk("%02x",*(ipsec_tunnel[curr].auth_key+i));
			printk("\n");
			printk("ipsec_tunnel :enc_key(%x) :",ipsec_tunnel[curr].enc_key_len);
			for(i=0;i<ipsec_tunnel[curr].enc_key_len;i++)
				printk("%02x",*(ipsec_tunnel[curr].enc_key+i));
			printk("\n");
			printk("ipsec_tunnel :enc_iv(%x) :",ipsec_tunnel[curr].enc_iv_len);
			for(i=0;i<ipsec_tunnel[curr].enc_iv_len;i++)
				printk("%02x",*(ipsec_tunnel[curr].enc_iv+i));
			printk("\n");
			printk("ipsec_tunnel :cipher_alg:%x\n",ipsec_tunnel[curr].cipher_alg);
			printk("ipsec_tunnel :auth_alg:%x\n",ipsec_tunnel[curr].auth_alg);
			printk("ipsec_tunnel :protocol:%x\n",ipsec_tunnel[curr].protocol);
			printk("ipsec_tunnel :sequence:%d\n",ipsec_tunnel[curr].current_sequence);
			ipsec_tunnel[curr].enable = 1;
			ipsec_tunnel[curr].xfrm = x;
			ipsec_vpn_tunnel_start();
	}
	if (sl351x_ipsec_able == 0) {
		// clean all the values that's been stored in ipsec_tunnel[curr]
		memset(&ipsec_tunnel[curr],0x0,sizeof(struct IPSEC_VPN_TUNNEL_CONFIG));
	}
#endif	

	x->data = esp;
	x->props.trailer_len = esp4_get_max_size(x, 0) - x->props.header_len;
	
	return 0;

error:

	x->data = esp;
	esp_destroy(x);
	x->data = NULL;
	return -EINVAL;
}

static struct xfrm_type esp_type =
{
	.description	= "ESP4",
	.owner		= THIS_MODULE,
	.proto	     	= IPPROTO_ESP,
	.init_state	= esp_init_state,
	.destructor	= esp_destroy,
	.get_max_size	= esp4_get_max_size,
	.input		= esp_input,
	.post_input	= esp_post_input,
	.output		= esp_output
};

static struct net_protocol esp4_protocol = {
	.handler	=	xfrm4_rcv,
	.err_handler	=	esp4_err,
	.no_policy	=	1,
};

static int __init esp4_init(void)
{
	struct xfrm_decap_state decap;

	if (sizeof(struct esp_decap_data)  >
	    sizeof(decap.decap_data)) {
		extern void decap_data_too_small(void);

		decap_data_too_small();
	}

	if (xfrm_register_type(&esp_type, AF_INET) < 0) {
		printk(KERN_INFO "ip esp init: can't add xfrm type\n");
		return -EAGAIN;
	}
	if (inet_add_protocol(&esp4_protocol, IPPROTO_ESP) < 0) {
		printk(KERN_INFO "ip esp init: can't add protocol\n");
		xfrm_unregister_type(&esp_type, AF_INET);
		return -EAGAIN;
	}

	return 0;
}

static void __exit esp4_fini(void)
{
	if (inet_del_protocol(&esp4_protocol, IPPROTO_ESP) < 0)
		printk(KERN_INFO "ip esp close: can't remove protocol\n");
	if (xfrm_unregister_type(&esp_type, AF_INET) < 0)
		printk(KERN_INFO "ip esp close: can't remove xfrm type\n");
}

module_init(esp4_init);
module_exit(esp4_fini);
MODULE_LICENSE("GPL");
