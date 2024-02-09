/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolatci <kpolatci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:35:23 by kpolatci          #+#    #+#             */
/*   Updated: 2024/01/04 16:34:11 by kpolatci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*create_env(char *node_str)
{
	char	*new_env;
	int		new_i;
	int		node_i;

	new_env = malloc(sizeof(char) * count_for_env(node_str) + 1);
	new_i = 0;
	node_i = 0;
	while (node_str[node_i])
	{
		if (node_str[node_i] == '\'' || node_str[node_i] == '\"' ||	
		node_str[node_i] == '$')
			copy_env(node_str, new_env, &new_i, &node_i);
		else
			new_env[new_i++] = node_str[node_i++];
	}
	new_env[new_i] = '\0';
	return (new_env);
}

void	copy_env(char *src, char *dest, int *dest_i, int *src_i)
{
	if (src[*src_i] == '\'')
		copy_env_single_quo(src, dest, dest_i, src_i);
	else if (src[*src_i] == '\"')
		copy_env_double_quo(src, dest, dest_i, src_i);
	else if (src[*src_i] == '$')
		copy_env_dollar(src, dest, dest_i, src_i);
}

void	copy_env_single_quo(char *src, char *dest, int *dest_i, int *src_i)
{
	int		temp;

	if (src[*src_i] == '\'')
	{
		temp = *src_i;
		pass_quotes(src, src_i, src[*src_i]);
		ft_strlcpy(src, (dest + *dest_i), (*src_i) - temp);
		(*dest_i) += (*src_i) - temp;
	}
}

void	copy_env_double_quo(char *src, char *dest, int *dest_i, int *src_i)
{
	if (src[*src_i] == '\"')
	{
		dest[(*dest_i)++] = src[(*src_i)++];
		while (src[*src_i] != '\"' && src[*src_i])
		{
			if (src[*src_i] == '$')
				copy_env_dollar(src, dest, dest_i, src_i);
			dest[(*dest_i)++] = src[(*src_i)++];
		}
		dest[(*dest_i)++] = src[(*src_i)++];
	}
}

void	copy_env_dollar(char *src, char *dest, int *dest_i, int *src_i)
{
	char	*temp_str;

	if (src[*src_i] == '$')
	{
		temp_str = dollar_substr(src, *src_i);
		temp_str = dollar_value(temp_str, g_glbl.env);
		ft_strlcpy(temp_str, (dest + *dest_i), ft_strlen(temp_str));
		(*dest_i) += ft_strlen(temp_str);
		(*src_i)++;
		while (!is_special_char(src[*src_i]) && src[*src_i])
			(*src_i)++;
	}
}