#!/bin/sh
echo [$0] ... > /dev/console
TROOT="/etc/templates"
NAT_CFG="hw_nat_cfg"
LANIP=`xmldbc -g /lan/ethernet/ip`
LANMASK=`xmldbc -g /lan/ethernet/netmask`
WANIP=`xmldbc -i -g /runtime/wan/inf:1/ip`
WANMASK=`xmldbc -i -g /runtime/wan/inf:1/netmask`
target=$1;
if [ "`xmldbc -i -g /runtime/router/disable_hwnat`" = "1" ]; then
	target="stop";
fi 
if [ "`xmldbc -g /bridge`" = "1" ]; then
    target="stop";
fi
if [ "`xmldbc -i -g /runtime/wan/inf:1/connectstatus`" != "connected" ]; then
	target="stop";
fi
if [ "`xmldbc -g /wan/rg/inf:1/mode`" != "1" -a "`xmldbc -g /wan/rg/inf:1/mode`" != "2" -a  "`xmldbc -g /wan/rg/inf:1/mode`" != "3" ]; then
	target="stop";
fi
if [ "`xmldbc -g /qos/mode`" = "1" ]; then
	target="stop";
fi

if [ "`xmldbc -g /wireless/auth_logo`" = "1" ]; then
	target="stop";
fi


case "$target" in
wanup|start|restart)
	echo "enable hw nat....^_^"
	$NAT_CFG del eth0
	$NAT_CFG del eth1
	$NAT_CFG add ip eth0 $LANIP $LANMASK
	$NAT_CFG add ip eth1 $WANIP $WANMASK
	$NAT_CFG set eth0 lan
	$NAT_CFG set eth1 wan
	$NAT_CFG set enable
	$NAT_CFG show ip
	echo 19 > /proc/sys/net/ipv4/storlink_fast_net
	rgdb -i -s /runtime/hw_nat/enable 1
	;;
wandown|stop)
	echo "disable hw nat.....^_^"
	$NAT_CFG del eth0
	$NAT_CFG del eth1
	$NAT_CFG set disable
	echo 0 > /proc/sys/net/ipv4/storlink_fast_net
	rgdb -i -s /runtime/hw_nat/enable 0
	;;
*)
	echo "usage: nat_cfg.sh {start|stop|restart}"
	;;
esac
