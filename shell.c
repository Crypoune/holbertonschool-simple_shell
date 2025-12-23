#include "shell.h"

/**
 * main - Simple shell implementation
 * Return: Always 0
 * Description: This function implements a simple shell that reads user input,
 * 			executes commands, and handles errors.
 * 			It displays a prompt, reads a command, forks a child process,
 * 			and executes the command using execve.
 * 			If the command is not found, it prints an error message.
 * 			The shell continues to run until EOF is encountered.
 * 			Note: This implementation does not handle built-in commands,
 * 			redirection, or piping.
 * 			Buffer size is limited to 1024 characters.
 * 			Environment variables are passed to execve using environ.
 * 			Error handling is done using perror and dprintf.
 * 			The shell uses waitpid to wait for the child process to finish.
 * 			The prompt is "($) ".
 * 			The command is read using fgets.
 * 			The newline character is removed from the input command.
 * 			The argv array is prepared with the command and a NULL terminator.
 * 			Forking is done using fork().
 * 			Execve is used to execute the command.
 * 			If fork fails, an error message is printed and the loop continues.
 * 			If execve fails in the child process, an error message is printed
 * 			and the child exits with status 1.
 * 			The parent process waits for the child to finish using waitpid.
 * 			The shell runs in an infinite loop until EOF is encountered.
 * 			Returns 0 on successful completion.
 */
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

		/* Préparer argv */
		{
			char *token;
			int i = 0;

			token = strtok(buffer, " `t");
			while (token != NULL)
			{
				argv[i++] = token;
				token = strtok(NULL, " \t");
			}
			argv[i] = NULL;
		}

		/* si l'utilisataur appuie juste sur Entrée */
		if (argv[0] == NULL)
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
