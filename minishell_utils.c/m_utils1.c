#include "minishell.h"

static void	*ft_memset(void *b, int c, int len)
{
	int			i;
	unsigned char	*a;

	a = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		a[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

static void	ft_bzero(void *s, int n)
{
	ft_memset(s, 0, n);
}

static void	*ft_calloc(int count, int size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (0);
	ft_bzero(ptr, size * count);
	return (ptr);
}

static int	str_in_array(const char *s, char delimiter)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == delimiter)
			s++;
		else
		{
			while (*s != delimiter && *s)
				s++;
			count++;
		}
	}
	return (count);
}

char	**ft_split(char *s, char c)
{
	char			**arr;
	int	j;
	int	a;

	if (!s)
		return (NULL);
	arr = (char **) ft_calloc(str_in_array(s, c) + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	a = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			j = 0;
			while (*s != c && *s && ++j)
				s++;
			arr[++a -1] = (char *) ft_calloc(j + 1, sizeof(char));
			ft_strlcpy(arr[a -1], s - j, j + 1);
		}
	}
	return (arr);
}