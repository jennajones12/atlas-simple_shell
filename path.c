#include "simple_shell.h"

char *check_path(char *command)
{
    char *path = getenv("PATH");
    char *path_copy = strdup(path);
    char *dir;
    char *full_path = malloc(PATH_MAX);
    struct stat sb;

    if (stat(command, &sb) == 0)
    {
        free(path_copy);
        return strdup(command);
    }

    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        snprintf(full_path, PATH_MAX, "%s/%s", dir, command);
        if (stat(full_path, &sb) == 0)
        {
            free(path_copy);
            return full_path;
        }
        dir = strtok(NULL, ":");
    }
    free(path_copy);
    free(full_path);
    return NULL;
}
