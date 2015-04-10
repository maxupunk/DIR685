/* String matching match for iptables
 * 
 * (C) 2005 Pablo Neira Ayuso <pablo@eurodev.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/autoconf.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/skbuff.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/netfilter_ipv4/ip_tables.h>
#include <linux/netfilter_ipv4/ipt_string.h>
#include <linux/textsearch.h>
#include <linux/tcp.h>
#include <linux/udp.h>

MODULE_AUTHOR("Pablo Neira Ayuso <pablo@eurodev.net>");
MODULE_DESCRIPTION("IP tables string match module");
MODULE_LICENSE("GPL");

#ifdef CONFIG_IP_NF_MATCH_STRING_DEBUG
#define dprintk(x, args...)     printk(x, ##args)
#else
#define dprintk(x, args...)
#endif

#ifdef CONFIG_IP_NF_MATCH_STRING_ENHANCE

struct dnshdr {
	__u16	id;
#if defined(__BIG_ENDIAN_BITFIELD)
	__u16	qr:1,
			opcode:4,
			aa:1,
			tc:1,
			rd:1,
			ra:1,
			reserced:3,
			rcode:4;
#elif defined(__LITTLE_ENDIAN_BITFIELD)
	__u16	rd:1,
			tc:1,
			aa:1,
			opcode:4,
			qr:1,
			rcode:4,
			reserced:3,
			ra:1;
#endif
	__u16	qdcount;
	__u16	ancount;
	__u16	nscount;
	__u16	arcount;
};

static int match_http_method(char *haystack, int hlen)
{
	if(strstr(haystack, "get")!=0 || strstr(haystack, "post")!=0 || strstr(haystack, "head")!=0
			|| strstr(haystack,"put")!=0 || strstr(haystack,"delete")!=0 || strstr(haystack, "options")!=0
			|| strstr(haystack,"trace")!=0 ||strstr(haystack,"connect")!=0)
	{
		dprintk("match_http_method match!\n");
		return 1;
	}
	return 0;
}
static char * get_one_query(char *string, int len, char * buffer, int bufflen)
{
	int i;

	for (i=0; i<len && i<bufflen; i++)
	{
		if (string[i] == '\0')	break;
		else					buffer[i] = string[i];
	}
	buffer[i]='\0';
	dprintk("get_one_query = %s\n", string);

	while (i < len && (string[i]=='\0')) i++;
	return &string[i];
}
static char * get_one_line(char *string, int len, char * buffer, int bufflen)
{
	int i;

	for (i=0; i<len && i<bufflen; i++)
	{
		if (string[i] == '\n' || string[i] == '\r')     break;
		else                                            buffer[i] = string[i];
	}
	buffer[i]='\0';
	while (i < len && (string[i]=='\r' || string[i]=='\n')) i++;
	return &string[i];
}
static int match_HTTP_REQ(char **haystack, int hlen)
{
	char *pend=(*haystack);
	char *pstart=(*haystack);//ponit to the http head
	char line[256];
	int line_len            =256;
	int data_len            = hlen;
	int data_line_len;
	int i;

	dprintk("match HTTP REQ -------->\n");
	dprintk("data_len=%d\n\n", data_len);
	if(data_len>16) //16 characters: "GET / HTTP/1.1\r\n"
	{
		memset(line,0,line_len);
		pend = get_one_line(pend, data_len, line, line_len);
		data_line_len = pend - pstart;
		data_len -= data_line_len;
		pstart = pend;
		dprintk("data_line_len=%d; data_len=%d\n", data_line_len,data_len);

		if(data_line_len > 12)  //12 characters: "GET HTTP/1.1"
		{
			for(i=0;i<line_len;i++) { if(line[i]>='A' && line[i]<='Z')line[i]+=32;  }

			return match_http_method(line, line_len);
			/*if(match_http_method(line, line_len))
			  {
				dprintk("found!\n");
				dprintk("match HTTP REQ <--------\n");
				return 1;
			  }
			*/
		}
	}
	dprintk("match HTTP REQ <--------\n");
	return 0;
}
static int match_DNS(char **queries, int qlen, int qcount, char *needle, int nlen)
{
	char	*pend		=(*queries);
	char	*pstart		=(*queries);
	char	buff[256];
	int		buff_len	= 256;
	int		cmp_qlen	= 0;
	int		i;
	
	unsigned int j;
	unsigned char * data;
	
	dprintk("match DNS -------->\n");
	for(i=0; i<qcount; i++)
	{
		qlen -= cmp_qlen;
		pend = get_one_query(pend, qlen, buff, buff_len);
		cmp_qlen = pend - pstart;
		
		dprintk("qlen=%d, pstart=%s, cmp_qlen=%d, \nneedle=%s, nlen=%d,\n pend-cmp_qlen=%s\n",
		qlen, pstart, cmp_qlen, needle, nlen, (char*)(pend-nlen-2));
		dprintk("cmp_qlen >= nlen %s \n", (cmp_qlen >= nlen?"TRUE":"FALSE"));
		dprintk("stncmp=%d\n", strncmp((char*)(pend-nlen-2), needle, nlen));
		data=(unsigned char *)(pend-nlen-2);
		dprintk("query in packet=");
		for(j=0;j<nlen;j++) dprintk("%02x ", data[j]);
		dprintk("\n");
		data=(unsigned char *)(needle);
		dprintk("needle         =");
		for(j=0;j<nlen;j++) dprintk("%02x ", data[j]);
		dprintk("\n");
		
		if (cmp_qlen >= nlen && (strncmp((char*)(pend-nlen-2), needle, nlen)==0))
		{
			dprintk("found!\n");
			dprintk("match DNS <--------\n");
			return 1;
		}
		pstart = pend;
	}
	dprintk("match DNS <--------\n");
	return 0;
}
static int match_URL(char **haystack, int hlen, char *needle, int nlen)
{
	char *pend=(*haystack);
	char *pstart=(*haystack);//ponit to the http head
	char *p_url_start;
	char url[512];
	char buff[256];
	char line[256];
	int url_len             =512;
	int buff_len            =256;
	int line_len            = 256;
	int data_len            = hlen;
	int data_line_len;
	int data_url_len        =0;
	int data_buff_len       =0;
	int i;

	dprintk("match URL -------->\n");
	if(data_len>16) //16 characters: "GET / HTTP/1.1\r\n"
	{
		dprintk("data_len=%d\n\n", data_len);
		memset(line,0,line_len);
		pend = get_one_line(pend, data_len, line, line_len);
		data_line_len = pend - pstart;
		data_len -= data_line_len;
		pstart = pend;
		if(data_line_len > 12)  //12 characters: "GET HTTP/1.1"
		{
			//dprintk("line before=%s\n", line);
			for(i=0;i<line_len;i++) { if(line[i]>='A' && line[i]<='Z')line[i]+=32;  }
			dprintk("line after =%s\n", line);
			if(match_http_method(line, line_len))
			{
				p_url_start=strstr(line," /");
				if(p_url_start!=0) p_url_start++;
				else return 0;

				memset(buff,0,buff_len);
				memset(url,0,url_len);
				i=0;
				while((p_url_start[i]!=' ') && (p_url_start[i]!='\0') && i<(buff_len-1))
				{
					buff[i]=p_url_start[i];
					i++;
				}
				buff[i]='\0';
				data_buff_len=i;
				
				dprintk("uri buff=%s, len=%d\n", buff, data_buff_len);
				if(strstr(buff, "http://")!=0)  // proxy case
				{
					for(i=0;i<data_buff_len;i++)
					{
						url[i]=buff[7+i];
					}
					url[i]='\0';
					data_url_len=i;
					dprintk("proxy case url=%s\n", url);
				}
				else
				{
					dprintk("data_len=%d\n", data_len);
					while(data_len>6)
					{
						memset(line,0,line_len);
						pend = get_one_line(pend, data_len, line, line_len);
						data_line_len = pend - pstart;
						data_len -= data_line_len;
						pstart = pend;

						for(i=0;i<line_len;i++) { if(line[i]>='A' && line[i]<='Z')line[i]+=32;  }
					
						if(strstr(line, "host: ")!=0)
						{
							dprintk("line =%s\n", line);
							p_url_start=strstr(line, "host: ");
							if(p_url_start!=0)      p_url_start+=6;
							else return 0;

							i=0;
							while((p_url_start[i]!=' ') && (p_url_start[i]!='\0'))
							{
								url[i]=p_url_start[i];
								i++;
							}
							data_url_len=i;
							for(i=0;i<data_buff_len;i++)
							{
								url[data_url_len+i]=buff[i];
							}
							url[data_url_len+i]='\0';
							data_url_len+=i-1;
							break;
						}
					}
				}
				dprintk("normal case url=%s, len=%d\n", url, data_url_len);
				dprintk("normal case needle=%s, len=%d\n", needle, nlen);
				if(data_url_len >= nlen)
				{
					for(i=0; i< nlen; i++){if(needle[i]>='A' && needle[i]<='Z') needle[i]+=32;}
					if(strstr(url, needle)!=0)
					{
						dprintk("found!\n");
						dprintk("match URL <--------\n");
						return 1;
					}
				}
			}
		}
	}
	dprintk("match URL <--------\n");
	return 0;
}

#endif

static int match(const struct sk_buff *skb,
		 const struct net_device *in,
		 const struct net_device *out,
		 const void *matchinfo,
		 int offset,
		 int *hotdrop)
{
	struct ts_state state;
	struct ipt_string_info *conf = (struct ipt_string_info *) matchinfo;
	int ret;
	struct iphdr *iph;
	struct tcphdr	*th,_tcph;
#ifdef CONFIG_IP_NF_MATCH_STRING_ENHANCE
	/* CONFIG_IP_NF_MATCH_STRING_ENHANCE is added by joanw */
	struct iphdr *ip	= skb->nh.iph;
	struct tcphdr *tcp	= (struct tcphdr *)((char *)ip+(ip->ihl*4));
	struct udphdr *udp  = (struct udphdr *)((char *)ip+(ip->ihl*4));
	struct dnshdr *dns;
	int hlen, nlen;
	int dnshdr_size=sizeof(struct dnshdr);
	char *needle, *haystack;
	unsigned int j;
	unsigned char * data;

	if(!ip) return 0;

	/* get lengths, and validate them */
	nlen = conf->patlen;
	hlen = ntohs(ip->tot_len)-(ip->ihl*4);
	if(nlen>hlen) return 0;

	needle = (char *)&conf->pattern;
	haystack = (char *)ip+(ip->ihl*4);
	if(conf->flags == IPT_URL_STRING)
	{
		hlen = ntohs(ip->tot_len)-(ip->ihl*4)-(tcp->doff*4);
		if(hlen>0)
		{
			dprintk("URL: tot_len=%d, ip_ihl=%d, doff=%d; hlen=%d\n",
					ntohs(ip->tot_len),(ip->ihl*4), (tcp->doff*4),hlen);
			haystack=(char *)tcp+(tcp->doff*4);
			return match_URL(&haystack,hlen, needle, nlen);
		}
		return 0;
	}
	else if(conf->flags == IPT_HTTP_REQ)
	{
		hlen=ntohs(ip->tot_len)-(ip->ihl*4)-(tcp->doff*4);
		if(hlen>0)
		{
			dprintk("HTTP_REQ: tot_len=%d, ip_ihl=%d, doff=%d; hlen=%d\n",
					ntohs(ip->tot_len), (ip->ihl*4),(tcp->doff*4),hlen);
			haystack=(char *)tcp+(tcp->doff*4);
			return match_HTTP_REQ(&haystack,hlen);
		}
		return 0;

	}
	else if(conf->flags == IPT_DNS_STRING)
	{
		dprintk("IPT_DNS_STRING\n");
		if (ntohs(udp->dest)==53) /* Destination port is "domain" */
		{
			hlen=ntohs(udp->len)-sizeof(udp);
			dprintk("needle=%s, nlen=%d\n", needle, nlen);
			dprintk("hlen=%d, dnshdr+nlen=%d\n", hlen, dnshdr_size+nlen);
			if (hlen < dnshdr_size+nlen)	return 0;
			
			dns=(struct dnshdr *)((char*)ip+(ip->ihl*4)+8);
			if(ntohs(dns->opcode)==0) /* DNS op code is query. */
			{
				dprintk("DNS: tot_len=%d, ip_ihl=%d, hlen=%d, dns dport=%d, dns len=%d, qdcount=%d\n",
				ntohs(ip->tot_len), (ip->ihl*4), hlen, ntohs(udp->dest), ntohs(udp->len),ntohs(dns->qdcount));
				haystack=(char *)dns + dnshdr_size;
#if 0
				data=(unsigned char *)udp;
				dprintk("udp packet=\n\t");
				for(j=0;j<8;j++) dprintk("%02x ", data[j]);		dprintk("\n\t");
				for(;j<16+8;j++) dprintk("%02x ", data[j]);		dprintk("\n\t");
				for(;j<hlen;j++) dprintk("%02x ", data[j]);		dprintk("\n\n");
#endif
				data=(unsigned char *)haystack;
				dprintk("dns header=\n\t");
				for(j=0;j<16;j++) dprintk("%02x ", data[j]);	dprintk("\n\t");
				for(;j<hlen;j++)  dprintk("%02x ", data[j]);	dprintk("\n");
				
				return match_DNS(&haystack,hlen, ntohs(dns->qdcount), needle, nlen);
			}
		}
	}
	return 0;
#else	
	memset(&state, 0, sizeof(struct ts_state));

	ret = (skb_find_text((struct sk_buff *)skb, conf->from_offset, 
			     conf->to_offset, conf->config, &state) 
			     != UINT_MAX) && !conf->invert;
#ifdef CONFIG_SL351x_NAT

	if(ret){		// string matched
		iph = skb->nh.iph;
		th = skb_header_pointer(skb, iph->ihl * 4,
				sizeof(_tcph), &_tcph);
		if((skb->nh.iph->protocol==IPPROTO_TCP) && (ntohs(th->dest) == 80)){
			url_block_len = ntohs(skb->nh.iph->tot_len) - (iph->ihl * 4) - (th->doff * 4);
			memcpy(block_url_info,skb->nh.iph,sizeof(struct iphdr)+sizeof(struct tcphdr));
			wake_up(&url_block_wait);
		}
	}
#endif
#endif
	return ret;
}

#define STRING_TEXT_PRIV(m) ((struct ipt_string_info *) m)

static int checkentry(const char *tablename,
		      const struct ipt_ip *ip,
		      void *matchinfo,
		      unsigned int matchsize,
		      unsigned int hook_mask)
{
	struct ipt_string_info *conf = matchinfo;
	struct ts_config *ts_conf;

#ifdef CONFIG_IP_NF_MATCH_STRING_ENHANCE
	if (conf->flags == IPT_URL_STRING || conf->flags == IPT_HTTP_REQ ||
			conf->flags == IPT_DNS_STRING)
		return 1;
#endif
			
	if (matchsize != IPT_ALIGN(sizeof(struct ipt_string_info)))
		return 0;

	/* Damn, can't handle this case properly with iptables... */
	if (conf->from_offset > conf->to_offset)
		return 0;

	ts_conf = textsearch_prepare(conf->algo, conf->pattern, conf->patlen,
				     GFP_KERNEL, TS_AUTOLOAD);
	if (IS_ERR(ts_conf))
		return 0;

	conf->config = ts_conf;

	return 1;
}

static void destroy(void *matchinfo, unsigned int matchsize)
{
#ifdef CONFIG_IP_NF_MATCH_STRING_ENHANCE
	struct ipt_string_info *conf = (struct ipt_string_info *) matchinfo;
	if (conf->flags != IPT_URL_STRING && conf->flags != IPT_HTTP_REQ &&
			conf->flags != IPT_DNS_STRING)
		textsearch_destroy(STRING_TEXT_PRIV(matchinfo)->config);
#else
	textsearch_destroy(STRING_TEXT_PRIV(matchinfo)->config);
#endif
}

static struct ipt_match string_match = {
	.name 		= "string",
	.match 		= match,
	.checkentry	= checkentry,
	.destroy 	= destroy,
	.me 		= THIS_MODULE
};

static int __init init(void)
{
	return ipt_register_match(&string_match);
}

static void __exit fini(void)
{
	ipt_unregister_match(&string_match);
}

module_init(init);
module_exit(fini);
