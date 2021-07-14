#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*res;

	res = malloc(sizeof(t_list));
	if (res)
	{
		res->content = content;
		res->next = NULL;
		return (res);
	}
	return (NULL);
}
