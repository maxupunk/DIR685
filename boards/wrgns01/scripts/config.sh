#!/bin/sh
image_sign=`cat /etc/config/image_sign`

case "$1" in
start)
	echo "Mounting proc and var ..."
	mount -t proc none /proc
	mount -t ramfs ramfs /var
#	cp -r /dev /var/
	mount -t ramfs ramfs /dev
#	mv /var/dev/* /dev
#	rm -rf /var/dev
	mkdir -p /var/etc /var/log /var/run /var/state /var/tmp /var/etc/ppp /var/etc/config /var/dnrd /var/etc/iproute2
	echo -n > /var/etc/resolv.conf
	echo -n > /var/TZ
# change printk loglevel back to 7 from boot quiet parameter.
	echo 7 > /proc/sys/kernel/printk
	#Module for ntfs
	mkdir -p /tmp/storage_dev
	insmod /lib/modules/ufsd.ko
	echo "" > /proc/sys/kernel/hotplug 
	mount -t sysfs . /sys
	
	echo "Starting udevd..." 
	/sbin/udevd --daemon 
	echo "Starting udevstart..." 
	/usr/bin/udevstart 
	echo "Starting udevstart..." 

	if [ -f /lib/modules/switch.ko ]; then
	echo "init switch chip"
	insmod /lib/modules/switch.ko
	mknod /dev/rtl8366sr c 221 0
	fi

	# UNIX 98 pty
	mkdir -p /dev/pts
	mknod -m666 /dev/pts/0 c 136 0
	mknod -m666 /dev/pts/1 c 136 1

	echo "***************  |  SYS:001" > /var/log/messages
	#for arm cpu we have  aligment problem,we need let the kernel handle unalignment problem
	echo 3 > /proc/cpu/alignment
	# The db should be bring up first ...
	echo "Start xmldb ..." > /dev/console
	xmldb -n $image_sign -t > /dev/console &
	sleep 1
	/etc/scripts/misc/profile.sh get
	/etc/templates/timezone.sh set
	/etc/templates/logs.sh
#	hendry modify, to differentiate usb and sata, we use fresetd before we run mnt_dev in udev.
	insmod /lib/modules/nas_gpio_access.ko
	echo "start fresetd ..."		> /dev/console 	
	fresetd &
#	end hendry	

	echo "Inserting modules ..." > /dev/console
	# insert fv13xx drivers
#	insmod /lib/modules/fvmem.ko
#	insmod /lib/modules/fvmac.ko share_mii=1 mac0_phyaddr=4 mac1_phyaddr=5

	# gpio/mii access driver & others
# hendry modify 
#	insmod /lib/modules/nas_gpio_access.ko
	#insmod /lib/modules/fv13xx_access.ko
	insmod /lib/modules/ifresetcnt.ko

	# bring up network devices
	env_lan=`rgdb -i -g /runtime/layout/lanmac`
	ifconfig eth0 hw ether $env_lan up
	env_wan=`rgdb -i -g /runtime/layout/wanmac`
	ifconfig eth1 hw ether $env_wan up
	rgdb -i -s /runtime/wan/inf:1/mac "$env_wan"

	ifconfig eth1 txqueuelen 1000
	ifconfig eth0 txqueuelen 1000
	ifconfig lo up
	TIMEOUT=`rgdb -g /nat/general/tcpidletimeout`
	[ "$TIMEOUT" = "" ] && TIMEOUT=600 && rgdb -s /nat/general/tcpidletimeout $TIMEOUT
	echo "$TIMEOUT" > /proc/sys/net/ipv4/netfilter/ip_conntrack_tcp_timeout_established
	echo 80 > /proc/sys/net/ipv4/netfilter/ip_conntrack_udp_timeout

	brctl addbr br0 	> /dev/console
	brctl stp br0 off	> /dev/console
	brctl setfd br0 0	> /dev/console

	brctl addbr br1 	> /dev/console
	brctl stp br1 off	> /dev/console
	brctl setfd br1 0	> /dev/console

    # Start up LAN interface & httpd
    ifconfig br0 0.0.0.0 up         > /dev/console
    ifconfig br1 0.0.0.0 up         > /dev/console
    /etc/templates/webs.sh start    > /dev/console
#marco
	mount -t usbfs usbfs /proc/bus/usb/
	ln -s /tmp/storage_dev /var/portal_share
	if [ -f /lib/modules/ehci-hcd-FOTG2XX-1.ko ]; then
	    insmod /lib/modules/ehci-hcd-FOTG2XX-1.ko > /dev/console
	fi
	if [ -f lib/modules/ehci-hcd-FOTG2XX.ko ]; then
	    insmod /lib/modules/ehci-hcd-FOTG2XX.ko > /dev/console
	fi

# joel mark now we support kcode not LPR	
#	mkdir -p /var/spool/lpd/lp0
#	lpd -I br0 -Z 1 -U 1 
	echo "" > /var/group
#	submit GROUP_ADD
#	submit USER_ADD
#	submit PURE-FTPD
#	submit NET_ACCESS
#	submit UPNP_AV_START
#	submit ITUNES_START
	nowdate1970=`date | grep 1970`
	nowdate1969=`date | grep 1969`
	if [ "$nowdate1970" != "" ] || [ "$nowdate1969" != "" ]; then
	echo "set time to 2000/01/01"
	date -s 010100002000
	fi	
	
	;;
stop)
	umount /tmp
	umount /proc
	umount /var
	;;
esac
