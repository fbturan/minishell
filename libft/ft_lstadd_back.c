/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatturan <fa.betulturan@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 03:31:06 by fatturan          #+#    #+#             */
/*   Updated: 2023/07/13 08:59:05 by fatturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*iter;

	iter = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (iter->next)
	{
		iter = iter->next;
	}
	iter->next = new;
}
