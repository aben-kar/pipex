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