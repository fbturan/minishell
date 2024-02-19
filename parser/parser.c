/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatturan <fa.betulturan@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 22:24:07 by kpolatci          #+#    #+#             */
/*   Updated: 2024/02/19 14:10:18 by fatturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_single_quote(char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == '\"')
		{
			index++;
			while (str[index] != '\"' && str[index])
				index++;
			if (!str[index])
				return (1);
		}
		if (str[index] == '\'')
		{
			index++;
			while (str[index] != '\'' && str[index])
				index++;
			if (!str[index])
				return (1);
		}
		index++;
	}
	return (0);
}

char	**ft_create_split(char *str)
{
	char	**split;
	int		split_index;
	int		index;
	int		temp;

	split_index = 0;
	index = 0;
	split = (char **)malloc(sizeof(char *) * ft_argc_count(str) + 1);
	pass_whitespaces(str, &index);
	while (str[index])
	{
		temp = index;
		pass_word(str, &index, &temp);
		split[split_index++] = ft_substr(str, temp - 1, index - 1);
		pass_whitespaces(str, &index);
	}
	split[split_index] = 0;
	return (split);
}

void	check_env(t_parser *parser)
{
	while (parser != NULL)
	{
		if (ft_find_char(parser->str, '$'))
			parser->str = create_env(parser->str);
		parser = parser->next;
	}
}

void	init_envair(char **env)
{
	int	i;

	i = ft_strlen_split(env);
	g_glbl.env = malloc(sizeof(char *) * (i + 1));
	g_glbl.export = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		g_glbl.env[i] = ft_strdup(env[i]);
		g_glbl.export[i] = ft_strdup(env[i]);
		i++;
	}
	g_glbl.env[i] = NULL;
	g_glbl.export[i] = NULL;
}

void	ft_process(void)
{
	t_parser	*parser;
	char		**split;
	char		*str;

	//ft_print_split(g_glbl.export);
	while (1)
	{
		str = readline("bash$: ");
		if (ft_is_single_quote(str))
			ft_error();
		split = ft_create_split(str);
		parser = ft_createnodes(split);
		determine_type(parser);
		check_env(parser);
		remove_quo_pars(parser);
		//ft_printlist(parser);
		ft_cmd_box(parser);
		//printf("%d\n", g_glbl.cmd_count);
		ft_process_cmd();
		
		//while (g_glbl.cmd)
		//{
		//	while (g_glbl.cmd->exec)
		//	{
		//		printf("exec:%s\n", g_glbl.cmd->exec->value);
		//		g_glbl.cmd->exec = g_glbl.cmd->exec->next;
		//	}
		//	while (g_glbl.cmd->redirect)
		//	{
		//		printf("redire:%s\n", g_glbl.cmd->redirect->value);
		//		g_glbl.cmd->redirect = g_glbl.cmd->redirect->next;
		//	}
		//	g_glbl.cmd = g_glbl.cmd->next;
		//	printf("bir sonraki pipe		");
		//}
	}
}