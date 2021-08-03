/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:30:36 by mrosette          #+#    #+#             */
/*   Updated: 2021/08/03 20:30:36 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *d, const char *sr, size_t s)
{
	int		i;
	size_t	len;

	if (!sr)
		return (0);
	i = 0;
	len = ft_strlen(sr);
	if (s == 0)
		return (len);
	while (sr[i] != '\0' && i < (int)s - 1)
	{
		d[i] = sr[i];
		i++;
	}
	d[i] = '\0';
	return (len);
}
