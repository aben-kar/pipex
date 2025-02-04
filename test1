#include "pipex.h"

void pipex_process(char **av, char **envp) {
    char **cmd1 = ft_split(av[2], ' ');
    if (!cmd1)
        exit(1);
    char **cmd2 = ft_split(av[3], ' ');
    if (!cmd2)
        return (ft_free(cmd1), exit(1));
    
    int fd[2];
    if (pipe(fd) == -1)
    {
        perror("pipe");
        return (ft_free(cmd1), ft_free(cmd2), exit(1));
    }
    
    pid_t id1 = fork();
    if (id1 < 0)
    {
        perror("fork");
        return (ft_free(cmd1), ft_free(cmd2), exit(1));
    }
    if (id1 == 0)
        child_process_1(fd, av[1], cmd1, cmd2, envp);
    
    pid_t id2 = fork();
    if (id2 < 0)
    {
        perror("fork");
        return (ft_free(cmd1), ft_free(cmd2), exit(1));
    }
    if (id2 == 0)
        child_process_2(fd, av[4], cmd2, cmd1, envp);
    
    close(fd[0]);
    close(fd[1]);

    waitpid(id1, NULL, 0);
    waitpid(id2, NULL, 0);
    
    ft_free(cmd1);
    ft_free(cmd2);
}
