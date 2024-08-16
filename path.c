#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>

/**
 * check_path - Check if a command exists in directories listed in PATH.
 * @command: The command to check.
 *
 * Return: Full path to the command if found, NULL otherwise.
 */
char *check_path(char *command)
{
    char *path_env, *path_copy, *dir;
    struct stat sb;
    char *full_path;

    /* Retrieve PATH environment variable */
    path_env = my_getenv("PATH");
    if (path_env == NULL)
    {
        return (NULL);  /* PATH not found */
    }

    /* Duplicate the PATH environment variable */
    path_copy = strdup(path_env);
    if (path_copy == NULL)
    {
        return (NULL);  /* Memory allocation failure */
    }

    /* Allocate memory for the full path */
    full_path = malloc(PATH_MAX);
    if (full_path == NULL)
    {
        free(path_copy);
        return (NULL);  /* Memory allocation failure */
    }

    /* Tokenize the PATH directories */
    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        /* Construct full path */
        snprintf(full_path, PATH_MAX, "%s/%s", dir, command);
        
        /* Check if the file exists */
        if (stat(full_path, &sb) == 0)
        {
            free(path_copy);
            return (full_path);  /* File found */
        }
        dir = strtok(NULL, ":");  /* Get next directory */
    }

    /* return NULL if not found */
    free(full_path);
    free(path_copy);
    return (NULL);  /* File not found */
}
