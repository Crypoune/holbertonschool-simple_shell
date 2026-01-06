#include "shell.h"

/**
 * main - entry point of the simple shell
 *
 * Return: Always 0
 */
int main(void)
{
	char buffer[BUFFER_SIZE];
	char **argv;

	while (1)
	{
		/* Afficher le prompt */
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);

		/* Lire la commande */
		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		/* Parser la ligne */
		argv = parse_line(buffer);
		if (!argv || argv[0])
		{
			free(argv);
			continue;
		}

		/* Gérer les built-ins */
		if (handle_builtins(argv))
		{
			free(argv);
			continue;
		}

		/* Exécuter la commande */
		execute_cmd(argv);
		free(argv);
	}

	return (0);
}
