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
	prev_arg = get_item(mini, arg_item, PREV_ITEM);
	next_arg = get_item(mini, arg_item, NEXT_ITEM);
	if (check_type(prev_arg, PIPE))
	{
		//new pipe
		pipe = 2;
	}
	if (next_arg && check_type(prev_arg, PIPE) && pipe != 1)
	{
		redir_exec(mini, next_arg->next);
	}
	if ((check_type(prev_arg, PIPE) || !prev_arg)
		&& pipe != 1)
		{
			printf("\ttoken=%s\n", arg_item->name);
		}
}

// int minishell_old(t_minishell *mini)
// {
// 	t_list *args;

// 	args = mini->args;
// 	if (!args)
// 		return (mini->ret = ERROR);
// 	while (args)
// 	{
// 		to_lower_case(args->content);
// 		args = args->next;
// 	}

// 	if (is_builtin(mini->args->content, NULL))
// 		builtins(mini);
// 	else if (ft_strcmp(mini->args->content, "history") == 0)
// 		show_working_history(mini);
// 	else
// 		execute(mini);
// 	return (SUCCESS);
// }

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

	arg_item = mini->arg_item;
	while (arg_item)
	{
		//printf("arg=%s[%d]\n", arg_item->name, arg_item->type);
		redir_exec(mini, arg_item);
		arg_item = arg_item->next;
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
