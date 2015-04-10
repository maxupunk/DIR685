/* vi: set sw=4 ts=4: */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/resource.h>
#include <errno.h>
#include <limits.h> 
#include <sys/types.h>
#include <unistd.h>

extern int bt_main(int argc, char * argv[], char * env[]);

int set_RLIMIT_AS(int size_M)
{
	struct rlimit r;
    r.rlim_cur = size_M*1024*1024;
	r.rlim_max = size_M*1024*1024;
	if (setrlimit(RLIMIT_AS,&r)<0)
    {
         fprintf(stderr,"setrlimit error\n");
         return -1;
    }
/*
	if(getrlimit(RLIMIT_AS,&r)<0)
    {
         fprintf(stderr,"getrlimit error\n");
         return -1;
    }
	printf("RLIMIT_AS cur:%d\n",r.rlim_cur);
    printf("RLIMIT_AS max:%d\n",r.rlim_max);
*/    
	return 0;
}


int main(int argc, char * argv[])
{
	int mem_limit_M;
	int pid;
	if(argc < 2)
	{
		printf("Usage: memctl mem_size_in_Mbytes application app_argv\n");
		return 0;
	}	
	mem_limit_M = atoi(argv[1]);
	if(mem_limit_M < 1 || mem_limit_M > 100)
	{
		printf("Usage: memctl mem_size_in_Mbytes application app_argv (mem_limit_M : 1 ~ 100 M)\n");
		return 0;
	}	
	set_RLIMIT_AS(mem_limit_M);
	printf("%s control vmmemory at %d M\n",argv[2],mem_limit_M);

	//pid=fork();
	
	//if(pid==0)
	{
		execvp(argv[2],&argv[2]);
		printf("never here!!\n");
		return 0;
	}
	//return 0;
}
