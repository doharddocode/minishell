#include "minishell.h"

static int set_oldpwd(t_envp *envp)
{
	char cwd[255];

	if (!getcwd(cwd, 255))
		return (ERROR);
	if (is_env_exist(envp, "OLDPWD"))
	{
		ft_envp_update_node(&envp, "OLDPWD", cwd);
	}
	else
		ft_envp_addback_node(&envp, ft_envp_new_node("OLDPWD", cwd));
	return (SUCCESS);
}

static int set_path(t_minishell *mini, t_envp *envp, int flag)
{
	int result;
	t_envp *envp_node;

	if (flag == 0)
	{
		envp_node = ft_copy_envp_node(ft_get_envp_node(envp, "OLDPWD"));
		if (!envp_node)
			return (mini->ret = ERROR);
		set_oldpwd(envp);
		ft_putendl_fd(envp_node->value, 1);
	}
	else
	{
		set_oldpwd(envp);
		envp_node = ft_copy_envp_node(ft_get_envp_node(envp, "HOME"));
		if (!envp_node)
			return (mini->ret = ERROR);
	}
	result = chdir(envp_node->value);
	return (result);
}

int	ft_cd(t_minishell *mini)
{
	int result;
	t_list *args;
	t_envp *envp;

	envp = mini->envp;
	args = mini->args->next;
	if (!args)
		return (set_path(mini, envp, 1));
	else if (!ft_strncmp(args->content, "-", 1))
		result = set_path(mini, envp, 0);
	else
	{
		set_oldpwd(envp);
		result = chdir(args->content);
		if (result < 0)
			return (mini->ret = ERROR);
	}
	return (mini->ret = result);
}