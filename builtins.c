#include "shell.h"

/**
 * handle_builtins - handle built-in commands
 * @argv: Array of command arguments
 *
 * Return: 1 if a builtin was executed, 0 otherwise
 */
int handle_builtins(char **argv)
{
	int i = 0;

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
		while (environ[i])
		{
			printf("%s\n", environ[i]);
			i++;
		}
		return (1);
	}

	return (0);
}
