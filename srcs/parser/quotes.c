#include "minishell.h"

int is_valid_quotes(char *arg, char quote)
{
	int i;
	int quote_count;

	i = 0;
	quote_count = 0;
	while (arg[i])
	{
		if (arg[i] == quote)
			quote_count++;
		i++;
	}
	if (quote_count % 2 != 0)
		return (0);
	return (1);
}

int parse_double_quotes(t_minishell *mini, t_arg **arg_list, char *arg, int *i)
{
	int j;
	char *substr;

	j = 0;
	if (arg[*i] == '"')
	{
		if (!is_valid_quotes(&arg[*i], '"'))
			return (ERROR);
		(*i) += 2;
		substr = ft_remove_chrnstr(arg, '"');
		if (!substr)
			return (ERROR);
		if (!ft_strlen(substr))
			ft_lstadd_back(&(mini->args), ft_lstnew(""));
		while (substr[j])
		{
			parse_env_vars(mini, arg_list, substr, &j);
			if (substr[j])
			{
				t_arg_addnode_back(arg_list, t_arg_new_node(substr[j]));
				j++;
			}
		}
		*i += (int)ft_strlen(substr);
	}
	return (SUCCESS);
}

int parse_single_quotes(t_minishell *mini, char *arg, int *i)
{
	char *substr;

	if (arg[*i] == '\'')
	{
		if (!is_valid_quotes(&arg[*i], '\''))
			return (ERROR);
		(*i) += 2;
		substr = ft_remove_chrnstr(arg, '\'');
		if (!substr)
			return (ERROR);
		ft_lstadd_back(&(mini->args), ft_lstnew(substr));
		*i += (int)ft_strlen(substr);
	}
	return (SUCCESS);
}