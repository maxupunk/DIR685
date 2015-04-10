#include <stdio.h>
#include <linux/input.h>
#include <fcntl.h>
typedef struct input_event Myinputevent;
#define DEVICE "/dev/input/"

int main(int argc, char **argv)
{
	int i, n; int fd;
    unsigned char data[8];
    Myinputevent event;
	char DEVICENAME[100];
	sprintf(DEVICENAME,"%s%s",DEVICE,argv[1]);
	
    fd = open( DEVICENAME , O_RDONLY, 0); 
    if (fd < 0)
    { 
    	perror("Can't open device...\n");
	    exit(1);
     } 
     while(1)
	 {    
	 	printf("Watting event ...\n\n\n");
        n = read(fd, &event, sizeof(Myinputevent) );
      //  if ( n != 16 )
       //    	perror(" Read data error! "); exit(1); 
     //   if(event.type == EV_KEY)
        { 
        	printf("@marco@key, the code is : %d \n",event.code);
		    if(event.value)  
		    	printf("    Press down.\n");    
		    else  printf("    Press up.\n");
        } 
    }
}    
