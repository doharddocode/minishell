#include "minishell.h"

void add_cmd_to_history(t_minishell *mini, char *cmd)
{
	char *result;

	result = NULL;
	if (cmd)
	{
		result = ft_strinit(ft_strlen(cmd), cmd);
		if (result)
			ft_lstadd_back(&(mini->work_history), ft_lstnew(result));
	}
}

static void print_history_line(t_list **line, char *content, char *sep, int counter)
{
	int i;
	char *cnt;
	t_list *tmp;

	cnt = ft_itoa(counter);
	if (!cnt)
		return ;
	ft_lstadd_back(line, ft_lstnew(sep));
	ft_lstadd_back(line, ft_lstnew(cnt));
	ft_lstadd_back(line, ft_lstnew(content));
	ft_free_str(cnt);
	tmp = *line;
	while (tmp)
	{
		if (tmp->content)
		{
			i = 0;
			while (((char *)(tmp->content))[i])
				write(1, &(tmp->content)[i++], 1);
			if (tmp->next)
				write(1, " ", 1);
			else
				write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
	t_list *tmp2;
	while (*line)
	{
		tmp2 = *line;
		*line = (*line)->next;
		free(tmp2);
	}
}

int show_working_history(t_minishell *mini)
{
	int counter;
	t_list *line;
	t_list *history;

	counter = 1;
	history = mini->work_history;
	while (history)
	{
		if (history->content)
		{
			line = NULL;
			print_history_line(&line, history->content, "  ", counter++);
		}
		history = history->next;
	}
	return (SUCCESS);
}
