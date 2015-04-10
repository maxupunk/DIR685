#ifndef _RGDB_NODE_DEFINE_H_ 
#define _RGDB_NODE_DEFINE_H_ 
 
/*RGDB node path define*/
#define RGDB_FRAMEIT_COLLECTIONID "/nas_ui/frameit/collection_id"
#define RGDB_GENERAL_MODELNAME "/sys/modelname"
#define RGDB_GENERAL_HWVERSION "/runtime/sys/info/hardwareversion"
#define RGDB_GENERAL_FWVERSION "/runtime/sys/info/firmwareversion"
#define RGDB_GENERAL_UPTIME "/runtime/sys/uptime"
#define RGDB_GZONE_ENABLE  "/gzone/enable"
#define RGDB_GZONE_TX  "/runtime/stats/gzone/tx/bytes"
#define RGDB_GZONE_RX  "/runtime/stats/gzone/rx/bytes"
#define RGDB_HD_DEVNAME "/runtime/nas/store_dev/devname"
#define RGDB_HD_NAME "/runtime/nas/store_dev/name"
#define RGDB_HD_FORMAT "/runtime/nas/store_dev/fsname"
#define RGDB_HD_CAPACITY "/runtime/nas/store_dev/capacity"
#define RGDB_HD_USED "/runtime/nas/store_dev/used"
#define RGDB_HD_AVAILABLE "/runtime/nas/store_dev/available"
#define RGDB_HD_USED_PERCENT "/runtime/nas/store_dev/used_percent"	// 0~100
#define RGDB_HD_HEALTH "/runtime/nas/store_dev/health"
#define RGDB_HD_TEMP_C "/runtime/nas/store_dev/temp/celsius"
#define RGDB_HD_TEMP_F "/runtime/nas/store_dev/temp/fahrenheit"
#define RGDB_HD_SLEEPTIME "/nas/store_dev/sleep_time"
#define RGDB_INTERNET_ROUTER_ENABLE "/runtime/router/enable"	//1:ap mode, 0:router mode
#define RGDB_INTERNET_MODE "/wan/rg/inf:1/mode"
#define RGDB_INTERNET_CONNECT_TYPE "/runtime/wan/inf:1/connecttype"	//1:static, 2:dhcp, 3:pppoe, 4:pptp, 5:l2tp
#define RGDB_INTERNET_CABLE_STATUS "/runtime/switch/wan_port/linktyp"	//0: disconnect, 1:100Full, 2: 100half, 3: 10 full, 4: 10half
#define RGDB_INTERNET_NETWORK_STATUS "/runtime/wan/inf:1/connectstatus"
#define RGDB_INTERNET_CONNECT_TIME "/runtime/wan/inf:1/uptime"
#define RGDB_INTERNET_MACADDR "/runtime/wan/inf:1/mac"
#define RGDB_INTERNET_IPADDR "/runtime/wan/inf:1/ip"
#define RGDB_INTERNET_NETMASK "/runtime/wan/inf:1/netmask"
#define RGDB_INTERNET_GATEWAY "/runtime/wan/inf:1/gateway"
#define RGDB_LCD_SLEEPTIME "/nas/ui/Lcd/sleep_time"
#define RGDB_LCD_BRIGHTNESS "/nas/ui/Lcd/brightness"
#define RGDB_LAN_TX  "/runtime/stats/lan/tx/bytes"	//lan send
#define RGDB_LAN_RX  "/runtime/stats/lan/rx/bytes"	//lan recevied
#define RGDB_PHOTO_TIME_DISPLAY "/nas/ui/photo_time_display"
#define RGDB_SCREENSAVER_SLEEPTIME "/nas/ui/screen_saver/sleep_time"
#define RGDB_TIMEZONE "/time/timezone"
#define RGDB_WIRED_MACADDR "/runtime/layout/lanmac"
#define RGDB_WIRED_IPADDR "/lan/ethernet/ip"
#define RGDB_WIRED_NETMASK "/lan/ethernet/netmask"
#define RGDB_WIRED_DHCP_SERVER "/lan/dhcp/server/enable" //1:enable 0:disable
#define RGDB_WIRED_CABLE_P1 "/runtime/switch/port:4/linkType"
#define RGDB_WIRED_CABLE_P2 "/runtime/switch/port:3/linkType"
#define RGDB_WIRED_CABLE_P3 "/runtime/switch/port:2/linkType"
#define RGDB_WIRED_CABLE_P4 "/runtime/switch/port:1/linkType"
#define RGDB_WIRELESS_RADIO "/wireless/enable"
#define RGDB_WIRELESS_AUTOCHANNEL_ENABLE "/wireless/autochannel"
#define RGDB_WIRELESS_CHANNEL "/wireless/channel"
#define RGDB_WIRELESS_AUTO_CHANNEL "/runtime/stats/wireless/channel"
#define RGDB_WIRELESS_HOST_SSID "/wireless/ssid"
#define RGDB_WIRELESS_GUEST_SSID "/wlan/inf:2/ssid"
#define RGDB_WIRELESS_MODE "/wireless/wlanmode"	// bit[0]=11b, bit[1]=11g, bit[2]=11n 1: 11b mode, 2: 11g mode, 3: 11g+11b mode, 4: 11n mode, 5: 11n+11b mode, 6: 11n+11g mode, 7: 11n+11g+11b mode
#define RGDB_WIRELESS_BANDWIDTH "/wireless/bandwidth" //1:11n HT20, 2:11n Auto20/40
#define RGDB_WIRELESS_HOST_SECURITY "/wireless/encrypttype"		//0:disable, 1:wep, 2:tkip, 3: aes, 4: tkip+aes
#define RGDB_WIRELESS_GUEST_SECURITY "/wlan/inf:2/encrypttype"
#define RGDB_WIRELESS_MACADDR "/runtime/layout/wlanmac"
#define RGDB_WIRELESS_WPS_PIN "/wireless/wps/pin"
#define RGDB_WIRELESS_RUNTIME_WPS_PIN "/runtime/wps/pin"
#define RGDB_WAN_TX  "/runtime/stats/wan/inf:1/tx/bytes"
#define RGDB_WAN_RX  "/runtime/stats/wan/inf:1/rx/bytes"
#define RGDB_WIRELESS_TX  "/runtime/stats/wireless/tx/bytes"
#define RGDB_WIRELESS_RX  "/runtime/stats/wireless/rx/bytes"
#define RGDB_WPS_SET_PIN_CODE "/wireless/wps/pin"
#define RGDB_WPS_GET_PIN_CODE   "/runtime/genpin"
#define RGDB_HW_NAT "/runtime/hw_nat/enable" //add by sonnia at 2009/2/3 01:46pm
#define RGDB_WPS_ENABLE "/wireless/wps/enable"

/* buffer define*/
#define RGDBBUFFER_SIZE     128

/* buffer type define*/
typedef unsigned char  _u8; //for example "_u8 rgdb_val_buf[RGDBBUFFER_SIZE]" 

#endif
