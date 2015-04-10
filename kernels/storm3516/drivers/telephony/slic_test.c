#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <syslog.h>

#include <termios.h>
#include <unistd.h>
#include <assert.h>

                              
//#include <linux/telephony/gemini.h>
//#include <linux/telephony/proslic.h>
//#include </home/middle/lepus/source/kernel/linux/include/linux/telephony.h>
#include <linux/telephony.h>
//#include "g72x.h"
#include <errno.h>

//#include "gemini_ssp.h"
#include </source/kernel/linux/include/asm/arch/gemini_ssp.h>

#define MENU_NUM  15
//#define SBUF_SIZE  180 //0xff0 //2560
//#define NUMBER_OF_CHAN	1

//extern int encode(unsigned char codec, unsigned int in_coding, unsigned char *in_buf, unsigned int ilen, unsigned char *out_buf, unsigned int *olen);
//extern int decode(unsigned char codec, unsigned int out_coding, unsigned char *in_buf, unsigned int ilen, unsigned char *out_buf, unsigned int *olen);

/*------------------------------------------------*/
int mygetch(void) {      
	int c=0;      
	struct termios org_opts, new_opts;      
	int res=0;          
	//-----  store old settings -----------      
	res=tcgetattr(STDIN_FILENO, &org_opts);      
	assert(res==0);          
	//---- set new terminal parms --------      
	memcpy(&new_opts, &org_opts, sizeof(new_opts));      
	new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);      
	tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);      
	c=getchar();          
	//------  restore old settings ---------      
	res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);      
	assert(res==0);      
	return(c);
}

// mknod /dev/phone0 c 100 0
int main(int argc, char *argv[])
{
    int fd,fd1;
    FILE *fp;
    char imgPt[] = "/dev/phone0";
    char imgPt1[] = "/dev/phone1";
    char filename[] = "slic_file";
    int i, inprog=1, err, j, k, outfd, *tmp=0, *tmpo=0, ret, timeout, ch, num;
    unsigned int value;
    //int ifunc, garbage;
    char ifunc, garbage;
    //unsigned char *buf = NULL, *obuf = NULL, *tbuf = NULL;
    unsigned char buf[SBUF_SIZE], obuf[SBUF_SIZE], tbuf[SBUF_SIZE], tobuf[SBUF_SIZE];
    char menu[][30] = {
    						{"0. Busy Tone"},
    						{"1. Ring Back Tone"},
    						{"2. OFF HOOK Tone"},
    						{"3. Congestion Tone"},
    						{"4. Ringing"},
    						{"5. Stop Ringing"},
    						{"6. Stop Tone"},
    						{"7. Hook States"},
    						{"8. Get Linefeed states"},
    						{"9. Set Linefeed states"},
    						{"a. Test phone transation"},
    						{"b. Test phone DTMF"},
    						{"c. Test two phone transation"},
    						{"d. Stop phone transation"},
    						{"Q. Exit"},

    						
    };
    
            printf("MESSAGE: Run SSP Program now...\n");
           usleep(10000);
         
        if( (fd = open(imgPt, O_SYNC|O_RDWR)) < 0)
        {
            printf("ERROR: Open SLIC device error: phone0\n");
            //return -1;
        }
        value = DMA_DEMO;
        ioctl( fd, SSP_SLIC_SET_MODE, &value);
        if(NUMBER_OF_CHAN>1)
        {
        		if( (fd1 = open(imgPt1, O_SYNC|O_RDWR)) < 0)
        		{
        		    printf("ERROR: Open SLIC device error: phone1\n");
        		    //return -1;
        		}
        		value = DMA_DEMO;
       			ioctl( fd1, SSP_SLIC_SET_MODE, &value);
        	
        }

		printf("MESSAGE: Open SLIC device successfully: \n");
  			
  		while(inprog)
  		{	
  			
  			printf("\n\n ======================= SSP Test =======================\n");
  		//	  printf(" 1. Busy Tone\n");
  		//	  printf(" 2. Ring Back Tone\n");
  		//	  printf(" 3. OFF HOOK Tone\n");
  		//	  printf(" 4. Congestion Tone\n");
  		//	  printf(" 5. Ringing\n");
  		//	  printf(" 6. Stop Ringing\n");
  		//	  printf(" 7. Stop Tone\n");
  		//	  printf(" 9. Exit\n");
  		//	  //printf(" 6. Dump SSP Registers\n");
  		//	  printf("===> ");
  		//	  scanf("%d",&ifunc);
  			  
  			for(i=0;i<(MENU_NUM/2);i++)  
  			{
  				printf("%-30s        %-30s\n", &menu[2*i][0],&menu[2*i+1][0]);
  			}
  			if(MENU_NUM%2)
  				printf("%-30s        \n", &menu[MENU_NUM-1][0]);
  			  //ifunc = getchar();
			//printf("--> %d \n",ifunc);
			do {
				printf("===>");
  			  scanf("%c",&ifunc);
  			  //printf("><%c\n",ifunc);
  			  scanf("%c", &garbage);
		      if (garbage != '\n')
		      	continue;
			} while (((ifunc < '0') || (ifunc > '9')) && 
			 ((ifunc < 'a') || (ifunc > 'z')) &&
			 ((ifunc < 'A') || (ifunc > 'Z')));
			
			switch(ifunc)
			{
				case '0':
					do {
						printf("Please input phone:");
						scanf("%d",&num);
						scanf("%c", &garbage);
						} while ((num != 0) && (num != 1));
					printf(" 0. Phone%d Busy Tone\n",num);
					if(num==0)
						ioctl( fd, SSP_GEN_BUSY_TONE, NULL);
					else
						ioctl( fd1, SSP_GEN_BUSY_TONE, NULL);
					break;
				case '1':
					do {
						printf("Please input phone:");
						scanf("%d",&num);
						scanf("%c", &garbage);

						} while ((num != 0) && (num != 1));
					printf(" 1. Phone%d Ring Back Tone\n",num);
					if(num==0)
						ioctl( fd, SSP_GEN_RINGBACK_TONE, NULL);
					else
						ioctl( fd1, SSP_GEN_RINGBACK_TONE, NULL);
					break;
				case '2':
					do {
						printf("Please input phone:");
						scanf("%d",&num);
						scanf("%c", &garbage);

						} while ((num != 0) && (num != 1));
					printf(" 2. Phone%d OFF HOOK Tone\n",num);
					if(num==0)
						ioctl( fd, SSP_GEN_OFFHOOK_TONE, NULL);
					else
						ioctl( fd1, SSP_GEN_OFFHOOK_TONE, NULL);
					break;
				case '3':
					do {
						printf("Please input phone:");
						scanf("%d",&num);
						scanf("%c", &garbage);

						} while ((num != 0) && (num != 1));
					printf(" 3. Phone%d Congestion Tone\n",num);
					if(num==0)
						ioctl( fd, SSP_GEN_CONGESTION_TONE, NULL);
					else
						ioctl( fd1, SSP_GEN_CONGESTION_TONE, NULL);
					break;
				case '4':
					do {
						printf("Please input phone:");
						scanf("%d",&num);
						scanf("%c", &garbage);

						} while ((num != 0) && (num != 1));
					printf(" 4. Phone%d Ringing\n",num);
					if(num==0)
						ioctl( fd, SSP_PHONE_RING_START, NULL);
					else
						ioctl( fd1, SSP_PHONE_RING_START, NULL);
					break;
				case '5':
					do {
						printf("Please input phone:");
						scanf("%d",&num);
						scanf("%c", &garbage);

						} while ((num != 0) && (num != 1));
					printf(" 5. Phone%d Stop Ringing\n",num);
					if(num==0)
						ioctl( fd, SSP_PHONE_RING_STOP, NULL);
					else
						ioctl( fd1, SSP_PHONE_RING_STOP, NULL);
					break;
				case '6':
					do {
						printf("Please input phone:");
						scanf("%d",&num);
						scanf("%c", &garbage);
						} while ((num != 0) && (num != 1));
					printf(" 6. Phone%d Stop Tone\n",num);
					if(num==0)
						ioctl( fd, SSP_DISABLE_DIALTONE, NULL);
					else
						ioctl( fd1, SSP_DISABLE_DIALTONE, NULL);
					break;
				case '7':
					do {
						printf("Please input phone:");
						scanf("%d",&num);
						scanf("%c", &garbage);

						} while ((num != 0) && (num != 1));
					printf(" 7. Phone%d Hook states\n",num);
					value = 0;
					if(num==0)
						ioctl( fd, SSP_GET_HOOK_STATUS, &value);
					else
						ioctl( fd1, SSP_GET_HOOK_STATUS, &value);
						
					if(value==0)
						printf("    ----> Phone%d Off Hook.\n",num);
					else
						printf("    ----> Phone%d On Hook.\n",num);
					break;	
				case '8':
					do {
						printf("Please input phone:");
						scanf("%d",&num);
						scanf("%c", &garbage);

						} while ((num != 0) && (num != 1));
					printf(" 8. Phone%d Get Linefeed states\n",num);
	//0x00	Open
	//0x11	Forward active
	//0x22	Forward on-hook transmission
	//0x33	TIP open
	//0x44	Ringing
	//0x55	Reverse active
	//0x66	Reverse on-hook transmission
	//0x77	RING open
					value = 0;
					if(num==0)
						ioctl( fd, SSP_GET_LINEFEED, &value);
					else
						ioctl( fd1, SSP_GET_LINEFEED, &value);
						
					printf("Linefeed : 0x%x\n",value);
						if(value&0x0f==0)
							printf("Linefeed : Open\n");
						else if(value&0x0f==1)
							printf("Linefeed : Forward active\n");
						else if(value&0x0f==2)
							printf("Linefeed : Forward on-hook transmissio\n");
						else if(value&0x0f==3)
							printf("Linefeed : TIP open\n");
						else if(value&0x0f==4)
							printf("Linefeed : Ringing\n");
						else if(value&0x0f==5)
							printf("Linefeed : Reverse active\n");
						else if(value&0x0f==6)
							printf("Linefeed : Reverse on-hook transmission\n");
						else if(value&0x0f==7)
							printf("Linefeed : RING open\n");
						else
								printf("Linefeed : out of range!!\n");
					
					break;	
				case '9':
					do {
						printf("Please input phone:");
						scanf("%d",&num);
						scanf("%c", &garbage);

						} while ((num != 0) && (num != 1));
					printf(" 9. Phone%d Set Linefeed states\n",num);
					value=0;
					printf("Linefeed = ");
  			  		scanf("%d",&value);
  			  if(num==0)
						ioctl( fd, SSP_SET_LINEFEED, &value);
					else
						ioctl( fd1, SSP_SET_LINEFEED, &value);
					break;
				case 'a':
					do {
						printf("Please input phone:");
						scanf("%d",&num);
						scanf("%c", &garbage);

						} while ((num != 0) && (num != 1));
					printf(" a. Phone%d Test phone transation\n", num);
					value = 1;
					if(num==0)
					{
						ioctl( fd, SSP_SLIC_SET_LINKSTATE, &value);
						ioctl( fd, SSP_SLIC_DMA_TEST, NULL);
					}
					else
	 				{
						ioctl( fd1, SSP_SLIC_SET_LINKSTATE, &value);
						ioctl( fd1, SSP_SLIC_DMA_TEST, NULL);
					}
					
	 				printf("phone%d start R/W  !!\n",num);
					i=0;
					
					timeout = 100*(8192/SBUF_SIZE);
					ch = 1;
					while(1){//(i<timeout){//((ch !='q') && (ch != '\n')){//((ch = getchar())!='q') && (ch != '\n')){ //q 0x71//(i<timeout)
							//printf("read !!\n");
							if(num==0)
	 							err = read (fd,buf,SBUF_SIZE);
	 						else
	 							err = read (fd1,buf,SBUF_SIZE);
	 							
   							if (err < 0)
	 							{
									printf("read err !!\n");
									break;
	 							}
#if 1	 							
							//for(i=0;i<SBUF_SIZE;i+=2)
							//{
							//	*(obuf+i) = *(buf+i+1);
							//	*(obuf+i+1) = *(buf+i);
							//}
	 						if(num==0)
	 							err = write (fd,buf,SBUF_SIZE);
	 						else
	 							err = write (fd1,buf,SBUF_SIZE);
	 							if (err < 0)
	 							{
									printf("write err !!\n");
									break;
	 							}
#else
							if(num==0)
	 							err = write (fd,buf,SBUF_SIZE);
	 						else
	 						{
	 							for(i=0;i<SBUF_SIZE;i+=2)
								{
									*(obuf+i) = *(buf+i+1);
									*(obuf+i+1) = *(buf+i);
								}
	 							err = write (fd1,obuf,SBUF_SIZE);
	 						}
	 							if (err < 0)
	 							{
									printf("write err !!\n");
									break;
	 							}
#endif	 							

	 					i++;
	 					
	 				};
	 				printf("end R/W  !!\n");
	 				value = 0;
					if(num==0)
					{
						ioctl( fd, SSP_SLIC_SET_LINKSTATE, &value);
						ioctl( fd, SSP_SLIC_STOP_DMA, NULL);
					}
					else
	 				{
						ioctl( fd1, SSP_SLIC_SET_LINKSTATE, &value);
						ioctl( fd1, SSP_SLIC_STOP_DMA, NULL);
					}
	 				//free (buf);
	 				//free (obuf);
	 				//free (tbuf);
	 				//printf("end free buffer  !!\n");
	 				
					break;
				case 'b':
					do {
						printf("Please input phone:");
						scanf("%d",&num);
						scanf("%c", &garbage);

						} while ((num != 0) && (num != 1));
					printf(" b. Phone%d Test phone DTMF\n",num);
					if(num==0)
						ioctl( fd, SSP_SLIC_DTMFACTION_TEST, NULL);
					else
						ioctl( fd1, SSP_SLIC_DTMFACTION_TEST, NULL);
					break;
				
				case 'c':
					if(NUMBER_OF_CHAN > 1)
					{
							printf(" c. Two Phone Test phone transation\n");
							value = 1;
							num = NUMBER_OF_CHAN;
						ioctl( fd, SSP_SLIC_SET_LINKSTATE, &value);
						ioctl( fd, SSP_SLIC_DMA_TEST, NULL);

						ioctl( fd1, SSP_SLIC_SET_LINKSTATE, &value);
						ioctl( fd1, SSP_SLIC_DMA_TEST, NULL);

					
	 				printf("(%d)start R/W  !!\n",num);
					i=0;
					
					timeout = 100*(8192/SBUF_SIZE);
					ch = 1;
					while(1){//i<timeout){//((ch !='q') && (ch != '\n')){//((ch = getchar())!='q') && (ch != '\n')){ //q 0x71//(i<timeout)
							//printf("read !!\n");
								//memset(buf,0x0,SBUF_SIZE);
								//memset(obuf,0x0,SBUF_SIZE);
	 							err = read (fd,buf,SBUF_SIZE);
								if (err < 0)
	 							{
									printf("read err !!\n");
									break;
	 							}
	 							//for(i=0;i<SBUF_SIZE;i+=2)
								//{
								//	*(obuf+i) = *(buf+i+1);
								//	*(obuf+i+1) = *(buf+i);
								//}

	 							err = write (fd1,buf,SBUF_SIZE);
	 							if (err < 0)
	 							{
									printf("write err !!\n");
									break;
	 							}
	 							///////////////////
	 							//memset(buf,0x0,SBUF_SIZE);
	 							err = read (fd1,tbuf,SBUF_SIZE);
	 							
   							if (err < 0)
	 							{
									printf("read err !!\n");
									break;
	 							}
								//memset(obuf,0x0,SBUF_SIZE);
								//for(i=0;i<SBUF_SIZE;i+=2)
								//{
								//	*(tobuf+i) = *(tbuf+i+1);
								//	*(tobuf+i+1) = *(tbuf+i);
								//}
	 							err = write (fd,tbuf,SBUF_SIZE);
	 							if (err < 0)
	 							{
									printf("write err !!\n");
									break;
	 							}

	 					i++;
	 					
	 				};
	 				printf("end R/W  !!\n");
	 				value = 0;

						ioctl( fd, SSP_SLIC_SET_LINKSTATE, &value);
						ioctl( fd, SSP_SLIC_STOP_DMA, NULL);

						ioctl( fd1, SSP_SLIC_SET_LINKSTATE, &value);
						ioctl( fd1, SSP_SLIC_STOP_DMA, NULL);

	 				}
					break;
					
				case 'd':
					printf("Stop phone transation");
					
					value = 0;
						ioctl( fd, SSP_SLIC_SET_LINKSTATE, &value);
						ioctl( fd, SSP_SLIC_STOP_DMA, NULL);
					if(NUMBER_OF_CHAN>1)
					{
						ioctl( fd1, SSP_SLIC_SET_LINKSTATE, &value);
						ioctl( fd1, SSP_SLIC_STOP_DMA, NULL);
					
					}
					
					break;
					
				case 'Q':
					printf(" Q. Exit\n");
					inprog = 0;
					ioctl( fd, SSP_DISABLE_DIALTONE, NULL);
					ioctl( fd, SSP_PHONE_RING_STOP, NULL);
					if(NUMBER_OF_CHAN>1)
					{
						ioctl( fd1, SSP_DISABLE_DIALTONE, NULL);
						ioctl( fd1, SSP_PHONE_RING_STOP, NULL);
					}
					break;
				default:
					printf("Out of Range !!\n");
				
			}//switch...
	  		
      	}//while...

				printf("close phone dev  !!\n");
      	close(fd); 
      	if(NUMBER_OF_CHAN>1)     
      		close(fd1); 

        printf("MESSAGE: Exit SLIC test program!!\n\n");
          usleep(10000); 
    return 0;
}
