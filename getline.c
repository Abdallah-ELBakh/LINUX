#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


/************************************************/
/*  Author  : ABDULLAH AYMAN                    */
/*  Date    : 31/1/2024  8:00PM                 */
/* topic    : Basic Shell concept               */
/* version  : 1.0                               */
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
