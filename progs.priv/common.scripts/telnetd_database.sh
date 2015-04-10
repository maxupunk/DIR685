#!/bin/sh
image_sign=`cat /etc/config/image_sign`
TELNETD=`rgdb -g /sys/telnetd`
PROTOCOL=`rgdb -g /sys/consoleprotocol/protocol`
TIMEOUT=`rgdb -g /sys/consoleprotocol/timeout`
if [ "$TELNETD" = "true" -o "$PROTOCOL" = "1" ]; then
	echo "Start telnetd ..." > /dev/console
	if [ -f "/usr/sbin/login" ]; then
		lf=`rgdb -i -g /runtime/layout/lanif`
		if [ ! -z "$TIMEOUT" ]; then
			to="-t $TIMEOUT"
		else
			to=
		fi
		username=@@USERNAME@@
		password=@@PASSWORD@@
		telnetd -l "/usr/sbin/login" -u $username:$password -i $lf @@SHELL@@ $to &
		echo "$!" > /var/run/telnetd.pid
	else
		telnetd &
	fi
else
	echo "Disable start-up daemon: telnetd."
	exit 0
fi
