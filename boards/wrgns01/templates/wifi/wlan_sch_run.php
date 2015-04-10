#!/bin/sh
echo [$0] $1 ... > /dev/console
<?	/* vi: set sw=4 ts=4: */
require("/etc/templates/troot/php");
$wlanif 	= query("/runtime/layout/wlanif"); 		//ra0
$wlanif2 	= query("/runtime/layout/wlanif2"); 	//ra1
$lanif 		= query("/runtime/layout/lanif"); 		//br0
$lanif2		= query("/runtime/layout/lanif2"); 		//br1
$wanif 		= query("/runtime/layout/wanif"); 		//eth1
$wlanmac 	= query("/runtime/layout/wlanmac");
$enable 	= query("/wireless/enable");
$g_enable	= query("/gzone/enable");
$HAPD_wlanif_conf 	= "/var/run/hostapd.".$wlanif.".conf";
$HAPD_wlanif2_conf 	= "/var/run/hostapd.".$wlanif2.".conf";
$wlanif_sch_wait 	= "/var/run/".$wlanif."_sch_wait";
$wlanif2_sch_wait 	= "/var/run/".$wlanif2."_sch_wait";

if ($generate_start==1)
{
	echo "echo Start WLAN layout ... > /dev/console\n";
	if($enable==1)
	{
		//let the hostapd up interface
		//echo "ifconfig ".$wlanif." up\n";
		
		// reset hostapd so the current encryption/security type is maintained
		//echo "killall hostapd > /dev/null 2>&1\n";
		
		if($g_enable==1)
		{
			// if $wlanif2_sch_wait exist meaning guest zone is currently not up, but waiting to be up
			// therefore we don't need to call config for guest zone at this point.
			// if $wlanif2_sch_wait doesn't exist we need to set up the entire guest zone as well
			echo "killall hostapd > /dev/null 2>&1\n";
			echo "if [ -f ".$wlanif2_sch_wait." ]; then\n";
			echo "hostapd ".$HAPD_wlanif_conf." &\n";
			echo "else\n";
			echo "ifconfig ".$wlanif2." up\n";
			echo "hostapd ".$HAPD_wlanif_conf." ".$HAPD_wlanif2_conf." &\n";
			echo "brctl addif ".$lanif2." ".$wlanif2."\n";
			echo "brctl setbwctrl ".$lanif." eth0 450\n";
			echo "brctl setbwctrl ".$lanif2." ".$wlanif2." 450\n";
			echo "fi\n";
			echo "brctl addif ".$lanif." ".$wlanif."\n";
			if (query("/wireless/wps/enable")==1)
			{ echo "/etc/templates/wps.sh setie\n"; }
		}
		else
		{
			echo "killall hostapd > /dev/null 2>&1\n";
			echo "brctl addif ".$lanif." ".$wlanif."\n";
			//echo "hostapd -dd -K -t ".$HAPD_wlanif_conf." &\n";
			echo "hostapd ".$HAPD_wlanif_conf." &\n";
			if (query("/wireless/wps/enable")==1)
			{ echo "/etc/templates/wps.sh setie\n"; }
		}
		
		// we finish getting wlanif up, if $wlanif_sch_wait exist we should remove it
		echo "if [ -f ".$wlanif_sch_wait." ]; then\n";
		echo "rm ".$wlanif_sch_wait."\n";
		echo "fi\n";
	}
}
else
{
	echo "echo Stop WLAN layout ... > /dev/console\n";
	if($enable==1)
	{
		if(query("/wireless/schedule/id")!="" && query("/wireless/schedule/id")!=0)
		{
			echo "echo 1 > ".$wlanif_sch_wait." \n";
		}
		echo "brctl delif ".$lanif." ".$wlanif."\n";
		echo "ifconfig ".$wlanif." down\n";
	}
}

?>
