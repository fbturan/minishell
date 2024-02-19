/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatturan <fa.betulturan@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:56:17 by fatturan          #+#    #+#             */
/*   Updated: 2024/02/19 13:04:49 by fatturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export_pwd(char *old_pwd, char *new_pwd)
{
	int	i;

	i = 0;
	while (g_glbl.export[i])
	{
		if (ft_strncmp(g_glbl.export[i], "PWD=", 4) == 0)
		{
			free(g_glbl.export[i]);
			g_glbl.export[i] = ft_strjoin("PWD=", new_pwd);
		}
		if (ft_strncmp(g_glbl.export[i], "OLDPWD=", 7) == 0)
		{
			free(g_glbl.export[i]);
			g_glbl.export[i] = ft_strjoin("OLDPWD=", old_pwd);
		}
		i++;
	}
}

void	ft_env_pwd(char *old_pwd, char *new_pwd)
{
	int	i;

	i = 0;
	while (g_glbl.env[i])
	{
		if (ft_strncmp(g_glbl.env[i], "PWD=", 4) == 0)
		{
			free(g_glbl.env[i]);
			g_glbl.env[i] = ft_strjoin("PWD=", new_pwd);
		}
		if (ft_strncmp(g_glbl.env[i], "OLDPWD=", 7) == 0)
		{
			free(g_glbl.env[i]);
			g_glbl.env[i] = ft_strjoin("OLDPWD=", old_pwd);
		}
		i++;
	}
}

void	ft_cd_error(char *s1, char *s2)
{
	write(2, "error", 5);
}

char	*ft_is_tilde(char *str)
{
	if (!ft_strlen(str) || str[0] != '=' || !getenv("HOME"))
		return (ft_strdup(str));
	str++;
	return (ft_strjoin(getenv("HOME"), str));
}

void	ft_cd_two(t_command *cmd)
{
	char	*tmp;
	char 	new_pwd[OPEN_MAX];
	char 	old_pwd[OPEN_MAX];

	getcwd(old_pwd, OPEN_MAX);
	tmp = ft_is_tilde(cmd->exec->next->value);
	if (chdir(tmp) != 0)
	{
		ft_cd_error(cmd->exec->value, cmd->exec->next->value);
	}
	free(tmp);
	getcwd(new_pwd, OPEN_MAX);
	ft_env_pwd(new_pwd, old_pwd);
	ft_export_pwd(new_pwd, old_pwd);
}

void	ft_cd(t_command *cmd)
{
	char *home;

	if (cmd->exec->next == NULL)
	{
		home = getenv("HOME");
		if (home && *home)
		{
			if (chdir(home))
				perror("minishell");
		}
	}
	ft_cd_two(cmd);
}