#ifndef _DRAW_TOOL_H_
#define _DRAW_TOOL_H_

#define H_STYLE 1
#define V_STYLE 2

typedef struct gridObj{
	DFBRectangle *rect;
	struct gridObj *next;
}GridObj;

typedef struct rgba_type{
	int r;
	int g;
	int b;
	int a;
}RgbaType;  

void clear_screen(RgbaType *rgba, DFBRectangle *DFBRectangle, IDirectFBSurface *surface);
void clear_screen_custom(RgbaType *rgba, int x, int y,int width, int height, IDirectFBSurface *surface);
void draw_title_string(char *text, IDirectFBFont *font, RgbaType *rgba, DFBRectangle *space, IDirectFBSurface *surface);
void set_rgba(RgbaType *rgba, int r, int g, int b, int a);
void scale_item(DFBRectangle *space, int icon_w, int icon_h);
void grid_free(GridObj *head);
void grid_center(DFBRectangle *space, DFBRectangle *gridItem);
void grid_init(DFBRectangle *space, int x, int y, int w, int h);
void draw_image_scale(char *icon_path, DFBRectangle *gridItem, IDirectFBSurface *surface, IDirectFB *gp_dfb);
void draw_image(char *icon_path, DFBRectangle *gridItem, IDirectFBSurface *surface, IDirectFB *gp_dfb);		
int draw_text(DFBRectangle *gridItem, char *text, IDirectFBFont *font, DFBSurfaceTextFlags flags, RgbaType *rgba, IDirectFBSurface *surface);							
int image_switch(char *image_path, DFBRectangle *space, IDirectFBSurface *window_surface, IDirectFB *gp_dfb);	
int get_grid_count(GridObj *grid);
IDirectFBFont* getFont(char *font_path, DFBFontDescription font_dsc, IDirectFB *gp_dfb);
GridObj* create_grid_tree(int grid_count, DFBRectangle *space);	
GridObj* create_view_tree(int grid_count, DFBRectangle *space);
GridObj* create_button_tree(int grid_count, DFBRectangle *space, int show_style);
GridObj* create_text_grid_tree(int page_size, int line_distance, DFBRectangle *space);
int check_image_available(char *icon_path, IDirectFB *gp_dfb);
int get_scale_size(char *icon_path, IDirectFB *gp_dfb);
#endif
