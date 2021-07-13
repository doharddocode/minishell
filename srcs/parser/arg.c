#include "minishell.h"

static void get_arglen_s_quote(char *str, int i, int *result, char quote)
{
	i++;
	(*result)++;
	while (str[i] && str[i] != '\'')
	{
		(*result)++;
		i++;
	}
	if (str[i] == '\'')
		(*result)++;
}

static void get_arglen_d_quote(char *str, int i, int *result, char quote)
{
	if (quote == '"')
	{
		i++;
		(*result)++;
		while (str[i] && str[i] != '"')
		{
			if (str[i] == '\\' && str[i + 1] == '"')
			{
				(*result) += 2;
				i += 2;
			}
			else
			{
				(*result)++;
				i++;
			}
		}
		if (str[i] == '"')
			(*result)++;
	}
}

static int get_arglen_quote(char *str, int i, int *result)
{
	if (str[i] == '"')
		get_arglen_d_quote(str, i, result, str[i]);
	else if (str[i] == '\'')
		get_arglen_s_quote(str, i, result, str[i]);
	return (*result);
}

int get_arglen(char *str, int i)
{
	int result;

	result = 0;
	if (str[i] == '\\')
	{
		result++;
		i++;
		while (str[i] && (str[i] == ' ' || str[i] != ' '))
		{
			i++;
			result++;
		}
	}
	else if (str[i] == '"' || str[i] == '\'')
		return (get_arglen_quote(str, i, &result));
	else
	{
		while (str[i] && str[i] != ' ')
		{
			if (str[i] == '"' || str[i] == '\'')
				return (get_arglen_quote(str, i, &result));
			result++;
			i++;
		}
	}
	return (result);
}

int add_arg_to_args(t_minishell *mini, char *arg)
{
	t_arg *arg_list;
	int i;

	i = 0;
	arg_list = NULL;
	//printf("arg_prev=%s\n", arg);
	while (arg[i])
		parse_to_arglist(mini, &arg_list, arg, &i);
	if (t_arg_to_string(arg_list))
		add_item_back(&(mini->arg_item), new_item(t_arg_to_string(arg_list)));
	else
		add_item_back(&(mini->arg_item), new_item(ft_strnew(0)));
	return (SUCCESS);
}
