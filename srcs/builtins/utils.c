/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:28:56 by mrosette          #+#    #+#             */
/*   Updated: 2021/08/03 20:28:57 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *arg, char *builtin_name)
{
	int		i;
	char	**builtins;

	to_lower_case(arg);
	if (!arg || ft_strlen(arg) < 0)
		return (ERROR);
	if (builtin_name)
		return (is_equal_strs(arg, builtin_name));
	else
	{
		builtins = ft_split(BUILTIN_FUNC, ' ');
		if (!builtins)
			return (ERROR);
		i = 0;
		while (builtins[i])
		{
			if (is_equal_strs(arg, builtins[i++]))
			{
				ft_free_arr(builtins);
				return (1);
			}
		}
	}
	ft_free_arr(builtins);
	return (SUCCESS);
}
