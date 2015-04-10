#include <sys/socket.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <net/if.h>
#include <errno.h>
#include "cli_cfg.h"
#include "sl_nat_cfg.h"

extern int cli_show_all_commands(CLICMD_T *cmd);
extern int nat_show_help_cmd(int argc, char ** argv);
static int nat_show_enable_cmd(int argc, char **argv);
static int nat_show_eth0_cmd(int argc, char **argv);
static int nat_show_eth1_cmd(int argc, char **argv);
static int nat_show_ip_cmd(int argc, char **argv);
static int nat_show_port_cmd(int argc, char **argv);
static int nat_show_weighting_cmd(int argc, char **argv);
static int nat_show_rule_cmd(int argc, char **argv);
static int nat_show_default_cmd(int argc, char **argv);

CLICMD_T nat_show_cmds[] = {
	{"?",		nat_show_help_cmd,  	"Help commands"},
	{"help", 	nat_show_help_cmd,  	"Help commands"},
	{"enable",     	nat_show_enable_cmd,   	"Show NAT enable function"},
	{"eth0",       	nat_show_eth0_cmd,	"Show NAT eht0 configurations"},
	{"eth1",       	nat_show_eth1_cmd,	"Show NAT eht1 configurations"},
	{"ip",         	nat_show_ip_cmd,	"Show all IP configurations"},
	{"port",       	nat_show_port_cmd,	"Show all port entries for NAS SW PORT List"},
	{"weighting",  	nat_show_weighting_cmd, "Show the weighting of all HW TxQ"},
	{"rule",       	nat_show_rule_cmd,	"Show all weighting rule of a specified Qid"},
	{"default",    	nat_show_default_cmd,	"Show the default HW TxQ"},    
	{0,0,0}
};


static char *protocol_msg[]= {
	"TCP",
	"UDP",
	"TCP AND UDP",
};

static char *devicename_msg[]= {
	"lan",
	"wan",
};


/*----------------------------------------------------------------------
* ROUTINE NAME - nat_show_enable_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: 
* INPUT      : int argc, char ** argv
* OUTPUT     : 0: SUCCESS 1:FAILED  
*----------------------------------------------------------------------*/
static int nat_show_enable_cmd( int argc, char ** argv)
{
	NAT_STATUS_T nat_status_lan, nat_status_wan;
	struct ifreq ifr;
	int s,ret;

	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
	{
		perror("socket");
		return 1;	
	}

	//sprintf(ifr.ifr_name, "eth%s", index);
	sprintf(ifr.ifr_name, "%s", "eth0");
	nat_status_lan.cmd = NATGSTATUS;
	nat_status_lan.len = sizeof(NAT_STATUS_T) - sizeof(NATCMD_HDR_T);
	ifr.ifr_data = (void *)&nat_status_lan;
	
	ret = ioctl(s, SIOCDEVLEPUS, &ifr) ;
	
    if (ret)
    {
		fprintf(stderr,"Invalid argument \n");
    	close(s);
		return ret;	
    }
	
	fprintf(stderr,"NAT Lan Status is %d\n",nat_status_lan.enable);

	sprintf(ifr.ifr_name, "%s", "eth1");
	nat_status_wan.cmd = NATGSTATUS;
	nat_status_wan.len = sizeof(NAT_STATUS_T) - sizeof(NATCMD_HDR_T);
	ifr.ifr_data = (void *)&nat_status_wan;
	
	ret = ioctl(s, SIOCDEVLEPUS, &ifr) ;


   	if (ret)
   	{
		fprintf(stderr,"Invalid argument \n");
   		close(s);
		return ret;	
   	}
   	close(s);
    
	
	fprintf(stderr,"NAT Wan Status is %d\n",nat_status_wan.enable);
	return 0;
}

/*----------------------------------------------------------------------
* ROUTINE NAME - nat_show_weighting_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: 
* INPUT      : int argc, char ** argv
* OUTPUT     :  0: SUCCESS 1:FAILED  
*----------------------------------------------------------------------*/
static int nat_show_weighting_cmd( int argc, char ** argv)
{
	struct ifreq ifr;
	int s;
	NAT_WEIGHT_T nat_weight ;
	int i,ret;
	
	s = socket(AF_INET, SOCK_DGRAM, 0);
   	if (s < 0)
   	{
		fprintf(stderr,"open socket fail\n");
   		return 1;
   	}
    
   	sprintf(ifr.ifr_name,"%s","eth1");
    nat_weight.cmd = NATGWEIGHT;
   	nat_weight.len = sizeof(NAT_WEIGHT_T) - sizeof(NATCMD_HDR_T);
	ifr.ifr_data = (void *)&nat_weight;
 
    ret = ioctl(s, SIOCDEVLEPUS, &ifr) ;
    	
    if (ret)
    {
		fprintf(stderr,"Invalid argument \n");
    	close(s);
		return ret;
    }
    close(s);
     
	fprintf(stderr,"Qid -- weighting value\n");
	
	for ( i = 0 ; i < CONFIG_NAT_TXQ_NUM ; i++)
	{
		fprintf(stderr,"%d -- %d \n",i+1, nat_weight.weight[i]);
	}
	
	return 0;
}


/*----------------------------------------------------------------------
* ROUTINE NAME - nat_show_default_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: 
* INPUT      : int argc, char ** argv
* OUTPUT     : 0: SUCCESS 1:FAILED   
*----------------------------------------------------------------------*/
static int nat_show_default_cmd( int argc, char ** argv)
{
	struct ifreq ifr;
	int s;
	NAT_QUEUE_T  nat_queue ;
	int ret;
	
	s = socket(AF_INET, SOCK_DGRAM, 0);
   	if (s < 0)
   	{
		fprintf(stderr,"open socket fail\n");
   		return 1;
   	}
    
   	sprintf(ifr.ifr_name, "%s" ,"eth1");
    nat_queue.cmd = NATGDEFQ;
   	nat_queue.len = sizeof(NAT_QUEUE_T) - sizeof(NATCMD_HDR_T);
	ifr.ifr_data = (void *)&nat_queue;
 
    ret = ioctl(s, SIOCDEVLEPUS, &ifr) ;
    	
    if (ret)
    {
		fprintf(stderr,"Invalid argument \n");
    	close(s);
		return ret;
    }
    
    close(s);
    
	fprintf(stderr,"NAT default HW TxQ is %d\n",nat_queue.qid+1);
	return 0;
}

/*----------------------------------------------------------------------
* ROUTINE NAME - nat_get_protocol_str
*-----------------------------------------------------------------------
* DESCRIPTION: 	To get the message of nat enabled flag
* INPUT      :	None
* OUTPUT     : 
*----------------------------------------------------------------------*/
char *nat_get_protocol_str(u_int32_t protocol)
{
	    
	if (protocol == 6)    
    		return ((char *)protocol_msg[0]);
    	else if (protocol == 17)
    		return ((char *)protocol_msg[1]);
    	else
		return ((char *)protocol_msg[2]);
}

/*----------------------------------------------------------------------
* ROUTINE NAME - nat_show_rule_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: 
* INPUT      : int argc, char ** argv
* OUTPUT     : 0: SUCCESS 1:FAILED    
*----------------------------------------------------------------------*/
static int nat_show_rule_cmd( int argc, char ** argv)
{
	struct ifreq ifr;
	int s;
	NAT_WRULE_ALL_T nat_rule_all;
	u_int32_t i,count ;
	u_int32_t total;
	u_int32_t qid;
	u_int32_t protocol;
	u_int32_t sip_start;
	u_int32_t sip_end;
	u_int32_t dip_start;
	u_int32_t dip_end;
	u_int16_t sport_start;
	u_int16_t sport_end;
	u_int16_t dport_start;
	u_int16_t dport_end;
		
	if (argc < 2)
	{
    		fprintf(stderr,"Syntax:  nat_cfg show rule qid(1-4)\n");
    		fprintf(stderr,"Example: nat_cfg show rule 4 \n");
    		return 1;
	}
	
    qid = atol(argv[1]) ;
    if (qid < 1 || qid > 4)
    {
    	fprintf(stderr," Qid is out of range !!\n");	
    	return 1;
    }
    	

	s = socket(AF_INET, SOCK_DGRAM, 0);
   	if (s < 0)
   	{
		fprintf(stderr,"open socket fail\n");
   		return 1;
   	}
    
   	sprintf(ifr.ifr_name, "%s","eth1");
    nat_rule_all.cmd = NATGWRULE;
   	nat_rule_all.len = sizeof(NAT_WRULE_ALL_T) - sizeof(NATCMD_HDR_T);
	nat_rule_all.total = qid-1 ;
	ifr.ifr_data = (void *)&nat_rule_all;
 
    ioctl(s, SIOCDEVLEPUS, &ifr) ;
    	
    if (errno	== 22)
    {
		fprintf(stderr,"Invalid argument \n");
    	close(s);
		return errno;
    }
    if (errno	== 7)
    {
		fprintf(stderr,"Entries is full \n");
    	close(s);
		return errno;
    }
    close(s);
  
	fprintf(stderr,"                          ================ Qid%d Weighting Rule ============== \n",qid);	
	fprintf(stderr,"ID Protocol     SourceIP      		           DestinationIP                       SourcePort           DestinationPort  \n");
	
	total = nat_rule_all.total;

	for (i=0,count=0 ; i <= CONFIG_NAT_MAX_WRULE && count < total; i++ ,count++)
	{
		char *str;
		char sips[32];
		char sipe[32];
		char dips[32];
		char dipe[32];
		
		protocol = nat_rule_all.entry[i].protocol ;
		sip_start = nat_rule_all.entry[i].sip_start ;
		sip_end = nat_rule_all.entry[i].sip_end ;
		dip_start = nat_rule_all.entry[i].dip_start ;
		dip_end = nat_rule_all.entry[i].dip_end ;
		sport_start = nat_rule_all.entry[i].sport_start ;
		sport_end = nat_rule_all.entry[i].sport_end ;
		dport_start = nat_rule_all.entry[i].dport_start ;
		dport_end = nat_rule_all.entry[i].dport_end ;
		
		str = nat_get_protocol_str(protocol);
		sprintf(sips,"%u.%u.%u.%u",IP3(sip_start),IP2(sip_start),IP1(sip_start),IP0(sip_start));
		sprintf(sipe,"%u.%u.%u.%u",IP3(sip_end),IP2(sip_end),IP1(sip_end),IP0(sip_end));
		sprintf(dips,"%u.%u.%u.%u",IP3(dip_start),IP2(dip_start),IP1(dip_start),IP0(dip_start));
		sprintf(dipe,"%u.%u.%u.%u",IP3(dip_end),IP2(dip_end),IP1(dip_end),IP0(dip_end));

		fprintf(stderr,"%d   %s      %15s-%15s      %15s-%15s       %5d-%5d          %5d-%5d \n",
		            i+1,str,sips,sipe,dips,dipe,sport_start,sport_end,
		                dport_start,dport_end);
	}
	
	return 0;
}

/*----------------------------------------------------------------------
* ROUTINE NAME - nat_show_eth0_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: 
* INPUT      : int argc, char ** argv
* OUTPUT     : 0: SUCCESS 1:FAILED 
*----------------------------------------------------------------------*/
static int nat_show_eth0_cmd( int argc, char ** argv)
{
	NAT_PORTCFG_T nat_port;
	struct ifreq ifr;
	int s, ret;

	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
	{
		perror("socket");
		return 1;
	}

	//sprintf(ifr.ifr_name, "eth%s", index);
	sprintf(ifr.ifr_name, "%s", "eth0");
	nat_port.cmd = NATGETPORT;
	nat_port.len = sizeof(NAT_PORTCFG_T) - sizeof(NATCMD_HDR_T);
	ifr.ifr_data = (void *)&nat_port;

    ret = ioctl(s, SIOCDEVLEPUS, &ifr) ;
    	
    if (ret)
    {
		fprintf(stderr,"Invalid argument \n");
    	close(s);
		return ret;
    }

    close(s);

	fprintf(stderr,"eth0 is %s port\n",devicename_msg[nat_port.portmap]);
	return 0;
}

/*----------------------------------------------------------------------
* ROUTINE NAME - nat_show_eth1_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: 
* INPUT      : int argc, char ** argv
* OUTPUT     : 0: SUCCESS 1:FAILED 
*----------------------------------------------------------------------*/
static int nat_show_eth1_cmd( int argc, char ** argv)
{
	NAT_PORTCFG_T nat_port;
	struct ifreq ifr;
	int s, ret;

	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
	{
		perror("socket");
		return 1;
	}

	//sprintf(ifr.ifr_name, "eth%s", index);
	sprintf(ifr.ifr_name, "%s", "eth1");
	nat_port.cmd = NATGETPORT;
	nat_port.len = sizeof(NAT_PORTCFG_T) - sizeof(NATCMD_HDR_T);
	ifr.ifr_data = (void *)&nat_port;

    ret = ioctl(s, SIOCDEVLEPUS, &ifr) ;
    	
    if (ret)
    {
		fprintf(stderr,"Invalid argument \n");
    	close(s);
		return ret;
    }

    close(s);
    
	fprintf(stderr,"eth1 is %s port\n",devicename_msg[nat_port.portmap]);
	return 0;
}

/*----------------------------------------------------------------------
* ROUTINE NAME - nat_show_ip_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: 
* INPUT      : int argc, char ** argv
* OUTPUT     : 0: SUCCESS 1:FAILED 
*----------------------------------------------------------------------*/
static int nat_show_ip_cmd( int argc, char ** argv)
{
	NAT_IPCFG_ALL_T ip_data_eth0,ip_data_eth1;
	struct ifreq ifr;
	int s;
	int ret;
	u_int32_t i,count ;
	u_int32_t total;
	u_int32_t ip, netmask;
	char ips[32];
	char netmasks[32];
	
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
	{
		fprintf(stderr,"open socket fail\n");
		return 1;
	}

	if (argc < 1)
	{
    		fprintf(stderr,"Example: nat_cfg show ip\n");
    		return 1;
	}

	sprintf(ifr.ifr_name, "%s", "eth0");
	ip_data_eth0.cmd = NATGETIP;
	ip_data_eth0.len = sizeof(NAT_IPCFG_ALL_T) - sizeof(NATCMD_HDR_T);
	ifr.ifr_data = (void *)&ip_data_eth0;
	
    ret = ioctl(s, SIOCDEVLEPUS, &ifr) ;
    	
	if (ret)
	{
	    fprintf(stderr,"Invalid argument \n");
	    close(s);
	    return ret;
	}

	fprintf(stderr,"devname \t IP \t Subnet Mask\n");
	
	total = ip_data_eth0.total;
	for (i=0,count=0 ; i <= CONFIG_NAT_MAX_IP_NUM && count < total; i++ ,count++)
	{
		
		ip = ip_data_eth0.entry[i].ipaddr ;
		netmask = ip_data_eth0.entry[i].netmask ;

		sprintf(ips,"%u.%u.%u.%u",IP3(ip),IP2(ip),IP1(ip),IP0(ip));
		sprintf(netmasks,"%u.%u.%u.%u",IP3(netmask),IP2(netmask),IP1(netmask),IP0(netmask));

		fprintf(stderr,"%s\t%15s\t%15s\n","eth0",ips,netmasks);
	}
	usleep(100);
	
	sprintf(ifr.ifr_name, "%s", "eth1");
	ip_data_eth1.cmd = NATGETIP;
	ip_data_eth1.len = sizeof(NAT_IPCFG_ALL_T) - sizeof(NATCMD_HDR_T);
	ifr.ifr_data = (void *)&ip_data_eth1;
	
    ret = ioctl(s, SIOCDEVLEPUS, &ifr) ;
    	
	if (ret)
	{
	    fprintf(stderr,"Invalid argument \n");
	    ret = close(s);
	    return ret;
	}
	
	total = ip_data_eth1.total;
	for (i=0,count=0 ; i <= CONFIG_NAT_MAX_IP_NUM && count < total; i++ ,count++)
	{
		
		ip = ip_data_eth1.entry[i].ipaddr ;
		netmask = ip_data_eth1.entry[i].netmask ;

		sprintf(ips,"%u.%u.%u.%u",IP3(ip),IP2(ip),IP1(ip),IP0(ip));
		sprintf(netmasks,"%u.%u.%u.%u",IP3(netmask),IP2(netmask),IP1(netmask),IP0(netmask));

		fprintf(stderr,"%s\t%15s\t%15s\n","eth1",ips,netmasks);
	}

	close(s);
	return 0;
}

/*----------------------------------------------------------------------
* ROUTINE NAME - nat_show_port_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: 
* INPUT      : int argc, char ** argv
* OUTPUT     : 0: SUCCESS 1:FAILED 
*----------------------------------------------------------------------*/
static int nat_show_port_cmd( int argc, char ** argv)
{
	struct ifreq ifr;
	int s;
	NAT_XPORT_ALL_T nat_port_all;
	u_int32_t i,count ;
	u_int32_t total;
	u_int32_t protocol;
	u_int16_t sport_start;
	u_int16_t sport_end;
	u_int16_t dport_start;
	u_int16_t dport_end;
	int ret;
		
	if (argc < 1)
	{
    		fprintf(stderr,"Syntax:  nat_cfg show port\n");
    		fprintf(stderr,"Example: nat_cfg show port\n");
    		return 1;
	}

	s = socket(AF_INET, SOCK_DGRAM, 0);
   	if (s < 0)
   	{
		fprintf(stderr,"open socket fail\n");
   		return 1;
   	}
    
   	sprintf(ifr.ifr_name, "eth1");
    nat_port_all.cmd = NATGXPORT;
   	nat_port_all.len = sizeof(NAT_XPORT_ALL_T) - sizeof(NATCMD_HDR_T);
	ifr.ifr_data = (void *)&nat_port_all;
 
    ret = ioctl(s, SIOCDEVLEPUS, &ifr) ;
    	
    if (errno == 22)
    {
		fprintf(stderr,"Invalid argument \n");
    	close(s);
		return errno;
    }
    if (errno == 7)
    {
		fprintf(stderr,"Entries is full \n");
    	close(s);
		return errno;
    }
    close(s);
  
	fprintf(stderr,"Protocol \t SourcePort \t DestinationPort  \n");
	
	total = nat_port_all.total;
	for (i=0,count=0 ; i <= CONFIG_NAT_MAX_XPORT && count < total; i++ ,count++)
	{
		char *str;
		
		protocol = nat_port_all.entry[i].protocol ;
		sport_start = nat_port_all.entry[i].sport_start ;
		sport_end = nat_port_all.entry[i].sport_end ;
		dport_start = nat_port_all.entry[i].dport_start ;
		dport_end = nat_port_all.entry[i].dport_end ;
		
		str = nat_get_protocol_str(protocol);
		fprintf(stderr,"%d   %s      %5d-%5d          %5d-%5d \n",
		            i+1,str,sport_start,sport_end,dport_start,dport_end);
	}
	
	return 0;
}
