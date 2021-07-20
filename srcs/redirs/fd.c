#include "minishell.h"

void	set_fds(t_minishell *mini)
{
	mini->pipe->pipeout = -1;
	mini->pipe->pipein = -1;
	mini->fdin = -1;
	mini->fdout = -1;
	mini->pid = -1;
	mini->fd_temp = -1;
}

void	ft_close(int x)
{
	if (x > 0)
		close(x);
}
