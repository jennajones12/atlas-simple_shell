#include "simple_shell.h"

/* Function to print the environment variables */
void print_env(void)
{
    char **env = environ;

    while (*env)
    {
        printf("%s\n", *env);
        env++;
    }
}

/* Custom getenv function for getting environment variables */
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

/* Function to get environment variable from a custom environment array */
char *get_env(const char *key, char **env)
{
    int i, j;
    int status;

    for (i = 0; env[i] != NULL; i++)
    {
        status = 1;
        for (j = 0; env[i][j] != '='; j++)
        {
            if (key[j] != env[i][j])
            {
                status = 0;
                break;
            }
        }
        if (status)
        {
            return (&env[i][j + 1]);
        }
    }
    return (NULL);
}

/* Function to print environment variables from a custom environment array */
void print_environment(char **env)
{
    char **ptr = env;

    while (*ptr)
    {
        printf("%s\n", *ptr);
        ptr++;
    }
}
