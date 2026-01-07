int execute_cmd(char **argv, char *prog_name, int cmd_count)
{
    pid_t pid;
    int status;
    char *cmd_path = NULL;
    struct stat st;

    if (!argv[0])
        return (127);

    if (strchr(argv[0], '/'))
    {
        if (stat(argv[0], &st) != 0)
        {
            dprintf(2, "%s: %d: %s: not found\n", prog_name, cmd_count, argv[0]);
            return (127);
        }
        if (S_ISDIR(st.st_mode) || access(argv[0], X_OK) != 0)
        {
            dprintf(2, "%s: %d: %s: Permission denied\n",
                    prog_name, cmd_count, argv[0]);
            return (126);
        }
        cmd_path = strdup(argv[0]);
        if (!cmd_path)
            return (1);
    }
    else
    {
        cmd_path = find_cmd(argv[0]);
        if (!cmd_path)
        {
            dprintf(2, "%s: %d: %s: not found\n", prog_name, cmd_count, argv[0]);
            return (127);
        }
    }

    /* Vérification stat supplémentaire */
    if (stat(cmd_path, &st) == 0 &&
        (S_ISDIR(st.st_mode) || access(cmd_path, X_OK) != 0))
    {
        dprintf(2, "%s: %d: %s: Permission denied\n",
                prog_name, cmd_count, argv[0]);
        free(cmd_path);
        return (126);
    }

    pid = fork();
    if (pid == -1)
    {
        perror(prog_name);
        free(cmd_path);
        return (1);
    }
    else if (pid == 0)
    {
        execve(cmd_path, argv, environ);
        perror(prog_name);
        exit(1);
    }
    else
    {
        waitpid(pid, &status, 0);
        free(cmd_path);
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
        else
            return (1);
    }
}
