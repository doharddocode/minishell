#include "minishell.h"

static char *start_parse_var(t_minishell *mini, char *arg, int *i)
{
	char *var_name;
	char *var_value;
	int var_len;

	var_len = 0;
	while (arg[*i] && arg[*i] != '$')
	{
		var_len++;
		(*i)++;
	}
	var_name = ft_substr((arg), *i - var_len, var_len);
	if (!var_name || !var_len)
		return (NULL);
	if (!is_var_exist(mini, var_name))
		return (NULL);
	var_value = get_var_value(mini, var_name);
	if (!var_value)
		return (NULL);
	*i -= 1;
	return (var_value);
}

int is_var_exist(t_minishell *mini, char *var_name)
{
	t_envp *envp;

	envp = mini->envp;
	while (envp)
	{
		if (!ft_strncmp(envp->key, var_name, ft_strlen(var_name)))
			return (1);
		envp = envp->next;
	}
	return (0);
}

char *get_var_value(t_minishell *mini, char *var_name)
{
	t_envp *envp;
	char *result;

	envp = mini->envp;
	result = NULL;
	while (envp)
	{
		if (!ft_strncmp(envp->key, var_name, ft_strlen(var_name)))
		{
			result = ft_strinit(ft_strlen(envp->value), envp->value);
			return (result);
		}
		envp = envp->next;
	}
	return (result);
}

char *parse_env_vars(t_minishell *mini, char *arg)
{
	int i;
	char *result;
	t_list *res_lst;

	i = 0;
	res_lst = NULL;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			i++;
			ft_lstadd_back(&res_lst, ft_lstnew(start_parse_var(mini, arg, &i)));
		}
		i++;
	}
	result = t_list_to_string(res_lst);
	ft_lstclear(&res_lst, free);
	return (result);
}