/*
  This is a module which is used for match support for every Nth packet
  This file is distributed under the terms of the GNU General Public
  License (GPL). Copies of the GPL can be obtained from:
     ftp://prep.ai.mit.edu/pub/gnu/GPL

  2001-07-18 Fabrice MARIE <fabrice@netfilter.org> : initial implementation.
  2001-09-20 Richard Wagner (rwagner@cloudnet.com)
        * added support for multiple counters
        * added support for matching on individual packets
          in the counter cycle
  2003-04-30 Maciej Soltysiak <solt@dns.toxicfilms.tv> : IPv6 Port
  2005-06-27 Harald Welte <laforg@netfilter.org>: API update

*/

#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <net/tcp.h>
#include <linux/spinlock.h>
#include <linux/netfilter_ipv6/ip6_tables.h>
#include <linux/netfilter_ipv6/ip6t_nth.h>

MODULE_LICENSE("GPL");

/*
 * State information.
 */
struct state {
	spinlock_t lock;
	u_int16_t number;
};

static struct state states[IP6T_NTH_NUM_COUNTERS];

static int
ip6t_nth_match(const struct sk_buff *pskb,
	      const struct net_device *in,
	      const struct net_device *out,
	      const void *matchinfo,
	      int offset,
	      unsigned int protoff,
	      int *hotdrop)
{
	/* Parameters from userspace */
	const struct ip6t_nth_info *info = matchinfo;
        unsigned counter = info->counter;
       	if((counter < 0) || (counter >= IP6T_NTH_NUM_COUNTERS)) 
      	{
       		printk(KERN_WARNING "nth: invalid counter %u. counter between 0 and %u\n", counter, IP6T_NTH_NUM_COUNTERS-1);
               return 0;
        };

        spin_lock(&states[counter].lock);

        /* Are we matching every nth packet?*/
        if (info->packet == 0xFF)
        {
		/* We're matching every nth packet and only every nth packet*/
		/* Do we match or invert match? */
		if (info->not == 0)
		{
			if (states[counter].number == 0)
			{
				++states[counter].number;
				goto match;
			}
			if (states[counter].number >= info->every)
				states[counter].number = 0; /* reset the counter */
			else
				++states[counter].number;
			goto dontmatch;
		}
		else
		{
			if (states[counter].number == 0)
			{
				++states[counter].number;
				goto dontmatch;
			}
			if (states[counter].number >= info->every)
				states[counter].number = 0;
			else
				++states[counter].number;
			goto match;
		}
        }
        else
        {
		/* We're using the --packet, so there must be a rule for every value */
		if (states[counter].number == info->packet)
		{
			/* only increment the counter when a match happens */
			if (states[counter].number >= info->every)
				states[counter].number = 0; /* reset the counter */
			else
				++states[counter].number;
			goto match;
		}
		else
			goto dontmatch;
	}

 dontmatch:
	/* don't match */
	spin_unlock(&states[counter].lock);
	return 0;

 match:
	spin_unlock(&states[counter].lock);
	return 1;
}

static int
ip6t_nth_checkentry(const char *tablename,
		   const struct ip6t_ip6 *e,
		   void *matchinfo,
		   unsigned int matchsize,
		   unsigned int hook_mask)
{
	/* Parameters from userspace */
	const struct ip6t_nth_info *info = matchinfo;
        unsigned counter = info->counter;
        if((counter < 0) || (counter >= IP6T_NTH_NUM_COUNTERS)) 
	{
		printk(KERN_WARNING "nth: invalid counter %u. counter between 0 and %u\n", counter, IP6T_NTH_NUM_COUNTERS-1);
               	return 0;
       	};

	if (matchsize != IP6T_ALIGN(sizeof(struct ip6t_nth_info))) {
		printk("nth: matchsize %u != %zu\n", matchsize,
		       IP6T_ALIGN(sizeof(struct ip6t_nth_info)));
		return 0;
	}

	states[counter].number = info->startat;

	return 1;
}

static struct ip6t_match ip6t_nth_reg = { 
	{NULL, NULL},
	"nth",
	ip6t_nth_match,
	ip6t_nth_checkentry,
	NULL,
	THIS_MODULE };

static int __init init(void)
{
	unsigned counter;
        memset(&states, 0, sizeof(states));
	if (ip6t_register_match(&ip6t_nth_reg))
		return -EINVAL;

        for(counter = 0; counter < IP6T_NTH_NUM_COUNTERS; counter++) 
	{
		spin_lock_init(&(states[counter].lock));
        };

	printk("ip6t_nth match loaded\n");
	return 0;
}

static void __exit fini(void)
{
	ip6t_unregister_match(&ip6t_nth_reg);
	printk("ip6t_nth match unloaded\n");
}

module_init(init);
module_exit(fini);
