#!/bin/sh
mkdir -p /tmp/fc_icon
mkdir -p /tmp/fit_icon
echo [$0] $1... > /dev/console
TROOT="/etc/templates"
case "$1" in
start)
	cp /directfb/directfbrc /var/.
#	/directfb/fcrss_server &
	sh /etc/templates/fcrss_server-loop.sh &
	echo $! > /var/run/fcrss_server-loop.pid
	;;
stop)
	if [ -f /var/run/fcrss_server-loop.pid ]; then
    pid=`cat /var/run/fcrss_server-loop.pid`
    if [ $pid != 0 ]; then
    kill $pid > /dev/null 2>&1
    fi
    rm -f /var/run/fcrss_server-loop.pid
    fi
	killall -9 fcrss_server		
	;;
restart)
	$0 stop
	$0 start
	;;
*)
	echo "usage: fcrss_server.sh {start|stop|restart}"
	;;
esac
