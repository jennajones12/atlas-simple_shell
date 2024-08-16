#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 100

extern char **environ;

void print_env(void);

int main(void)
{
    char *input = NULL;
    size_t input_size = 0;
    char *args[MAX_ARG_SIZE];
    char *token;
    int status;
    pid_t pid;
    int i;
    int only_spaces;

    while (1)
    {
        printf("$ ");
        if (getline(&input, &input_size, stdin) == -1)
        {
            if (feof(stdin))  /* End of file reached */
                break;
            perror("getline");
            exit(EXIT_FAILURE);
        }

        /* Remove newline character from input */
        input[strlen(input) - 1] = '\0';

        /* Check if input contains only spaces */
        only_spaces = 1;
        for (i = 0; i < (int)strlen(input); i++)
        {
            if (input[i] != ' ')
            {
                only_spaces = 0;
                break;
            }
        }
        if (only_spaces)
        {
            continue;
        }

        /* Tokenize input */
        i = 0;
        token = strtok(input, " ");
        while (token != NULL)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        /* Check for built-in commands */
        if (strcmp(args[0], "env") == 0)
        {
            print_env();
            continue;
        }

        /* Fork and execute command */
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            if (execve(args[0], args, environ) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            waitpid(pid, &status, 0);
        }
    }

    free(input);
    return 0;
}
