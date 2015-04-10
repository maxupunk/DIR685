#!/bin/sh
echo [$0] $1 ... > /dev/console
<?
/* vi: set sw=4 ts=4: */
require("/etc/templates/troot.php");

$bridge = query("/bridge");
if ($bridge!=1)	{ $router_on = 1; } else { $router_on = 0; }
//if (query("/gzone/isolation") == 1) { $GZONE_ISOLATED = 1; } else { $GZONE_ISOLATED = 0; }

if ($router_on==1)
{
	if ($generate_start==1)
	{
//		$HZONE = "";
//		$GZONE = "";
//		$wanmac = query("/runtime/layout/wanmac");
//		$lanmac = query("/runtime/layout/lanmac");
//		$lanmac2 = query("/runtime/layout/lanmac2");
	
		echo "echo Start router layout ...\n";
		if (query("/runtime/router/enable")==1)
		{
			echo "echo Already in router mode!\n";
			exit;
		}
		echo "ifconfig eth0 up\n";
		echo "ifconfig eth1 up\n";
		echo "brctl addif br0 eth0\n";
		echo "brctl addif br0 ra0\n";
		echo "ifconfig br0 up\n";
		echo "rgdb -i -s /runtime/router/enable 1\n";
		echo "echo joel disable stun ..\n";
		echo "rgdb -i -s /runtime/func/stun/enabled 0\n"; 
//		echo "insmod NetUSB\n";
// sam_pan add
		echo "sh /etc/scripts/network_usb.sh start\n";
	}
	else
	{
		echo "echo Stop router layout ...\n";
//		echo "rmmod NetUSB\n";
//sam_pan add
		echo "sh /etc/scripts/network_usb.sh stop\n";
		echo "brctl delif br0 eth1\n";
		echo "ifconfig ra0 down\n";
		echo "ifconfig eth0 down\n";
		echo "ifconfig eth1 down\n";
		echo "rgdb -i -s /runtime/router/enable \"\"\n";
	}
}
else
{
	if ($generate_start==1)
	{
		echo "echo Start bridge layout ...\n";
		if (query("/runtime/router/enable")==0)
		{
			echo "echo Already in bridge mode!\n";
			exit;
		}
		echo "ifconfig eth0 up\n";
		echo "ifconfig eth1 up\n";
		echo "brctl addif br0 eth0\n";
		echo "brctl addif br0 eth1\n";
		echo "brctl addif br0 ra0\n";
		echo "ifconfig br0 up\n";
		echo "rgdb -i -s /runtime/router/enable 0\n";
//		echo "insmod NetUSB\n";
// sam_pan add
        echo "sh /etc/scripts/network_usb.sh start\n";
	}
	else
	{
		echo "echo Stop bridge layout ...\n";
//		echo "rmmod NetUSB\n";
//sam_pan add
        echo "sh /etc/scripts/network_usb.sh stop\n";
		echo "brctl delif br0 eth0\n";
		echo "brctl delif br0 eth1\n";
		//joel workarround if we do not remove ra0 the ap mode switch,bridge in kernel will fail to forward packet.
		//and need remove last,if not last kernel panic
		echo "brctl delif br0 ra0\n";
		echo "rgdb -i -s /runtime/router/enable \"\"\n";
	}
}
?>
