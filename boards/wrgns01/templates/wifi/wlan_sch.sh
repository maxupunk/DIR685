#!/bin/sh
echo [$0] $1 ... > /dev/console
case "$1" in
start|restart)
	[ -f /var/run/wlan_sch_stop.sh ] && sh /var/run/wlan_sch_stop.sh > /dev/console
	xmldbc -A /etc/templates/wifi/wlan_sch.php -V generate_start=1 > /var/run/wlan_sch_start.sh
	xmldbc -A /etc/templates/wifi/wlan_sch.php -V generate_start=0 > /var/run/wlan_sch_stop.sh
	sh /var/run/wlan_sch_start.sh > /dev/console
	;;
stop)
	[ -f /var/run/wlan_sch_stop.sh ] && sh /var/run/wlan_sch_stop.sh > /dev/console
	rm -f /var/run/wlan_sch_stop.sh
	;;
*)
	echo "Usage $0 {start|stop|restart}"
	;;
esac
exit 0
