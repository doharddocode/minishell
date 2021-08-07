#include "minishell.h"

static char	*join_path(char *path1, char *path2)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(path1, "/");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, path2);
	ft_free_str(temp);
	if (!result)
		return (NULL);
	return (result);
}

char	*check_dir(char *path, char *cmd)
{
	DIR				*catalog;
	struct dirent	*item;
	char			*result;

	result = NULL;
	catalog = opendir(path);
	if (!catalog)
		return (NULL);
	item = readdir(catalog);
	while (item)
	{
		if (!ft_strcmp(item->d_name, cmd))
			result = join_path(path, item->d_name);
		item = readdir(catalog);
	}
	closedir(catalog);
	return (result);
}

int	launch_exec(t_minishell *mini, char *exec_path, t_arg_item *arg_item)
{
	int		return_val;
	char	**envp_arr;
	char	**args_arr;

	g_sig.pid = fork();
	if (g_sig.pid == 0)
	{
		envp_arr = t_enpv_to_array(mini->envp);
		args_arr = arg_to_array(arg_item);
		if (!envp_arr || !args_arr)
			return (mini->ret = ERROR);
		if (ft_strchr(exec_path, '/'))
			mini->ret = execve(exec_path, args_arr, envp_arr);
		ft_free_arr(args_arr);
		ft_free_arr(envp_arr);
		return_val = get_errror_msg(exec_path);
		exit(return_val);
	}
	else
		waitpid(g_sig.pid, &return_val, 0);
	if (g_sig.sigint == 1 || g_sig.sigquit == 1)
		return (g_sig.exit_status);
	return_val = ret_val(return_val);
	return (return_val);
}

int	exec_ret(t_minishell *mini, char *exec_path, t_arg_item *arg_item)
{
	int	return_val;

	if (exec_path)
		return_val = launch_exec(mini, exec_path, arg_item);
	else
		return_val = launch_exec(mini, arg_item->name, arg_item);
	return (return_val);
}

int	execute(t_minishell *mini, t_arg_item *arg_item)
{
	int		i;
	int		return_val;
	char	*exec_path;
	char	**bin;
	t_envp	*path_env;

	i = 0;
	exec_path = NULL;
	path_env = ft_get_envp_node(mini->envp, "PATH");
	if (!path_env)
		return (item_not_found(mini, arg_item->name,
				"No such file or director\n"));
	bin = ft_split(path_env->value, ':');
	if (!bin)
		return (ERROR);
	while (arg_item && arg_item->name && bin[i] && !exec_path)
	{
		exec_path = check_dir(bin[i], arg_item->name);
		i++;
	}
	return_val = exec_ret(mini, exec_path, arg_item);
	ft_free_arr(bin);
	free(exec_path);
	return (return_val);
}
