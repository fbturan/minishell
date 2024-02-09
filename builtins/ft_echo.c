/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatturan <fa.betulturan@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:56:23 by fatturan          #+#    #+#             */
/*   Updated: 2023/12/18 16:56:25 by fatturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parser *ft_check_n(t_parser *main, int *flag)
{
	int	i;

	while(main != NULL)
	{
		i = 0;
		while(main->str[i])
		{
			if (i == 0 && main->str[0] != '-')
				break;
			else if (i != 0 && main->str[i] != 'n')
				break;
			i++;
		}
		if (main->str[i] == '\0')
			*flag = 1;
		if(main->str[i])
			return(main);
		main = main->next;
	}
	return(main);
}

void	ft_echo(t_parser *main)
{
	int	flag;

	flag = 0;
	
		main = ft_check_n(main->next, &flag);
	if (main != NULL)
	{
		while (main != NULL && main->type != PIPE)
		{
			printf("%s", main->str);
			main = main->next;
		}
		if (!flag)
			printf("\n");
	}
}