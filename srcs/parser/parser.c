#include "minishell.h"

int parser(t_minishell *mini)
{
	int arglen;
	char *arg;
	int i;
	char *line;

	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, &handle_signal);
	i = 0;
	mini->arg_item = NULL;
	arg = NULL;
	line = readline(PROMT);
	if (line == NULL)
	{
		mini->exit = 1;
		ft_putstr_fd("\e[1A\e[11C" "exit\n", 1);
		exit(0);
	}
	add_cmd_to_history(mini, line);
	while (line[i])
	{
		i = skip_spaces(line, i) + 1;
		arglen = get_arglen(line, i);
		if (arglen < 1)
			return (ERROR);
		arg = ft_substr(line, i, arglen);
		if (!arg)
			return (ERROR);
		if (arg[0] == '\'' || arg[0] == '"')
			if (check_param_quote(arg, arg[0]) == ERROR)
				return (exit_with_error("bad syntax near quotes!"));
		add_arg_to_args(mini, arg);
		i += arglen;
		i = skip_spaces(line, i);
		i++;
		free(arg);
	}
	return (SUCCESS);
}
