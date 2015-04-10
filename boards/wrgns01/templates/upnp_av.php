#!/bin/sh
echo [$0] ... > /dev/console
<?
/* vi: set sw=4 ts=4: */
require("/etc/templates/troot.php");
$upnpav_conf="/etc/upnpav.conf";
$shared_name="/etc/shared_name";
if ($generate_start==1)
{
	if(query("/runtime/nas/store_dev/mount")=="" && query("/runtime/nas/store_dev/devname")=="")
	{
		echo "No HD found  > /dev/console\n";
	}
	else
	{
		if (query("/nas/upnp/enable")!="1")
		{
			echo "upnp-av is disabled ! > /dev/console\n";
		}
		else
		{
			$path=query("/nas/upnp/path");
			//$path="/tmp/".$path;
			$model_name = query("/sys/modelname");
			$db_dir=query("/runtime/nas/store_dev/mount");
			fwrite($shared_name,"".$db_dir." = HD_a2/".$path."\n");
			if($path=="")
			{
				fwrite($upnpav_conf,"ShareFolder:/mnt/HD_a2\n");
			}
			else
			{
				fwrite($upnpav_conf,"ShareFolder:/mnt/HD_a2/".$path."\n");
			}
			//echo "echo ln -s ".$path." /mnt/HD_a2 \n";
			echo "echo \"Start upnp-av ...\" > /dev/console\n";
			$HD_NAME=query("/runtime/nas/store_dev/mount");
			echo "mkdir -p /mnt/HD_a2/".$HD_NAME."/.systemfile/.upnpav-db/\n";
			echo "ScanMedia &\n";
			
		//	echo "prescan & \n";
			echo "upnp 0 \"D-LINK\" \"http:\/\/www.dlink.com/\" \"Network File Server with USB2.0 and wifi interface\" ".$model_name." 2.0 &\n";		
			echo "inotify_uPNP -mqr \"/mnt/HD_a2/".$path."\" & \n";
			
		}
	}
}
else
{
	if (query("/nas/upnp/enable")!="1")
	{
		echo "upnp-av is disabled ! > /dev/console\n";
	}
	else
	{	
		echo "echo \"Stop upnp-av ...\" > /dev/console\n";

		echo "i=`pidof ScanMedia`\n";
		echo "if [ \"\$i\" != \"\" ];then \n";
		echo "killall -w ScanMedia \n";
		echo "rm /tmp/prescan* \n";
		echo "fi \n";

		echo "i=`pidof upnp`\n";
		echo "if [ \"\$i\" != \"\" ];then \n";
		echo "killall -w upnp\n"; 		
		echo "fi \n";

		echo "i=`pidof inotify_uPNP`\n";
		echo "if [ \"\$i\" != \"\" ];then \n";
		echo "killall -w inotify_uPNP\n";
		echo "fi \n";
	}
}
?>
