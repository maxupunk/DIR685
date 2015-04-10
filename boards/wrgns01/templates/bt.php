#!/bin/sh
echo [$0] ... > /dev/console
<?
/* vi: set sw=4 ts=4: */
require("/etc/templates/troot.php");

$bt_pidf = "/var/run/bt.pid";
$btdog_pidf = "/var/run/btdog.pid";

$bt_enable = query("/nas/bt/enable");
$bt_path_header = query("/nas/bt/path_header");
$bt_path = query("/nas/bt/path");
$devname = query("/runtime/nas/store_dev/devname");
$dev_mount_name = query("/runtime/nas/store_dev/mount");
$cfg_port = "63521";

if ($generate_start==1)
{
	echo "echo generate_start ! > /dev/console\n";
	if ($bt_enable!="1")
	{
		echo "echo BT is disabled ! > /dev/console\n";
	}
	else if ($devname=="")
	{
		echo "echo No Hard Drive exist ! > /dev/console\n";
	}
	else if ($bt_path_header!=$dev_mount_name)
	{
		echo "echo The attached Hard Drive has changed. > /dev/console\n";
	}
	else
	{
		echo "echo BT is enabled ! > /dev/console\n";
		$root="/tmp/storage_dev/";
		$root = $root.$bt_path_header.$bt_path;       
		$BTConfigFilePath = $root."/btsettings.txt";
		fwrite($BTConfigFilePath, "webui_port: ".$cfg_port."\n");
		fwrite2($BTConfigFilePath, "dir_active: incomplete\n");
		fwrite2($BTConfigFilePath, "dir_completed: complete\n");  
		fwrite2($BTConfigFilePath, "dir_torrent_files: torrents\n");
		//fwrite2($BTConfigFilePath, "webui_dir_files: /www/bt_ui\n");
		echo "chmod 644 ".$BTConfigFilePath."\n";

		echo "mkdir -p ".$root."/complete\n";
		echo "mkdir -p ".$root."/incomplete\n";
		echo "mkdir -p ".$root."/torrents\n";
		echo "chmod 777 ".$root."/complete\n";
		echo "chmod 777 ".$root."/incomplete\n";
		echo "chmod 777 ".$root."/torrents\n";
		echo "echo \"Start BT ...\" > /dev/console\n";
		echo "cd ".$root." && umask 000 && memctrl 30 btdog bt -daemon-loop & \n";
	}
}
else
{
	if ($bt_enable!="1")
	{
		echo "echo BT is disabled ! > /dev/console\n";
	}
	else
	{	
		echo "echo \"Stop BT ...\" > /dev/console\n";
		echo "killall -w btdog > /dev/console 2>&1 \n";
		echo "killall -w bt > /dev/console 2>&1 \n";
		echo "i=`pidof bt`\n";
		echo "cnt=0\n";
		echo "limit=5\n";
		echo "while \[ \"$i\" != \"\" \ -o \"$cnt\" -lt \"$limit\"  ]\n";
		echo "do\n";
		echo "sleep 1\n";
		echo "cnt=`expr $cnt + 1`\n";
		echo "i=`pidof bt`\n";
		echo "done\n";
		
	}
}
?>
