#include "minishell.h"

int		shellpipe(t_minishell *mini)
{
	int pid;
	int pipfd[2];

	pipe(pipfd);
	pid = fork();
	if (pid == 0)
	{
		close(pipfd[1]);
		dup2(pipfd[0], 0);
		mini->pipe->pipein = pipfd[0];
		mini->pipe->daddy = 0;
		mini->last = 0;
		return(2);
	}
	else
	{
		close(pipfd[0]);
		dup2(pipfd[1], 1);
		mini->pipe->pipeout = pipfd[1];
		mini->last = 0;
		return(1);
	}
}
