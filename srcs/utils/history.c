/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:27:50 by mrosette          #+#    #+#             */
/*   Updated: 2021/08/03 20:27:51 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_cmd_to_history(t_minishell *mini, char *cmd)
{
	char	*result;

	result = NULL;
	if (cmd)
	{
		result = ft_strinit(ft_strlen(cmd), cmd);
		if (result)
			ft_lstadd_back(&(mini->work_history), ft_lstnew(result));
	}
}

static t_list	**line_add(t_list **line, char *cont, char *sep, char *cnt)
{
	ft_lstadd_back(line, ft_lstnew(sep));
	ft_lstadd_back(line, ft_lstnew(cnt));
	ft_lstadd_back(line, ft_lstnew(cont));
	ft_free_str(cnt);
	return (line);
}

static void	writes(t_list *tmp)
{
	int	i;

	i = 0;
	while (((char *)(tmp->content))[i])
		write(1, &(tmp->content)[i++], 1);
	if (tmp->next)
		write(1, " ", 1);
	else
		write(1, "\n", 1);
}

static void	print_history_line(t_list **line, char *content,
			char *sep, int counter)
{
	char	*cnt;
	t_list	*tmp;
	t_list	*tmp2;

	cnt = ft_itoa(counter);
	if (!cnt)
		return ;
	tmp = *line_add(line, content, sep, cnt);
	while (tmp)
	{
		if (tmp->content)
			writes(tmp);
		tmp = tmp->next;
	}
	while (*line)
	{
		tmp2 = *line;
		*line = (*line)->next;
		free(tmp2);
	}
}

int	show_working_history(t_minishell *mini)
{
	int		counter;
	t_list	*line;
	t_list	*history;

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
