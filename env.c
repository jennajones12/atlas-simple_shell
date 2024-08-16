#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

/**
 * print_env - Prints the environment variables.
 */
void print_env(void)
{
    char **env = environ;
    
    while (*env)
    {
        printf("%s\n", *env);
        env++;
    }
}

/**
 * my_getenv - Gets a specific environment variable.
 * @name: The name of the variable.
 *
 * Return: The value of the variable or NULL if not found.
 */
char *my_getenv(const char *name)
{
    int i, j;
    int status;

    for (i = 0; environ[i] != NULL; i++)
    {
        status = 1;
        for (j = 0; environ[i][j] != '='; j++)
        {
            if (name[j] != environ[i][j])
            {
                status = 0;
                break;
            }
        }
        if (status)
        {
            return (&environ[i][j + 1]);
        }
    }
    return (NULL);
}
