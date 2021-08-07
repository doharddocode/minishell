#include "minishell.h"

int	ft_env(t_minishell *mini)
{
	if (!is_env_exist(mini->envp, "PATH"))
	{
		item_not_found(mini, "env", "No such file or directory\n");
		return (ERROR);
	}
	print_envp_list(mini->envp, NULL);
	return (SUCCESS);
}
