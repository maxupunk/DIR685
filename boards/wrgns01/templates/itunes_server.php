#!/bin/sh
echo [$0] ... > /dev/console
<?
/* vi: set sw=4 ts=4: */
require("/etc/templates/troot.php");

if ($generate_start==1)
{
	if(query("/runtime/nas/store_dev/mount")=="" && query("/runtime/nas/store_dev/devname")=="")
	{
		echo "No HD found  > /dev/console\n";
	}
	else
	{
		if (query("/nas/iTunes/enable")!="1")
		{
			echo "itunes-server is disabled ! > /dev/console\n";
		}
		else
		{
			anchor("/nas/iTunes");
			$password = query("password");
			$root="/tmp/storage_dev/";
			$root = $root.query("path");       
			$iTunesConfigFilePath = "/var/mt-daapd.conf";
			$rescan=query("rescan");
			//$db_dir=query("/runtime/itunes/db_path");//jana removed
			$db_dir=query("/runtime/nas/store_dev/mount");//jana added
			
			fwrite($iTunesConfigFilePath, "web_root        /etc/admin-root\n");
			fwrite2($iTunesConfigFilePath, "port            3689\n");
			//fwrite2($iTunesConfigFilePath, "admin_pw        ".$password."\n");//jana removed  
			fwrite2($iTunesConfigFilePath, "admin_pw        vykvkhvkhvilhbn1561\n");//jana added
			fwrite2($iTunesConfigFilePath, "mp3_dir         ".$root."\n");
			fwrite2($iTunesConfigFilePath, "servername      DIR-685\n");
			fwrite2($iTunesConfigFilePath, "runas           root\n");
			fwrite2($iTunesConfigFilePath, "playlist        /etc/mt-daapd.playlist\n");
			fwrite2($iTunesConfigFilePath, "extensions      .mp3,.m4a,.m4p\n");
			fwrite2($iTunesConfigFilePath, "db_dir          /tmp/storage_dev/".$db_dir."/.systemfile/\n");
			fwrite2($iTunesConfigFilePath, "rescan_interval ".$rescan."\n");	
			fwrite2($iTunesConfigFilePath, "scan_type       0\n");
			fwrite2($iTunesConfigFilePath, "always_scan     1\n");
			fwrite2($iTunesConfigFilePath, "logfile         /var/log/mt-daapd.log\n");
			fwrite2($iTunesConfigFilePath, "process_m3u     0\n");
			fwrite2($iTunesConfigFilePath, "compress        0\n");	
			
			echo "echo \"Start mt-daapd and mDNSResponderPoxis ...\" > /dev/console\n";
			echo "mt-daapd -c ".$iTunesConfigFilePath." & \n";		
			echo "mDNSResponderPosix -b -f /etc/rendezvous.conf \n";		
			echo "inotify_iTune -mqr ".$root." &\n";
		}
	}
}
else
{
	if (query("/nas/iTunes/enable")!="1")
	{
		echo "itunes-server is disabled ! > /dev/console\n";
	}
	else
	{	
		echo "echo \"Stop itunes-server ...\" > /dev/console\n";
		echo "killall -w mt-daapd\n"; 
		echo "killall -w mDNSResponderPosix\n";
		echo "killall -w inotify_iTune\n";
	}
}
?>
