#include "minishell.h"

int ft_pwd(t_minishell *mini)
{
	(void)mini;
	char cwd[255];

	if (!getcwd(cwd, 255))
		return (ERROR);
	ft_putendl_fd(getcwd(cwd, 255), 1);
	return (SUCCESS);
}