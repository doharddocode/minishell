#include "minishell.h"

char	*ft_strcpy(char *s1, const char *s2)
{
	size_t	cur;

	cur = 0;
	while (s2[cur] != '\0')
	{
		s1[cur] = s2[cur];
		cur++;
	}
	s1[cur] = '\0';
	return (s1);
}

int add_arg_to_args(t_minishell *mini, char **arg)
{
	//printf("arg to add = [%s]\n", *arg);
	ft_lstadd_back(&(mini->args), ft_lstnew(*arg));
	*arg = NULL;
	return (SUCCESS);
}

int	add_char_to_arg(char **prev_arg, char symb)
{
	size_t new_strlen;
	char *temp;

	if (!*prev_arg)
	{
		*prev_arg = ft_strnew(1);
		if (!*prev_arg)
			return (ERROR);
		*prev_arg[0] = symb;
	}
	else if (ft_strlen(*prev_arg) > 0)
	{
		new_strlen = ft_strlen(*prev_arg) + 1;
		temp = ft_strnew(new_strlen);
		if (!temp)
			return (ERROR);
		ft_strcpy(temp, *prev_arg);
		temp[ft_strlen(*prev_arg)] = symb;
		ft_free_str(*prev_arg);
		*prev_arg = ft_strnew(new_strlen);
		if (!*prev_arg)
			return (ERROR);
		ft_strcpy(*prev_arg, temp);
		ft_free_str(temp);
	}
	return (SUCCESS);
}

int skip_spaces(const char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (--i);
}

int parser(t_minishell *mini, const char *str)
{
	int i;
	char *arg;

	i = 0;
	arg = NULL;
	mini->args = NULL;
	while (str[i])
	{
		if (str[i] != ' ')
			add_char_to_arg(&arg, str[i]);
		if (str[i] == ' ')
		{
			i = skip_spaces(str, i);
			add_arg_to_args(mini, &arg);
		}
		i++;
	}
	add_arg_to_args(mini, &arg);
	builtins(mini);
	return (SUCCESS);
}