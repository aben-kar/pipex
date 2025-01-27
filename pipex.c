#include "pipex.h"

int main(int ac, char **av, char **envp)
{
    if(ac > 0)
    {
        char **split_av = ft_split(av[1], ' ');
        char **split_av1 = ft_split(av[2], ' ');
        if(!split_av || !split_av1)
            return 0;
        // ft_free(split_av);
        // ft_free(split_av1);

        int fd[2];
        if (pipe(fd) == -1)
        {
            ft_free(split_av);
            ft_free(split_av1);
            return 1;
        }
    
        int id = fork();

        if (id == 0)
        {
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);

            if (!(access(split_av[0], F_OK | X_OK)))
                execve(av[1], split_av, envp);
        

            char **res = envp;
            while(*res)
            {
                char *found = ft_strnstr(*res, "PATH=", 5);
                if (found)
                {
                    char **split_path = ft_split(found + 5, ':');
                    if(split_path)
                    {
                        int i = 0;
                        while(split_path[i])
                        {
                            char *tmp = ft_strjoin(split_path[i], "/");
                            char *cmd = ft_strjoin(tmp, split_av[0]);
                            free(tmp);
                            if (!(access(cmd, F_OK | X_OK)))
                            {
                                free(cmd);
                                ft_free(split_path);
                                ft_free(split_av);
                                ft_free(split_av1);
                                execve(cmd, split_av, envp);
                            }
                            free(cmd);
                            i++;
                        }
                        ft_free(split_path);
                    }
                }
                res++;
            }
            ft_free(split_av);
            ft_free(split_av1);
        }
        else
        {
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);

            if (!(access(split_av1[0], F_OK | X_OK)))
                execve(av[2], split_av1, envp);

            char **res1 = envp;
            while(*res1)
            {
                char *found1 = ft_strnstr(*res1, "PATH=", 5);
                if(found1)
                {
                    char **split_path1 = ft_split(found1, ':');
                    if (split_path1)
                    {
                        int j = 0;
                        while (split_path1[j])
                        {
                            char *tmp1 = ft_strjoin(split_path1[j], "/");
                            char *cmd1 = ft_strjoin(tmp1, split_av1[0]);
                            free(tmp1);
                            if (!(access(cmd1, F_OK | X_OK)))
                            {
                                free(cmd1);
                                ft_free(split_path1);
                                ft_free(split_av);
                                ft_free(split_av1);
                                execve(cmd1, split_av1, envp);
                            }
                            free(cmd1);
                            j++;
                        }
                        ft_free(split_path1);
                    }
                }
                res1++;
            }
            ft_free(split_av);
            ft_free(split_av1);
            wait(NULL);
        }
    }
}