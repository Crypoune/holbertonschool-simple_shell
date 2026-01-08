#include "shell.h"

/**
 * _getenv - Get the value of an environment variable
 * @name: Name of the environment variable
 *
 * Return: Pointer to the value of the environment variable, or NULL if not found
 */
char *_getenv(const char *name)
{
	extern char **environ;
	size_t name_len = strlen(name);
	char **env;

	if (!name || !environ)
		return (NULL);

	for (env = environ; *env; env++)
	{
		if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
		{
			return (&(*env)[name_len + 1]);
		}
	}
	return (NULL);
}
