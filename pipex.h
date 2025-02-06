/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:07:44 by acben-ka          #+#    #+#             */
/*   Updated: 2025/02/06 15:21:58 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

typedef struct myvariable {
    int i;
    char **directories;
    char *cmd_path;
    char *tmp;
    char **cmd1;
    char **cmd2;
    pid_t id1;
    pid_t id2;
}t_myvariable;


void	ft_free(char **prr);
char **ft_split(char const *s, char *c);
char **get_path_directories(char **envp);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *str, const char *find, size_t n);
void	ft_perror(char *err);
void child_process_1(int *fd, char *input_file, t_myvariable *pipex, char **envp);
void child_process_2(int *fd, char *output_file, t_myvariable *pipex, char **envp);
char **split_arguments(char *arg);
void create_pipe(int *fd, char **cmd1, char **cmd2);
void create_forks(int *fd, char **av,t_myvariable *pipex, char **envp);
char *find_executable_path(char *cmd, char **envp);
int	count_word(char const *s1, char *sp);


#endif
