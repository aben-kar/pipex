/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:06:30 by acben-ka          #+#    #+#             */
/*   Updated: 2025/02/04 23:07:02 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int is_separator(char c, char *separators) {
    int i = 0;
    while (separators[i]) {
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

char **ft_split(char const *s, char *c) {
    size_t j = 0;
    size_t i = 0;
    char **prr;
    size_t len_word = count_word(s, c);

    if (!s || !len_word)
        return NULL;

    prr = (char **)calloc((len_word + 1), sizeof(char *));
    if (prr == NULL)
        return NULL;

    while (j < len_word) {
        while (is_separator(s[i], c) && s[i])
            i++;
        if (s[i]) {
            prr[j] = ft_strsdup(s, &i, c);
            if (!prr[j]) {
                ft_free(prr);
                return NULL;
            }
        }
        j++;
    }
    return prr;
}
