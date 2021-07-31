#include "minishell.h"

void	free_envp_list(t_minishell *mini)
{
	t_envp	*tmp;

	while (mini->envp)
	{
		tmp = mini->envp;
		mini->envp = mini->envp->next;
		ft_free_str(tmp->key);
		ft_free_str(tmp->value);
		free(tmp);
	}
	mini->envp = NULL;
}

void	free_history(t_minishell *mini)
{
	ft_lstclear(&mini->work_history, free);
}

void	free_arg_item(t_minishell *mini)
{
	t_arg_item	*tmp;

	while (mini->arg_item)
	{
		tmp = mini->arg_item;
		mini->arg_item = mini->arg_item->next;
		ft_free_str(tmp->name);
		free(tmp);
	}
	mini->arg_item = NULL;
}

int	ft_envp_update_node(t_envp *envp, char *key, char *new_value)
{
	if (!new_value)
		return (ERROR);
	while (envp)
	{
		if (!ft_strncmp(envp->key, key, ft_strlen(envp->key))
			&& ft_strlen(envp->key) == ft_strlen(key))
		{
			ft_free_str(envp->value);
			envp->value = ft_strinit(ft_strlen(new_value), new_value);
			if (envp->value)
				return (ERROR);
		}
		envp = envp->next;
	}
	return (SUCCESS);
}
