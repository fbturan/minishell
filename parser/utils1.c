/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolatci <kpolatci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:01:06 by kpolatci          #+#    #+#             */
/*   Updated: 2023/10/23 23:08:14 by kpolatci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pass_whitespaces(char *str, int *index)
{
	while (((str[*index] >= 9 && str[*index] <= 13) || str[*index] == 32)
		&& str[*index])
		(*index)++;
}

void	pass_quotes(char *str, int *index, char c)
{
	(*index)++;
	while (str[*index] != c && str[*index])
		(*index)++;
	if (str[*index])
		(*index)++;
}

void	pass_redirection(char *str, int *index, int *count)
{
	if (ft_find_str(str, ">>", index) || ft_find_str(str, "<<", index))
		(*count)++;
	else if (ft_find_str(str, ">", index) || ft_find_str(str, "<", index))
		(*count)++;
	else if (ft_find_str(str, "|", index))
		(*count)++;
}

void	pass_word(char *str, int *index, int *count)
{
	if (ft_is_redirection(str[*index]))
		pass_redirection(str, index, count);
	else if (ft_is_quotes(str[*index]))
	{
		pass_quotes(str, index, str[*index]);
		if (ft_is_redirection(str[*index])
			|| ft_is_whitespaces(str[*index]) || !str[*index])
		{
			(*count)++;
			return ;
		}
		pass_word(str, index, count);
	}
	else
	{
		while (!ft_is_whitespaces(str[*index]) && !ft_is_quotes(str[*index])
			&& !ft_is_redirection(str[*index]) && str[*index])
			(*index)++;
		if (ft_is_quotes(str[*index]))
		{
			pass_word(str, index, count);
			return ;
		}
		(*count)++;
	}
}

int	ft_argc_count(char *str)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	pass_whitespaces(str, &index);
	while (str[index])
	{
		pass_word(str, &index, &count);
		pass_whitespaces(str, &index);
	}
	return (count);
}
