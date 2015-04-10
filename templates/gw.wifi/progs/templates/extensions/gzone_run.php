#!/bin/sh
echo [$0] ... > /dev/console
<? /* vi: set sw=4 ts=4: */
require("/etc/templates/troot.php");

$lanif = query("/runtime/layout/lanif2");
$dhcpd_pidf = "/var/run/udhcpd-".$lanif.".pid";
$dhcpd_conf = "/var/run/udhcpd-".$lanif.".conf";
$dhcpd_lease= "/var/run/udhcpd-".$lanif.".lease";
$dhcpd_patch= "/var/run/dhcppatch-".$lanif.".pid";

$dhcpd_enable = query("/gzone/dhcp/server/enable");
$gzone_enable = query("/gzone/enable");
$gzone_lockclient = query("/gzone/lockclient/enable");
//if lock client is enabled, reserve lock client list from leases file.
if($gzone_lockclient=="1")	{$dhcpd_clearleases = 0;}
else 						{$dhcpd_clearleases = 1;}

if ($generate_start==1)
{
	if (query("/runtime/router/enable")!=1)
	{
		echo "echo Bridge mode selected, Guest Zone is disabled ! > /dev/console\n";
	}
	else
	{
		$lanmac = query("runtime/layout/lanmac2");
		set("/runtime/sys/info/lanmac2", $lanmac);
		
		anchor("/gzone/ethernet");
		$ipaddr		= query("ip");
		$netmask	= query("netmask");
		if ($gzone_enable==1)
		{
			echo "echo \"Start Guest Zone (".$lanif."/".$ipaddr."/".$netmask.")...\" > /dev/console\n";
			echo "ifconfig ".$lanif." ".$ipaddr;
			if ($netmask != "") { echo " netmask ".$netmask; }
			echo "\n";
			echo "/etc/templates/rg.sh misc\n"; 
		}
		if ($dhcpd_enable==1)
		{
			anchor("/gzone/dhcp/server/pool:1");
			$ipstr = query("startip");
			$ipend = query("endip");
			$dmain = query("domain");
			$wins0 = query("primarywins");
			$wins1 = query("secondarywins");
			$ltime = query("leasetime");
			if ($ltime == "") { $ltime=8640; }
			if ($dmain == "") { $dmain=query("/runtime/wan/inf:1/domain"); }

			/* clear leases*/
			if ($dhcpd_clearleases == 1)
			{
				if ($ipstr	!= query("/runtime/dhcpserver/gzone/ipaddr")	||
					$netmask!= query("/runtime/dhcpserver/gzone/netmask")	||
					$ipstr	!= query("/runtime/dhcpserver/gzone/startip")	||
					$ipend	!= query("/runtime/dhcpserver/gzone/endip"))
				{
					echo "echo -n > ".$dhcpd_lease."\n";
					set("/runtime/dhcpserver/gzone/ipaddr",		$ipaddr);
					set("/runtime/dhcpserver/gzone/netmask",	$netmask);
					set("/runtime/dhcpserver/gzone/startip",	$ipstr);
					set("/runtime/dhcpserver/gzone/endip",		$ipend);
				}
			}
			fwrite( $dhcpd_conf, "start ".		$ipstr."\n");
			fwrite2($dhcpd_conf, "end ".		$ipend."\n");
			fwrite2($dhcpd_conf, "interface ".	$lanif."\n");
			fwrite2($dhcpd_conf, "lease_file ".	$dhcpd_lease."\n");
			fwrite2($dhcpd_conf, "pidfile ".	$dhcpd_pidf."\n");
			fwrite2($dhcpd_conf, "auto_time ".	"10\n");
			fwrite2($dhcpd_conf, "opt lease ".	$ltime."\n");

			if ($dmain!="")		{ fwrite2($dhcpd_conf, "opt domain ".$dmain."\n"); }
			if ($netmask!="")	{ fwrite2($dhcpd_conf, "opt subnet ".$netmask."\n"); }
			if ($ipaddr!="")	{ fwrite2($dhcpd_conf, "opt router ".$ipaddr."\n"); }
			if ($wins0!="")		{ fwrite2($dhcpd_conf, "opt wins ".$wins0."\n"); }
			if ($wins1!="")		{ fwrite2($dhcpd_conf, "opt wins ".$wins1."\n"); }

			if (query("/dnsrelay/mode") != "1")	/* 1:disable, 2:auto */
			{
				fwrite2($dhcpd_conf, "opt dns ".$ipaddr."\n");
			}
			else
			{
				$dns = query("/runtime/wan/inf:1/primarydns");
				if ($dns != "")	{ fwrite2($dhcpd_conf, "opt dns ".$dns."\n"); }
				$dns=query("/runtime/wan/inf:1/secondarydns");
				if ($dns != "")	{ fwrite2($dhcpd_conf, "opt dns ".$dns."\n"); }
			}
			

			if (query("staticdhcp/enable") == 1)
			{
				for ("/gzone/dhcp/server/pool:1/staticdhcp/entry")
				{
					if (query("enable") == 1)
					{
						$hostname=query("hostname");
						$ip=query("ip");
						$mac=query("mac");
						fwrite2($dhcpd_conf, "static ".$hostname." ".$ip." ".$mac."\n");
					}
				}
			}

			echo "udhcpd ".$dhcpd_conf." &\n";
			echo "dhcpxmlpatch -f ".$dhcpd_lease." -p /runtime/dhcpserver:2 &\n";
			echo "echo $! > ".$dhcpd_patch."\n";
		}
	}
}
else
{
	echo "echo \"Stop Guest Zone(".$lanif.")...\" > /dev/console\n";
	if (query("/runtime/router/enable")!=1)
	{
		echo "echo Bridge mode selected, Guest Zone is disabled ! > /dev/console\n";
	}
	else
	{
		if ($dhcpd_enable==1)
		{
			echo "if [ -f ".$dhcpd_patch." ]; then\n";
			echo "	pid=`cat ".$dhcpd_patch."`\n";
			echo "	if [ \"$pid\" != \"0\" ]; then\n";
			echo "		kill \"$pid\" > /dev/console 2>&1\n";
			echo "	fi\n";
			echo "	rm -f ".$dhcpd_patch."\n";
			echo "fi\n";

			echo "if [ -f ".$dhcpd_pidf." ]; then\n";
			echo "	pid=`cat ".$dhcpd_pidf."`\n";
			echo "	if [ \"$pid\" != \"0\" ]; then\n";
			echo "		kill \"$pid\" > /dev/console 2>&1\n";
			echo "	fi\n";
			echo "	rm -f ".$dhcpd_pidf."\n";
			echo "fi\n";
		}
		if ($gzone_enable==1)
		{
			echo "ifconfig ".$lanif." 0.0.0.0 > /dev/console 2>&1\n";
			echo "/etc/templates/rg.sh misc\n"; 
		}
	}
}
?>
