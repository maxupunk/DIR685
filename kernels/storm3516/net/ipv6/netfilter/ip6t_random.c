/*
  This is a module which is used for a "random" match support.
  This file is distributed under the terms of the GNU General Public
  License (GPL). Copies of the GPL can be obtained from:
     ftp://prep.ai.mit.edu/pub/gnu/GPL

  2001-10-14 Fabrice MARIE <fabrice@netfilter.org> : initial implementation.
  2003-04-30 Maciej Soltysiak <solt@dns.toxicfilms.tv> : IPv6 Port
*/

#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <linux/random.h>
#include <net/tcp.h>
#include <linux/spinlock.h>
#include <linux/netfilter_ipv6/ip6_tables.h>
#include <linux/netfilter_ipv6/ip6t_random.h>

MODULE_LICENSE("GPL");

static int
ip6t_rand_match(const struct sk_buff *pskb,
	       const struct net_device *in,
	       const struct net_device *out,
	       const void *matchinfo,
	       int offset,
	       unsigned int protoff,
	       int *hotdrop)
{
	/* Parameters from userspace */
	const struct ip6t_rand_info *info = matchinfo;
	u_int8_t random_number;

	/* get 1 random number from the kernel random number generation routine */
	get_random_bytes((void *)(&random_number), 1);

	/* Do we match ? */
	if (random_number <= info->average)
		return 1;
	else
		return 0;
}

static int
ip6t_rand_checkentry(const char *tablename,
		   const struct ip6t_ip6 *e,
		   void *matchinfo,
		   unsigned int matchsize,
		   unsigned int hook_mask)
{
	/* Parameters from userspace */
	const struct ip6t_rand_info *info = matchinfo;

	if (matchsize != IP6T_ALIGN(sizeof(struct ip6t_rand_info))) {
		printk("ip6t_random: matchsize %u != %Zd\n", matchsize,
		       IP6T_ALIGN(sizeof(struct ip6t_rand_info)));
		return 0;
	}

	/* must be  1 <= average % <= 99 */
	/* 1  x 2.55 = 2   */
	/* 99 x 2.55 = 252 */
	if ((info->average < 2) || (info->average > 252)) {
		printk("ip6t_random:  invalid average %u\n", info->average);
		return 0;
	}

	return 1;
}

static struct ip6t_match ip6t_rand_reg = { 
	{NULL, NULL},
	"random",
	ip6t_rand_match,
	ip6t_rand_checkentry,
	NULL,
	THIS_MODULE };

static int __init init(void)
{
	if (ip6t_register_match(&ip6t_rand_reg))
		return -EINVAL;

	printk("ip6t_random match loaded\n");
	return 0;
}

static void __exit fini(void)
{
	ip6t_unregister_match(&ip6t_rand_reg);
	printk("ip6t_random match unloaded\n");
}

module_init(init);
module_exit(fini);
