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

void	set_flags(t_minishell *mini)
{
	mini->pipe->count = 1;
	mini->pipe->daddy = 1;
	mini->last = 1;
	mini->pipe->insidepipe = 0;
	mini->redir_flag = 0;
}

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void	close_all(t_minishell *mini)
{
	dup2(mini->in, 0);
	dup2(mini->out, 1);
	ft_close(mini->pipe->pipein);
	ft_close(mini->pipe->pipeout);
	ft_close(mini->fdin);
	ft_close(mini->fdout);
	ft_close(mini->fd_temp);
}
