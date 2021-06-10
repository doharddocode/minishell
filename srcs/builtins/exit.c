#include "minishell.h"

static int is_numeric(char *str)
{
	int i;

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

int ft_exit(t_minishell *mini)
{
	ft_putstr_fd("exit ", 2);
	mini->exit = 1;
	if (mini->args)
	{
		mini->args = mini->args->next;
		if (mini->args && mini->args->next)
		{
			mini->ret = 1;
			ft_putendl_fd("minishell: exit: too many arguments", 2);
		}
		else if (mini->args && !is_numeric(mini->args->content))
		{
			mini->ret = 255;
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(mini->args->content, 2);
			ft_putendl_fd(": numeric argument required", 2);
		}
		else if (mini->args && mini->args->content)
			mini->ret = ft_atoi(mini->args->content);
		else
			mini->ret = 0;
	}
	return (mini->ret);
}