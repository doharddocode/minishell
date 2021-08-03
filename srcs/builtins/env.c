/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:28:48 by mrosette          #+#    #+#             */
/*   Updated: 2021/08/03 20:28:48 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_minishell *mini)
{
	if (!is_env_exist(mini->envp, "PATH"))
	{
		item_not_found(mini, "env", "No such file or director\n");
		return (ERROR);
	}
	print_envp_list(mini->envp, NULL);
	return (SUCCESS);
}
