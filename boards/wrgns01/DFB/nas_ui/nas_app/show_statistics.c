#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stddef.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <directfb.h>
#include <sys/stat.h>
#include <pthread.h>
#include <stdlib.h>
#include <xmldb.h>
#include <libxmldbc.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include "alpha_dfb_define.h"
#include "nas_str_define.h"
#include "draw_tool.h"
#include "file_tool.h"
#include "menu_tool.h"
#include "show_statistics.h"
#include "alert_center.h"
#include "detect_info.h"
#include "rgdb_node_define.h"

#ifdef RTL8366RB
#include "drivers/net/rtl8366rb/rtl8368s_asicdrv.h"
#include "drivers/net/rtl8366rb/rtl8366rb_api.h" 
#include <drivers/net/rtl8366rb/rtl8366_ioctl.h>
#else
#include "drivers/net/rtl8366s/rtl8366s_asicdrv.h"
#include "drivers/net/rtl8366s/rtl8366s_api.h"
#include "drivers/net/rtl8366s/rtl8366_ioctl.h"
#endif

//start extern variable or function from showimg.c
extern IDirectFB *gp_dfb;
extern IDirectFBSurface *page_surface;
extern IDirectFBSurface *title_window_surface;
extern IDirectFBFont *font_title;	
extern DFBRectangle *title_space;
extern RgbaType *rgba;
extern RgbaType *rgba2;
extern TimeTab gTimeTab;	
extern int GetInputDeviceEventByType(IDirectFBEventBuffer *p_eventbuffer, int PType); 
//end extern variable or function from showimg.c

//Add mutex 2009/1/22 02:50pm
pthread_mutex_t draw_mutex = PTHREAD_MUTEX_INITIALIZER;

#if DEBUG_STATISTIC
	#define s_dprintf printf
#else
	#define s_dprintf(x,args...)
#endif

/******************************************************************************/
typedef	struct thread_arg{
	char				*name;
	char 				*tx;	//Rgdb tx name -- define at rgdb_node_define.h
	char				*rx;	//Rgdb rx name
	IDirectFBWindow     *window; 
   	IDirectFBSurface    *surface;
   	IDirectFBSurface    *subsurface;	 
   	int 	    		rect_x;
   	int					rect_y;
}Tread_Arg ;

typedef struct draw_stat{
	char *name;
	int i;	
	int KborMb;//0:Kb 1:Mb
	uint64 tx;
	uint64 rx;
	uint64 sum;
	int scope;
	int num;	
	long time;	
	unsigned long start_time_sec;
	unsigned long start_time_usec;		
}DrawStat;

int gThreadRun=0;	

/*************************** Set pthread arg ******************************************/	
Tread_Arg *set_threadarg(char *name, char *tx,char *rx ,IDirectFBSurface *window_surface_pic,
IDirectFBSurface *subsurface,int x,int y)
{
	Tread_Arg	*statarg=NULL;
  	statarg = (Tread_Arg*)malloc(sizeof(Tread_Arg));
  	statarg->name=name;
  	statarg->tx=tx;
  	statarg->rx=rx;
  	statarg->surface=window_surface_pic;
  	statarg->subsurface=subsurface; 			
  	statarg->rect_x=x;
  	statarg->rect_y=y;	
  return statarg;
}
/*************************** Show info for debug **************************************/
#if DEBUG_STATISTIC	
void show_wlan_mode(int wlan_mode)
{
	printf("wireless wlan_mode: %d ",wlan_mode);
	switch(wlan_mode)
	{
		case 1:
			printf("11b mode\n");break;
		case 2:
			printf("11g mode\n");break;
		case 3:
			printf("11g+11b mode\n");break;
		case 4:
			printf("11n mode\n");break;
		case 5:
			printf("11n+11b mode\n");break;
		case 6:
			printf("11n+11g mode\n");break;
		case 7:
			printf("11n+11g+11b mode\n");break;
		default:
			printf("Can't fine wlan mode\n");break;
	}	
}
long glocal_time(int show)
{
	struct tm *p_time;	
	long time=0;
	
	//Get time
	p_time=localtime(&gTimeTab.timep);		
	time=(p_time->tm_hour*60*60)+(p_time->tm_min)*60+p_time->tm_sec;	
	if(show==1)
		printf("print now time:%d:%d:%d\n",p_time->tm_hour,p_time->tm_min,p_time->tm_sec);
	return time;
}
void show_statistic_status(DrawStat *gStat)
{
	printf("Name:%s\n",gStat->name);
	printf("scope:%d\n",gStat->scope);	
	printf("lattices:%d\n",gStat->i);
	printf("sum:%lld kb\n",gStat->sum);
	printf("num:%d\n",gStat->num);
	printf("KborMb:%d(0:Kb 1:Mb)\n",gStat->KborMb);	
	printf("time:%ld usec\n",gStat->time);
	printf("tx:%lld kB\n",gStat->tx);
	printf("rx:%lld kB\n",gStat->rx);
}
#endif
/*************************** Write words on subsurface ******************************************/	
void draw_text_onsubsurface(int x, int y,DFBRectangle *rectstring, char *text, 
IDirectFBFont *font, DFBSurfaceTextFlags flags, RgbaType *rgba, IDirectFBSurface *window_surface_pic)
{
  IDirectFBSurface       *subsurface_string;

  window_surface_pic->GetSubSurface(window_surface_pic,rectstring,&subsurface_string); 
    	  	        		  	  		  	  	  		 	
  DFBCHECK(subsurface_string->SetFont (subsurface_string, font)); 
  DFBCHECK(subsurface_string->SetColor(subsurface_string, rgba->r, rgba->g, rgba->b, rgba->a ));   	 	  	
  DFBCHECK(subsurface_string->DrawString (subsurface_string, text, -1, x , y, flags));   	  	  	  	
  
  //release                              
  subsurface_string->Release(subsurface_string);  
  return ;
}	
/*************************** Draw Num pic  ******************************************/	
void  draw_statistics_num(IDirectFBSurface *subsurface_num,int statisticdata)
{
	int n1,n2,n3;

 	if (statisticdata==0)
 	{n1=n2=n3=0;}
 	else
 	{
	   n1=statisticdata/100;
	   n2=statisticdata/10;
	   n2=n2%10;              
	   n3=statisticdata%10;
 	}         												 	

#if USE_TEXT //Use Text to draw Number

	char hundreds[0],tens[0],units[0];
	int fontheight=0;
	int num_width=0;
	int width=0;
	
	IDirectFBFont        	*font_num;		
	RgbaType			 	*rgba_num; 	
 	rgba_num = (RgbaType*)malloc(sizeof(RgbaType));
 
    DFBFontDescription Fdesc;
	Fdesc.flags = DFDESC_HEIGHT;
	Fdesc.height = 105;
	DFBCHECK(gp_dfb->CreateFont( gp_dfb, FONTS_DIGI, &Fdesc, &font_num )); 
 	font_num->GetHeight( font_num, &fontheight );
 	font_num->GetStringWidth (font_num,"0",-1,&num_width); 
 
 	sprintf(hundreds,"%d",n1);
 	sprintf(tens,"%d",n2);	
	sprintf(units,"%d",n3);	
		
	set_rgba(rgba_num, 0xFF, 0xFF, 0xFF, 255);
	
    DFBRectangle *rect1; //hundreds
	rect1=(DFBRectangle*)malloc(sizeof(DFBRectangle));		
	grid_init(rect1, 95						,  H_IMAGE-fontheight+15, W_NUM, H_NUM);

    DFBRectangle *rect2; //tens
	rect2=(DFBRectangle*)malloc(sizeof(DFBRectangle));		
	grid_init(rect2, 95+num_width-N_DIS 	, H_IMAGE-fontheight+15, W_NUM, H_NUM);

    DFBRectangle *rect3; //units
	rect3=(DFBRectangle*)malloc(sizeof(DFBRectangle));		
	grid_init(rect3, 95+num_width*2-N_DIS*2 , H_IMAGE-fontheight+15, W_NUM, H_NUM);			

	#if DRAW_BG_NUM //Draw backgroud number
	RgbaType			 	*bg_rgba_num; 
 	bg_rgba_num = (RgbaType*)malloc(sizeof(RgbaType));
 		
	set_rgba(bg_rgba_num, 0x5A, 0x5A, 0x5A, 255);	
	width 	= draw_text(rect1, "8"			,font_num, DSTF_TOPRIGHT, bg_rgba_num, subsurface_num);
	width 	= draw_text(rect2, "8"			,font_num, DSTF_TOPRIGHT, bg_rgba_num, subsurface_num);	
	set_rgba(bg_rgba_num, 0x80, 0x80, 0x80, 255); //color for Internet		
	width 	= draw_text(rect3, "8"			,font_num, DSTF_TOPRIGHT, bg_rgba_num, subsurface_num);	

	//release
	free(bg_rgba_num);
	#endif
		
	width 	= draw_text(rect1, &hundreds[0]	,font_num, DSTF_TOPRIGHT, rgba_num, subsurface_num);
	width 	= draw_text(rect2, &tens[0]		,font_num, DSTF_TOPRIGHT, rgba_num, subsurface_num);
	width 	= draw_text(rect3, &units[0]	,font_num, DSTF_TOPRIGHT, rgba_num, subsurface_num);
		
	//release
	font_num->Release( font_num ); 
	free(rgba_num);

#else   //Use Image to draw Number
          												
    DFBRectangle *rect1;
	rect1=(DFBRectangle*)malloc(sizeof(DFBRectangle));		
	grid_init(rect1, 96-W_NUM-N_DIS, H_IMAGE-H_NUM, W_NUM, H_NUM);
				
    DFBRectangle *rect2;
	rect2=(DFBRectangle*)malloc(sizeof(DFBRectangle));		
	grid_init(rect2, 96						 , H_IMAGE-H_NUM, W_NUM, H_NUM);

    DFBRectangle *rect3;
	rect3=(DFBRectangle*)malloc(sizeof(DFBRectangle));		
	grid_init(rect3, 96+W_NUM+N_DIS, H_IMAGE-H_NUM, W_NUM, H_NUM);					
         
	draw_image(num_pic[n1], rect1,subsurface_num, gp_dfb);   
	draw_image(num_pic[n2], rect2,subsurface_num, gp_dfb);   
	draw_image(num_pic[n3], rect3,subsurface_num, gp_dfb);  

#endif	

	//release													     
	free(rect1);    
	free(rect2);
	free(rect3);      
 	return ;  		 
}
/*************************** Draw Statistics ******************************************/	
/*Total 36 lattices
 *
 *Internet and LAN -->
 *	Gigabit Ehternet : 
 *	0,256(=0.25M)--3 lattices,512--6,1024(=1M)--9,
 *	1--9,2--12,4--15,8--18,15--21,
 *	30--24,62--27,125--30,250--32,500--32,(1000)--32
 *
 *Wireless -->
 *	11g 							: 36 Mbps (linear ; 1Mbps/1 lattice)
 *	11n HT 	 Channel Width->20 		: 90 Mbps (linear ; 2.5Mbps/1 lattice)
 *	11n Auto Channel Width->20/40 	: 180Mbps (linear ; 5Mbps/1 lattice)
 *	
 */	 
 /*
 scope(0~13):for Internet and LAN
 0:0k		1:1~256k	2:257~512k	3:513~1024k or 3:0~1M	4:1~2M		5:2~4M		6:4~8M
 7:8~15M	8:15~30M	9:30~62M	10:62~125M	11:125~250M	12:250~500M	13:500Mup
 */
int decide_scope(char* name,int num,int KborMb) /* for Internet and LAN */
{
	int i=0;			
	
	if(KborMb==0)
	{
		if(num==gigabit_ehternet[0])	
			return 0;
		for(i=0;i<3;i++)
		{
			if( gigabit_ehternet[i+1]> num && num >= gigabit_ehternet[i])
			{
				s_dprintf("Scope=%d. %d <= %d < %d\n",i,gigabit_ehternet[i],num,gigabit_ehternet[i+1]);
				return i;
			}
		}
	}
	else if(KborMb==1)
	{
		if(num==gigabit_ehternet[0])
			return 0;
		if(num >= gigabit_ehternet[13])
		{
			s_dprintf("Scope=13. %d > %d\n",num,gigabit_ehternet[13]);	
			return 13;
		}
		for(i=4;i<13;i++)
		{
			if( gigabit_ehternet[i+1]> num && num >= gigabit_ehternet[i])
			{
				s_dprintf("Scope=%d. %d <= %d < %d\n",i,gigabit_ehternet[i],num,gigabit_ehternet[i+1]);
				return i-1;
			}
		}
	}
	
	//ERROR
	printf("Error: Cannot find lan or wan scope!\n%s num%d kborMb%d",name,num,KborMb);
	return -1;	
}
int decide_wlan_scope(int num)
{
	int i=0;
	_u8 rgdb_val_buf[RGDBBUFFER_SIZE];	
	int wlan_mode=0,wlan_bandwidth=0;
		
	/*	1: 11b mode, 2: 11g mode, 3: 11g+11b mode, 4: 11n mode, 
	 *	5: 11n+11b mode, 6: 11n+11g mode, 7: 11n+11g+11b mode */
	memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
	xmldbc_get_wb(NULL, 0, RGDB_WIRELESS_MODE , rgdb_val_buf, RGDBBUFFER_SIZE);
	wlan_mode=atoi(rgdb_val_buf);
	if(strcmp(rgdb_val_buf,"")==0)
		wlan_mode=6;
		
#if DEBUG_STATISTIC	
	show_wlan_mode(wlan_mode);
#endif
	
	if(wlan_mode==2||wlan_mode==3) //11g(2: 11g mode, 3: 11g+11b mode)
	{
		i=num;
		return i;
	}
	else if(wlan_mode==4 || wlan_mode==5 || wlan_mode==6 || wlan_mode==7) //11n
	{
	    memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
	    xmldbc_get_wb(NULL, 0, RGDB_WIRELESS_BANDWIDTH , rgdb_val_buf, RGDBBUFFER_SIZE);
		wlan_bandwidth=atoi(rgdb_val_buf);		
		if(strcmp(rgdb_val_buf,"")==0)
			wlan_bandwidth=2;
	
		s_dprintf("wireless wlan_bandwidth: %d\n",wlan_bandwidth);	
	
		if(wlan_bandwidth==2)	//wlan_bandwidth=1(11n HT20),wlan_bandwidth=2(11n Auto20/40)	
		{
			i=num/5;
			return i;
		}
		else if(wlan_bandwidth==1)
		{			
			i=num/2.5;
			return i;
		}
	}

	//ERROR
	printf("Cannot find wlan scope!\nwlan_mode %d,num %d",wlan_mode,num);	
	return -1;
}
int decide_lattices(int count,DrawStat *gStat,DrawStat *pre_gStat)
{
	if(count==1)
	{
		gStat->scope=0;
		gStat->i=0;
		return 1;
	}
	
	if(strcmp(gStat->name,STATISTIC_WIRELESS)==0)
	{
		if(gStat->KborMb==1)
		{
			gStat->scope=decide_wlan_scope(gStat->num);
			if(gStat->scope < 0) gStat->scope=0;			
			pre_gStat->i=pre_gStat->scope;
			gStat->i=gStat->scope;
		}
		else if(gStat->KborMb==0)
		{		
			pre_gStat->i=pre_gStat->scope;
			gStat->i=0;
		}
	}
	else
	{			
		gStat->scope=decide_scope(gStat->name,gStat->num,gStat->KborMb);
		if(gStat->scope < 0) gStat->scope=0;	
		pre_gStat->i=pre_gStat->scope*3;
		gStat->i=gStat->scope*3;
	}
			
	if(gStat->i>=32) 	gStat->i=32;
	if(pre_gStat->i>=32) 	pre_gStat->i=32;	
	
	return 1;
}
void draw_KborMb(char *name,int KborMb,IDirectFBSurface *bps_surface)
{
	IDirectFBFont        	*font_KborMb;	
	RgbaType			 	*rgba_KborMb;
  	DFBRectangle 			*rect_KborMb;
 	IDirectFBSurface		*bps_subsurface;//Draw kbps or Mbps at sub-surface;
	
	DFBFontDescription Fdesc;
	Fdesc.flags = DFDESC_HEIGHT;
	Fdesc.height = 22;
	DFBCHECK(gp_dfb->CreateFont( gp_dfb, FONTS_DECKER, &Fdesc, &font_KborMb ));
         	
	char *word_KborMb=NULL;
	if(KborMb==0)
		word_KborMb=STATISTIC_KB;
	else if(KborMb==1)
		word_KborMb=STATISTIC_MB;
			
	rect_KborMb =(DFBRectangle*)malloc(sizeof(DFBRectangle));		
	rgba_KborMb =(RgbaType*)malloc(sizeof(RgbaType));
			
	if(strcmp(name,STATISTIC_NETWORK)==0)
	{
		set_rgba(rgba_KborMb, 0xCF, 0xCF, 0xFF, 255);
		DFBRectangle rect= { 360, H_IMAGE ,W_IMAGE+70, 30 };		
		
		bps_surface->GetSubSurface(bps_surface,&rect,&bps_subsurface); 		
		bps_subsurface->Clear(bps_subsurface,0,0,0,0);			
		grid_init(rect_KborMb,0,0 ,W_IMAGE+70, 30 );			
		draw_text_onsubsurface(0,0,rect_KborMb, word_KborMb, font_KborMb, DSTF_TOPLEFT, rgba_KborMb, bps_subsurface);
        bps_surface->Flip(bps_surface,NULL,0);
	}
	else if(strcmp(name,STATISTIC_INTERNET)==0)
	{
		set_rgba(rgba_KborMb, 188, 188, 0xFF, 255);
		DFBRectangle rect= { 182, 170+H_IMAGE , W_IMAGE+70, 30 };	
			
		bps_surface->GetSubSurface(bps_surface,&rect,&bps_subsurface); 		
		bps_subsurface->Clear(bps_subsurface,0,0,0,0);		
		grid_init(rect_KborMb, 0,0 ,W_IMAGE+70, 30 );			
		draw_text_onsubsurface(0,0,rect_KborMb, word_KborMb, font_KborMb, DSTF_TOPLEFT, rgba_KborMb, bps_subsurface);
        bps_surface->Flip(bps_surface,NULL,0);    
	}
	else if(strcmp(name,STATISTIC_WIRELESS)==0)
	{
		set_rgba(rgba_KborMb, 0xCF, 0xCF, 0xFF, 255);
		DFBRectangle rect= { 10, H_IMAGE , W_IMAGE+70, 30 };		
		
		bps_surface->GetSubSurface(bps_surface,&rect,&bps_subsurface); 		
		bps_subsurface->Clear(bps_subsurface,0,0,0,0);		
		grid_init(rect_KborMb, 0,0 ,W_IMAGE+70, 30 );			
		draw_text_onsubsurface(0,0,rect_KborMb, word_KborMb, font_KborMb, DSTF_TOPLEFT, rgba_KborMb, bps_subsurface);
        bps_surface->Flip(bps_surface,NULL,0);    
	}
	
	font_KborMb->Release( font_KborMb ); 
	free(rect_KborMb);
	free(rgba_KborMb);
	if(bps_subsurface)	bps_subsurface->Release(bps_subsurface);
}
/*
	
	eth1					  eth0
     _|_						|
	|_5_| <--software port		|
 __/__|__\___\__               _|_
|_0_|_1_|_2_|_3_|<--LAN port  |_4_| <--WAN port

LAN port:	Rx-->0+1+2+3= Tx-->5
			Tx-->0+1+2+3= Rx-->5
LAN flow:
	Tx=Port 5(Tx)
	Rx=Port 5(Rx)
WAN flow:
	Tx=Port 5(Tx)-eth0(Rx)+eth1(Tx)
	Rx=Port 5(Rx)-eth0(Tx)+eth1(Rx)
*/
void gLAN_TxRx_from_hw(int fd,DrawStat *gStat)
{
	getMibCounter_t hw_flow;
	int port=0;
	gStat->tx=0;	
	gStat->rx=0;
	
	for(port=0;port<=3;port++)
	{
		hw_flow.port=port;
		ioctl(fd, GETMIBCOUNTER, &hw_flow);
		s_dprintf("port:%d Tx=%lld Rx=%lld\n\n",port,hw_flow.TxOctets,hw_flow.RxOctets);
		gStat->tx=gStat->tx+hw_flow.TxOctets;//byte
		gStat->rx=gStat->rx+hw_flow.RxOctets;//byte
	}
}
void gWAN_TxRx_from_hw(int fd,DrawStat *gStat)
{
	char *endptr;
	_u8 rgdb_val_buf[RGDBBUFFER_SIZE];
	uint64 lan_hw_tx,lan_hw_rx;
	uint64 wan_sw_tx,wan_sw_rx;
	uint64 lan_sw_tx,lan_sw_rx;
		
	gLAN_TxRx_from_hw(fd,gStat);
	lan_hw_rx=gStat->tx;
	lan_hw_tx=gStat->rx;
	
	//LAN_Tx	
	memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
	xmldbc_get_wb(NULL, 0, RGDB_LAN_TX, rgdb_val_buf, RGDBBUFFER_SIZE);
	lan_sw_tx=strtoull(rgdb_val_buf,&endptr,10);
	//LAN_Rx   
	memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
	xmldbc_get_wb(NULL, 0, RGDB_LAN_RX, rgdb_val_buf, RGDBBUFFER_SIZE);
	lan_sw_rx=strtoull(rgdb_val_buf,&endptr,10); 

	//WAN_Tx	
	memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
	xmldbc_get_wb(NULL, 0, RGDB_WAN_TX, rgdb_val_buf, RGDBBUFFER_SIZE);
	wan_sw_tx=strtoull(rgdb_val_buf,&endptr,10);
	//WAN_Rx   
	memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
	xmldbc_get_wb(NULL, 0, RGDB_WAN_RX, rgdb_val_buf, RGDBBUFFER_SIZE);
	wan_sw_rx=strtoull(rgdb_val_buf,&endptr,10);

	gStat->tx=lan_hw_rx-lan_sw_rx+wan_sw_tx;
	gStat->rx=lan_hw_tx-lan_sw_tx+wan_sw_rx;
	
	s_dprintf("Internet Tx= Lan hw Rx: %lld - sw Rx: %lld + Wan sw Tx: %lld\n",lan_hw_rx,lan_sw_rx,wan_sw_tx);
	s_dprintf("Internet Rx= Lan hw Tx: %lld - sw Tx: %lld + Wan sw Tx: %lld\n",lan_hw_tx,lan_sw_tx,wan_sw_rx);
}
void gTxRx_from_sw(Tread_Arg *s,DrawStat *gStat)
{
	char *endptr;
	int gz_enable=0,wlan_enable=0;
	_u8 rgdb_val_buf[RGDBBUFFER_SIZE];
	//Software flow, data which get from DB is the same with data which get from 'ifconfig'.
	//Tx	
	memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
	xmldbc_get_wb(NULL, 0, s->tx, rgdb_val_buf, RGDBBUFFER_SIZE);
	gStat->tx=strtoull(rgdb_val_buf,&endptr,10);
	s_dprintf("gTxRx_from_sw=> name %s tx %s\n",gStat->name,rgdb_val_buf);
	
	//Rx   
	memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
	xmldbc_get_wb(NULL, 0, s->rx, rgdb_val_buf, RGDBBUFFER_SIZE);
	gStat->tx=strtoull(rgdb_val_buf,&endptr,10);
	s_dprintf("gTxRx_from_sw=> name %s rx %s\n",gStat->name,rgdb_val_buf);

	s_dprintf("gTxRx_from_sw=> name %s tx %lld rx% lld\n",gStat->name,gStat->tx,gStat->rx);	
	
	//GZone
	if(strcmp(s->name,STATISTIC_WIRELESS)==0)
	{
		memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
		xmldbc_get_wb(NULL, 0, RGDB_GZONE_ENABLE, rgdb_val_buf, RGDBBUFFER_SIZE);
		gz_enable=atoi(rgdb_val_buf);

		memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
		xmldbc_get_wb(NULL, 0, RGDB_WIRELESS_RADIO, rgdb_val_buf, RGDBBUFFER_SIZE);
		wlan_enable=atoi(rgdb_val_buf);
		
		if( wlan_enable==1 && gz_enable==1 )
		{
			memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
			xmldbc_get_wb(NULL, 0, RGDB_GZONE_TX, rgdb_val_buf, RGDBBUFFER_SIZE);
			gStat->tx=gStat->tx+strtoull(rgdb_val_buf,&endptr,10);			
			
			memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
			xmldbc_get_wb(NULL, 0, RGDB_GZONE_RX, rgdb_val_buf, RGDBBUFFER_SIZE);	
			gStat->tx=gStat->tx+strtoull(rgdb_val_buf,&endptr,10);							

			s_dprintf("after add gzone flow: \ngTxRx_from_sw=> tx %lld rx% lld\n",gStat->tx,gStat->rx);	
		}
	}
}
//modify get pass time at 2009/2/6 09:58am
float gPass_Time(int count,DrawStat *gStat,DrawStat *pre_gStat)
{
	float pass_time=0;
    struct timeval now;
    
    while(pass_time < 1)
    {
	    gettimeofday(&now, NULL);
	    
	    if(count==1)
	    {
	    	gStat->start_time_sec=now.tv_sec;
	    	gStat->start_time_usec=now.tv_usec;
	    	s_dprintf("start_time= %ld:%ld\n",gStat->start_time_sec,gStat->start_time_usec);
	    	return 1;
	    }
		
		s_dprintf("now time %ld:%ld\n",now.tv_sec,now.tv_usec);		
		
		now.tv_sec=now.tv_sec-gStat->start_time_sec;
		now.tv_usec=now.tv_usec-gStat->start_time_usec;		
		gStat->time=1000000*now.tv_sec+now.tv_usec;	
		
		if(gStat->time < 0)
			return -1;
				
		pass_time=gStat->time-pre_gStat->time;
		pass_time=pass_time/1000000;
		s_dprintf("pass_time %.2f sec\n",pass_time);
		
		if(pass_time == 0)
			sleep(1);		
				
		if(pass_time < 0)
			return -1;
	}
	
	return pass_time;
}
void decide_KborMb(int count,DrawStat *gStat)
{
	if(gStat->num >= 1024)
	{
		gStat->num=gStat->num/1024;//Mb
		gStat->KborMb=1;
		s_dprintf("%d-> name %s,num %d Mb\n",count,gStat->name,gStat->num);	
		if(999 < gStat->num)//Should never come to this condition
		{
			s_dprintf("Caution: %d num > 999 Mb\n",count); 
			gStat->num=999;			
		}
	}
	else if(999 < gStat->num && gStat->num <1024)
	{	/* 1024kbits > now_num >= 1000kbits => now_num= 1 Mbits*/
		gStat->num=1;
		gStat->KborMb=1;
		s_dprintf("%d-> name %s,num %d Mb\n",count,gStat->name,gStat->num);		
	}
	else
	{
		gStat->KborMb=0;
		s_dprintf("%d-> name %s,num %d Kb\n",count,gStat->name,gStat->num);	
	}
}
void draw_speed_gauge(DFBRectangle *rect0,Tread_Arg *s,DrawStat *gStat,DrawStat *pre_gStat)
{	
	pthread_mutex_lock(&draw_mutex);//lock the stack
	s->subsurface->Clear(s->subsurface,0,0,0,0);	
	
#if DRAW_BY_LATTICES
	draw_image(image_names[pre_gStat->i], rect0,s->subsurface, gp_dfb);		           		
#else
	draw_image(image_names[gStat->i], rect0,s->subsurface, gp_dfb);	
#endif

	draw_statistics_num(s->subsurface,gStat->num); //Draw 3-numbers	
	draw_KborMb(s->name,gStat->KborMb,s->surface); //Draw STATISTIC_MB or STATISTIC_KB
	s->subsurface->Flip(s->subsurface,NULL,0);  
	pthread_mutex_unlock(&draw_mutex);//free the lock of the stack	
}
void run_speed_gauge(DFBRectangle *rect0,Tread_Arg *s,DrawStat *gStat,DrawStat *pre_gStat)
{ 
	if( pre_gStat->num < gStat->num )//this number is bigger or smaller than previous number	
	{            	 	                                             
		for (; pre_gStat->i <= gStat->i; pre_gStat->i++)//pic from pre_i increase to i progressively
		{ 				              						
			draw_speed_gauge(rect0,s,gStat,pre_gStat);
		}
	}
	else if(pre_gStat->num > gStat->num)
	{        
		for (; pre_gStat->i >= gStat->i ; pre_gStat->i-- )//pic from pre_i decrease to i progressively
		{     		
			draw_speed_gauge(rect0,s,gStat,pre_gStat);		
		}
	}
	else if(pre_gStat->num == gStat->num)
	{    		       	       	   
		draw_speed_gauge(rect0,s,gStat,pre_gStat);     	
	}  	
}
void init_Stat(DrawStat *gStat)
{
	gStat->i=0;	
	gStat->KborMb=0;//0:Kb 1:Mb
	gStat->tx=0;
	gStat->rx=0;
	gStat->sum=0;
	gStat->scope=0;
	gStat->num=0;	
	gStat->time=0;		
}
void calculate_flow(int hw_nat_enable,int fd,Tread_Arg *s,DrawStat *gStat)
{
	//Get Tx and Rx
	if(hw_nat_enable==1)
	{
		if(strcmp(s->name,STATISTIC_INTERNET)==0)
		{
			gWAN_TxRx_from_hw(fd,gStat);
		}
		else if(strcmp(s->name,STATISTIC_NETWORK)==0)
			gLAN_TxRx_from_hw(fd,gStat);//Port:5=LAN				
		else if(strcmp(s->name,STATISTIC_WIRELESS)==0)
			gTxRx_from_sw(s,gStat);	
	}
	else if(hw_nat_enable==0)
	{
		gTxRx_from_sw(s,gStat);	
	}
 	
 	//Calculate Sum=Tx+Rx kbits
	//1024 Byte = 1 kByte
	gStat->tx=gStat->tx/(1024);
 	gStat->rx=gStat->rx/(1024);
 	//Sum=Tx+Rx kByte
 	gStat->sum=gStat->tx+gStat->rx;
	//1 kByte = 8 kbits
	gStat->sum=gStat->sum*8; //kbits(kbps)	
}

/*	 _______________			
	|  ___________	|===> s->surface( subsurface_network, subsurface_wireless, subsurface_internet)			
	| |	 		  |	|
	| |	 		  |====> s->subsurface (for draw number and images)
	| |	 		  |	|
	| |___________|	|
	| Kbps or Mbps	|						
	|_____Name______|	

	step 0: check hw_nat enable or not
			if Yes, then get flow data from hw port
			if No, then get flow data from rgdb
	step 1: set pre stat= stat and set stat=0	
	step 2:	calculate flow value
	step 3: get pass time(this time-last get value time)
			if "first time" get data, then do step 1.
			else "Not" first time get data, then do step 4
	step 4: get flow value (kbps/second)
	step 5: decide statistic data is Kbps or Mbps
	step 6: decide how many lattices to draw according to statistic value and type(lan,wan,wlan)
	step 7: draw speed gauge
*/
void* run_statistics(void* stat)
{
	DrawStat gStat,pre_gStat;
	_u8 rgdb_val_buf[RGDBBUFFER_SIZE];
	Tread_Arg *s=(	Tread_Arg * ) stat;		
	float pass_time=0;
	int count=0;	
	int fd=0;
	int hw_nat_enable=0;

	//check hw_nat enable or not
	//hw_nat_enable=> enable:1 disable:0
	memset(rgdb_val_buf, 0x0, RGDBBUFFER_SIZE);
	xmldbc_get_wb(NULL, 0, RGDB_HW_NAT, rgdb_val_buf, RGDBBUFFER_SIZE);
	hw_nat_enable=atoi(rgdb_val_buf);

	if(hw_nat_enable==1)
	{
		fd = open(RTL8366S_IOCTL_DEV, O_RDONLY);
		if (fd <=0) {
			pthread_exit(0);  
			return NULL; 
		}	
	}
	
	//*this s->subsurface only draw images and numbers. *//	
	DFBRectangle rect= { s->rect_x, s->rect_y, W_IMAGE, H_IMAGE };			
	s->surface->GetSubSurface(s->surface,&rect,&s->subsurface);    

	DFBRectangle *rect0;
	rect0=(DFBRectangle*)malloc(sizeof(DFBRectangle));		
	grid_init(rect0, 0, 0, W_IMAGE, H_IMAGE);						     

	gStat.name=s->name;
  				
	while(gThreadRun)
	{
 	  	//pthread_testcancel();		
		pthread_mutex_lock(&draw_mutex);//lock the stack
	
		do{	//count==1,only calculat stat num, but don't draw the speed gauge. 
			
			count++;	
			
			pre_gStat=gStat;//Store pre stat data
			init_Stat(&gStat);//init stat data

#if DEBUG_STATISTIC
			printf("======== Start %d %s ========\n",count,gStat.name);
			long nowtime=0;		
			nowtime=glocal_time(1);
#endif		
			calculate_flow(hw_nat_enable,fd,s,&gStat);
			if(gStat.sum < pre_gStat.sum)//check: stat_sum must bigger than pre_sum
			{
				s_dprintf("Error:%s sum %lld < pre_sum %lld\n",gStat.name,gStat.sum,pre_gStat.sum);
				count=0; //give up this stat data
				init_Stat(&gStat);
			}
			
			//Get Pass Time= get Tx&Rx time - pre_get Tx&Rx time 
			pass_time=gPass_Time(count,&gStat,&pre_gStat);
			if(pass_time==-1)
			{
				s_dprintf("Error: get or pass time < 0\n");
				pass_time=1;					
				count=0;	//give up this statistic data				
			}
		
		}while(count <= 0); //count<=0 , give up this statistic data, reget statistic data 
		
		pthread_mutex_unlock(&draw_mutex);//free the lock of the stack	
    	
    	gStat.num=(gStat.sum-pre_gStat.sum)/pass_time;//num speed : kbps/second
		
		//decide statistic data is Kbps or Mbps
		decide_KborMb(count,&gStat);	      
		//decide how many lattices to draw according to statistic data and type
		decide_lattices(count,&gStat,&pre_gStat);			
		
		//draw speed gauge	
		if(count>1)
#if DRAW_BY_LATTICES
			run_speed_gauge(rect0,s,&gStat,&pre_gStat);
#else
			draw_speed_gauge(rect0,s,&gStat,&pre_gStat);		
#endif

#if DEBUG_STATISTIC		
		show_statistic_status(&gStat);
		printf("======== End %d %s ==========\n",count,gStat.name);	
#endif	
					
		sleep(1);	//get new statistics in every second
	}
    
	free(rect0);
	if(fd) close(fd);
	if(s->subsurface)	s->subsurface->Release(s->subsurface);
	s_dprintf("Leave pthread");
	pthread_exit(0);  
	return NULL; 
}
/*************************** Show Statistics (Major Function)******************************************/	
/*
subsurface_wireless	subsurface_network (include image, number,name,STATISTIC_MB )
 _______|_______________|_______
|	 ___|___		 ___|___	|
|	|		|		|		|	|
|	|		|		|		|	|
|	|		|		|		|	|
|	|_______|		|_______|	|	==> all window_pic & window_surface_pic
|			 _______			|
|			|		|			|
|			|		|			|
|			|		|			|
|			|_______|			|
|_____subsurface_internet_______|
|___________[Time]______________|

*/
void Show_Statistics(IDirectFBEventBuffer *p_eventbuffer, IDirectFBDisplayLayer *main_layer)
{		
	
	IDirectFBWindow      	*window_pic; 
	IDirectFBSurface     	*window_surface_pic;
	
	//subsurface include words, images, numbers.
	IDirectFBSurface     	*subsurface_wireless;
	IDirectFBSurface     	*subsurface_network; 
	IDirectFBSurface     	*subsurface_internet;
	 
	IDirectFBFont        	*font1;
	IDirectFBFont        	*font2;	
	
	RgbaType			 	*rgba_text;
	DFBRectangle 			*rect_text;
	DFBRectangle 			*rect0;          	
	
	pthread_t 				id[3];
	Tread_Arg 				*thread_wireless=NULL;
	Tread_Arg 				*thread_network=NULL;
	Tread_Arg 				*thread_internet=NULL;
	
	void *exit_status;
	
	char *word,*word1,*word2,*word3;				
	int fontheight=0;	
	int key=0;
	
	//start title init 							
	draw_title_string(TITLE_STATISTIC_INFO, font_title, rgba, title_space, title_window_surface);						
	//end title init 
	
	/***************   Set Font Description   ****************************/ 
	
	DFBFontDescription Fdesc;
	
	Fdesc.flags = DFDESC_HEIGHT;
	Fdesc.height = 22;
	 
	DFBCHECK(gp_dfb->CreateFont( gp_dfb, FONTS_DECKER, &Fdesc, &font1 ));
	
	font1->GetHeight( font1, &fontheight );
	
	Fdesc.height = 28;
	DFBCHECK(gp_dfb->CreateFont( gp_dfb,  FONTS_DECKER, &Fdesc, &font2 ));     
	  
	/*****************  set windows' description  *********************/ 
	
	DFBWindowDescription desc;
	 
	desc.flags  = ( DWDESC_POSX | DWDESC_POSY |DWDESC_WIDTH | DWDESC_HEIGHT | DWDESC_CAPS );
	desc.caps   = DWCAPS_ALPHACHANNEL;
	
	desc.posx   = 0;
	desc.posy   = 50;
	desc.width  = 640;
	desc.height = 400;
			
	DFBCHECK(main_layer->CreateWindow( main_layer, &desc, &window_pic ) );
	window_pic->GetSurface( window_pic, &window_surface_pic );
	window_surface_pic->Clear(window_surface_pic,0,0,0,0);
	
	/******** draw STATISTIC_MB *************/
	word=STATISTIC_MB;
			
	rect_text=(DFBRectangle*)malloc(sizeof(DFBRectangle));		
	rgba_text = (RgbaType*)malloc(sizeof(RgbaType));
	
	set_rgba(rgba_text, 0xCF, 0xCF, 0xFF, 255);
					
	grid_init(rect_text,10, H_IMAGE , W_IMAGE+70, 30 );	
	draw_text_onsubsurface(0,0,rect_text, word, font1, DSTF_TOPLEFT, rgba_text, window_surface_pic);
	
	grid_init(rect_text,360, H_IMAGE , W_IMAGE+70, 30 );	
	draw_text_onsubsurface(0,0,rect_text, word, font1, DSTF_TOPLEFT, rgba_text, window_surface_pic);
	
	set_rgba(rgba_text, 188, 188, 0xFF, 255);
	grid_init(rect_text, 182, 170+H_IMAGE , W_IMAGE+70, 30 );	
	draw_text_onsubsurface(0,0,rect_text, word, font1, DSTF_TOPLEFT, rgba_text, window_surface_pic);					
			
	/*Wireless*** set SubSurface's description & write words for Wireless *****************/ 
	
	rect0=(DFBRectangle*)malloc(sizeof(DFBRectangle));		
	grid_init(rect0, 0, 0, W_IMAGE, H_IMAGE);	
					
	DFBRectangle rectwireless= { 30, 0, W_IMAGE, H_IMAGE+60 };						
	window_surface_pic->GetSubSurface(window_surface_pic,&rectwireless,&subsurface_wireless);   
	
	word1=STATISTIC_WIRELESS;	
	set_rgba(rgba_text, 255, 255, 255, 255);                                          
	grid_init(rect_text,0, H_IMAGE , W_IMAGE, 60 );	
	draw_text_onsubsurface( W_IMAGE/2, 30,rect_text, word1, font2, DSTF_TOPCENTER, rgba_text, subsurface_wireless);
				                                     
	draw_image(image_names[0], rect0,subsurface_wireless, gp_dfb);  
	draw_statistics_num(subsurface_wireless,0);  
	 
	/*Network*** set SubSurface's description & write words for Network *******************/ 
	
	DFBRectangle rectnetwork= { 385, 0, W_IMAGE, H_IMAGE+60 };	
	window_surface_pic->GetSubSurface(window_surface_pic,&rectnetwork,&subsurface_network);   
	  
	word2=STATISTIC_NETWORK;					
	draw_text_onsubsurface( W_IMAGE/2, 30,rect_text, word2, font2, DSTF_TOPCENTER, rgba_text, subsurface_network);
				  	
	draw_image(image_names[0], rect0,subsurface_network, gp_dfb); 					
	draw_statistics_num(subsurface_network,0);
				
	/*Internet*** set SubSurface's description & write words for Internet *************/ 
	
	DFBRectangle rectinternet= {207, 170, W_IMAGE, H_IMAGE+60 };	
	window_surface_pic->GetSubSurface(window_surface_pic,&rectinternet,&subsurface_internet);   
	  
	word3=STATISTIC_INTERNET;				
	draw_text_onsubsurface( W_IMAGE/2, 30,rect_text, word3, font2, DSTF_TOPCENTER, rgba_text, subsurface_internet);
						  			
	draw_image(image_names[0], rect0,subsurface_internet, gp_dfb); 					
	draw_statistics_num(subsurface_internet,0);
				 
	window_pic->SetOpacity( window_pic, 0xFF );   //show window
	
	/**************************** Use pthread ********************************************/  			
	
	//set pthread argument
	thread_wireless=set_threadarg(	word1,	RGDB_WIRELESS_TX, 	RGDB_WIRELESS_RX,	window_surface_pic,	subsurface_wireless	,	30	, 0		);
	thread_network =set_threadarg(	word2,	RGDB_LAN_TX		,	RGDB_LAN_RX		,	window_surface_pic,	subsurface_network	,	385	, 0		);
	thread_internet=set_threadarg(	word3,	RGDB_WAN_TX		,	RGDB_WAN_RX		,	window_surface_pic,	subsurface_internet	,	207	, 170	);						
	
	//Create the thread
	gThreadRun=1;
	pthread_create(&id[0], NULL, run_statistics,(void *) thread_wireless); 		
	pthread_create(&id[1], NULL, run_statistics,(void *) thread_network); 							  	  
	pthread_create(&id[2], NULL, run_statistics,(void *) thread_internet);    	  		

	while(1){            
		key = GetInputDeviceEventByType(p_eventbuffer, PTYPE_DEFAULT_API);   	
			
		if( key == DIKI_UP ){
			gThreadRun=0;
			//	+++ Teresa Ke, use gThreadRun grobal var. and pthread_exit() function.
			//pthread_cancel(id[0]);
			pthread_join(id[0],&exit_status);   // Wait for the thread to terminate.				
			//pthread_cancel(id[1]);
		  	pthread_join(id[1],&exit_status);	// Wait for the thread to terminate.				
			//pthread_cancel(id[2]);						  	
		  	pthread_join(id[2],&exit_status);	// Wait for the thread to terminate.	
					
		    /************************** go back to provious page ****************************************************/      
			draw_title_string(TITLE_STATISTIC_SHOW, font_title, rgba, title_space, title_window_surface);
					
			free(rect0);	
		  	free(rect_text);
			free(rgba_text);
					
			font2->Release( font2 );     						
			font1->Release( font1 );    
					
			if(thread_wireless)	free(thread_wireless);
			if(thread_network)	free(thread_network);
			if(thread_internet)	free(thread_internet);
					
			if(window_surface_pic)	window_surface_pic->Release(window_surface_pic);
			if(subsurface_wireless)	subsurface_wireless->Release(subsurface_wireless);
			if(subsurface_network)	subsurface_network->Release(subsurface_network ); 
			if(subsurface_internet)	subsurface_internet->Release(subsurface_internet);
			window_pic->Destroy( window_pic);
			window_pic->Release( window_pic);      
		
			return;	  			 
		}else if( key == DIKI_A || key == DIKI_B ){							 		
			window_pic->SetOpacity( window_pic, 0 ); 
			Detect_USBMount(p_eventbuffer);
			window_pic->SetOpacity( window_pic, 255 ); 
			draw_title_string(TITLE_STATISTIC_INFO, font_title, rgba, title_space, title_window_surface);										
		}
		p_eventbuffer->Reset(p_eventbuffer);					
	}       		
}
