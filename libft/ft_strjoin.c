/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:30:40 by mrosette          #+#    #+#             */
/*   Updated: 2021/08/03 20:30:40 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	set_strlens(char const *s1, char const *s2,
							int *str1len, int *str2len)
{
	if (s1 == NULL)
		*str1len = 0;
	else
		*str1len = (int)ft_strlen(s1);
	if (s2 == NULL)
		*str2len = 0;
	else
		*str2len = (int)ft_strlen(s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	char	*start;
	int		str1len;
	int		str2len;

	if (!s1 && !s2)
		return (NULL);
	set_strlens(s1, s2, &str1len, &str2len);
	result = (char *)malloc(str1len + str2len + 1);
	start = result;
	if (result)
	{
		while (s1 && *s1)
			*result++ = *s1++;
		while (s2 && *s2)
			*result++ = *s2++;
		*result = '\0';
	}
	return (start);
}
