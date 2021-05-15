#include "minishell.h"

int ft_arr_size(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return (i);
	while (arr[i])
		i++;
	return (i);
}

int ft_cpy_env(t_minishell *mini, char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (ERROR);
	mini->envp = (char **)malloc(ft_arr_size(envp) * sizeof(char *) + 1);
	if (mini->envp)
	{
		while (envp[i])
		{
			mini->envp[i] = ft_strdup(envp[i]);
			if (!mini->envp[i])
			{
				ft_free_arr(mini->envp);
				return (ERROR);
			}
			i++;
		}
		mini->envp[i] = NULL;
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	mini;
	char		*line;

	ft_cpy_env(&mini, envp);
	mini.exit = 0;
	(void)argc;
	(void)argv;
	line = NULL;
	while (!mini.exit)
	{
		ft_putstr_fd("minishell> ", 1);
		get_next_line(0, &line);
		parser(&mini, line);
		free(line);
		/**исполнение**/
	}
	return (0);
}
