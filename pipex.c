#include "pipex.h"


int main(int ac, char *av[], char **envp)
{
    char **split_av = ft_split(av[1], ' ');
    if (!split_av || !split_av[0])
        return 1;
    
    int fd[2];
    

    if (pipe(fd) == -1)
        return (1);

    int id = fork();

    if (id == 0)
    {
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
					    char *cmd = ft_strjoin(tmp, split_av[0]);
                        printf("%s\n", cmd);
					    if (!access(cmd, F_OK | X_OK))
						    execve(cmd, &split_av[0], envp);
                        i++;
                    }
                }
            }
            res++;
        }
    }
    else
    {
        
    }
}