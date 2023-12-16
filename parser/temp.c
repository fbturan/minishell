/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolatci <kpolatci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 20:41:49 by kpolatci          #+#    #+#             */
/*   Updated: 2023/12/15 02:24:32 by kpolatci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_split(char **str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		printf("%s\n", str[index]);
		index++;
	}
}

void	ft_printlist(t_parser *parser)
{
	while (parser != NULL)
	{
		printf("%s   => Type: %d\n", parser->str, parser->type);
		parser = parser->next;
	}
}

void	ft_error(void)
{
	printf("Error!");
	exit(1);
}
