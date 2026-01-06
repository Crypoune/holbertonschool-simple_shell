#include "shell.h"

/**
 * get_path - get PATH value from environment
 *
 * Return: pointer to PATH value, or NULL
 */
static char *get_path(void)
{
	int i = 0;

	while (environ[i])
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
		i++;
	}
	return (NULL);
}

/**
 * find_cmd - find full path of a command
 * @cmd: command name
 *
 * Return: malloc'ed full path, or NULL if not found
 */
char *find_cmd(char *cmd)
{
	char *path, *path_copy, *dir;
	char *full_path;

	/* Case 1: absolute or relative path */
	if (strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (strdup(cmd));
		return (NULL);
	}

	/* Case 2: search in PATH */
	path = get_path();
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(cmd) + 2);
		if (!full_path)
			break;

		sprintf(full_path, "%s/%s", dir, cmd);

		if (access(full_path, F_OK) == 0)
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
