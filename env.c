#include "simple_shell.h"
#include <stdio.h>

extern char **environ;

void print_env(void)
{
    char **env = environ;

    while (*env)
    {
        printf("%s\n", *env);
        env++;
    }
}
