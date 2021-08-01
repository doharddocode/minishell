#include "minishell.h"

t_arg_item	*new_item(char *name)
{
	t_arg_item	*result;

	result = malloc(sizeof(t_arg_item));
	if (result)
	{
		result->name = name;
		result->next = NULL;
		result->prev = NULL;
		return (result);
	}
	return (NULL);
}

char	*t_arg_to_string(t_arg *arg)
{
	char	*result;
	char	*temp_str;
	char	*symb_to_str;
	t_arg	*temp_node;

	temp_node = arg;
	result = ft_strnew(1);
	if (!result)
		ft_free_str(result);
	while (arg && temp_node)
	{
		temp_str = result;
		if (!temp_node->symb)
			return (NULL);
		symb_to_str = ft_strinit(1, &(temp_node->symb));
		if (!symb_to_str)
			return (NULL);
		result = ft_strjoin(result, symb_to_str);
		ft_free_str(temp_str);
		ft_free_str(symb_to_str);
		temp_node = temp_node->next;
	}
	return (result);
}

size_t	ft_envp_size(t_envp *root)
{
	size_t	size;

	size = 0;
	while (root)
	{
		root = root->next;
		size++;
	}
	return (size);
}

void	print_envp_list(t_envp *envp, char *prefix)
{
	char	*result;
	char	*p_str;

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

t_envp	*ft_get_envp_node(t_envp *envp, char *key)
{
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
