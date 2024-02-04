#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>


int main (int argc, char *argv[])

{
	int LocalCounter = 1;
	while(argv[LocalCounter])
	{
		printf("%s ",argv[LocalCounter]);
		LocalCounter++;
	}
	printf("\n");
	return 0 ;
}
