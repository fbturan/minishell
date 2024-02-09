/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolatci <kpolatci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 06:01:34 by kpolatci          #+#    #+#             */
/*   Updated: 2024/01/04 16:32:45 by kpolatci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_for_env(char *str)
{
	int	len;
	int	index;

	index = 0;
	len = 0;
	while (str[index])
	{
		if (str[index] == '\'')
			count_for_single_quo(str, str[index], &index, &len);
		else if (str[index] == '\"')
			count_for_double_quo(str, str[index], &index, &len);
		else if (str[index] == '$')
			count_dollar(str, &index, &len);
		else
		{
			index++;
			len++;
		}
	}
	return (len);
}

void	count_dollar(char *str, int *index, int *len)
{
	char	*new_str;

	new_str = dollar_substr(str, *index);
	new_str = dollar_value(new_str, g_glbl.env);
	(*len) += ft_strlen(new_str);
	(*index)++;
	while (!is_special_char(str[*index]) && str[*index])
		(*index)++;
}

void	count_for_single_quo(char *str, char c, int *index, int *len)
{
	int	temp;

	if (c == '\'')
	{
		temp = *index;
		pass_quotes(str, index, c);
		(*len) += (*index) - temp;
	}
}

void	count_for_double_quo(char *str, char c, int *index, int *len)
{
	if (c == '\"')
	{
		(*index)++;
		(*len)++;
		while (str[*index] != '\"' && str[*index])
		{
			if (str[*index] == '$')
				count_dollar(str, index, len);
			if (str[*index] != '\"')
			{
				(*index)++;
				(*len)++;
			}
		}
		(*index)++;
		(*len)++;
	}
}
