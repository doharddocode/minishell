#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst_last;

	lst_last = ft_lstlast(*lst);
	if (lst_last)
		lst_last->next = new;
	else
		*lst = new;
	new->next = NULL;
}
