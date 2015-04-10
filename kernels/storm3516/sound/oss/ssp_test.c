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
//#include <storm_ssp.h>
#include <linux/soundcard.h>	

#include "/source/kernel/linux/sound/oss/storm_ssp.h"

#include <errno.h>
#define MENU_NUM  10
#define SBUF_SIZE  (2048) //2048//1024 



// mknod /dev/sspi2s c 10 244
int main(int argc, char *argv[])
{
    int fd, fdx;
    FILE *fp;
    char imgPt[] = "/dev/dsp";
    char imgPtx[] = "/dev/mixer";
    char filename[] = "/mnt/ide3/public/test.wav";
    int i, inprog=1, err, j, k, outfd, *tmp=0, *tmpo=0, ret, timeout, ch,vol=0;
    unsigned int value;
    struct stat fileStat;
    int handle,num;
    char *imgBuff;
    int fileLen;
    //int ifunc, garbage;
    char ifunc, garbage;
    //unsigned char *buf = NULL, *obuf = NULL, *tbuf = NULL;
    char menu[][30] = {
    						{"0. Play test(volume)"},
    						{"1. Init cs4341"},
    						{"2. + level"},
    						{"3. - level"},
    						{"4. Play test"},
    						{"5. Set data format"},
    						{"6. Set stereo"},
    						{"7. Set speed"},
    						{"8. Set channel"},
    						{"Q. Exit"},

    						
    };
    
            printf("MESSAGE: Run SSP Program now...\n");
           usleep(10000);
         printf("open %s\n",imgPt);
        if( (fd = open(imgPt, O_SYNC|O_RDWR)) < 0)
        {
            printf("ERROR: Open I2S device error: \n");
            return -1;
        }
        
        // printf("open %s\n",imgPtx);
        //if( (fdx = open(imgPtx, O_SYNC|O_RDWR)) < 0)
        //{
        //    printf("ERROR: Open cs4341 error: \n");
        //    return -1;
        //}

		printf("MESSAGE: Open SLIC device successfully: \n");
  			
  		while(inprog)
  		{	
  			printf("\n\n ======================= SSP I2S Test =======================\n");

  			  
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
					ioctl( fd, SSP_I2S_INIT_BUF, NULL);
					if((fp = fopen(filename, "rb")) == NULL)
					{
						printf("open file error: %s\n",filename);
	 					break;
	 				}
	 				
	 				handle = fileno(fp);
        if (fstat(handle,&fileStat) < 0)
        { 
            printf("read file state error\n");
	 					break;
        }
        //Get file Length
        fileLen = fileStat.st_size;
        printf("fileLen = %d (0x%x)\n",fileLen,fileLen);
        
        ioctl(fd, SSP_I2S_FILE_LEN, &fileLen);
        
        imgBuff = malloc(SBUF_SIZE); //malloc(fileLen+2);
    		if (! imgBuff)
    		{      
        	printf("imgBuff buffer alloc error.\n");
	 					break;
    		}

				fseek(fp,0,0);
     		
     		i = fileLen / SBUF_SIZE;
     		j = fileLen % SBUF_SIZE;
     		printf("I2S test start --> i:%d  j:%d\n",i,j);
     		for(k=0;k<i;k++)
     		{
     			memset(imgBuff, 0x0 ,SBUF_SIZE);
     		   fseek(fp,k*SBUF_SIZE,SEEK_SET); //SEEK_SET =0 //beginning of file
     		   fread(imgBuff,SBUF_SIZE,1,fp);     
     		   if((k%100)==0)
     		   {  
     		   	if(vol<30)
     		   		ioctl( fd, SSP_I2S_INC_LEVEL, NULL);   
     		   	else if(vol>30)
     		   			ioctl( fd, SSP_I2S_DEC_LEVEL, NULL);   
     		   			vol++;
     		   			if(vol>60)
     		   				vol = 0;
     		   }
     		   
     		   
     		   
wt_again:     		   			
     		   			err = write (fd,imgBuff,SBUF_SIZE);
	 							if (err < 0)
	 							{
									printf("write err !!\n");
									break;
	 							}
	 						//	printf("len = %d\n",err);
	 							if( err != SBUF_SIZE)
	 							{
	 								//printf("no empty buffer !!\n");
	 								
	 								goto wt_again;
	 							}
	 							//printf(".");
     		}
     		if(j!=0)
     		{
     				memset(imgBuff, 0x0 ,SBUF_SIZE);
     		   	fseek(fp,k*SBUF_SIZE,SEEK_SET); //SEEK_SET =0 //beginning of file
     		   	fread(imgBuff,j,1,fp);          
wt_again1:     		   			
     		   			err = write (fd,imgBuff,SBUF_SIZE);
	 							if (err < 0)
	 							{
									printf("write err !!\n");
									break;
	 							}
	 							if( err != SBUF_SIZE)
	 							{
	 								//printf("no empty buffer !!\n");
	 								goto wt_again1;
	 							}
	 							//printf("*");
     			
     		}
     		printf("\nI2S test end <--\n");
     		ioctl( fd, SSP_I2S_STOP_DMA, NULL);
     		
//Read file to buffer               
        
/*
名　稱：fseek
語　法：int fseek(int fp, int offset);
傳回值：整數
簡　介：移動檔案指標。
種　類：檔案存取

本函式將檔案 fp 的指標移到指定的偏移位元 (offset) 上。使用本函式就像 C 語言中的 fseek(fp, offset, SEEK_SET) 函式。成功則傳回 0，失敗則傳回 -1 值。當 fp 由 fopen() 開啟 "http://...." 或是 "ftp://...." 等 URL 檔案時，本函式無法作用。


--------------------------------------------------------------------------------

名　稱：ftell
語　法：int ftell(int fp);
傳回值：整數
簡　介：取得檔案讀寫指標位置。
種　類：檔案存取

本函式傳回檔案 fp 的指標偏移位元 (offset) 值。當發生錯誤時，傳回 false 值。檔案指標 fp 必須是有效的，且使用 fopen() 或者 popen() 二個函式開啟方可作用。
*/        
				printf("close file ctrl \n");
        fclose(fp);  
 						 							
					break;

				case '1':
					printf(" 1. Init cs4341\n");
					ioctl( fd, SSP_I2S_INIT_MIXER, NULL);
					break;
					
				case '2':
					printf(" 2. + level\n");
					ioctl( fd, SSP_I2S_INC_LEVEL, NULL);
					break;
					
				case '3':
					printf(" 3. - level\n");
					ioctl( fd, SSP_I2S_DEC_LEVEL, NULL);
					break;
					
				case '4':
					ioctl( fd, SSP_I2S_INIT_BUF, NULL);
					if((fp = fopen(filename, "rb")) == NULL)
					{
						printf("open file error: %s\n",filename);
	 					break;
	 				}
	 				
	 				handle = fileno(fp);
        if (fstat(handle,&fileStat) < 0)
        { 
            printf("read file state error\n");
	 					break;
        }
        //Get file Length
        fileLen = fileStat.st_size;
        printf("fileLen = %d (0x%x)\n",fileLen,fileLen);
        
        ioctl(fd, SSP_I2S_FILE_LEN, &fileLen);
        
        imgBuff = malloc(SBUF_SIZE); //malloc(fileLen+2);
    		if (! imgBuff)
    		{      
        	printf("imgBuff buffer alloc error.\n");
	 					break;
    		}

				fseek(fp,0,0);
     		
     		i = fileLen / SBUF_SIZE;
     		j = fileLen % SBUF_SIZE;
     		printf("I2S test start --> i:%d  j:%d\n",i,j);
     		for(k=0;k<i;k++)
     		{
     			memset(imgBuff, 0x0 ,SBUF_SIZE);
     		   fseek(fp,k*SBUF_SIZE,SEEK_SET); //SEEK_SET =0 //beginning of file
     		   fread(imgBuff,SBUF_SIZE,1,fp);     
  		   
     		   
wt_again4:     		   			
     		   			err = write (fd,imgBuff,SBUF_SIZE);
	 							if (err < 0)
	 							{
									printf("write err !!\n");
									break;
	 							}
	 						//	printf("len = %d\n",err);
	 							if( err != SBUF_SIZE)
	 							{
	 								//printf("no empty buffer !!\n");
	 								
	 								goto wt_again4;
	 							}
	 							//printf(".");
     		}
     		if(j!=0)
     		{
     				memset(imgBuff, 0x0 ,SBUF_SIZE);
     		   	fseek(fp,k*SBUF_SIZE,SEEK_SET); //SEEK_SET =0 //beginning of file
     		   	fread(imgBuff,j,1,fp);          
wt_again41:     		   			
     		   			err = write (fd,imgBuff,SBUF_SIZE);
	 							if (err < 0)
	 							{
									printf("write err !!\n");
									break;
	 							}
	 							if( err != SBUF_SIZE)
	 							{
	 								//printf("no empty buffer !!\n");
	 								goto wt_again41;
	 							}
	 							//printf("*");
     			
     		}
     		printf("\nI2S test end <--\n");
     		ioctl( fd, SSP_I2S_STOP_DMA, NULL);
     		
//Read file to buffer               
        
/*
名　稱：fseek
語　法：int fseek(int fp, int offset);
傳回值：整數
簡　介：移動檔案指標。
種　類：檔案存取

本函式將檔案 fp 的指標移到指定的偏移位元 (offset) 上。使用本函式就像 C 語言中的 fseek(fp, offset, SEEK_SET) 函式。成功則傳回 0，失敗則傳回 -1 值。當 fp 由 fopen() 開啟 "http://...." 或是 "ftp://...." 等 URL 檔案時，本函式無法作用。


--------------------------------------------------------------------------------

名　稱：ftell
語　法：int ftell(int fp);
傳回值：整數
簡　介：取得檔案讀寫指標位置。
種　類：檔案存取

本函式傳回檔案 fp 的指標偏移位元 (offset) 值。當發生錯誤時，傳回 false 值。檔案指標 fp 必須是有效的，且使用 fopen() 或者 popen() 二個函式開啟方可作用。
*/        
				printf("close file ctrl \n");
        fclose(fp);  
 						 							
					break;
					
				case '5':
					printf(" 5. Set data format\n");
					printf("SSP_DF_16BITB_LINEAR : 0\n");
					printf("SSP_DF_8BIT_ULAW : 1\n");
					printf("SSP_DF_8BIT_ALAW : 2\n");
					printf("SSP_DF_16BITL_LINEAR : 3\n");
					do {
						printf("Please input:");
						scanf("%d",&num);
						scanf("%c", &garbage);

						} while ((num < 0) && (num > 3));

					ioctl( fd, SSP_I2S_SETFMT, &num);
					break;
					
				case '6':
					printf(" 6. Set stereo(0 or 1)\n");

					do {
						printf("Please input:");
						scanf("%d",&num);
						scanf("%c", &garbage);

						} while ((num != 0) && (num != 1));

					ioctl( fd, SSP_I2S_STEREO, &num);
				break;
				case '7':
					printf(" 7. Set speed\n");
					printf("44KHZ : 0\n");
					printf("22KHZ : 1\n");
					printf("48KHZ : 2\n");
					printf("24KHZ : 3\n");
					do {
						printf("Please input:");
						scanf("%d",&num);
						scanf("%c", &garbage);

						} while ((num < 0) && (num > 3));

					ioctl( fd, SSP_I2S_SETSPEED, &num);
					break;
				
				case '8':
					printf(" 8. Set channel(1 or 2)\n");
					printf("MONO : 1\n");
					printf("STEREO : 2\n");
					do {
						printf("Please input:");
						scanf("%d",&num);
						scanf("%c", &garbage);

						} while ((num != 2) && (num != 1));

					ioctl( fd, SSP_I2S_SETCHANNELS, &num);
					break;
 	
				case 'Q':
					printf(" Q. Exit\n");
					inprog = 0;
					ioctl( fd, SSP_I2S_STOP_DMA, NULL);
					break;
				default:
					printf("Out of Range !!\n");
				
						}//switch...
	  		
      	}//while...

				printf("close phone dev  !!\n");
      	close(fd);  
      	//close(fdx);    

        printf("MESSAGE: Exit SLIC test program!!\n\n");
          usleep(10000); 
    return 0;
}
