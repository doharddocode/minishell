#include "minishell.h"

t_arg_item *get_item(t_minishell *mini, t_arg_item *current_item, int n_item)
{
	t_arg_item *root;

	root = mini->arg_item;
	while (root)
	{
		if (n_item == NEXT_ITEM && root == current_item)
			return (root->next);
		else if (n_item == PREV_ITEM && root->next == current_item)
			return (root);
		root = root->next;
	}
	return (NULL);
}

t_arg_item *new_item(char *name)
{
	t_arg_item *result;

	result = malloc(sizeof(t_arg_item));
	if (result)
	{
		result->name = name;
		set_arg_type(result);
		result->next = NULL;
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
		last->next = new_item;
	else
		*root = new_item;
	new_item->next = NULL;
}
