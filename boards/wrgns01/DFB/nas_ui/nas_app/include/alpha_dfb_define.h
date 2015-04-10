#ifndef _ALPHA_DFB_DEFINE_H_ 
#define _ALPHA_DFB_DEFINE_H_

/*system define*/ 
//#define DEBUG 1
#define SHOW_BIG 0
#define FILE_MAX_SIZE 5000000
#define NEED_COMPRESS_SIZE 1000000
#define NOTJPEG_MAX_SIZE 1000000
#define PHOTO_TMP_DIR "/tmp/.photo"
#define STORAGE_DEV_PATH "/tmp/storage_dev/"
#define MOUNT_TABLE_PATH "/tmp/mount_table"
#define ONBOARD_PATH "/directfb/"
#define RESULT_SCREENSAVERTIMEOUT_KEY -1
//999minutes-> because NEVER_RUN_TIMEOUT should bigger than HD and LCD max timeout=120min, and screen saver max timeout=60min
#define NEVER_RUN_TIMEOUT 999*60	//if timeout > 120 minutes(ex:130 minutes) , is never run.
#define DETECTING_TIMEOUT  45	//timeout for detecting device. if > timeout, show error messg.
#define UNMOUNTING_TIMEOUT 60	//timeout for unmounting device. if > timeout, show error messg.
#define ALL_CHANNELS_EXE 1 //set 1, system will first execute all_channels application.
//+++ Teresa Ke
#define DEFAULT_MSG_MAX_LINE		5
#define DEFAULT_MSG_MAX_TEXT_LENGTH	64

/* font define*/
#define FONTS ONBOARD_PATH"font"
#define FONTS_DECKER FONTS"/Arena Condensed Bold.ttf"
#define FONTS_DIGI FONTS"/DS-DIGI.TTF"

/* images define*/
#define IMAGES ONBOARD_PATH"images"
#define BG_0_G IMAGES"/screen_main_menu.png"
#define WAN_ON_G IMAGES"/685_internet-ON.png"
#define FRAMECHANNEL_ON_G IMAGES"/f.png"
#define CONFIRM_BG IMAGES"/confirm.png"
#define M_IMAGE_G IMAGES"/pub_everyone.gif"
#define MENU_0_G IMAGES"/Settings.png"
#define MENU_1_G IMAGES"/framechannel.png"
#define MENU_2_G IMAGES"/Statistics.png"
#define MENU_3_G IMAGES"/Status.png"
#define MENU_4_G IMAGES"/WPS.png"
#define MENU_5_G IMAGES"/frameit.png"
#define MENU_6_G IMAGES"/M/upnp.png"
#define UPNP_0_G IMAGES"/M/upnp_controller.png"
#define UPNP_1_G IMAGES"/M/upnp_renderer.png"
#define APP_0_G IMAGES"/A/calendar.png"
#define APP_1_G IMAGES"/A/DateTime.png"
#define APP_2_G IMAGES"/A/Photos.png"
#define APP_3_G IMAGES"/A/Weather.png"
#define APP_4_G IMAGES"/A/RSSChannel1.png"
#define APP_5_G IMAGES"/A/RSSChannel2.png"
#define APP_6_G IMAGES"/A/rss_update.png"
#define STAT_1_G_P1 IMAGES"/B/HD Bar.png"
#define STAT_1_G_P2 IMAGES"/B/HD Main.png"
#define STAT_0_G IMAGES"/B/Downloads.png"
#define STAT_1_G IMAGES"/B/Hard Disk Status.png"
#define STAT_2_G IMAGES"/B/General Info.png"
#define STAT_3_G IMAGES"/B/Internet Status.png"
#define STAT_4_G IMAGES"/B/Wired Status.png"
#define STAT_5_G IMAGES"/B/Wireless Status.png"
#define SET_0_G IMAGES"/E/Luminance.png"
#define SET_1_G IMAGES"/E/Power Saving.png"
#define SET_2_G IMAGES"/E/Screen Saver.png"
#define SET_3_G IMAGES"/E/reset_frameid.png"
#define SET_4_G IMAGES"/E/photo_time_display.png"
#define WPS_0_G IMAGES"/D/Bar left.png"
#define WPS_1_G IMAGES"/D/Bar right.png"
#define FOLDER_G IMAGES"/A/Folder.png"
#define FOLDER_SELECTED_G IMAGES"/A/Folder-1.png"
#define HD_G IMAGES"/A/hdd_unmount.png"
#define USB_G IMAGES"/A/usbpendrive_unmount.png"
#define SCREEN_SAVER_BG "screen_bg.jpg"		// "HD_PATH/SCREEN_SAVER_BG"
#define PHOTO_LOADING_G IMAGES"/loading.png"
#define MOVE_RIGHT_G IMAGES"/next.png"
#define MOVE_LEFT_G IMAGES"/previous.png"
#define MOVE_UP_G IMAGES"/up.png"
#define MEDIA_PLAY_0_G IMAGES"/M/play.png"
#define MEDIA_PLAY_1_G IMAGES"/M/stop.png"
#define MEDIA_PLAY_2_G IMAGES"/M/pause.png"
#define MEDIA_PLAY_3_G IMAGES"/M/mute.png"
#define MEDIA_PLAY_4_G IMAGES"/M/vup.png"
#define MEDIA_PLAY_5_G IMAGES"/M/vdown.png"
#define WAN_PORT_UP_G IMAGES"/TV/wan_icon.png"
#define LAN_PORT_1_UP_G IMAGES"/TV/TV_1_icon.png"
#define LAN_PORT_2_UP_G IMAGES"/TV/TV_2_icon.png"
#define LAN_PORT_3_UP_G IMAGES"/TV/TV_3_icon.png"
#define LAN_PORT_4_UP_G IMAGES"/TV/TV_4_icon.png"
#define ALL_PORT_DOWN_G IMAGES"/TV/ports_down.png"

/* execute file define*/
#define CHECK_DOMAIN_NAME ONBOARD_PATH"check_domain_name"
#define WEB_TCPREQ ONBOARD_PATH"web_tcpreq"

/* time define*/	
typedef unsigned int  _u32;	

typedef struct time_tab{
	time_t timep;
	int TimeZone;			//add by sonnia at 20080911
	int ScreenSaverTimeout;
	int DisplaySaverTimeout; //add by sonnia
	int HardDriveTimeout; 	//add by sonnia
}TimeTab;

/* event type define*/
enum PType{
	PTYPE_DEFAULT_API,
	PTYPE_SCREEN_SAVER,
	PTYPE_DETECT_INFO,
    PTYPE_NOSCREEN_API,
    PTYPE_DETECTING_DEVICE,
    PTYPE_UNMOUNTING_DEVICE
};

/* debug define*/
#ifndef DEBUG
	#define dprintf(format, args...)
#else
	#define dprintf(format, args...)	fprintf( stderr, format, ##args)
#endif

#define DFBCHECK(x...)                                         \
  {                                                            \
    DFBResult err = x;                                         \
                                                               \
    if (err != DFB_OK)                                         \
      {                                                        \
        fprintf( stderr, "%s <%d>:\n\t", __FILE__, __LINE__ ); \
        DirectFBErrorFatal( #x, err );                         \
      }                                                        \
  }
    
#endif
