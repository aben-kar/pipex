/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:12:53 by acben-ka          #+#    #+#             */
/*   Updated: 2025/02/07 20:00:12 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path_directories(char **envp)
{
	char	*found;
	char	**split_path;

	while (*envp)
	{
		found = ft_strnstr(*envp, "PATH=", 5);
		if (found)
		{
			split_path = ft_split(found + 5, ":");
			if (!split_path)
			{
				write(2, "PATH not found in environment.\n", 31);
				return (NULL);
			}
			return (split_path);
		}
		envp++;
	}
	return (NULL);
}

void	ft_perror(char *err)
{
	perror(err);
	exit(1);
}

char	**split_arguments(char *arg)
{
	char	**splitted;

	splitted = ft_split(arg, " \t");
	if (!splitted)
		return (NULL);
	return (splitted);
}

void	create_pipe(int *fd, char **cmd1, char **cmd2)
{
	if (pipe(fd) == -1)
	{
		ft_free(cmd1);
		ft_free(cmd2);
		ft_perror("pipe");
	}
}

void	create_forks(int *fd, char **av, t_mypipex *pipex, char **envp)
{
	pipex->id1 = fork();
	if (pipex->id1 < 0)
	{
		close_pipe_fds(fd);
		free_commands(pipex);
		ft_perror("fork");
	}
	if (pipex->id1 == 0)
		child_process_1(fd, av[1], pipex, envp);
	pipex->id2 = fork();
	if (pipex->id2 < 0)
	{
		close_pipe_fds(fd);
		free_commands(pipex);
		ft_perror("fork");
	}
	if (pipex->id2 == 0)
		child_process_2(fd, av[4], pipex, envp);
	close_pipe_fds(fd);
	waitpid(pipex->id1, NULL, 0);
	waitpid(pipex->id2, NULL, 0);
}
