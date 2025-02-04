/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:07:59 by acben-ka          #+#    #+#             */
/*   Updated: 2025/02/04 23:08:02 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void handle_error(const char *msg, int exit_code) {
    perror(msg);
    exit(exit_code);
}

char **split_arguments(char *arg) {
    return ft_split(arg, " \t");
}

void create_pipe(int *fd, char **cmd1, char **cmd2) {
    if (pipe(fd) == -1) {
        handle_error("pipe failed", 1);
        ft_free(cmd1);
        ft_free(cmd2);
        exit(1);
    }
}

void create_forks(int *fd, char **av, t_myvariable *pipex, char **envp) { //27 line
    t_myvariable i;

    if (pipex->cmd1 && pipex->cmd1[0]) {
        i.id1 = fork();
        if (i.id1 < 0) {
            handle_error("fork failed", 1);
            ft_free(pipex->cmd1);
            ft_free(pipex->cmd2);
            exit(1);
        }
        if (i.id1 == 0)
            child_process_1(fd, av[1], pipex->cmd1, envp);
    }
    i.id2 = fork();
    if (i.id2 < 0) {
        handle_error("fork failed", 1);
        ft_free(pipex->cmd1);
        ft_free(pipex->cmd2);
        exit(1);
    }
    if (i.id2 == 0)
        child_process_2(fd, av[4], pipex->cmd2, envp);
    close(fd[0]);
    close(fd[1]);
    if (i.id1 > 0) 
        waitpid(i.id1, NULL, 0);
    waitpid(i.id2, NULL, 0);
}
