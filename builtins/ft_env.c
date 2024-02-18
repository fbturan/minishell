/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatturan <fa.betulturan@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:56:27 by fatturan          #+#    #+#             */
/*   Updated: 2024/02/18 18:08:23 by fatturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_execute *exec)
{
	int		i;
	char	**tmp;

	i = 0;
	while (g_glbl.env[i])
	{
		tmp = ft_split(g_glbl.env[i], '=');
		if (tmp[0] && tmp[1])
			printf("%s=\"%s\"\n", tmp[0], tmp[1]);
		if (!tmp[1])
			printf("%s\"\"\n", tmp[0]);
		i++;
		ft_free_2D(tmp);
	}
}
