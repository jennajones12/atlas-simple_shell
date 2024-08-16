#include "simple_shell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

/* Custom function to get environment variable */
char *get_env_var(const char *name) {
    int i;
    for (i = 0; environ[i] != NULL; i++) {
        if (strncmp(environ[i], name, strlen(name)) == 0 && environ[i][strlen(name)] == '=') {
            return environ[i] + strlen(name) + 1;
        }
    }
    return NULL;
}

void execute_command(char **toks) {
    /* Example usage of get_env_var */
    char *path = get_env_var("PATH");
    if (path != NULL) {
        printf("PATH: %s\n", path);
    }

    /* Execute command */
    if (execve(toks[0], toks, environ) == -1) {
        perror("execve");
        exit(EXIT_FAILURE);
    }
}
