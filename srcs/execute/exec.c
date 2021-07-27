#include "minishell.h"

static char *join_path(char *path1, char *path2)
{
	char *temp;
	char *result;

	temp = ft_strjoin(path1, "/");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, path2);
	ft_free_str(temp);
	if (!result)
		return (NULL);
	return (result);
}

char *check_dir(char *path, char *cmd)
{
	DIR *catalog;
	struct dirent *item;
	char *result;

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

int launch_exec(t_minishell *mini, char *exec_path, t_arg_item *arg_item)
{
	int return_val;
	char **envp_arr;
	char **args_arr;

	sig.pid = fork();
	if (sig.pid == 0)
	{
		envp_arr = t_enpv_to_array(mini->envp);
		args_arr = arg_to_array(arg_item);
		if (!envp_arr || !args_arr)
			return (mini->ret = ERROR);
		if (ft_strchr(exec_path, '/'))
			mini->ret = execve(exec_path, args_arr, envp_arr);
		int i = 0;
		while(args_arr[i])
			free(args_arr[i++]);
		free(args_arr);
		while(envp_arr[i])
			free(envp_arr[i++]);
		free(envp_arr);
		return_val = get_errror_msg(exec_path);
		exit(return_val);
		close(mini->pipe->pipein);
	}
	else
		waitpid(sig.pid, &return_val, 0);
	if (sig.sigint == 1 || sig.sigquit == 1)
		return (sig.exit_status);
	if (return_val == 32256 || return_val == 32512)
		return_val /= 256;
	else
		return_val = return_val != 0;
	return (return_val);
}

int execute(t_minishell *mini, t_arg_item *arg_item)
{
	int i;
	int return_val;
	char *exec_path;
	char **bin;
	t_envp *path_env;

	i = 0;
	exec_path = NULL;
	path_env = ft_get_envp_node(mini->envp, "PATH");
	if (!path_env)
		return (mini->ret = ERROR);
	bin = ft_split(path_env->value, ':');
	if (!bin)
		return (ERROR);
	while (arg_item && arg_item->name && bin[i] && !exec_path)
	{
		exec_path = check_dir(bin[i], arg_item->name);
		i++;
	}
	if (exec_path)
		return_val = launch_exec(mini, exec_path, arg_item);
	else if (arg_item)
		return_val = launch_exec(mini, arg_item->name, arg_item);
	i = 0;
	while (bin[i])
	{
		free(bin[i++]);
	}
	free(bin);
	free(exec_path);
	return (return_val);
}
