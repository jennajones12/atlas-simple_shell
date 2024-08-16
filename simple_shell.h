#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>


void execute_command(char **toks);
char *check_path(char *command);
void print_env(void);
char *my_getenv(const char *name);

#endif /* SIMPLE_SHELL_H */
