#!/bin/sh
echo [$0] ... > /dev/console
appex_func="`rgdb -i -g /runtime/func/appex`"
appex_en="`rgdb -i -g /apx/enable`"

if [ "$appex_func" = "1" -a "$appex_en" = "1" ]; then
	insmod /lib/modules/appex.o
	sleep 1

	shaperEnable="`rgdb -g /apx/shaperEnable`"
	hostFairEnable="`rgdb -g /apx/hostFairEnable`"
	ipConntrackMax="`cat /proc/sys/net/ipv4/ip_conntrack_max`"
	engineRemain="`cat /proc/net/appex/cmd | grep engine | scut -p : -f 2 -n 2`"

	rgdb -g /apx/tcpAccEnable		> /proc/net/appex/tcpAccEnable
	rgdb -g /apx/dataCompEnable		> /proc/net/appex/dataCompEnable
	rgdb -g /apx/advAccEnable		> /proc/net/appex/advAccEnable
	echo $shaperEnable				> /proc/net/appex/shaperEnable
	rgdb -g /apx/wanAutoDetect		> /proc/net/appex/wanRateAutoDetect
	rgdb -g /apx/wanBurstBytes		> /proc/net/appex/wanBurstBytes
	rgdb -g /apx/wanKbps			> /proc/net/appex/wanKbps
	rgdb -g /apx/wanInBurstBytes	> /proc/net/appex/wanInBurstBytes
	rgdb -g /apx/wanInKbps			> /proc/net/appex/wanInKbps
	rgdb -g /apx/voipAccEnable		> /proc/net/appex/voipAccEnable
	rgdb -g /apx/voipSkipPackets	> /proc/net/appex/voipSkipPackets

	if [ "$shaperEnable" != "1" ]; then
		hostFairEnable=0
	fi

	echo $hostFairEnable			> /proc/net/appex/hostFairEnable
#we don't set those values, just use default value in module	
#	rgdb -g /apx/hostTcpAccSessNum	> /proc/net/appex/hostFairTcpAccSessNum
#	rgdb -g /apx/hostTcpActSessNum	> /proc/net/appex/hostFairTcpActSessNum
#	rgdb -g /apx/hostUdpSessNum		> /proc/net/appex/hostFairUdpSessNum

	echo "engine: $ipConntrackMax $engineRemain" > /proc/net/appex/cmd
else
	rmmod appex
fi
