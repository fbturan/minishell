/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatturan <fa.betulturan@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:56:23 by fatturan          #+#    #+#             */
/*   Updated: 2024/02/18 15:20:52 by fatturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command *ft_check_n(t_command *cmd, int *flag)
{
	int	i;

	while(cmd != NULL)
	{
		i = 0;
		while(cmd->exec->value[i])
		{
			if (i == 0 && cmd->exec->value[0] != '-')
				break;
			else if (i != 0 && cmd->exec->value[i] != 'n')
				break;
			i++;
		}
		if (cmd->exec->value[i] == '\0')
			*flag = 1;
		if(cmd->exec->value[i])
			return(cmd);
		cmd = cmd->next;
	}
	return(cmd);
}

void	ft_echo(t_command *cmd)
{
	int	flag;

	flag = 0;
	
		cmd = ft_check_n(cmd->next, &flag);
	if (cmd != NULL)
	{
		while (cmd != NULL && cmd->exec->value)
		{
			printf("%s", cmd->exec->value);
			cmd = cmd->next;
		}
		if (!flag)
			printf("\n");
	}
}