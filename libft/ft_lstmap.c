#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*el;

	new = NULL;
	while (lst && f)
	{
		el = ft_lstnew(f(lst->content));
		if (el)
		{
			ft_lstadd_back(&new, el);
			lst = lst->next;
		}
		else
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
	}
	return (new);
}
