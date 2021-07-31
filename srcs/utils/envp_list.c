#include "minishell.h"

char *env_to_str(char *prefix, char *key, char *value, char *del)
{
	int i;
	char *result;
	size_t total_size;

	i = 0;
	total_size = 0;
	if (prefix)
		total_size += ft_strlen(prefix);
	total_size += ft_strlen(key) + ft_strlen(value) + ft_strlen(del);
	result = ft_strnew(total_size);
	if (!result)
		return (NULL);
	ft_stricpy(&result, prefix, &i);
	ft_stricpy(&result, key, &i);
	ft_stricpy(&result, del, &i);
	ft_stricpy(&result, value, &i);
	return (result);
}

void	print_envp_list(t_envp *envp, char *prefix)
{
	char *result;
	char *p_str;

	p_str = NULL;
	while (envp)
	{
		if (prefix)
			p_str = ft_strjoin(prefix, " ");
		result = env_to_str(p_str, envp->key, envp->value, "=");
		if (result)
			ft_putendl_fd(result, 1);
		envp = envp->next;
		free(result);
		free(p_str);
	}

}

static void swap(t_envp *current, t_envp *next)
{
	char *key;
	char *value;

	key = current->key;
	value = current->value;
	current->key = next->key;
	current->value = next->value;
	next->key = key;
	next->value = value;
}

void sort_envp_list(t_envp *envp)
{
	int swapped;
	t_envp *ptr_1;
	t_envp *ptr_2;

	if (!envp)
		return ;
	swapped = 1;
	ptr_2 = NULL;
	while (swapped)
	{
		swapped = 0;
		ptr_1 = envp;
		while (ptr_1->next != ptr_2)
		{
			if (ft_strcmp(ptr_1->key, ptr_1->next->key) > 0)
			{
				swap(ptr_1, ptr_1->next);
				swapped = 1;
			}
			ptr_1 = ptr_1->next;
		}
		ptr_2 = ptr_1;
	}
}

size_t ft_envp_size(t_envp *root)
{
	size_t size;

	size = 0;
	while (root)
	{
		root = root->next;
		size++;
	}
	return (size);
}

void ft_delete_envp_node(t_envp **root, t_envp *node)
{
	t_envp *prev;
	t_envp *temp;

	temp = *root;
	if (temp && ft_strncmp(temp->key, node->key, ft_strlen(node->key)) == 0)
		*root = temp->next;
	else
	{
		while (temp && ft_strncmp(temp->key, node->key, ft_strlen(node->key)))
		{
			prev = temp;
			temp = temp->next;
		}
		if (temp == NULL)
			return ;
		prev->next = temp->next;
	}
	ft_free_str(temp->key);
	ft_free_str(temp->value);
	free(temp);
//	temp->next = node->next;
//	ft_free_str(node->key);
//	ft_free_str(node->value);
//	free(node);
//	return (temp);
}

t_envp *ft_copy_envp_node(t_envp *node)
{
	t_envp *res;

	if (!node)
		return (NULL);
	res = (t_envp *)malloc(sizeof(t_envp) * 1);
	if (!res)
		return (NULL);
	res->key = ft_strinit(ft_strlen(node->key), node->key);
	res->value = ft_strinit(ft_strlen(node->value), node->value);
	res->next = node->next;
	return (res);
}

t_envp	*ft_get_envp_node(t_envp *envp, char *key)
{
	t_envp *res;

	if (!key)
		return (NULL);
	while (envp)
	{
		if (!ft_strncmp(envp->key, key, ft_strlen(envp->key))
			&& ft_strlen(envp->key) == ft_strlen(key))
		{
			return (envp);
		}
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
			if (envp->value)
				return (ERROR);
		}
		envp = envp->next;
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
}

int ft_cpy_env(t_minishell *mini, char **envp)
{
	int	i;
	int j;
	char **result;

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
		ft_envp_addback_node(&mini->envp, ft_envp_new_node(result[0], result[1]));
		i++;
		free(result[0]);
		free(result[1]);
		free(result);
	}
	return (SUCCESS);
}

int is_env_exist(t_envp *envp, char *var_name)
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
