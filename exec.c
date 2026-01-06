#include "shell.h"

/**
 * execute_cmd - execute a command
 * @argv: argument vector
 */
void execute_cmd(char **argv)
{
	pid_t pid;
	char *cmd_path;

	cmd_path = find_cmd(argv[0]);
	if (!cmd_path)
	{
		dprintf(2, "./shell: %s: not found\n", argv[0]);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return;
	}

	if (pid == 0)
	{
		execve(cmd_path, argv, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}

	free(cmd_path);
}
