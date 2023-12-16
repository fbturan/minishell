/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolatci <kpolatci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:47:15 by kpolatci          #+#    #+#             */
/*   Updated: 2023/12/14 06:36:23 by kpolatci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

int	ft_strlen2(char **str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	ft_strlcpy(char *src, char *dst, int size)
{
	int	index;

	index = 0;
	while (index < size)
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;

	join = malloc(sizeof(char *) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (0);
	if (s1)
		ft_strlcpy(s1, join, ft_strlen(s1));
	if (s2)
		ft_strlcpy(s2, join + ft_strlen(s1), ft_strlen(s2));
	free(s1);
	free(s2);
	return (join);
}

char	*ft_strdup(char *str)
{
	char	*dup;

	dup = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!dup)
		return (0);
	ft_strlcpy(str, dup, ft_strlen(str));
	return (dup);
}
