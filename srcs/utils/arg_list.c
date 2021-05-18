#include "minishell.h"

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