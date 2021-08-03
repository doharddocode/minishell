/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:28:46 by mrosette          #+#    #+#             */
/*   Updated: 2021/08/03 20:28:47 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

void	message(t_arg_item *tmp)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(tmp->name, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

int	ft_exit(t_minishell *mini)
{
	t_arg_item	*tmp;

	ft_putstr_fd("exit\n", 2);
	mini->exit = 1;
	tmp = mini->arg_item;
	if (tmp)
	{
		tmp = tmp->next;
		if (tmp && tmp->next)
		{
			mini->ret = 1;
			ft_putendl_fd("minishell: exit: too many arguments", 2);
		}
		else if (tmp && !is_numeric(tmp->name))
		{
			mini->ret = 255;
			message(tmp);
		}
		else if (tmp && tmp->name)
			mini->ret = ft_atoi(tmp->name);
		else
			mini->ret = 0;
	}
	return (mini->ret);
}
