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
char *my_getenv(const char *name);
void print_environment(char **env);
char *get_env(const char *key, char **env);

#endif /* SIMPLE_SHELL_H */
