#include "minishell.h"

void handle_signal(int signal_code)
{
	char	*num;

	if (signal_code == SIGINT)
	{
		if (sig.pid == 0)
		{
			sig.sigint = 1;
			ft_putstr_fd("\n", 2);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			sig.exit_status = 1;
		}
		else
		{
			ft_putstr_fd("\n", 2);
			sig.exit_status = 130;
		}
	}
	else if (signal_code == SIGQUIT)
	{
		if (sig.pid != 0)
		{
			num = ft_itoa(signal_code);
			if (num)
			{
				ft_putstr_fd("Quit: ", 2);
				ft_putendl_fd(num, 2);
				sig.exit_status = 131;
				sig.sigquit = 1;
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
	sig.sigint = 0;
	sig.sigquit = 0;
	sig.pid = 0;
	sig.exit_status = 0;
}
