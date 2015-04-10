#!/bin/sh
echo [$0] ... > /dev/console
<?
/* vi: set sw=4 ts=4: */
require("/etc/templates/troot.php");

if ($generate_start==1)
{
	if (query("/nas/upnp/enable")!="1")
	{
		echo "echo \"Upnp-av server is disabled !\" > /dev/console\n";
	}
	else
	{
		anchor("/nas/upnp");
		$rescan = query("rescan");
		
		if($rescan !="0" && $rescan != "")
		{
			echo "while [ 1=1 ]; do\n";
			echo "\tsleep ".$rescan."\n";		
			echo "\tScanMedia \n";	
			echo "done \n";
		}			
	}
}
else if ($generate_start==2)
{
	if (query("/nas/upnp/enable")!="1")
	{
		echo "echo \"Upnp-av server is disabled !\" > /dev/console\n";
	}
	else
	{
		echo "echo \"Start scan media !\" > /dev/console\n";
		echo "ScanMedia &\n";
	}
}

?>
