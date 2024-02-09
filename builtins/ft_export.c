 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatturan <fa.betulturan@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:56:47 by fatturan          #+#    #+#             */
/*   Updated: 2023/12/25 16:18:53 by fatturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_equal(char *env, char *exp)
{
	int	i;
	int	j;

	if (!env)
		return (0);
	i = 0;
	j = 0;
	while (env[i])
	{

	}

}

int	ft_if_equal(char **new, int *i, char *value, char *flag)
{
	char	**env;
	char	**value;

	env = ft_split(new[*i], '=');
	value = ft_split(value, '=');
	if (ft_is_equal(env[0], value[0]))
	{
		free(new[*i]);
		new[*i] = ft_strdup(value);
		if (flag == "env")
			return (1);
		else if (flag == "export")
			return (2);
	}
	ft_free_2D(env);
	ft_free_2D(value);
}

void	ft_add_exp(char **new_exp, char *value)
{
	int	i;
	int	check;

	i = -1;
	while (g_glbl.export[++i])
	{
		new_exp[i] = ft_strdup(g_glbl.export[i]);
		check = ft_if_equal(new_exp, &i, value, "export");
	}
	if (check == 1)
		new_exp[i] = NULL;
	else if (check != 1)
	{
		new_exp[i] = ft_strdup(value);
		new_exp[i + 1] = NULL;
	}
	ft_free_2D(g_glbl.export);
	g_glbl.export = new_exp;
}

void	ft_add_env(char **new_env, char *value)
{
	int	i;
	int	check;

	i = -1;
	while (g_glbl.env[++i])
	{
		new_env[i] = ft_strdup(g_glbl.env[i]);
		check = ft_if_equal(new_env, &i, value, "env");
	}
	if (check == 1)
		new_env[i] = NULL;
	else if (check != 1)
	{
		new_env[i] = ft_strdup(value);
		new_env[i + 1] = NULL;
	}
	ft_free_2D(g_glbl.env);
	g_glbl.env = new_env;
}

int	ft_exp_count(void)
{
	int	len;

	len = 0;
	while(g_glbl.export[len])
		len++;
	return (len);
}

void	ft_add_to(char *value, char *flag)
{
	char	**new;

	new = malloc(sizeof(char *) * (ft_exp_count() + 2));
	if (flag == "export")
		ft_add_exp(new, value);
	else if (flag == "env")
		ft_add_env(new, value);
}

void	ft_env_or_exp(t_execute *exec)
{
	if (ft_strchr(exec->value, '=') == NULL)
		ft_add_to(exec->value, "export");
	else
		ft_add_to(exec->value, "env");
}

int	ft_check_err(char *value, char *flag)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (value[i])
	{
		if (!(value[i] >= 'A' && value[i] <= 'Z') && !(value[i] >= 'a' && value[i] <= 'z')
			&& !(value[i] >= '0' && value[i] <= '9') && value[i]
			&& value[i] != '=' && value[i] != '_' && value[i] != '//')
			flag = 1;
		if (value[i - 1] == '+' && value[i] == '=')
		{
			g_glbl.exp_plus_flag = 1;
			flag = 0;
		}
		if (((value[0] >= 'A' && value[0] <= 'Z') && !(value[0] >= 'a' && value[0] <= 'z')
			|| value[0] == '_') && flag == 0)
			return (0);
		printf("minishell: %s: '%s': not a valid indentifier\n", flag, value);
		return (1);
	}
}

int	ft_exec_count(t_execute *exec)
{
	int	len;

	len = 0;
	while (exec)
	{
		len++;
		exec = exec->next;
	}
	return (len);
}

static void	ft_print_export(void)
{
	int		i;
	char	**arg;

	i = 0;
	while (g_glbl.export[i])
	{
		arg = ft_split(g_glbl.export[i], '=');
		if (arg[1] == NULL && ft_strchr(g_glbl.export[i], '='))
			printf("declare -x %s=\"\"\n", arg[0]);
		else if (arg[1] == NULL)
			printf("declare -x %s\n", arg[0]);
		else
			printf("declare -x %s=\"%s\"\n", arg[0], arg[1]);
		i++;
	}
		ft_free_2D(arg);
}

void	ft_export(t_command *command) //neden exec almadık da cmd aldık = norm
{
	t_execute	*exec;

	exec = command->exec;
	if (ft_exec_count(exec) == 1)
		ft_print_export();
	else
	{
		exec = exec->next;
		while(exec)
		{
			if (ft_check_err(exec->value, "export"))
			{
				exec = exec->next;
				continue;
			}
			else
				ft_env_or_exp(exec);
			exec = exec->next;
		}
	}
}