#!/bin/sh
echo [$0] $1 ... > /dev/console
TROOT="/etc/templates"
case "$1" in
start|restart)
	/etc/templates/wifi/wlan_sch.sh stop  > /dev/console
	[ -f /var/run/wlan_stop.sh ] && sh /var/run/wlan_stop.sh > /dev/console
	rgdb -A $TROOT/wifi/wlan_run.php -V generate_start=0 > /var/run/wlan_stop.sh
	rgdb -A $TROOT/wifi/wlan_run.php -V generate_start=1 > /var/run/wlan_start.sh
	sh /var/run/wlan_start.sh > /dev/console
	sh /etc/templates/wifi/wlan_sch.sh start > /dev/console
	;;
stop)
	/etc/templates/wifi/wlan_sch.sh stop  > /dev/console
	if [ -f /var/run/wlan_stop.sh ]; then
		sh /var/run/wlan_stop.sh > /dev/console
		rm -f /var/run/wlan_stop.sh
	fi
	
	;;
*)
	echo "usage: wlan.sh {start|stop|restart}" > /dev/console
	;;
esac
