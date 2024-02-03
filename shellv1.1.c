#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


/************************************************/
/*  Author  : ABDULLAH AYMAN                    */
/*  Date    : 3/2/2024  12:14AM                 */
/* topic    : Basic Shell concept               */
/* version  : 1.1                               */
/************************************************/
//------Code------//


int main (void)
{
	char* buffer = NULL;
	size_t n =10;
	while(1)
	{
		printf(":)");
		getline(&buffer,&n,stdin);
		printf("you said :%s\n",buffer);\
		//remove the newline character in the entered cmd
		buffer[strcspn(buffer,"\n")]='\0';
		//check if the entered string is exit
		if(strcmp(buffer , "exit") == 0)
		{
			printf(":( good bye\n");
			break;
		}
		
		
	}
	free(buffer);
	return 0;

}

//Prototypes
int pwd (int argc , char * argv[]);
int IS_REG(const char* Path);
int move (int argc , char* argv[]);
int echo(int argc, char *argv[]);

int main (void)
{
	while(1)
	{
		
	       	char* cmd=NULL,*cmd_cpy=NULL,*token=NULL;
                char* delim = " ";
       		size_t n = 0;
        	int input=0;
        	int argc = 0 , Local_Counter = 0;
        	char **argv=NULL;
		printf(":)");
		while (input =  getline(&cmd , &n,stdin) == 0 )
		{
			//do nothing
		}
		if(input == -1)
		{
			return -1;
		}
		//take a copy of the entered string command
		cmd_cpy = strdup(cmd);
		
		//tokenize the entered string 
		token = strtok(cmd , delim);
		// loop to fine how many tokens are in the entered cmd and store them in argc
		while (token)
		{
			token = strtok(NULL,delim);
			argc++;
		}
		//allocate memory for argv to hole the tokens
		argv = malloc(sizeof(char*)*argc);
		//loop to tokenize cmd_cpy and fill the memory of argv
		token = strtok(cmd_cpy,delim);

		while(token)
		{
			argv[Local_Counter] = token ;
			token = strtok(NULL,delim);
			Local_Counter++;
		}
		//set the last element of the argv array 
		argv[Local_Counter] = NULL ;
		// check what is the entered command
		/**********************************/
		//exit?
		if(strcmp(argv[0],"exit\n") == 0)
		{
			printf(":( good bye\n");
			free(argv);
                       	break;
		}
		else if(strcmp(argv[0],"mypwd\n") == 0)
                {
                	if(pwd (argc ,argv) != 0)
			{
				perror("Error in executing PWD");
				free(argv);
			}	
                }
		else if(strcmp(argv[0],"mymove\n") == 0)
                {
			if(move(argc ,argv) !=0)
			{
				perror("Error in moving File\n");
			}
					
               	}
		else if(strcmp(argv[0],"myecho\n") == 0)
                {
                        if(echo(argc ,argv) !=0)
                        {
                                perror("Error in echoing\n");
                        }

                }
		else
		{
			printf("Please insert a correct command\n");
		}

	free(argv);
	}
	
	return 0;

}







//built in commands
//
int pwd (int argc , char * argv[])

{
         char cwd[1024];
	 memset(cwd,0,sizeof(cwd));
        if(argc != 1)
        {
                fprintf (stderr,"Usage %s <directory>\n",argv[0]);
                return -1;
        }
        printf("current directory>> %s\n",getcwd(cwd,sizeof(cwd)));
        return 0;
}


int IS_REG(const char* Path)
{
        struct stat Path_Stat;
        stat(Path,&Path_Stat);
        return (S_ISREG(Path_Stat.st_mode));
}
int move (int argc , char* argv[])
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



int echo(int argc, char *argv[])

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
