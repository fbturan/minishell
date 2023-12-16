/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatturan <fa.betulturan@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 18:07:58 by fatturan          #+#    #+#             */
/*   Updated: 2023/07/13 09:50:53 by fatturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_block;
	t_list	*new_list;

	if (!lst)
		return (0);
	new_list = 0;
	while (lst)
	{
		new_block = ft_lstnew(f(lst -> content));
		if (new_block == 0)
		{
			ft_lstclear(&new_list, del);
			return (0);
		}
		ft_lstadd_back(&new_list, new_block);
		lst = lst -> next;
	}
	return (new_list);
}
