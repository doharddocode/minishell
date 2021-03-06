#include "minishell.h"

int	ft_cpy_env(t_minishell *mini, char **envp)
{
	int		i;
	int		j;
	char	**result;

	i = 0;
	j = 0;
	if (!envp)
		return (ERROR);
	mini->envp = NULL;
	while (envp[i])
	{
		result = ft_split(envp[i], '=');
		if (!result)
			return (ERROR);
		ft_envp_addback_node(&mini->envp, ft_envp_new_node(result[0],
				result[1]));
		i++;
		free(result[0]);
		free(result[1]);
		free(result);
	}
	return (SUCCESS);
}

int	is_env_exist(t_envp *envp, char *var_name)
{
	if (!var_name)
		return (ERROR);
	while (envp)
	{
		if (envp->key)
		{
			if (!ft_strncmp(envp->key, var_name, ft_strlen(envp->key))
				&& ft_strlen(envp->key) == ft_strlen(var_name))
			{
				return (1);
			}
		}
		envp = envp->next;
	}
	return (0);
}

t_envp	*ft_envp_new_node(char *key, char *value)
{
	t_envp	*node;

	node = (t_envp *)malloc(sizeof(t_envp));
	if (!node || !key || !value)
		return (NULL);
	node->key = ft_strinit(ft_strlen(key), key);
	node->value = ft_strinit(ft_strlen(value), value);
	node->next = NULL;
	if (!node->key || !node->value)
		return (NULL);
	return (node);
}

t_envp	*ft_envp_last_node(t_envp *envp)
{
	while (envp && envp->next)
		envp = envp->next;
	return (envp);
}

void	ft_envp_addback_node(t_envp **envp, t_envp *new_node)
{
	t_envp	*last_node;

	last_node = ft_envp_last_node(*envp);
	if (last_node)
		last_node->next = new_node;
	else
		*envp = new_node;
}
