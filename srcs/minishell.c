#include "minishell.h"

t_signal	sigs;

int check_type(t_arg_item *arg_item, int type)
{
	if (arg_item && arg_item->type == type)
		return (1);
	return (0);
}

void set_arg_type(t_arg_item *item)
{
	if (ft_strcmp(item->name, "|") == 0)
		item->type = PIPE;
	else if (ft_strcmp(item->name, ">") == 0)
		item->type = REDIR;
	else
		item->type = ARGUMENT;
}

void run_cmd(t_minishell *mini, t_arg_item *arg_item)
{
	t_arg_item *temp;

	temp = arg_item;
	if (mini->pipe->count == 0)
		return ;
	while (temp)
	{
		to_lower_case(arg_item->name);
		temp = temp->next;
	}
	if (is_builtin(mini->arg_item->name, NULL))
		builtins(mini);
	else if (ft_strcmp(mini->arg_item->name, "history") == 0)
		show_working_history(mini);
	else
		execute(mini, arg_item);
	ft_close(mini->pipe->pipein);
	ft_close(mini->pipe->pipeout);
	mini->pipe->pipein = -1;
	mini->pipe->pipeout = -1;
	mini->pipe->count = 0;
}

void	redir_exec(t_minishell *mini, t_arg_item *arg_item)
{
	int pipe;
	t_arg_item *next_arg;
	t_arg_item *prev_arg;

	pipe = 0;
	prev_arg = get_prev_arg(arg_item);
	next_arg = get_next_arg(arg_item);
	printf("arg %s\n", arg_item->name);
	if (next_arg)
		printf("next %s\n", next_arg->name);
		if (prev_arg)
		printf("prev %s\n", prev_arg->name);
	if (check_type(prev_arg, PIPE))
	{
		pipe = shellpipe(mini);
		printf("pipe %d\n", pipe);
	}
	if (next_arg && pipe != 1)
	{
		redir_exec(mini, next_arg->next);
		printf("exit redir\n");
	}
	printf("i am here bitch\n");
	if ((check_type(prev_arg, PIPE) || !prev_arg) && pipe != 1 && mini->no_exec == 0)
	{
		run_cmd(mini, arg_item);
		printf("exit epta\n");
	}
	printf("pipein %d\n", mini->pipe->pipein);
}

void	minishell(t_minishell *mini)
{
	t_arg_item *arg_item;
	int state;

	arg_item = mini->arg_item;
	while (mini->arg_item)
	{
		mini->pipe->count = 1;
		mini->pipe->daddy = 1;
		mini->last = 1;
		redir_exec(mini, arg_item);
		ft_close(mini->pipe->pipein);
		ft_close(mini->pipe->pipeout);
		set_fds(mini);
		printf("	stop\n");
		printf("pipein %d\n", mini->pipe->pipein);
		waitpid(-1, &state, 0);
		printf("	stop\n");
		state = WEXITSTATUS(state);
		mini->ret = (mini->last != 0) ? mini->ret : state;
		printf("dad %d\n", mini->pipe->daddy);
		if (mini->pipe->daddy == 0)
			exit(mini->ret);
		printf("epta\n");
		mini->no_exec = 0;
		// if (mini->arg_item)
		// 	mini->arg_item = mini->arg_item->next;
		mini->arg_item = mini->arg_item->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	mini;
	t_pipe		pipe;
	char		*line;

	ft_cpy_env(&mini, envp);
	pipe.flag = 0;
	mini.pipe = &pipe;
	mini.ret = 0;
	mini.work_history = NULL;
	mini.exit = 0;
	mini.is_quote_parse = 0;
	mini.no_exec = 0;
	(void)argc;
	(void)argv;
	line = NULL;
	while (!mini.exit)
	{
		ft_putstr_fd("minishell> ", 1);
		get_next_line(0, &line);
		if (parser(&mini, line) != ERROR)
		{
			add_cmd_to_history(&mini, line);
			free(line);
			minishell(&mini);
		}
	}
	return (SUCCESS);
}
