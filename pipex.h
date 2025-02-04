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
void pipex_process(char **av, char **envp);
void child_process_1(int *fd, char *input_file, char **cmd, char **envp);
void child_process_2(int *fd, char *output_file, char **cmd2, char **envp);
char **split_arguments(char *arg);
void create_pipe(int *fd, char **cmd1, char **cmd2);
void create_forks(int *fd, char **av,t_myvariable *pipex, char **envp);
void handle_error(const char *msg, int exit_code);
#endif
