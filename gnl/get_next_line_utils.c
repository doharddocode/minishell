/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:26:50 by mrosette          #+#    #+#             */
/*   Updated: 2021/08/03 20:26:50 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_gnl_strjoin(char const *s1, char const *s2)
{
	char	*start;
	char	*result;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	s1_len = check_len(s1);
	s2_len = check_len(s2);
	result = (char *)malloc(s1_len + s2_len + 1);
	start = result;
	if (!start)
		return (NULL);
	while (*s1)
		*result++ = *s1++;
	while (s2 && *s2)
		*result++ = *s2++;
	*result = '\0';
	return (start);
}

char	*ft_gnl_strdup(const char *s1)
{
	char	*str;
	size_t	len;

	len = ft_gnl_strlen(s1, 0);
	str = (char *)malloc(BUFF_SIZE + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
		str[len] = s1[len];
	return (str);
}

char	*ft_gnl_strchr(const char *str, int c)
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

char	*ft_gnl_strncpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
