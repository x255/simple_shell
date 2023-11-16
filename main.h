#ifndef MAIN_H
#define MAIN_H

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int lsh_cd();
int lsh_help();
int lsh_exit();
int printenv();
char *get_location(char *command);
int lsh_launch(char **args);
int lsh_execute(char **args, char *copy_env[]);
char *lsh_read_line(void);
char **lsh_split_line(char *line);
void lsh_loop(char *copy_env[]);

#endif /* MAIN_H */
