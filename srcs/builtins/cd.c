#include "minishell.h"

static void	print_cd_error(t_arg_item *args)
{
	ft_putstr_fd("cd: ", 2);
	if (args->next)
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args->name, 2);
}

static int	set_oldpwd(t_envp *envp)
{
	char	cwd[255];

	if (!getcwd(cwd, 255))
		return (ERROR);
	if (is_env_exist(envp, "OLDPWD"))
	{
		ft_envp_update_node(envp, "OLDPWD", cwd);
	}
	else
		ft_envp_addback_node(&envp, ft_envp_new_node("OLDPWD", cwd));
	return (SUCCESS);
}

static int	set_path(t_minishell *mini, t_envp *envp, int flag)
{
	int		result;
	t_envp	*envp_node;

	if (flag == 0)
	{
		envp_node = ft_copy_envp_node(ft_get_envp_node(envp, "OLDPWD"));
		if (!envp_node)
			return (item_not_found(mini, "cd", "OLDPWD not set\n"));
		set_oldpwd(envp);
		ft_putendl_fd(envp_node->value, 1);
	}
	else
	{
		set_oldpwd(envp);
		envp_node = ft_copy_envp_node(ft_get_envp_node(envp, "HOME"));
		if (!envp_node)
			return (item_not_found(mini, "cd", "HOME not set\n"));
	}
	result = chdir(envp_node->value);
	ft_free_str(envp_node->value);
	ft_free_str(envp_node->key);
	free(envp_node);
	envp_node = NULL;
	return (result);
}

int	ft_cd(t_minishell *mini)
{
	int			result;
	t_arg_item	*args;
	t_envp		*envp;

	envp = mini->envp;
	args = mini->arg_item->next;
	if (!args)
		return (set_path(mini, envp, 1));
	else if (!ft_strncmp(args->name, "-", 1))
		result = set_path(mini, envp, 0);
	else
	{
		set_oldpwd(envp);
		result = chdir(args->name);
		if (result < 0)
			result *= -1;
		if (result != 0)
			print_cd_error(args);
	}
	return (mini->ret = result);
}
