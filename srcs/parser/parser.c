#include "minishell.h"

int parser(t_minishell *mini)
{

	int arglen;
	char *arg;
	int i;
	char *line;
	struct termios ts;

	tgetent(0, "xterm-256color");
	tcgetattr(0, &ts);
	ts.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &ts);
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, &handle_signal);
	ft_putstr_fd(PROMT, 1);
	i = 0;
	mini->arg_item = NULL;
	arg = NULL;
	line = NULL;
	line = readline(NULL);
	if (line == NULL)
	{
		mini->exit = 1;
		ft_exit(mini);
		return (ERROR);
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
		add_arg_to_args(mini, arg);
		i += arglen;
		i = skip_spaces(line, i);
		i++;
	}
	return (SUCCESS);
}
