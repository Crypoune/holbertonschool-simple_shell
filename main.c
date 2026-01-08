#include "shell.h"

/**
 * ignore_ctrlc - Signal handler to ignore Ctrl+C
 * @sig: Signal number
 */
void ignore_ctrlc(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, "$ ", 2);
}

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
	int cmd_count = 0, interactive = 0, status = 0;

	(void)argc;
	interactive = isatty(STDIN_FILENO);
	signal(SIGINT, ignore_ctrlc);
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
		if (handle_builtins(args, &status, line))
		{
			free_argv(args);
			continue;
		}
		status = execute_cmd(args, argv[0], cmd_count);
		free_argv(args);
	}
	cleanup_shell(line);
	return (status);
}
