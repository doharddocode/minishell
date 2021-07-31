#include "minishell.h"

int	is_shieild_symb(char symb)
{
	if (ft_strchr(SP_SYMBOLS, symb))
		return (1);
	else
		return (0);
}

static int	escape_quotes(t_arg **arg_list, char *arg, int *i)
{
	if (is_shieild_symb(arg[(*i) + 1]))
	{
		t_arg_addnode_back(arg_list, t_arg_new_node(arg[++(*i)]));
		next_symbol(arg, i);
	}
	else
		t_arg_addnode_back(arg_list, t_arg_new_node(arg[(*i)++]));
	return (SUCCESS);
}

static int	escape_common(t_arg **arg_list, char *arg, int *i)
{
	t_arg_addnode_back(arg_list, t_arg_new_node(arg[++(*i)]));
	next_symbol(arg, i);
	return (SUCCESS);
}

int	parse_escape(t_minishell *mini, t_arg **arg_list, char *arg, int *i)
{
	if (arg[*i] == '\\' && arg[*i + 1])
	{
		if (mini->is_quote_parse)
			escape_quotes(arg_list, arg, i);
		else
			escape_common(arg_list, arg, i);
		parse_escape(mini, arg_list, arg, i);
	}
	else if (arg[*i] == '\\' && (!arg[*i + 1] || arg[*i + 1] == ' '))
		next_symbol(arg, i);
	return (SUCCESS);
}
