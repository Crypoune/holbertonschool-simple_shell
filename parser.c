#include "shell.h"

/**
 * parse_line - split a line into arguments
 * @line: input line
 *
 * Return: NULL-terminated array of arguments
 */
char **parse_line(char *line)
{
	char **argv;
	char *token;
	int i = 0;

	argv = malloc(sizeof(char *) * (MAX_ARGS));
	if (!argv)
		return (NULL);

	token = strtok(line, " \t\n");
	while (token != NULL && i < MAX_ARGS - 1)
	{
		argv[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	argv[i] = NULL;

	return (argv);
}
