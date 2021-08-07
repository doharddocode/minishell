#include "minishell.h"

void	parse_to_arglist(t_minishell *mini, t_arg **arg_list, char *arg, int *i)
{
	if (!mini->is_quote_parse)
		parse_quotes(mini, arg_list, arg, i);
	parse_escape(mini, arg_list, arg, i);
	parse_env_vars(mini, arg_list, arg, i);
	if (arg[*i] && is_normal_symbol(mini, arg[*i]))
	{
		t_arg_addnode_back(arg_list, t_arg_new_node(arg[*i]));
		next_symbol(arg, i);
	}
}

void	next_symbol(char *str, int *counter)
{
	if (str[*counter])
		(*counter)++;
}

int	is_normal_symbol(t_minishell *mini, char symb)
{
	if (mini->is_quote_parse && symb == '\'')
		return (1);
	else if (symb != '"' && symb != '\'' && symb != '\\' && symb != '\0')
		return (1);
	else
		return (0);
}

int	skip_spaces(char *str, int i)
{
	if (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
	}
	return (--i);
}
