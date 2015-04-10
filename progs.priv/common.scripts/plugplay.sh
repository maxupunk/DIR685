#!/bin/sh

### fix bug of soft-reboot problem
if [ -f "/usr/sbin/alpha_3gtool" ] ;then  alpha_3gtool -M; fi

USBOLD=0
while [ 1 ];do 

### don't enter until mode 6
WANMODE=`rgdb -g /wan/rg/inf:1/mode`
RECONNMODE=`rgdb -g /wan/rg/inf:1/ppp3g/reconnmode`
AUTORECONNECT=`rgdb -g /wan/rg/inf:1/ppp3g/autoreconnect`
ONDEMAND=`rgdb -g /wan/rg/inf:1/ppp3g/ondemand`

if [ "$WANMODE" != "6" ] ;then sleep 5;continue;fi
if [ "$RECONNMODE" = "2" ] ;then sleep 5;continue;fi
if [ ! -e /var/run/fresetd_unixsock ];then sleep 5;continue;fi

### detect usb plugplay problem
USBNEW=`ls -le /proc/bus/usb/devices | cut -c 55-62`
USBTYPE=`rgdb -i -g "/runtime/stats/usb/devices/driver"`

if [ "$USBTYPE" = "" ] && [ "$USBOLD" != "$USBNEW" ];then
if [ -f "/usr/sbin/alpha_3gtool" ] ;then  alpha_3gtool -M; fi
fi

##### PLUGPLAYSTART
if [ "$USBTYPE" != "" ] && [ "$USBTYPE" != "0" ] && [ "$USBOLD" != "$USBNEW" ];then

if [ "$AUTORECONNECT" = "0" ] && [ "$ONDEMAND" = "0" ];then 
USBOLD=$USBNEW;
continue;
fi

submit WAN
/var/run/ppp-session1.sh stop;sleep 5;
/var/run/ppp-session1.sh start;sleep 30;
USBOLD=$USBNEW
continue;
fi

##### PLUGPLAYSTOP
if [ "$USBTYPE" = "" ] && [ "$USBOLD" != "$USBNEW" ];then
/var/run/ppp-session1.sh stop;sleep 10;
USBOLD=$USBNEW
continue;
fi

### detect state error problem
CONNECTSTATUS=`rgdb -i -g /runtime/wan/inf:1/connectstatus`
if [ "$CONNECTSTATUS" = "connecting" ] || [ "$CONNECTSTATUS" = "disconnecting" ];then
echo "TRY TO WAITING 3G ...";sleep 30;continue;
fi
if [ "$USBTYPE" != "" ] && [ "$USBTYPE" != "0" ] && [ "$CONNECTSTATUS" != "connected" ] && [ "$CONNECTSTATUS" != "ondemand" ];then 
echo "TRY TO CONNECT 3G ...";sleep 10;USBOLD=0;continue;
fi
if [ "$USBTYPE" = "" ] && [ "$CONNECTSTATUS" != "disconnected" ] && [ "$CONNECTSTATUS" != "" ];then 
echo "TRY TO DISCONNECT 3G ...";sleep 10;USBOLD=0;continue;
fi

### fix bug of pppd ondemand mode
if [ "$CONNECTSTATUS" = "ondemand" ] && [ ! -e /var/run/ppp?.pid ];then
echo "TRY TO SAVE THE PPPD ...";sleep 30;USBOLD=0;continue;
fi

sleep 5;
echo -n .
done &

