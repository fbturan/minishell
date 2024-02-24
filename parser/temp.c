/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatturan <fa.betulturan@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 20:41:49 by kpolatci          #+#    #+#             */
/*   Updated: 2024/02/24 13:10:56 by fatturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_split(char **str)
{
	int	index;

	index = 0;
	if (!(*str))
		return ;
	while (str[index] != NULL)
	{
		printf("%s\n", str[index]);
		index++;
	}
}

void	ft_printlist(t_parser *parser)
{
	while (parser != NULL)
	{
		if (!parser->prev)
			printf("(null)");
		if ((parser->prev))
			printf("prev: %s			", parser->prev->str);
		printf("kendisi: %s 			\n", parser->str);
		parser = parser->next;
	}
}

void	ft_error(void)
{
	printf("Error!");
	exit(1);
}

void	ft_free_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
