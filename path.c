#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
    char full_path[1024];

    path_env = getenv("PATH");
    if (path_env == NULL)
    {
        return NULL;
    }

    path = strdup(path_env);
    if (path == NULL)
    {
        return NULL;
    }

    dir = strtok(path, ":");
    while (dir != NULL)
    {
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
        printf("Checking path: %s\n", full_path);
        if (access(full_path, X_OK) == 0)
        {
            free(path);
            return strdup(full_path);
        }
        dir = strtok(NULL, ":");
    }

    free(path);
    return NULL;
}
