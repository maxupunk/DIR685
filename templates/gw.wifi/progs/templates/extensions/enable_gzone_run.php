#!/bin/sh
echo [$0] ... > /dev/console
<? /* vi: set sw=4 ts=4: */
require("/etc/templates/troot.php");
$gzone_sch=query("/gzone/schedule/id");
$sch_sock_path="/var/run/schedule_usock";
$script_path="/etc/scripts/layout_gzone.sh";
$enable=query("/gzone/enable");
if($generate_start == 1)
{
	if($enable == 1)
	{
		if($gzone_sch != "" && $gzone_sch != 0)
		{
			$UNIQUEID=$gzone_sch;
			require("/etc/templates/rg/__schedule.php");
			$sch_cmd ="usockc ".$sch_sock_path." \"act=add start=".$START." end=".$END." days=".$DAYS." cmd=[".$script_path."]\"\n";
			echo $sch_cmd."\n";
		}
		else
		{
			echo $script_path." restart\n";
		}
	}
}
else
{
	if($enable == 1)
	{
		if($gzone_sch != "" && $gzone_sch != 0)
		{
			$UNIQUEID=$gzone_sch;
			require("/etc/templates/rg/__schedule.php");
			$sch_cmd ="usockc ".$sch_sock_path." \"act=del cmd=[".$script_path."]\"\n";
			echo $sch_cmd."\n";
		}
		else
		{
			echo $script_path." stop\n";
		}
	}
}
?>
