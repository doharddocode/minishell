#include "minishell.h"

char *env_to_str(char *prefix, char *key, char *value)
{
	int i;
	char *result;
	size_t total_size;

	i = 0;
	total_size = 0;
	if (prefix)
		total_size += ft_strlen(prefix);
	total_size += ft_strlen(key) + ft_strlen(value);
	result = ft_strnew(total_size);
	if (!result)
		return (NULL);
	ft_stricpy(&result, prefix, &i);
	ft_stricpy(&result, key, &i);
	ft_stricpy(&result, value, &i);
	return (result);
}

void	print_envp_list(t_envp *envp, char *prefix)
{
	char *env_key;
	char *result;
	char *p_str;

	while (envp)
	{
		if (prefix)
			p_str = ft_strjoin(prefix, " ");
		env_key = ft_strjoin(envp->key, "=");
		result = env_to_str(p_str, env_key, envp->value);
		if (result)
			ft_putendl_fd(result, 1);
		envp = envp->next;
	}
}

void sort_envp_list(t_envp **envp)
{
	t_envp *head;
	t_envp *temp;
	char *temp_key;
	char *temp_value;

	head = *envp;
	while (head != NULL)
	{
		temp = head;
		while (temp->next != NULL)
		{
			if (ft_strcmp(temp->key, temp->next->key) > 0)
			{
				temp_key = temp->key;
				temp_value = temp->value;
				temp->key = temp->next->key;
				temp->value = temp->next->value;
				temp->next->key = temp_key;
				temp->next->value = temp_value;
			}
			temp = temp->next;
		}
		head = head->next;
	}
}

t_envp *ft_delete_envp_node(t_envp *root, t_envp *node)
{
	t_envp *temp;

	temp = root;
	while (temp->next != node)
		temp = temp->next;
	temp->next = node->next;
	ft_free_str(node->key);
	ft_free_str(node->value);
	free(node);
	return (temp);
}

t_envp	*ft_get_envp_node(t_envp *envp, char *key)
{
	t_envp *res;

	if (!key)
		return (NULL);
	res = (t_envp *)malloc(sizeof(t_envp));
	if (!res)
		return (NULL);
	while (envp)
	{
		if (!ft_strncmp(envp->key, key, ft_strlen(envp->key))
			&& ft_strlen(envp->key) == ft_strlen(key))
		{
//			res->key = ft_strinit(ft_strlen(envp->key), envp->key);
//			res->value = ft_strinit(ft_strlen(envp->value), envp->value);
//			res->next = envp->next;
//			return (res);
			return (envp);
		}
		envp = envp->next;
	}
	return (NULL);
}

int ft_envp_update_node(t_envp **envp, char *key, char *new_value)
{
	if (!new_value)
		return (ERROR);
	while (envp)
	{
		if (!ft_strncmp((*envp)->key, key, ft_strlen((*envp)->key))
			&& ft_strlen((*envp)->key) == ft_strlen(key))
		{
			ft_free_str((*envp)->value);
			(*envp)->value = ft_strinit(ft_strlen(new_value), new_value);
			if ((*envp)->value)
				return (ERROR);
		}
		*envp = (*envp)->next;
	}
	return (SUCCESS);
}

t_envp *ft_envp_new_node(char *key, char *value)
{
	t_envp *node;

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
		ft_envp_addback_node(&mini->envp, ft_envp_new_node(result[0], result[1]));
		i++;
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
