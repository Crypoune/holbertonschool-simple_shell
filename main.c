#include "shell.h"

/**
 * main - Point d'entrée du shell simple
 * @argc: Nombre d'arguments
 * @argv: Tableau des arguments
 *
 * Return: 0 en cas de succès
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **args;
	int status = 0;
	int cmd_count = 0;

	(void)argc;

	while (1)
	{
		/* Afficher le prompt */
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);

		/* Lire la commande */
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			if (isatty(STDIN_FILENO))
				write(1, "\n", 1);
			break;
		}

		/* Supprimer le saut de ligne */
		if (read == 1)
			continue;

		line[read - 1] = '\0';

		args = parse_line(line);
		if (!args || !args[0])
		{
			free(args);
			continue;
		}

		if (handle_builtins(args))
		{
			free(args);
			continue;
		}

		cmd_count++;
		status = execute_cmd(args, argv[0], cmd_count);
		free(args);
	}

	free(line);
	return (status);
}
