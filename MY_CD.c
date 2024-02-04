#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>


int main (int argc , char * argv[])

{
	char cwd[1024];
	if(argc != 2)
	{
		fprintf (stderr,"Usage %s <directory>\n",argv[0]);
		return -1;	
	}
	printf("curretn directory %s\n",getcwd(cwd,sizeof(cwd)));
	if(chdir(argv[1]) != 0)
	{
		printf("Couldn't change directory");
		return -1;
	}
	printf("curretn directory %s\n",getcwd(cwd,sizeof(cwd)));
	return 0;
}
