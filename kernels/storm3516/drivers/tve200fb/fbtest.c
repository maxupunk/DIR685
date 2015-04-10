#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <syslog.h>
#include <errno.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>

#include "ffb-api.h"

#define MAX_X	720
#define MAX_Y   480

static unsigned char *video_addr;
static struct fb_var_screeninfo fb_vinfo;
static int fb_max_x = 720;
static int fb_max_y = 576;
static int fb_Bpp = 4;

static void draw_point(int x, int y, int red, int green, int blue)
{
        unsigned char *addr;

        addr = video_addr + (y * fb_max_x * 4) + (x * 4);

//      printf("%s: x=%d, y=%d, addr=0x%x\r\n", __func__, x, y, addr);

        addr[0] = 0;
        addr[1] = blue;
        addr[2] = green;
        addr[3] = red;
}

int main(int argc, char *argv[])
{
    	FILE *fp; 
    	int  fb_dev_fd; 
    	struct stat fileStat;
    	int  handle;
    	unsigned int  file_size;
    	unsigned char *video_buffer;
    	unsigned int  i, x, y;
	int ret;
	unsigned int data, input_res;
	int RGBorder;
	unsigned char  pixel[4];
	unsigned char *ptr, *ptr1, *addr;
	int file_type;
	int line_size;

	if (argc < 2)
	{
		printf("usage: vtest {imagefile} [input file type: 0-CIF, 1-VGA, 2-D1 ] [RGB ordering: 0-555, 1-565, 2-888]\r\n");
		exit(-1);
	}
/*************************************************/	
    	if((fp = fopen(argv[1], "rb")) == NULL)
    	{
    		printf("open %s fail !\n", argv[1]);
    		return (-1);
	}	
    	handle = fileno(fp);
    	if (fstat(handle, &fileStat) < 0)
    	{
        	printf("ERROR: Read File Stat Error.\n");
        	return -1;
    	}        
    	file_size = fileStat.st_size;
	printf("file size = %d \n",file_size);
	
    	video_buffer = malloc(file_size+2);
    	if (!video_buffer)
    	{
		printf("ERROR: Allocate video buffer %d bytes failed!!\r\n", file_size+2);
       		return -1;    
	}

    	if(fread(video_buffer, file_size, 1, fp) != 1 || ferror(fp))
    	{
        	free(video_buffer);
        	fclose(fp);
		printf("ERROR: Read %s failed!!!\r\n", argv[1]);
        	return -1;
    	}
    	fclose(fp);       


	printf("Open /dev/fb0 device......\r\n");
    	if( (fb_dev_fd = open("/dev/fb0", O_RDWR)) < 0)
    	{
    		printf("open %s fail !\n", "/dev/fb0");
    		return (-1);
	}

	if (ioctl(fb_dev_fd, FBIOGET_VSCREENINFO, &fb_vinfo)) {
                printf("Can't get VSCREENINFO: %s\n", strerror(errno));
               return 1;
        }

        fb_max_x = fb_vinfo.xres;
        fb_max_y = fb_vinfo.yres;

	//debug_Aaron, fix the input resolution to D1
	input_res = 2;
	ioctl(fb_dev_fd, FFB_INPUT_RES, &input_res);
	if (argc > 2)
	{
		file_type = atoi(argv[2]);
	}	
	else
		file_type = 2;
	if (file_type == 1)   /* VGA */
		line_size = 640;
	else
		line_size = 720;

	if (argc > 3)
	{	
		RGBorder = atoi(argv[3]);
		ioctl(fb_dev_fd, FFB_SET_RGB_ORDER, &RGBorder);
	}

	ioctl(fb_dev_fd, FFB_GET_CTRL1_VAL, &data);
	printf("Ctrl1 value=%d\r\n", data);

	printf("Write Out %s to /dev/fb0...\r\n", argv[1]);

        addr = mmap(NULL, fb_max_x*fb_max_y*fb_Bpp, PROT_READ|PROT_WRITE,MAP_SHARED,fb_dev_fd,0);

	if (addr == 0xffffffff)
	{
		printf("%s: mmap() failed!!!\r\n", __func__);
		exit(-1);
	}
	printf("addr=0x%x\r\n", addr);
	ptr1 = addr;

	video_addr = addr;
//debug_Aaron on 03/11/2008, for RGB 888
	if (RGBorder == 2)
	{
		ptr = video_buffer;
		x = y = 0;
		for (i=0; i < file_size; i+=3)
		{
			draw_point(x, y, *ptr, *(ptr+1), *(ptr+2)); 
			ptr += 3;
			x += 1;
			if ( x >= line_size)
			{
				x = 0;
				y++;
			}
		}
	}
	else
	{
		//write(fd, video_buffer, file_size);
		memcpy(ptr1, video_buffer, file_size);
	}


	while(1)
	{
		printf("Any key...\r\n");		
		sleep(3);
	}
        free(video_buffer);
	close(fb_dev_fd);
	
}


