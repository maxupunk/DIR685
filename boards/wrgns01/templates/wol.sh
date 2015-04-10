#!/bin/sh
echo [$0] ... > /dev/console
TROOT="/etc/templates"
case "$1" in
start|restart)
	[ -f /var/run/wol_stop.sh ] && sh /var/run/wol_stop.sh > /dev/console
	rgdb -A $TROOT/wol_run.php -V generate_start=1 > /var/run/wol_start.sh
	rgdb -A $TROOT/wol_run.php -V generate_start=0 > /var/run/wol_stop.sh
	sh /var/run/wol_start.sh > /dev/console
	;;
stop)
	if [ -f /var/run/wol_stop.sh ]; then
		sh /var/run/wol_stop.sh > /dev/console
		rm -f /var/run/wol_stop.sh
	fi
	;;
*)
	echo "usage: wol.sh {start|stop|restart}"
	;;
esac
