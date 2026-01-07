#include "shell.h"

/**
 * find_cmd - Trouve le chemin complet d'une commande
 * @cmd: La commande à chercher
 *
 * Return: Le chemin complet de la commande, ou NULL si non trouvée
 */
char *find_cmd(char *cmd)
{
	char *path, *path_copy, *dir;
	char full_path[1024];
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

	path_copy = strdup(path + 5);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		if (*dir == '\0')
			dir = ".";

		snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
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
