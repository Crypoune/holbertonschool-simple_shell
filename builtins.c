#include "shell.h"

/**
 * handle_builtins - handle built-in commands
 * @argv: Array of command arguments
 * @status: Pointer to the exit status
 *
 * Return: 1 if a builtin was executed, 0 otherwise
 */
int handle_builtins(char **argv, int *status)
{
	int i = 0;
	int exit_code;

	if (!argv || !argv[0])
		return (0);

	/* exit built-in */
	if (strcmp(argv[0], "exit") == 0)
	{
		if (argv[1])
		{
			exit_code = atoi(argv[1]);
			exit(exit_code);
		}
		exit(*status);
	}

	/* env built-in */
	if (strcmp(argv[0], "env") == 0)
	{
		while (environ[i])
		{
			printf("%s\n", environ[i]);
			i++;
		}
		*status = 0;
		return (1);
	}

	return (0);
}
