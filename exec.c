#include "shell.h"

/**
 * check_absolute_path - check if the command is an absolute or relative path
 * @cmd: command name
 * @prog_name: program name (shell)
 * @cmd_count: command count (for error messages)
 * @error_code: pointer to error code
 *
 * Return: full path of the command, or NULL if not found
 */
static char *check_absolute_path(char *cmd, char *prog_name, int cmd_count,
	int *error_code)
{
	struct stat st;

	if (stat(cmd, &st) != 0)
	{
		dprintf(2, "%s: %d: %s: not found\n",
			prog_name, cmd_count, cmd);
		*error_code = 127;
		return (NULL);
	}

	if (S_ISDIR(st.st_mode))
	{
		dprintf(2, "%s: %d: %s: is a directory\n",
			prog_name, cmd_count, cmd);
		*error_code = 126;
		return (NULL);
	}

	if (access(cmd, X_OK) != 0)
	{
		dprintf(2, "%s: %d: %s: Permission denied\n",
			prog_name, cmd_count, cmd);
		*error_code = 126;
		return (NULL);
	}

	*error_code = 0;
	return (strdup(cmd));
}

/**
 * get_cmd_path - get the full path of a command
 * @cmd: command name
 * @prog_name: program name (shell)
 * @cmd_count: command count (for error messages)
 * @error_code: pointer to error code
 *
 * Return: full path of the command, or NULL if not found
 */
static char *get_cmd_path(char *cmd, char *prog_name, int cmd_count,
	int *error_code)
{
	char *cmd_path;

	if (!cmd)
	{
		*error_code = 127;
		return (NULL);
	}

	if (strchr(cmd, '/'))
		return (check_absolute_path(cmd, prog_name, cmd_count, error_code));

	cmd_path = find_cmd(cmd);
	if (!cmd_path)
	{
		dprintf(2, "%s: %d: %s: not found\n",
			prog_name, cmd_count, cmd);
		*error_code = 127;
		return (NULL);
	}

	*error_code = 0;
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
	int error_code = 0;
	char *cmd_path;

	if (!argv[0])
		return (127);

	cmd_path = get_cmd_path(argv[0], prog_name, cmd_count, &error_code);
	if (!cmd_path)
		return (error_code);

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
		free(cmd_path);
		perror(prog_name);
		exit(127);
	}

	waitpid(pid, &status, 0);
	free(cmd_path);

	return (handle_exit_status(status));
}
