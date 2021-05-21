#include "minishell.h"

static int get_arg_len_quote(char *str, int i, int *result, char quote)
{
	if (quote == '"' || quote == '\'')
	{
		i++;
		if (!is_valid_quotes(str, quote))
			return (0);
		while (str[i])
		{
			if (str[i] == quote)
			{
				if (i < (ft_strlen(str) - 1))
				{
					if (str[i + 1] == ' ')
					{
						(*result)++;
						break;
					}
				}
			}
			i++;
			(*result)++;
		}
		return (*result += 1);
	}
	return (*result = -1);
}

static int get_arg_len(t_minishell *mini, char *str, int i)
{
	int result;

	result = 0;
	if (!get_arg_len_quote(str, i, &result, str[i]))
		return (result = 0);
	if (result == -1)
	{
		result = 0;
		while (str[i] && str[i] != ' ')
		{
			result++;
			i++;
		}
	}
	return (result);
}

static int add_arg_to_args(t_minishell *mini, char *arg)
{
	t_arg *arg_list;
	int i;

	i = 0;
	arg_list = NULL;
	while (arg[i])
	{
		if (parse_double_quotes(mini, &arg_list, arg, &i) == ERROR)
			return (ERROR);
		if (parse_single_quotes(mini, &arg_list, arg, &i) == ERROR)
			return (ERROR);
		parse_env_vars(mini, &arg_list, arg, &i);
		if (arg[i] && arg[i] != '\'' && arg[i] != '"')
		{
			t_arg_addnode_back(&arg_list, t_arg_new_node(arg[i]));
			i++;
		}
	}
	if (t_arg_to_string(arg_list))
		ft_lstadd_back(&(mini->args), ft_lstnew(t_arg_to_string(arg_list)));
	return (SUCCESS);
}

int parser(t_minishell *mini, char *str)
{

	int arg_len;
	char *arg;
	int i;

	i = 0;
	mini->args = NULL;
	arg = NULL;
	while (str[i])
	{
		i = skip_spaces(str, i) + 1;
		arg_len = get_arg_len(mini, str, i);
		if (arg_len < 1)
			return (ERROR);
		arg = ft_substr(str, i, arg_len);
		if (!arg)
			return (ERROR);
		if (add_arg_to_args(mini, arg) == ERROR)
			return (ERROR);
		i += arg_len;
		i = skip_spaces(str, i);
		i++;
	}
	return (SUCCESS);
}