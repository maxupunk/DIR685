#!/bin/sh
echo [$0] ... > /dev/console
TROOT="/etc/templates"
case "$1" in
start|restart)
	[ -f /var/run/upnp_av_stop.sh ] && sh /var/run/upnp_av_stop.sh > /dev/console
	rgdb -A $TROOT/upnp_av.php -V generate_start=1 > /var/run/upnp_av_start.sh
	rgdb -A $TROOT/upnp_av.php -V generate_start=0 > /var/run/upnp_av_stop.sh
	rgdb -A $TROOT/prescan.php -V generate_start=1 > /var/run/prescan_start.sh
	sh /var/run/upnp_av_start.sh &> /dev/console
	sh /var/run/prescan_start.sh &> /dev/console
	;;
stop)
	if [ -f /var/run/upnp_av_stop.sh ]; then
		sh /var/run/upnp_av_stop.sh > /dev/console
		rm -f /var/run/upnp_av_stop.sh
	fi
	;;
*)
	echo "usage: upnp_av.sh {start|stop|restart}"
	;;
esac
