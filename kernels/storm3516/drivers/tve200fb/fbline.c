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

#include "ffb-api.h"

unsigned char *video_addr;

#define MAX_X	720
#define MAX_Y	480
#define RED_COLOR	0xff
#define GREEN_COLOR	0xff
#define BLUE_COLOR	0xff
static void draw_point(int x, int y)
{
	unsigned char *addr;

	addr = video_addr + (y * MAX_X * 4) + (x * 4);	

//	printf("%s: x=%d, y=%d, addr=0x%x\r\n", __func__, x, y, addr);

	addr[0] = 0;
	addr[1] = BLUE_COLOR;
	addr[2] = GREEN_COLOR;
	addr[3] = RED_COLOR;
}
static void draw_line(int x, int y, int x1)
{
//	printf("%s: x=%d, y=%d, x1=%d\r\n", __func__, x, y, x1);
	for (; x < x1; x++)
	{
		draw_point(x, y);
	}
}
static void draw_rect(int x, int y, int x1, int y1)
{
	for (; y < y1; y++)
        {
                draw_line(x, y, x1);
        }
}	

int main(int argc, char *argv[])
{
	int fd;
    	unsigned char *video_buffer;
    	unsigned int  x, y;
	int ret;
	unsigned int data, input_res;
	int RGBorder;

	if (argc < 3)
	{
		printf("usage: vtest {x y} [x1] [y1]\r\n");
		exit(-1);
	}

	printf("Open /dev/fb0 device......\r\n");
    	if( (fd = open("/dev/fb0", O_RDWR)) < 0)
    	{
    		printf("open %s fail !\n", "/dev/tve");
    		return (-1);
	}

	input_res = 2;
	ioctl(fd, FFB_INPUT_RES, &input_res);
	RGBorder = 2;
	ioctl(fd, FFB_SET_RGB_ORDER, &RGBorder);

	ioctl(fd, FFB_GET_CTRL1_VAL, &data);
	printf("Ctrl1 value=%d\r\n", data);

        video_addr = mmap(NULL, MAX_X*MAX_Y*4, PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

	if (video_addr == 0xffffffff)
	{
		printf("%s: mmap() failed!!!\r\n", __func__);
		exit(-1);
	}
	printf("video_addr=0x%x\r\n", video_addr);
	x = atoi(argv[1]);
	y = atoi(argv[2]);
	if (argc < 4)
		draw_point(x, y);
	else
	{
		if (argc < 5)
			draw_line(x, y, atoi(argv[3]));
		else
			draw_rect(x, y, atoi(argv[3]), atoi(argv[4]));
	}
		
	while(1)
	{
		printf("Any key...\r\n");		
		sleep(3);
	}
        free(video_buffer);
	close(fd);
	
}


