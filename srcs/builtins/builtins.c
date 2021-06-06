#include "minishell.h"

static void init_builtins(int (*builtins_func[7])(t_minishell *mini))
{
	builtins_func[0] = ft_echo;
	builtins_func[1] = ft_cd;
	builtins_func[2] = ft_pwd;
	builtins_func[3] = ft_export;
}

int builtins(t_minishell *mini)
{
	int (*builtins_func[7]) (t_minishell *mini);
	t_list *args;

	init_builtins(builtins_func);
	args = mini->args;
	while (args)
	{
		if (is_builtin(args->content, "echo"))
			builtins_func[0](mini);
		else if (is_builtin(args->content, "cd"))
			builtins_func[1](mini);
		else if (is_builtin(args->content, "pwd"))
			builtins_func[2](mini);
		else if (is_builtin(args->content, "export"))
			builtins_func[3](mini);
		args = args->next;
	}
	return (SUCCESS);
}