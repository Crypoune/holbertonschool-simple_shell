#include "shell.h"

/**
 * parse_line - parse a line into arguments
 * @line: input line
 *
 * Return: argument vector (NULL-terminated) or NULL on failure
 */
char **parse_line(char *line)
{
	char **argv;
	char *token;
	int i = 0;

	if (!line)
		return (NULL);

	argv = malloc(sizeof(char *) * MAX_ARGS);
	if (!argv)
		return (NULL);

	token = strtok(line, " \t");
	while (token && i < MAX_ARGS - 1)
	{
		argv[i] = strdup(token);
		if (!argv[i])
		{
			/* nettoyage en cas d'échec */
			while (i > 0)
				free(argv[--i]);
			free(argv);
			return (NULL);
		}
		i++;
		token = strtok(NULL, " \t");
	}
	argv[i] = NULL;

	return (argv);
}
