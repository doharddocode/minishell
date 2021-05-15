#include "minishell.h"

t_list *delete_root(t_list *args_root)
{
	t_list *temp;
	temp = args_root->next;
	ft_free_str(args_root->content);
	free(args_root);
	return (temp);
}
