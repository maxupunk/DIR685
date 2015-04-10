#!/bin/sh

samba_enable="NO"
. /etc/rc.conf


smbspool=/var/spool/samba
pidfiledir=/var/run

case $UseHddApp in
[Yy][Ee][Ss])
	smbd=/usr/hddapp/sbin/smbd
	nmbd=/usr/hddapp/sbin/nmbd
	;;
*)
	smbd=/usr/sbin/smbd
	nmbd=/usr/sbin/nmbd
	;;
esac

case $samba_enable in
[Yy][Ee][Ss])
       ;;
[Nn][Oo])
       return 0
       ;;
*)
       echo "Please set samba_enable=\"Yes\" in /etc/rc.conf to start samba service"
       ;;
esac

# start
if [ "x$1" = "x" -o "x$1" = "xstart" ]; then
	if [ -f $smbd ]; then
		if [ -d $smbspool ]; then
			rm -f $smbspool/*
		fi
		echo
		echo "##################"
		echo ' Starting Samba'
		echo "##################"
		$smbd -D
		$nmbd -D
	fi

# stop
elif [ "x$1" = "xstop" ]; then
	killall smbd
	kill -9 `cat $pidfiledir/nmbd.pid`
	echo
	echo "##################"
	echo ' Stoping Samba'
	echo "##################"
elif [ "x$1" = "xrestart" ]; then
	$0 stop
	$0 start
fi
