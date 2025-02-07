/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:06:30 by acben-ka          #+#    #+#             */
/*   Updated: 2025/02/07 19:35:11 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_separator(char c, char *separators)
{
	int	i;

	i = 0;
	while (separators[i])
	{
		if (c == separators[i])
			return (1);
		i++;
	}
	return (0);
}

int	count_word(char const *s1, char *sp)
{
	int	i;
	int	count;
	int	check;

	i = 0;
	count = 0;
	check = 1;
	while (s1[i])
	{
		if (!is_separator(s1[i], sp) && check == 1)
		{
			count += 1;
			check = 0;
		}
		else if (is_separator(s1[i], sp))
			check = 1;
		i++;
	}
	return (count);
}

char	*ft_strsdup(char const *s, size_t *j, char *sp)
{
	char	*result;
	size_t	i;
	size_t	k;

	i = *j;
	while (!is_separator(s[*j], sp) && s[*j])
		(*j)++;
	result = (char *)malloc((*j - i + 1) * sizeof(char));
	if (!result)
		return (NULL);
	k = 0;
	while (k < *j - i)
	{
		result[k] = s[i + k];
		k++;
	}
	result[k] = '\0';
	return (result);
}

void	ft_free(char **prr)
{
	int	i;

	i = 0;
	while (prr && prr[i])
	{
		free(prr[i]);
		i++;
	}
	if (prr)
		free(prr);
}

char	**ft_split(char const *s, char *c)
{
	t_mypipex	s1;

	s1.j = -1;
	s1.u = 0;
	s1.len_word = count_word(s, c);
	if (!s || !s1.len_word)
		return (NULL);
	s1.prr = (char **)calloc((s1.len_word + 1), sizeof(char *));
	if (s1.prr == NULL)
		return (NULL);
	while (++(s1.j) < s1.len_word)
	{
		while (is_separator(s[s1.u], c) && s[s1.u])
			s1.u++;
		if (s[s1.u])
		{
			s1.prr[s1.j] = ft_strsdup(s, &s1.u, c);
			if (!s1.prr[s1.j])
			{
				ft_free(s1.prr);
				return (NULL);
			}
		}
	}
	return (s1.prr);
}
