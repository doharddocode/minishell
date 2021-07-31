#include "minishell.h"

static void	get_arglen_s_quote(char *str, int i, int *result, char quote)
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

static void	get_arglen_d_quote(char *str, int i, int *result, char quote)
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

static int	get_arglen_quote(char *str, int i, int *result)
{
	if (str[i] == '"')
		get_arglen_d_quote(str, i, result, str[i]);
	else if (str[i] == '\'')
		get_arglen_s_quote(str, i, result, str[i]);
	return (*result);
}

int	get_arglen(t_minishell *mini, char *str, int i)
{
	mini->arg_len = 0;
	if (str[i] == '\\')
	{
		mini->arg_len++;
		i++;
		while (str[i] && (str[i] == ' ' || str[i] != ' '))
		{
			i++;
			mini->arg_len++;
		}
	}
	else if (str[i] == '"' || str[i] == '\'')
		return (get_arglen_quote(str, i, &mini->arg_len));
	else
	{
		while (str[i] && str[i] != ' ')
		{
			if (str[i] == '"' || str[i] == '\'')
				return (get_arglen_quote(str, i, &mini->arg_len));
			mini->arg_len++;
			i++;
		}
	}
	return (mini->arg_len);
}

int	add_arg_to_args(t_minishell *mini, char *arg)
{
	t_arg	*arg_list;
	int		i;
	char	*res;

	i = 0;
	arg_list = NULL;
	while (arg[i])
		parse_to_arglist(mini, &arg_list, arg, &i);
	res = t_arg_to_string(arg_list);
	t_arg_clear(&arg_list, free);
	if (res)
		add_item_back(&(mini->arg_item), new_item(res));
	else
		add_item_back(&(mini->arg_item), new_item(ft_strnew(0)));
	return (SUCCESS);
}
