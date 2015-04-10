#!/bin/sh
echo [$0] ... > /dev/console
# +++ Teresa, 2009/1/7 02:21下午
# Stop LCD Display(alpha_nas)
if [ -f /etc/templates/lcd_display.sh ]; then
/etc/templates/lcd_display.sh fw_upgrade &		> /dev/console
fi
# --- Teresa, 2009/1/7 02:21下午
if [ "`rgdb -i -g /runtime/func/lpd`" = "1" ]; then
/etc/templates/lpd.sh stop		> /dev/console
fi
# stop Neaps
/etc/templates/neaps.sh stop	> /dev/console
# stop LLD2D
/etc/templates/lld2d.sh stop	> /dev/console
# Stop WAN
/etc/templates/wan.sh stop		> /dev/console
# Stop UPNP ...
/etc/templates/upnpd.sh stop	> /dev/console
# stop fresetd ...
killall fresetd
# stop DNRD
/etc/templates/dnrd.sh stop		> /dev/console
# Stop RG
/etc/templates/rg.sh stop		> /dev/console
# Stop GZONE
if [ -f /var/run/gzone_stop.sh ]; then
sh /var/run/gzone_stop.sh		> /dev/console
fi
# Stop WLAN
/etc/templates/wlan.sh stop		> /dev/console
# Stop LAN
/etc/templates/lan.sh stop		> /dev/console
# +++ Teresa, 2008/12/31 04:09下午
if [ -f /etc/templates/hd_process.sh ]; then
/etc/templates/hd_process.sh stop		> /dev/console
fi
# Stop fcrss server
if [ -f /etc/templates/fcrss_server.sh ]; then
/etc/templates/fcrss_server.sh stop		> /dev/console
fi
# Stop
killall fresetd &
killall udevd &
# --- Teresa, 2008/12/31 04:09下午
# Start to burn flash
/etc/scripts/startburning.sh	> /dev/console
	