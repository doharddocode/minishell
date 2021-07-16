#include "minishell.h"

int parser(t_minishell *mini)
{

	int arglen;
	char *arg;
	int i;
	char *str;

	i = 0;
	mini->arg_item = NULL;
	arg = NULL;
	str = NULL;
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, &handle_signal);
	if (get_next_line(0, &str) == -2 && mini->exit == 1)
		printf("exit\n");
	while (str[i])
	{
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
