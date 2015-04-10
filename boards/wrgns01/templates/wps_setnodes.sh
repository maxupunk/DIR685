#!/bin/sh
sleep 3
CONF_PATH="/var/run/RT2860AP.dat"
XMLDBC="xmldbc -s "

WSCSTATUS=`grep WscConfStatus $CONF_PATH | cut -d= -f2`
TMP=`grep SSID $CONF_PATH`
SSID=`echo $TMP | cut -d= -f2 | cut -d\; -f1`
AUTHTYPE=`grep AuthMode $CONF_PATH | cut -d= -f2 | cut -d\; -f1`
ENCRYPTTYPE=`grep EncrypType $CONF_PATH | cut -d= -f2 | cut -d\; -f1`

echo "SSID=$SSID"
if [ "$SSID" != "" ]; then
	xmldbc -s /wireless/ssid $SSID
fi

xmldbc -s /wireless/wps/configured 1

echo "AUTHTYPE=$AUTHTYPE"
echo "ENCYPTTYPE=$ENCRYPTTYPE"
if [ "$AUTHTYPE" != "" ]; then
	case "$AUTHTYPE" in
	OPEN)
		AUTHTYPE="0"
		if [ "$ENCRYPTTYPE" = "NONE" ]; then
			ENCRYPTTYPE="0"
		else
			METHOD="WEP"
		fi
		;;
	SHARED)
		AUTHTYPE="1"
		METHOD="WEP"
		;;
	WPA)
		AUTHTYPE="2"
		;;
	WPAPSK)
		AUTHTYPE="3"
		METHOD="PSK"
		;;
	WPA2)
		AUTHTYPE="4"
		;;
	WPA2PSK)
		AUTHTYPE="5"
		METHOD="PSK"
		;;
	WPAWPA2)
		AUTHTYPE="6"
		;;
	WPAPSKWPA2PSK)
		AUTHTYPE="7"
		METHOD="PSK"
		;;
	*)
		;;
	esac
fi
case "$METHOD" in
	WEP)
		ENCRYPTTYPE="1"
		WEPINDEX=`grep DefaultKeyID $CONF_PATH | cut -d= -f2`
		KEYTYPE="Key"$WEPINDEX"Type"
		KEYSTR="Key"$WEPINDEX"Str"
		WEPTYPE=`grep $KEYTYPE $CONF_PATH | cut -d= -f2`
		WEP=`grep $KEYSTR $CONF_PATH | cut -d= -f2`
		$XMLDBC /wireless/wep/defkey $WEPINDEX
		$XMLDBC /wireless/wep/format $WEPTYPE
		$XMLDBC /wireless/wep/key $WEP
		;;
	PSK)
		if [ "$ENCRYPTTYPE" = "TKIP" ]; then
			ENCRYPTTYPE=2
		else
			ENCRYPTTYPE=3
		fi
		WPAPSK=`grep WPAPSK= $CONF_PATH | cut -d= -f2`
		$XMLDBC /wireless/wpa/key $WPAPSK
		;;
	*)
		;;
esac
$XMLDBC /wireless/authtype $AUTHTYPE
$XMLDBC /wireless/encrypttype $ENCRYPTTYPE
/etc/scripts/misc/profile.sh put > /dev/console
exit 0
