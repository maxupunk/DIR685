#!/bin/sh
echo [$0] $1 ... > /dev/console
case "$1" in
start|restart)
	[ -f /var/run/layout_gzone_stop.sh ] && sh /var/run/layout_gzone_stop.sh > /dev/console
	xmldbc -A /etc/scripts/layout_gzone_run.php -V generate_start=1 > /var/run/layout_gzone_start.sh
	xmldbc -A /etc/scripts/layout_gzone_run.php -V generate_start=0 > /var/run/layout_gzone_stop.sh
	sh /var/run/layout_gzone_start.sh > /dev/console
	;;
stop)
	if [ -f /var/run/layout_gzone_stop.sh ]; then
		sh /var/run/layout_gzone_stop.sh > /dev/console
		rm -f /var/run/layout_gzone_stop.sh
	fi
	;;
*)
	echo "Usage $0 {start|stop|restart}"
	;;
esac
exit 0
