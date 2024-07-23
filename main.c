#include "simple_shell.h"

int main()
{
	char in[100] = {'\0'}; /*input string storage*/
	char *drifter; /*temporary storage of the individual tokens before assigning them to the array*/
	char *toks[100]; /*array of tokens converted from the input provided*/
	int end; /*used to store the result of strcmp for checking if the exit command is entered*/
	size_t i; /*iterative variable used for processing strtok*/

	end = 1;

	while(end != 0 ) /*loop keeps shell running until the exit command is entered*/
	{
		printf("$: ");
		fgets(in, sizeof(in), stdin); /*reads the input from the terminal*/
		in[strcspn(in, "\n")] = 0; /*removes the newline at the end of the input string*/
		end = strcmp(in,"exit"); /*sets the value of end to the output of comparing the input with the literal "exit" used to check for the exit command in the input*/
		drifter = strtok(in, " ");
		i = 0;
		while (drifter != NULL) /*loop to handle the assignment of the tokens to the toks array*/
		{
			toks[i++] = drifter;
			drifter = strtok(NULL, " ");
		}
	}
	return(0);
}