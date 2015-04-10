#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <directfb.h>
#include <stdlib.h>
#include "alpha_dfb_define.h"
#include "menu_tool.h"
#include "draw_tool.h"
#include "file_tool.h"

/*-----------------------
	layout function
-------------------------*/

void set_rgba(RgbaType *rgba, int r, int g, int b, int a){
	rgba->r = r;
	rgba->g = g;	
	rgba->b = b;
	rgba->a = a;	
}	 	

void grid_init(DFBRectangle *space, int x, int y, int w, int h){
	space->x=x;
	space->y=y;
	space->w=w;
	space->h=h;	
}

GridObj* create_grid_tree(int grid_count, DFBRectangle *space){	
	GridObj *head=NULL, *tail=NULL;	
	int x, y, w, h;
	int y_plus, x_plus, x_tmp, i;
	
	x=space->x;	
	y=space->y;	
	w=space->w;	
	h=space->h;		
	x_plus = w/3;	
	y_plus = h;
				
	for(i=0; i<grid_count; i++){
		if(head==NULL){
			head = (GridObj*)malloc(sizeof(GridObj));	
			head->rect = (DFBRectangle*)malloc(sizeof(DFBRectangle));
			head->rect->x = x-x_plus;			
			tail=head;			
		}else{
			x_tmp = tail->rect->x;
			tail->next = (GridObj*)malloc(sizeof(GridObj));				
			tail = tail->next;
			tail->rect = (DFBRectangle*)malloc(sizeof(DFBRectangle));
			tail->rect->x = x_tmp+x_plus;			
		}			
		tail->rect->y = y;
		tail->rect->w = x_plus;
		tail->rect->h = y_plus;
		tail->next = NULL;						
	}		
	return head;																										     			     			     			     						
}


GridObj* create_view_tree(int grid_count, DFBRectangle *space){	
	GridObj *head=NULL, *tail=NULL;	
	int x, y, w, h, i;
		
	x=space->x;	
	y=space->y;	
	w=space->w;	
	h=space->h;			
				
	for(i=0; i<grid_count; i++){
		if(head==NULL){
			head = (GridObj*)malloc(sizeof(GridObj));	
			head->rect = (DFBRectangle*)malloc(sizeof(DFBRectangle));			
			tail=head;			
		}else{			
			tail->next = (GridObj*)malloc(sizeof(GridObj));				
			tail = tail->next;
			tail->rect = (DFBRectangle*)malloc(sizeof(DFBRectangle));			
		}		
		tail->rect->x = x;	
		tail->rect->y = y;
		tail->rect->w = w;
		tail->rect->h = h;
		tail->next = NULL;				
	}		
	return head;																										     			     			     			     						
}

GridObj* create_text_grid_tree(int page_size, int line_distance, DFBRectangle *space)
{	
	GridObj *head=NULL, *tail=NULL;	
	int x, y, h;
	int y_plus, i;
	
	x=space->x;	
	y=space->y;			
	h=space->h;			
	y_plus = h / page_size;
	if(line_distance!=0) y_plus=line_distance;
				
	for(i=0; i<page_size; i++)
	{
		if(head==NULL)
		{
			head = (GridObj*)malloc(sizeof(GridObj));	
			head->rect = (DFBRectangle*)malloc(sizeof(DFBRectangle));						
			head->rect->y = y;					
			tail=head;						
		}else{			
			tail->next = (GridObj*)malloc(sizeof(GridObj));				
			tail = tail->next;
			tail->rect = (DFBRectangle*)malloc(sizeof(DFBRectangle));	
			y=y+y_plus;
			tail->rect->y = y;		
		}			
		tail->rect->x = x;		
		tail->rect->w = 0;
		tail->rect->h = 0;
		tail->next = NULL;						
	}		
	return head;																										     			     			     			     						
}

GridObj* create_button_tree(int button_count, DFBRectangle *space, int show_style){	
	GridObj *head=NULL, *tail=NULL;	
	int x, y, w, h, i, x_plus;
		
	x=space->x;	
	y=space->y;		
	x_plus=space->w/button_count;	
	w=x_plus;
	h=space->h;			
				
	for(i=0; i<button_count; i++)
	{
		if(head==NULL){
			head = (GridObj*)malloc(sizeof(GridObj));	
			head->rect = (DFBRectangle*)malloc(sizeof(DFBRectangle));			
			tail=head;			
			tail->rect->x = x;
		}else{									
			tail->next = (GridObj*)malloc(sizeof(GridObj));				
			tail->next->rect = (DFBRectangle*)malloc(sizeof(DFBRectangle));								
			tail->next->rect->x = tail->rect->x+x_plus;
			tail = tail->next;						
		}					
		tail->rect->y = y;
		tail->rect->w = w;
		tail->rect->h = h;		
		tail->next = NULL;		
		dprintf("\ntail->rect->x %d, tail->rect->y %d, tail->rect->w %d, tail->rect->h %d\n", tail->rect->x, tail->rect->y, tail->rect->w, tail->rect->h);		
	}		
	return head;																										     			     			     			     						
}



int get_grid_count(GridObj *grid){
	GridObj *head;
	int count=0;
	
	head=grid;		
	while(head!=NULL){
		count++;
		head=head->next;
	}
	
	return count;		
}

void grid_free(GridObj *head){	
	if(head!=NULL){
		grid_free(head->next);	
		free(head->rect);
		free(head);
	}	
}
	
/*------------------------------------------
	draw functions
-------------------------------------------*/

void clear_screen(RgbaType *rgba, DFBRectangle *gridItem, IDirectFBSurface *surface){
	DFBCHECK(surface->SetColor( surface, rgba->r, rgba->g, rgba->b, rgba->a));  	
  	DFBCHECK(surface->FillRectangle( surface, gridItem->x, gridItem->y, gridItem->w, gridItem->h));
}	

void clear_screen_custom(RgbaType *rgba, int x, int y,int width, int height, IDirectFBSurface *surface){
	DFBCHECK(surface->SetColor( surface, rgba->r, rgba->g, rgba->b, rgba->a));  	
  	DFBCHECK(surface->FillRectangle( surface, x, y, width, height));
}

void grid_center(DFBRectangle *space, DFBRectangle *gridItem){							
	int wg=0, hg=0;
	if(gridItem->w > space->w) wg=(gridItem->w-space->w)/2;
	if(gridItem->h > space->h) hg=(gridItem->h-space->h)/2;
	space->x=space->x+wg;
	space->y=space->y+hg;	
}	
		
void scale_item(DFBRectangle *space, int icon_w, int icon_h){		
	float w = 0, h = 0, d=0;
	int flag=0;
	
	w=(float)icon_w;
	h=(float)icon_h;		
			
	if(space->w > icon_w){
		flag++;
		space->w=icon_w;
	}	
	
	if(space->h > icon_h){ 
		flag++;
		space->h=icon_h;
		if(flag==2) return;
	}	
	
	if(icon_w > icon_h){
		d=w/h;
		while(1){
			if(((space->w > w)&&(space->h > h))||2*d>h) break;
			w=w-d;
			if(h>d*2) h--;
		}				
	}else if(icon_h > icon_w){
		d=h/w;	
		while(1){
			if(((space->w > w)&&(space->h > h))||2*d>w) break;
			h=h-d;
			w--;
		}		
	}				
	space->w = w;
	space->h = h;
}	

void draw_image(char *icon_path, DFBRectangle *gridItem, IDirectFBSurface *surface, IDirectFB *gp_dfb)
{	
	IDirectFBImageProvider *provider;
	int flag;	
	
	flag = check_image_available(icon_path, gp_dfb);	
	if(flag==0) icon_path=M_IMAGE_G; 
	surface->ReleaseSource(surface);				
	gp_dfb->CreateImageProvider( gp_dfb, icon_path, &provider );									
	provider->RenderTo( provider, surface, gridItem);     	
	provider->Release( provider );		
}	


void draw_image_scale(char *icon_path, DFBRectangle *gridItem, IDirectFBSurface *surface, IDirectFB *gp_dfb)
{
	IDirectFBImageProvider *provider;	
	DFBSurfaceDescription dsc;
	DFBRectangle *space;
	int flag;
	
	flag = check_image_available(icon_path, gp_dfb);
	if(flag==0) icon_path=M_IMAGE_G;
	surface->ReleaseSource(surface);
			
	space=(DFBRectangle*)malloc(sizeof(DFBRectangle));
	space->x=gridItem->x;
	space->y=gridItem->y;
	space->w=gridItem->w;
	space->h=gridItem->h;	
		
	gp_dfb->CreateImageProvider( gp_dfb, icon_path, &provider );						
	provider->GetSurfaceDescription (provider, &dsc);	
	scale_item(space, dsc.width, dsc.height);
	grid_center(space, gridItem);			
	provider->RenderTo( provider, surface, space);     	
	provider->Release( provider );
	free(space);
}
	
int image_switch(char *image_path, DFBRectangle *space, IDirectFBSurface *window_surface, IDirectFB *gp_dfb){
	window_surface->Clear(window_surface, 0, 0, 0, 0);
	draw_image(image_path, space, window_surface, gp_dfb);
	window_surface->Flip( window_surface, NULL, DSFLIP_NONE );
	return 1;	
}	


int check_image_available(char *icon_path, IDirectFB *gp_dfb)
{
	IDirectFBImageProvider *provider;
	int flag=1;
				
	if(icon_path!=NULL&&!check_image_sizesafe(icon_path, FILE_MAX_SIZE)) flag=0;				
	if(gp_dfb->CreateImageProvider( gp_dfb, icon_path, &provider )!=DFB_OK) 	
		flag=0;						
	else	
		provider->Release( provider );				
	return flag;
}	

/*------------------------------------------
	draw text functions
-------------------------------------------*/

IDirectFBFont* getFont(char *font_path, DFBFontDescription font_dsc, IDirectFB *gp_dfb)
{
	IDirectFBFont *font;	
	
	if(gp_dfb->CreateFont( gp_dfb, font_path, &font_dsc, &font )!=DFB_OK)
	{		
		gp_dfb->CreateFont( gp_dfb, FONTS_DECKER, &font_dsc, &font);
	}	
	return font;
}

int draw_text(DFBRectangle *gridItem, char *text, IDirectFBFont *font, DFBSurfaceTextFlags flags, RgbaType *rgba, IDirectFBSurface *surface){
	int x = 0, y = 0, width = 0, height = 0, text_width = 0;
		  	
	x = gridItem->x;
	y = gridItem->y;					
	width = gridItem->w;
	height = gridItem->h;		  	        	
	surface->ReleaseSource(surface);	  	  		  	  	  		 	
  	surface->SetFont (surface, font); 
  	surface->SetColor( surface, rgba->r, rgba->g, rgba->b, rgba->a );
  	font->GetStringWidth (font, text, -1, &text_width);  	
  	surface->DrawString (surface, text, -1, x , y, flags);   	  	  	  		
  	return text_width;
}

void draw_title_string(char *text, IDirectFBFont *font, RgbaType *rgba, DFBRectangle *space, IDirectFBSurface *surface){	
  	char tmp[34], *hs=NULL;
  	int len, len2;
  	
  	memset(tmp, 0, 34);
  	surface->Clear(surface, 0, 0 ,0 ,0);
  	len=strlen(text);
  	if(len>30) 
  	{
  			strncpy(tmp, text, 30);  		
  			strcat(tmp,"...");
  	}else{
  			strncpy(tmp, text, 30);
	}			
	
	if((hs=strstr(tmp, "amp;"))!=NULL)
	{		
		len2=strlen(hs);				
		strcpy(tmp+(len-len2), hs+4);		
		len=len-4;
		memset(tmp+len, 0, 34-len);		
	}
	
	draw_text(space, tmp, font, DSTF_TOPCENTER, rgba, surface);	
	surface->Flip( surface, NULL, DSFLIP_NONE );			
}	

int get_scale_size(char *icon_path, IDirectFB *gp_dfb)
{
	IDirectFBImageProvider *provider;	
	DFBSurfaceDescription dsc;
	int w=0, h=0, scale_size=1, scale_size2=1;
			
	if(icon_path==NULL) return 0;
			
	if(gp_dfb->CreateImageProvider( gp_dfb, icon_path, &provider )==DFB_OK) 		
	{				
		provider->GetSurfaceDescription (provider, &dsc);		
		w=dsc.width;
		h=dsc.height;
		provider->Release( provider );	
		dprintf("\nicon_path %s w %d h %d\n", icon_path, w, h);
			
		if(w<=640) scale_size=1;
		else if(w>=640&&w<1280) scale_size = 1;  
		else if(w>=1280&&w<2560) scale_size = 2; //scale 1/2	
		else if(w>=2560&&w<3840) scale_size = 4; //scale 1/4	
		else if(w>=3840) scale_size = 8; 	       //scale 1/8			
		
		if(h<480) scale_size2=1;
		else if(h>=480&&h<960) scale_size2 = 1;  
		else if(h>=960&&h<1920) scale_size2 = 2; //scale 1/2	
		else if(h>=1920&&h<2880) scale_size2 = 4; //scale 1/4	
		else if(h>2880) scale_size2 = 8; 	       //scale 1/8				
		
		if(scale_size>scale_size2) return scale_size;
		else return scale_size2;
	}else{
		return 0;
	}	
}
