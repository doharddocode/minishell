/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:28:03 by mrosette          #+#    #+#             */
/*   Updated: 2021/08/03 20:28:03 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_write(t_minishell *mini, char *buf, int str_len)
{
	size_t	byte;
	size_t	wrote;

	wrote = 0;
	while ((int)wrote < str_len)
	{
		byte = write(mini->fd_temp, buf + wrote, str_len - wrote);
		if (byte >= 0)
			wrote += byte;
	}
}

void	heredoc(t_minishell *mini, t_arg_item *arg)
{
	char	*end;
	size_t	str_len;
	char	*buf;
	int		flag;

	flag = 1;
	end = arg->name;
	ft_close(mini->fd_temp);
	mini->fd_temp = open("tmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	while (flag)
	{
		ft_putstr_fd("> ", 1);
		get_next_line(1, &buf);
		str_len = ft_strlen(buf);
		if (!ft_strcmp(buf, end))
			break ;
		check_write(mini, buf, str_len);
		write(mini->fd_temp, "\n", 1);
		free(buf);
	}
	free(buf);
	ft_close(mini->fd_temp);
	mini->fd_temp = open("tmp", O_RDONLY, S_IRWXU);
	dup2(mini->fd_temp, 0);
	unlink("tmp");
}
