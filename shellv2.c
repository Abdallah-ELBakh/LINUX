#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>


#define MAX_TOKENS 100
#define MAX_TOKEN_LEN 100
typedef enum {
    NOCMD=0,
    MYECHO,
    MYMOVE,
    MYPWD,
    MYCD,
    MYEXIT,
	CLEAR,
    EXTERNAL
} CMD_t;

////////////////////////////////////////////////////////////////////
int echo(int argc, char *argv[]);                                 //
char** tokenize_and_parse(char *input, CMD_t* CMD ,int* result);  //
void EXECUTER(char** argv , char* PATH);                          //
/////////////////////////////////////////////////////////////////

int main(void)
{
	CMD_t CMD;
        size_t n = 25;
	char* cmd=NULL;
        int input=0;
	int result=0;
	char** tokens =NULL;
	while(1)
	{
		CMD = 0;
		input = 0;
		n=25;
		cmd =NULL;
		tokens = NULL;
		printf(":)");
                while (1)
                {
			input = getline(&cmd , &n,stdin);
			if(input == -1)
			{
				free(cmd);
				return -1;
			}else if(input == 0)
			{
				continue;	
			}
			else
			{
				break;
			}
                        
                }
		tokens=	tokenize_and_parse(cmd,&CMD,&result);
		//printf("CMD_ID :%d\n",CMD);
		free(cmd);
		
		switch(CMD)
		{
			case MYECHO:
           		//	echo(result,tokens);
				for(int i =1 ; i<result ; i++)
				{
					printf("%s ",tokens[i]);
				}
					printf("\n");
            			break;
        	case MYPWD:
            	//printf("mypwd command\n");
				char cwd[1024];
        		if(result != 1)
        		{
                fprintf (stderr,"Usage %s <directory>\n",tokens[0]);
                break;
        		}
        		printf("current directory>> %s\n",getcwd(cwd,sizeof(cwd)));
            	break;
        	case MYCD:
    			//printf(":)mycd command\n");
				char cwd2[1024];
				if(result != 2)
				{
					fprintf (stderr,":( Usage %s <directory>\n",tokens[0]);
					break;	
				}
				printf(":)OLD directory %s\n",getcwd(cwd2,sizeof(cwd2)));
				if(chdir(tokens[1]) != 0)
				{
					printf(":(Couldn't change directory");
					break;
				}
				printf(":)NEW directory %s\n",getcwd(cwd2,sizeof(cwd2)));
    			break;
        	case MYEXIT:
            	printf("\n:( Good Bye\n");
				return 0;
            	break;
			case EXTERNAL:
				__pid_t pid = fork();
				if(pid == 0)
				{
					//child process
					execvp(tokens[0],tokens);
					// if execvp fails 
					perror("Execution failed");
					exit(EXIT_FAILURE);
				}else if(pid < 0)
				{
					perror("Fork Failed");
				}
				else 
				{
					//parent process
					int status;
					waitpid(pid,&status,0);
				}
                break;
			case CLEAR:
				system("clear");
				break;
        	default:
            	printf("Unknown command\n");
            	break;


		}
		free(tokens);

	}
	free(tokens);
	return 0;
}

char** tokenize_and_parse(char *input, CMD_t* CMD,int* num) 
{
    char *token;
    char *input_copy = strdup(input);  // Make a copy of the input string
    int num_tokens = 0;
    if (input_copy == NULL) 
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    // Tokenize the input string
    token = strtok(input_copy, " \t\n");
    while (token != NULL) 
    {
        num_tokens++;
        token = strtok(NULL, " \t\n");
    }
	*num = num_tokens;
    // Allocate memory for the array of tokens
    char** tokens = (char **)malloc((num_tokens) * sizeof(char *));
    if (tokens == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(input_copy);
        exit(EXIT_FAILURE);
    }
    // Tokenize the input string again to populate the array of tokens
    token = strtok(input, " \n");
    for (int i = 0; i < num_tokens; i++) {
        tokens[i] = strdup(token);
        token = strtok(NULL, " \n");
    }
    // Print the tokens
	/*
    printf("Tokens:\n");
    for (int i = 0; i < num_tokens; i++) {
        printf("token %d: %s\n", i+1, tokens[i]);
    }
	*/
    // Parse the tokens (dummy parsing)
	
    //printf("\nParsing:\n");
    if(strcmp(tokens[0],"exit") == 0)
	{
	//	printf("EXITING");
		*CMD = MYEXIT;
		free(input_copy);
		return (char**)tokens;
	}
	else if(strcmp(tokens[0],"mypwd") == 0)
            {
	//	printf("PWDDD:\n");
            	*CMD = MYPWD;
				free(input_copy);
				return (char**)tokens;
            }
	else if(strcmp(tokens[0],"mymove") == 0)
            {
	//	printf("MOVVVE\n");
		*CMD = MYMOVE;
		free(input_copy);
		return (char**)tokens;
				
           	}
	else if(strcmp(tokens[0],"myecho") == 0)
        {
	//	printf("ECHOOOO\n");
            *CMD = MYECHO;
			free(input_copy);
			*num=num_tokens;
			return (char**)tokens;
        }
	else if(strcmp(tokens[0],"mycd") == 0)
	{
		*CMD = MYCD;
		free(input_copy);
		*num=num_tokens;
		return (char**)tokens;

	}
	else if(strcmp(tokens[0],"clear") == 0)
	{
		*CMD = CLEAR;
		free(input_copy);
		*num=num_tokens;
		return (char**)tokens;
	}
	else
	{
		*CMD = EXTERNAL;

		free(input_copy);
		return (char**)tokens;
	}
}
    





int echo(int argc, char *argv[])

{
        int LocalCounter = 1;
        while(argv[LocalCounter]!=NULL)
        {
                printf("%s ",argv[LocalCounter]);
                LocalCounter++;
        }
        printf("\n");
        return 0 ;
}


void EXECUTER(char** argv , char* PATH)
{
	//int execvp(const char *file, char *const argv[]);

}
