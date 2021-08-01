#include "minishell.h"

t_signal	g_sig;

void	set_arg_type(t_arg_item *item)
{
	if (ft_strcmp(item->name, "|") == 0)
		item->type = PIPE;
	else if (ft_strcmp(item->name, ">") == 0)
		item->type = REDIR;
	else if (ft_strcmp(item->name, "<") == 0)
		item->type = INPUT;
	else if (ft_strcmp(item->name, ">>") == 0)
		item->type = APPEND;
	else if (ft_strcmp(item->name, "<<") == 0)
		item->type = HEREDOC;
	else if (item->prev == NULL || item->prev->type == PIPE)
		item->type = COMMAND;
	else
		item->type = ARGUMENT;
}

void	run_cmd(t_minishell *mini, t_arg_item *arg_item)
{
	t_arg_item	*temp;

	temp = arg_item;
	if (mini->pipe->count == 0)
		return ;
	while (temp)
	{
		to_lower_case(arg_item->name);
		temp = temp->next;
	}
	if (is_builtin(arg_item->name, NULL))
		mini->ret = builtins(mini);
	else if (ft_strcmp(arg_item->name, "history") == 0)
		show_working_history(mini);
	else
		mini->ret = execute(mini, arg_item);
	ft_close(mini->pipe->pipein);
	ft_close(mini->pipe->pipeout);
	mini->pipe->pipein = -1;
	mini->pipe->pipeout = -1;
	mini->pipe->count = 0;
}

void	redir_exec(t_minishell *mini, t_arg_item *arg_item)
{
	int			pipe;
	t_arg_item	*next_arg;
	t_arg_item	*prev_arg;

	pipe = 0;
	prev_arg = get_prev_arg(arg_item);
	next_arg = get_next_arg(arg_item);
	if (check_type(prev_arg, REDIR))
		redirect(mini, arg_item, REDIR);
	else if (check_type(prev_arg, APPEND))
		redirect(mini, arg_item, APPEND);
	else if (check_type(prev_arg, INPUT))
		input(mini, arg_item);
	else if (check_type(prev_arg, HEREDOC))
		heredoc(mini, arg_item);
	else if (check_type(prev_arg, PIPE))
		pipe = shellpipe(mini);
	if (next_arg && check_for_redirs(prev_arg, next_arg, mini) == 0
		&& pipe != 1)
		redir_exec(mini, next_arg->next);
	if ((check_type(prev_arg, PIPE) || !prev_arg) && pipe != 1
		&& mini->no_exec == 0)
		run_cmd(mini, arg_item);
}

void	minishell(t_minishell *mini)
{
	t_arg_item	*arg_item;
	int			state;

	arg_item = mini->arg_item;
	while (arg_item)
	{
		set_flags(mini);
		redir_exec(mini, arg_item);
		close_all(mini);
		set_fds(mini);
		waitpid(-1, &state, 0);
		state = WEXITSTATUS(state);
		if (mini->last == 0)
			mini->ret = state;
		if (mini->pipe->daddy == 0)
			exit(mini->ret);
		mini->no_exec = 0;
		if (mini->redir_flag)
			arg_item = next_arg(arg_item, mini->pipe->insidepipe);
		else
			break ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell		mini;
	t_pipe			pipe;
	struct termios	ts;

	tcgetattr(0, &ts);
	ts.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &ts);
	ft_cpy_env(&mini, envp);
	pipe.flag = 0;
	init_flags(&mini, &pipe);
	(void)argc;
	(void)argv;
	set_fds(&mini);
	while (mini.exit == 0)
	{
		init_signal();
		mini.arg_item = NULL;
		if (parser(&mini) != ERROR
			&& validate_line(&mini, mini.arg_item) != ERROR)
			minishell(&mini);
		free_arg_item(&mini);
	}
	free_envp_list(&mini);
	free_history(&mini);
	return (SUCCESS);
}
