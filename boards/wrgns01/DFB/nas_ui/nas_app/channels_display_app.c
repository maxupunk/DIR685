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
#include <errno.h>
#include <fcntl.h>
#include "alpha_dfb_define.h"
#include "draw_tool.h"
#include "file_tool.h"
#include "menu_tool.h"
#include "fcrss_parser.h"
#include "fcrss_command.h"
#include "fcrss_serialize.h"
#include "str_tool.h"
#include "alert_center.h"
#include "detect_info.h"
#include "fcrss_handler.h"
#include "download_tool.h"

//extern variable from main.c
extern IDirectFB *gp_dfb;
extern IDirectFBDisplayLayer *main_layer;
extern DFBWindowDescription win_dsc;
extern DFBRectangle *screen_space;
extern int GetInputDeviceEventByType(IDirectFBEventBuffer *p_eventbuffer, int PType); 

//extern variable from fcrss_handler.c
extern FcNode *fcshow_node;

//extern variable from framechannel.c
extern pthread_mutex_t f_mutex;
extern pthread_cond_t f_cond;
extern int pthread_num_f;

void Channels_Display_App(IDirectFBEventBuffer *p_eventbuffer)
{					
	DownloadObj *dobj;
	GridObj *grid;		
	IconObj *icon;	
	ViewObj *view;	
	pthread_t tid[2];		
	struct timespec ts;
	int key = 0, serv_response=0, grid_count=1, download_count=3, node_count=0;	
	int thread_flag=0;	
			 		     		
	
	icon_alert(PHOTO_LOADING_G, D_MOVE_CENTER);	
	
	//get channel_show node tree
	serv_response= client_cmd_handler(p_eventbuffer, CHANNEL_SHOW_GET, NULL); 		
	
	if(serv_response!=REQ_SUCCESS) 
	{		
		close_icon_alert();
		if(serv_response==WAN_ERROR) alert_cmd_handler(p_eventbuffer, WAN_ERROR);			
		else if(serv_response==DNS_ERROR) alert_cmd_handler(p_eventbuffer, DNS_ERROR);
		return;			
	}	
				
	//get channel_show node count
	node_count=get_fcnode_count(fcshow_node);	
			
	//create one window to show photo
	win_dsc.caps = DWCAPS_NONE;
	grid=create_view_tree(grid_count, screen_space);
	icon=create_icon_tree(grid, main_layer, win_dsc); 										
	
	fc_download_init_v2(fcshow_node);
				
    //draw first photo, set window opacity and position of window stack 
	draw_image_scale(fcshow_node->local_file_path, screen_space, icon->window_surface, gp_dfb);		
	icon_opacity(icon, 255);	 	 	    			
	icon_stackclass(icon, DWSC_MIDDLE);	     	
									
	//close loading icon
	close_icon_alert();
	
	//create DownloadObj for download thread(thread id is tid[0])
	dobj=(DownloadObj*)malloc(sizeof(DownloadObj));
	dobj->node=fcshow_node;
	dobj->d_count=download_count;
	dobj->d_flag=1;		
										
	//create ViewObj for slide-show thread(thread id is tid[1]) to display photos 
	view=(ViewObj*)malloc(sizeof(ViewObj));
	view->p_eventbuffer=p_eventbuffer;
	view->node=fcshow_node;
	view->flag=1;	
	pthread_create(&tid[1], NULL, &view_player_r, view);			                                              	  							                                   	  		
		
	while(1)
	{            		
		key = GetInputDeviceEventByType(p_eventbuffer,PTYPE_NOSCREEN_API);  
		
 		if( key == DIKI_UP ){	
 			//goto point
 			key_up:   			 			 						
			//delete slide show thread
			dprintf("\ndelete old slide show thread by tid %d\n", (int)tid[1]);
			thread_flag=pthread_cancel(tid[1]);
			pthread_cancel_msg(thread_flag);
			  	 			
 			client_cmd_handler(p_eventbuffer, CHANNEL_SHOW_THREAD_STOP, NULL);  
 			free(view);	
 			free(dobj);
 			grid_free(grid);
 			icons_free(icon); 									 		     			
 			remove_fcfile(fcshow_node);
 			fcshow_node=delete_fcnode_tree(fcshow_node);     						     			  			     			
 			win_dsc.caps = DWCAPS_ALPHACHANNEL;   		 			 			 			
 			return;	          			           												
		}else if( key == DIKI_LEFT && node_count>1){			
			//delete slide show thread
			dprintf("\ndelete old slide show thread by tid %d\n", (int)tid[1]);
			thread_flag=pthread_cancel(tid[1]);
			pthread_cancel_msg(thread_flag);
			
			//check network status
			serv_response=client_cmd_handler(p_eventbuffer, CHECK_SERVER_STATUS, NULL); 
														
			//move left
			shift_fcnode_left(fcshow_node);
			fcshow_node=get_fcnode_head(fcshow_node);	
			
			if(serv_response==WAN_ERROR||serv_response==DNS_ERROR)
			{					
				while(!check_file_exist(fcshow_node->local_file_path)) 
				{
					//move left
					shift_fcnode_left(fcshow_node);
					fcshow_node=get_fcnode_head(fcshow_node);
				}																														
			}else{																									                        	            				
				//create left-download thread
				if(pthread_num_f<2)
				{			
					dobj->node=fcshow_node;		
					dobj->d_flag=0;		
					
					ts.tv_sec=time(NULL)+60;
					thread_flag=pthread_create(&tid[0], NULL, &fc_download_r, dobj);
	            	pthread_create_msg(thread_flag);	         	           		                        		       						
					pthread_mutex_lock(&f_mutex);	
					dprintf("\nbefore cond wait\n");																										
					if(pthread_num_f!=0) pthread_cond_timedwait(&f_cond, &f_mutex, &ts);				
					dprintf("\nafter cond wait\n");					
					pthread_mutex_unlock(&f_mutex);		
				}																												
			}	
			
			//draw photo
			int fd;
			
			if(((fd=open(fcshow_node->local_file_path, O_RDWR))!=-1)&&check_image_available(fcshow_node->local_file_path, gp_dfb))
			{																			
				if(lockf(fd, F_TEST, 0)==-1)
				{
					dprintf("\n file %s is locked\n", fcshow_node->local_file_path);										
				}else{
					dprintf("\nleft filename-> %s\n", fcshow_node->local_file_path);
					icon->window_surface->Clear(icon->window_surface, 0, 0, 0, 0);						
					draw_image_scale(fcshow_node->local_file_path, screen_space, icon->window_surface, gp_dfb);
					icon->window_surface->Flip(icon->window_surface, NULL, DSFLIP_NONE );	                        
				}
				close(fd);					
			}					
				
			p_eventbuffer->Reset(p_eventbuffer);									
		}else if( key == DIKI_RIGHT && node_count>1){
			//delete slide show thread
			dprintf("\ndelete old slide show thread by tid %d\n", (int)tid[1]);
			thread_flag=pthread_cancel(tid[1]);
			pthread_cancel_msg(thread_flag);
			
			//check network status
			serv_response=client_cmd_handler(p_eventbuffer, CHECK_SERVER_STATUS, NULL); 
													 																							
			//move right
			shift_fcnode_right(fcshow_node);
			fcshow_node=get_fcnode_head(fcshow_node);
			
			if(serv_response==WAN_ERROR||serv_response==DNS_ERROR)
			{					
				while(!check_file_exist(fcshow_node->local_file_path)) 
				{
					//move left
					shift_fcnode_right(fcshow_node);
					fcshow_node=get_fcnode_head(fcshow_node);
				}																														
			}else{					
				//create right-download thread				
				if(pthread_num_f<2)
				{								
					dobj->node=fcshow_node;			
					dobj->d_flag=1;	
					
					ts.tv_sec=time(NULL)+60;
					thread_flag=pthread_create(&tid[0], NULL, &fc_download_r, dobj);			
					pthread_create_msg(thread_flag);																				
					pthread_mutex_lock(&f_mutex);	
					dprintf("\nbefore cond wait\n");																										
					if(pthread_num_f!=0) pthread_cond_timedwait(&f_cond, &f_mutex, &ts);				
					dprintf("\nafter cond wait\n");									
					pthread_mutex_unlock(&f_mutex);																					
				}	
				
			}	
						
			//draw photo
			int fd;
			
			if(((fd=open(fcshow_node->local_file_path, O_RDWR))!=-1)&&check_image_available(fcshow_node->local_file_path, gp_dfb))
			{	        		        																							        		        		        		        	
				if(lockf(fd, F_TEST, 0)==-1)
				{
					dprintf("\nfile %s is locked\n", fcshow_node->local_file_path);					
				}else{
		        	dprintf("\nright filename-> %s\n", fcshow_node->local_file_path);
		        	icon->window_surface->Clear(icon->window_surface, 0, 0, 0, 0);									
				    draw_image_scale(fcshow_node->local_file_path, screen_space, icon->window_surface, gp_dfb);			    
					icon->window_surface->Flip(icon->window_surface, NULL, DSFLIP_NONE );	            			
				}	
				close(fd);									
			}	
						
			p_eventbuffer->Reset(p_eventbuffer);								
		}else if( key == DIKI_V){													
			//slide show start, check update version 			
			serv_response=client_cmd_handler(p_eventbuffer, GET_CHANNEL_SHOW_UPDATE_VERSION, NULL); 
			
			switch(serv_response)
			{	 						
				case DNS_ERROR:
				case WAN_ERROR:					
					//wan error mode
					dprintf("\nwan error mode\n");
					if(node_count>1)
					{	
						//move right
						shift_fcnode_right(fcshow_node);
						
						//create right-download thread
						fcshow_node=get_fcnode_head(fcshow_node);							
																		
						//draw photo										
						if(check_file_exist(fcshow_node->local_file_path)&&check_image_available(fcshow_node->local_file_path, gp_dfb))
						{																		
							icon->window_surface->Clear(icon->window_surface, 0, 0, 0, 0);						
							draw_image_scale(fcshow_node->local_file_path, screen_space, icon->window_surface, gp_dfb);									
							icon->window_surface->Flip(icon->window_surface, NULL, DSFLIP_NONE );								
							view->flag=1;
						}else{
							view->flag=0;
						}												
					}				
						
					//run slide-show function
					view->node=fcshow_node;							
					pthread_create(&tid[1], NULL, &view_player_r, view);					
					break;				
				case DO_UPDATE:									
					//channel-show update mode	
					dprintf("\nupdate mode\n");						
														
					//do channel show update
					serv_response= client_cmd_handler(p_eventbuffer, CHANNEL_SHOW_UPDATE, NULL); 					
					if(serv_response!=REQ_SUCCESS&&serv_response!=WAN_ERROR&&serv_response!=DNS_ERROR) goto key_up;					 					
					
					//reassign node_count.
                    node_count=get_fcnode_count(fcshow_node); 
                                                            
                    //download some photos
                    dobj->node=fcshow_node;  
                    dobj->d_flag=1;	
                    
                   	if(pthread_num_f<2)
					{																				
						ts.tv_sec=time(NULL)+60;
						thread_flag=pthread_create(&tid[0], NULL, &fc_download_r, dobj);			
						pthread_create_msg(thread_flag);																				
						pthread_mutex_lock(&f_mutex);	
						dprintf("\nbefore cond wait\n");																										
						if(pthread_num_f!=0) pthread_cond_timedwait(&f_cond, &f_mutex, &ts);				
						dprintf("\nafter cond wait\n");									
						pthread_mutex_unlock(&f_mutex);																					
					}	
							                  		                    																																																											
					//draw photo										
					int fd;
					
					if(((fd=open(fcshow_node->local_file_path, O_RDWR))!=-1)&&check_image_available(fcshow_node->local_file_path, gp_dfb))
					{																																																												
						if(lockf(fd, F_TEST, 0)==-1)
						{
							dprintf("\n file %s is locked\n", fcshow_node->local_file_path);										
							view->flag=0;
						}else{			
							dprintf("\nupdate mode filename-> %s\n", fcshow_node->local_file_path);
							icon->window_surface->Clear(icon->window_surface, 0, 0, 0, 0);																		
							draw_image_scale(fcshow_node->local_file_path, screen_space, icon->window_surface, gp_dfb);									
							icon->window_surface->Flip(icon->window_surface, NULL, DSFLIP_NONE );				
							view->flag=1;
						}								
						close(fd);																													
					}else{						
						view->flag=0;
					}				
																				
					//run slide-show function			
					view->node=fcshow_node;
					pthread_create(&tid[1], NULL, &view_player_r, view);									
					break;
				case DO_NOTHING:					
					//slide show mode
					dprintf("\nslide show mode\n");		
																				
					if(node_count>1)
					{																									
						//move right
						shift_fcnode_right(fcshow_node);
						
						//create right-download thread
						fcshow_node=get_fcnode_head(fcshow_node);									
						if(pthread_num_f<2)
						{								
							dobj->node=fcshow_node;			
							dobj->d_flag=1;	
							
							ts.tv_sec=time(NULL)+60;
							thread_flag=pthread_create(&tid[0], NULL, &fc_download_r, dobj);			
							pthread_create_msg(thread_flag);																				
							pthread_mutex_lock(&f_mutex);	
							dprintf("\nbefore cond wait\n");																										
							if(pthread_num_f!=0) pthread_cond_timedwait(&f_cond, &f_mutex, &ts);				
							dprintf("\nafter cond wait\n");									
							pthread_mutex_unlock(&f_mutex);																					
						}	
																										
						//draw photo	
						int fd;
																					
						if(((fd=open(fcshow_node->local_file_path, O_RDWR))!=-1)&&check_image_available(fcshow_node->local_file_path, gp_dfb))
						{																																																											
							if(lockf(fd, F_TEST, 0)==-1)
							{
								dprintf("\n file %s is locked\n", fcshow_node->local_file_path);										
								view->flag=0;	
							}else{											
								dprintf("\nslide show mode filename-> %s\n", fcshow_node->local_file_path);
								icon->window_surface->Clear(icon->window_surface, 0, 0, 0, 0);													
								draw_image_scale(fcshow_node->local_file_path, screen_space, icon->window_surface, gp_dfb);																
								icon->window_surface->Flip(icon->window_surface, NULL, DSFLIP_NONE );															
								view->flag=1;	
							}
							close(fd);																														
						}else{
							view->flag=0;
						}												
					}		
										
					//run slide-show function 					
					view->node=fcshow_node;	
					pthread_create(&tid[1], NULL, &view_player_r, view);									
					break;				
				default:
					goto key_up;
					break;
			}											
		}else if( key == DIKI_DOWN && node_count>1){			
			
			//delete slide show thread
			dprintf("\ndelete old slide show thread by tid %d\n", (int)tid[1]);
			thread_flag=pthread_cancel(tid[1]);
			pthread_cancel_msg(thread_flag);
						
			//run slide-show function 								
			p_eventbuffer->Reset(p_eventbuffer);								
			view->node=get_fcnode_head(fcshow_node);
			view->flag=1;		
			pthread_create(&tid[1], NULL, &view_player_r, view);						
		}else if( key == DIKI_A || key == DIKI_B ){									
			//delete slide show thread
			dprintf("\ndelete old slide show thread by tid %d\n", (int)tid[1]);
			thread_flag=pthread_cancel(tid[1]);
			pthread_cancel_msg(thread_flag);
																									
			//hide channel-show surface
			icon_opacity(icon, 0);
			
			//show USB user interface
			Detect_USBMount(p_eventbuffer);
			
			//show channel-show surface
			icon_opacity(icon, 255);
			
			//run slide-show function 								
			p_eventbuffer->Reset(p_eventbuffer);								
			view->node=get_fcnode_head(fcshow_node);
			view->flag=1;		
			pthread_create(&tid[1], NULL, &view_player_r, view);											
		}			
	}	    				                        
}
