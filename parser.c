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
	char *token, *line_copy;
	int i = 0;
	int j;

	if (!line)
		return (NULL);
	line_copy = strdup(line);
	if (!line_copy)
		return (NULL);
	argv = malloc(sizeof(char *) * MAX_ARGS);
	if (!argv)
	{
		free(line_copy);
		return (NULL);
	}
	token = strtok(line_copy, " \t");
	while (token && i < MAX_ARGS - 1)
	{
		argv[i] = strdup(token);
		if (!argv[i])
		{
			for (j = 0; j < i; j++)
			{
				free(argv[j]);
			}
			free(argv);
			free(line_copy);
			return (NULL);
		}
		i++;
		token = strtok(NULL, " \t");
	}
	argv[i] = NULL;
	free(line_copy);
	return (argv);
}
