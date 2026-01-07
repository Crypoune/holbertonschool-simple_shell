#include "shell.h"

/**
 * main - Entry point of the shell program
 * @argc: Number of arguments
 * @argv: Array of arguments
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **args;
	int cmd_count = 0;
	int interactive = 0, status = 0;

	(void)argc;
	interactive = isatty(STDIN_FILENO);
	while (1)
	{
		if (interactive)
			write(1, "$ ", 2);
		read = getline(&line, &len, stdin);
		cmd_count++;
		if (read == -1)
		{
			if (interactive)
				write(1, "\n", 1);
			break;
		}
		if (read == 1)
			continue;
		line[read - 1] = '\0';
		args = parse_line(line);
		if (!args || !args[0])
		{
			free_argv(args);
			continue;
		}
		if (handle_builtins(args))
		{
			free_argv(args);
			continue;
		}
		status = execute_cmd(args, argv[0], cmd_count);
		free_argv(args);
	}
	free(line);
	return (status);
}
