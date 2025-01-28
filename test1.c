#include "pipex.h"

int main(int ac, char **av, char **envp) {
    if (ac > 2) {
        char **split_av = ft_split(av[1], ' ');
        char **split_av1 = ft_split(av[2], ' ');
        if (!split_av || !split_av1) {
            return 1;
        }

        int fd[2];
        if (pipe(fd) == -1) {
            return 1;
        }

        int id = fork();
        if (id == 0) {
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);

            if ((access(split_av[0], F_OK | X_OK)) == 0)
                execve(split_av[0], split_av, envp);

            char **res = envp;
            while (*res) {
                char *found = ft_strnstr(*res, "PATH=", 5);
                if (found) {
                    char **split_path = ft_split(found + 5, ':');
                    if (split_path) {
                        int i = 0;
                        while (split_path[i]) {
                            char *tmp = ft_strjoin(split_path[i], "/");
                            char *cmd = ft_strjoin(tmp, split_av[0]);
                            if ((access(cmd, F_OK | X_OK)) == 0) {
                                execve(cmd, split_av, envp);
                            }
                            i++;
                        }
                    }
                }
                res++;
            }
        } else {
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);

            if ((access(split_av1[0], F_OK | X_OK)) == 0)
                execve(split_av1[0], split_av1, envp);

            char **res1 = envp;
            while (*res1) {
                char *found1 = ft_strnstr(*res1, "PATH=", 5);
                if (found1) {
                    char **split_path1 = ft_split(found1 + 5, ':');
                    if (split_path1) {
                        int j = 0;
                        while (split_path1[j]) {
                            char *tmp1 = ft_strjoin(split_path1[j], "/");
                            char *cmd1 = ft_strjoin(tmp1, split_av1[0]);
                            if ((access(cmd1, F_OK | X_OK)) == 0) {
                                execve(cmd1, split_av1, envp);
                            }
                            j++;
                        }
                    }
                }
                res1++;
            }
            wait(NULL);
        }
    } else {
        write(STDERR_FILENO, "Usage: ./pipex \"cmd1\" \"cmd2\"\n", 30);
    }
    return 0;
}







#include "pipex.h"

void execute_command(char **cmd, char **envp)
{
    if (access(cmd[0], F_OK | X_OK) == 0)
        execve(cmd[0], cmd, envp);

    char **res = envp;
    while (*res)
    {
        char *found = ft_strnstr(*res, "PATH=", 5);
        if (found)
        {
            char **split_path = ft_split(found + 5, ':');
            if (split_path)
            {
                for (int i = 0; split_path[i]; i++)
                {
                    char *tmp = ft_strjoin(split_path[i], "/");
                    char *full_cmd = ft_strjoin(tmp, cmd[0]);
                    free(tmp);

                    if (access(full_cmd, F_OK | X_OK) == 0)
                    {
                        ft_free(split_path);
                        execve(full_cmd, cmd, envp);
                        free(full_cmd);
                        return;
                    }
                    free(full_cmd);
                }
                ft_free(split_path);
            }
        }
        res++;
    }
    perror("command not found");
    exit(1);
}

void execute_pipex(char **cmd1, char **cmd2, char **envp)
{
    int fd[2];
    if (pipe(fd) == -1)
    {
        perror("pipe");
        return;
    }

    int id = fork();
    if (id == -1)
    {
        perror("fork");
        return;
    }

    if (id == 0)
    {
        // Child process
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execute_command(cmd1, envp);
    }
    else
    {
        // Parent process
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        execute_command(cmd2, envp);
        wait(NULL);
    }
}

#include "pipex.h"

int main(int ac, char **av, char **envp)
{
    if (ac != 3) // Ensure correct number of arguments
    {
        fprintf(stderr, "Usage: %s <cmd1> <cmd2>\n", av[0]);
        return 1;
    }

    char **split_av = ft_split(av[1], ' ');
    char **split_av1 = ft_split(av[2], ' ');

    if (!split_av || !split_av1)
        return 1;

    execute_pipex(split_av, split_av1, envp);

    ft_free(split_av);
    ft_free(split_av1);

    return 0;
}