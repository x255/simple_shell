#include "main.h"

/**
 * printenv - is used to print the values of environment variables.
 * It takes a null-terminated array of strings, `copy_env`, as input.
 * @copy_env: The list of environment variables to printc.
 * Return: returns 0
 */
int printenv(char *copy_env[])
{
int j = 0;
while (copy_env[j] != NULL)
{
printf("%s\n", copy_env[j]);
j++;
}
return (0);
}
/**
 * lsh_cd - is used to change the current working directory.
 * It takes an array of strings, `args`, as input.
 * @args: The list of arguments passed to the "cd" command.
 * Return: Returns 1 if the directory was changed successfully,
 * otherwise returns an error.
 */
int lsh_cd(char **args)
{
if (args[1] == NULL)
{
fprintf(stderr, "lsh: expected argument to \"cd\"\n");
}
else
{
if (chdir(args[1]) != 0)
{
perror("lsh");
}
}
return (1);
}
/**
 * lsh_help - is a built-in command used to print help information.
 * It takes a list of arguments, but it does not examine them.
 * Return: Always returns 1, indicating that the
 * program should continue executing.
 */

int lsh_help(void)
{
printf("Stephen Brennan's LSH\n");
printf("Type program names and arguments, and hit enter.\n");
printf("The following are built in:\n");
printf("Use the man command for information on other programs.\n");
return (1);
}

/**
 * lsh_exit - is a built-in command used to
 * terminate the execution of the program.
 * It takes a list of arguments, but it does not examine them.
 * Return: Always returns 0, indicating that
 * the program should terminate execution.
 */

int lsh_exit(void)
{
return (0);
}
