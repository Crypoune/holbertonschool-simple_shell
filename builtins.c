#include "shell.h"

/**
 * handle_builtins - handle built-in commands
 * @argv: Array of command arguments
 * @status: Pointer to the exit status
 * @line: input line to free on exit
 *
 * Return: 1 if a builtin was executed, 0 otherwise
 */
int handle_builtins(char **argv, int *status, char *line)
{
	int i = 0;
	int exit_code;

	if (!argv || !argv[0])
		return (0);

	/* exit built-in */
	if (strcmp(argv[0], "exit") == 0)
	{
		exit_code = argv[1] ? atoi(argv[1]) : *status;

		free_argv(argv);
		cleanup_shell(line);
		exit(exit_code);
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
