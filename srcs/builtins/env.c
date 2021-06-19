#include "minishell.h"

int ft_env(t_minishell *mini)
{
	print_envp_list(mini->envp, NULL);
	return (mini->ret = SUCCESS);
}