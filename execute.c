#include "simple_shell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

void execute_command(char **toks) {
    if (execve(toks[0], toks, environ) == -1) {
        perror("execve");
        exit(EXIT_FAILURE);
    }
}
