#include "main.h"
/**
 * get_location - Retrieves the location of a
 * command within the system's PATH environment variable.
 * @command: The command for which the location is to be retrieved.
 * Return: A pointer to a string containing the location of the
 * command, or NULL if not found.
 */

char *get_location(char *command)
{
char *path, *path_copy, *path_token, *file_path;
int command_length, directory_length;
struct stat buffer;
path = getenv("PATH");

if (path)
{
/* Duplicate the path string -> remember to free up memory*/
/* for this because strdup allocates memory that needs to be freed*/
path_copy = strdup(path);
/* Get length of the command that was passed */
command_length = strlen(command);
path_token = strtok(path_copy, ":");
while (path_token != NULL)
{
directory_length = strlen(path_token);
file_path = malloc(command_length + directory_length + 2);
strcpy(file_path, path_token);
strcat(file_path, "/");
strcat(file_path, command);
strcat(file_path, "\0");
if (stat(file_path, &buffer) == 0)
{
free(path_copy);
return (file_path);
}
else
{
free(file_path);
path_token = strtok(NULL, ":");
}
}
free(path_copy);
if (stat(command, &buffer) == 0)
{
return (command);
}
return (NULL);
}
return (NULL);
}
/**
 * lsh_launch - Launches a command by forking a child
 * process and executing it.
 * @args: An array of strings representing the command and its arguments.
 * Return: Always returns 1, to continue execution.
 */
int lsh_launch(char **args)
{
pid_t pid;
int status;
char *command = NULL, *actual_command = NULL;
pid = fork();
if (pid == 0)
{
if (args)
{
/* get the command */
command = args[0];
/* generate the path to this command before passing it to execve */
actual_command = get_location(command);
/* execute the actual command with execve */
if (execve(actual_command, args, NULL) == -1)
{
perror("Error:");
}
}
exit(EXIT_FAILURE);
}
else if (pid < 0)
{
perror("lsh");
}
else
{
do {
waitpid(pid, &status, WUNTRACED);
} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
return (1);
}
/**
 * lsh_execute - Executes a command based on the input arguments.
 * @args: An array of strings representing the command and its arguments.
 * @copy_env: An array of strings representing the environment variables.
 * Return: 1 if the shell should continue running, 0 if it should terminate
 */
int lsh_execute(char **args, char *copy_env[])
{
if (args[0] == NULL)
{
return (1);
}
if (strcmp(args[0], "env") == 0)
{
printenv(copy_env);
}
if (strcmp(args[0], "cd") == 0)
{
lsh_cd(args);
}
if (strcmp(args[0], "help") == 0)
{
lsh_help(args);
}
if (strcmp(args[0], "exit") == 0)
{
lsh_exit(args);
}
return (lsh_launch(args));
}
/**
 * lsh_read_line - Reads a line from stdin.
 * Return: The line from stdin.
 */
char *lsh_read_line(void)
{
#ifdef LSH_USE_STD_GETLINE
char *line = NULL;
ssize_t bufsize = 0;
if (getline(&line, &bufsize, stdin) == -1)
{
if (feof(stdin))
{
exit(EXIT_SUCCESS);
}
else
{
perror("lsh: getline\n");
exit(EXIT_FAILURE);
}
}
return (line);
#else
#define LSH_RL_BUFSIZE 1024
int bufsize = LSH_RL_BUFSIZE, position = 0, c;
char *buffer = malloc(sizeof(char) * bufsize);
if (!buffer)
{
fprintf(stderr, "lsh: allocation error\n");
exit(EXIT_FAILURE);
}
while (1)
{
c = getchar();
if (c == EOF)
{
exit(EXIT_SUCCESS);
}
else if (c == '\n')
{
buffer[position] = '\0';
return (buffer);
}
else
{
buffer[position] = c;
}
position++;
if (position >= bufsize)
{
bufsize += LSH_RL_BUFSIZE, buffer = realloc(buffer, bufsize);
if (!buffer)
{
fprintf(stderr, "lsh: allocation error\n");
exit(EXIT_FAILURE);
}
}
}
#endif
}
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
/**
 * lsh_split_line - Splits a line into an array of tokens
 * @line: The line to be split.
 * Return: Null-terminated array of tokens.
 */
char **lsh_split_line(char *line)
{
int bufsize = LSH_TOK_BUFSIZE, position = 0;
char **tokens = malloc(bufsize *sizeof(char *));
char *token, **tokens_backup;
if (!tokens)
{
fprintf(stderr, "lsh: allocation error\n");
exit(EXIT_FAILURE);
}
token = strtok(line, LSH_TOK_DELIM);
while (token != NULL)
{
tokens[position] = token;
position++;

if (position >= bufsize)
{
bufsize += LSH_TOK_BUFSIZE;
tokens_backup = tokens;
tokens = realloc(tokens, bufsize *sizeof(char *));
if (!tokens)
{
free(tokens_backup);
fprintf(stderr, "lsh: allocation error\n");
exit(EXIT_FAILURE);
}
}

token = strtok(NULL, LSH_TOK_DELIM);
}
tokens[position] = NULL;
return (tokens);
}
