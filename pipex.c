#include "pipex.h"

int main(int ac, char **av, char **envp) {
    if (ac > 3) {
        char **split_av = ft_split(av[2], ' ');
        char **split_av1 = ft_split(av[3], ' ');
        if (!split_av || !split_av1) {
            return 1;
        }

        int fd[2];
            //fd[0] ==> read;
            //fd[1] == write;
        if (pipe(fd) == -1) {
            return 1;
        }

        int id1 = fork();
        if (id1 == 0) {
            int in_file = open(av[1], O_RDONLY | O_CREAT, 0644);
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            dup2(in_file, 0);
            close(in_file);

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
            
            int id2 = fork();
            if (id2 == 0) {
                int output_file = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                close(fd[1]);
                dup2(fd[0], 0);
                close(fd[0]);
                dup2(output_file, STDOUT_FILENO);
                close(output_file);

                if ((access(split_av1[0], F_OK | X_OK)) == 0)
                {
                     execve(split_av1[0], split_av1, envp);
                }
               
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
            }
            close(fd[0]);
            close(fd[1]);
            wait(NULL);
            wait(NULL);
        }
    } else {
        return (-1);
    }
    return 0;
}

