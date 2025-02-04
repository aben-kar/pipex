#include "pipex.h"

char **get_path_directories(char **envp) {
    while (*envp) {
        char *found = ft_strnstr(*envp, "PATH=", 5);
        if (found) {
            char **split_path = ft_split(found + 5, ":");
            if (!split_path)
                return (NULL);
            return split_path;
        }
        envp++;
    }
    return (NULL);
}

void pipex_process(char **av, char **envp) {
    char **cmd1 = ft_split(av[2], " \t");
    char **cmd2 = ft_split(av[3], " \t");

    if (!cmd2) {
        ft_free(cmd1);
        exit(1);
    }

    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        ft_free(cmd1);
        ft_free(cmd2);
        exit(1);
    }

    pid_t id1 = -1;
    if (cmd1 && cmd1[0]) {
        id1 = fork();
        if (id1 < 0) {
            perror("fork");
            ft_free(cmd1);
            ft_free(cmd2);
            exit(1);
        }
        if (id1 == 0)
            child_process_1(fd, av[1], cmd1, envp);
    }

    pid_t id2 = fork();
    if (id2 < 0) {
        perror("fork");
        ft_free(cmd1);
        ft_free(cmd2);
        exit(1);
    }
    if (id2 == 0)
        child_process_2(fd, av[4], cmd2, envp);

    close(fd[0]);
    close(fd[1]);

    if (id1 > 0) 
        waitpid(id1, NULL, 0);
    waitpid(id2, NULL, 0);

    ft_free(cmd1);
    ft_free(cmd2);
}
