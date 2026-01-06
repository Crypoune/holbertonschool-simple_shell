#include "shell.h"

/**
 * find_cmd - find full path of a command
 * @cmd: command name
 *
 * Return: malloc'ed full path, or NULL if not found
 */
char *find_cmd(char *cmd)
{
	char *path, *path_copy, *dir;
	char full_path[1024];

	if (!cmd)
		return (NULL);

	/* If absolute or relative path */
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (strdup(cmd));
		return (NULL);
	}

	/* Search in PATH */
	path = getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (strdup(full_path));
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
