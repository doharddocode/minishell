/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:31:09 by mrosette          #+#    #+#             */
/*   Updated: 2021/08/03 20:31:09 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	wl;

	i = 0;
	str = NULL;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		wl = 0;
	else
		wl = ft_min(ft_strlen(s) - start, len);
	str = malloc(wl + 1);
	if (str)
	{
		while (wl--)
			str[i++] = s[start++];
		str[i] = '\0';
	}
	return (str);
}
