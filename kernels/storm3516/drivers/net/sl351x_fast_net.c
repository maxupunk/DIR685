#include <linux/skbuff.h>
#include <linux/if_ether.h>
#include <linux/ip.h>

#include "../../net/bridge/br_private.h"

#include <linux/ip.h>
#include <linux/tcp.h>
#ifdef	CONFIG_NETFILTER
#include <linux/netfilter_ipv4/ip_conntrack.h>
#include <linux/netfilter_ipv4/ip_conntrack_protocol.h>

#include <linux/netfilter_ipv4/ip_conntrack_helper.h>
#include <linux/netfilter_ipv4/ip_conntrack_core.h>
#include <linux/netfilter_ipv4/listhelp.h>
#include <net/ip.h>
#include <linux/netfilter_ipv4/ip_nat.h>
#include <linux/netfilter_ipv4/ip_nat_core.h>
#endif
#include <asm/arch/sl351x_gmac.h>
#include <linux/sysctl_storlink.h>

/*
// in route.c
int sl_ip_route_cache(struct sk_buff *skb, u32 daddr, u32 saddr,
		   u8 tos, struct net_device *dev);
*/
/*
//in ip_nat_core.c
int
manip_pkt(u_int16_t proto,
	  struct sk_buff **pskb,
	  unsigned int iphdroff,
	  const struct ip_conntrack_tuple *target,
	  enum ip_nat_manip_type maniptype);
*/

/* storlink_ctl.fast_net bits
	bit 1  enable / disable
	bit 2  transmit through device tx queue / through Linux TC
	bit 5  GMAC and other PCI devices are combined into a bridge device / None
	bit 7  fast_ipsec_vpn enable / disable
*/

int sl_fast_bridging(struct sk_buff *skb, int in_device_gmac_index);
int sl_fast_nat_route(struct sk_buff *skb, int in_device_gmac_index);

int sl_fast_net(struct sk_buff *skb) {

	int r;
	int in_device_gmac_index = -1;
#if defined(CONFIG_SL351x_NAT) ||defined(CONFIG_SL351X_BR)
	TOE_INFO_T	*toe;
	toe = (TOE_INFO_T *)&toe_private_data;

	if(toe->gmac[0].dev == skb->dev) {
		in_device_gmac_index = 0;
	}
	else if(toe->gmac[1].dev == skb->dev) {
		in_device_gmac_index = 1;
	}
#endif

	if (in_irq())
		return 0;

	if(unlikely(!(storlink_ctl.fast_net & 1))) {
		return 0;
	}

	//+++ add by siyou 2009/2/18 11:43am.
	//sl_fast_net() will be call twice when pkt receive from eth0.
	//first time is from eth0, second time is from br0.
	//and then the br0 pkt will be fastnet, then the url blocking will no chance to filter.
	//so we return when dev is from br0, the bad news is pkts from eth0 will not go fastnet.
	if (strcmp(skb->dev->name,"br0") == 0)
		return 0;
	//--- end add.
	
	if((r=sl_fast_bridging(skb, in_device_gmac_index)) == 1) {
		return 1;
	}
	else if (r == 2) //add by siyou. it is head to bridge ip, no need further process.
		return 0;

#ifdef	CONFIG_NETFILTER
	if(sl_fast_nat_route(skb, in_device_gmac_index)) {
		return 1;
	}
#endif
#ifdef	CONFIG_SL351X_IPSEC
	if((storlink_ctl.fast_net & 64) && ((__u8)(skb->cb[28]) != 2) && (sl_fast_ipsec(skb))) {
		ipsec_handle_skb_finish();
		return 1;
	}
#endif
	return 0;
}
EXPORT_SYMBOL(sl_fast_net);

uint32_t inline getDeviceIp(struct net_device *dev)
{
struct in_device *in_dev = dev->ip_ptr;
	
	//Teresa i the interface set to 0.0.0.0 the ifa_list is null. 2009/3/12 10:13¤U¤È
	if (in_dev && in_dev->ifa_list)
		return in_dev->ifa_list->ifa_address;
	return 0;
}

/** 
 * Fast bridging. Michael Wu 
 **/

int sl_fast_bridging(struct sk_buff *skb, int in_device_gmac_index) {

	TOE_INFO_T			*toe = (TOE_INFO_T*)&toe_private_data;
	struct net_bridge_fdb_entry *br_fdb, *br_fdb_sa;
	struct net_bridge_port *br_port;
	struct net_device *dst_nic;
	unsigned char	*sa, *da;
	int r=0;

	da = (unsigned char*)(skb->mac.raw);
	sa = da + ETH_ALEN;

	if( (br_port = rcu_dereference(skb->dev->br_port)) == NULL) {
		goto no_bridge;
	}

	if (unlikely(br_fdb = br_fdb_get(br_port->br, da)) == NULL)
		goto no_hash_1;

	if (unlikely(br_fdb_sa = br_fdb_get(br_port->br, sa)) == NULL)
		goto no_hash_2;

	if( unlikely(br_fdb->is_local))
	{
	uint32_t ipaddr = getDeviceIp(br_port->br->dev);
	struct iphdr *iph = (struct iphdr*)&(skb->data[0]);

		//printk("ip=%x", ipaddr);
		//printk(",skb dst ip=%x\n", iph->daddr);
		if ( ipaddr == iph->daddr)
			r = 2; //dst is to bridge's ip, no need further nat process.
		goto not_local;
	}
	dst_nic = br_fdb->dst->dev;

#if defined(CONFIG_SL351X_BR)
	// If the skb origin from gmac and destinate to gmac then we need to skip handling this packet.
	if(unlikely(in_device_gmac_index!=-1) && toe->gmac[1-in_device_gmac_index].dev == dst_nic) {
		return 0;
	}
#endif

	br_fdb_sa->ageing_timer = jiffies;
	skb->dev = dst_nic;
	skb->data = skb->data - ETH_HLEN;
	skb->len += ETH_HLEN;

	if(likely(storlink_ctl.fast_net & 2)) {
		// transmit packet directly to device tx queue
		if(unlikely(dst_nic->hard_start_xmit(skb, dst_nic))) {
			dev_kfree_skb(skb);
			printk("%s::fast bridging %s->hard_start_xmit failed\n",  __func__, dst_nic->name);
		};
	}
	else {
		if(unlikely(dev_queue_xmit(skb))) {
			printk("%s %s fast bridging dev_queue_xmit failed\n", __func__, dst_nic->name);
		}
	}

	return 1;

not_local:
	br_fdb_put(br_fdb_sa);
no_hash_2:
	br_fdb_put(br_fdb);
no_hash_1:		
no_bridge:
		
	return r;
}

#ifdef	CONFIG_NETFILTER
int rnd = 0;

int sl_fast_nat_route(struct sk_buff *skb, int in_device_gmac_index) {

	TOE_INFO_T			*toe = (TOE_INFO_T*)&toe_private_data;
/**
* Fast NAT and Routing. Michael Wu
**/

	struct ethhdr *eth, ehdr;
	struct iphdr *iph;
	u32	sip, dip;
	u16	sport, dport;
	int i;
	struct net_device *orig_dev = skb->dev;

	/*I've seen packets with nr_frags!=0 from RT2860. It shouldn't happen...*/
	if(skb_shinfo(skb)->nr_frags) {
		printk("%s::frags %d\n", __func__, skb_shinfo(skb)->nr_frags);
		return 0;
	}
	eth = (struct ethhdr*)(skb->mac.raw);
	iph = (struct iphdr*)&(skb->data[0]);

	for (i=0; i<ETH_ALEN; i++) {
		ehdr.h_dest[i]=eth->h_dest[i];
		ehdr.h_source[i]=eth->h_source[i];
	}

	if( likely(eth->h_proto == __constant_htons(ETH_P_IP)) && 
		likely(! (iph->frag_off & __constant_htons(IP_OFFSET)) ) &&
		likely(iph->ihl == 5 ) ) {
		struct ip_conntrack_tuple tuple;
		struct ip_conntrack_protocol *protocol;
		struct ip_conntrack_tuple_hash *h;
		struct ip_conntrack *ct;
		struct ip_conntrack_tuple target;
		int ips_src_nat_manip;  // What to do for IPS_SRC_NAT? Depends on CT_DIR direction
		int ips_dst_nat_manip;  // What to do for IPS_DST_NAT?
		int nat_change_dst = 0;	// will NAT change the destination IP?
		struct net_bridge_port *br_port=NULL;
		struct hh_cache *hh = NULL;
		int hh_alen;
		struct net_bridge_fdb_entry *br_fdb=NULL;
		struct net_bridge *br=NULL;

		// only handle ETH_P_IP frames that are not Fragmented
		// and without IP options (iph->ihl == 5)
		sip = iph->saddr;
		dip = iph->daddr;

		skb->nh.iph = iph;
		if (unlikely(skb->len < ntohs(iph->tot_len))) {
			printk("ERROR %s %s:: skb->len(%d) < iph->tot_len %d\n",
				skb->dev->name, __func__, skb->len, ntohs(iph->tot_len));
		}

		if( unlikely(iph->ihl*4 > ntohs(iph->tot_len) ) ) {

			printk("ERROR %s %s:: iph->ihl*4 (%d) > ntohs(iph->tot_len) (%d) \n", 
				skb->dev->name, __func__, iph->ihl*4, ntohs(iph->tot_len) );		
			return 0;
		}
		protocol = __ip_conntrack_proto_find(iph->protocol);

		// The following code references ip_conntrack_core.c ip_ct_get_tuple
		// set up tuple
		tuple.src.ip = iph->saddr;
		tuple.dst.ip = iph->daddr;
		tuple.dst.protonum = iph->protocol;
		tuple.dst.dir = IP_CT_DIR_ORIGINAL;

		if( unlikely(!protocol || !protocol->pkt_to_tuple(skb, iph->ihl*4, &tuple)) ) {
			printk("%s:: protocol->pkt_to_tuple failed protocol = %d\n", __func__, iph->protocol);
			goto skip_fast_nat;
		}

		// The following code references ip_conntrack_core.c resolve_normal_ct
		
		// ct->ct_general.use is incremented in ip_conntrack_find_get()
		// We need to remember to release it.
		// see resolve_normal_ct in ip_conntrck_core and nf_conntrack_put in skbuff.h for detail.

		if( unlikely(!(h = ip_conntrack_find_get(&tuple, NULL))) ) {
			//printk("%s::cannot find ip_conntrack!\n", __func__);
			goto skip_fast_nat;
		}

		// From this point on, we need to decrement ct_general.use before leaving
		ct = tuplehash_to_ctrack(h);
		
//		printk("ct->ct_general.use = %d\n", ct->ct_general.use);
		
		if(ct->helper) {
			/* We do not handle connections that have a helper method. For example, FTP control session. */
/*
			printk("ct->helper!=NULL\n");

			printk("src=%u.%u.%u.%u dst=%u.%u.%u.%u \n",
			   NIPQUAD(tuple.src.ip), NIPQUAD(tuple.dst.ip));		
			
			printk("sport=%hu dport=%hu \n",
				  ntohs(tuple.src.u.tcp.port),
				  ntohs(tuple.dst.u.tcp.port));
*/
			goto release_ct;
		}

		// In below, we filter out special cases that we don't want to do fast-NAT. Let Linux handle these cases.

		if(iph->protocol == IPPROTO_TCP) {
//			printk("1\n");
			struct tcphdr *tcp_hdr;
			tcp_hdr = (struct tcphdr *)((u32)iph + (iph->ihl*4));
			
			// skip fast nat if TCP not in TCP_CONNTRACK_ESTABLISHED state
			// we let Kernel handle other special cases
			if( unlikely(ct->proto.tcp.state != TCP_CONNTRACK_ESTABLISHED) ) {
//				printk("2\n");
				goto release_ct;
			}

			if( unlikely(tcp_flag_word(tcp_hdr) & (TCP_FLAG_SYN | TCP_FLAG_FIN | TCP_FLAG_RST)) ) {
//				printk("3\n");
				goto release_ct;
			}

			sport = tcp_hdr->source;
			dport = tcp_hdr->dest;

			if ( dport == htons(80) ) //trap for url blocking from wireless sta. by siyou 2009/3/9 01:01pm
				goto release_ct;
		}
		/* Fast-NAT seems to be able to handle ICMP packets, but 
		they are handled specially in Kernel,
		so we don't want to do fast NAT on ICMP packets.
		see ip_nat_standalone.c/ip_nat_fn for detail
		*/
		else if(unlikely(iph->protocol == IPPROTO_ICMP)) {
			goto release_ct;
		}
		else
			goto release_ct;

		
		// Do the real NAT work. If no NAT is needed, then it is equivalent to fast routing.
		
		// Below is condensed version of ip_nat_packet in ip_nat_core.c
		// Instead of mimicking of calling it from PRE ROUTING and POST ROUTING twice
		// and let ip_nat_packet to filter out the unneeded call, instead we derived the needed NAT action directly

		/* We are aiming to look like inverse of other direction. */
		invert_tuplepr(&target, &ct->tuplehash[!DIRECTION(h)].tuple);

		/* Lookup routing cache.
		  * On successful return, reference to skb->dst will be incremented. 
		  * Kernel will release skb->dst when freeing skb, but if we failed to transmit the packet,
		  * we need to release skb->dst our self.
		  */

		/*
		  * if ((ct->status & IPS_SRC_NAT) && DIRECTION(h) == IP_CT_DIR_REPLY) ||
		  *     ((ct->status & IPS_DST_NAT) && DIRECTION(h) == IP_CT_DIR_ORIGINAL)
		  * then NAT will change destination IP
		  */
		if(DIRECTION(h) == IP_CT_DIR_ORIGINAL) {
			if(ct->status & IPS_DST_NAT) {
				nat_change_dst = 1;
			}
			ips_src_nat_manip = IP_NAT_MANIP_SRC;
			ips_dst_nat_manip = IP_NAT_MANIP_DST;
		}
		else { // DIRECTION(h) == IP_CT_DIR_REPLY
			if(ct->status & IPS_SRC_NAT) {
				nat_change_dst = 1;
			}
			ips_src_nat_manip = IP_NAT_MANIP_DST;
			ips_dst_nat_manip = IP_NAT_MANIP_SRC;
		
		}

		// for packets origing from a device that's part of a bridge, we need to change skb->dev to the bridge device
		if( likely(storlink_ctl.fast_net & 16) && (br_port = rcu_dereference(skb->dev->br_port)) != NULL ) {
			skb->dev = br_port->br->dev;
		}

		if( unlikely(!sl_ip_route_cache(skb,
							nat_change_dst ? target.dst.ip : skb->nh.iph->daddr,
							skb->nh.iph->saddr,
							skb->nh.iph->tos, skb->dev, skb->dev->ifindex, 0)) ) {
			goto release_ct;
		}
		
		if(ct->status & IPS_SRC_NAT) {
			if( unlikely (!manip_pkt(target.dst.protonum, &skb, 0, &target, ips_src_nat_manip)) ) {
					
				dst_release(skb->dst);	// release the dst previously acquired by sl_ip_route_cache
				goto release_ct;
			}
		}

		if(ct->status & IPS_DST_NAT) {
			if( unlikely (!manip_pkt(target.dst.protonum, &skb, 0, &target, ips_dst_nat_manip)) ) {
					
				dst_release(skb->dst);	// release the dst previously acquired by sl_ip_route_cache
				goto release_ct;
			}
		}

		/* Original code 
		// #define DIRECTION(h) ((enum ip_conntrack_dir)(h)->tuple.dst.dir)
		if (DIRECTION(h) == IP_CT_DIR_ORIGINAL) {
			if(sl_nat_packet (ct, IP_CT_DIR_ORIGINAL, IP_NAT_MANIP_SRC, skb)) {
//				printk("4\n");
				goto transmit_packet;
			}
			else if(sl_nat_packet (ct, IP_CT_DIR_ORIGINAL, IP_NAT_MANIP_DST, skb)) {
//				printk("4-2\n");
				goto transmit_packet;
			}
			else {
				goto release_ct;
			}
		}
		else if(DIRECTION(h) == IP_CT_DIR_REPLY) {
			if(sl_nat_packet (ct, IP_CT_DIR_REPLY, IP_NAT_MANIP_DST, skb)) {
//				printk("5\n");
				goto transmit_packet;
			}
			else if(sl_nat_packet (ct, IP_CT_DIR_REPLY, IP_NAT_MANIP_SRC, skb)) {
//				printk("5-2\n");
				goto transmit_packet;
			}
			else
			{
				goto release_ct;
			}
		}
		*/
		
		//transmit_packet:;

		nf_conntrack_put(&ct->ct_general);

		hh = skb->dst->hh;

		// The following code references ip_finish_output2 in ip_output.c
//			printk("6\n");

		read_lock_bh(&hh->hh_lock);

		hh_alen = HH_DATA_ALIGN(hh->hh_len);
			
		// Originally soulbe be:
		// memcpy(skb->data - hh_alen, hh->hh_data, hh_alen);
		//skb_push(skb, hh->hh_len);

		memcpy(skb->data - ETH_HLEN - RX_INSERT_BYTES, hh->hh_data, hh_alen);
		read_unlock_bh(&hh->hh_lock);

	/*
			if(unlikely(printk_ratelimit())) {
				printk("%s:: header cache hit!\n", __func__);
			}
	*/
			
		skb->dev = skb->dst->dev;
/*
			if((rnd++) == 100) {
				rnd = 0;
				printk("freeing skb. skb.skb_shinfo->nr_frags=%d\n", skb_shinfo(skb)->nr_frags);
				dev_kfree_skb(skb);
				printk("end freeing skb\n");
			}
*/
		if(likely(storlink_ctl.fast_net & 2)) {
//				struct net_bridge_fdb_entry *br_fdb;
//				struct net_bridge *br;
				// check to see if destination device is a bridge device. send packet directly to the real device.
			if( likely(storlink_ctl.fast_net & 16) && skb->dev->hard_start_xmit == br_dev_xmit ) {
				unsigned char* da = (unsigned char*)skb->mac.raw;
				br = netdev_priv(skb->dev);
				if ((br_fdb = br_fdb_get(br, da)) != NULL) {
					skb->dev = br_fdb->dst->dev;
					br_fdb_put(br_fdb);
				}
			}
#if defined (CONFIG_SL351x_NAT)
			if ((orig_dev->features & NETIF_F_HWNAT) && (skb->dev->features & NETIF_F_HWNAT)) {
//				printk("fastnet error: %s to %s\n", orig_dev->name, skb->dev->name );
				skb->dev = orig_dev;
				if (eth->h_proto == __constant_htons(ETH_P_IP)) {
					skb->nh.iph->saddr = sip;
					skb->nh.iph->daddr = dip;
					if(iph->protocol == IPPROTO_TCP) 
					{
					struct tcphdr *tcp_hdr;
						tcp_hdr = (struct tcphdr *)((u32)iph + (iph->ihl*4));
						tcp_hdr->source = sport;
						tcp_hdr->dest = dport;
					}
				}
				for (i=0; i<ETH_ALEN; i++) {
					eth->h_dest[i] = ehdr.h_dest[i];
					eth->h_source[i] = ehdr.h_source[i];
				}
				return 0;
			}
#endif
			skb->data -= ETH_HLEN;
			skb->len  += ETH_HLEN;
			if(unlikely(skb->dev->hard_start_xmit(skb, skb->dev))) {
				dev_kfree_skb(skb);
				printk("%s::fast routing %s->hard_start_xmit failed \n", __func__, skb->dev->name);
				return 1;
			};
		} else {
			skb->data -= ETH_HLEN;
			skb->len  += ETH_HLEN;
			if(unlikely(dev_queue_xmit(skb))) {
				printk("%s %s fast routing dev_queue_xmit failed\n", __func__, skb->dev->name);
			}
		}
		return 1;

release_ct:
		nf_conntrack_put(&ct->ct_general);
			
skip_fast_nat:;
		skb->dev = orig_dev; //add by siyou, fix sometimes access web server fail. 2008/12/25 04:44pm
		if (eth->h_proto == __constant_htons(ETH_P_IP)) {
			skb->nh.iph->saddr = sip;
			skb->nh.iph->daddr = dip;
		}
		for (i=0; i<ETH_ALEN; i++) {
			eth->h_dest[i] = ehdr.h_dest[i];
			eth->h_source[i] = ehdr.h_source[i];
		}
	} else {
	}
	return 0;
}
#endif

