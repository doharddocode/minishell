#include "minishell.h"

char	**t_enpv_to_array(t_envp *envp)
{
	int i;
	char **envp_arr;

	i = 0;
	envp_arr = (char **)malloc(sizeof(char *) * (ft_envp_size(envp) + 1));
	if (!envp_arr)
		return (NULL);
	while (envp)
	{
		envp_arr[i++] = env_to_str(NULL, envp->key, envp->value, "=");
		envp = envp->next;
	}
	envp_arr[i] = NULL;
	return (envp_arr);
}

char	**arg_to_array(t_arg_item *arg_item)
{
	int i;
	char **result_arr;

	i = 0;
	result_arr = (char **)malloc(sizeof(char *) * (arg_item_count(arg_item) + 1));
	if (!result_arr)
		return (NULL);
	while (arg_item)
	{
		result_arr[i++] = ft_strdup(arg_item->name);
		arg_item = arg_item->next;
	}
	result_arr[i] = NULL;
	return (result_arr);
}
