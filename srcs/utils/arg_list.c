#include "minishell.h"

void	t_arg_lstdelone(t_arg *lst)
{
	free(lst);
	lst = NULL;
}


void	t_arg_clear(t_arg **lst, void (*del)(void *))
{
	if (*lst)
	{
		if ((*lst)->next)
			t_arg_clear(&((*lst)->next), del);
		t_arg_lstdelone(*lst);
		*lst = NULL;
	}
}

char *t_arg_to_string(t_arg *arg)
{
	char *result;
	char *temp_str;
	char *symb_to_str;
	t_arg *temp_node;

	temp_node = arg;
	result = ft_strnew(1);
	if (!result || !arg)
		return (NULL);
	while (temp_node)
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

t_arg *t_arg_new_node(char symb)
{
	t_arg *node;

	node = (t_arg *)malloc(sizeof(t_arg) * 1);
	if (!node)
		return (NULL);
	node->symb = symb;
	node->next = NULL;
	return (node);
}

t_arg *t_arg_last_node(t_arg *arg)
{
	while (arg && arg->next)
		arg = arg->next;
	return (arg);
}

void t_arg_addnode_back(t_arg **arg, t_arg *new_node)
{
	t_arg *last_node;

	last_node = t_arg_last_node(*arg);
	if (last_node)
		last_node->next = new_node;
	else
		*arg = new_node;
	new_node->next = NULL;
}
