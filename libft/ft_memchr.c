/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:29:48 by mrosette          #+#    #+#             */
/*   Updated: 2021/08/03 20:29:48 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*f;
	unsigned char	ch;

	ch = (unsigned char)c;
	i = 0;
	f = (void *)s;
	while (i < n)
	{
		if (f[i] == ch)
			return (&f[i]);
		i++;
	}
	return (NULL);
}
