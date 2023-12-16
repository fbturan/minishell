/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolatci <kpolatci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 22:04:53 by kpolatci          #+#    #+#             */
/*   Updated: 2023/10/23 23:57:37 by kpolatci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parser	*ft_nodelast(t_parser	*pars)
{
	while (pars->next != NULL)
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
	return (parser);
}

int	ft_arg_count(t_parser *main)
{
	int	len;

	len = 0;
	while (main->next)
	{
		len++;
		main = main->next;
	}
	return (len);
}