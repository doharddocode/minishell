#include "minishell.h"

void	init_flags(t_minishell *mini)
{
	t_pipe	pipe;

	pipe.flag = 0;
	mini->ret = 0;
	mini->work_history = NULL;
	mini->exit = 0;
	mini->is_quote_parse = 0;
	mini->no_exec = 0;
	mini->in = dup(0);
	mini->out = dup(1);
	mini->pipe = &pipe;
}
