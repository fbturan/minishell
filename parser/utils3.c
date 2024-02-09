/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolatci <kpolatci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:47:15 by kpolatci          #+#    #+#             */
/*   Updated: 2024/01/04 16:40:35 by kpolatci         ###   ########.fr       */
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

int	ft_strlen_split(char **str)
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

char	*ft_strdup(char *str)
{
	char	*dup;

	dup = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!dup)
		return (0);
	ft_strlcpy(str, dup, ft_strlen(str));
	return (dup);
}

int	ft_find_char(char *str, char c)
{
	while ((*str))
	{
		if ((*str) == c)
			return (1);
		str++;
	}
	return (0);
}
