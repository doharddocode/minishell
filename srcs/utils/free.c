/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:27:52 by mrosette          #+#    #+#             */
/*   Updated: 2021/08/03 20:27:53 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			ft_free_str(arr[i]);
			i++;
		}
		free(arr);
		arr = NULL;
	}
}

void	ft_free_str(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}
