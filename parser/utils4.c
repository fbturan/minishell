/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolatci <kpolatci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 06:28:38 by kpolatci          #+#    #+#             */
/*   Updated: 2024/02/20 18:11:50 by kpolatci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_quo_pars(t_parser *pars)
{
	while (pars != NULL)
	{
		pars->str = ft_removed(pars->str);
		pars = pars->next;
	}
}

char	*ft_removed(char *str)
{
	char	*new_str;
	char	*p;
	char	c;

	new_str = (char *)malloc(ft_count_for_rem(str) + 1);
	p = new_str;
	while (*str)
	{
		if ((*str) == '\'' || (*str) == '\"')
		{
			c = (*str);
			str++;
			while ((*str) && (*str) != c)
				(*p++) = (*str++);
			if (*str)
				str++;
		}
		else
			(*p++) = (*str++);
	}
	(*p) = '\0';
	return (new_str);
}

int	ft_count_for_rem(char *str)
{
	int	index;
	int	len;

	index = 0;
	len = 0;
	while (str[index])
	{
		if (str[index] == '\'' || str[index] == '\"')
		{
			len++;
			pass_quotes(str, &index, str[index]);
		}
		else
			index++;
	}
	return (ft_strlen(str) - (len * 2));
}

void	determine_type(t_parser *pars)
{
	if (!pars)
		return ;
	while (pars != NULL)
	{
		if (pars->str[0] == '>' && pars->str[1] == '>' && !(pars->str[2]))
			pars->type = D_OUTPUT_R;
		else if (pars->str[0] == '<' && pars->str[1] == '<' && !(pars->str[2]))
			pars->type = D_INPUT_R;
		else if (pars->str[0] == '>' && !(pars->str[1]))
			pars->type = OUTPUT_R;
		else if (pars->str[0] == '<' && !(pars->str[1]))
			pars->type = INPUT_R;
		else if (pars->str[0] == '|' && !(pars->str[1]))
			pars->type = PIPE;
		else
			pars->type = ARG;
		pars = pars->next;
	}
}
