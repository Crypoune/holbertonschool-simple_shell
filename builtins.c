#include "shell.h"

/**
 * handle_builtins - Gère les commandes built-in
 * @argv: Tableau des arguments de la commande
 *
 * Return: 1 si une built-in a été exécutée, 0 sinon
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
