/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:28:05 by mrosette          #+#    #+#             */
/*   Updated: 2021/08/03 20:39:10 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect(t_minishell *mini, t_arg_item *arg, int flag)
{
	ft_close(mini->fdout);
	if (flag == REDIR)
		mini->fdout = open(arg->name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		mini->fdout = open(arg->name, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (mini->fdout == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg->name, 2);
		ft_putendl_fd(": No such file or directory\n", 2);
		mini->ret = 1;
		mini->no_exec = 1;
		return ;
	}
	dup2(mini->fdout, 1);
}

void	input(t_minishell *mini, t_arg_item *arg)
{
	ft_close(mini->fdin);
	mini->fdin = open(arg->name, O_RDONLY, S_IRWXU);
	if (mini->fdin == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg->name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		mini->ret = 1;
		mini->no_exec = 1;
		return ;
	}
	dup2(mini->fdin, 0);
}

int	shellpipe(t_minishell *mini)
{
	pid_t	pid;
	int		pipfd[2];

	mini->pipe->insidepipe = 1;
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
		return (2);
	}
	else
	{
		ft_close(pipfd[0]);
		dup2(pipfd[1], 1);
		mini->pipe->pipeout = pipfd[1];
		mini->last = 0;
		mini->pid = pid;
		return (1);
	}
}
