/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boxing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolatci <kpolatci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:32:45 by fatturan          #+#    #+#             */
/*   Updated: 2024/02/20 17:52:12 by kpolatci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_send_box(t_command *cmd, t_parser **main)
{
	if ((*main)->type == ARG)
		cmd->exec = ft_exec_box(&cmd->exec, *main);
	else if ((*main)->type == OUTPUT_R || (*main)->type == INPUT_R)
		cmd->redirect = ft_redirect_box(&cmd->redirect, *main);
	else if ((*main)->type == D_OUTPUT_R || (*main)->type == D_INPUT_R)
		cmd->redirect = ft_redirect_box(&cmd->redirect, *main);
}

void	ft_add_box(t_command *cmd)
{
	t_command	*tmp;

	tmp = g_glbl.cmd;
	if (!(tmp))
		g_glbl.cmd = cmd;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cmd;
		cmd->prev = tmp;
	}
}

t_command	*ft_init_cmd(void)
{
	t_command	*new_cmd;

	new_cmd = calloc(sizeof(t_command), 1);
	new_cmd->prev = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	ft_cmd_box(t_parser *main)
{
	t_command	*cmd;

	cmd = NULL;
	g_glbl.cmd = NULL;
	g_glbl.cmd_count = 0;
	while (main)
	{
		if (main->type == PIPE || main->prev == NULL)
		{
			if (main->type == PIPE)
				main = main->next;
			cmd = ft_init_cmd();
			ft_add_box(cmd);
			g_glbl.cmd_count += 1;
		}
		ft_send_box(cmd, &main);
		main = main->next;
	}
}
