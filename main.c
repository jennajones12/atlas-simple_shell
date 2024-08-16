#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024

extern char **environ;

/**
 * main - Entry point of the shell program.
 *
 * Return: 0 on success.
 */
int main(void)
{
    char input[MAX_INPUT_SIZE];
    char *toks[MAX_INPUT_SIZE / 2 + 1]; /* Token array */
    char *token;
    int i, j;

    /* Test with a known command */
    char *test_toks[] = {"/bin/ls", NULL};
    execute_command(test_toks);

    while (1)
    {
        printf("$ ");
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
        {
            perror("fgets");
            exit(EXIT_FAILURE);
        }

        /* Remove trailing newline */
        input[strcspn(input, "\n")] = '\0';

        /* Tokenize input */
        i = 0;
        token = strtok(input, " ");
        while (token != NULL)
        {
            toks[i++] = token;
            token = strtok(NULL, " ");
        }
        toks[i] = NULL; /* Null-terminate the array */

        /* Check if the input is not empty */
        if (toks[0] != NULL)
        {
            /* Debug: Print the command and arguments */
            printf("Command: %s\n", toks[0]);
            for (j = 0; j < i; j++)
            {
                printf("Arg[%d]: %s\n", j, toks[j]);
            }

            /* Execute the command */
            execute_command(toks);
        }
    }

    return 0;
}
