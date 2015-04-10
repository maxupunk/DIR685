#!/bin/sh
echo "[$0]vendor = $1" > /dev/console
echo "[$0]product = $2" > /dev/console
case "$1" in
1a8d)
	echo "Brand: BandRich, Inc" > /dev/console
	if [ "$2" = 1000 ]; then
	echo "sleep 3" > /dev/console
	sleep 3
	usb_modeswitch -v 0x1a8d -p 0x1000 -m 0x05 -M 555342435886b2851200000080000603000000020000000000000000000000 -n 1 -r 0x82 > /dev/console
	echo "sleep 1" > /dev/console
	sleep 1 
	usb_modeswitch -v 0x1a8d -p 0x1000 -m 0x05 -M 55534243f814b9851200000080000603000000020000000000000000000000 -n 1 -r 0x82 > /dev/console
	echo "sleep 1" > /dev/console
	sleep 1 
	usb_modeswitch -v 0x1a8d -p 0x1000 -m 0x05 -M 5553424308a0e2851200000080000600000000020000000000000000000000 -n 1 -r 0x82 > /dev/console
	echo "sleep 5" > /dev/console
	sleep 5
	usb_modeswitch -v 0x1a8d -p 0x1000 -m 0x05 -M 555342435886b2851200000080000603000000020000000000000000000000 -n 1 -r 0x82 > /dev/console
	echo "sleep 1" > /dev/console
	sleep 1 
	usb_modeswitch -v 0x1a8d -p 0x1000 -m 0x05 -M 55534243f814b9851200000080000603000000020000000000000000000000 -n 1 -r 0x82 > /dev/console
	echo "sleep 1" > /dev/console
	sleep 1 
	usb_modeswitch -v 0x1a8d -p 0x1000 -m 0x05 -M 5553424308a0e2851200000080000600000000020000000000000000000000 -n 1 -r 0x82 > /dev/console
#	/usr/sbin/usb_modeswitch -v 0x1a8d -p 0x1000 -V 0x1a8d -P 0x1002 -m 0x05 -r 0x82 -M 55534243109298820000000000000600000000000000000000000000000000 > /dev/console
#	echo "sleep 1" > /dev/console
#	sleep 1 
#	/usr/sbin/usb_modeswitch -v 0x1a8d -p 0x1000 -V 0x1a8d -P 0x1002 -m 0x05 -r 0x82 -M 555342439034a0820000000000000600000000000000000000000000000000 > /dev/console

	#remove the modem link if it already exist
	rm /dev/usb_modem_dialing_link
	ln -s /dev/ttyUSB0 /dev/usb_modem_dialing_link
	echo "[$0]making device file link..." > /dev/console
	fi
	;;
07d1)
	echo "Brand: D-Link" > /dev/console
#	if [ "$2" = A800 ]
#	echo "sleep 3, running background" > /dev/console
#	sleep 3
#	/usr/sbin/usb_modeswitch -v 0x07d1 -p 0xA800 -m 0x01 -r 0x01 -M 5553424328a662818000000080000606f50402527000000000000000000000 > /dev/console
	
	#remove the modem link if it already exist
#	rm /dev/usb_modem_dialing_link
#	ln -s /dev/ttyUSB2 /dev/usb_modem_dialing_link
#	echo "[$0]making device file link..." > /dev/console
#	fi

# for DWM-156
	echo "Brand: D-Link DWM-156" > /dev/console
	if [ "$2" = a800 ]; then 
	echo "sleep 3, running background" > /dev/console
	sleep 3
	/usr/sbin/usb_modeswitch -v 0x07d1 -p 0xA800 -s $3 > /dev/console
	
	#remove the modem link if it already exist
	rm /dev/usb_modem_dialing_link
	ln -s /dev/ttyUSB0 /dev/usb_modem_dialing_link
	echo "[$0]making device file link..." > /dev/console
	fi
	;;
1c9e)
	echo "Brand: D-Link" > /dev/console
	if [ "$2" = f000 ]; then
	echo "sleep 3, running background" > /dev/console
	sleep 3
	/usr/sbin/usb_modeswitch -W -v 0x1c9e -p 0xf000 -V 0x1c9e -P 0x9603 -m 0x01 -r 0x01 -M 5553424328a662818000000080000606f50402527000000000000000000000 > /dev/console
	
	#remove the modem link if it already exist
	rm /dev/usb_modem_dialing_link
	ln -s /dev/ttyUSB2 /dev/usb_modem_dialing_link
	echo "[$0]making device file link..." > /dev/console
	fi
	;;
1e0e)
	echo "Brand: Alpha" > /dev/console
	if [ "$2" = f000 ]; then
	echo "sleep 3, running background" > /dev/console
	sleep 3
	/usr/sbin/usb_modeswitch -v 0x1e0e -p 0xf000 -V 0x1e0e -P 0x9200 -m 0x01 -M 5553424312345678000000000000061b000000020000000000000000000000 > /dev/console
	
	#remove the modem link if it already exist
	rm /dev/usb_modem_dialing_link
	ln -s /dev/ttyUSB2 /dev/usb_modem_dialing_link
	echo "[$0]making device file link..." > /dev/console
	fi
	;;
0471)
	echo "Edge" > /dev/console
	if [ "$2" = 1210 ]; then
	echo "sleep 3, running background: device is $3" > /dev/console
	sleep 3
	/usr/sbin/usb_modeswitch -e /dev/"$3" > /dev/console
	
	#remove the modem link if it already exist
	rm /dev/usb_modem_dialing_link
	ln -s /dev/ttyACM0 /dev/usb_modem_dialing_link
	echo "[$0]making device file link..." > /dev/console	
	fi
	;;
*)
	echo "unsupported vendor id and/or product id"
	;;
esac

exit 0
