#!/bin/sh
echo [$0] ... > /dev/console
TROOT="/etc/templates"
case "$1" in
start|restart)
	[ -f /var/run/pure_ftpd_stop.sh ] && sh /var/run/pure_ftpd_stop.sh > /dev/console
	rgdb -A $TROOT/pure_ftpd.php -V generate_start=1 > /var/run/pure_ftpd_start.sh
	rgdb -A $TROOT/pure_ftpd.php -V generate_start=0 > /var/run/pure_ftpd_stop.sh
	sh /var/run/pure_ftpd_start.sh > /dev/console
	;;
stop)
	if [ -f /var/run/pure_ftpd_stop.sh ]; then
		sh /var/run/pure_ftpd_stop.sh > /dev/console
#		rm -f /var/run/pure_ftpd_stop.sh
	fi
	;;
*)
	echo "usage: pure_ftpd.sh {start|stop|restart}"
	;;
esac
