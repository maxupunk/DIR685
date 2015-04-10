#!/bin/sh
echo [$0] ... > /dev/console
<? /* vi: set sw=4 ts=4: */
$TROOT="/etc/templates";
$wireless_conf = "/var/run/RT2880AP.dat";

$wlanif  	= query("/runtime/layout/wlanif");
$wlanif2 	= query("/runtime/layout/wlanif2");
$lanif		= query("/runtime/layout/lanif");
$lanif2		= query("/runtime/layout/lanif2");
$wlanmac 	= query("/runtime/layout/wlanmac");
$wlanmac2	= query("/runtime/layout/wlanmac2");
$wlxmlpatch_pid="/var/run/wlxmlpatch.RT2880.pid";

$authtype	= query("/wireless/authtype");
$wlan_en	= query("/wireless/enable");
$wlan2lan	= query("/wireless/bridge/wlan2lan");	if ($wlan2lan!="0")	{$wlan2lan="1";}
if (query("/runtime/router/enable")=="0")
{	$wlanip = query("/runtime/wan/inf:1/ip");	}
else
{	$wlanip = query("/lan/ethernet/ip");		}
$wps_enable = query("/wireless/wps/enable");
$debug      = query("/runtime/debug_wps");

if ($generate_start==1)
{
	echo "echo Start WLAN interface ".$wlanif." ... > /dev/console\n";
	if ($wlan_en!=1)
	{
		echo "echo WLAN is disabled ! > /dev/console\n";
		/* Turn off the WLAN LED when wireless is off */
		echo "usockc /var/run/fresetd_unixsock RADIO_OFF\n";	
		exit;
	}
	
	/* Generate Ralink RT2860 wireless driver configuration file*/
	echo "xmldbc -A ".$TROOT."/wifi/RT2880AP.php > ".$wireless_conf."\n";
	
	if (query("/wireless/wps/enable")=="1") { echo "/etc/templates/wps.sh pre_setie\n"; }
	
	/* Second BSSID */ //--dat_mbssid.php is called within RT2880AP.php
//	if (query("/gzone/members/wlan:2/enable") == 1) { require($template_root."/wifi/dat_mbssid.php"); }

	/* re-insert wireless module. */
	require($TROOT."/wifi/restart_wlan_driver.php");

	/* bridge to lan */
	echo "echo ".$wlan2lan." > /proc/net/br_forward_br0\n";

	/* Enable WPS ? */
	$HAPD_wps = 0;
	if (query("/wireless/wps/enable")==1)
	{
		$HAPD_wps = 1;
		$HAPD_eapuserfile = "/var/run/hostapd.wps.eap_user";
	}

	/* Generate config file for hostapd */
	$HAPD_interface = $wlanif;
	$HAPD_bridge	= $lanif;
	$HAPD_conf		= "/var/run/hostapd.".$HAPD_interface.".conf";
	anchor("/wireless");
	require($TROOT."/wifi/hostapd_used.php");
	$hostapd_conf	= $HAPD_conf;

	if (query("/gzone/members/wlan:2/enable") == 1)
	{
//		echo "wlconf wl0.1 up \n";
//		echo "ifconfig ".$wlanif2." hw ether ".$wlanmac2." \n";
//		echo "ifconfig ".$wlanif2." up \n";

		/* Generate config gile for hostapd */
		$HAPD_wps = 0;
		$HAPD_interface = $wlanif2;
		$HAPD_bridge	= $lanif2;
		$HAPD_conf		= "/var/run/hostapd.".$HAPD_interface.".conf";
		anchor("/wlan/inf:2");
		require($TROOT."/wifi/hostapd_used.php");
		$hostapd_conf = $hostapd_conf." ".$HAPD_conf;
//		$hostapd_conf	= $HAPD_conf;
	}
//run it in wlan_sch_run.php
//	echo "hostapd ".$hostapd_conf." &\n";
//	echo "hostapd -dd -K -t ".$hostapd_conf." &\n";
	
	/* start wlxmlpatch */
	echo "wlxmlpatch -S ".$wlanif." /runtime/stats/wireless RADIO_A_ON RADIO_A_BLINK RT2880 > /dev/console &\n";
	echo "echo $! > ".$wlxmlpatch_pid."\n";
	
	/* Turn on the WLAN LED when wireless is ready. */
	echo "usockc /var/run/fresetd_unixsock RADIO_ON\n";
//run it in wlan_sch_run.php
	//if (query("/wireless/wps/enable")==1) { echo "/etc/templates/wps.sh setie\n"; }
	echo "echo Start WLAN interface ".$wlanif." Done !!! > /dev/console\n";
}
else
{
	echo "echo Stop WLAN interface ".$wlanif." ... > /dev/console\n";
	
//	echo "ifconfig ".$wlanif2." down \n";
//	echo "ifconfig ".$wlanif." down\n";
	echo "rmmod /lib/modules/rt2880_iNIC.ko\n";
	
	if (query("/wireless/wps/enable")=="1") { echo "killall wps > /dev/console\n"; }
	echo "killall hostapd > /dev/null 2>&1\n";

	// kill wlxmlpatch
	echo "echo \"Stop wlxmlpatch ...(RT2860)\" > /dev/console\n";
	echo "if [ -f ".$wlxmlpatch_pid." ]; then \n";
	echo "  wlxmlpid=`cat ".$wlxmlpatch_pid."`\n";
	echo "  if [ $wlxmlpid != 0 ]; then \n";
	echo "      kill $wlxmlpid\n";
	echo "  fi\n";
	echo "  rm -f ".$wlxmlpatch_pid."\n";
	echo "fi\n";


	if (query("/wireless/enable")!=1)
	{
		echo "echo WLAN is disabled ! > /dev/console\n";
		exit;
	}

//	echo "killall rt2880apd\n";
//	echo "killall -SIGKILL wscd\n";
	echo "usockc /var/run/fresetd_unixsock WPS_NONE\n";
}
?>
