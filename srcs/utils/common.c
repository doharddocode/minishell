#include "minishell.h"

char *t_list_to_string(t_list *list)
{
	char *result;
	char *temp_str;
	t_list *temp_node;

	temp_node = list;
	result = ft_strnew(1);
	if (!result || !list)
		return (NULL);
	while (temp_node)
	{
		temp_str = result;
		if (!temp_node->content)
			return (NULL);
		result = ft_strjoin(result, temp_node->content);
		ft_free_str(temp_str);
		temp_node = temp_node->next;
	}
	return (result);
}
