#include "minishell.h"

int	ft_pwd(t_minishell *mini)
{
	char	cwd[255];

	(void)mini;
	if (!getcwd(cwd, 255))
		return (1);
	ft_putendl_fd(getcwd(cwd, 255), 1);
	return (SUCCESS);
}
