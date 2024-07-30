#include "simple_shell.h"

int main(int argc, char **argv)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *drifter; /* temporary storage of the individual tokens before assigning them to the array */
    char *toks[100]; /* array of tokens converted from the input provided */
    size_t i; /* iterative variable used for processing strtok */
    char *command_path;

    (void)argc; /* to avoid unused variable warning */
    (void)argv; /* to avoid unused variable warning */

    while (1) /* loop keeps shell running until the exit command is entered */
    {
        printf("$: ");
        nread = getline(&line, &len, stdin); /* reads the input from the terminal */
        if (nread == -1) /* handle end-of-file condition (Ctrl+D) */
        {
            printf("\n");
            break;
        }
        line[strcspn(line, "\n")] = 0; /* removes the newline at the end of the input string */
        drifter = strtok(line, " ");
        i = 0;
        while (drifter != NULL) /* loop to handle the assignment of the tokens to the toks array */
        {
            toks[i++] = drifter;
            drifter = strtok(NULL, " ");
        }
        toks[i] = NULL; /* Null-terminate the array of tokens */

        if (toks[0] != NULL)
        {
            if (strcmp(toks[0], "exit") == 0)
            {
                free(line);
                exit(0);
            }
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
    free(line);
    return (0);
}
