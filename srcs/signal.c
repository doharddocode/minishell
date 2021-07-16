#include "minishell.h"

void handle_signal(int signal_code)
{
	if (signal_code == SIGINT)
	{
		sig.sigint = 1;
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("minishell> ", 2);
		sig.exit_status = 1;
	}
}

void	init_signal(void)
{
	sig.sigint = 0;
	sig.sigquit = 0;
	sig.pid = 0;
	sig.exit_status = 0;
}
