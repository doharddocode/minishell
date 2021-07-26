#include "minishell.h"

static void init_builtins(int (*builtins_func[7])(t_minishell *mini))
{
	builtins_func[0] = ft_echo;
	builtins_func[1] = ft_cd;
	builtins_func[2] = ft_pwd;
	builtins_func[3] = ft_export;
	builtins_func[4] = ft_unset;
	builtins_func[5] = ft_env;
	builtins_func[6] = ft_exit;
}

int	builtins(t_minishell *mini)
{
	int (*builtins_func[7]) (t_minishell *mini);

	init_builtins(builtins_func);
	if (is_builtin(mini->arg_item->name, "echo"))
		return (builtins_func[0](mini));
	else if (is_builtin(mini->arg_item->name, "cd"))
		return (builtins_func[1](mini));
	else if (is_builtin(mini->arg_item->name, "pwd"))
		return (builtins_func[2](mini));
	else if (is_builtin(mini->arg_item->name, "export"))
		return (builtins_func[3](mini));
	else if (is_builtin(mini->arg_item->name, "unset"))
		return (builtins_func[4](mini));
	else if (is_builtin(mini->arg_item->name, "env"))
		return (builtins_func[5](mini));
	else if (is_builtin(mini->arg_item->name, "exit"))
		return (builtins_func[6](mini));
	return (SUCCESS);
}
