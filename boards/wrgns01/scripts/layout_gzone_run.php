#!/bin/sh
echo [$0] $1 ... > /dev/console
<?	/* vi: set sw=4 ts=4: */
require("/etc/templates/troot/php");
$enable		= query("/gzone/enable");
$ipaddr		= query("/gzone/ethernet/ip");
$netmask	= query("/gzone/ethernet/netmask");
$wlanif  	= query("/runtime/layout/wlanif"); 		//ra0
$wlanif2 	= query("/runtime/layout/wlanif2"); 	//ra1
$lanif		= query("/runtime/layout/lanif"); 		//br0
$lanif2		= query("/runtime/layout/lanif2"); 		//br1
$wanif 		= query("/runtime/layout/wanif"); 		//eth1
$wlanmac 	= query("/runtime/layout/wlanmac");
$wlanmac2	= query("/runtime/layout/wlanmac2");
$HAPD_wlanif_conf	= "/var/run/hostapd.".$wlanif.".conf";
$HAPD_wlanif2_conf 	= "/var/run/hostapd.".$wlanif2.".conf";
$wlanif_sch_wait 	= "/var/run/".$wlanif."_sch_wait";
$wlanif2_sch_wait 	= "/var/run/".$wlanif2."_sch_wait";

if (query("/bridge")==1)
{
	echo "echo Bridge mode enabled, disable Guest Zone > /dev/console\n";
	exit;
}

$wlan = query("/gzone/members/wlan:2/enable");

//if (query("/gzone/isolation") == 1) { $GZONE_ISOLATED = 1; } else {$GZONE_ISOLATED = 0; }

if ($generate_start==1)
{
	echo "echo Start Guest Zone layout ... > /dev/console\n";
	if($enable==1)
	{
		if ($wlan==1)
		{
			// if wlan is enable, but $wlanif_sch_wait exist, 
			// this means host zone is on schedule but not up yet.
			// guest zone is not supposed to be up unless host zone is.
			// Hence we do nothing, since host zone schedule will bring guest zone up when it comes up
			
			// if $wlanif_sch_wait doesn't exist, this means host zone is on,
			// and we can proceed to getting guest zone up.
			echo "if [ ! -f ".$wlanif_sch_wait." ]; then\n";
			echo "ifconfig ".$wlanif2." up\n";
			echo "killall hostapd > /dev/null 2>&1\n";
			echo "hostapd ".$HAPD_wlanif_conf." ".$HAPD_wlanif2_conf." &\n";
			echo "brctl addif ".$lanif2." ".$wlanif2."\n";
			echo "brctl setbwctrl ".$lanif." eth0 450\n";
			echo "brctl setbwctrl ".$lanif2." ".$wlanif2." 450\n";
			echo "fi\n";
			
			if (query("/wireless/wps/enable")==1)
			{ echo "/etc/templates/wps.sh setie\n"; }

			// we finish getting wlanif up, if $wlanif2_sch_wait exist we should remove it
			echo "if [ -f ".$wlanif2_sch_wait." ]; then\n";
			echo "rm ".$wlanif2_sch_wait."\n";
			echo "fi\n";
		}
		echo "ifconfig ".$lanif2." ".$ipaddr;
		if ($netmask != "") { echo " netmask ".$netmask; }
		echo "\n";
	}
}
else
{
	echo "echo Stop Guest Zone layout ... > /dev/console\n";
	if($enable==1)
	{	
		if ($wlan==1)
		{	
			if(query("/gzone/schedule/id")!="" && query("/gzone/schedule/id")!=0)
			{
				echo "echo 1 > ".$wlanif2_sch_wait." \n";
			}
			echo "brctl delif ".$lanif2." ".$wlanif2."\n";
			echo "brctl setbwctrl ".$lanif." eth0 900\n";
			echo "ifconfig ".$wlanif2." down\n";
		}
		echo "ifconfig ".$lanif2." 0.0.0.0\n";
	}
}

?>
