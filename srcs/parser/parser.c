#include "minishell.h"

int parser(t_minishell *mini, char *str)
{

	int arglen;
	char *arg;
	int i;

	i = 0;
	mini->args = NULL;
	arg = NULL;
	while (str[i])
	{
		if (str[i] == '|')
		{
			mini->pipe->flag = 1;
			i++;
		}
		i = skip_spaces(str, i) + 1;
		arglen = get_arglen(str, i);
		if (arglen < 1)
			return (ERROR);
		arg = ft_substr(str, i, arglen);
		if (!arg)
			return (ERROR);
		add_arg_to_args(mini, arg);
		i += arglen;
		i = skip_spaces(str, i);
		i++;
	}
	return (SUCCESS);
}