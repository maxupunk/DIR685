#!/bin/sh
echo [$0] ... > /dev/console
TROOT="/etc/templates"
case "$1" in
start|restart)
	[ -f /var/run/bt_stop.sh ] && sh /var/run/bt_stop.sh > /dev/console
	rgdb -A $TROOT/bt.php -V generate_start=1 > /var/run/bt_start.sh
	rgdb -A $TROOT/bt.php -V generate_start=0 > /var/run/bt_stop.sh
	sh /var/run/bt_start.sh > /dev/console
	;;
stop)
	if [ -f /var/run/bt_stop.sh ]; then
		sh /var/run/bt_stop.sh > /dev/console
		rm -f /var/run/bt_stop.sh
	fi
	;;
*)
	echo "usage: bt.sh {start|stop|restart}"
	;;
esac
