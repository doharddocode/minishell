#include "minishell.h"

static char	*quote_substr(int *q_cnt, char *str, char symb)
{
	char	*result;
	int		i;

	i = 1;
	(*q_cnt) = 1;
	while (str[i])
	{
		if (str[i] == symb && i == (int)ft_strlen(str) - 1 && str[i - 1] != '\\')
			(*q_cnt)++;
		i++;
	}
	if ((*q_cnt) % 2 == 0)
		result = ft_substr(str, 1, ft_strlen(str) - 2);
	else
		return (NULL);
	return (result);
}

static int	parse_double_quotes(t_minishell *mini, t_arg **arg_list,
		char *arg, int *i)
{
	int		j;
	int		q_cnt;
	char	*substr;

	j = 0;
	if (arg[*i] == '"')
	{
		substr = quote_substr(&q_cnt, &arg[*i], '"');
		(*i) += 1;
		if (!substr)
			return (ERROR);
		(*i) += 1;
		if (ft_strlen(substr))
			while (substr[j])
				parse_to_arglist(mini, arg_list, substr, &j);
		*i += (int)ft_strlen(substr);
		ft_free_str(substr);
	}
	return (SUCCESS);
}

static int	parse_single_quotes(t_arg **arg_list,
		char *arg, int *i)
{
	int		j;
	int		q_cnt;
	char	*substr;

	j = 0;
	if (arg[*i] == '\'')
	{
		substr = quote_substr(&q_cnt, &arg[*i], '\'');
		(*i)++;
		if (!substr)
			return (ERROR);
		if (ft_strlen(substr))
		{
			while (substr[j])
			{
				t_arg_addnode_back(arg_list, t_arg_new_node(substr[j]));
				next_symbol(substr, &j);
			}
		}
		*i += ((int)ft_strlen(substr) + q_cnt - 1);
		ft_free_str(substr);
	}
	return (SUCCESS);
}

int	parse_quotes(t_minishell *mini, t_arg **arg_list, char *arg, int *i)
{
	mini->is_quote_parse = 1;
	parse_single_quotes(arg_list, arg, i);
	parse_double_quotes(mini, arg_list, arg, i);
	mini->is_quote_parse = 0;
	return (SUCCESS);
}
