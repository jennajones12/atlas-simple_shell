#include "simple_shell.h"

int main()
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *drifter; /* temp storage of indvdual tokens before assigning them to the array */
    char *toks[100]; /* array of tokens converted from input provided */
    int end; /* used to store result of strcmp for checking if the exit command is entered */
    size_t i; /* iterative var used for processing strtok */

    end = 1;

    while (end != 0) /* loop keeps shell running until exit cmd entered */
    {
        printf("$: ");
        nread = getline(&line, &len, stdin); /* reads input from terminal */
        if (nread == -1) /* handle eof condition (Ctrl+D) */
        {
            printf("\n");
            break;
        }
        line[strcspn(line, "\n")] = 0; /* rmvs newline at eoi str */
        end = strcmp(line, "exit"); /* sets val of end to output of comparing input w literal "exit"- used to check for exit cmd */
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
            execute_command(toks);
        }
    }
    free(line);
    return (0);
}
