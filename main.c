#include "simple_shell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern char **environ;

char *my_getenv(const char *name)
{
    int i;
    size_t len = strlen(name);

    for (i = 0; environ[i] != NULL; i++)
    {
        if (strncmp(name, environ[i], len) == 0 && environ[i][len] == '=')
        {
            return &environ[i][len + 1];
        }
    }
    return NULL;
}

size_t my_strcspn(const char *s, const char *reject)
{
    size_t i, j;

    for (i = 0; s[i] != '\0'; i++)
    {
        for (j = 0; reject[j] != '\0'; j++)
        {
            if (s[i] == reject[j])
            {
                return i;
            }
        }
    }
    return i;
}

int main(int argc, char **argv)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *drifter; /* temp storage of tokens before assigning to array */
    char *toks[100]; /* array of tokens converted from input provided */
    size_t i; /* iterative variable used for processing strtok */
    char *command_path;

    (void)argc; /* to avoid unused variable warning */
    (void)argv; /* to avoid unused variable warning */

    while (1) /* loop keeps shell running until exit command entered */
    {
        printf("$ ");
        nread = getline(&line, &len, stdin); /* reads input from terminal */
        if (nread == -1) /* handle end-of-file (Ctrl+D) */
        {
            printf("\n");
            break;
        }

        line[my_strcspn(line, "\n")] = '\0'; /* removes newline end of input str */
        drifter = strtok(line, " ");
        i = 0;
        while (drifter != NULL) /* loop to handle assignment of tokens to toks array */
        {
            toks[i++] = drifter;
            drifter = strtok(NULL, " ");
        }
        toks[i] = NULL; /* Null-terminate array of tokens */

        if (toks[0] != NULL)
        {
            if (strcmp(toks[0], "exit") == 0)
            {
                free(line);
                exit(0);
            }
            else if (strcmp(toks[0], "env") == 0)
            {
                print_env();
            }
            else
            {
                command_path = check_path(toks[0]);
                if (command_path != NULL)
                {
                    toks[0] = command_path;
                    execute_command(toks);
                    free(command_path);
                }
                else
                {
                    fprintf(stderr, "%s: command not found\n", toks[0]);
                }
            }
        }
    }
    free(line);
    return (0);
}
