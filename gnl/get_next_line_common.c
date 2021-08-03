/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_common.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:26:43 by mrosette          #+#    #+#             */
/*   Updated: 2021/08/03 20:26:44 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	check_len(const char *str)
{
	size_t	len;

	if (str)
		len = ft_gnl_strlen(str, 1);
	else
		len = 0;
	return (len);
}

size_t	ft_gnl_strlen(const char *str, int flag)
{
	size_t	count;

	count = 0;
	if (flag)
		while (str[count] && str[count] != '\n')
			count++;
	else
		while (str[count])
			count++;
	return (count);
}

int	ft_gnl_free_str(char *str, int return_val)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
	return (return_val);
}

void	fill_line(char *e_l_p, char **remainer, char **line)
{
	e_l_p = ft_gnl_strchr(*remainer, '\n');
	if (e_l_p)
	{
		*e_l_p = '\0';
		*line = ft_gnl_strdup(*remainer);
		ft_gnl_strncpy(*remainer, ++e_l_p);
	}
	else
	{
		*line = ft_gnl_strdup(*remainer);
		ft_gnl_free_str(*remainer, 1);
	}
}
