#include "minishell.h"

static int check_types(t_arg_item *arg_item, char *which_types)
{
	if (!which_types)
		return (0);
	if (ft_strchr(which_types, 'R') && check_type(arg_item, REDIR))
		return (1);
	else if (ft_strchr(which_types, 'A') && check_type(arg_item, APPEND))
		return (1);
	else if (ft_strchr(which_types, 'I') && check_type(arg_item, INPUT))
		return (1);
	else if (ft_strchr(which_types, 'P') && check_type(arg_item, PIPE))
		return (1);
	return (0);
}

int validate_line(t_minishell *mini, t_arg_item *arg_item)
{
	while (arg_item)
	{
		if (check_types(arg_item, "RAI")
			&& (!arg_item->next || check_types(arg_item->next, "RAIP")))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
			if (arg_item->next)
				ft_putstr_fd(arg_item->next->name, 2);
			else
				ft_putstr_fd("newline", 2);
			ft_putstr_fd("'\n", 2);
			mini->ret = 258;
			return (ERROR);
		}
		if (check_type(arg_item, PIPE) && (!arg_item->prev || !arg_item->next
			|| check_types(arg_item->prev, "RAIP")))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
			ft_putstr_fd(arg_item->name, 2);
			ft_putstr_fd("'\n", 2);
			mini->ret = 258;
			return (ERROR);
		}
		arg_item = arg_item->next;
	}
	return (SUCCESS);
}