#!/bin/sh
echo [$0] $1 ... > /dev/console
case "$1" in
get)
	devconf get -f /var/run/rgdb.xml.gz
	if [ "$?" != "0" ]; then
		echo "CAN NOT get devive config, generate default!" > /dev/console
		/etc/scripts/misc/profile.sh reset
		/etc/scripts/misc/profile.sh put
		exit 0
	fi
	gunzip /var/run/rgdb.xml.gz
	rgdb -l /var/run/rgdb.xml
	if [ "$?" != "0" ]; then
		echo "Invalid config, generate default!" > /dev/console
		/etc/scripts/misc/profile.sh reset
		/etc/scripts/misc/profile.sh put
	else
		/etc/scripts/misc/defnodes.sh
	fi
	rm -f /var/run/rgdb.xml
	;;
put)
	rgdb -D /var/run/rgdb.xml
	gzip /var/run/rgdb.xml
	devconf put -f /var/run/rgdb.xml.gz
	if [ "$?" = "0" ]; then
		echo "ok" > /dev/console
	else
		echo "failed" > /dev/console
	fi
	rm -f /var/run/rgdb.xml.gz
	cd
	rgdb -s /sys/restore_default 1
	;;
reset)
	if [ "$2" != "" ]; then
		cp $2 /var/run/rgdb.xml.gz
		rm -f $2
	else
		cp /etc/config/defaultvalue.gz /var/run/rgdb.xml.gz
	fi
	gunzip /var/run/rgdb.xml.gz
	rgdb -l /var/run/rgdb.xml
	/etc/scripts/misc/defnodes.sh
	if [ -f /etc/scripts/freset_setnodes.sh -a "$2" = "" ]; then
		sh /etc/scripts/freset_setnodes.sh
	fi
	rm -f rgdb.xml
	cd
	;;
*)
	echo "Usage: $0 get/put/reset"
esac
