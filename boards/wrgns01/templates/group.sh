#!/bin/sh
echo [$0] ... > /dev/console
TROOT="/etc/templates"
case "$1" in
add)
	rgdb -A $TROOT/group.php -V generate_start=1 > /var/run/group_add.sh
	sh /var/run/group_add.sh > /dev/console
#	rm -f /var/run/group_add.sh
	;;
del)
	rgdb -A $TROOT/group.php -V generate_start=0 > /var/run/group_del.sh
	sh /var/run/group_del.sh > /dev/console
	rm -f /var/run/group_del.sh
	;;
*)
	echo "usage: group.sh {add|mod|del}"
	;;
esac
