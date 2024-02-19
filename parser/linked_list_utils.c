/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatturan <fa.betulturan@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 22:04:53 by kpolatci          #+#    #+#             */
/*   Updated: 2024/02/19 13:07:07 by fatturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parser	*ft_nodelast(t_parser	*pars)
{
	while (pars != NULL && pars->next != NULL)
		pars = pars->next;
	return (pars);
}

void	ft_nodeadd_back(t_parser **pars, t_parser *new)
{
	if (*pars == NULL)
	{
		*pars = new;
		return ;
	}
	ft_nodelast(*pars)->next = new;
}

t_parser	*ft_nodenew(char *str)
{
	t_parser	*new;

	new = (t_parser *)malloc(sizeof(t_parser));
	if (!new)
		return (NULL);
	new->str = str;
	new->next = NULL;
	return (new);
}

t_parser	*ft_createnodes(char **str)
{
	t_parser	*parser;
	int			index;

	index = -1;
	parser = NULL;
	while (str[++index])
		ft_nodeadd_back(&parser, ft_nodenew(ft_strdup(str[index])));
	ft_add_prev_parser(parser);
	return (parser);
}

void	ft_add_prev_parser(t_parser	*parser)
{
	t_parser	*temp;

	temp = NULL;
	while (parser)
	{
		parser->prev = temp;
		temp = parser;
		parser = parser->next;
	}
}

int	ft_arg_count(t_execute *exec)
{
	int	len;

	len = 0;
	while (exec->next)
	{
		len++;
		exec = exec->next;
	}
	return (len);
}
