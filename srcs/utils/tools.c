/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:27:49 by mrosette          #+#    #+#             */
/*   Updated: 2021/08/03 20:27:49 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**t_enpv_to_array(t_envp *envp)
{
	int		i;
	char	**envp_arr;

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
	int		i;
	char	**result_arr;

	i = 0;
	result_arr = (char **)malloc(sizeof(char *)
			* (arg_item_count(arg_item) + 1));
	if (!result_arr)
		return (NULL);
	while (arg_item && arg_item->type < REDIR)
	{
		result_arr[i++] = ft_strdup(arg_item->name);
		arg_item = arg_item->next;
	}
	result_arr[i] = NULL;
	return (result_arr);
}

int	check_type(t_arg_item *arg_item, int type)
{
	if (arg_item && arg_item->type == type)
		return (1);
	return (0);
}

int	check_for_redirs(t_arg_item *prev, t_arg_item *next, t_minishell *mini)
{
	if (prev && next)
	{
		if ((prev->type == REDIR || prev->type == APPEND) && next->type == PIPE)
		{
			mini->redir_flag = 1;
			return (1);
		}
	}
	return (0);
}

t_arg_item	*next_arg(t_arg_item *arg, int insidepipe)
{
	t_arg_item	*tmp;

	tmp = arg;
	if (insidepipe)
	{
		while (arg->type != PIPE && arg->next)
			arg = arg->next;
		if (arg)
			arg = arg->next;
	}
	if (arg)
		arg = arg->next;
	while (arg && arg->type != COMMAND)
		arg = arg->next;
	return (arg);
}
