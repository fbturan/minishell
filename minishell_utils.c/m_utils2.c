#include "minishell.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (!*(s + i))
			return (0);
		i++;
	}
	return ((char *)(s + i));
}
