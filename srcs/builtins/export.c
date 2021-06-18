#include "minishell.h"

static void add_env(t_minishell *mini, char **result)
{
	if (result)
	{
		if (!is_env_exist(mini->envp, result[0]))
			ft_envp_addback_node(&mini->envp,
								 ft_envp_new_node(result[0], result[1]));
		else
			ft_envp_update_node(&mini->envp, result[0], result[1]);
	}
}

int ft_export(t_minishell *mini)
{
	char **result;
	t_list *args;

	args = mini->args->next;
	if (!args)
	{
		sort_envp_list(&mini->envp);
		print_envp_list(mini->envp, "declare -x");
	}
	else
	{
		if (ft_strchr(args->content, '='))
		{
			result = ft_split(args->content, '=');
			add_env(mini, result);
		}
	}
	return (mini->ret = SUCCESS);
}