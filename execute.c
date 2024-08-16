#include "simple_shell.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

/* Custom function to get environment variable */
char *get_env_var(const char *name) {
    int i;
    size_t name_len = strlen(name);

    for (i = 0; environ[i] != NULL; i++) {
        if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=') {
            return environ[i] + name_len + 1;
        }
    }
    return NULL;
}

void execute_command(char **toks) {
    /* Example usage of get_env_var */
    char *path = get_env_var("PATH");
    if (path != NULL) {
        const char *prefix = "PATH: ";
        write(STDOUT_FILENO, prefix, strlen(prefix));
        write(STDOUT_FILENO, path, strlen(path));
        write(STDOUT_FILENO, "\n", 1);
    }

    /* Execute command */
    if (execve(toks[0], toks, environ) == -1) {
        perror("execve");
        _exit(EXIT_FAILURE);
    }
}
