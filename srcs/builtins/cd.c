#include "minishell.h"

static int set_oldpwd(t_envp *envp)
{
	char *oldpwd;
	char cwd[255];

	if (!getcwd(cwd, 255))
		return (ERROR);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return (ERROR);
	if (is_env_exist(envp, "OLDPWD"))
		ft_envp_update_node(envp, "OLDPWD", oldpwd);
	else
		ft_envp_addback_node(&envp, ft_envp_new_node(&oldpwd));
	return (SUCCESS);
}

static int set_path(t_envp *envp, int flag)
{
	int result;
	char *env_path;

	if (flag == 0)
	{
		env_path = ft_get_envp_node(envp, "OLDPWD")->value;
		if (!env_path)
			return (ERROR);
		set_oldpwd(envp);

	}
	else
	{
		set_oldpwd(envp);
		env_path = ft_get_envp_node(envp, "HOME")->value;
		if (!env_path)
			return (ERROR);
	}
	result = chdir(env_path);
	return (result);
}

int	ft_cd(t_minishell *mini)
{
	int result;
	t_list *args;
	t_envp *envp = mini->envp;

	args = mini->args->next;
	if (!args)
		return (set_path(envp, 1));
	else if (!ft_strncmp(args->content, "-", 1))
		result = set_path(envp, 0);
	else
	{
		result = chdir(args->content);
		if (result < 0)
			return (ERROR);
	}
	return (result);
}