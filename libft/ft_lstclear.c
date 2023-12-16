/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatturan <fa.betulturan@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:31:00 by fatturan          #+#    #+#             */
/*   Updated: 2023/07/13 09:04:46 by fatturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*iter;

	if (lst)
	{
		while (*lst)
		{
			iter = (*lst)->next;
			ft_lstdelone(*lst, del);
			(*lst) = iter;
		}
	}
}
