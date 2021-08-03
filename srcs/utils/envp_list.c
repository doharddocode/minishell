/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:27:56 by mrosette          #+#    #+#             */
/*   Updated: 2021/08/03 20:27:56 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_to_str(char *prefix, char *key, char *value, char *del)
{
	int		i;
	char	*result;
	size_t	total_size;

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

static void	swap(t_envp *current, t_envp *next)
{
	char	*key;
	char	*value;

	key = current->key;
	value = current->value;
	current->key = next->key;
	current->value = next->value;
	next->key = key;
	next->value = value;
}

void	ft_delete_envp_node(t_envp **root, t_envp *node)
{
	t_envp	*prev;
	t_envp	*temp;

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
}

t_envp	*ft_copy_envp_node(t_envp *node)
{
	t_envp	*res;

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

void	sort_envp_list(t_envp *envp)
{
	int		swapped;
	t_envp	*ptr_1;
	t_envp	*ptr_2;

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
