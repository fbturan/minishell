/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolatci <kpolatci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:33:40 by kpolatci          #+#    #+#             */
/*   Updated: 2024/01/04 16:32:45 by kpolatci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_whitespaces(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_is_quotes(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	ft_is_redirection(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	ft_find_str(char *str, char *c, int *index)
{
	int	temp;
	int	j;

	j = 0;
	temp = *index;
	while (str[*index] == c[j] && c[j])
	{
		(*index)++;
		j++;
	}
	if (!c[j])
		return (1);
	*index = temp;
	return (0);
}

char	*ft_substr(char *str, int start, int end)
{
	char	*sub;
	int		index;

	index = 0;
	if (end >= ft_strlen(str))
		return (0);
	sub = (char *)malloc(sizeof(char) * end - start + 2);
	sub[end - start + 1] = '\0';
	while (start <= end)
		sub[index++] = str[start++];
	return (sub);
}
