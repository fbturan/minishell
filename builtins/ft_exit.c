#include "../minishell.h"
#include "../libft/libft.h"

static int	ft_exit_nbr(char *str)
{
	while (*str)
	{
		if ((ft_isdigit(*str)) || (*str == '+') || (*str == '-'))
			*str++;
		return (0);
	}
	return (1); 
}

//3 durum var sadece exit yazılması 2den fazla arg olması non-numeric olma durumu
void	ft_exit(t_parser *main)
{
	if (ft_arg_count(main) == 1)
		//globalli falan
		main->next;//öylesine
	else if (ft_arg_count(main) > 2)
	{
		ft_putendl_fd("exit\n exit: too many arguments", 2);
		//errno = 1;
		return ;
	}
	else
	{
		if (ft_exit_nbr(main->next->str))
		{
			ft_putendl_fd("exit\n", 1);
			exit(ft_atoi(main->next->str) % 256);
		}
		ft_putendl_fd("exit\n exit: numeric argument required\n", 2);
		exit(-1 % 256);
	}
}