#include "minishell.h"

char *t_arg_to_string(t_arg *arg)
{
	char *result;
	char *temp_str;
	char *symb_to_str;
	t_arg *temp_node;

	temp_node = arg;
	result = ft_strnew(1);
	if (!result || !arg)
		return (NULL);
	while (temp_node)
	{
		temp_str = result;
		if (!temp_node->symb)
			return (NULL);
		symb_to_str = ft_strinit(1, &(temp_node->symb));
		if (!symb_to_str)
			return (NULL);
		result = ft_strjoin(result, symb_to_str);
		ft_free_str(temp_str);
		ft_free_str(symb_to_str);
		temp_node = temp_node->next;
	}
	return (result);
}

char	*ft_remove_chrnstr(const char *str, char symb)
{
	int		i;
	int		j;
	char	*result;

	result = (char *)malloc(ft_strlen(str) * sizeof(char) + 1);
	if (result)
	{
		i = 0;
		j = 0;
		while (str[i])
		{
			if (str[i] != symb)
				result[j++] = str[i];
			i++;
		}
		result[j] = '\0';
		return (result);
	}
	return (NULL);
}

int add_arg_to_args(t_minishell *mini, char *arg)
{
	t_arg *arg_list;
	int i;

	i = 0;
	arg_list = NULL;
	while (arg[i])
	{
		parse_double_quotes(mini, &arg_list, arg, &i);
		parse_env_vars(mini, &arg_list, arg, &i);
		if (arg[i])
		{
			parse_env_vars(mini, &arg_list, arg, &i);
			t_arg_addnode_back(&arg_list, t_arg_new_node(arg[i]));
			i++;
		}
	}
	ft_lstadd_back(&(mini->args), ft_lstnew(t_arg_to_string(arg_list)));
	return (SUCCESS);
}

int skip_spaces(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (--i);
}

int get_arg_len(t_minishell *mini, char *str, int i)
{
	int result;

	result = 0;
	if (str[i] == '"')
	{
		i++;
		if (!is_valid_double_quote(str))
			return (0);
		while (str[i++] != '"')
			result++;
		return (result + 2);
	}
	while ((str[i] && str[i] != ' ' && str[i] != '"'))
	{
		result++;
		i++;
	}
	return (result);
}

int parser(t_minishell *mini, char *str)
{

	int arg_len;
	char *arg;
	int i;

	i = 0;
	mini->args = NULL;
	arg = NULL;
	while (str[i])
	{
		i = skip_spaces(str, i) + 1;
		arg_len = get_arg_len(mini, str, i);
		if (!arg_len)
			return (ERROR);
		arg = ft_substr(str, i, arg_len);
		if (!arg)
			return (ERROR);
		add_arg_to_args(mini, arg);
		i += arg_len;
		i = skip_spaces(str, i);
		i++;
	}
	return (SUCCESS);
}