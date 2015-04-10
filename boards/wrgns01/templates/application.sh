#!/bin/sh
submit GROUP_ADD
submit USER_ADD
submit PURE-FTPD
submit NET_ACCESS
submit UPNP_AV_START
submit ITUNES_START
submit BT_START
rgdb -A /etc/templates/hd_process.php -V generate_start=0 > /var/run/hd_process_stop.sh

#marco , move form config.sh to system.sh
echo 1 > /tmp/started
