#include "minishell.h"

static char *start_parse_var(t_minishell *mini, char *arg, int *i)
{
	char *var_name;
	char *var_value;
	int var_len;

	var_len = 0;
	while (arg[*i] && arg[*i] != '$' && arg[*i] != ' ')
	{
		if (arg[*i] == '\'' || arg[*i] == '"')
			break;
		var_len++;
		(*i)++;
	}
	if (!var_len)
		return (NULL);
	var_name = ft_substr((arg), *i - var_len, var_len);
	if (!var_name)
		return (NULL);
	var_value = get_var_value(mini, var_name);
	if (!var_value)
		return (NULL);
	*i -= 1;
	return (var_value);
}

char *get_var_value(t_minishell *mini, char *var_name)
{
	t_envp *envp;

	envp = mini->envp;
	while (envp)
	{
		if (!ft_strncmp(envp->key, var_name, ft_strlen(var_name))
				&& ft_strlen(var_name) == ft_strlen(envp->key))
			return (ft_strinit(ft_strlen(envp->value), envp->value));
		envp = envp->next;
	}
	return (ft_strnew(1));
}

static char *parse_env_vars_inner(t_minishell *mini, char *arg, int *i)
{
	t_list *res_lst;
	char *result;

	res_lst = NULL;
	while (arg[*i] && arg[*i] != ' ')
	{
		if (arg[*i] == '\'' || arg[*i] == '"')
		{
			break;
		}
		if (arg[*i] == '$')
		{
			(*i)++;
			ft_lstadd_back(&res_lst, ft_lstnew(start_parse_var(mini, arg, i)));
			if (!arg[*i])
				break;
		}
		(*i)++;
	}
	result = t_list_to_string(res_lst);
	ft_lstclear(&res_lst, free);
	return (result);
}

void parse_env_vars(t_minishell *mini, t_arg **arg_list, char *arg, int *i)
{
	int j;
	char *env_var;

	if (arg[*i] == '$')
	{
		env_var = parse_env_vars_inner(mini, arg, i);
		j = 0;
		while (env_var && env_var[j])
		{
			t_arg_addnode_back(arg_list, t_arg_new_node(env_var[j]));
			j++;
		}
	}
}
