#include "shell.h"

/**
 * free_argv - free memory allocated for argument vector
 * @argv: argument vector to free
 *
 * Return: void
 */
void free_argv(char **argv)
{
	int i = 0;

	if (!argv)
		return;

	while (argv[i])
	{
		free(argv[i]);
		i++;
	}

	free(argv);
}
