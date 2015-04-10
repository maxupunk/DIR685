/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2004 Netfilter Core Team <coreteam@netfilter.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

/* Everything about the rules for NAT. */
#include <linux/types.h>
#include <linux/ip.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/module.h>
#include <linux/kmod.h>
#include <linux/skbuff.h>
#include <linux/proc_fs.h>
#include <net/checksum.h>
#include <net/route.h>
#include <linux/bitops.h>

#define ASSERT_READ_LOCK(x)
#define ASSERT_WRITE_LOCK(x)

#include <linux/netfilter_ipv4/ip_tables.h>
#include <linux/netfilter_ipv4/ip_nat.h>
#include <linux/netfilter_ipv4/ip_nat_core.h>
#include <linux/netfilter_ipv4/ip_nat_rule.h>
#include <linux/netfilter_ipv4/listhelp.h>

#if defined (ALPHA_RESTRICTED_CONE) || defined (ALPHA_FULL_CONE)//marco	
#include <linux/tcp.h>
extern unsigned long ip_ct_tcp_timeout_syn_sent ;
extern unsigned long ip_ct_tcp_timeout_syn_recv ;
extern unsigned long ip_ct_tcp_timeout_established ;
extern unsigned long ip_ct_tcp_timeout_fin_wait ;
extern unsigned long ip_ct_tcp_timeout_close_wait ;
extern unsigned long ip_ct_tcp_timeout_last_ack ;
extern unsigned long ip_ct_tcp_timeout_time_wait ;
extern unsigned long ip_ct_tcp_timeout_close ;
extern unsigned long ip_ct_tcp_timeout_max_retrans ; 
extern const unsigned long * tcp_timeouts[];
extern struct ip_conntrack *find_appropriate_conntrack(const struct ip_conntrack_tuple *tuple);
extern enum tcp_conntrack tcp_conntracks[2][5][TCP_CONNTRACK_MAX];	
extern unsigned int get_conntrack_index(const struct tcphdr *tcph);
#define UDP_TIMEOUT (90*HZ)
#define UDP_STREAM_TIMEOUT (180*HZ)
#endif
#if 0
#define DEBUGP printk
#else
#define DEBUGP(format, args...)
#endif

#define NAT_VALID_HOOKS ((1<<NF_IP_PRE_ROUTING) | (1<<NF_IP_POST_ROUTING) | (1<<NF_IP_LOCAL_OUT))

static struct
{
	struct ipt_replace repl;
	struct ipt_standard entries[3];
	struct ipt_error term;
} nat_initial_table __initdata
= { { "nat", NAT_VALID_HOOKS, 4,
      sizeof(struct ipt_standard) * 3 + sizeof(struct ipt_error),
      { [NF_IP_PRE_ROUTING] = 0,
	[NF_IP_POST_ROUTING] = sizeof(struct ipt_standard),
	[NF_IP_LOCAL_OUT] = sizeof(struct ipt_standard) * 2 },
      { [NF_IP_PRE_ROUTING] = 0,
	[NF_IP_POST_ROUTING] = sizeof(struct ipt_standard),
	[NF_IP_LOCAL_OUT] = sizeof(struct ipt_standard) * 2 },
      0, NULL, { } },
    {
	    /* PRE_ROUTING */
	    { { { { 0 }, { 0 }, { 0 }, { 0 }, "", "", { 0 }, { 0 }, 0, 0, 0 },
		0,
		sizeof(struct ipt_entry),
		sizeof(struct ipt_standard),
		0, { 0, 0 }, { } },
	      { { { { IPT_ALIGN(sizeof(struct ipt_standard_target)), "" } }, { } },
		-NF_ACCEPT - 1 } },
	    /* POST_ROUTING */
	    { { { { 0 }, { 0 }, { 0 }, { 0 }, "", "", { 0 }, { 0 }, 0, 0, 0 },
		0,
		sizeof(struct ipt_entry),
		sizeof(struct ipt_standard),
		0, { 0, 0 }, { } },
	      { { { { IPT_ALIGN(sizeof(struct ipt_standard_target)), "" } }, { } },
		-NF_ACCEPT - 1 } },
	    /* LOCAL_OUT */
	    { { { { 0 }, { 0 }, { 0 }, { 0 }, "", "", { 0 }, { 0 }, 0, 0, 0 },
		0,
		sizeof(struct ipt_entry),
		sizeof(struct ipt_standard),
		0, { 0, 0 }, { } },
	      { { { { IPT_ALIGN(sizeof(struct ipt_standard_target)), "" } }, { } },
		-NF_ACCEPT - 1 } }
    },
    /* ERROR */
    { { { { 0 }, { 0 }, { 0 }, { 0 }, "", "", { 0 }, { 0 }, 0, 0, 0 },
	0,
	sizeof(struct ipt_entry),
	sizeof(struct ipt_error),
	0, { 0, 0 }, { } },
      { { { { IPT_ALIGN(sizeof(struct ipt_error_target)), IPT_ERROR_TARGET } },
	  { } },
	"ERROR"
      }
    }
};

static struct ipt_table nat_table = {
	.name		= "nat",
	.valid_hooks	= NAT_VALID_HOOKS,
	.lock		= RW_LOCK_UNLOCKED,
	.me		= THIS_MODULE,
};

/* Source NAT */
static unsigned int ipt_snat_target(struct sk_buff **pskb,
				    const struct net_device *in,
				    const struct net_device *out,
				    unsigned int hooknum,
				    const void *targinfo,
				    void *userinfo)
{
	struct ip_conntrack *ct;
	enum ip_conntrack_info ctinfo;
	const struct ip_nat_multi_range_compat *mr = targinfo;

	IP_NF_ASSERT(hooknum == NF_IP_POST_ROUTING);

	ct = ip_conntrack_get(*pskb, &ctinfo);

	/* Connection must be valid and new. */
	IP_NF_ASSERT(ct && (ctinfo == IP_CT_NEW || ctinfo == IP_CT_RELATED
	                    || ctinfo == IP_CT_RELATED + IP_CT_IS_REPLY));
	IP_NF_ASSERT(out);

	return ip_nat_setup_info(ct, &mr->range[0], hooknum);
}

/* Before 2.6.11 we did implicit source NAT if required. Warn about change. */
static void warn_if_extra_mangle(u32 dstip, u32 srcip)
{
	static int warned = 0;
	struct flowi fl = { .nl_u = { .ip4_u = { .daddr = dstip } } };
	struct rtable *rt;

	if (ip_route_output_key(&rt, &fl) != 0)
		return;

	if (rt->rt_src != srcip && !warned) {
		printk("NAT: no longer support implicit source local NAT\n");
		printk("NAT: packet src %u.%u.%u.%u -> dst %u.%u.%u.%u\n",
		       NIPQUAD(srcip), NIPQUAD(dstip));
		warned = 1;
	}
	ip_rt_put(rt);
}

static unsigned int ipt_dnat_target(struct sk_buff **pskb,
				    const struct net_device *in,
				    const struct net_device *out,
				    unsigned int hooknum,
				    const void *targinfo,
				    void *userinfo)
{
	struct ip_conntrack *ct;
#if defined (ALPHA_RESTRICTED_CONE) || defined (ALPHA_FULL_CONE)//marco	
	struct ip_conntrack *found_ct=NULL;
	struct ip_nat_range mod_range[2];//marco, the mr->range[0] is const, so we create another one to mod. its content
	struct ip_conntrack_tuple curr_tuple;//marco
	unsigned int index;//for tcp conntrack timeout refresh
	enum ip_conntrack_dir dir;//for tcp conntrack timeout refresh
	enum tcp_conntrack new_state, old_state;	//for tcp conntrack timeout refresh
#endif
	enum ip_conntrack_info ctinfo;
	const struct ip_nat_multi_range_compat *mr = targinfo;
	
	IP_NF_ASSERT(hooknum == NF_IP_PRE_ROUTING
		     || hooknum == NF_IP_LOCAL_OUT);

	ct = ip_conntrack_get(*pskb, &ctinfo);

	/* Connection must be valid and new. */
	IP_NF_ASSERT(ct && (ctinfo == IP_CT_NEW || ctinfo == IP_CT_RELATED));

	if (hooknum == NF_IP_LOCAL_OUT
	    && mr->range[0].flags & IP_NAT_RANGE_MAP_IPS)
		warn_if_extra_mangle((*pskb)->nh.iph->daddr,
				     mr->range[0].min_ip);

#if defined (ALPHA_RESTRICTED_CONE) || defined (ALPHA_FULL_CONE)//marco	
		
	memcpy(&mod_range,&mr->range[0],sizeof(struct ip_nat_range)*2 );			     
 	//if the range ip is 0,we start restricted nat
	if(mr->range[0].min_ip==0 || mr->range[0].max_ip==0)
	{
		invert_tuplepr(&curr_tuple,&ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple);
		
		found_ct=find_appropriate_conntrack( (struct ip_conntrack_tuple*)&curr_tuple);
		if( found_ct)//find out conntrack, and replace the range ip and port	 
		{
			mod_range[0].min_ip=found_ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.ip;
			mod_range[0].max_ip=found_ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.ip;		
			mod_range[0].min=found_ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u;
			mod_range[0].max=found_ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u;
			atomic_inc(&ct->ct_general.use);
			
			if(ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum==IPPROTO_UDP)//udp
			{
				if (ct->status & IPS_SEEN_REPLY) 
				{
					 ip_ct_refresh_acct(ct, ctinfo,*pskb,UDP_STREAM_TIMEOUT);
					set_bit(IPS_ASSURED_BIT, &ct->status); 
				}
				else
					 ip_ct_refresh_acct(ct, ctinfo,*pskb,UDP_TIMEOUT); 				
			}
			else if(ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum==IPPROTO_TCP)//tcp
			{
				struct sk_buff * tmp_buf=*pskb;		
				int timeout=0;		
				extern int ip_ct_tcp_max_retrans ;				
				struct tcphdr *th, _tcph;
				struct iphdr *iph = tmp_buf->nh.iph;
				th = skb_header_pointer(*pskb, iph->ihl * 4,sizeof(_tcph), &_tcph);				
				old_state = ct->proto.tcp.state;
				dir = CTINFO2DIR(ctinfo);
				index = get_conntrack_index(th);
				new_state = tcp_conntracks[dir][index][old_state];	
				
				timeout = ct->proto.tcp.retrans >= ip_ct_tcp_max_retrans
		  && *tcp_timeouts[new_state] > ip_ct_tcp_timeout_max_retrans
		  ? ip_ct_tcp_timeout_max_retrans : *tcp_timeouts[new_state];

				 ip_ct_refresh_acct(ct, ctinfo,*pskb,timeout);			
			}
		}
		else
			return IPT_CONTINUE;	
	}
		//full cone will start if iptables have range ip 255.255.255.255
	else if(mr->range[0].min_ip==0xffffffff || mr->range[0].max_ip==0xffffffff)
	{
		invert_tuplepr(&curr_tuple,&ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple);
		
		found_ct=find_appropriate_conntrack_for_fullcone( (struct ip_conntrack_tuple*)&curr_tuple);
		if( found_ct)//find out conntrack, and replace the range ip and port	 
		{
			mod_range[0].min_ip=found_ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.ip;
			mod_range[0].max_ip=found_ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.ip;		
			mod_range[0].min=found_ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u;
			mod_range[0].max=found_ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u;
			atomic_inc(&ct->ct_general.use);			
			if(ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum==IPPROTO_UDP)//udp
			{
				if (ct->status & IPS_SEEN_REPLY) 
				{
					ip_ct_refresh_acct(ct, ctinfo,*pskb,UDP_STREAM_TIMEOUT);
					set_bit(IPS_ASSURED_BIT, &ct->status); 
				}
				else
					 ip_ct_refresh_acct(ct, ctinfo,*pskb,UDP_TIMEOUT); 				
			}
			else if(ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum==IPPROTO_TCP)//tcp
			{
				struct sk_buff * tmp_buf=*pskb;	
				int timeout=0;		
				extern int ip_ct_tcp_max_retrans ;				
				struct tcphdr *th, _tcph;
				struct iphdr *iph = tmp_buf->nh.iph;
				th = skb_header_pointer(*pskb, iph->ihl * 4,sizeof(_tcph), &_tcph);				
				old_state = ct->proto.tcp.state;
				dir = CTINFO2DIR(ctinfo);
				index = get_conntrack_index(th);
				new_state = tcp_conntracks[dir][index][old_state];																
				timeout = ct->proto.tcp.retrans >= ip_ct_tcp_max_retrans
		  && *tcp_timeouts[new_state] > ip_ct_tcp_timeout_max_retrans
		  ? ip_ct_tcp_timeout_max_retrans : *tcp_timeouts[new_state];

				 ip_ct_refresh_acct(ct, ctinfo,*pskb,timeout);						 
			}       
		}
		else
			return IPT_CONTINUE;	
	}
 	return ip_nat_setup_info(ct, &mod_range[0], hooknum);
#else 	
	return ip_nat_setup_info(ct, &mr->range[0], hooknum);
#endif	
}

static int ipt_snat_checkentry(const char *tablename,
			       const struct ipt_entry *e,
			       void *targinfo,
			       unsigned int targinfosize,
			       unsigned int hook_mask)
{
	struct ip_nat_multi_range_compat *mr = targinfo;

	/* Must be a valid range */
	if (mr->rangesize != 1) {
		printk("SNAT: multiple ranges no longer supported\n");
		return 0;
	}

	if (targinfosize != IPT_ALIGN(sizeof(struct ip_nat_multi_range_compat))) {
		DEBUGP("SNAT: Target size %u wrong for %u ranges\n",
		       targinfosize, mr->rangesize);
		return 0;
	}

	/* Only allow these for NAT. */
	if (strcmp(tablename, "nat") != 0) {
		DEBUGP("SNAT: wrong table %s\n", tablename);
		return 0;
	}

	if (hook_mask & ~(1 << NF_IP_POST_ROUTING)) {
		DEBUGP("SNAT: hook mask 0x%x bad\n", hook_mask);
		return 0;
	}
	return 1;
}

static int ipt_dnat_checkentry(const char *tablename,
			       const struct ipt_entry *e,
			       void *targinfo,
			       unsigned int targinfosize,
			       unsigned int hook_mask)
{
	struct ip_nat_multi_range_compat *mr = targinfo;

	/* Must be a valid range */
	if (mr->rangesize != 1) {
		printk("DNAT: multiple ranges no longer supported\n");
		return 0;
	}

	if (targinfosize != IPT_ALIGN(sizeof(struct ip_nat_multi_range_compat))) {
		DEBUGP("DNAT: Target size %u wrong for %u ranges\n",
		       targinfosize, mr->rangesize);
		return 0;
	}

	/* Only allow these for NAT. */
	if (strcmp(tablename, "nat") != 0) {
		DEBUGP("DNAT: wrong table %s\n", tablename);
		return 0;
	}

	if (hook_mask & ~((1 << NF_IP_PRE_ROUTING) | (1 << NF_IP_LOCAL_OUT))) {
		DEBUGP("DNAT: hook mask 0x%x bad\n", hook_mask);
		return 0;
	}
	
	return 1;
}

inline unsigned int
alloc_null_binding(struct ip_conntrack *conntrack,
		   struct ip_nat_info *info,
		   unsigned int hooknum)
{
	/* Force range to this IP; let proto decide mapping for
	   per-proto parts (hence not IP_NAT_RANGE_PROTO_SPECIFIED).
	   Use reply in case it's already been mangled (eg local packet).
	*/
	u_int32_t ip
		= (HOOK2MANIP(hooknum) == IP_NAT_MANIP_SRC
		   ? conntrack->tuplehash[IP_CT_DIR_REPLY].tuple.dst.ip
		   : conntrack->tuplehash[IP_CT_DIR_REPLY].tuple.src.ip);
	struct ip_nat_range range
		= { IP_NAT_RANGE_MAP_IPS, ip, ip, { 0 }, { 0 } };

	DEBUGP("Allocating NULL binding for %p (%u.%u.%u.%u)\n", conntrack,
	       NIPQUAD(ip));
	return ip_nat_setup_info(conntrack, &range, hooknum);
}

unsigned int
alloc_null_binding_confirmed(struct ip_conntrack *conntrack,
                             struct ip_nat_info *info,
                             unsigned int hooknum)
{
	u_int32_t ip
		= (HOOK2MANIP(hooknum) == IP_NAT_MANIP_SRC
		   ? conntrack->tuplehash[IP_CT_DIR_REPLY].tuple.dst.ip
		   : conntrack->tuplehash[IP_CT_DIR_REPLY].tuple.src.ip);
	u_int16_t all
		= (HOOK2MANIP(hooknum) == IP_NAT_MANIP_SRC
		   ? conntrack->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u.all
		   : conntrack->tuplehash[IP_CT_DIR_REPLY].tuple.src.u.all);
	struct ip_nat_range range
		= { IP_NAT_RANGE_MAP_IPS, ip, ip, { all }, { all } };

	DEBUGP("Allocating NULL binding for confirmed %p (%u.%u.%u.%u)\n",
	       conntrack, NIPQUAD(ip));
	return ip_nat_setup_info(conntrack, &range, hooknum);
}

int ip_nat_rule_find(struct sk_buff **pskb,
		     unsigned int hooknum,
		     const struct net_device *in,
		     const struct net_device *out,
		     struct ip_conntrack *ct,
		     struct ip_nat_info *info)
{
	int ret;

	ret = ipt_do_table(pskb, hooknum, in, out, &nat_table, NULL);

	if (ret == NF_ACCEPT) {
		if (!ip_nat_initialized(ct, HOOK2MANIP(hooknum)))
			/* NUL mapping */
			ret = alloc_null_binding(ct, info, hooknum);
	}
	return ret;
}

static struct ipt_target ipt_snat_reg = {
	.name		= "SNAT",
	.target		= ipt_snat_target,
	.checkentry	= ipt_snat_checkentry,
};

static struct ipt_target ipt_dnat_reg = {
	.name		= "DNAT",
	.target		= ipt_dnat_target,
	.checkentry	= ipt_dnat_checkentry,
};

int __init ip_nat_rule_init(void)
{
	int ret;

	ret = ipt_register_table(&nat_table, &nat_initial_table.repl);
	if (ret != 0)
		return ret;
	ret = ipt_register_target(&ipt_snat_reg);
	if (ret != 0)
		goto unregister_table;

	ret = ipt_register_target(&ipt_dnat_reg);
	if (ret != 0)
		goto unregister_snat;

	return ret;

 unregister_snat:
	ipt_unregister_target(&ipt_snat_reg);
 unregister_table:
	ipt_unregister_table(&nat_table);

	return ret;
}

void ip_nat_rule_cleanup(void)
{
	ipt_unregister_target(&ipt_dnat_reg);
	ipt_unregister_target(&ipt_snat_reg);
	ipt_unregister_table(&nat_table);
}
