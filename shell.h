#ifndef SHELL_H
#define SHELL_H

/* Standard library headers */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/* Process & wait */
#include <sys/types.h>
#include <sys/wait.h>

/* File control / error handling */
#include <errno.h>

#define MAX_ARGS 64
#define BUFFER_SIZE 1024

/* Function prototypes */
extern char **environ;

/* parser */
char **parse_line(char *line);

/* path */
char *find_cmd(char *cmd);

/* exec */
void execute_cmd(char **argv);

/* builtins */
int handle_builtins(char **argv);

/* env */
void print_env(void);

#endif /* SHELL_H */
