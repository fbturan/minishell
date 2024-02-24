/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_box.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolatci <kpolatci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:04:49 by fatturan          #+#    #+#             */
/*   Updated: 2024/02/20 18:16:15 by kpolatci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redirect	*ft_last_redirect(t_redirect *redirect)
{
	if (redirect)
	{
		while (redirect->next)
			redirect = redirect->next;
		return (redirect);
	}
	return (0);
}

void	ft_add_redirect_box(t_redirect **redirect, t_redirect *new)
{
	t_redirect	*temp;

	if (redirect)
	{
		if (*redirect == NULL)
			*redirect = new;
		else
		{
			if (*redirect)
				temp = ft_last_redirect(*redirect);
			temp->next = new;
		}
	}
}

t_redirect	*ft_init_redirect_box(enum e_token type, char *str)
{
	t_redirect	*new_redirect;

	new_redirect = calloc(sizeof(t_redirect), 1);
	new_redirect->value = str;
	new_redirect->type = type;
	new_redirect->next = NULL;
	return (new_redirect);
}

t_redirect	*ft_redirect_box(t_redirect **redirect, t_parser *main)
{
	t_redirect	*new_redirect;

	if (main->type == OUTPUT_R && main->next->str)
		new_redirect = ft_init_redirect_box(IN_FILE, main->next->str);
	else if (main->type == INPUT_R && main->next->str)
		new_redirect = ft_init_redirect_box(OUT_FILE, main->next->str);
	else if (main->type == D_INPUT_R && main->next->str)
		new_redirect = ft_init_redirect_box(D_OUT_FILE, main->next->str);
	else if (main->type == D_OUTPUT_R && main->next->str)
		new_redirect = ft_init_redirect_box(D_IN_FILE, main->next->str);
	ft_add_redirect_box(redirect, new_redirect);
	return (*redirect);
}
