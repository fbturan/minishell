#include "../minishell.h"

void	ft_pwd(void)
{
	char	buffer[OPEN_MAX];

	getcwd(buffer, OPEN_MAX);
	printf("%s\n", buffer);
}