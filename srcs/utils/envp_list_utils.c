#include "minishell.h"

t_envp *ft_envp_new_node(char *var)
{
	t_envp *node;
	char **result;

	result = ft_split(var, '=');
	node = (t_envp *)malloc(sizeof(t_envp));
	if (!node || !result)
		return (NULL);
	if (result[0])
		node->key = result[0];
	else
		node->key = NULL;
	if (result[1])
		node->value = result[1];
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

t_envp *ft_envp_last_node(t_envp *envp)
{
	while (envp && envp->next)
		envp = envp->next;
	return (envp);
}

void ft_envp_addback_node(t_envp **envp, t_envp *new_node)
{
	t_envp *last_node;

	last_node = ft_envp_last_node(*envp);
	if (last_node)
		last_node->next = new_node;
	else
		*envp = new_node;
	new_node->next = NULL;
}

int ft_cpy_env(t_minishell *mini, char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (ERROR);
	mini->envp = NULL;
	while (envp[i])
	{
		ft_envp_addback_node(&mini->envp, ft_envp_new_node(envp[i]));
		i++;
	}
	return (SUCCESS);
}
