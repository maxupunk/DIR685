#!/bin/sh
echo [$0] $1 ... > /dev/console
case "$1" in
start|restart)
	[ -f /var/run/wlan_sch_run_stop.sh ] && sh /var/run/wlan_sch_run_stop.sh > /dev/console
	xmldbc -A /etc/templates/wifi/wlan_sch_run.php -V generate_start=1 > /var/run/wlan_sch_run_start.sh
	xmldbc -A /etc/templates/wifi/wlan_sch_run.php -V generate_start=0 > /var/run/wlan_sch_run_stop.sh
	sh /var/run/wlan_sch_run_start.sh > /dev/console
	;;
stop)
	if [ -f /var/run/wlan_sch_run_stop.sh ]; then
		sh /var/run/wlan_sch_run_stop.sh > /dev/console
		rm -f /var/run/wlan_sch_run_stop.sh
	fi
	;;
*)
	echo "Usage $0 {start|stop|restart}"
	;;
esac
exit 0
