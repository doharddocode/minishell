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

t_arg	*t_arg_new_node(char symb)
{
	t_arg	*node;

	node = (t_arg *)calloc(1, sizeof(t_arg));
	if (!node)
		return (NULL);
	node->symb = symb;
	node->next = NULL;
	return (node);
}

t_arg	*t_arg_last_node(t_arg *arg)
{
	while (arg && arg->next)
		arg = arg->next;
	return (arg);
}

void	t_arg_addnode_back(t_arg **arg, t_arg *new_node)
{
	t_arg	*last_node;

	last_node = t_arg_last_node(*arg);
	if (last_node)
		last_node->next = new_node;
	else
		*arg = new_node;
	new_node->next = NULL;
}
