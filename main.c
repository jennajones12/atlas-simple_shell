#include "simple_shell.h"

int main()
{
	char in[100] = {'\0'};
	char read;
	int end;

	end = 1;

	while(end != 0 )
	{
		printf("$: ");
		read = scanf("%s",in);
		end = strcmp(in,"exit");
	}
	return(0);
}