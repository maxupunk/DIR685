#!/bin/sh
echo [$0] ... > /dev/console
TROOT="/etc/templates"
case "$1" in
add)
	rgdb -A $TROOT/user.php -V generate_start=1 > /var/run/user_add.sh
	sh /var/run/user_add.sh > /dev/console
#	rm -f /var/run/user_add.sh
	;;
del)
	rgdb -A $TROOT/user.php -V generate_start=0 > /var/run/user_del.sh
	sh /var/run/user_del.sh > /dev/console
#	rm -f /var/run/user_del.sh
	;;
*)
	echo "usage: network_access.sh {start|stop|restart}"
	;;
esac
