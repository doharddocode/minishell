/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivangluskov <ivangluskov@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 01:59:11 by ivangluskov       #+#    #+#             */
/*   Updated: 2020/12/13 01:59:12 by ivangluskov      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t		g_strlen(const char *str, int flag)
{
	size_t count;

	count = 0;
	if (flag)
		while (str[count] && str[count] != '\n')
			count++;
	else
		while (str[count])
			count++;
	return (count);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*start;
	char	*result;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	s1_len = (s1) ? g_strlen(s1, 1) : 0;
	s2_len = (s2) ? g_strlen(s2, 1) : 0;
	result = (char*)malloc(s1_len + s2_len + 1);
	if (!(start = result))
		return (NULL);
	while (*s1)
		*result++ = *s1++;
	while (s2 && *s2)
		*result++ = *s2++;
	*result = '\0';
	return (start);
}

char		*ft_strdup(const char *s1)
{
	char	*str;
	size_t	len;

	len = g_strlen(s1, 0);
	if (!(str = (char *)malloc(BUFFER_SIZE + 1)))
		return (NULL);
	str[len] = '\0';
	while (len--)
		str[len] = s1[len];
	return (str);
}

char		*ft_gnl_strchr(const char *str, int c)
{
	if (str)
	{
		while (*str)
		{
			if (*str == c)
				return ((char *)str);
			str++;
		}
		if (*str == c)
			return ((char *)str);
	}
	return (NULL);
}

char		*ft_gnl_strncpy(char *dst, const char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
