#include "shell.h"

/**
 * handle_builtins - handle shell built-in commands
 * @argv: argument vector
 *
 * Return: 1 if a built-in was executed, 0 otherwise
 */
int handle_builtins(char **argv)
{
	int i;

	if (!argv || !argv[0])
		return (0);

	/* exit built-in */
	if (strcmp(argv[0], "exit") == 0)
	{
		exit(0);
	}

	/* env built-in */
	if (strcmp(argv[0], "env") == 0)
	{
		i = 0;
		while (environ[i])
		{
			write(STDOUT_FILENO, environ[i], strlen(environ[i]));
			write(STDOUT_FILENO, "\n", 1);
			i++;
		}
		return (1);
	}

	return (0);
}
