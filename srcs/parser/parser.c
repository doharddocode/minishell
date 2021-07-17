#include "minishell.h"

int parser(t_minishell *mini)
{

	int arglen;
	char *arg;
	int i;
	char *line;

	i = 0;
	mini->arg_item = NULL;
	arg = NULL;
	line = NULL;
	get_next_line(1, &line);
	add_cmd_to_history(&mini, line);
	while (line[i])
	{
		i = skip_spaces(line, i) + 1;
		arglen = get_arglen(line, i);
		if (arglen < 1)
			return (ERROR);
		arg = ft_substr(line, i, arglen);
		if (!arg)
			return (ERROR);
		add_arg_to_args(mini, arg);
		i += arglen;
		i = skip_spaces(line, i);
		i++;
	}
	return (SUCCESS);
}
