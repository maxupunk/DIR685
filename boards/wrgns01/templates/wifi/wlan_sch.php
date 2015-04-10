#!/bin/sh
echo [$0] ... > /dev/console
<? /* vi: set sw=4 ts=4: */
require("/etc/templates/troot.php");
$wlanif=query("/runtime/layout/wlanif"); 		//ra0
$wlanif_sch_wait="/var/run/".$wlanif."_sch_wait";
$wlan_sch=query("/wireless/schedule/id");
$sch_sock_path="/var/run/schedule_usock";
$script_path="/etc/templates/wifi/wlan_sch_run.sh";
if ($generate_start==1)
{
	if($wlan_sch != "" && $wlan_sch != 0)
	{
		echo "ifconfig ".$wlanif." down\n";
		// create a file indicating host zone is waiting on schedule, 
		// the file will be remove once /etc/templates/wifi/wlan_sch_run.sh is run
		echo "echo 1 > ".$wlanif_sch_wait." \n";
		$UNIQUEID=$wlan_sch;
		require("/etc/templates/rg/__schedule.php");
		$sch_cmd ="usockc ".$sch_sock_path." \"act=add start=".$START." end=".$END." days=".$DAYS." cmd=[".$script_path."]\"\n";
		echo $sch_cmd."\n";
	}
	else
	{
		echo $script_path." restart\n";
	}
}
else
{
	if($wlan_sch != "" && $wlan_sch != 0)
	{
		$UNIQUEID=$wlan_sch;
		require("/etc/templates/rg/__schedule.php");
		$sch_cmd ="usockc ".$sch_sock_path." \"act=del cmd=[".$script_path."]\"\n";
		echo $sch_cmd."\n";
	}
	else
	{
		echo $script_path." stop\n";
	}
}
?>
