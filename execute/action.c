/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatturan <fa.betulturan@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:13:36 by kpolatci          #+#    #+#             */
/*   Updated: 2024/02/24 14:07:17 by fatturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_args_fill(t_execute *execute)
{
	char	**args;
	int		i;
	int		arg_count;

	i = 1;
	arg_count = ft_exec_count(execute);
	args = (char **)malloc(sizeof(char *) * (arg_count + 1));
	args[0] = ft_strdup(execute->value);
	execute = execute->next;
	while (i < arg_count && execute)
	{
		args[i] = ft_strdup(execute->value);
		execute = execute->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}


int	ft_redi_outputs(t_command *cmd)
{
	t_redirect	*redirect;
	int			check;

	check = -1;
	redirect = cmd->redirect;
	while (redirect)
	{
		if (redirect->type == IN_FILE)
			check = ft_output(redirect->value, IN_FILE);
		else if (redirect->type == OUT_FILE)
			check = ft_input(redirect->value);
		else if (redirect->type == D_IN_FILE)
			check = ft_output(redirect->value, D_IN_FILE);
		else if (redirect->type == D_OUT_FILE)
			//dup2(cmd->heredoc_fd[0], 0);
		if (check == 0)
			return (0);
		redirect = redirect->next;
	}
	return (1);
}


void	ft_pipe_route(t_command *cmd)
{
	if (cmd->prev == NULL)
		dup2(cmd->fd[1], 1);
	else if (cmd->next == NULL)
		dup2(cmd->prev->fd[0], 0);
	else
	{
		dup2(cmd->prev->fd[0], 0);
		dup2(cmd->fd[1], 1);
	}
}

void	ft_command_route(t_command *cmd)
{
	if (g_glbl.cmd_count > 1)
	{
		ft_pipe_route(cmd);
	}
	ft_redi_outputs(cmd);
	ft_close_all_fd();
}

void	ft_action(t_command *cmd)
{
	char		*path;
	char		**args;
	pid_t		pid;

	pid = fork();
	if (pid == 0)
	{
		ft_command_route(cmd);
		if (cmd->exec != NULL)
		{
			path = ft_get_path(cmd->exec->value);
			args = ft_args_fill(cmd->exec);
		}
		execve(path, args, g_glbl.env);
		if (cmd->exec != NULL)
			ft_command_err(cmd->exec->value);
		exit(1);
	}
	else
		cmd->p_pid = pid;
}