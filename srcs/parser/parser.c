#include "minishell.h"

int add_arg_to_args(t_minishell *mini, char *arg)
{
	char *env_var;

	env_var = parse_env_vars(mini, arg);
	if (env_var)
		ft_lstadd_back(&(mini->args), ft_lstnew(env_var));
	else
		ft_lstadd_back(&(mini->args), ft_lstnew(arg));
	return (SUCCESS);
}

int skip_spaces(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (--i);
}

int get_arg_len(char *str, int *i)
{
	int result;

	result = 0;
	while (!str[*i] || str[*i] != ' ')
	{
		if (!str[*i])
			break;
		result++;
		*i = *i + 1;
	}
	return (result);
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
		arg_len = get_arg_len(str, &i);
		i -= arg_len;
		arg = ft_substr(str, i, arg_len);
		if (!arg)
			return (ERROR);
		add_arg_to_args(mini, arg);
		i += arg_len;
		i = skip_spaces(str, i);
		i++;
	}
	return (SUCCESS);
}