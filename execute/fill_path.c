/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatturan <fa.betulturan@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:28:48 by kpolatci          #+#    #+#             */
/*   Updated: 2024/02/24 13:36:37 by fatturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_split_path(char *env_path)
{
	while (*env_path != '=')
		env_path++;
	env_path++;
	return (ft_strdup(env_path));
}

char	*ft_env_path(char *path)
{
	int		i;
	size_t	len;
	char	**env;

	env = g_glbl.env;
	len = ft_strlen(path);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], path, len))
		{
			free(path);
			return (ft_split_path(env[i]));
		}
		i++;
	}
	free(path);
	return (ft_calloc(sizeof(char *), 1));
}

void	ft_fill_path(void)
{
	char	*path;

	path = NULL;
	if (g_glbl.path)
		ft_free_2d(g_glbl.path);
	path = ft_env_path("PATH=");
	if (!(*path))
		g_glbl.path = NULL;
	else
		g_glbl.path = ft_split(path, ':');
	free(path);
}
