#include "minishell.h"

int minishell(t_minishell *mini)
{
	t_list *args;

	args = mini->args;
	if (!args)
		return (mini->ret = ERROR);
	while (args)
	{
		to_lower_case(args->content);
		args = args->next;
	}
	if (is_builtin(mini->args->content, NULL))
		builtins(mini);
	else
		execute(mini);
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	mini;
	char		*line;

	ft_cpy_env(&mini, envp);
	mini.exit = 0;
	mini.is_quote_parse = 0;
	(void)argc;
	(void)argv;
	line = NULL;
	while (!mini.exit)
	{
		ft_putstr_fd("minishell> ", 1);
		get_next_line(0, &line);
		if (parser(&mini, line) != ERROR)
		{
			free(line);
			minishell(&mini);
		}
	}
	return (SUCCESS);
}
