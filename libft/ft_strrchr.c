/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:31:12 by mrosette          #+#    #+#             */
/*   Updated: 2021/08/03 20:31:12 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	const char	*rst;

	rst = NULL;
	while (*str)
	{
		if (*str == c)
			rst = str;
		str++;
	}
	if (*str == c)
		return ((char *)str);
	return ((char *)rst);
}
