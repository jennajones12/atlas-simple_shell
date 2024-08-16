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
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARG_SIZE];
    char *token;
    int status;
    pid_t pid;
    int i;

    while (1)
    {
        printf("$ ");
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
        {
            perror("fgets");
            exit(EXIT_FAILURE);
        }

        /* Remove newline character from input */
        input[strcspn(input, "\n")] = '\0';

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
            /* Child process */
            if (execve(args[0], args, environ) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            /* Parent process */
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
