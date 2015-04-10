/* vi: set sw=4 ts=4: */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dtrace.h>
#include <signal.h>

extern int bt_main(int argc, char * argv[], char * env[]);

static void quit_signal(int sig)
{
	if (sig!=SIGTERM) exit(0);
}

int main(int argc, char * argv[], char * env[])
{
	char * base;
	int ret = 1;
	
	base = strrchr(argv[0], '/');
	if (base) base = base + 1;
	else base = argv[0];
		
	signal (SIGINT,  quit_signal);
	signal (SIGTERM, quit_signal);
	signal (SIGQUIT, quit_signal);
	
	if (strcmp(base, "btgi")==0)		
		ret = bt_main(argc, argv, env); 
	else
		printf("BT, unknown command %s\n", base);
		
	return ret;
}
