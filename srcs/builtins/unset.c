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
	mini->arg_item = mini->arg_item->next;
	if (mini->arg_item)
		delete_env(mini, mini->arg_item->name);
	return (SUCCESS);
}
