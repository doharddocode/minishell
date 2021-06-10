#include "minishell.h"

static void init_builtins(int (*builtins_func[7])(t_minishell *mini))
{
	builtins_func[0] = ft_echo;
	builtins_func[1] = ft_cd;
	builtins_func[2] = ft_pwd;
	builtins_func[3] = ft_export;
	builtins_func[4] = ft_unset;
	builtins_func[5] = ft_exit;
}

int builtins(t_minishell *mini)
{
	int (*builtins_func[7]) (t_minishell *mini);

	init_builtins(builtins_func);
	while (mini->args)
	{
		if (is_builtin(mini->args->content, "echo"))
			builtins_func[0](mini);
		else if (is_builtin(mini->args->content, "cd"))
			builtins_func[1](mini);
		else if (is_builtin(mini->args->content, "pwd"))
			builtins_func[2](mini);
		else if (is_builtin(mini->args->content, "export"))
			builtins_func[3](mini);
		else if (is_builtin(mini->args->content, "unset"))
			builtins_func[4](mini);
		else if (is_builtin(mini->args->content, "exit"))
			builtins_func[5](mini);
		if (mini->args)
			mini->args = mini->args->next;
	}
	return (SUCCESS);
}