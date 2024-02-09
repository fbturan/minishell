/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatturan <fa.betulturan@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:56:57 by fatturan          #+#    #+#             */
/*   Updated: 2024/01/30 15:00:59 by fatturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp1(char *tmp, char *value, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (tmp[i] != value[i])
			return (0);
		i++;
	}
	if (tmp[i])
		return (0);
	return (1);
}

char	*ft_before_equal(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	tmp = malloc(sizeof(char) * i + 1);
	while (str[j] && str[j] != '=')
	{
		tmp[j] = str[j];
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

void	ft_del_exp(char *value)
{
	int		i;
	char	*tmp;

	i = 0;
	while (g_glbl.export[i])
	{
		tmp = ft_before_equal(g_glbl.export[i]);
		if (ft_strncmp1(tmp, value, ft_strlen(value)))
		{
			free (g_glbl.export);
			while (g_glbl.export[i])
			{
				g_glbl.export[i] = g_glbl.export[i + 1];
				i++;
 			}
			free (tmp);
			return ;
		}
	}
}

void	ft_del_env(char *value)
{
	int		i;
	char	*tmp;

	i = 0;
	while (g_glbl.env[i])
	{
		tmp = ft_before_equal(g_glbl.env[i]);
		if (ft_strncmp(tmp, value, ft_strlen(value)))
		{
			free (g_glbl.env);
			while (g_glbl.env[i])
			{
				g_glbl.env[i] = g_glbl.env[i + 1];
				i++;
 			}
			free (tmp);
			return ;
		}
	}
}

void	ft_unset(t_command *cmd)
{
	t_execute	*exec;

	exec = cmd->exec;
	exec = exec->next;
	while (exec)
	{
		if (ft_check_err(exec->value, "unset"))
			break;
		ft_del_env(exec->value);
		ft_del_exp(exec->value);
		exec = exec->next;
	}
}