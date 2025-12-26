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

/* Function prototypes */
extern char **environ;

#endif /* SHELL_H */
