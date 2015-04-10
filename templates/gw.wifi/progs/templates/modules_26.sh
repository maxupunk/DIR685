#!/bin/sh
case "$1" in
insmod)
    if [ "`rgdb -i -g /runtime/func/stun/enabled`" = "1" ]; then
		model="`rgdb -i -g /runtime/layout/image_sign`"
		if [ $model = "wrgn22_dlwbr_dir605b" -o $model = "wrgn22_dlwbr_dir615" -o $model = "wrgn23_dlwbr_dir300b" -o $model = "wrgn23_dlwbr_dir600b" ]; then
			echo 4096 > /proc/sys/net/ipv4/ip_conntrack_max
		fi
		insmod /lib/modules/ip_stun_func.ko
		insmod /lib/modules/sw_tcpip.ko
    fi
	insmod /lib/modules/ifresetcnt.ko
	insmod /lib/modules/ip_conntrack_ike_m.ko
	insmod /lib/modules/ip_conntrack_esp_m.ko
	insmod /lib/modules/ip_conntrack_proto_esp_m.ko
	insmod /lib/modules/ip_nat_proto_esp_m.ko

    if [ "`rgdb -i -g /runtime/func/netsniper`" = "1" ]; then
	insmod /lib/modules/ipt_PERS.ko
    fi

    ;;
rmmod)
	insmod /lib/modules/ip_nat_proto_esp_m.ko
	insmod /lib/modules/ip_conntrack_proto_esp_m.ko
	insmod /lib/modules/ip_conntrack_esp_m.ko
	insmod /lib/modules/ip_conntrack_ike_m.ko
	rmmod ifresetcnt
	if [ "`rgdb -i -g /runtime/func/stun/enabled`" = "1" ]; then
        	rmmod ip_stun_func
		rmmod sw_tcpip
        fi
	if [ "`rgdb -i -g /runtime/func/netsniper`" = "1" ]; then
		rmmod ipt_PERS
	fi
    ;;
esac

