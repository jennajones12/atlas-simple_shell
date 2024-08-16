#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PATH_SIZE 1024

/**
 * check_path - Find the full path of a command.
 * @cmd: The command to find.
 *
 * Return: The full path of the command or NULL if not found.
 */
char *check_path(char *cmd)
{
    char *path_env;
    char *path;
    char *dir;
    char full_path[MAX_PATH_SIZE];
    char *result = NULL;

    path_env = getenv("PATH");
    if (path_env == NULL)
    {
        fprintf(stderr, "Error: PATH environment variable not set.\n");
        return NULL;
    }

    path = strdup(path_env);
    if (path == NULL)
    {
        perror("strdup");
        return NULL;
    }

    dir = strtok(path, ":");
    while (dir != NULL)
    {
        /* Use sprintf to construct the full path */
        sprintf(full_path, "%s/%s", dir, cmd);
        if (access(full_path, X_OK) == 0)
        {
            result = strdup(full_path);
            if (result == NULL)
            {
                perror("strdup");
                free(path);
                return NULL;
            }
            break;
        }
        dir = strtok(NULL, ":");
    }

    free(path);
    return result;
}
