#ifndef _MENU_TOOL_H_
#define _MENU_TOOL_H_
#include "draw_tool.h"
#include "fcrss_parser.h"
#include "file_tool.h"
#include "packet_serialize.h" 

typedef struct icon_obj{
	int index;
	char *icon_dsc;
	char *icon_path;					
	struct icon_obj *right;
	struct icon_obj *left;			
	IDirectFBWindow *window;		
	IDirectFBSurface *window_surface;		
}IconObj;

typedef struct slide_obj{
	int x;
	int end_x;
	int y;
	int len;
	int step; 	
	int show_flag;
	DFBRectangle *icon_space;
	DFBRectangle *big_icon_space;
	IconObj *frame;
	IconObj *frame2;
	IconObj *frame3;
}SlideObj;

typedef struct view_obj{
	FcNode *node;	
	//IconObj *icon;
	int flag;
	IDirectFBEventBuffer *p_eventbuffer;
}ViewObj;

typedef struct text_obj{
	int index;
	char *content;
	DFBRectangle *text_space;
	struct text_obj *right;
	struct text_obj *left;
}TextObj;

int get_icon_count(IconObj *icon);
SlideObj* slide_init(GridObj *grid, int slide_step);
IconObj* get_icon_head(IconObj *icon);
IconObj* get_icon_tail(IconObj *icon);
IconObj* create_icon_tree(GridObj *grid, IDirectFBDisplayLayer *main_layer, DFBWindowDescription win_dsc);
IconObj* slide_right(FcNode *node, SlideObj *slide_info,IconObj *icon, IDirectFB *gp_dfb);
IconObj* slide_left(FcNode *node, SlideObj *slide_info,IconObj *icon, IDirectFB *gp_dfb);
IconObj* folder_selected(char *file_path, IDirectFB *gp_dfb, IDirectFBDisplayLayer *main_layer, DFBWindowDescription win_dsc);
FcNode* create_fcfile_tree(char *local_dir_path, int is_top_layer, int *folder_exist_flag, IDirectFB *gp_dfb);
FcNode* reset_fcfile_tree(FcNode *node, char *this_guid);
FcNode* filter_photo_tree(FcNode *node);
FcNode* create_menu_tree(char *menu_title[], char *menu_icon_path[]);
FcNode* get_fcnode_selected(int node_count, FcNode *node, int flag);
TextObj* create_text_node_tree(GridObj *grid);
void icons_free(IconObj *icon);
void icon_clear(IconObj *icon, RgbaType *rgba);
void icon_opacity(IconObj *icon, int opacity_value);
void icon_stackclass(IconObj *icon, DFBWindowStackingClass stack_leve);
void set_icon_value(IconObj *icon, char *icon_dsc, char *icon_path, int index);
void set_windsc_xywh(DFBWindowDescription *dsc, DFBRectangle *gridItem);									
void set_icon_window(IDirectFBDisplayLayer *main_layer, DFBWindowDescription win_dsc, IconObj *icon);
void move_left_index(FcNode *node, IconObj *icon);
void move_right_index(FcNode *node, IconObj *icon);
void blit_to_frame(FcNode *node, SlideObj *slide_info, IconObj *frame, IconObj *icon, IDirectFB *gp_dfb);
void draw_icon_tree(FcNode *node, IconObj *icon, DFBRectangle *icon_space, IDirectFB *gp_dfb);
void remove_fcfile(FcNode *head);
void view_player(ViewObj *view);
void* view_player_r(void *arg);
void pthread_cancel_msg(int thread_flag);
void pthread_create_msg(int thread_flag);
void draw_text_table(TextObj *head, IDirectFBSurface *surface);
void upnp_text_node_map(UPnPNode *uhead, TextObj *thead);
void texts_free(TextObj *text);
void go_next_page(UPnPNode *unode, TextObj *tnode, IDirectFBSurface *surface);
void go_prev_page(int page_size, UPnPNode **unode, TextObj *tnode, IDirectFBSurface *surface);
void shift_text_left(TextObj **head, IDirectFBSurface *surface);
void shift_text_right(TextObj **head, IDirectFBSurface *surface);
#endif	




		
							
