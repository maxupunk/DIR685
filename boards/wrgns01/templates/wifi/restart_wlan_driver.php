echo "restart WLAN driver ..." > /dev/console
# remove interface from bridge
#brctl delif br0 ra0
#brctl delif br1 ra1
# remove wireless driver
#rmmod /lib/modules/rt2880_iNIC.ko
# install wireless driver
insmod /lib/modules/rt2880_iNIC.ko mode=ap bridge=0
# bring up the interfaces
ifconfig ra0 txqueuelen 1000
# do not up if , let hostapd do it
#ifconfig ra0 up
ifconfig ra1 txqueuelen 1000
#ifconfig ra1 up
# add interfaces to bridge
#brctl addif br0 ra0
#brctl addif br1 ra1
