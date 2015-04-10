/*
 *	Handle incoming frames
 *	Linux ethernet bridge
 *
 *	Authors:
 *	Lennert Buytenhek		<buytenh@gnu.org>
 *
 *	$Id: br_input.c,v 1.1.1.1 2006/04/03 08:41:29 amos_lee Exp $
 *
 *	This program is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License
 *	as published by the Free Software Foundation; either version
 *	2 of the License, or (at your option) any later version.
 */

#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/netfilter_bridge.h>
#include "br_private.h"

#ifdef CONFIG_BRIDGE_IGMPP_PROCFS
		#include <linux/ip.h>
		#include <linux/in.h>
	#include <linux/igmp.h>
#endif

const unsigned char bridge_ula[6] = { 0x01, 0x80, 0xc2, 0x00, 0x00, 0x00 };

static int br_pass_frame_up_finish(struct sk_buff *skb)
{
	netif_receive_skb(skb);
	return 0;
}

static void br_pass_frame_up(struct net_bridge *br, struct sk_buff *skb)
{
	struct net_device *indev;

	br->statistics.rx_packets++;
	br->statistics.rx_bytes += skb->len;

	indev = skb->dev;
	skb->dev = br->dev;

	NF_HOOK(PF_BRIDGE, NF_BR_LOCAL_IN, skb, indev, NULL,
			br_pass_frame_up_finish);
}

#ifdef CONFIG_BRIDGE_IGMPP_PROCFS
/* snoop_MAC() => If IP address that existed in br_mac_table ,replace it,
 * else create a new list entry and add it to list.
 * called under bridge lock */
static void snoop_MAC(struct net_bridge *br ,struct sk_buff *skb2)
{
	uint32_t ip32 =  (uint32_t) skb2->nh.iph->saddr;

	struct br_mac_table_t *tlist;
	int find = 0;;
	list_for_each_entry(tlist,&(br->br_mac_table.list), list){
		if ( tlist->ip_addr == ip32){
			find =1;
			int i;
			struct ethhdr * src = eth_hdr(skb2);
			for (i =0; i<6; i++)
				tlist->mac_addr[i] = src->h_source[i];
			break;
		}
	}
	if (find == 0 ){
		struct br_mac_table_t * new_entry;
		new_entry = (struct br_mac_table_t *)kmalloc(sizeof(struct br_mac_table_t), GFP_ATOMIC);
		if (new_entry != NULL){
			int i;
			struct ethhdr * src = eth_hdr(skb2);
			for (i =0; i<6; i++)
				new_entry->mac_addr[i] = src->h_source[i];
			new_entry->ip_addr = ip32;
			list_add(&(new_entry->list), &(br->br_mac_table.list));
		}else{
			#ifdef CONFIG_BRIDGE_IGMPP_PROCFS_DEBUG
			printk(KERN_INFO "[BR_MAC_PROC]-> alloc new br_mac_table_t fail !!\n");
			#endif
		}
	}
}
#endif 

/* note: already called with rcu_read_lock (preempt_disabled) */
int br_handle_frame_finish(struct sk_buff *skb)
{
	const unsigned char *dest = eth_hdr(skb)->h_dest;
	struct net_bridge_port *p = skb->dev->br_port;
	struct net_bridge *br = p->br;
	struct net_bridge_fdb_entry *dst;
	int passedup = 0;

	/* insert into forwarding database after filtering to avoid spoofing */
	br_fdb_update(p->br, p, eth_hdr(skb)->h_source);

	if (is_multicast_ether_addr(dest)) {
#ifdef CONFIG_BRIDGE_IGMPP_PROCFS

		spin_lock_bh(&br->lock); // bridge lock

		if (atomic_read(&br->br_mac_table_enable) == 1 )
			if(skb->nh.iph->protocol == IPPROTO_IGMP){ // IGMP protocol number: 0x02
				struct sk_buff *skb2;
				if ((skb2 = skb_clone(skb, GFP_ATOMIC)) != NULL) {
					skb_pull(skb2, skb2->nh.iph->ihl<<2);
					struct igmphdr *ih = (struct igmphdr *) skb2->data;
					if (ih->type == IGMP_HOST_MEMBERSHIP_REPORT ||		// IGMPv1 REPORT
						ih->type == IGMPV2_HOST_MEMBERSHIP_REPORT ||	// IGMPv2 REPORT
						ih->type == IGMPV3_HOST_MEMBERSHIP_REPORT	)	// IGMPv3 REPORT
					{
						snoop_MAC(br, skb2);
					}
					kfree_skb(skb2);
				}else{
					#ifdef CONFIG_BRIDGE_IGMPP_PROCFS_DEBUG
					printk(KERN_INFO "[BR_MAC_PROC]-> alloc new sk_buff fail !!\n");
					#endif
				}
			}

		spin_unlock_bh(&br->lock); // bridge unlock

#endif
		br->statistics.multicast++;
		br_flood_forward(br, skb, 1);
			br_pass_frame_up(br, skb);
		goto out;
	}

	if (br->dev->flags & IFF_PROMISC) {
		struct sk_buff *skb2;

		skb2 = skb_clone(skb, GFP_ATOMIC);
		if (skb2 != NULL) {
			passedup = 1;
			br_pass_frame_up(br, skb2);
		}
	}

	if (dest[0] & 1) {
		br_flood_forward(br, skb, !passedup);
		if (!passedup)
			br_pass_frame_up(br, skb);
		goto out;
	}

	dst = __br_fdb_get(br, dest);
	if (dst != NULL && dst->is_local) {
		if (!passedup)
			br_pass_frame_up(br, skb);
		else
			kfree_skb(skb);
		goto out;
	}

	if (dst != NULL) {
		br_forward(dst->dst, skb);
		goto out;
	}

	br_flood_forward(br, skb, 0);

out:
	return 0;
}

/*
 * Called via br_handle_frame_hook.
 * Return 0 if *pskb should be processed furthur
 *	  1 if *pskb is handled
 * note: already called with rcu_read_lock (preempt_disabled) 
 */
int br_handle_frame(struct net_bridge_port *p, struct sk_buff **pskb)
{
	struct sk_buff *skb = *pskb;
	const unsigned char *dest = eth_hdr(skb)->h_dest;

	if (p->state == BR_STATE_DISABLED)
		goto err;

	if (!is_valid_ether_addr(eth_hdr(skb)->h_source))
		goto err;

	if (p->state == BR_STATE_LEARNING)
		br_fdb_update(p->br, p, eth_hdr(skb)->h_source);

	if (p->br->stp_enabled &&
	    !memcmp(dest, bridge_ula, 5) &&
	    !(dest[5] & 0xF0)) {
		if (!dest[5]) {
			NF_HOOK(PF_BRIDGE, NF_BR_LOCAL_IN, skb, skb->dev, 
				NULL, br_stp_handle_bpdu);
			return 1;
		}
	}

	else if (p->state == BR_STATE_FORWARDING) {
		if (br_should_route_hook) {
			if (br_should_route_hook(pskb)) 
				return 0;
			skb = *pskb;
			dest = eth_hdr(skb)->h_dest;
		}

		if (!compare_ether_addr(p->br->dev->dev_addr, dest))
			skb->pkt_type = PACKET_HOST;

		NF_HOOK(PF_BRIDGE, NF_BR_PRE_ROUTING, skb, skb->dev, NULL,
			br_handle_frame_finish);
		return 1;
	}

err:
	kfree_skb(skb);
	return 1;
}
