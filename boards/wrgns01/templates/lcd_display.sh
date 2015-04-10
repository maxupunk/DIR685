#!/bin/sh
echo [$0] ... > /dev/console
TROOT="/etc/templates"
case "$1" in
start)
	cp /directfb/directfbrc /var/.
#	/directfb/alpha_nas &
	memctrl 40 /etc/templates/alpha_nas-loop.sh & 
	echo $! > /var/run/alpha_nas-loop.pid
	;;
stop)
	if [ -f /var/run/alpha_nas-loop.pid ]; then
    pid=`cat /var/run/alpha_nas-loop.pid`
    if [ $pid != 0 ]; then
    kill $pid > /dev/null 2>&1
    fi
    rm -f /var/run/alpha_nas-loop.pid
    fi
	killall -9 alpha_nas
	;;
fw_upgrade)
	ssignal 22 &
	sleep 2
	$0 stop		> /dev/console
	;;
*)
	echo "usage: lcd_display.sh {start|stop|fw_upgrade}"
	;;
esac
