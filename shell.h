#ifndef SHELL_H
#define SHELL_H

/* Standard library headers */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

/* Process & wait */
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* File control / error handling */
#include <errno.h>

/* Constants */
#define MAX_ARGS 64   /* argument number limit */

/* External variables */
extern char **environ;

/* Function prototypes */
/* parser */
char **parse_line(char *line);

/* path */
char *find_cmd(char *cmd);

/* exec */
int execute_cmd(char **argv, char *prog_name, int cmd_count);

/* builtins */
int handle_builtins(char **argv);

/* cleanup */
void free_argv(char **argv);

#endif /* SHELL_H */
