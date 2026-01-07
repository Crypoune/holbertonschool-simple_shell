#include "shell.h"

/**
 * find_cmd - Find the full path of a command
 * @cmd: Command name
 *
 * Return: The full path of the command, or NULL if not found
 */
char *find_cmd(char *cmd)
{
	char *path, *path_copy, *dir;
	char full_path[PATH_MAX];
	struct stat st;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (strchr(cmd, '/'))
	{
		if ((stat(cmd, &st) != 0) || (S_ISDIR(st.st_mode) || access(cmd, X_OK) != 0))
			return (NULL);
		return (strdup(cmd));
	}

	path = getenv("PATH");
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

		strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, cmd);

		if (stat(full_path, &st) == 0 &&
			!S_ISDIR(st.st_mode) &&
			access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (strdup(full_path));
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
