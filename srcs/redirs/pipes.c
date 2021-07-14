#include "minishell.h"

int		shellpipe(t_minishell *mini)
{
	pid_t pid;
	int pipfd[2];

	pipe(pipfd);
	pid = fork();
	if (pid == 0)
	{
		ft_close(pipfd[1]);
		dup2(pipfd[0], 0);
		mini->pipe->pipein = pipfd[0];
		mini->pipe->daddy = 0;
		mini->pid = -1;
		mini->no_exec = 0;
		return(2);
	}
	else
	{
		ft_close(pipfd[0]);
		dup2(pipfd[1], 1);
		mini->pipe->pipeout = pipfd[1];
		mini->last = 0;
		mini->pid = pid;
		printf("PIPE ALIVE\n");
		return(1);
	}
}
