#include "minishell.h"

int check_type(t_arg_item *arg_item, int type)
{
	if (arg_item && arg_item->type == type)
		return (1);
	return (0);
}


void	redir_exec(t_minishell *mini, t_arg_item *arg_item)
{
	int pipe;
	t_arg_item *next_arg;
	t_arg_item *prev_arg;

	pipe = 0;
	prev_arg = NULL;
	prev_arg = get_item(mini, arg_item, PREV_ITEM);
	next_arg = get_item(mini, arg_item, NEXT_ITEM);
	if (check_type(prev_arg, PIPE))
	{
		pipe = shellpipe(mini);
		printf("%d\n", pipe);
	}
	if (next_arg && pipe != 1)
		redir_exec(mini, next_arg->next);
	if ((check_type(prev_arg, PIPE) || !prev_arg) && pipe != 1 && mini->no_exec == 0)
	{
		run_cmd(mini, arg_item);
	}
}

void run_cmd(t_minishell *mini, t_arg_item *item)
{
	t_arg_item *temp;

	temp = item;
	while (temp)
	{
		to_lower_case(item->name);
		temp = temp->next;
	}
	if (is_builtin(mini->arg_item->name, NULL))
		builtins(mini);
	else if (ft_strcmp(mini->arg_item->name, "history") == 0)
		show_working_history(mini);
	else
		execute(mini);
}

void set_arg_type(t_arg_item *item)
{
	if (ft_strcmp(item->name, "|") == 0)
		item->type = PIPE;
	else
		item->type = ARGUMENT;
}

void	minishell(t_minishell *mini)
{
	t_arg_item *arg_item;
	int state;

	arg_item = mini->arg_item;
	while (arg_item)
	{
		mini->pipe->count = 1;
		mini->pipe->daddy = 1;
		mini->last = 1;
		redir_exec(mini, arg_item);
		ft_close(mini->pipe->pipein);
		ft_close(mini->pipe->pipeout);
		set_fds(mini);
		waitpid(-1, &state, 0);
		state = WEXITSTATUS(state);
		mini->ret = (mini->last != 0) ? mini->ret : state;
		if (mini->pipe->daddy == 0)
			exit(mini->ret);
		mini->exec_no = 0;
		arg_item = arg_item->next;
		mini->no_exec = 0;
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
