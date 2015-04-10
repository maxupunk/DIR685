#include <sys/socket.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <net/if.h>
#include "cli_cfg.h"
#include "sl_nat_cfg.h"

extern int cli_show_all_commands(CLICMD_T *cmd);
extern int nat_set_help_cmd(int argc, char ** argv);

static int nat_set_enable_cmd(int argc, char ** argv);
static int nat_set_disable_cmd(int argc, char **argv);
static int nat_set_eth0_cmd(int argc, char **argv);
static int nat_set_eth1_cmd(int argc, char **argv);
static int nat_set_weighting_cmd(int argc, char **argv);
static int nat_set_default_cmd(int argc, char **argv);

CLICMD_T nat_set_cmds[] = {
    {"?",    	   nat_set_help_cmd,  	 "Help commands"},
    {"help", 	   nat_set_help_cmd,  	 "Help commands"},
    {"enable",     nat_set_enable_cmd,   "Enable NAT function"},
    {"disable",    nat_set_disable_cmd,	 "Disable NAT function"},
    {"eth0",       nat_set_eth0_cmd,	 "Set NAT eth0 configuration"},
    {"eth1",   	   nat_set_eth1_cmd,	 "Set NAT eth1 configuration"},
    {"weighting",  nat_set_weighting_cmd, "Set the weighting of all HW TxQ"},
    {"default",    nat_set_default_cmd,   "Set the default HW TxQ"},
    {0,0,0}
};  



/*----------------------------------------------------------------------
* ROUTINE NAME - nat_set_enable_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: Enable NAT command
* Syntax     : Set NAT enable 
* INPUT      : int argc, char ** argv
* OUTPUT     : 0: SUCCESS 1:FAILED  
*----------------------------------------------------------------------*/
static int nat_set_enable_cmd(int argc, char **argv)
{
	NAT_STATUS_T nat_status;
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
	nat_status.cmd = NATSSTATUS;
	nat_status.len = sizeof(NAT_STATUS_T) - sizeof(NATCMD_HDR_T);
	nat_status.enable = 1;
	ifr.ifr_data = (void *)&nat_status;

    ret = ioctl(s, SIOCDEVLEPUS, &ifr) ;
    	
	if (ret)
	{
	    fprintf(stderr,"Invalid argument \n");
	    close(s);
	    return ret;
	}
    	
	fprintf(stderr,"set eth0 enabled\n");
 
 	sprintf(ifr.ifr_name, "%s", "eth1");
	nat_status.cmd = NATSSTATUS;
	nat_status.len = sizeof(NAT_STATUS_T) - sizeof(NATCMD_HDR_T);
	nat_status.enable = 1;
	ifr.ifr_data = (void *)&nat_status;

    ret = ioctl(s, SIOCDEVLEPUS, &ifr) ;
    	
	if (ret)
	{
	    fprintf(stderr,"Invalid argument \n");
	    close(s);
	    return ret;
	}
    	
	fprintf(stderr,"set eth1 enabled\n");
   	
    close(s);
    return 0;
}

/*----------------------------------------------------------------------
* ROUTINE NAME - nat_set_disable_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: Disable NAT command
* Syntax     : Set NAT disable 
* INPUT      : int argc, char ** argv
* OUTPUT     : 0: SUCCESS 1:FAILED   
*----------------------------------------------------------------------*/
static int nat_set_disable_cmd(int argc, char **argv)
{
	NAT_STATUS_T nat_status;
	struct ifreq ifr;
	int s,ret;

	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
	{
		perror("socket");
		return 1;
	}

	//sprintf(ifr.ifr_name, "eth%s", index);
	sprintf(ifr.ifr_name, "%s", "eth1");
	nat_status.cmd = NATSSTATUS;
	nat_status.len = sizeof(NAT_STATUS_T) - sizeof(NATCMD_HDR_T);
	nat_status.enable = 0;
	ifr.ifr_data = (void *)&nat_status;

    ret = ioctl(s, SIOCDEVLEPUS, &ifr) ;
    	
	if (ret)
	{
	    fprintf(stderr,"Invalid argument \n");
	    close(s);
	    return ret;
	}

	fprintf(stderr,"set nat disabled\n");
    
    close(s);
    return 0;
}

/*----------------------------------------------------------------------
* ROUTINE NAME - nat_set_eth0_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: Set NAT eth0 portmap
* Syntax     : 
* INPUT      : int argc, char ** argv
* OUTPUT     : 0: SUCCESS 1:FAILED  
*----------------------------------------------------------------------*/
static int nat_set_eth0_cmd(int argc, char **argv)
{
	NAT_PORTCFG_T nat_port;
	struct ifreq ifr;
	int s,ret;
	
    if (argc < 2 )
    {
    	fprintf(stderr,"Syntax:  nat_cfg set eth0 port(lan or wan)\n");
    	fprintf(stderr,"Example: nat_cfg set eth0 lan\n");
    	return 1;
    }


	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
	{
		perror("socket");
		return 1;
	}

	//sprintf(ifr.ifr_name, "eth%s", index);
	sprintf(ifr.ifr_name, "%s", "eth0");
	nat_port.cmd = NATSETPORT;
	nat_port.len = sizeof(NAT_PORTCFG_T) - sizeof(NATCMD_HDR_T);
	
	if(strcmp(argv[1],"lan") == 0)
	    nat_port.portmap = 0;
	else if(strcmp(argv[1],"wan") == 0)
	    nat_port.portmap = 1;

	ifr.ifr_data = (void *)&nat_port;

    ret = ioctl(s, SIOCDEVLEPUS, &ifr) ;
    	
    if (ret)
    {
		fprintf(stderr,"Invalid argument \n");
    	close(s);
		return ret;
    }

	fprintf(stderr,"set nat %s eth0\n",argv[1]);
    
    close(s);
    return 0;
    	
}

/*----------------------------------------------------------------------
* ROUTINE NAME - nat_set_eth1_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: Set NAT eth1 portmap
* Syntax     : 
* INPUT      : int argc, char ** argv
* OUTPUT     : 0: SUCCESS 1:FAILED    
*----------------------------------------------------------------------*/
static int nat_set_eth1_cmd(int argc, char **argv)
{
	NAT_PORTCFG_T nat_port;
	struct ifreq ifr;
	int s,ret;
	
    if (argc < 2 )
    {
    	fprintf(stderr,"Syntax:  nat_cfg set eth1 port(lan or wan)\n");
    	fprintf(stderr,"Example: nat_cfg set eth1 wan\n");
    	return 1;
    }

	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
	{
		perror("socket");
		return 1;
	}

	//sprintf(ifr.ifr_name, "eth%s", index);
	sprintf(ifr.ifr_name, "%s", "eth1");
	nat_port.cmd = NATSETPORT;
	nat_port.len = sizeof(NAT_PORTCFG_T) - sizeof(NATCMD_HDR_T);

	if(strcmp(argv[1],"lan") == 0)
	    nat_port.portmap = 0;
	else if(strcmp(argv[1],"wan") == 0)
	    nat_port.portmap = 1;

	ifr.ifr_data = (void *)&nat_port;

    ret = ioctl(s, SIOCDEVLEPUS, &ifr) ;
    	
    if (ret)
    {
		fprintf(stderr,"Invalid argument \n");
    	close(s);
		return ret;
    }

	fprintf(stderr,"set nat %s eth1\n",argv[1]);
    
    close(s);
    return 0;
}

/*----------------------------------------------------------------------
* ROUTINE NAME - nat_set_weighting_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: Set NAT eth1 portmap
* Syntax     : 
* INPUT      : int argc, char ** argv
* OUTPUT     : 0: SUCCESS 1:FAILED    
*----------------------------------------------------------------------*/
static int nat_set_weighting_cmd(int argc, char **argv)
{
	NAT_WEIGHT_T nat_weight ;
	struct ifreq ifr;
	int s;
	u_int8_t weight1,weight2,weight3,weight4;
 	int i,ret;
    
    if (argc < 5 )
    {
    	fprintf(stderr,"Syntax:  nat_cfg set weighting qid1_value(1-63),qid2_value,qid3_value,qid4_value\n");
    	fprintf(stderr,"Example: nat_cfg set weighting 63 50 4 1 \n");
    	return 1;
    }
    	
	weight1 = atoi(argv[1]);
    if (weight1 > 63 || weight1 < 1 )
    {
    	fprintf(stderr,"qid1 weighting value is out of range (1-63) !! \n");
    	return 1;
    }
    
	weight2 = atoi(argv[2]);
    if (weight2 > 63 || weight2 < 1 )
    {
    	fprintf(stderr,"qid2 weighting value is out of range (1-63) !! \n");
    	return 1;
    }

	weight3 = atoi(argv[3]);
    if (weight3 > 63 || weight3 < 1 )
    {
    	fprintf(stderr,"qid3 weighting value is out of range (1-63) !! \n");
    	return 1;
    }

	weight4 = atoi(argv[4]);
    if (weight4 > 63 || weight4 < 1 )
    {
    	fprintf(stderr,"qid4 weighting value is out of range (1-63) !! \n");
    	return 1;
    }
	
	for ( i=0 ; i<2 ; i++)
	{
		s = socket(AF_INET, SOCK_DGRAM, 0);
    	if (s < 0)
    	{
			fprintf(stderr,"open socket fail\n");
    		return 1;
    	}
    
    	sprintf(ifr.ifr_name, "eth%d",i);
    	nat_weight.cmd = NATSWEIGHT;
    	nat_weight.len = sizeof(NAT_WEIGHT_T) - sizeof(NATCMD_HDR_T);
    	nat_weight.weight[0] = weight1 ;
    	nat_weight.weight[1] = weight2 ;
    	nat_weight.weight[2] = weight3 ;
    	nat_weight.weight[3] = weight4 ;
		ifr.ifr_data = (void *)&nat_weight;
 
    	ret = ioctl(s, SIOCDEVLEPUS, &ifr) ;
    		
    	if (ret)
    	{
			fprintf(stderr,"Invalid argument \n");
    		close(s);
			return ret;
    	}
    	close(s);
	}
   	return 0;
}

/*----------------------------------------------------------------------
* ROUTINE NAME - nat_set_default_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: Set NAT eth1 portmap
* Syntax     : 
* INPUT      : int argc, char ** argv
* OUTPUT     : 0: SUCCESS 1:FAILED   
*----------------------------------------------------------------------*/
static int nat_set_default_cmd(int argc, char **argv)
{
	NAT_QUEUE_T  nat_queue ;
	struct ifreq ifr;
	int s;
	u_int8_t qid ;
    int i,ret;
    
   	if (argc < 2 )
    {
    	fprintf(stderr,"Syntax:  nat_cfg set default qid(1-4)\n");
    	fprintf(stderr,"Example: nat_cfg set default 2 \n");
    	return 1;
    }
    	
    qid = atoi(argv[1]) ;
    if ( qid > 4 || qid < 1)
    {
    	fprintf(stderr,"qid is out of range(1-4) !! \n");
    	return 1;
   	}	
    	
	for ( i=0 ; i<2 ; i++)
	{
		s = socket(AF_INET, SOCK_DGRAM, 0);
    	if (s < 0)
    	{
			fprintf(stderr,"open socket fail\n");
    		return 1;
    	}
    
    	sprintf(ifr.ifr_name, "eth%d",i);
    	nat_queue.cmd = NATSDEFQ;
    	nat_queue.len = sizeof(NAT_QUEUE_T) - sizeof(NATCMD_HDR_T);
    	nat_queue.qid = qid-1 ;
		ifr.ifr_data = (void *)&nat_queue;
 
    	ret = ioctl(s, SIOCDEVLEPUS, &ifr) ;
    		
    	if (ret)
    	{
			fprintf(stderr,"Invalid argument \n");
    		close(s);
			return ret;
    	}
    	close(s);
	}
   	return 0;
}
