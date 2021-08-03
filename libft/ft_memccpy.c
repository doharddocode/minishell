/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:29:55 by mrosette          #+#    #+#             */
/*   Updated: 2021/08/03 20:29:56 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*source;
	unsigned char	ci;

	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	ci = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		dest[i] = source[i];
		if (source[i] == ci)
			return ((void *)&dest[i + 1]);
		i++;
	}
	return (NULL);
}
