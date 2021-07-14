#include "minishell.h"

void add_cmd_to_history(t_minishell *mini, char *cmd)
{
	char *result;

	if (cmd)
	{
		result = ft_strinit(ft_strlen(cmd), cmd);
		if (result)
			ft_lstadd_back(&mini->work_history, ft_lstnew(result));
	}
}

static void print_history_line(t_list *line, char *content,
							   char *sep, int counter)
{
	int i;

	ft_lstadd_back(&line, ft_lstnew(sep));
	ft_lstadd_back(&line, ft_lstnew(ft_itoa(counter)));
	ft_lstadd_back(&line, ft_lstnew(content));
	while (line)
	{
		if (line->content)
		{
			i = 0;
			while (((char *)(line->content))[i])
				write(1, &(line->content)[i++], 1);
			if (line->next)
				write(1, " ", 1);
			else
				write(1, "\n", 1);
		}
		line = line->next;
	}
}

int show_working_history(t_minishell *mini)
{
	int counter;
	t_arg_item *line;
	t_arg_item *history;

	// counter = 1;
	// history = mini->work_history;
	// while (history)
	// {
	// 	line = NULL;
	// 	if (history->content)
	// 		print_history_line(line, history->content, "  ", counter++);
	// 	ft_lstclear(&line, free);
	// 	history = history->next;
	// }
	return (mini->ret = SUCCESS);
}
