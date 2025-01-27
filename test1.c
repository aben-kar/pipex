#include "pipex.c"

int main(int ac, char *av[], char **envp)
{
    char **split_av1 = ft_split(av[1], ' ');
    char **split_av2 = ft_split(av[2], ' ');
    if (!split_av1 || !split_av2)
        return 1;
    
    int fd[2];
    

    if (pipe(fd) == -1)
        return (1);

    int id = fork();

    if (id == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        char **res = envp;
        while(*res)
        {
            char *found = ft_strstr(*res, "PATH=/home/acben-ka");
            if(found)
            {
                char **split_path = ft_split(found + 5, ':');
                if(split_path)
                {
                    int i = 0;
                    while (split_path[i])
                    {
					    char *tmp = ft_strjoin(split_path[i], "/");
					    char *cmd = ft_strjoin(tmp, split_av1[0]);
                        // printf("%s\n", cmd);
					    if (!access(cmd, F_OK | X_OK))
						    execve(cmd, split_av1, envp);
                        i++;
                    }
                }
            }
            res++;
        }
    }
    else
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

        char **res1 = envp;
        while (*res1)
        {
            char *found1 = ft_strstr(*res1, "PATH=/home/acben-ka");
            if (found1)
            {
                char **split_path1 = ft_split(found1 + 5, ':');
                if (split_path1)
                {
                    int j = 0;
                    while(split_path1[j])
                    {
                        char *tmp1 = ft_strjoin(split_path1[j], "/");
                        char *cmd1 = ft_strjoin(tmp1, split_av2[0]);
                        if (!access(cmd1, F_OK | X_OK))
                            execve(cmd1, split_av2, envp);
                        j++;
                    }
                }
            }
            res1++;
        }
    }
}