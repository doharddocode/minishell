#include "minishell.h"

void free_envp_list(t_minishell *mini)
{
	while (mini->envp)
	{
		ft_free_str(mini->envp->key);
		ft_free_str(mini->envp->value);
		mini->envp = mini->envp->next;
	}
	free(mini->envp);
	mini->envp = NULL;
}

void free_history(t_minishell *mini)
{
	ft_lstclear(&mini->work_history, free);
}

void free_arg_item(t_minishell *mini)
{
	while (mini->arg_item)
	{
		ft_free_str(mini->arg_item->name);
		mini->arg_item = mini->arg_item->next;
	}
	free(mini->arg_item);
	mini->arg_item = NULL;
}