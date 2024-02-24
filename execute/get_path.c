/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatturan <fa.betulturan@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:00:34 by kpolatci          #+#    #+#             */
/*   Updated: 2024/02/24 14:08:57 by fatturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_no_file_err(t_command *cmd)
{
	printf("file not found: error");
	exit(1);
}

void	ft_command_err(char *cmd)
{
	printf("command not found: error");
	exit(1);
}

void	ft_check_dir(char *command)
{
	DIR	*dir;

	if (!command)
		exit(EXIT_SUCCESS);
	dir = opendir(command);
	if (dir && readdir(dir))
	{
		closedir(dir);
		directory_err(command);
	}
}

char	*get_path(char *cmd)
{
	char	*path;
	char	**paths;
	char	*new_cmd;

	ft_check_dir(cmd);
	if (ft_is_equal(cmd, "export") || ft_is_equal(cmd, "unset"))
		exit(EXIT_SUCCESS);
	if (!access(cmd, F_OK) && ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	paths = g_glbl.path;
	if (!paths)
		ft_command_err(cmd);
	new_cmd = ft_strjoin("/", cmd);
	while (*paths)
	{
		path = ft_strjoin(*paths, new_cmd);
		if (!access(path, F_OK))
			return (path);
		free(path);
		paths++;
	}
	if (ft_strchr(cmd, '/'))
		ft_no_file_err(cmd);
	free(new_cmd);
	return (NULL);
}
