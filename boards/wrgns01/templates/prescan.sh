#!/bin/sh
echo [$0] ... > /dev/console
TROOT="/etc/templates"
case "$1" in
start)
	rgdb -A $TROOT/prescan.php -V generate_start=1 > /var/run/prescan.sh
	sh /var/run/prescan.sh > /dev/console
#	rm -f /var/run/user_add.sh
	;;
stop)
	rgdb -A $TROOT/prescan.php -V generate_start=0 > /var/run/prescan_close.sh
	sh /var/run/prescan_close.sh > /dev/console
#	rm -f /var/run/user_del.sh
	;;
now)
	rgdb -A $TROOT/prescan.php -V generate_start=2 > /var/run/scan_media.sh
	sh /var/run/scan_media.sh > /dev/console
	;;
*)
	echo "usage: prescan.sh {start|stop|now}"
	;;
esac
