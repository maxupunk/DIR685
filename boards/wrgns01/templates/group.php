#!/bin/sh
echo [$0] ... > /dev/console
<?
/* vi: set sw=4 ts=4: */
require("/etc/templates/troot.php");
$ftp_gp="/etc/ftpgroup";
$group_file="/etc/group";
if ($generate_start==1)//add
{
	fwrite($group_file,"");
	for("/nas/group")
	{
		$name=query("name");
		echo "addgroup -g ".$name."\n";	
	}
}
else//del
{
	echo "echo \"Delgroup ...\" > /dev/console\n";
	echo "delgroup ".$name." \n"; 
	$ftpgroup="/etc/ftpgroup";
	fwrite($ftp_gp,"");
	for ("/nas/group")//update ftp acc.
	{
		$permission=query("ftp/permission");		
		if($permission!="")//for ftp acc.
		{
			$group=query("/nas/group:".$@."/name");
			fwrite2($ftp_gp,"".$group.",".$permission."\n");
		}	
	}
}
?>
