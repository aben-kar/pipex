/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:14:28 by acben-ka          #+#    #+#             */
/*   Updated: 2025/02/07 20:04:14 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	count_char(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == '/')
			count++;
		str++;
	}
	return (count);
}

void	close_pipe_fds(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	free_commands(t_mypipex *pipex)
{
	ft_free(pipex->cmd1);
	ft_free(pipex->cmd2);
}
