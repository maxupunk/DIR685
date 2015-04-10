#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "cli_cfg.h"
#include "sl_nat_cfg.h"

extern int cli_show_all_commands(CLICMD_T *cmd);
extern int nat_add_help_cmd(int argc, char ** argv);
int nat_add_ip_cmd(int argc, char **argv);
int nat_add_port_cmd(int argc, char **argv);
int nat_add_rule_cmd(int argc, char **argv);

CLICMD_T nat_add_cmds[] = {
    {"?",    	   nat_add_help_cmd,  	"Help commands"},
    {"help", 	   nat_add_help_cmd,  	"Help commands"},
    {"ip",     	   nat_add_ip_cmd,  	"Add a IP configuration"},
    {"port",       nat_add_port_cmd,	"Add a TCP/UDP port entry from NAT SW PORT lists"},
    {"rule",       nat_add_rule_cmd,	"Add a weighting rule to a specified TxQ"},
    {0,0,0}
};





/*----------------------------------------------------------------------
* ROUTINE NAME - nat_add_rule_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: 
* INPUT      : int argc, char ** argv
* OUTPUT     : 0: SUCCESS 1:FAILED  
*----------------------------------------------------------------------*/
int nat_add_rule_cmd( int argc, char ** argv)
{
	NAT_WRULE_T nat_rule ;
	struct ifreq ifr;
	int s;
	u_int32_t qid;
	u_int32_t protocol;
	u_int32_t ip1,ip2,ip3,ip4;
	u_int32_t sip_start;
	u_int32_t sip_end;
	u_int32_t dip_start;
	u_int32_t dip_end;
	u_int16_t sport_start;
	u_int16_t sport_end;
	u_int16_t dport_start;
	u_int16_t dport_end;

	if (argc < 11)
	{
    	fprintf(stderr,"Syntax:  nat_cfg add rule qid(1-4) protocol(tcp/udp) sips sipe dips dipe sports(1-65535) sporte dports dporte \n");
    	fprintf(stderr,"Example: nat_cfg add rule 1 tcp 192.168.2.1 192.168.2.100 200.2.2.1 200.2.2.100 1 65535 1 65535 \n");
    	return 1;
	}	  
//qid
    qid = atol(argv[1]) ;
    if (qid < 1 || qid >4)
    {
    	fprintf(stderr," Qid is out of range !!\n");	
    	return 1;
	}
//protocol
	if (strcmp(argv[2],"udp")==0)
		protocol = PROTOCOL_UDP;
	else
		protocol = PROTOCOL_TCP;

//source ip start
	if (sscanf(argv[3] ,"%u.%u.%u.%u",&ip1,&ip2,&ip3,&ip4)==4)
		sip_start=IPIV(ip1,ip2,ip3,ip4);
	else
    {
    	if(strcmp(argv[3],"0")==0)
    		sip_start = 0;
    	else
    	{
    		fprintf(stderr,"Error Source IP Start !!\n");	
    		return 1;
    	}
	}
//source ip end
	if (sscanf(argv[4] ,"%u.%u.%u.%u",&ip1,&ip2,&ip3,&ip4)==4)
		sip_end=IPIV(ip1,ip2,ip3,ip4);
	else
   	{
   		if(strcmp(argv[4],"0")==0)
   			sip_end = 0 ;
   		else
   		{
   			fprintf(stderr,"Error Source IP End!!\n");	
   			return 1;
   		}
	}
//destination IP start
	if (sscanf(argv[5] ,"%u.%u.%u.%u",&ip1,&ip2,&ip3,&ip4)==4)
		dip_start=IPIV(ip1,ip2,ip3,ip4);
	else
    {
    	if(strcmp(argv[5],"0")==0)
    		dip_start = 0 ;
    	else
    	{
    		fprintf(stderr,"Error Destination IP Start!!\n");	
    		return 1;
    	}
	}
//destination IP end
	if (sscanf(argv[6] ,"%u.%u.%u.%u",&ip1,&ip2,&ip3,&ip4)==4)
		dip_end=IPIV(ip1,ip2,ip3,ip4);
	else
    {
    	if(strcmp(argv[6],"0")==0)
    		dip_end = 0 ;
    	else
    	{
    		fprintf(stderr,"Error Destination IP End!!\n");	
    		return 1;
    	}
	}
//source port start		
    sport_start = atoi(argv[7]) ;
//source port end		
    sport_end = atoi(argv[8]) ;
//destination port start		
    dport_start = atoi(argv[9]) ;
//destination port end		
    dport_end = atoi(argv[10]) ;

	nat_rule.qid = qid-1 ;
	nat_rule.entry.protocol = protocol;
	nat_rule.entry.sip_start = sip_start;
	nat_rule.entry.sip_end = sip_end;
	nat_rule.entry.dip_start = dip_start;
	nat_rule.entry.dip_end = dip_end;
	nat_rule.entry.sport_start = sport_start;
	nat_rule.entry.sport_end = sport_end;
	nat_rule.entry.dport_start = dport_start;
	nat_rule.entry.dport_end = dport_end;

	s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0)
    {
		fprintf(stderr,"open socket fail\n");
    	return 1;
    }
    
    sprintf(ifr.ifr_name, "eth1");
    nat_rule.cmd = NATAWRULE;
    nat_rule.len = sizeof(NAT_WRULE_T) - sizeof(NATCMD_HDR_T);
	ifr.ifr_data = (void *)&nat_rule;
 
    ioctl(s, SIOCDEVLEPUS, &ifr) ;
    		
	if (errno == 22)
    {
		fprintf(stderr,"Invalid argument \n");
    	close(s);
		return errno;
    }
    if (errno == 7)
    {
		fprintf(stderr,"Entries is full a\n");
    	close(s);
		return 22;
    }
    close(s);

   	
	return 0;
}

/*----------------------------------------------------------------------
* ROUTINE NAME - nat_add_ip_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: 
* INPUT      : int argc, char ** argv
* OUTPUT     : 0: SUCCESS 1:FAILED  
*----------------------------------------------------------------------*/
int nat_add_ip_cmd( int argc, char ** argv)
{
	NAT_IPCFG_T ip_data;
	struct ifreq ifr;
	int s;
	u_int32_t ip, netmask;
	u_int32_t ip1,ip2,ip3,ip4;
	
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
	{
		fprintf(stderr,"open socket fail\n");
		return 1;
	}

	if (argc < 4)
	{
    	fprintf(stderr,"Syntax:  nat_cfg add ip device_Name(eth0 eth1) IP Subnet_Mask(255.255.255.0)\n");
    	fprintf(stderr,"Example: nat_cfg add ip eth1 192.168.1.200 255.255.255.0\n");
    	return 1;
	}	  

//Device Name
	if (!strcmp(argv[1],"eth0")==0 && !strcmp(argv[1],"eth1")==0)
	{
		fprintf(stderr,"Error Device Name!!\n");
		return 1;
	}

//IP
	if (sscanf(argv[2] ,"%u.%u.%u.%u",&ip1,&ip2,&ip3,&ip4)==4)
		ip=IPIV(ip1,ip2,ip3,ip4);
	else
    {
    	fprintf(stderr,"Error IP!!\n");	
    	return 1;
	}
//Subnet Mask
	if (sscanf(argv[3] ,"%u.%u.%u.%u",&ip1,&ip2,&ip3,&ip4)==4)
		netmask=IPIV(ip1,ip2,ip3,ip4);
	else
    {
    	fprintf(stderr,"Error Subnet Mask!!\n");	
    	return 1;
	}

	sprintf(ifr.ifr_name, "%s", argv[1]);
	ip_data.cmd = NATADDIP;
	ip_data.len = sizeof(NAT_IPCFG_T) - sizeof(NATCMD_HDR_T);
	ip_data.entry.ipaddr = ip;
	ip_data.entry.netmask = netmask;
	ifr.ifr_data = (void *)&ip_data;
	
    ioctl(s, SIOCDEVLEPUS, &ifr) ;
    	
    	
	if (errno == 22)
	{
	    fprintf(stderr,"Invalid argument\n");
	    close(s);
	    return errno;
	}

	if (errno == 7)
	{
	    fprintf(stderr,"Too many IP(configuration is full)\n");
	    close(s);
	    return errno;
	}
	    	
    close(s);
	return 0;
}

/*----------------------------------------------------------------------
* ROUTINE NAME - nat_add_port_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: 
* INPUT      : int argc, char ** argv
* OUTPUT     : 0: SUCCESS 1:FAILED  
*----------------------------------------------------------------------*/
int nat_add_port_cmd( int argc, char ** argv)
{
	NAT_XPORT_T nat_port ;
	struct ifreq ifr;
	int s;
	u_int32_t protocol;
	u_int16_t sport_start;
	u_int16_t sport_end;
	u_int16_t dport_start;
	u_int16_t dport_end;

	if (argc < 6)
	{
    	fprintf(stderr,"Syntax:  nat_cfg add port protocol(tcp/udp/both) sports(1-65535) sporte dports dporte \n");
    	fprintf(stderr,"Example: nat_cfg add port tcp 1 65535 1 65535 \n");
    	return 1;
	}

//protocol
	if (strcmp(argv[1],"tcp")==0)
		protocol = PROTOCOL_TCP;
	else if (strcmp(argv[1],"udp")==0)
		protocol = PROTOCOL_UDP;
	else
		protocol = PROTOCOL_TCP_AND_UDP;
		

//source port start		
    sport_start = atoi(argv[2]) ;
//source port end		
   	sport_end = atoi(argv[3]) ;
//destination port start		
    dport_start = atoi(argv[4]) ;
//destination port end		
    dport_end = atoi(argv[5]) ;

	nat_port.entry.protocol = protocol;
	nat_port.entry.sport_start = sport_start;
	nat_port.entry.sport_end = sport_end;
	nat_port.entry.dport_start = dport_start;
	nat_port.entry.dport_end = dport_end;

	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
	{
		fprintf(stderr,"open socket fail\n");
		return 1;
	}

	sprintf(ifr.ifr_name, "eth0");
	nat_port.cmd = NATAXPORT;
	nat_port.len = sizeof(NAT_XPORT_T) - sizeof(NATCMD_HDR_T);
	ifr.ifr_data = (void *)&nat_port;

	ioctl(s, SIOCDEVLEPUS, &ifr) ;
	
    if (errno == 22)
	{
		fprintf(stderr,"Invalid argument \n");
		close(s);
		return errno;
	}
	if (errno == 7)
	{
		fprintf(stderr,"Too many entries(port list is full)\n");
		close(s);
		return errno;
	}
	close(s);
   	
	return 0;
}
