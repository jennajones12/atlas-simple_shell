#include "simple_shell.h"

void execute_command(char **toks)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (execve(toks[0], toks, environ) == -1)
        {
            perror(toks[0]);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(&status);
    }
}
