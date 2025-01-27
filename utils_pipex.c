#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}


void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*s;
	size_t			i;

	i = 0;
	if (size != 0 && (count > SIZE_MAX / size))
		return (NULL);
	s = (unsigned char *)malloc(count * size);
	if (s == NULL)
		return (NULL);
	while (i < count * size)
	{
		s[i] = 0;
		i++;
	}
	return (s);
}
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (dst == NULL && src == NULL)
		return (NULL);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*concate;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	concate = (char *)ft_calloc((len_s1 + len_s2 + 1), sizeof(char));
	if (concate == NULL)
		return (NULL);
	ft_memcpy(concate, s1, len_s1);
	ft_memcpy(concate + len_s1, s2, len_s2);
	return (concate);
}

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

void	*ft_free(char **prr)
{
	int	i;

	i = 0;
	while (prr[i])
	{
		free(prr[i]);
		i++;
	}
	free(prr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	j;
	size_t	i;
	char	**prr;
	size_t	len_word;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	len_word = count_word(s, c);
	prr = (char **)ft_calloc((len_word + 1), sizeof(char *));
	if (prr == NULL)
		return (NULL);
	while (j < len_word)
	{
		while (s[i] == c && s[i])
			i++;
		prr[j] = ft_strsdup(s, &i, c);
		if (!prr[j])
			return (ft_free(prr));
		j++;
	}
	return (prr);
}
char	*ft_strnstr(const char *str, const char *find, size_t n)
{
	size_t	i;
	size_t	j;

	if (*find == '\0')
		return ((char *)str);
	i = 0;
	while (str[i] && i < n)
	{
		j = 0;
		while (find[j] && str[i + j] == find[j] && (i + j) < n)
			j++;
		if (find[j] == '\0')
			return ((char *)(&str[i]));
		i++;
	}
	return (NULL);
}