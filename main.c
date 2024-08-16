#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 100

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
        printf("$");
        if (getline(&input, &input_size, stdin) == -1)
        {
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

        /* Handle built-in commands */
        if (strcmp(args[0], "env") == 0)
        {
            print_env();
            continue;
        }

        /* Execute /bin/ls command */
        if (strcmp(args[0], "/bin/ls") == 0)
        {
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
            continue;
        }

        /* Fork and execute other commands */
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
