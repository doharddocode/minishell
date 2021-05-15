#include "minishell.h"

static void init_builtins(int (*builtins_func[7])(t_minishell *mini))
{
	builtins_func[0] = ft_echo;
}

int builtins(t_minishell *mini)
{
	int (*builtins_func[7]) (t_minishell *mini);
	t_list *args;

	init_builtins(builtins_func);
	args = mini->args;
	while (args)
	{
		if (!ft_strncmp(args->content, "echo", ft_strlen("echo")))
			builtins_func[0](mini);
		args = args->next;
	}
	return (SUCCESS);
}