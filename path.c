#include "simple_shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

char *check_path(char *command) {
    char *path = getenv("PATH");
    char *full_path;
    char *path_copy;
    char *dir;
    struct stat sb;

    if (path == NULL) {
        return NULL;
    }

    path_copy = strdup(path);
    if (path_copy == NULL) {
        return NULL;
    }

    dir = strtok(path_copy, ":");
    while (dir != NULL) {
        full_path = malloc(PATH_MAX);
        if (full_path == NULL) {
            free(path_copy);
            return NULL;
        }

        snprintf(full_path, PATH_MAX, "%s/%s", dir, command);
        if (stat(full_path, &sb) == 0) {
            free(path_copy);
            return full_path;
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}
