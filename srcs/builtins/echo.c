/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:28:49 by mrosette          #+#    #+#             */
/*   Updated: 2021/08/03 20:28:50 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_option(t_arg_item **args, char *option_name)
{
	int	is_n;

	is_n = 0;
	while (*args && !ft_strncmp((*args)->name, option_name,
			ft_strlen(option_name)))
	{
		if (!ft_strncmp((*args)->name, option_name, ft_strlen(option_name))
			&& ft_strlen((*args)->name) == ft_strlen(option_name))
		{
			is_n++;
			(*args) = (*args)->next;
		}
		else
			break ;
	}
	if (is_n)
		return (1);
	return (0);
}

int	ft_echo(t_minishell *mini)
{
	t_arg_item	*args;
	int			n_opt;

	args = mini->arg_item->next;
	n_opt = check_option(&args, "-n");
	while (args && arg_item_count(mini->arg_item) > 1 && args->type < REDIR)
	{
		ft_putstr_fd(args->name, 1);
		if (args->next && ft_strlen(args->name) && (args->next->type < REDIR))
		{
			write(1, " ", 1);
		}
		args = args->next;
	}
	if (!n_opt)
		write(1, "\n", 1);
	return (SUCCESS);
}
