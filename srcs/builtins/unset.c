#include "minishell.h"

static	void delete_env(t_minishell *mini, char *var_name)
{
	t_envp *node;

	if (is_env_exist(mini->envp, var_name))
	{
		node = ft_get_envp_node(mini->envp, var_name);
		if (node)
			mini->envp = ft_delete_envp_node(mini->envp, node);
	}
}

int ft_unset(t_minishell *mini)
{
	mini->args = mini->args->next;
	if (mini->args)
		delete_env(mini, mini->args->content);
	return (mini->ret = SUCCESS);
}