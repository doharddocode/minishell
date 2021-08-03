/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:29:15 by mrosette          #+#    #+#             */
/*   Updated: 2021/08/03 20:29:15 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if (count == 0)
		count = 1;
	if (size == 0)
		size = 1;
	str = (char *)malloc(count * size);
	if (str)
	{
		ft_bzero(str, count * size);
		return (str);
	}
	else
		return (NULL);
}
