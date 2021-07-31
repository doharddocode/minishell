#include "minishell.h"

int	iterator(int i, int arglen, char *line)
{
	i += arglen;
	i = skip_spaces(line, i);
	i++;
	return (i);
}

static int	parser_util(t_minishell *mini, char *line, int i, char *arg)
{
	int		arglen;

	while (line[i])
	{
		i = skip_spaces(line, i) + 1;
		arglen = get_arglen(mini, line, i);
		if (arglen < 1)
			return (ERROR);
		arg = ft_substr(line, i, arglen);
		if (!arg)
			return (ERROR);
		if (arg[0] == '\'' || arg[0] == '"')
		{
			if (check_param_quote(arg, arg[0]) == ERROR)
			{
				free(arg);
				return (exit_with_error("bad syntax near quotes!"));
			}
		}
		add_arg_to_args(mini, arg);
		i = iterator(i, arglen, line);
		free(arg);
	}
	return (0);
}

int	parser(t_minishell *mini)
{
	char	*line;
	int		res;
	char	*arg;

	arg = NULL;
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, &handle_signal);
	line = readline(PROMT);
	if (line == NULL)
	{
		mini->exit = 1;
		ft_putstr_fd("\e[1A\e[11C" "exit\n", 1);
		exit(0);
	}
	add_cmd_to_history(mini, line);
	add_history(line);
	res = parser_util(mini, line, 0, arg);
	if (res == ERROR)
	{
		free(line);
		return (ERROR);
	}
	free(line);
	return (SUCCESS);
}

int	check_param_quote(char *param, char quote_type)
{
	int	i;

	i = 1;
	while (param && param[i])
	{
		if (param[i] == quote_type)
			return (1);
		i++;
	}
	return (ERROR);
}
