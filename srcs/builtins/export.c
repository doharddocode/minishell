#include "minishell.h"

static int	error_handle(t_arg_item *args, int valid_value)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd("'", 2);
	if (valid_value == -1 && args->next)
		ft_putstr_fd(args->next->name, 2);
	else
		ft_putstr_fd(args->name, 2);
	ft_putstr_fd("': ", 2);
	ft_putendl_fd("not a valid identifier", 2);
	return (ERROR);
}

static int	check_env(t_arg_item *args, char *env_name)
{
	int	i;

	i = 0;
	if (env_name[i] == '=')
		return (-1);
	if (env_name[i] != '_' && ft_isdigit(env_name[i]))
		return (0);
	while (env_name[i] && env_name[i] != '=')
	{
		if (!ft_isalpha(env_name[i]) && !ft_isdigit(env_name[i])
			&& env_name[i] != '_')
			return (0);
		i++;
	}
	if (args->next && ft_strncmp(args->next->name, "=", 1))
		return (0);
	return (1);
}

static void	add_env(t_minishell *mini, char *arg)
{
	int		i;
	char	*env_name;
	char	*env_val;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	env_name = ft_substr(arg, 0, i);
	if (!env_name)
		return ;
	if (i == (int)ft_strlen(arg))
		env_val = ft_strnew(1);
	else
		env_val = ft_substr(arg, i + 1, ft_strlen(arg));
	if (!env_val)
		return ;
	if (!is_env_exist(mini->envp, env_name))
		ft_envp_addback_node(&mini->envp, ft_envp_new_node(env_name, env_val));
	else
		ft_envp_update_node(mini->envp, env_name, env_val);
	ft_free_str(env_name);
	ft_free_str(env_val);
}

int	ft_export(t_minishell *mini)
{
	int			is_valid_env;
	t_arg_item	*args;

	args = mini->arg_item->next;
	if (!args)
	{
		sort_envp_list(mini->envp);
		print_envp_list(mini->envp, "declare -x");
	}
	else
	{
		is_valid_env = check_env(args, args->name);
		if (is_valid_env == 1)
			add_env(mini, args->name);
		else
			return (error_handle(args, is_valid_env));
	}
	return (SUCCESS);
}
