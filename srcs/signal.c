/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:27:10 by mrosette          #+#    #+#             */
/*   Updated: 2021/08/03 20:27:10 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	code_one(void)
{
	if (g_sig.pid == 0)
	{
		g_sig.sigint = 1;
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig.exit_status = 1;
	}
	else
	{
		ft_putstr_fd("\n", 2);
		g_sig.exit_status = 130;
	}
}

void	code_two(char *num)
{
	ft_putstr_fd("Quit: ", 2);
	ft_putendl_fd(num, 2);
	g_sig.exit_status = 131;
	g_sig.sigquit = 1;
}

void	handle_signal(int signal_code)
{
	char	*num;

	if (signal_code == SIGINT)
	{
		code_one();
	}
	else if (signal_code == SIGQUIT)
	{
		if (g_sig.pid != 0)
		{
			num = ft_itoa(signal_code);
			if (num)
			{
				code_two(num);
				ft_free_str(num);
			}
		}
		else
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	init_signal(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 0;
	g_sig.exit_status = 0;
}
