#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stddef.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <directfb.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <xmldb.h>
#include <libxmldbc.h>
#include <ctype.h>
#include "alpha_dfb_define.h"
#include "nas_str_define.h"
#include "draw_tool.h"
#include "menu_tool.h"
#include "file_tool.h"
#include "st_router_info.h"
#include "alert_center.h"
#include "detect_info.h"
#include "rgdb_node_define.h"
#include "confirm_center.h"

//start extern variable or function from main.c
extern IDirectFB *gp_dfb;
extern DFBWindowDescription win_dsc;
extern IDirectFBDisplayLayer *main_layer;
extern IDirectFBSurface *title_window_surface;
extern IDirectFBFont *font_title;	
extern DFBRectangle *screen_space, *title_space;
extern RgbaType *rgba, *rgba2; 
extern int GetInputDeviceEventByType(IDirectFBEventBuffer *p_eventbuffer, int PType); 
//end extern variable or function from main.c

void GetConnectTypeName(char *stat);
void GetLinkTypeName(char *stat);
void GetRadioCheckName(char *stat);
void GetWlanModeName(char *stat);
void GetSecurityName(char *stat);
void GetMACFormat(char *stat);
void GetIPFormat(char *stat);
void GetTimeFormat(char *stat);
void GetFirmwareVersion(char *stat, char *current_fw_ver);

char ghddevname[RGDBBUFFER_SIZE];

void GetRouterInfo(InfoValue *datalist)
{
	unsigned char rgdb_val_buf[RGDBBUFFER_SIZE];
	
	datalist->title=gGeneralTitle[GENERAL_TITLE];
	datalist->name[GENERAL_MODELNAME]=gGeneralTitle[GENERAL_MODELNAME];
	xmldbc_get_wb(NULL, 0, RGDB_GENERAL_MODELNAME, datalist->value[GENERAL_MODELNAME], RGDBBUFFER_SIZE);

	datalist->name[GENERAL_HWVERSION]=gGeneralTitle[GENERAL_HWVERSION];
	xmldbc_get_wb(NULL, 0, RGDB_GENERAL_HWVERSION, datalist->value[GENERAL_HWVERSION], RGDBBUFFER_SIZE);
	
	datalist->name[GENERAL_FWVERSION]=gGeneralTitle[GENERAL_FWVERSION];
	xmldbc_get_wb(NULL, 0, RGDB_GENERAL_FWVERSION, datalist->value[GENERAL_FWVERSION], RGDBBUFFER_SIZE);
	
	datalist->name[GENERAL_UPTIME]=gGeneralTitle[GENERAL_UPTIME];
	xmldbc_get_wb(NULL, 0, RGDB_GENERAL_UPTIME, datalist->value[GENERAL_UPTIME], RGDBBUFFER_SIZE);
	GetTimeFormat(datalist->value[GENERAL_UPTIME]);
	
	datalist->name[GENERAL_NEWFW]=gGeneralTitle[GENERAL_NEWFW];
	memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
	xmldbc_get_wb(NULL, 0, RGDB_INTERNET_CABLE_STATUS, rgdb_val_buf, RGDBBUFFER_SIZE);
	GetLinkTypeName(rgdb_val_buf);
	if(strcmp(rgdb_val_buf,"Disconnect")==0)	//Disconnect
		strcpy(datalist->value[GENERAL_NEWFW],"");
	else
		GetFirmwareVersion(datalist->value[GENERAL_NEWFW],datalist->value[GENERAL_FWVERSION]);

	datalist->max=sizeof(gGeneralTitle)/sizeof(gGeneralTitle[0]);
	
	return;
}

void GetInternetStatus(InfoValue *datalist)
{
	unsigned char rgdb_val_buf[RGDBBUFFER_SIZE];
	int itmp;
	
	datalist->title=gInternetTitle[INTERNET_TITLE];
	datalist->name[INTERNET_CONNECT_TYPE]=gInternetTitle[INTERNET_CONNECT_TYPE];
	memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
	xmldbc_get_wb(NULL, 0, RGDB_INTERNET_ROUTER_ENABLE, rgdb_val_buf, RGDBBUFFER_SIZE);
	if(strcmp(rgdb_val_buf,"1")==0)	//ap mode
		xmldbc_get_wb(NULL, 0, RGDB_INTERNET_MODE, datalist->value[INTERNET_CONNECT_TYPE], RGDBBUFFER_SIZE);
	else
		xmldbc_get_wb(NULL, 0, RGDB_INTERNET_CONNECT_TYPE, datalist->value[INTERNET_CONNECT_TYPE], RGDBBUFFER_SIZE);
	GetConnectTypeName(datalist->value[INTERNET_CONNECT_TYPE]);
	
	datalist->name[INTERNET_CABLE_STATUS]=gInternetTitle[INTERNET_CABLE_STATUS];
	xmldbc_get_wb(NULL, 0, RGDB_INTERNET_CABLE_STATUS, datalist->value[INTERNET_CABLE_STATUS], RGDBBUFFER_SIZE);
	GetLinkTypeName(datalist->value[INTERNET_CABLE_STATUS]);
	
	datalist->name[INTERNET_NETWORK_STATUS]=gInternetTitle[INTERNET_NETWORK_STATUS];
	xmldbc_get_wb(NULL, 0, RGDB_INTERNET_NETWORK_STATUS, datalist->value[INTERNET_NETWORK_STATUS], RGDBBUFFER_SIZE);
	datalist->value[INTERNET_NETWORK_STATUS][0]=toupper(datalist->value[INTERNET_NETWORK_STATUS][0]);		//connected or disconnected
	//ppp mode maybe use PPPOP-PADO or another...
	if (strcmp(datalist->value[INTERNET_NETWORK_STATUS],"Connected")!=0 || 
		strcmp(datalist->value[INTERNET_CABLE_STATUS],"Disconnect")==0)
		strcpy(datalist->value[INTERNET_NETWORK_STATUS],"Disconnected");
	
	datalist->name[INTERNET_CONNECT_TIME]=gInternetTitle[INTERNET_CONNECT_TIME];
	memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
	xmldbc_get_wb(NULL, 0, RGDB_GENERAL_UPTIME, rgdb_val_buf, RGDBBUFFER_SIZE);
	itmp=atoi(rgdb_val_buf);
	xmldbc_get_wb(NULL, 0, RGDB_INTERNET_CONNECT_TIME, datalist->value[INTERNET_CONNECT_TIME], RGDBBUFFER_SIZE);
	sprintf(datalist->value[INTERNET_CONNECT_TIME],"%d",itmp-atoi(datalist->value[INTERNET_CONNECT_TIME]));
	
	/* when network_status is disconnected, then wan up time, ipaddr, mask and gateway is null */
	if(strcmp(datalist->value[INTERNET_NETWORK_STATUS],"Connected")!=0)	datalist->value[INTERNET_CONNECT_TIME][0]='\0';
	GetTimeFormat(datalist->value[INTERNET_CONNECT_TIME]);
	
	datalist->name[INTERNET_MACADDR]=gInternetTitle[INTERNET_MACADDR];
	xmldbc_get_wb(NULL, 0, RGDB_INTERNET_MACADDR, datalist->value[INTERNET_MACADDR], RGDBBUFFER_SIZE);
	GetMACFormat(datalist->value[INTERNET_MACADDR]);
	
	datalist->name[INTERNET_IPADDR]=gInternetTitle[INTERNET_IPADDR];
	xmldbc_get_wb(NULL, 0, RGDB_INTERNET_IPADDR, datalist->value[INTERNET_IPADDR], RGDBBUFFER_SIZE);
	if(strcmp(datalist->value[INTERNET_NETWORK_STATUS],"Connected")!=0)	datalist->value[INTERNET_IPADDR][0]='\0';
	GetIPFormat(datalist->value[INTERNET_IPADDR]);
	
	datalist->name[INTERNET_NETMASK]=gInternetTitle[INTERNET_NETMASK];
	xmldbc_get_wb(NULL, 0, RGDB_INTERNET_NETMASK, datalist->value[INTERNET_NETMASK], RGDBBUFFER_SIZE);
	if(strcmp(datalist->value[INTERNET_NETWORK_STATUS],"Connected")!=0)	datalist->value[INTERNET_NETMASK][0]='\0';
	GetIPFormat(datalist->value[INTERNET_NETMASK]);
	
	datalist->name[INTERNET_GATEWAY]=gInternetTitle[INTERNET_GATEWAY];
	xmldbc_get_wb(NULL, 0, RGDB_INTERNET_GATEWAY, datalist->value[INTERNET_GATEWAY], RGDBBUFFER_SIZE);
	if(strcmp(datalist->value[INTERNET_NETWORK_STATUS],"Connected")!=0)	datalist->value[INTERNET_GATEWAY][0]='\0';
	if(!(strcmp(datalist->value[INTERNET_CONNECT_TYPE],"DHCP client")==0 || 
		 strcmp(datalist->value[INTERNET_CONNECT_TYPE],"Static IP")==0))	
		strcpy(datalist->value[INTERNET_GATEWAY],datalist->value[INTERNET_IPADDR]);
	GetIPFormat(datalist->value[INTERNET_GATEWAY]);
	
	datalist->max=sizeof(gInternetTitle)/sizeof(gInternetTitle[0]);
	
	return;
}

void GetWiredStatus(InfoValue *datalist)
{
	datalist->title=gWiredTitle[WIRED_TITLE];
	datalist->name[WIRED_MACADDR]=gWiredTitle[WIRED_MACADDR];
	xmldbc_get_wb(NULL, 0, RGDB_WIRED_MACADDR, datalist->value[WIRED_MACADDR], RGDBBUFFER_SIZE);
	GetMACFormat(datalist->value[WIRED_MACADDR]);
	
	datalist->name[WIRED_IPADDR]=gWiredTitle[WIRED_IPADDR];
	xmldbc_get_wb(NULL, 0, RGDB_WIRED_IPADDR, datalist->value[WIRED_IPADDR], RGDBBUFFER_SIZE);
	GetIPFormat(datalist->value[WIRED_IPADDR]);
	
	datalist->name[WIRED_NETMASK]=gWiredTitle[WIRED_NETMASK];
	xmldbc_get_wb(NULL, 0, RGDB_WIRED_NETMASK, datalist->value[WIRED_NETMASK], RGDBBUFFER_SIZE);
	GetIPFormat(datalist->value[WIRED_NETMASK]);
	
	datalist->name[WIRED_DHCP_SERVER]=gWiredTitle[WIRED_DHCP_SERVER];
	xmldbc_get_wb(NULL, 0, RGDB_WIRED_DHCP_SERVER, datalist->value[WIRED_DHCP_SERVER], RGDBBUFFER_SIZE);
	GetRadioCheckName(datalist->value[WIRED_DHCP_SERVER]);
	
	datalist->name[WIRED_CABLE_P1]=gWiredTitle[WIRED_CABLE_P1];
	xmldbc_get_wb(NULL, 0, RGDB_WIRED_CABLE_P1, datalist->value[WIRED_CABLE_P1], RGDBBUFFER_SIZE);
	GetLinkTypeName(datalist->value[WIRED_CABLE_P1]);
	
	datalist->name[WIRED_CABLE_P2]=gWiredTitle[WIRED_CABLE_P2];
	xmldbc_get_wb(NULL, 0, RGDB_WIRED_CABLE_P2, datalist->value[WIRED_CABLE_P2], RGDBBUFFER_SIZE);
	GetLinkTypeName(datalist->value[WIRED_CABLE_P2]);
	
	datalist->name[WIRED_CABLE_P3]=gWiredTitle[WIRED_CABLE_P3];
	xmldbc_get_wb(NULL, 0, RGDB_WIRED_CABLE_P3, datalist->value[WIRED_CABLE_P3], RGDBBUFFER_SIZE);
	GetLinkTypeName(datalist->value[WIRED_CABLE_P3]);
	
	datalist->name[WIRED_CABLE_P4]=gWiredTitle[WIRED_CABLE_P4];
	xmldbc_get_wb(NULL, 0, RGDB_WIRED_CABLE_P4, datalist->value[WIRED_CABLE_P4], RGDBBUFFER_SIZE);
	GetLinkTypeName(datalist->value[WIRED_CABLE_P4]);
	
	datalist->max=sizeof(gWiredTitle)/sizeof(gWiredTitle[0]);
	
	return;
}

void GetWirelessStatus(InfoValue *datalist)
{
	unsigned char rgdb_val_buf[RGDBBUFFER_SIZE];
	
	datalist->title=gWirelessTitle[WIRELESS_TITLE];
	datalist->name[WIRELESS_RADIO]=gWirelessTitle[WIRELESS_RADIO];
	xmldbc_get_wb(NULL, 0, RGDB_WIRELESS_RADIO, datalist->value[WIRELESS_RADIO], RGDBBUFFER_SIZE);
	GetRadioCheckName(datalist->value[WIRELESS_RADIO]);
	
	datalist->name[WIRELESS_CHANNEL]=gWirelessTitle[WIRELESS_CHANNEL];
	/* auto channel check */
	memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
	xmldbc_get_wb(NULL, 0, RGDB_WIRELESS_AUTOCHANNEL_ENABLE, rgdb_val_buf, RGDBBUFFER_SIZE);
	if(strcmp(rgdb_val_buf,"1")==0 || strcmp(datalist->value[WIRELESS_RADIO],"0")==0)
		xmldbc_get_wb(NULL, 0, RGDB_WIRELESS_AUTO_CHANNEL, datalist->value[WIRELESS_CHANNEL], RGDBBUFFER_SIZE);
	else
		xmldbc_get_wb(NULL, 0, RGDB_WIRELESS_CHANNEL, datalist->value[WIRELESS_CHANNEL], RGDBBUFFER_SIZE);
		
	datalist->name[WIRELESS_HOST_SSID]=gWirelessTitle[WIRELESS_HOST_SSID];
	xmldbc_get_wb(NULL, 0, RGDB_WIRELESS_HOST_SSID, datalist->value[WIRELESS_HOST_SSID], RGDBBUFFER_SIZE);
	
	datalist->name[WIRELESS_GUEST_SSID]=gWirelessTitle[WIRELESS_GUEST_SSID];
	xmldbc_get_wb(NULL, 0, RGDB_WIRELESS_GUEST_SSID, datalist->value[WIRELESS_GUEST_SSID], RGDBBUFFER_SIZE);
	
	datalist->name[WIRELESS_MODE]=gWirelessTitle[WIRELESS_MODE];
	xmldbc_get_wb(NULL, 0, RGDB_WIRELESS_MODE, datalist->value[WIRELESS_MODE], RGDBBUFFER_SIZE);
	GetWlanModeName(datalist->value[WIRELESS_MODE]);
	
	datalist->name[WIRELESS_HOST_SECURITY]=gWirelessTitle[WIRELESS_HOST_SECURITY];
	xmldbc_get_wb(NULL, 0, RGDB_WIRELESS_HOST_SECURITY, datalist->value[WIRELESS_HOST_SECURITY], RGDBBUFFER_SIZE);
	GetSecurityName(datalist->value[WIRELESS_HOST_SECURITY]);
	
	datalist->name[WIRELESS_GUEST_SECURITY]=gWirelessTitle[WIRELESS_GUEST_SECURITY];
	xmldbc_get_wb(NULL, 0, RGDB_WIRELESS_GUEST_SECURITY, datalist->value[WIRELESS_GUEST_SECURITY], RGDBBUFFER_SIZE);
	GetSecurityName(datalist->value[WIRELESS_GUEST_SECURITY]);
	
	datalist->name[WIRELESS_MACADDR]=gWirelessTitle[WIRELESS_MACADDR];
	xmldbc_get_wb(NULL, 0, RGDB_WIRELESS_MACADDR, datalist->value[WIRELESS_MACADDR], RGDBBUFFER_SIZE);
	GetMACFormat(datalist->value[WIRELESS_MACADDR]);
	
	datalist->name[WIRELESS_WPS_NUMBER]=gWirelessTitle[WIRELESS_WPS_NUMBER];
	xmldbc_get_wb(NULL, 0, RGDB_WIRELESS_WPS_PIN, datalist->value[WIRELESS_WPS_NUMBER], RGDBBUFFER_SIZE);
	if(strcmp(datalist->value[WIRELESS_WPS_NUMBER],"")==0)
		xmldbc_get_wb(NULL, 0, RGDB_WIRELESS_RUNTIME_WPS_PIN, datalist->value[WIRELESS_WPS_NUMBER], RGDBBUFFER_SIZE);
	
	datalist->max=sizeof(gWirelessTitle)/sizeof(gWirelessTitle[0]);
	
	return;
}

void GetHDInfo(InfoValue *datalist)
{
	unsigned char rgdb_val_buf[RGDBBUFFER_SIZE];
	char command[128];
	
	datalist->title=gHDTitle[HD_TITLE];
	datalist->name[HD_NAME]=gHDTitle[HD_NAME];
	datalist->name[HD_FORMAT]=gHDTitle[HD_FORMAT];
	datalist->name[HD_CAPACITY]=gHDTitle[HD_CAPACITY];
	datalist->name[HD_USED]=gHDTitle[HD_USED];
	datalist->name[HD_AVAILABLE]=gHDTitle[HD_AVAILABLE];
	datalist->name[HD_HEALTH]=gHDTitle[HD_HEALTH];
	datalist->name[HD_TEMP]=gHDTitle[HD_TEMP];
	
	datalist->max=sizeof(gHDTitle)/sizeof(gHDTitle[0]);
	
	//+++ get hd name and check exist.
	memset(ghddevname, 0x0, RGDBBUFFER_SIZE);
	xmldbc_get_wb(NULL, 0, RGDB_HD_DEVNAME, ghddevname, RGDBBUFFER_SIZE);
	
	if(strcmp(ghddevname,"")!=0)
	{
		sprintf(command,"smartmon /dev/%s",ghddevname);
		system(command);
		
		xmldbc_get_wb(NULL, 0, RGDB_HD_NAME, datalist->value[HD_NAME], RGDBBUFFER_SIZE);
		xmldbc_get_wb(NULL, 0, RGDB_HD_FORMAT, datalist->value[HD_FORMAT], RGDBBUFFER_SIZE);
		xmldbc_get_wb(NULL, 0, RGDB_HD_CAPACITY, datalist->value[HD_CAPACITY], RGDBBUFFER_SIZE);
		xmldbc_get_wb(NULL, 0, RGDB_HD_USED, datalist->value[HD_USED], RGDBBUFFER_SIZE);
		xmldbc_get_wb(NULL, 0, RGDB_HD_AVAILABLE, datalist->value[HD_AVAILABLE], RGDBBUFFER_SIZE);
		xmldbc_get_wb(NULL, 0, RGDB_HD_HEALTH, datalist->value[HD_HEALTH], RGDBBUFFER_SIZE);

		memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
		xmldbc_get_wb(NULL, 0, RGDB_HD_TEMP_C, datalist->value[HD_TEMP], RGDBBUFFER_SIZE);
		xmldbc_get_wb(NULL, 0, RGDB_HD_TEMP_F, rgdb_val_buf, RGDBBUFFER_SIZE);
		if(strcmp(rgdb_val_buf,"")!=0)
		{
			//when have temp_f must have temp_c
			strcat(datalist->value[HD_TEMP]," C/");
			strcat(datalist->value[HD_TEMP],rgdb_val_buf);
			strcat(datalist->value[HD_TEMP]," F");
		}
		
		//last value not to show. last value record hard drive used percent.
		xmldbc_get_wb(NULL, 0, RGDB_HD_USED_PERCENT, datalist->value[datalist->max], RGDBBUFFER_SIZE);
		if(strcmp(datalist->value[datalist->max],"")==0 || strcmp(datalist->value[HD_NAME],"")==0)
			strcpy(datalist->value[datalist->max],"0");
		else if(atoi(datalist->value[datalist->max])<=2) //maybe is "0%"
			strcpy(datalist->value[datalist->max],"2%");
	}
	
	return;
}

InfoValue* GetDBValue(int segment)
{
	InfoValue *datalist = (InfoValue*)malloc(sizeof(InfoValue));
		
	memset(datalist,0,sizeof(InfoValue));
	switch(segment)
	{
		case ROUTER_INFO:
			GetRouterInfo(datalist);
			break;
		case INTERNET_STATUS:
			GetInternetStatus(datalist);
			break;
		case WIRED_STATUS:
			GetWiredStatus(datalist);
			break;
		case WIRELESS_STATUS:
			GetWirelessStatus(datalist);
			break;
		case HD_SPACE:
			GetHDInfo(datalist);
			break;
	}
	return datalist;
}

void SetupHDCapacityImg(IDirectFBSurface *surface, DFBRectangle *phdinfo, int used)
{
	DFBRectangle *space;
	DFBSurfaceDescription sur_dsc;
	IDirectFBSurface *capacity_surface;
	IDirectFBImageProvider *provider;
	int hd_percent;
	
	space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	surface->SetBlittingFlags( surface, DSBLIT_BLEND_ALPHACHANNEL );
	//capacity background
	grid_init(space, phdinfo->x, phdinfo->y, 170, 331);
	draw_image(STAT_1_G_P2, space, surface, gp_dfb);
	//capacity value
	DFBCHECK(gp_dfb->CreateImageProvider( gp_dfb, STAT_1_G_P1, &provider ));
	DFBCHECK(provider->GetSurfaceDescription (provider, &sur_dsc));	//w:124, h:285
	DFBCHECK(gp_dfb->CreateSurface( gp_dfb, &sur_dsc, &capacity_surface ));
	provider->RenderTo( provider, capacity_surface, NULL );
	provider->Release( provider );
	
	hd_percent = sur_dsc.height * used / 100;
	grid_init(space, phdinfo->x+23, phdinfo->h+15-hd_percent, sur_dsc.width, hd_percent);
	surface->StretchBlit( surface, capacity_surface, NULL, space );
	
	capacity_surface->Release (capacity_surface);
	free(space);
}

void start_drawing(IDirectFBWindow *window, IDirectFBSurface *surface, int page_width, int page_height, InfoValue *pDataList, int segment)
{
	DFBRectangle *space;
	IDirectFBFont *fontT,*fontV;
	DFBFontDescription font_dsc;
	RgbaType *rgba_title = NULL;
	int x_pos=90,y_pos=90,y_offset=38,font_size=28,i,str_width;
	
	if(segment==HD_SPACE)
	{
		x_pos=page_width/2-30;
		font_size=26;
	}
	
	rgba_title = (RgbaType*)malloc(sizeof(RgbaType));
	set_rgba(rgba_title, 122, 235, 253, 255);
	
	surface->Clear( surface, 0, 0, 0, 0);
	//start title init 
	space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	draw_title_string(pDataList->title, font_title, rgba, title_space, title_window_surface);					
	//end title init 
	
	font_dsc.flags = DFDESC_HEIGHT;
	font_dsc.height = font_size;
	fontT =(IDirectFBFont*)getFont(FONTS_DECKER, font_dsc,gp_dfb);	//title font
	fontV =(IDirectFBFont*)getFont(FONTS_DECKER, font_dsc,gp_dfb);	//value font
	
	for(i=1;i<pDataList->max;i++)	//start from name(1) because pDataList[0] is title
	{
		grid_init(space, x_pos, y_pos+(y_offset*(i-1)), page_width/2, 20);
		str_width = draw_text(space, pDataList->name[i],fontT, DSTF_TOPLEFT, rgba_title, surface);
		grid_init(space, x_pos+str_width+10, y_pos+(y_offset*(i-1)), page_width/2, 20);
		//+++ modify by siyou. use N/A instead of Blank. 2009/2/13 11:45
		//if(strcmp(pDataList->value[i],"")!=0)
		if(strcmp(pDataList->value[i],"")==0)
			strcpy(pDataList->value[i],"N/A");
		draw_text(space, pDataList->value[i],fontV, DSTF_TOPLEFT, rgba, surface);
	}
	if(segment==HD_SPACE)
	{
		DFBRectangle hdinfo_leftname;
		grid_init(&hdinfo_leftname, 120, 80, 100, 370);
		grid_init(space, hdinfo_leftname.x, hdinfo_leftname.y, page_width/2, 50);
		draw_text(space, ST_ROUTER_HD_AVAILABLE,fontT, DSTF_TOPRIGHT, rgba_title, surface);
		grid_init(space, hdinfo_leftname.x, hdinfo_leftname.h, page_width/2, 50);
		draw_text(space, ST_ROUTER_HD_USED,fontT, DSTF_TOPRIGHT, rgba_title, surface);
		SetupHDCapacityImg(surface, &hdinfo_leftname, atoi(pDataList->value[pDataList->max])/*percent*/);
	}
	
	surface->Flip( surface, NULL, DSFLIP_NONE );
	window->SetOpacity(window,255);
	fontT->Release( fontT );
	fontV->Release( fontV );
	free(rgba_title);
	free(space);
}

void Show_Router_Info(IDirectFBEventBuffer *p_eventbuffer/*, IDirectFBDisplayLayer *main_layer, DFBRectangle *container*/, int segment)
{		
	GridObj *grid;
	IconObj *icon;			
	int key = 0; 						
	int grid_count=1;	
	InfoValue *RouterInfoData;
	
	//start draw menu init	               
	grid=create_view_tree(grid_count, screen_space);			
	icon=create_icon_tree(grid, main_layer, win_dsc); 
	//draw_icon_tree(fcitem_node, icon, screen_space, gp_dfb);	
	
	RouterInfoData = GetDBValue(segment);
	start_drawing(icon->window,icon->window_surface, screen_space->w, screen_space->h, RouterInfoData, segment);	
	if(segment==HD_SPACE)
	{
		if(strcmp(ghddevname,"")==0)
		{
			Alert_Center(p_eventbuffer,NO_HD_ALERT);
			icons_free(icon);
			free(RouterInfoData);
			return;
		}
	}
	
	while(1){
		key = GetInputDeviceEventByType(p_eventbuffer, PTYPE_DEFAULT_API);
		if( key == DIKI_UP ){
			grid_free(grid);
			icons_free(icon);
			free(RouterInfoData);
			break;
		}else if( key == DIKI_A || key == DIKI_B ){	
			icon_opacity(icon, 0);				
			Detect_USBMount(p_eventbuffer);
			draw_title_string(RouterInfoData->title, font_title, rgba, title_space, title_window_surface);	
			icon_opacity(icon, 255);				
		}
		p_eventbuffer->Reset(p_eventbuffer);						
	}
}

/***********************************************************************/
void GetConnectTypeName(char *stat)
{
	if(stat==NULL || *stat=='\0')	return;
	
	if(strcmp(stat,"1")==0)
		strcpy(stat,ST_ROUTER_STATIC);
	else if(strcmp(stat,"2")==0)
		strcpy(stat,ST_ROUTER_DHCP);
	else if(strcmp(stat,"3")==0)
		strcpy(stat,ST_ROUTER_PPPOE);
	else if(strcmp(stat,"4")==0)
		strcpy(stat,ST_ROUTER_PPTP);
	else if(strcmp(stat,"5")==0)
		strcpy(stat,ST_ROUTER_L2TP);
	else if(strcmp(stat,"6")==0)
		strcpy(stat,ST_ROUTER_WWAN);
	return;
}

void GetLinkTypeName(char *stat)
{
	if(stat==NULL || *stat=='\0')	return;
	
	if(strcmp(stat,"1")==0)
		strcpy(stat,ST_ROUTER_100FULL);
	else if(strcmp(stat,"2")==0)
		strcpy(stat,ST_ROUTER_100HALF);
	else if(strcmp(stat,"3")==0)
		strcpy(stat,ST_ROUTER_10FULL);
	else if(strcmp(stat,"4")==0)
		strcpy(stat,ST_ROUTER_10HALF);
	else if(strcmp(stat,"5")==0)
		strcpy(stat,ST_ROUTER_1000FULL);
	else if(strcmp(stat,"6")==0)
		strcpy(stat,ST_ROUTER_1000HALF);
	else	//include "0"
		strcpy(stat,ST_ROUTER_DISCONNECT);
	return;
}

void GetRadioCheckName(char *stat)
{
	if(stat==NULL || *stat=='\0')	return;
	
	if(strcmp(stat,"1")==0)
		strcpy(stat,FUNC_ENABLE);
	else	//include "0"
		strcpy(stat,FUNC_DISABLE);
	return;
}

void GetSecurityName(char *stat)
{
	if(stat==NULL || *stat=='\0')	return;
	
	if(strcmp(stat,"0")==0)
		strcpy(stat,FUNC_DISABLE);
	else if(strcmp(stat,"1")==0)
		strcpy(stat,ST_ROUTER_WEP);
	else
		strcpy(stat,ST_ROUTER_WPA);
	return;
}

void GetWlanModeName(char *stat)
{
	if(stat==NULL || *stat=='\0')	return;
	
	if(strcmp(stat,"1")==0)
		strcpy(stat,ST_ROUTER_WLAN_MODE_B);
	else if(strcmp(stat,"2")==0)
		strcpy(stat,ST_ROUTER_WLAN_MODE_G);
	else if(strcmp(stat,"3")==0)
		strcpy(stat,ST_ROUTER_WLAN_MODE_BG);
	else if(strcmp(stat,"4")==0)
		strcpy(stat,ST_ROUTER_WLAN_MODE_N);
	else if(strcmp(stat,"5")==0)
		strcpy(stat,ST_ROUTER_WLAN_MODE_NB);
	else if(strcmp(stat,"6")==0)
		strcpy(stat,ST_ROUTER_WLAN_MODE_NG);
	else if(strcmp(stat,"7")==0)
		strcpy(stat,ST_ROUTER_WLAN_MODE_NBG);
	else	//include "0"
		strcpy(stat,FUNC_DISABLE);
	return;
}

void GetMACFormat(char *stat)
{
	if(*stat=='\0')
		strcpy(stat,ST_ROUTER_FORMAT_MAC);
	return;
}

void GetIPFormat(char *stat)
{
	if(*stat=='\0')
		strcpy(stat,ST_ROUTER_FORMAT_IP);
	return;
}

void GetTimeFormat(char *stat)
{
	int day,hour,min,sec,total;
	
	if(stat==NULL)	return;
	if(*stat=='\0')
	{
		strcpy(stat,ST_ROUTER_FORMAT_TIME);
		return;
	}
	
	total=atoi(stat);
	hour=total/3600;
	sec=total-hour*3600;
	if(sec>=60)
	{
		min=sec/60;
		sec=sec-min*60;
	}
	else
		min=0;
	if(hour>=24)
	{
		day=hour/24;
		hour=hour-day*24;
	}
	else
		day=0;
	sprintf(stat,"%d Days, %02dh:%02dm:%02ds",day,hour,min,sec);
	return;
}

#define DEFAULT_REMOTE_SERVER "wrpd.dlink.com.tw"
//example: "/router/firmware/query.asp?model=DIR-685_Ax_Default_FW_0101"
#define DEFAULT_REMOTE_FILE_PATH "/router/firmware/query.asp?model=DIR-685_Ax_Default_FW_"
#define VERSION_XML "/var/get_new_ver.xml"
#define DEFAULT_FIRMWARE_VERSION_LATEST "Latest Firmware Version"
#define DEFAULT_FIRMWARE_VERSION_OLD	"Have New Firmware version"
/*
->get remote xml format example:
	<FW_Version>
		<Major>01</Major>
		<Minor>01</Minor>
->it will compare current_fw_ver with Major and Minor, and return stat.
*/
void GetAndCheckFWVersion(char *stat, char *current_fw_ver)
{
	char *pbuffer,*pstr;
	char major[3]="",minor[3]="",remote_path[128];
	int cmajor,cminor,i,ret=0;
    
	sscanf(current_fw_ver,"%d.%d",&cmajor,&cminor);
	sprintf(remote_path,"%s%02d%02d",DEFAULT_REMOTE_FILE_PATH,cmajor,cminor);
	ret=get_remote_file(DEFAULT_REMOTE_SERVER,remote_path,VERSION_XML);
	
	if(ret)
	{
		pbuffer=get_xml_strbuff(VERSION_XML);
    	unlink(VERSION_XML);
    	
    	if(pbuffer!=NULL)
    	{
    		pstr=pbuffer;
	    	while( (pstr = strstr(pstr,"<Major>")) != NULL)
	    	{
	    		pstr += strlen("<Major>");
	    		for(i=0; i < sizeof(major)-1 && *pstr != '<'; i++)
					major[i] = *pstr++;
				major[i] = 0;
	    	}
	    	pstr=pbuffer;
	    	while( (pstr = strstr(pstr,"<Minor>")) != NULL)
	    	{
	    		pstr += strlen("<Minor>");
	    		for(i=0; i < sizeof(minor)-1 && *pstr != '<'; i++)
					minor[i] = *pstr++;
				minor[i] = 0;
	    	}
	    	if(cmajor<atoi(major) || (cmajor<=atoi(major)&&cminor<atoi(minor)))
	    	{
	    		strcpy(stat,DEFAULT_FIRMWARE_VERSION_OLD);
	    		return;
	    	}
	    }
		
    }
    strcpy(stat,DEFAULT_FIRMWARE_VERSION_LATEST);
    return;
}

void GetFirmwareVersion(char *stat, char *current_fw_ver)
{
	DFBRectangle *screen_info_space;
	GridObj *grid;
	IconObj *icon;		
	int grid_count=1;
	Messages MsgTable[1];
	
	//start draw menu init	        
	screen_info_space = (DFBRectangle*)malloc(sizeof(DFBRectangle));
	grid_init(screen_info_space, 70, 70, screen_space->w-(70*2), screen_space->h-(70*2));
	grid=create_view_tree(grid_count, screen_info_space);			
	icon=create_icon_tree(grid, main_layer, win_dsc); 
	memset(MsgTable,0,sizeof(MsgTable));
	MsgTable[0].msg=ST_ROUTER_FIREWARE_MSG;
	draw_detected_ui(icon, screen_info_space, MsgTable, sizeof(MsgTable)/sizeof(MsgTable[0]), DONOTHAVECONFIRM);
	
	GetAndCheckFWVersion(stat,current_fw_ver);
	
	grid_free(grid);
	icons_free(icon);
	free(screen_info_space);
			
	return;
}
/***********************************************************************/

