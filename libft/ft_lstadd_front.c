#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*ptr;

	ptr = *lst;
	*lst = new;
	new->next = ptr;
}
