#include "shell.h"

/**
 * execute_cmd - execute a command
 * @argv: argument vector
 * @prog_name: name of the program
 * @cmd_count: command count for error messages
 *
 * Return: 1 on success, 127 if command not found, other on error
 */
int execute_cmd(char **argv, char *prog_name, int cmd_count)
{
	pid_t pid;
	int status;
	char *cmd_path;

	cmd_path = find_cmd(argv[0]);
	if (!cmd_path)
	{
		dprintf(2, "%s: %d: %s: not found\n",
				prog_name, cmd_count, argv[0]);
		return (127);
	}

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
