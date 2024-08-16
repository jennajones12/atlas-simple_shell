#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern char **environ;

/**
 * execute_command - Execute a command with arguments.
 * @toks: Array of arguments.
 */
void execute_command(char **toks)
{
    char *path;

    /* Find the path of the command */
    path = get_env("PATH", environ);
    if (path == NULL)
    {
        fprintf(stderr, "%s: command not found\n", toks[0]);
        return;
    }

    printf("Executing command: %s\n", toks[0]); // Debug statement

    /* Replace current process image with new one */
    if (execve(toks[0], toks, environ) == -1)
    {
        perror("execve failed");
    }
}
