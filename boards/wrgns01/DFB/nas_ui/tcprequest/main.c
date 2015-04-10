#include <stdio.h>
#include "webtcpreq.h"


int main(int argc, char *argv[])
{	
	int flag=0;
		
	flag=web_tcpreq(argv[1], argv[2], argv[3]);			
	if(flag==1) printf("1\n");
	else printf("0\n");
	return 1;
}
