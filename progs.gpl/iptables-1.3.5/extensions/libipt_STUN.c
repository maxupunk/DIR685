
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdlib.h>

#include <iptables.h>
#include <linux/netfilter_ipv4/ip_tables.h>
#include <linux/netfilter_ipv4/ip_nat_rule.h>

#include <linux/netfilter_ipv4/ipt_STUN_common.h>

static enum stun		stun_state=__NONE;
static struct option	options[]= {
	{"type",	1,	NULL,	't'},
	{NULL,		0,	NULL,	0}
};

/* Function which prints out usage message. */
void	help(void)
{
	printf("STUN v%s options:\n"" --type <port>[-<port>]\n"
		"				Port (range) to map to.\n", IPTABLES_VERSION);
}

/* Initialize the target. */
void	init(struct ipt_entry_target *t, 
			unsigned int *nfcache)
{
	struct ip_nat_multi_range	*mr=(struct ip_nat_multi_range *)t->data;

	mr->rangesize=1;
	*nfcache|=NFC_UNKNOWN;
}

/* Parses ports , copying from ipt_MASQUERADE.C*/
static void		parse_port(const char *arg, 
							struct ip_nat_multi_range *mr)
{
	const char	*dash;
	int 		port;

	mr->range[0].flags|=IP_NAT_RANGE_PROTO_SPECIFIED;

	port=atoi(arg);
	if (port<=0||port>65535)
		exit_error(PARAMETER_PROBLEM, "Port `%s' not valid\n", arg);

	dash=strchr(arg, '-');
	if (!dash) {
		mr->range[0].min.tcp.port=mr->range[0].max.tcp.port=htons(port);
	} else {
		int maxport;

		maxport=atoi(dash+1);
		if (maxport==0||maxport>65535)
			exit_error(PARAMETER_PROBLEM, "Port `%s' not valid\n", dash+1);
		if (maxport<port)
			/* People are stupid.  Present reader excepted. */
			exit_error(PARAMETER_PROBLEM, "Port range `%s' funky\n", arg);
		mr->range[0].min.tcp.port=htons(port);
		mr->range[0].max.tcp.port=htons(maxport);
#if	(STUN_DEBUG==1)
		printf("port = %d\n", mr->range[0].min.tcp.port);
		printf("maxport = %d\n", mr->range[0].max.tcp.port);
#endif
	}
}

void	clear_stun_state(struct ip_nat_multi_range *mr)
{
	unsigned int	tmp=0;
	
	tmp|=IP_NAT_SYMMETRIC;
	tmp|=IP_NAT_FULL_CONE;
	tmp|=IP_NAT_RESTRICTED_CONE;
	tmp|=IP_NAT_PORT_RESTRICTED_CONE;
	
	mr->range[0].flags&=(~tmp);
}

/* parse STUN type and port */
int		get_stun_state(const char *optarg, 
					enum stun *stun_state, 
					struct ip_nat_multi_range *mr, 
					bool port_ok)
{
	int		ret=0;	/* 0, means error */
	int		tmp;
	char	*ptmp, *qtmp, *newtmp, newoptarg[20]={0};
	
	/* parser #num:#port-#maxport, ptmp=":#port-#maxport", qtmp="-#maxport" */
	ptmp=strstr(optarg, ":");
	qtmp=strstr(optarg, "-");
	strcpy(newoptarg, optarg);
	newtmp=strtok(newoptarg, ":");

	if((ptmp==NULL)^(qtmp==NULL)) {
		goto RET;			
	} else {				/* if -j STUN --stun #num, ok */
		if(ptmp&&qtmp) {	/* if -j STUN --stun #num:#port-#maxport, ok */
			if(port_ok) {
				ptmp=ptmp+1;
				parse_port(ptmp, mr);
			} else
				exit_error(PARAMETER_PROBLEM, "Need TCP or UDP with port specification");
		}
	}
	tmp=atoi(newtmp);
	/* clear all bits of STUN-flags */
	//clear_stun_state(mr);
	
	switch(tmp) {
	case 1:
		*stun_state=__PORT_RESTRICTED_CONE;
		mr->range[0].flags|=IP_NAT_PORT_RESTRICTED_CONE;
		ret=1;
		break;
	case 2:
		*stun_state=__RESTRICTED_CONE;
		mr->range[0].flags|=IP_NAT_RESTRICTED_CONE;
		ret=1;
		break;
	case 3:
		*stun_state=__FULL_CONE;
		mr->range[0].flags|=IP_NAT_FULL_CONE;
		ret=1;
		break;
	case 4:
		*stun_state=__SYMMETRIC_NAT;
		mr->range[0].flags|=IP_NAT_SYMMETRIC;
		ret=1;
		break;
	default:
		*stun_state=__ERROR;
	}
RET:
	return	ret;
}

/* Function which parses command options; returns true if it ate an option */
int		parse(int c, 
			char **argv, 
			int invert, 
			unsigned int *flags,
			const struct ipt_entry *entry, 
			struct ipt_entry_target **target)
{
	bool	stun_ok=false;
	bool	port_ok=false;
	int		ret=0;		/* 0 means error */
	struct ip_nat_multi_range	*mr=(struct ip_nat_multi_range *)(*target)->data;

	if(entry->ip.proto==IPPROTO_TCP||entry->ip.proto==IPPROTO_UDP) {
		port_ok=true;
	}
	
	switch(c) {
	case 't':
		if((ret=get_stun_state(optarg, &stun_state, mr, port_ok))!=1) {
			/* error state */
		}
		stun_ok=true;
		break;
	default:
		/* error */
		break;
	}
#if	(STUN_DEBUG==1)
	printf("stun_ok = %d\n", stun_ok);
	printf("stun_state = %d (%s)\n", stun_state, stun_dsc[stun_state]);
	printf("ret = %d\n", ret);
	printf("port = %d\n", mr->range[0].min.tcp.port);
	printf("maxport = %d\n", mr->range[0].max.tcp.port);
	printf("min_ip = %x\n", mr->range[0].min_ip);
	printf("max_ip = %x\n", mr->range[0].max_ip);
#endif

	return	ret;
}

/* Final check; exit if not ok. */
void	final_check(unsigned int flags)
{
}

/* Prints out the target iff non-NULL: put space at end */
void	print(const struct ipt_ip *ip,
			const struct ipt_entry_target *target, 
			int numeric)
{
	struct ip_nat_multi_range	*mr=(struct ip_nat_multi_range *)target->data;
	
	if(mr->range[0].flags&IP_NAT_PORT_RESTRICTED_CONE)
		printf("--type Port Restricted CONE\n");
	else if(mr->range[0].flags&IP_NAT_RESTRICTED_CONE)
		printf("--type Restricted CONE\n");
	else if(mr->range[0].flags&IP_NAT_FULL_CONE)
		printf("--type Full CONE\n");
	else if(mr->range[0].flags&IP_NAT_SYMMETRIC)
		printf("--type Symmetric NAT\n");
	else
		/* error state */
		printf("STUN Error!!\n");

	if(mr->range[0].flags & IP_NAT_RANGE_PROTO_SPECIFIED){
		printf(" stun ports: ");
		printf("%hu", ntohs(mr->range[0].min.tcp.port));
		if (mr->range[0].max.tcp.port != mr->range[0].min.tcp.port)
			printf("-%hu", ntohs(mr->range[0].max.tcp.port));
		printf(" ");
	}
	printf("\n");
}

/* Saves the targinfo in parsable form to stdout. */
void	save(const struct ipt_ip *ip, 
			const struct ipt_entry_target *target)
{
	//struct ip_nat_multi_range	*mr=(struct ip_nat_multi_range *)target->data;
}

static struct iptables_target	stun= {
	.next			= NULL,
	.name			= "STUN",
	.version		= IPTABLES_VERSION,
	.size			= IPT_ALIGN(sizeof(struct ip_nat_multi_range)),
	.userspacesize	= IPT_ALIGN(sizeof(struct ip_nat_multi_range)),

	.help			= &help,
	.init			= &init,
	.parse			= &parse,
	.final_check	= &final_check,
	.print			= &print,
	.save			= &save,

	.extra_opts		= options
	/*.option_offset	= ,
	.t				= ,
	.tflags			= ,
	.used			= */
};

void	_init(void)
{
	register_target(&stun);
}
