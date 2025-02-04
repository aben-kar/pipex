#include "pipex.h"

int	count_word(char const *s1, char sp)
{
	int	i;
	int	count;
	int	check;

	i = 0;
	count = 0;
	check = 1;
	while (s1[i])
	{
		if (s1[i] != sp && check == 1)
		{
			count += 1;
			check = 0;
		}
		else if (s1[i] == sp)
			check = 1;
		i++;
	}
	return (count);
}

char	*ft_strsdup(char const *s, size_t *j, char sp)
{
	char	*result;
	size_t	i;
	size_t	k;

	i = *j;
	while (s[*j] != sp && s[*j])
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

char **ft_split(char const *s, char c) {
    size_t j;
    size_t i;

	j = 0;
	i = 0;
    char **prr;
    size_t len_word = count_word(s, c);
    if (!s || !len_word)
        return NULL;
    prr = (char **)ft_calloc((len_word + 1), sizeof(char *));
    if (prr == NULL)
        return NULL;
    while (j < len_word) {
        while (s[i] == c && s[i])
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

char **get_path_directories(char **envp) {
    while (*envp) {
        char *found = ft_strnstr(*envp, "PATH=", 5);
        if (found) {
            char **split_path = ft_split(found + 5, ':');
            if (!split_path)
                return (NULL);
            return split_path;
        }
        envp++;
    }
    return (NULL);
}
