#!/bin/sh
echo [$0] ... > /dev/console
<? /* vi: set sw=4 ts=4: */
require("/etc/templates/troot.php");

/* detect interface */
$WANDEV = query("/runtime/wan/inf:1/interface");
$H_LANDEV = query("/runtime/layout/lanif");
$G_LANDEV = query("/runtime/layout/lanif2");
$gzone_enable = query("/gzone/enable");
$wan_up = query("/runtime/wan/inf:1/connectstatus");
echo "echo -n Interface is wanif=".$WANDEV." lanif=".$H_LANDEV." \n";
if 		( $WANDEV=="" || $H_LANDEV=="" ){ echo "echo ... Interface Error!!! \n";exit; }
else if ( $gzone_enable=="1" && $G_LANDEV=="" ) { echo "echo ... Guest Zone Interface Error!!! \n";exit; }
else 	{ echo "echo ... OK \n"; }

/* tc debug */
$TC="echo tc";
$TC="tc";
$K=kbps;
$K=kbit;
$layer7_mark_chain="POST_L7";

/* main */
if ($generate_start==1)
{
	echo "echo Start QOS system ... \n";
	if($wan_up!="connected")
	{
		echo "echo WAN is down!\n";
		exit;
	}
	/* process node */
	$QOS_ENABLE  = query("/qos/mode");
	$UPSTREAM    = query("/qos/bandwidth/upstream");
	$DOWNSTREAM  = query("/qos/bandwidth/downstream");
	echo "echo QOS=".$QOS_ENABLE." UPSTREAM=".$UPSTREAM." DOWNSTREAM=".$DOWNSTREAM." \n";
	if ( $DOWNSTREAM==0 || $DOWNSTREAM=="" ){ $DOWNSTREAM=102400; }
	if ( $UPSTREAM==0   || $UPSTREAM==""   ){ $UPSTREAM=102400; }
	if ( $QOS_ENABLE!=1 && $QOS_ENABLE!=2 ){ echo "echo QOS is disabled. \n";exit; }

	/*----------------------------------------------------------------------------*/
	/* WAN (uplink) */
	$PRIO_ALL=$UPSTREAM ;
	//calculating relative root r2q and root class quantum
	//default quantum with default rfq = 10, quantum = rate/r2q
	$CLASS_QUAN = $PRIO_ALL / 10 ; 
	if( $CLASS_QUAN < 12 ) //minimum quantum should be at least max packet size: 1500byte = 1.5kbyte = 12 kbit
	{
		//quantum below minimum, but can be solved through reducing r2q from default
		$r2q = 1;
	}
	else if( $CLASS_QUAN > 480 ) //maximum quantum should be less than 60000byte = 60 kbyte = 480 kbit
	{
		//quantum above maximum, should increase r2q value to bring down quantum value
		$r2q_value = $PRIO_ALL / 480 ; // 100 * 480
		$r2q_value = $r2q_value + 1;
		$r2q = $r2q_value;
	}
	else
	{
		$r2q = 10;
	}
	
	// ceil for classes
	$PRIO0_MAX=$PRIO_ALL * 90 / 100 ; 	//ack
	$PRIO1_MAX=$PRIO_ALL * 90 / 100 ; 	//short/voice
	$PRIO2_MAX=$PRIO_ALL * 80 / 100 ;	//video
	$PRIO3_MAX=$PRIO_ALL * 80 / 100 ;	//normal/http
	$PRIO4_MAX=$PRIO_ALL * 70 / 100 ;	//ftp,http file
	$PRIO5_MAX=$PRIO_ALL * 70 / 100 ;	//BT,P2P
	
	// rate for classes
	$PRIO0_MIN=$PRIO_ALL * 17 / 100 ;
	$PRIO1_MIN=$PRIO_ALL * 15 / 100 ;
	$PRIO2_MIN=$PRIO_ALL * 12 / 100 ;
	$PRIO3_MIN=$PRIO_ALL * 10 / 100 ;
	$PRIO4_MIN=$PRIO_ALL * 7 / 100 ;
	$PRIO5_MIN=$PRIO_ALL * 5 / 100 ;
	
	// make sure quantum doesn't drop below 1500
	$quant0 = "";
	$quant1 = "";
	$quant2 = "";
	$quant3 = "";
	$quant4 = "";
	$quant5 = "";
	$quantum = $PRIO0_MIN / $r2q;
	if($quantum < 12)	{ $quant0 = "quantum 1500 "; }
	$quantum = $PRIO1_MIN / $r2q;
	if($quantum < 12)	{ $quant1 = "quantum 1500 "; }
	$quantum = $PRIO2_MIN / $r2q;
	if($quantum < 12)	{ $quant2 = "quantum 1500 "; }
	$quantum = $PRIO3_MIN / $r2q;
	if($quantum < 12)	{ $quant3 = "quantum 1500 "; }
	$quantum = $PRIO4_MIN / $r2q;
	if($quantum < 12)	{ $quant4 = "quantum 1500 "; }
	$quantum = $PRIO5_MIN / $r2q;
	if($quantum < 12)	{ $quant5 = "quantum 1500 "; }
	
/*	The empty class is no longer necessary, since it will be done by default with htb 	*/
/*	$PRIO6_MIN=$PRIO_ALL * 30 / 100 ; 	*/

	// default 3 where all the normal packets go
	echo $TC." qdisc add dev ".$WANDEV." handle 1: root htb r2q ".$r2q." default 15 \n";
	echo $TC." class add dev ".$WANDEV." parent 1: classid 1:1 htb rate ".$PRIO_ALL.$K." ceil ".$PRIO_ALL.$K." \n";
	// lower prio means its packet well be send first and it can borrow bandwidth before other classes
	echo $TC." class add dev ".$WANDEV." parent 1:1 classid 1:10 htb prio 0  rate ".$PRIO0_MIN.$K." ceil ".$PRIO0_MAX.$K." ".$quant0."burst 50k cburst 50k \n";
	echo $TC." class add dev ".$WANDEV." parent 1:1 classid 1:11 htb prio 1  rate ".$PRIO1_MIN.$K." ceil ".$PRIO1_MAX.$K." ".$quant1."burst 50k cburst 50k \n";
	echo $TC." class add dev ".$WANDEV." parent 1:1 classid 1:12 htb prio 2  rate ".$PRIO2_MIN.$K." ceil ".$PRIO2_MAX.$K." ".$quant2."burst 50k cburst 50k \n";
	echo $TC." class add dev ".$WANDEV." parent 1:1 classid 1:13 htb prio 3  rate ".$PRIO3_MIN.$K." ceil ".$PRIO3_MAX.$K." ".$quant3."\n";
	echo $TC." class add dev ".$WANDEV." parent 1:1 classid 1:14 htb prio 4  rate ".$PRIO4_MIN.$K." ceil ".$PRIO4_MAX.$K." ".$quant4."\n";
	echo $TC." class add dev ".$WANDEV." parent 1:1 classid 1:15 htb prio 5  rate ".$PRIO5_MIN.$K." ceil ".$PRIO5_MAX.$K." ".$quant5."\n";
/*	echo $TC." class add dev ".$WANDEV." parent 1:1 classid 1:16 htb prio 6  rate ".$PRIO6_MIN.$K." ceil ".$PRIO6_MAX.$K." \n"; 	*/
	echo $TC." qdisc add dev ".$WANDEV." parent 1:10 handle 100: pfifo limit 10 \n";
	echo $TC." qdisc add dev ".$WANDEV." parent 1:11 handle 110: pfifo limit 20 \n";
	echo $TC." qdisc add dev ".$WANDEV." parent 1:12 handle 120: pfifo limit 30 \n";
	echo $TC." qdisc add dev ".$WANDEV." parent 1:13 handle 130: pfifo limit 40 \n";
	echo $TC." qdisc add dev ".$WANDEV." parent 1:14 handle 140: pfifo limit 30 \n";
	echo $TC." qdisc add dev ".$WANDEV." parent 1:15 handle 150: pfifo limit 20 \n";
/*	echo $TC." qdisc add dev ".$WANDEV." parent 1:16 handle 160: pfifo limit 2 \n"; 	*/
	/*----------------------------------------------------------------------------*/

	/*----------------------------------------------------------------------------*/
	//match ack bit and packet size smaller than 64 not include 64
	echo $TC." filter add dev ".$WANDEV." parent 1: protocol ip prio 2 u32 match ip protocol 6 0xff match u8 0x05 0x0f at 0 match u16 0x0000 0xffc0 at 2 match u8 0x10 0x10 at 33 flowid 1:10 \n"; 
	
	//voip and also match udp packet with size smaller than 128 not include 128
	echo $TC." filter add dev ".$WANDEV." parent 1: protocol ip prio 1 handle 11 fw classid 1:11 \n"; 
	echo $TC." filter add dev ".$WANDEV." parent 1: protocol ip prio 2 u32 match ip protocol 17 0xff match u8 0x05 0x0f at 0 match u16 0x0000 0xff80 at 2 flowid 1:11 \n"; 
	
	//video
	echo $TC." filter add dev ".$WANDEV." parent 1: protocol ip prio 1 handle 12 fw classid 1:12 \n"; 	
	
	//match http port
	echo $TC." filter add dev ".$WANDEV." parent 1: protocol ip prio 2 u32 match ip dport 80 0xffff flowid 1:13 \n"; 
	
	//ftp and file transfer
	echo $TC." filter add dev ".$WANDEV." parent 1: protocol ip prio 1 handle 14 fw classid 1:14 \n"; 
	
	//bt,p2p
	echo $TC." filter add dev ".$WANDEV." parent 1: protocol ip prio 1 handle 15 fw classid 1:15 \n"; 
	

	//the rest of the ip packets
	echo $TC." filter add dev ".$WANDEV." parent 1: protocol ip prio 100 u32  match ip dst 0.0.0.0/0 flowid 1:13 \n";
	/*----------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------------*/
	/* Host Zone LAN(downlink) */
	//reserve 10% for guest zone if it is enabled
	if ( $gzone_enable=="1" ) 	{ $PRIO_ALL=$DOWNSTREAM * 90 / 100; }
	else 						{ $PRIO_ALL=$DOWNSTREAM; }
	
	//calculating relative root r2q and root class quantum
	//default quantum with default rfq = 10, quantum = rate/r2q
	$CLASS_QUAN = $PRIO_ALL / 10 ; 
	if( $CLASS_QUAN < 12 ) //minimum quantum should be at least max packet size: 1500byte = 1.5kbyte = 12 kbit
	{
		//quantum below minimum, but can be solved through reducing r2q from default
		$r2q = 1;
	}
	else if( $CLASS_QUAN > 480 ) //maximum quantum should be less than 60000byte = 60 kbyte = 480 kbit
	{
		//quantum above maximum, should increase r2q value to bring down quantum value
		$r2q_value = $PRIO_ALL / 480 ; // 100 * 480
		$r2q_value = $r2q_value + 1;
		$r2q = $r2q_value;
	}
	else
	{
		$r2q = 10;
	}
	
	$PRIO0_MAX=$PRIO_ALL * 100 / 100 ; 	//reserved, http, dhcp, msn, mail, ftp, SIP...etc.
	$PRIO1_MAX=$PRIO_ALL * 90 / 100 ; 	//non-specified
	
	$PRIO0_MIN=$PRIO_ALL * 30 / 100 ;
	$PRIO1_MIN=$PRIO_ALL * 15 / 100 ;	
	$quantum = $PRIO0_MIN / $r2q;
	if($quantum < 12)	{ $quant0 = "quantum 1500 "; }
	else 				{ $quant0 = ""; }
	$quantum = $PRIO1_MIN / $r2q;
	if($quantum < 12)	{ $quant1 = "quantum 1500 "; }
	else 				{ $quant1 = ""; }
/*	The empty class is no longer necessary, since it will be done by default with htb 	*/
/*	$PRIO2_MIN=$PRIO_ALL * 76 / 100 ; 	*/
	
	echo $TC." qdisc add dev ".$H_LANDEV." handle 2: root htb r2q ".$r2q." default 21 \n";
	echo $TC." class add dev ".$H_LANDEV." parent 2: classid 2:2 htb rate ".$PRIO_ALL.$K." ceil ".$PRIO_ALL.$K." \n";
	
	echo $TC." class add dev ".$H_LANDEV." parent 2:2 classid 2:20 htb prio 0  rate ".$PRIO0_MIN.$K." ceil ".$PRIO0_MAX.$K." ".$quant0."burst 50k cburst 50k \n";
	echo $TC." class add dev ".$H_LANDEV." parent 2:2 classid 2:21 htb prio 1  rate ".$PRIO1_MIN.$K." ceil ".$PRIO1_MAX.$K." ".$quant1."\n";
	echo $TC." qdisc add dev ".$H_LANDEV." parent 2:20 handle 200: pfifo limit 50 \n";
	echo $TC." qdisc add dev ".$H_LANDEV." parent 2:21 handle 210: pfifo limit 20 \n";

	echo $TC." filter add dev ".$H_LANDEV." parent 2: protocol ip prio 1 u32 match ip protocol 6 0xff match ip sport 53 0xffff flowid 2:20 \n"; 	//DHCP
	echo $TC." filter add dev ".$H_LANDEV." parent 2: protocol ip prio 1 u32 match ip protocol 6 0xff match ip sport 80 0xffff flowid 2:20 \n"; 	//HTTP
	echo $TC." filter add dev ".$H_LANDEV." parent 2: protocol ip prio 1 u32 match ip protocol 6 0xff match ip sport 443 0xffff flowid 2:20 \n"; 	//HTTPS
	echo $TC." filter add dev ".$H_LANDEV." parent 2: protocol ip prio 1 u32 match ip protocol 6 0xff match ip sport 21 0xffff flowid 2:20 \n"; 	//FTP
	echo $TC." filter add dev ".$H_LANDEV." parent 2: protocol ip prio 1 u32 match ip protocol 6 0xff match ip sport 990 0xffff flowid 2:20 \n"; 	//FTPS
	echo $TC." filter add dev ".$H_LANDEV." parent 2: protocol ip prio 1 u32 match ip protocol 6 0xff match ip sport 25 0xffff flowid 2:20 \n"; 	//SMTP
	echo $TC." filter add dev ".$H_LANDEV." parent 2: protocol ip prio 1 u32 match ip protocol 6 0xff match ip sport 587 0xffff flowid 2:20 \n"; 	//SMTP submission
	echo $TC." filter add dev ".$H_LANDEV." parent 2: protocol ip prio 1 u32 match ip protocol 6 0xff match ip sport 110 0xffff flowid 2:20 \n"; 	//POP3
	echo $TC." filter add dev ".$H_LANDEV." parent 2: protocol ip prio 1 u32 match ip protocol 6 0xff match ip sport 995 0xffff flowid 2:20 \n"; 	//POP3S
	echo $TC." filter add dev ".$H_LANDEV." parent 2: protocol ip prio 1 u32 match ip protocol 6 0xff match ip sport 1863 0xffff flowid 2:20 \n"; 	//MSNP
	echo $TC." filter add dev ".$H_LANDEV." parent 2: protocol ip prio 1 u32 match ip protocol 6 0xff match ip sport 5060 0xffff flowid 2:20 \n"; 	//SIP(TCP)
	echo $TC." filter add dev ".$H_LANDEV." parent 2: protocol ip prio 1 u32 match ip protocol 17 0xff match ip sport 5060 0xffff flowid 2:20 \n"; 	//SIP(UDP)
	echo $TC." filter add dev ".$H_LANDEV." parent 2: protocol ip prio 100 u32  match ip dst 0.0.0.0/0 flowid 2:21 \n"; //none-reserved traffic
	/*----------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------------*/
	/* Guest Zone LAN(downlink) */
	if ( $gzone_enable=="1" )
	{
		// At anytime guest zone can at most only occupy 20% of the bandwidth
		$PRIO_ALL=$DOWNSTREAM / 5;	
		//calculating relative root r2q and root class quantum
		//default quantum with default rfq = 10, quantum = rate/r2q
		$CLASS_QUAN = $PRIO_ALL / 10 ; 
		if( $CLASS_QUAN < 12 ) //minimum quantum should be at least max packet size: 1500byte = 1.5kbyte = 12 kbit
		{
			//quantum below minimum, but can be solved through reducing r2q from default
			$r2q = 1;
		}
		else if( $CLASS_QUAN > 480 ) //maximum quantum should be less than 60000byte = 60 kbyte = 480 kbit
		{
			//quantum above maximum, should increase r2q value to bring down quantum value
			$r2q_value = $PRIO_ALL / 480 ; // 100 * 480
			$r2q_value = $r2q_value + 1;
			$r2q = $r2q_value;
		}
		else
		{
			$r2q = 10;
		}
		
		echo $TC." qdisc add dev ".$G_LANDEV." handle 3: root htb r2q ".$r2q." default 3 \n";
		echo $TC." class add dev ".$G_LANDEV." parent 3: classid 3:3 htb rate ".$PRIO_ALL.$K." ceil ".$PRIO_ALL.$K." \n";
		echo $TC." qdisc add dev ".$G_LANDEV." parent 3:3 handle 300: pfifo limit 50 \n";
		echo $TC." filter add dev ".$G_LANDEV." parent 3: protocol ip prio 100 u32  match ip dst 0.0.0.0/0 flowid 3:3 \n";
	}

	/*-----------------------------------------------------*/
//	echo "echo ".$QOS_ENABLE." ".$UPSTREAM." ".$DOWNSTREAM." > /proc/fastnat/qos \n";
//	echo "echo -1 > /proc/fastnat/formqossupport \n";
	/*-----------------------------------------------------*/

	
	/*-----------------------------------------------------*/
	for("/qos/entry")
	{
		$ENABLE		= query("enable");
		$STARTIP	= query("startip");
		$ENDIP		= query("endip");
		$STARTPORT	= query("startport");
		$ENDPORT	= query("endport");
		$PRIORITY	= query("priority");

		/* 
		echo "echo  ENABLE=$ENABLE STARTIP=$STARTIP ENDIP=$ENDIP STARTPORT=$STARTPORT ENDPORT=$ENDPORT PRIORITY=$PRIORITY \n";
		*/

		if ( $ENABLE == 1 )
		{
		if( $STARTIP == "*" ){ $STARTIP="0.0.0.0"; }
		if( $STARTPORT == "*"  ||  $ENDPORT == "*" ){ $STARTPORT=0;$ENDPORT=0; }

//		echo "echo ".$STARTIP.":".$STARTPORT."-".$ENDPORT.":".$PRIORITY." > /proc/fastnat/formqossupport \n";
		}

	}
	/*-----------------------------------------------------*/

}
else
{
	echo "echo Stop QOS system ... \n";
	echo $TC." qdisc del dev ".$WANDEV." root \n";
	echo $TC." qdisc del dev ".$H_LANDEV." root \n";
	if ( $gzone_enable=="1" )
	{
		echo $TC." qdisc del dev ".$G_LANDEV." root \n";
	}
//	echo "echo 0 > /proc/fastnat/qos \n";
}

?>
