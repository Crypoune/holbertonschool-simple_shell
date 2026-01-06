#include "shell.h"

/**
 * execute_cmd - Exécute une commande externe
 * @argv: Tableau des arguments de la commande
 * @prog_name: Nom du programme (shell)
 * @cmd_count: Numéro de la commande (pour les messages d'erreur)
 * Return: 1 en cas de succès, code d'erreur sinon
 */
int execute_cmd(char **argv, char *prog_name, int cmd_count)
{
	pid_t pid;
	int status;
	char *cmd_path;

	cmd_path = find_cmd(argv[0]);

	/* If command not found in PATH*/
	if (!cmd_path)
	{
		dprintf(2, "%s: %d: %s: not found\n",
				prog_name, cmd_count, argv[0]);
		return (127);
	}

	/* If no permission or is a directory */
	if (strcmp(cmd_path, "NO_PERMISSION") == 0 ||
	    strcmp(cmd_path, "IS_A_DIR") == 0)
	{
		dprintf(2, "%s: %d: %s: Permission denied\n",
				prog_name, cmd_count, argv[0]);
		free(cmd_path);
		return (126);
	}

	/* Execute the command */
	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, argv, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
		free(cmd_path);
		return (1);
	}

	waitpid(pid, &status, 0);
	free(cmd_path);
	return (1);
}
