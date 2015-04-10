#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>
#include "fcrss_parser.h"

pthread_mutex_t p_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t p_cond = PTHREAD_COND_INITIALIZER;
int count=0;

void *do_gethostbyname_r(void *arg)
{
	pthread_detach(pthread_self());
	struct hostent *host;	
	
	if((host = gethostbyname(arg))==NULL)
	{										
		pthread_exit(NULL);		
		return 0;		
	}				
	
	count++;						
	pthread_cond_signal(&p_cond);			
	pthread_exit(NULL);
}	

int main(int argc, char *argv[])   
{	
	pthread_t tid;
	int flag;		
	struct timespec ts;
	
	ts.tv_sec=time(NULL)+5;		
	pthread_create(&tid, NULL, do_gethostbyname_r, argv[1]);					
	pthread_mutex_lock(&p_mutex);			
	pthread_cond_timedwait(&p_cond, &p_mutex, &ts);		
	pthread_mutex_unlock(&p_mutex);			
	flag=pthread_cancel(tid);
	if(count==0) printf("fail\n");
	else printf("ok\n");	
	return 1;			
}