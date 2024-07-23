#include "simple_shell.h"

int main()
{
	char in[100] = {'\0'}; //input string storage
	char *drifter; //temporary storage of the individual tokens before assigning them to the array
	char *toks[100]; //array of tokens converted from the input provided
	int end; //used to store the result of strcmp for checking if the exit command is entered
	size_t i; //iterative variable used for processing strtok

	end = 1;

	while(end != 0 )
	{
		printf("$: ");
		scanf("%s",in);
		drifter = strtok(in, " ");
		i = 0;
		while (drifter != NULL)
		{
			toks[i++] = drifter;
			drifter = strtok(NULL, " ");
		}
		end = strcmp(in,"exit");
	}
	return(0);
}