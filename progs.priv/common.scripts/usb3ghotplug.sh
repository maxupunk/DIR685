#!/bin/sh
#This script is designed to be called by udev/hotplug
WANMODE=`rgdb -g /wan/rg/inf:1/mode`

#2 is vid 
#3 is pid
#4 is kernel name
#5 is model name

echo "[$0] [$1] [$2] [$3] [$4] [$5] [$6].." > /dev/console

#for kernel 2.6 use
case "$1" in
start)
	echo "[$0] alpha_3gtool --Debug -v $2 -p $3 -k $4 -m $5" > /dev/console 
	/usr/sbin/alpha_3gtool --Debug -v $2 -p $3 -k $4 -m $5

	if [ "$WANMODE" = "6" ]; then
	sleep 5
	echo "[$0] submit WAN" > /dev/console
	submit WAN
	fi
	;;
stop)
	echo "[$0] stop .." > /dev/console
	/usr/sbin/alpha_3gtool --Debug --clear
	
	if [ "$WANMODE" = "6" ]; then
	sh /var/run/wan_stop.sh
	fi
	;;
	
restart)
	echo "[$0] alpha_3gtool --Debug -v $2 -p $3 -k $4 -m $5" > /dev/console 
	/usr/sbin/alpha_3gtool --Debug -v $2 -p $3 -k $4 -m $5
	
	echo "[$0] restart .." > /dev/console
	if [ "$WANMODE" = "6" ]; then
	killall -w pppd;
	sh /var/run/wan_stop.sh
	echo "[$0] submit WAN" > /dev/console
	submit WAN
	fi
	;;

switch)
	echo "[$0] switch alpha_3gtool --Debug -v $2 -p $3 -k $4 -m $5" > /dev/console 
	/usr/sbin/alpha_3gtool --Debug -v $2 -p $3 -k $4 -m $5
	;;
	
killpppd)
	echo "[$0] killpppd $2" > /dev/console
	killall pppd;
	;;

#for kernel 2.4 use
start_dial)
	if [ "$WANMODE" = "6" ]; then
		#we need to remake config file for pppd
		submit WAN
	fi
	;;
	
stop_dial)
	if [ "$WANMODE" = "6" ]; then
	sh /var/run/wan_stop.sh
	fi
	;;	
*)
	echo "Usage: usb3ghotplug.sh {start|stop|restart|killpppd|start_broadcast|stop_broadcast}"
	;;
esac
exit 0
