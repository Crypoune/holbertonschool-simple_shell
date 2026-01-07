#include "shell.h"

int cmd_error = 0;

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

	cmd_error = 0;


	if (!cmd || cmd[0] == '\0')
	{
		cmd_error = 127;
		return (NULL);
	}

	/* If absolute or relative path */
	if (strchr(cmd, '/'))
	{
		if (stat(cmd, &st) != 0)
		{
			cmd_error = 127;
			return (NULL);
		}

		if (S_ISDIR(st.st_mode) || access(cmd, X_OK) != 0)
		{
			cmd_error = 126;
			return (NULL);
		}
		return (strdup(cmd));
	}

	/* Search in PATH */
	path = getenv("PATH");
	if (!path || path[0] == '\0')
	{
		cmd_error = 127;
		return (NULL);
	}

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		if (*dir == '\0')
			dir = ".";

		snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			if (S_ISDIR(st.st_mode) || access(full_path, X_OK) != 0)
			{
				cmd_error = 126;
				return (NULL);
			}
			return (strdup(full_path));
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	cmd_error = 127;
	return (NULL);
}
