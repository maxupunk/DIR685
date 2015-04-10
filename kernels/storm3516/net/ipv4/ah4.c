#include <linux/config.h>
#include <linux/module.h>
#include <net/ip.h>
#include <net/xfrm.h>
#include <net/ah.h>
#include <linux/crypto.h>
#include <linux/pfkeyv2.h>
#include <net/icmp.h>
#include <asm/scatterlist.h>

#ifdef CONFIG_SL2312_IPSEC
#include <linux/time.h>
extern unsigned long crypto_flags;
//extern unsigned long crypto_go;
extern  spinlock_t crypto_done_lock;
extern  unsigned int crypto_done ;
#endif

#ifdef CONFIG_SL351X_IPSEC
#include <asm/arch/sl351x_ipsec.h>
extern	struct IPSEC_VPN_TUNNEL_CONFIG	ipsec_tunnel[MAX_IPSEC_TUNNEL];
extern	void ipsec_vpn_tunnel_start(void);
extern	int	disable_vpn_hash(struct IPSEC_VPN_TUNNEL_CONFIG *tunnel_ptr);
#endif

/* Clear mutable options and find final destination to substitute
 * into IP header for icv calculation. Options are already checked
 * for validity, so paranoia is not required. */

static int ip_clear_mutable_options(struct iphdr *iph, u32 *daddr)
{
	unsigned char * optptr = (unsigned char*)(iph+1);
	int  l = iph->ihl*4 - sizeof(struct iphdr);
	int  optlen;

	while (l > 0) {
		switch (*optptr) {
		case IPOPT_END:
			return 0;
		case IPOPT_NOOP:
			l--;
			optptr++;
			continue;
		}
		optlen = optptr[1];
		if (optlen<2 || optlen>l)
			return -EINVAL;
		switch (*optptr) {
		case IPOPT_SEC:
		case 0x85:	/* Some "Extended Security" crap. */
		case 0x86:	/* Another "Commercial Security" crap. */
		case IPOPT_RA:
		case 0x80|21:	/* RFC1770 */
			break;
		case IPOPT_LSRR:
		case IPOPT_SSRR:
			if (optlen < 6)
				return -EINVAL;
			memcpy(daddr, optptr+optlen-4, 4);
			/* Fall through */
		default:
			memset(optptr+2, 0, optlen-2);
		}
		l -= optlen;
		optptr += optlen;
	}
	return 0;
}

static int ah_output(struct xfrm_state *x, struct sk_buff *skb)
{
	int err;
	struct iphdr *iph, *top_iph;
	struct ip_auth_hdr *ah;
	struct ah_data *ahp;
	union {
		struct iphdr	iph;
		char 		buf[60];
	} tmp_iph;

	top_iph = skb->nh.iph;
	iph = &tmp_iph.iph;

	iph->tos = top_iph->tos;
	iph->ttl = top_iph->ttl;
	iph->frag_off = top_iph->frag_off;

	if (top_iph->ihl != 5) {
		iph->daddr = top_iph->daddr;
		memcpy(iph+1, top_iph+1, top_iph->ihl*4 - sizeof(struct iphdr));
		err = ip_clear_mutable_options(top_iph, &top_iph->daddr);
		if (err)
			goto error;
	}

	ah = (struct ip_auth_hdr *)((char *)top_iph+top_iph->ihl*4);
	ah->nexthdr = top_iph->protocol;

	top_iph->tos = 0;
	top_iph->tot_len = htons(skb->len);
	top_iph->frag_off = 0;
	top_iph->ttl = 0;
	top_iph->protocol = IPPROTO_AH;
	top_iph->check = 0;

	ahp = x->data;
	ah->hdrlen  = (XFRM_ALIGN8(sizeof(struct ip_auth_hdr) + 
				   ahp->icv_trunc_len) >> 2) - 2;

	ah->reserved = 0;
	ah->spi = x->id.spi;
	ah->seq_no = htonl(++x->replay.oseq);
	ahp->icv(ahp, skb, ah->auth_data);
#ifdef CONFIG_SL2312_IPSEC			
//		crypto_go = 1;
#endif	
	top_iph->tos = iph->tos;
	top_iph->ttl = iph->ttl;
	top_iph->frag_off = iph->frag_off;
	if (top_iph->ihl != 5) {
		top_iph->daddr = iph->daddr;
		memcpy(top_iph+1, iph+1, top_iph->ihl*4 - sizeof(struct iphdr));
	}

	ip_send_check(top_iph);

	err = 0;

error:
	return err;
}

static int ah_input(struct xfrm_state *x, struct xfrm_decap_state *decap, struct sk_buff *skb)
{
	int ah_hlen;
	struct iphdr *iph;
	struct ip_auth_hdr *ah;
	struct ah_data *ahp;
	char work_buf[60];

	if (!pskb_may_pull(skb, sizeof(struct ip_auth_hdr)))
		goto out;

	ah = (struct ip_auth_hdr*)skb->data;
	ahp = x->data;
	ah_hlen = (ah->hdrlen + 2) << 2;
	
	if (ah_hlen != XFRM_ALIGN8(sizeof(struct ip_auth_hdr) + ahp->icv_full_len) &&
	    ah_hlen != XFRM_ALIGN8(sizeof(struct ip_auth_hdr) + ahp->icv_trunc_len)) 
		goto out;

	if (!pskb_may_pull(skb, ah_hlen))
		goto out;

	/* We are going to _remove_ AH header to keep sockets happy,
	 * so... Later this can change. */
	if (skb_cloned(skb) &&
	    pskb_expand_head(skb, 0, 0, GFP_ATOMIC))
		goto out;

	skb->ip_summed = CHECKSUM_NONE;

	ah = (struct ip_auth_hdr*)skb->data;
	iph = skb->nh.iph;

	memcpy(work_buf, iph, iph->ihl*4);

	iph->ttl = 0;
	iph->tos = 0;
	iph->frag_off = 0;
	iph->check = 0;
	if (iph->ihl != 5) {
		u32 dummy;
		if (ip_clear_mutable_options(iph, &dummy))
			goto out;
	}
        {
		u8 auth_data[MAX_AH_AUTH_LEN];
		
		memcpy(auth_data, ah->auth_data, ahp->icv_trunc_len);
		skb_push(skb, skb->data - skb->nh.raw);
#ifdef CONFIG_SL2312_IPSEC		
		//while (1) {
		//if (crypto_go){
		//	break;
		//}
		//schedule();
		//};
#endif
		//printk("1\n");
		ahp->icv(ahp, skb, ah->auth_data);
		//printk("2\n");
#ifdef CONFIG_SL2312_IPSEC			
//		crypto_go = 1;
#endif	
		if (memcmp(ah->auth_data, auth_data, ahp->icv_trunc_len)) {
			x->stats.integrity_failed++;
			goto out;
		}
	}
	((struct iphdr*)work_buf)->protocol = ah->nexthdr;
	skb->nh.raw = skb_pull(skb, ah_hlen);
	memcpy(skb->nh.raw, work_buf, iph->ihl*4);
	skb->nh.iph->tot_len = htons(skb->len);
	skb_pull(skb, skb->nh.iph->ihl*4);
	skb->h.raw = skb->data;

	return 0;

out:
	return -EINVAL;
}

static void ah4_err(struct sk_buff *skb, u32 info)
{
	struct iphdr *iph = (struct iphdr*)skb->data;
	struct ip_auth_hdr *ah = (struct ip_auth_hdr*)(skb->data+(iph->ihl<<2));
	struct xfrm_state *x;

	if (skb->h.icmph->type != ICMP_DEST_UNREACH ||
	    skb->h.icmph->code != ICMP_FRAG_NEEDED)
		return;

	x = xfrm_state_lookup((xfrm_address_t *)&iph->daddr, ah->spi, IPPROTO_AH, AF_INET);
	if (!x)
		return;
	printk(KERN_DEBUG "pmtu discovery on SA AH/%08x/%08x\n",
	       ntohl(ah->spi), ntohl(iph->daddr));
	xfrm_state_put(x);
}

static int ah_init_state(struct xfrm_state *x)
{
	struct ah_data *ahp = NULL;
	struct xfrm_algo_desc *aalg_desc;
#ifdef CONFIG_SL351X_IPSEC
	int	i=0, curr=-1;
	int sl351x_ipsec_able = 1;
#endif

	if (!x->aalg)
		goto error;

	/* null auth can use a zero length key */
	if (x->aalg->alg_key_len > 512)
		goto error;

	if (x->encap)
		goto error;

	ahp = kmalloc(sizeof(*ahp), GFP_KERNEL);
	if (ahp == NULL)
		return -ENOMEM;

	memset(ahp, 0, sizeof(*ahp));

	ahp->key = x->aalg->alg_key;
	ahp->key_len = (x->aalg->alg_key_len+7)/8;
	ahp->tfm = crypto_alloc_tfm(x->aalg->alg_name, 0);
	if (!ahp->tfm)
		goto error;
	ahp->icv = ah_hmac_digest;
	
	/*
	 * Lookup the algorithm description maintained by xfrm_algo,
	 * verify crypto transform properties, and store information
	 * we need for AH processing.  This lookup cannot fail here
	 * after a successful crypto_alloc_tfm().
	 */
	aalg_desc = xfrm_aalg_get_byname(x->aalg->alg_name, 0);
	BUG_ON(!aalg_desc);

	if (aalg_desc->uinfo.auth.icv_fullbits/8 !=
	    crypto_tfm_alg_digestsize(ahp->tfm)) {
		printk(KERN_INFO "AH: %s digestsize %u != %hu\n",
		       x->aalg->alg_name, crypto_tfm_alg_digestsize(ahp->tfm),
		       aalg_desc->uinfo.auth.icv_fullbits/8);
		goto error;
	}
	
	ahp->icv_full_len = aalg_desc->uinfo.auth.icv_fullbits/8;
	ahp->icv_trunc_len = aalg_desc->uinfo.auth.icv_truncbits/8;
	
	BUG_ON(ahp->icv_trunc_len > MAX_AH_AUTH_LEN);
	
	ahp->work_icv = kmalloc(ahp->icv_full_len, GFP_KERNEL);
	if (!ahp->work_icv)
		goto error;
	
	x->props.header_len = XFRM_ALIGN8(sizeof(struct ip_auth_hdr) + ahp->icv_trunc_len);
	if (x->props.mode)
		x->props.header_len += sizeof(struct iphdr);
	x->data = ahp;
#ifdef CONFIG_SL351X_IPSEC
	if (x->props.mode == 0)		// if transport mode, disable hardware acceleration
		sl351x_ipsec_able = 0;
	
	if (sl351x_ipsec_able)
	{
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
		printk("%s::spi:0x%02x%02x%02x%02x\n",__func__,(x->id.spi&0x000000ff),((x->id.spi&0x0000ff00)>>8),((x->id.spi&0x00ff0000)>>16),((x->id.spi&0xff000000)>>24));
		printk("%s::src:%x, dst:%x\n",__func__,(*(x)).props.saddr.a4,(*(x)).id.daddr.a4);
		ipsec_tunnel[curr].spi = x->id.spi;
		ipsec_tunnel[curr].protocol = x->id.proto;
		ipsec_tunnel[curr].src_WAN_IP = ntohl((*(x)).props.saddr.a4);
		ipsec_tunnel[curr].dst_WAN_IP = ntohl((*(x)).id.daddr.a4);
		ipsec_tunnel[curr].current_sequence = x->replay.oseq;

		// setting up AH's key and key length
		printk("%s:ahp->key(%x) -->key:",__func__,ahp->key_len);
		for(i=0;i<ahp->key_len;i++)
			printk("%02x",*(ahp->key+i));
		printk("\n");
		memcpy(&ipsec_tunnel[curr].auth_key, ahp->key, ahp->key_len);
		ipsec_tunnel[curr].auth_key_len = ahp->key_len;
		
		ipsec_tunnel[curr].auth_alg = ipsec_get_auth_algorithm(x->aalg->alg_name,1);
		printk("ahp->auth.tfm: %s, #: %x\n", x->aalg->alg_name,ipsec_tunnel[curr].auth_alg);
		ipsec_tunnel[curr].icv_full_len = ahp->icv_full_len;
		ipsec_tunnel[curr].icv_trunc_len = ahp->icv_trunc_len;

		printk("ipsec_tunnel ipsec_tunnel[%x]:\n",curr);
		printk("ipsec_tunnel :spi:0x%02x%02x%02x%02x\n",(ipsec_tunnel[curr].spi&0x000000ff),((ipsec_tunnel[curr].spi&0x0000ff00)>>8),((ipsec_tunnel[curr].spi&0x00ff0000)>>16),((ipsec_tunnel[curr].spi&0xff000000)>>24));		
		printk("ipsec_tunnel :src: %x  dst:%x\n",ipsec_tunnel[curr].src_WAN_IP,ipsec_tunnel[curr].dst_WAN_IP);
		printk("ipsec_tunnel :auth_key(%x) :",ipsec_tunnel[curr].auth_key_len);
		for(i=0;i<ipsec_tunnel[curr].auth_key_len;i++)
			printk("%02x",*(ipsec_tunnel[curr].auth_key+i));
		printk("\n");
		printk("ipsec_tunnel :auth_alg:%x\n",ipsec_tunnel[curr].auth_alg);
		printk("ipsec_tunnel :protocol:%x\n",ipsec_tunnel[curr].protocol);
		printk("ipsec_tunnel :sequence:%d\n",ipsec_tunnel[curr].current_sequence);
		ipsec_tunnel[curr].enable = 1;
		ipsec_tunnel[curr].xfrm = x;
		ipsec_vpn_tunnel_start();
	}

	struct timeval t;
	do_gettimeofday(&t);
	unsigned long day;
	unsigned int hour,minute,second;
	second = t.tv_sec%60;
	day = t.tv_sec/60;
	minute = day % 60;
	day = day/60;
	hour = day % 24;
	day = day/24;
	printk("time: day:%d  %02d:%02d:%02d\n",day,hour,minute,second);
#endif

	return 0;

error:
	if (ahp) {
		kfree(ahp->work_icv);
		crypto_free_tfm(ahp->tfm);
		kfree(ahp);
	}
	return -EINVAL;
}

static void ah_destroy(struct xfrm_state *x)
{
	struct ah_data *ahp = x->data;

	if (!ahp)
		return;
#ifdef CONFIG_SL351X_IPSEC
	int i=0,count=0;
	for (i=0;i<MAX_IPSEC_TUNNEL;i++)
	{
		if((ipsec_tunnel[i].src_WAN_IP==(ntohl((*(x)).props.saddr.a4)))
			&& (ipsec_tunnel[i].dst_WAN_IP==(ntohl((*(x)).id.daddr.a4)))
			&& (ipsec_tunnel[i].spi == x->id.spi))
		{
			printk("%s::disabling ipsec_tunnel[%d]\n",__func__,i);
			disable_vpn_hash(&ipsec_tunnel[i]);
			memset(&ipsec_tunnel[i],0x0,sizeof(struct IPSEC_VPN_TUNNEL_CONFIG));
			count++;
		}
	}
#endif

	kfree(ahp->work_icv);
	ahp->work_icv = NULL;
	crypto_free_tfm(ahp->tfm);
	ahp->tfm = NULL;
	kfree(ahp);
}


static struct xfrm_type ah_type =
{
	.description	= "AH4",
	.owner		= THIS_MODULE,
	.proto	     	= IPPROTO_AH,
	.init_state	= ah_init_state,
	.destructor	= ah_destroy,
	.input		= ah_input,
	.output		= ah_output
};

static struct net_protocol ah4_protocol = {
	.handler	=	xfrm4_rcv,
	.err_handler	=	ah4_err,
	.no_policy	=	1,
};

static int __init ah4_init(void)
{
	if (xfrm_register_type(&ah_type, AF_INET) < 0) {
		printk(KERN_INFO "ip ah init: can't add xfrm type\n");
		return -EAGAIN;
	}
	if (inet_add_protocol(&ah4_protocol, IPPROTO_AH) < 0) {
		printk(KERN_INFO "ip ah init: can't add protocol\n");
		xfrm_unregister_type(&ah_type, AF_INET);
		return -EAGAIN;
	}
	return 0;
}

static void __exit ah4_fini(void)
{
	if (inet_del_protocol(&ah4_protocol, IPPROTO_AH) < 0)
		printk(KERN_INFO "ip ah close: can't remove protocol\n");
	if (xfrm_unregister_type(&ah_type, AF_INET) < 0)
		printk(KERN_INFO "ip ah close: can't remove xfrm type\n");
}

module_init(ah4_init);
module_exit(ah4_fini);
MODULE_LICENSE("GPL");
