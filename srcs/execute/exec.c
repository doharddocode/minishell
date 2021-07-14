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
	return (result);
}

int launch_exec(t_minishell *mini, char *exec_path, t_arg_item *arg_item)
{
	char **envp_arr;
	char **args_arr;
	pid_t fork_pid;

	fork_pid = fork(); //убрать глобалку
	if (fork_pid == 0)
	{
		envp_arr = t_enpv_to_array(mini->envp);
		printf("%s\n", arg_item->name);
		args_arr = arg_to_array(arg_item);
		if (!envp_arr || !args_arr)
			return (mini->ret = ERROR);
		printf("args %s\n", args_arr[0]);
		printf("path %s\n", exec_path);
		if (ft_strchr(exec_path, '/'))
			mini->ret = execve(exec_path, args_arr, envp_arr);
		exit(mini->ret);
	}
	else
	{
		waitpid(fork_pid, &mini->ret, 0);
		printf("DAD ALIVE\n");
	}
	return (mini->ret);
}

int execute(t_minishell *mini, t_arg_item *arg_item)
{
	int i;
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
		launch_exec(mini, exec_path, arg_item);
	return (mini->ret);
}
