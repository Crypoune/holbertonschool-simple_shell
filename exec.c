#include "shell.h"

static int check_cmd_error(char *cmd, char *prog_name, int cmd_count)
{
	struct stat st;

	if (!cmd)
		return (127);

	if (strchr(cmd, '/'))
	{
		if (stat(cmd, &st) != 0)
		{
			dprintf(2, "%s: %d: %s: not found\n",
				prog_name, cmd_count, cmd);
			return (127);
		}

		if (S_ISDIR(st.st_mode) || access(cmd, X_OK) != 0)
		{
			dprintf(2, "%s: %d: %s: Permission denied\n",
				prog_name, cmd_count, cmd);
			return (126);
		}

		return (0);
	}

	if (!find_cmd(cmd))
	{
		dprintf(2, "%s: %d: %s: not found\n",
			prog_name, cmd_count, cmd);
		return (127);
	}

	return (0);
}

/**
 * get_cmd_path - get the full path of a command
 * @cmd: command name
 * @prog_name: program name (shell)
 * @cmd_count: command count (for error messages)
 *
 * Return: full path of the command, or NULL if not found
 */
static char *get_cmd_path(char *cmd, char *prog_name, int cmd_count)
{
	struct stat st;
	char *cmd_path;

	if (!cmd)
		return (NULL);

	if (strchr(cmd, '/'))
	{
		if (stat(cmd, &st) != 0)
		{
			dprintf(2, "%s: %d: %s: not found\n",
				prog_name, cmd_count, cmd);
			return (NULL);
		}
		if (S_ISDIR(st.st_mode) || access(cmd, X_OK) != 0)
		{
			dprintf(2, "%s: %d: %s: Permission denied\n",
				prog_name, cmd_count, cmd);
			return (NULL);
		}

		return (strdup(cmd));
	}

	cmd_path = find_cmd(cmd);
	if (!cmd_path)
		dprintf(2, "%s: %d: %s: not found\n",
			prog_name, cmd_count, cmd);

	return (cmd_path);
}

/**
 * handle_exit_status - handle the exit status
 * @status: exit status of the child process
 *
 * Return: appropriate exit code
 */
static int handle_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

/**
 * execute_cmd - Exécute une commande externe
 * @argv: Tableau des arguments de la commande
 * @prog_name: Nom du programme (shell)
 * @cmd_count: Numéro de la commande (pour les messages d'erreur)
 *
 * Return: 1 en cas de succès, code d'erreur sinon
 */
int execute_cmd(char **argv, char *prog_name, int cmd_count)
{
	pid_t pid;
	int status;
	int error_code;
	char *cmd_path;

	if (!argv[0])
		return (127);

	error_code = check_cmd_error(argv[0], prog_name, cmd_count);
	if (error_code != 0)
		return (error_code);

	cmd_path = get_cmd_path(argv[0], prog_name, cmd_count);
	if (!cmd_path)
		return (127);

	pid = fork();
	if (pid == -1)
	{
		perror(prog_name);
		free(cmd_path);
		return (1);
	}

	if (pid == 0)
	{
		execve(cmd_path, argv, environ);
		perror(prog_name);
		exit(127);
	}

	waitpid(pid, &status, 0);
	free(cmd_path);

	return (handle_exit_status(status));
}
