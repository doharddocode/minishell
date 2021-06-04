#include "minishell.h"

t_envp	*ft_get_envp_node(t_envp *envp, char *key)
{
	if (!key)
		return (NULL);
	while (envp)
	{
		if (!ft_strncmp(envp->key, key, ft_strlen(envp->key))
			&& ft_strlen(envp->key) == ft_strlen(key))
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}

int ft_envp_update_node(t_envp *envp, char *key, char *new_value)
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
			if (!envp->value)
				return (ERROR);
		}
		envp = envp->next;
	}
	return (SUCCESS);
}

t_envp *ft_envp_new_node(char **result)
{
	t_envp *node;

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
	char **result;

	i = 0;
	if (!envp)
		return (ERROR);
	mini->envp = NULL;
	while (envp[i])
	{
		result = ft_split(envp[i], '=');
		if (!result)
			return (ERROR);
		ft_envp_addback_node(&mini->envp, ft_envp_new_node(result));
		i++;
//		ft_free_arr(result);
	}
	return (SUCCESS);
}

int is_env_exist(t_envp *envp, char *var_name)
{
	if (!var_name)
		return (ERROR);
	while (envp)
	{
		if (!ft_strncmp(envp->key, var_name, ft_strlen(envp->key))
			&& ft_strlen(envp->key) == ft_strlen(var_name))
		{
			return (1);
		}
		envp = envp->next;
	}
	return (0);
}
