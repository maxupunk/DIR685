#!/bin/sh
echo [$0] ... > /dev/console
<?
/* vi: set sw=4 ts=4: */

if ($generate_start==1)
{
	if (query("/runtime/router/enable")!=1)
	{
		echo "echo Router function is off, WoL will not be enabled !!! > /dev/console\n";
	}
	else
	{
		$enable_wol	= query("/wol/enable");
		
		if($enable_wol==1)
		{
			echo "echo Start Wake on LAN ... > /dev/console\n";
			
			$udp_port	= query("/wol/udp/port");
			$tcp_port	= query("/wol/tcp/port");
			$inf		= query("/wol/interface");
						
			if($udp_port!="" && $tcp_port!="")
			{
				echo "echo open UDP and TCP port ... > /dev/console\n";
				echo "iptables -t nat -D PRE_MISC -p udp --dport ".$udp_port." -j ACCEPT\n";
				echo "iptables -t nat -D PRE_MISC -p tcp --dport ".$tcp_port." -j ACCEPT\n";
				echo "iptables -t nat -I PRE_MISC -p udp --dport ".$udp_port." -j ACCEPT\n";
				echo "iptables -t nat -I PRE_MISC -p tcp --dport ".$tcp_port." -j ACCEPT\n";
				echo "wol -u ".$udp_port." -t ".$tcp_port." -w eth1 -i ".$inf." &\n";
			}
			else if($udp_port!=""&& $tcp_port=="")
			{
				echo "echo open UDP port ... > /dev/console\n";
				echo "iptables -t nat -D PRE_MISC -p udp --dport ".$udp_port." -j ACCEPT\n";
				echo "iptables -t nat -I PRE_MISC -p udp --dport ".$udp_port." -j ACCEPT\n";
				echo "wol -u ".$udp_port." -w eth1 -i ".$inf." &\n";			
			}
			else if($udp_port=="" && $tcp_port!="")
			{
				echo "echo open TCP port ... > /dev/console\n";
				echo "iptables -t nat -D PRE_MISC -p tcp --dport ".$tcp_port." -j ACCEPT\n";
				echo "iptables -t nat -I PRE_MISC -p tcp --dport ".$tcp_port." -j ACCEPT\n";
				echo "wol -t ".$tcp_port." -w eth1 -i ".$inf." &\n";				
			}
			else
			{
				echo "echo ERROR ... > /dev/console\n";
			}
		}
	}
}
else
{
	echo "echo Stop Wake on LAN ... > /dev/console\n";
	if (query("/runtime/router/enable")!=1)
	{
		echo "echo DNRD is not enabled ! > /dev/console\n";
	}
	else
	{
		$udp_port	= query("/wol/udp/port");
		$tcp_port	= query("/wol/tcp/port");
		echo "killall wol > /dev/console\n";	
		
		if($udp_port!="" && $tcp_port!="")
		{
			echo "iptables -t nat -D PRE_MISC -p udp --dport ".$udp_port." -j ACCEPT\n";
			echo "iptables -t nat -D PRE_MISC -p tcp --dport ".$tcp_port." -j ACCEPT\n";
		}
		else if($udp_port!=""&& $tcp_port=="")
		{
			echo "iptables -t nat -D PRE_MISC -p udp --dport ".$udp_port." -j ACCEPT\n";	
		}
		else if($udp_port=="" && $tcp_port!="")
		{
			echo "iptables -t nat -D PRE_MISC -p tcp --dport ".$tcp_port." -j ACCEPT\n";			
		}
	}
}
?>
# wol_run.php <<<
