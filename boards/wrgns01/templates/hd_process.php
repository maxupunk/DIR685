#!/bin/sh
echo [$0] ... > /dev/console
<?
/* vi: set sw=4 ts=4: */
require("/etc/templates/troot.php");
$hd_name = query("/runtime/nas/store_dev/devname");

if ($generate_start==1)
{

	echo "/etc/templates/itunes_server.sh restart \n";
	echo "/etc/templates/pure_ftpd.sh restart \n";
	echo "/etc/templates/upnp_av.sh restart \n";
	echo "/etc/templates/network_access.sh restart \n";
	echo "/etc/templates/bt.sh restart \n";
	if($hd_name!="")
	{
		echo "smartctl -s on /dev/".$hd_name." \n" ;
		$hd_sleep_time = query("/nas/store_dev/sleep_time");
		echo "smart_spindown /dev/".$hd_name." ".$hd_sleep_time." & \n";
	}
	
}
else if ($generate_start==0)
{
	$path_network_access = "/var/run/network_access_stop.sh";
	$path_itunes_server = "/var/run/itunes_server_stop.sh";
	$path_pure_ftpd = "/var/run/pure_ftpd_stop.sh";
	$path_upnp_av = "/var/run/upnp_av_stop.sh";
	$path_bt = "/var/run/bt_stop.sh";
	
	echo "killall -w smart_spindown & \n";
	echo "smartmon -F & \n";
	
	$dummy = fread($path_bt);
	if ($dummy != "") { echo "sh ".$path_bt."\n"; }
	$dummy = fread($path_network_access);
	if ($dummy != "") { echo "sh ".$path_network_access."\n"; } 
	$dummy = fread($path_itunes_server);
	if ($dummy != "") { echo "sh ".$path_itunes_server."\n"; } 
	$dummy = fread($path_pure_ftpd);
	if ($dummy != "") { echo "sh ".$path_pure_ftpd."\n"; } 
	$dummy = fread($path_upnp_av);
	if ($dummy != "") { echo "sh ".$path_upnp_av."\n"; }
	
	if($hd_name!="")
	{
		echo "sleep 2\n";
		echo "umnt_dev ".$hd_name." \n";
		echo "rmmod sata \n";
		echo "ssignal 38 & \n"; /* send key to end "unmounting" in lcd */
	}
	
	
}
else if ($generate_before_format==1)
{
	$path_network_access = "/var/run/network_access_stop.sh";
	$path_itunes_server = "/var/run/itunes_server_stop.sh";
	$path_pure_ftpd = "/var/run/pure_ftpd_stop.sh";
	$path_upnp_av = "/var/run/upnp_av_stop.sh";
	$path_bt = "/var/run/bt_stop.sh";
	
	$dummy = fread($path_bt);
	if ($dummy != "") { echo "sh ".$path_bt."\n"; }
	$dummy = fread($path_network_access);
	if ($dummy != "") { echo "sh ".$path_network_access."\n"; } 
	$dummy = fread($path_itunes_server);
	if ($dummy != "") { echo "sh ".$path_itunes_server."\n"; } 
	$dummy = fread($path_pure_ftpd);
	if ($dummy != "") { echo "sh ".$path_pure_ftpd."\n"; } 
	$dummy = fread($path_upnp_av);
	if ($dummy != "") { echo "sh ".$path_upnp_av."\n"; }
	echo "killall -w smart_spindown & \n";
	
	if($hd_name!="")
	{
		echo "umnt_dev ".$hd_name." \n";
	}
}
else if ($generate_before_format==0)
{
	echo "echo 1 > /var/is_sata_hd\n";
	/* we need this line below to check if hd is successfully formatted or not */
	echo "mnt_dev ".$hd_name." 0\n";

	/* fix bug : after format, hd name is still blank. Re-install sata to prevent this. */
	echo "umnt_dev ".$hd_name." \n";
	echo "rmmod sata\n";
	echo "echo 1 > /var/is_sata_hd\n";
	echo "insmod sata\n";
	
	/* some HD must run twice. */
	echo "SATA_STAT=`cat /proc/sata_stat|scut -f 3|grep ".$hd_name."`\n";
	echo "if [ \"$SATA_STAT\" = \"\" ]; then \n";
	echo "echo ===============restart=========================== > /dev/console \n";
	echo "rmmod sata\n";
	echo "sleep 1\n";
	echo "insmod sata\n";
	echo "fi\n";
	
	echo "/etc/templates/pure_ftpd.sh start \n";
	echo "/etc/templates/upnp_av.sh start \n";
	echo "/etc/templates/itunes_server.sh start \n";
	echo "/etc/templates/network_access.sh start \n";
	echo "/etc/templates/bt.sh restart \n";
	
	echo "smartctl -s on /dev/".$hd_name. " \n" ;
	$hd_timeout = query("/nas/store_dev/sleep_time");
	echo "smart_spindown /dev/".$hd_name." ".$hd_timeout." & \n";
}
?>
