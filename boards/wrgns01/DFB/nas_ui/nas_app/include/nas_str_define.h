#ifndef _NAS_STR_DEFINE_H_
#define _NAS_STR_DEFINE_H_

/*main.c*/
//"Router Settings","Photos","FrameChannel","Router Statistics","Status","WPS"
//"Sun","Mon","Tue","Wed","Thu","Fri","Sat"
#define TITLE_ROUTER_SET "Settings"
#define TITLE_PHOTOS "Photos"
#define TITLE_FRAMECHANNEL "FrameChannel"
#define TITLE_STATISTIC_SHOW "Statistics"
#define TITLE_STATUS "Status"
#define TITLE_WPS "WPS"

#define WEEK_SUN "Sun"
#define WEEK_MON "Mon"
#define WEEK_TUE "Tue"
#define WEEK_WED "Wed"
#define WEEK_THU "Thu"
#define WEEK_FRI "Fri"
#define WEEK_SAT "Sat"

/*frame_channel.c*/
//"Reset Channel","Manual Channel Update","Display All Channels"
#define TITLE_CHANNELS_DISPLAY "Display All Channels"
#define TITLE_RESET_CHANNEL "Reset Channel"
#define TITLE_CHANNEL_UPDATA "Manual Channel Update"

/*setting.c*/
//"LCD Luminance Settings","Hard Drive Hibernation Settings","LCD Hibernation Settings","Clock Display Settings"
#define TITLE_LCD_LUN_SET "LCD Brightness"
#define TITLE_HD_SLEEP_SET "Power Settings"
#define TITLE_LCD_SLEEP_SET "LCD Hibernation Settings" 
#define TITLE_CLOCK_DISPLAY_SET "Clock Display Settings"

/*status.c*/
//"Wireless Status","Hard Disk Status","General Router Info","Internet Status","Wired Status"
#define TITLE_WIRELESS_STATUS "Wireless Status"
#define TITLE_HD_STATUS "Hard Disk Status"
#define TITLE_ROUTER_STATUS "General Router Information"
#define TITLE_INTERNET_STATUS "Internet Status"
#define TITLE_WIRED_STATUS "LAN Status"

//////////////////////////////////////////////
//Use at display_saving and harddevice_saving.c
#define SLEEP_5MIN "5"
#define SLEEP_10MIN "10"
#define SLEEP_15MIN "15"
#define SLEEP_30MIN "30"
#define SLEEP_60MIN "60"
#define SLEEP_90MIN "90"
#define SLEEP_120MIN "120min"
#define SLEEP_NEVER "Never"
//Use at frameit_handler and fcrss_handler.c
#define NETWORK_ERROR "Network Is Unreachable!"
#define DNS_ERROR_MSG "DNS ERROR!"
//Use at adjust_luminance,harddevice_saving,and display_saving.c 
#define SAVE_MSG "Save and apply settings?" 
//Use at harddevice_saving and st_router_info.c
#define NO_HD_ALERT "No Hard Disk found!"
///////////////////////////////////////////////

/*adjust_luminance.c*/
#define TITLE_LCD_LUN "Adjust the LCD Brightness"
#define LCD_LUM_DARK "Darker"
#define LCD_LUM_BRI "Brighter"

/*album_local_app.c*/
#define ALBUM_ALERT "Can't find folders or photos" 
#define IMAGE_UNSUPPORT_ALERT "Photo type is not supported!" 

/*alert_center.c*/
#define ALERT_CENTER_MSG "Press Center Button"

/*clock_display.c*/
#define CLOCK_DISPLAY_MSG "Show date/time during slideshow?"

/*confirm_center.c*/
#define SELECT_YES "Yes"
#define SELECT_NO "No"

/*detect_info.c*/
#define DETECT_INFO_FORMAT_OK "Format OK."
#define DETECT_INFO_FORMAT_FAIL "Format Error."
#define DETECT_INFO_FORMAT_HD "Format Hard Drive."
#define DETECT_INFO_DETECT_HD "Hard Drive Detected."
#define DETECT_INFO_ASK "Do you want to format?"
#define DETECT_INFO_DOFORMAT "Formatting..."
#define DETECT_INFO_WAIT "Please wait." 
#define DETECT_INFO_FIRMWARE "Firmware upgrading ..."
#define DETECT_INFO_DOBACKUP_HD  "Don't power off the device."
#define DETECT_INFO_DETECT_HDMOUNT "Hard Drive Detected Successfully."
#define DETECT_INFO_BACKUP_OK "Backup Successful."
#define DETECT_INFO_BACKUP_FAIL "Backup Failed."
#define DETECT_INFO_BACKUP_ERR "USB storage device is larger \nthan 20GB."
#define DETECT_INFO_DETECT_USB "USB storage device detected."
#define DETECT_INFO_VIEW_PHOTO "Directly view photos ?"
#define DETECT_INFO_BACKUP_USB "Backup data from USB \nstorage device?"
#define DETECT_INFO_DOBACKUP_USB "Backing up USB data ..."
#define DETECT_INFO_DODETECT "Detecting hard drive ..."
#define DETECT_INFO_DODETECT_ERROR "Detect hard drive failed."
#define DETECT_INFO_DOUNMOUNTING "Unmounting hard drive ..."
#define DETECT_INFO_DOUNMOUNTING_SUCCESS "Unmount success."
#define DETECT_INFO_DOUNMOUNTING_ERROR "Unmount hard drive failed."

/*display_saving.c*/
#define TITLE_LCD_SLEEP "Display Hibernation Time"
#define LCD_SLEEP_MSG1 "Set the display to hibernate when display is "
#define LCD_SLEEP_MSG2 "inactive for:"
//#define LCD_SLEEP_MSG2 "when display is inactive for:"

/*fcrss_handler.c*/
#define FCRSS_UNIXSOCK_FAIL "Trying to Connect to Server..."
#define FCRSS_GET_ACTIVE_CODE_FAIL "Failed to get Activation Code"
#define FCRSS_EVER_REGISTER "Registration Successful!!"
#define FCRSS_NEVER_REGISTER "Please Register Account!!"
#define FCRSS_FCNODE_ISNULL "No Service..."
#define FCRSS_RESET_FRAMEID_FAIL "Reset FrameId Failed!"
#define FCRSS_RESET_FRAMEID "Frame ID has been reset."
#define FCRSS_UPDATE_SUCCESS "FrameChannel Update Success!"
#define FCRSS_UPDATE_FAIL "FrameChannel Update FAILED!"
#define FCRSS_DO_GET_ACTIVE_CODE "Getting Activation Code..."
#define FCRSS_CHECK_REGISTER "Checking Registration Status..."

/*frameit_display_app.c*/
#define FRAMEIT_DISPLAY_MSG "Loading..."

/*frameit_handler.c*/
#define FRAMEIT_HANDLER_MSG "Service Initialization..."

/*harddevice_saving.c*/
#define TITLE_HD_SLEEP "Hard Disk Sleep Time"
#define HD_SLEEP_MSG "Hibernate the Hard Drive after being inactive for:"

/*reset_frameid_app.c*/
#define RESET_FRAMEID_MSG "Reset FrameChannel ID?" 

/*screen_saver_app.c*/
#define DEFAULT_MERIDIAN_AM "AM"
#define DEFAULT_MERIDIAN_PM "PM"
#define DEFAULT_TIMESTR_PART ":"

/*show_statistics.c*/
#define TITLE_STATISTIC_INFO "Statistics" 
#define STATISTIC_MB "Send/Receive Rate    Mbps"
#define STATISTIC_KB "Send/Receive Rate     Kbps"
#define STATISTIC_WIRELESS "Wireless"
#define STATISTIC_INTERNET "Internet"
#define STATISTIC_NETWORK "Network"

/*st_router_info.c*/
#define FUNC_ENABLE "Enabled"
#define FUNC_DISABLE "Disabled"
#define ROUTERINFO_GENERAL_INFO "General Router Information"
#define ROUTERINFO_GENERAL_MODELNAME "Model Name :"
#define ROUTERINFO_GENERAL_HWVERSION "Hardware Version :"
#define ROUTERINFO_GENERAL_FWVERSION "Firmware Version :"
#define ROUTERINFO_GENERAL_UPTIME "System Up Time :"
#define ROUTERINFO_GENERAL_NEWFW "New Firmware :"

#define ROUTERINFO_INTERNET_STATUS "Internet Status"
#define ROUTERINFO_INTERNET_CONNECT_TYPE "Connection Type :"
#define ROUTERINFO_INTERNET_CABLE_STATUS "Cable Status :"
#define ROUTERINFO_INTERNET_NETWORK_STATUS "Network Status :"
#define ROUTERINFO_INTERNET_CONNECT_TIME "Connection Time :"
#define ROUTERINFO_INTERNET_MACADDR "MAC Address :"
#define ROUTERINFO_INTERNET_IPADDR "IP Address :"
#define ROUTERINFO_INTERNET_NETMASK "Subnet Mask :"
#define ROUTERINFO_INTERNET_GATEWAY "Gateway :"

#define ROUTERINFO_WIRED_STATUS		"LAN Status"
#define ROUTERINFO_WIRED_MACADDR	"MAC Address :"
#define ROUTERINFO_WIRED_IPADDR 	"IP Address :"
#define ROUTERINFO_WIRED_NETMASK 	"Subnet Mask :"
#define ROUTERINFO_WIRED_DHCP_SERVER "DHCP Server :"
#define ROUTERINFO_WIRED_CABLE_P1 	"Cable Status Port 1 :"
#define ROUTERINFO_WIRED_CABLE_P2 	"Cable Status Port 2 :"
#define ROUTERINFO_WIRED_CABLE_P3 	"Cable Status Port 3 :"
#define ROUTERINFO_WIRED_CABLE_P4 	"Cable Status Port 4 :"

#define ROUTERINFO_WIRELESS_STATUS		"Wireless Status"
#define ROUTERINFO_WIRELESS_RADIO 		"Wireless Radio :"
#define ROUTERINFO_WIRELESS_CHANNEL 	"Wireless Channel :"
#define ROUTERINFO_WIRELESS_HOST_SSID	"Host Network Name(SSID) :"
#define ROUTERINFO_WIRELESS_GUEST_SSID	"Guest Network Name(SSID) :"
#define ROUTERINFO_WIRELESS_MODE 		"802.11 Mode :"
#define ROUTERINFO_WIRELESS_HOST_SECURITY 	"Host Zone Security Mode :"
#define ROUTERINFO_WIRELESS_GUEST_SECURITY 	"Guest Zone Security Mode :"
#define ROUTERINFO_WIRELESS_MACADDR 	"MAC Address :"
#define ROUTERINFO_WIRELESS_WPS_NUMBER 	"WPS PIN Number :"

#define ROUTERINFO_HD_SPACE 	"Available Hard Disk Space"
#define ROUTERINFO_HD_NAME 		"HD :"
#define ROUTERINFO_HD_FORMAT 	"Format :"
#define ROUTERINFO_HD_CAPACITY 	"Capacity :"
#define ROUTERINFO_HD_USED 		"Used :"
#define ROUTERINFO_HD_AVAILABLE "Available :"
#define ROUTERINFO_HD_HEALTH 	"Disk Health :"
#define ROUTERINFO_HD_TEMP 		"Disk Temp :"

#define ST_ROUTER_HD_AVAILABLE "Available"
#define ST_ROUTER_HD_USED "Used"
#define ST_ROUTER_STATIC "Static IP"
#define ST_ROUTER_DHCP "DHCP client"
#define ST_ROUTER_PPPOE "PPPoE"
#define ST_ROUTER_PPTP "PPTP"
#define ST_ROUTER_L2TP "L2TP"
#define ST_ROUTER_WWAN "WWAN(3g)"
#define ST_ROUTER_100FULL "100 Full"
#define ST_ROUTER_100HALF "100 Half"
#define ST_ROUTER_10FULL "10 Full"
#define ST_ROUTER_10HALF "10 Half"
#define ST_ROUTER_1000FULL "1000 Full"
#define ST_ROUTER_1000HALF "1000 Half"
#define ST_ROUTER_DISCONNECT "Disconnected"
#define ST_ROUTER_WEP "WEP"
#define ST_ROUTER_WPA "WPA/WPA2"
#define ST_ROUTER_WLAN_MODE_B "802.11b"
#define ST_ROUTER_WLAN_MODE_G "802.11g"
#define ST_ROUTER_WLAN_MODE_BG "802.11g, 802.11b"
#define ST_ROUTER_WLAN_MODE_N "802.11n"
#define ST_ROUTER_WLAN_MODE_NB "802.11n, 802.11b"
#define ST_ROUTER_WLAN_MODE_NG "802.11n, 802.11g"
#define ST_ROUTER_WLAN_MODE_NBG "802.11n, 802.11g & 802.11b"
#define ST_ROUTER_FORMAT_MAC "00:00:00:00:00:00"
#define ST_ROUTER_FORMAT_IP "0.0.0.0"
#define ST_ROUTER_FORMAT_TIME "0 Days, 00h:00m:00s"
#define ST_ROUTER_FIREWARE_MSG "Checking Firmware Version ..." 

/*wps.c*/
#define WPS_MSG "WPS In Progress"
#define WPS_ERROR "WPS Error"
#define WPS_OVERLAP "WPS Overlap"
#define WPS_SUCCESS "WPS Success"
#define WPS_GET_PIN "Getting PIN"
#define WPS_PIN_ERROR "Get PIN Error"
#define WPS_DISABLE "WPS Disable"

#endif /* _NAS_STR_DEFINE_H_ */ 
