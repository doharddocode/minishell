#include "minishell.h"

t_arg_item *get_next_arg(t_arg_item *current_arg)
{
	while (current_arg && current_arg->type < REDIR)
		current_arg = current_arg->next;
	return (current_arg);
}

t_arg_item *get_prev_arg(t_arg_item *current_arg)
{
	while (current_arg && current_arg->type < REDIR)
		current_arg = current_arg->prev;
	return (current_arg);
}

int arg_item_count(t_arg_item *root)
{
	int i;

	i = 0;
	while (root)
	{
		root = root->next;
		i++;
	}
	return (i);
}

t_arg_item *new_item(char *name)
{
	t_arg_item *result;

	result = malloc(sizeof(t_arg_item));
	if (result)
	{
		result->name = name;
		// set_arg_type(result);
		result->next = NULL;
		result->prev = NULL;
		return (result);
	}
	return (NULL);
}

t_arg_item *item_last(t_arg_item *root)
{
	while (root && root->next)
		root = root->next;
	return (root);
}

void	add_item_back(t_arg_item **root, t_arg_item *new_item)
{
	t_arg_item	*last;

	last = item_last(*root);
	if (last)
	{
		last->next = new_item;
		new_item->prev = last;
	}
	else
		*root = new_item;
	new_item->next = NULL;
	set_arg_type(new_item);
}

