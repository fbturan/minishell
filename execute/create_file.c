/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolatci <kpolatci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:47:54 by kpolatci          #+#    #+#             */
/*   Updated: 2024/02/20 18:48:05 by kpolatci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_output(char *file, int mode)
{
	int	fd;

	fd = 0;
	if (mode == IN_FILE)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else if (mode == D_IN_FILE)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
	{
		perror("minishell");
		if (is_parent())
		{
			//g_glbl.erorno = 1;
			return (0);
		}
		else
			//exit(errno);
			exit(1);
	}
	dup2(fd, 1);
	close(fd);
	return (1);
}

int	ft_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		if (is_parent())
		{
			//g_glbl.erorno = 1;
			return (0);
		}
		else
			exit(1);
	}
	dup2(fd, 0);
	close(fd);
	return (1);
}