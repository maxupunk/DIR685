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

#define FILE_TYPE_VIF	0
#define FILE_TYPE_VGA   1	
#define FILE_TYPE_D1    2  	

#define RGB_ORDER_555	0
#define RGB_ORDER_565   1	
#define RGB_ORDER_888	2

#define MAX_X	720
#define MAX_Y   480
unsigned char video_buf[MAX_X*MAX_Y*4];
unsigned char *video_addr;
int fb_fd;
static void draw_point(int x, int y, int red, int green, int blue)
{
        unsigned char *addr;

        addr = video_buf + (y * MAX_X * 4) + (x * 4);

//      printf("%s: x=%d, y=%d, addr=0x%x\r\n", __func__, x, y, addr);

        addr[0] = 0;
        addr[1] = blue;
        addr[2] = green;
        addr[3] = red;
}

static void usage(void)
{
	 printf("usage: vtest {conf_file}\r\n");
}

static int show_file(char *filename, int file_type, int RGBorder)
{
    	FILE *fp; 
    	int  fd; 
    	struct stat fileStat;
    	int  handle;
    	unsigned int  file_size;
    	unsigned char *file_buffer;
    	unsigned int  i, x, y, x1;
	int ret;
	unsigned int data;
	unsigned char *ptr, *ptr1, *addr;
	int line_size;

    	if((fp = fopen(filename, "rb")) == NULL)
    	{
    		printf("open %s fail !\n", filename);
    		return (-1);
	}	
	printf("Open %s OK\r\n", filename);
    	handle = fileno(fp);
    	if (fstat(handle, &fileStat) < 0)
    	{
        	printf("ERROR: Read File Stat Error.\n");
        	return -1;
    	}        
    	file_size = fileStat.st_size;
	printf("file size = %d \n",file_size);
	
    	file_buffer = malloc(file_size + 2);
    	if (!file_buffer)
    	{
		printf("ERROR: Allocate file buffer %d bytes failed!!\r\n", file_size+2);
       		return -1;    
	}

    	if(fread(file_buffer, file_size, 1, fp) != 1 || ferror(fp))
    	{
        	free(file_buffer);
        	fclose(fp);
		printf("ERROR: Read %s failed!!!\r\n", filename);
        	return -1;
    	}
    	fclose(fp);       

	if (file_type == FILE_TYPE_VGA)   /* VGA */
		line_size = 640;
	else
		line_size = 720;

	//ioctl(fb_fd, FFB_SET_RGB_ORDER, &RGBorder);

	//ioctl(fb_fd, FFB_GET_CTRL1_VAL, &data);
	//printf("Ctrl1 value=%d\r\n", data);

	printf("Write Out %s to /dev/fb0...\r\n", filename);

	//debug_Aaron on 03/11/2008, for RGB 888
	ptr = file_buffer;
	if (RGBorder == RGB_ORDER_888)
	{
		x = y = 0;
		for (i=0; i < file_size; i+=3)
		{
			draw_point(x, y, *ptr, *(ptr+1), *(ptr+2)); 	
			x++;
			ptr += 3;
			if ( x >= line_size)
			{
				x = 0;
				y++;
			}
		}
		memcpy(video_addr, video_buf, MAX_X*MAX_Y*4);
	}
	else
	{
		memcpy(video_addr, file_buffer, file_size);
	}

        free(file_buffer);
	
}


int main(int argc, char *argv[])
{
	FILE *fp;
        int  fd; 
        struct stat fileStat;
        int  handle;
        unsigned int  file_size;
        unsigned char *file_buffer;
	int input_res;
	int file_type, RGBorder;
	char szFileName[512+1];
	char szFileType[20+1];
	char szRGBorder[20+1];
	char *ptr;

	if (argc < 2)
	{
		usage();
		exit(-1);
	}

	printf("Open /dev/fb0 device......\r\n");
        if( (fb_fd = open("/dev/fb0", O_RDWR)) < 0)
        {
                printf("open %s fail !\n", "/dev/tve");
                return (-1);
        }
	 //debug_Aaron, fix the input resolution to D1
        input_res = 2;
        ioctl(fb_fd, FFB_INPUT_RES, &input_res);

	RGBorder = 2;
	ioctl(fb_fd, FFB_SET_RGB_ORDER, &RGBorder);

 	video_addr = mmap(NULL, MAX_X*MAX_Y*4, PROT_READ|PROT_WRITE,MAP_SHARED, fb_fd, 0);

        if (video_addr == 0xffffffff)
        {
                printf("%s: mmap() failed!!!\r\n", __func__);
                exit(-1);
        }
        printf("video_addr=0x%x\r\n", video_addr);

	if((fp = fopen(argv[1], "rb")) == NULL)
        {
                printf("open %s fail !\n", argv[1]);
                return (-1);
        }
        printf("Open %s OK\r\n", argv[1]);
        handle = fileno(fp);
        if (fstat(handle, &fileStat) < 0)
        {
                printf("ERROR: Read File Stat Error.\n");
                return -1;
        }
        file_size = fileStat.st_size;
        printf("file size = %d \n",file_size);

        file_buffer = malloc(file_size + 2);
        if (!file_buffer)
        {
                printf("ERROR: Allocate file buffer %d bytes failed!!\r\n", file_size+2);
                return -1;
        }

        if(fread(file_buffer, file_size, 1, fp) != 1 || ferror(fp))
        {
                free(file_buffer);
                fclose(fp);
                printf("ERROR: Read %s failed!!!\r\n", argv[1]);
                return -1;
        }
	file_buffer[file_size] = 0;
        fclose(fp);


	ptr = file_buffer;
	printf("%s\r\n", ptr);

	while (ptr != NULL)
	{	
		sscanf(ptr, "%s %s %s", szFileName, szFileType, szRGBorder);
		printf("File Name=%s, File Type=%s, RGB order=%s\r\n", szFileName, szFileType, szRGBorder);

		if (!strcmp(szFileName, "sleep"))
		{
			sleep(atoi(szFileType));
			ptr = strchr(ptr, '\n');

                	if (ptr != NULL)
                        	ptr++;
			continue;
		}

		if (!strcmp(szFileType, "VIF"))
			file_type = FILE_TYPE_VIF;
		else if (!strcmp(szFileType, "VGA"))
			file_type = FILE_TYPE_VGA;
	        else if (!strcmp(szFileType, "D1"))
                        file_type = FILE_TYPE_D1;

		if (!strcmp(szRGBorder, "RGB555"))
			RGBorder = RGB_ORDER_555;
		else if (!strcmp(szRGBorder, "RGB565"))
                        RGBorder = RGB_ORDER_565;
		else if (!strcmp(szRGBorder, "RGB888"))
                        RGBorder = RGB_ORDER_888;

		show_file(szFileName, file_type, RGBorder);

		//sleep(5);

		ptr = strchr(ptr, '\n');
		
		if (ptr != NULL)
			ptr++;		
	}
		
	close(fb_fd);
}
