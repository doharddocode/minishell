#include "minishell.h"

static int check_option_n(t_list  *args)
{
	if (!ft_strncmp(args->content, "-n", 2))
		return (1);
	return (0);
}

t_list *delete_root(t_list *args_root)
{
	t_list *temp;
	temp = args_root->next;
	ft_free_str(args_root->content);
	free(args_root);
	return (temp);
}

int ft_echo(t_minishell *mini)
{
	t_list *args;
	int n_opt;

	args = delete_root(mini->args);
	n_opt = check_option_n(args);
	if (n_opt)
		args = args->next;
	while (args)
	{
		ft_putstr_fd(args->content, 1);
		if (args->next)
			write(1, " ", 1);
		args = args->next;
	}
	if (!n_opt)
		write(1, "\n", 1);
	return (SUCCESS);
}