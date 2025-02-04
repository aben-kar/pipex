#ifndef PIPEX_H
#define PIPEX_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int	count_word(char const *s1, char sp);
char	*ft_strsdup(char const *s, size_t *j, char sp);
void	*ft_free(char **prr);
char	**ft_split(char const *s, char c);
char **get_path_directories(char **envp);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *str, const char *find, size_t n);
void pipex_process(char **av, char **envp);
void child_process_1(int *fd, char *input_file, char **cmd, char **cmd2, char **envp);
void child_process_2(int *fd, char *output_file, char **cmd2, char **cmd, char **envp);

#endif
