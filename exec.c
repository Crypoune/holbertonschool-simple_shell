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
	struct stat st;

	if (!argv[0])
		return 127;


	if (strchr(argv[0], '/'))
	{
		if (stat(argv[0], &st) != 0)  // fichier inexistant
		{
			dprintf(2, "%s: %d: %s: not found\n", prog_name, cmd_count, argv[0]);
			return 127;
		}

		if (S_ISDIR(st.st_mode) || access(argv[0], X_OK) != 0) // dossier ou non exécutable
		{
			dprintf(2, "%s: %d: %s: Permission denied\n", prog_name, cmd_count, argv[0]);
			return 126;
		}

		cmd_path = strdup(argv[0]);
	}
	else
	{
		cmd_path = find_cmd(argv[0]);
		if (!cmd_path)
		{
			dprintf(2, "%s: %d: %s: not found\n", prog_name, cmd_count, argv[0]);
			return 127; /* jamais fork */
		}
	}

	if (stat(cmd_path, &st) == 0 &&
		(S_ISDIR(st.st_mode) || access(cmd_path, X_OK) != 0))
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
		perror(prog_name);
		exit(1);
	}
	waitpid(pid, &status, 0);
	free(cmd_path);
	return (WEXITSTATUS(status));
}
