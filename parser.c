#include "shell.h"

/**
 * parse_line - parse a line into arguments
 * @line: input line
 *
 * Return: argument vector
 */
char **parse_line(char *line)
{
	char **argv;
	char *token;
	int i = 0;

	argv = malloc(sizeof(char *) * MAX_ARGS);
	if (!argv)
		return (NULL);

	token = strtok(line, " \t");
	while (token && i < MAX_ARGS - 1)
	{
		argv[i++] = token;
		token = strtok(NULL, " \t");
	}
	argv[i] = NULL;

	return (argv);
}
