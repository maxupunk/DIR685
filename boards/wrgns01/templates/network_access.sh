#!/bin/sh
echo [$0] ... > /dev/console
TROOT="/etc/templates"
case "$1" in
start|restart)
	[ -f /var/run/network_access_stop.sh ] && sh /var/run/network_access_stop.sh > /dev/console
	/usr/sbin/get_device_name
	rgdb -A $TROOT/network_access.php -V generate_start=1 > /var/run/network_access_start.sh
	rgdb -A $TROOT/network_access.php -V generate_start=0 > /var/run/network_access_stop.sh
	sh /var/run/network_access_start.sh > /dev/console
	;;
stop)
	if [ -f /var/run/network_access_stop.sh ]; then
		sh /var/run/network_access_stop.sh > /dev/console
		rm -f /var/run/network_access_stop.sh
	fi
	;;
reload)
	if [ "`pidof smbd`" = "" ]; then
	/usr/sbin/get_device_name 
	rgdb -A $TROOT/network_access.php -V generate_start=1 > /var/run/network_access_start.sh
	sh /var/run/network_access_start.sh > /dev/console
	else
	#update db for open mode
	/usr/sbin/get_device_name 
	#update the config file
	rgdb -A $TROOT/network_access.php -V generate_start=1 
	#reload
	rgdb -A $TROOT/network_access.php -V generate_start=2 > /var/run/network_access_reload.sh
	sh /var/run/network_access_reload.sh > /dev/console
	fi
	;;
*)
	echo "usage: network_access.sh {start|stop|restart}"
	;;
esac
