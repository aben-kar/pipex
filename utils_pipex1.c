/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:07:59 by acben-ka          #+#    #+#             */
/*   Updated: 2025/02/06 00:48:36 by acben-ka         ###   ########.fr       */
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

void	ft_perror(char *err)
{
	perror(err);
	// exit(1);
}

char **split_arguments(char *arg) {
    return ft_split(arg, " \t");
}

void create_pipe(int *fd, char **cmd1, char **cmd2) {
    if (pipe(fd) == -1) {
        ft_perror("pipe");
        ft_free(cmd1);
        ft_free(cmd2);
        exit(1);
    }
}

void create_forks(int *fd, char **av, t_myvariable *pipex, char **envp) {
    t_myvariable i;

    i.id1 = -1;
    if (pipex->cmd1 && pipex->cmd1[0]) {
        i.id1 = fork();
        if (i.id1 < 0) {
            ft_perror("fork");
            ft_free(pipex->cmd1);
            ft_free(pipex->cmd2);
            exit(1);
        }
        if (i.id1 == 0) {
            child_process_1(fd, av[1], pipex, envp);
        }
    }
    else{
        write(2, "Command not foundddd.\n", 22);
    }
    
    i.id2 = fork();
    if (i.id2 < 0) {
        ft_perror("fork");
        ft_free(pipex->cmd1);
        ft_free(pipex->cmd2);
        exit(1);
    }   
    if (i.id2 == 0)
    {
        child_process_2(fd, av[4], pipex, envp);
    }
        
    close(fd[0]);
    close(fd[1]);

    waitpid(i.id1, NULL, 0);
    waitpid(i.id2, NULL, 0);
}
