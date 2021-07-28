#include "minishell.h"

void free_envp_list(t_minishell *mini)
{
	t_envp *tmp;

	while (mini->envp)
	{
		tmp = mini->envp;
		mini->envp = mini->envp->next;

		ft_free_str(tmp->key);
		ft_free_str(tmp->value);
		free(tmp);
	}
	// free(mini->envp);
	mini->envp = NULL;
}

void free_history(t_minishell *mini)
{
	ft_lstclear(&mini->work_history, free);
}

void free_arg_item(t_minishell *mini)
{
	t_arg_item *tmp;

	while (mini->arg_item)
	{
		tmp = mini->arg_item;
		mini->arg_item = mini->arg_item->next;
		ft_free_str(tmp->name);
		free(tmp);
	}
	// free(mini->arg_item);
	mini->arg_item = NULL;
}
