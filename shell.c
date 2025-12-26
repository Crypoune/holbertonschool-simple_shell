#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - entry point of the simple shell
 *
 * Description:
 * Displays a prompt, reads a command line,
 * executes it, and waits for completion.
 *
 * Return: Always 0.
 */

extern char **environ;

int main(void)
{
	char buffer[1024];
	char *argv[2];
	pid_t pid;

	while (1)
	{
		/* Afficher le prompt */
		if (write(1, "($) ", 4) == -1)
			return (1);

		/* Lire la commande */
		if (fgets(buffer, 1024, stdin) == NULL)
		{
			if (feof(stdin))
				write(1, "\n", 1);
			break;
		}

		/* Supprimer le \n */
		buffer[strcspn(buffer, "\n")] = '\0';

			argv[0] = buffer;
			argv[1] = NULL;
		/* si l'utilisataur appuie juste sur Entrée */
		if (argv[0][0] == '\0')
			continue;

		/* Créer un processus fils */
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}
		else if (pid == 0)
		{
			/* Processus fils : exécuter la commande */
			if (execve(argv[0], argv, environ) == -1)
			{
				dprintf(2, "./shell: %s: No such file or directory\n", argv[0]);
				exit(1);
			}
		}
		else
		{
			/* Processus parent : attendre la fin du child */
			int status;
			waitpid(pid, &status, 0);
		}
	}

	return (0);
}
