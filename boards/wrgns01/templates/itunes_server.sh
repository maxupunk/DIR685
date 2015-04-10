#!/bin/sh
echo [$0] ... > /dev/console
TROOT="/etc/templates"
case "$1" in
delay_restart)
  sleep 5
	[ -f /var/run/itunes_server_stop.sh ] && sh /var/run/itunes_server_stop.sh > /dev/console
	rgdb -A $TROOT/itunes_server.php -V generate_start=1 > /var/run/itunes_server_start.sh
	rgdb -A $TROOT/itunes_server.php -V generate_start=0 > /var/run/itunes_server_stop.sh
	sh /var/run/itunes_server_start.sh > /dev/console
	;;
start|restart)
	[ -f /var/run/itunes_server_stop.sh ] && sh /var/run/itunes_server_stop.sh > /dev/console
	rgdb -A $TROOT/itunes_server.php -V generate_start=1 > /var/run/itunes_server_start.sh
	rgdb -A $TROOT/itunes_server.php -V generate_start=0 > /var/run/itunes_server_stop.sh
	sh /var/run/itunes_server_start.sh > /dev/console
	;;
stop)
	if [ -f /var/run/itunes_server_stop.sh ]; then
		sh /var/run/itunes_server_stop.sh > /dev/console
		rm -f /var/run/itunes_server_stop.sh
	fi
	;;
*)
	echo "usage: itunes_server_stop.sh {start|stop|restart}"
	;;
esac
