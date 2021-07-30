#include "minishell.h"

static void print_exit_status(t_minishell *mini, t_arg **arglist,
							  char *arg, int *i)
{
	int cnt;
	char	*exit_status;

	exit_status = ft_itoa(mini->ret);
	if (exit_status)
	{
		next_symbol(arg, i);
		cnt = 0;
		while (exit_status[cnt])
			t_arg_addnode_back(arglist, t_arg_new_node(exit_status[cnt++]));
		ft_free_str(exit_status);
	}
	next_symbol(arg, i);
}

static char *start_parse_var(t_minishell *mini, char *arg, int *i)
{
	char *var_name;
	char *var_value;
	int var_len;

	var_len = 0;
	while (arg[*i] && arg[*i] != '$' && arg[*i] != ' ')
	{
		if (is_shieild_symb(arg[*i]) || arg[*i] == '"')
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
	ft_free_str(var_name);
	if (!var_value)
		return (NULL);
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
	return (NULL);
}

static char *parse_env_vars_inner(t_minishell *mini, char *arg, int *i)
{
	t_list *res_lst;
	char *result;

	res_lst = NULL;
	(*i)++;
	ft_lstadd_back(&res_lst, ft_lstnew(start_parse_var(mini, arg, i)));
	result = t_list_to_string(res_lst);
	ft_lstclear(&res_lst, free);
	return (result);
}

void parse_env_vars(t_minishell *mini, t_arg **arg_list, char *arg, int *i)
{
	int j;
	char *env_var;

	if (arg[*i] == '$' && (arg[(*i) + 1] != ' ') && ft_strlen(&arg[*i]) > 1)
	{
		if (arg[(*i) + 1] == '?')
			print_exit_status(mini, arg_list, arg, i);
		else
		{
			env_var = parse_env_vars_inner(mini, arg, i);
			j = 0;
			while (env_var && env_var[j])
			{
				t_arg_addnode_back(arg_list, t_arg_new_node(env_var[j]));
				j++;
			}
			parse_env_vars(mini, arg_list, arg, i);
			ft_free_str(env_var);
		}
	}
}
