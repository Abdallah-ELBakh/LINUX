#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
int IS_REG(const char* Path)
{
	struct stat Path_Stat;
	stat(Path,&Path_Stat);
	return (S_ISREG(Path_Stat.st_mode));
}
int main (int argc , char* argv[])
{
	char* SRC_Path=NULL;
	char* DEST_Path = NULL;

	if (argc != 3)
	{
		printf("Too few Arguments , Usage : %s <src path> <dest path> \n",argv[0]);
		return -1;
	}
	SRC_Path= argv[1];
	DEST_Path=argv[2];
	if( IS_REG(SRC_Path) == IS_REG(DEST_Path) )
	{
		printf("Paths types are identical\n");

		if(IS_REG(SRC_Path) !=0)
		{
			if(rename(SRC_Path,DEST_Path) != 0)
			{
				printf("Error moving File\n");
				return -1;
			}
			printf("file was Moved successfully\n");
		}
		else
		{
			if(rename(SRC_Path,DEST_Path) != 0)
                        {
                                printf("Error moving Directory\n");
				return -1;
                        }
			printf("Directory was Moved Successfully\n");
		}
		return 0;
	}
	else
	{
		perror("Both paths must refer to the same type either both files or directories\n");
		return -1;
	}
	

}

