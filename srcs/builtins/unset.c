/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:28:59 by mrosette          #+#    #+#             */
/*   Updated: 2021/08/03 20:28:59 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_env(t_minishell *mini, char *var_name)
{
	t_envp	*node;

	if (is_env_exist(mini->envp, var_name))
	{
		node = ft_get_envp_node(mini->envp, var_name);
		if (node)
			ft_delete_envp_node(&mini->envp, node);
	}
}

int	ft_unset(t_minishell *mini)
{
	t_arg_item	*arg_item_tmp;

	arg_item_tmp = mini->arg_item->next;
	if (arg_item_tmp)
	{
		delete_env(mini, arg_item_tmp->name);
	}
	return (SUCCESS);
}
