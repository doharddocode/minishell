/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:28:58 by mrosette          #+#    #+#             */
/*   Updated: 2021/08/03 20:28:58 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_minishell *mini)
{
	char	cwd[255];

	(void)mini;
	if (!getcwd(cwd, 255))
		return (1);
	ft_putendl_fd(getcwd(cwd, 255), 1);
	return (SUCCESS);
}
