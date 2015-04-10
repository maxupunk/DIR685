#!/bin/sh
echo [$0] ... > /dev/console
sleep 5
/etc/templates/wan.sh stop > /dev/console
/etc/scripts/misc/profile.sh reset
/etc/scripts/misc/profile.sh put
echo "[$0] reset config done !" > /dev/console
rgdb -s /sys/restore_default 0
reboot
