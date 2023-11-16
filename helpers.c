#include "main.h"

/**
 * lsh_loop - Executes a loop that continuously gets input and executes it.
 * @copy_env: An array of strings representing the environment variables.
 *
 * This function prompts the user with a "$" symbol, reads a line of input,
 * splits the line into arguments, executes the command,
 * and repeats the process
 * until the command indicates that the shell should terminate.
 */
void lsh_loop(char *copy_env[])
{
char *line;
char **args;
int status;
do {
printf("$");
line = lsh_read_line();
args = lsh_split_line(line);
status = lsh_execute(args, copy_env);
free(line);
free(args);
} while (status);
}

