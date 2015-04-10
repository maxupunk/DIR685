#!/bin/sh
echo [$0] ... > /dev/console
TROOT="/etc/templates"
case "$1" in
start)
	smart_spindown /dev/`rgdb -i -g /runtime/nas/store_dev/devname` `rgdb -g /nas/store_dev/sleep_time` &
	;;
stop)
	killall smart_spindown
	;;
*)
	echo "usage: hd_sleeptime.sh {start|stop}" > /dev/console
	;;
esac
