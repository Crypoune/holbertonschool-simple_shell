#include "shell.h"

/**
 * concatenate_path - concatenate directory and command to form full path
 * @dir: directory path
 * @cmd: command name
 *
 * Return: full path string, or NULL on failure
 */
static char *concatenate_path(const char *dir, const char *cmd)
{
	char *full_path = malloc(strlen(dir) + strlen(cmd) + 2);
	if (!full_path)
		return (NULL);

	strcpy(full_path, dir);
	strcat(full_path, "/");
	strcat(full_path, cmd);

	return (full_path);
}

/**
 * find_cmd - Find the full path of a command
 * @cmd: Command name
 *
 * Return: The full path of the command, or NULL if not found
 */
char *find_cmd(char *cmd)
{
	char *path, *path_copy, *dir;
	char *full_path;
	struct stat st;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (strchr(cmd, '/'))
	{
		if (stat(cmd, &st) != 0 || S_ISDIR(st.st_mode) || access(cmd, X_OK) != 0)
			return (NULL);
		return (strdup(cmd));
	}
	path = _getenv("PATH");
	if (!path || !*path)
		return (NULL);
	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);
	dir = strtok(path_copy, ":");
	while (dir)
	{
		if (*dir == '\0')
			dir = ".";
		full_path = concatenate_path(dir, cmd);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		if (stat(full_path, &st) == 0 && !S_ISDIR(st.st_mode)
		&& access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
