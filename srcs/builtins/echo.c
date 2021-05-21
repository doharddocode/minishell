#include "minishell.h"

static int check_option(t_list **args, char *option_name)
{
	int is_n = 0;

	while (*args && !ft_strncmp((*args)->content, option_name, ft_strlen(option_name)))
	{
		if (!ft_strncmp((*args)->content, option_name, ft_strlen(option_name))
			&& ft_strlen((*args)->content) == ft_strlen(option_name))
		{
			is_n++;
			(*args) = (*args)->next;
		}
		else
			break;
	}
	if (is_n)
		return (1);
	return (0);
}

int ft_echo(t_minishell *mini)
{
	t_list *args;
	int n_opt;

	args = mini->args->next;
	n_opt = check_option(&args, "-n");
	while (args && ft_lstsize(mini->args) > 1)
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