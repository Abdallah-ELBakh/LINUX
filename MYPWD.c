#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

int main (int argc , char * argv[])

{
        char cwd[1024];
        if(argc != 1)
        {
                fprintf (stderr,"Usage %s <directory>\n",argv[0]);
                return -1;
        }
        printf("current directory>> %s\n",getcwd(cwd,sizeof(cwd)));
        return 0;
}

