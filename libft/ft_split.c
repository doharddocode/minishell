/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:30:27 by mrosette          #+#    #+#             */
/*   Updated: 2021/08/03 20:30:27 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	**ft_malloc_clean(char **result)
{
	unsigned int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

static size_t	count_words(char const *s, char c)
{
	size_t	res;

	res = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			res++;
			while (*s && *s != c)
				s++;
		}
	}
	return (res);
}

static char	*get_word(char *str, char c, int *skip)
{
	int	len;

	len = 0;
	*skip = 0;
	while (*str == c)
	{
		str++;
		(*skip)++;
	}
	while (str[len] && str[len] != c)
		len++;
	return (ft_substr(str, 0, len));
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	cnt;
	int		skip;
	char	**result;
	char	*str;

	if (!s)
		return (NULL);
	i = 0;
	str = (char *)s;
	cnt = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (result)
	{
		while (i < cnt)
		{
			result[i] = get_word(str, c, &skip);
			if (!(result[i]))
				return (ft_malloc_clean(result));
			str += ft_strlen(result[i++]) + skip;
		}
		result[i] = NULL;
		return (result);
	}
	return (NULL);
}
