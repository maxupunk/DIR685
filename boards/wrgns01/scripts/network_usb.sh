#!/bin/sh
echo [$0] $1... > /dev/console
case "$1" in
start)
	if [ -f /lib/modules/NetUSB.ko ]; then
	insmod NetUSB
	else
	insmod sxuptp.ko
	insmod sxuptp_generic.ko
	insmod jcp.ko
	insmod jcp_cmd.ko
	fi

	;;
stop)
	if [ -f /lib/modules/NetUSB.ko ]; then
	rmmod NetUSB.ko
	else
	rmmod jcp_cmd.ko
	rmmod jcp.ko
	rmmod sxuptp_generic.ko
	rmmod sxuptp.ko
	fi

	;;
restart)
	$0 stop
	$0 start
	;;
*)
	echo "usage: network_usb.sh {start|stop|restart}"
	;;
esac
