/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:27:21 by mrosette          #+#    #+#             */
/*   Updated: 2021/08/03 20:27:22 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*to_lower_case(char *str)
{
	char	*s;

	s = str;
	while (*str != '\0')
	{
		if (*str >= 'A' && *str <= 'Z')
			*str = *str + 32;
		++str;
	}
	return (s);
}

int	is_equal_strs(char *str1, char *str2)
{
	if (!ft_strncmp(str1, str2, ft_strlen(str2))
		&& ft_strlen(str1) == ft_strlen(str2))
		return (1);
	return (0);
}

void	ft_stricpy(char **dest, char *src, int *pos)
{
	int	i;

	i = 0;
	if (!src)
		return ;
	while (src[i] != '\0')
	{
		(*dest)[*pos] = src[i];
		i++;
		(*pos)++;
	}
}

char	*t_list_to_string(t_list *list)
{
	char	*result;
	char	*temp_str;
	t_list	*temp_node;

	temp_node = list;
	result = ft_strnew(1);
	if (!result || !list)
	{
		ft_free_str(result);
		return (NULL);
	}
	while (temp_node)
	{
		temp_str = result;
		if (!temp_node->content)
		{
			ft_free_str(result);
			return (NULL);
		}
		result = ft_strjoin(result, temp_node->content);
		ft_free_str(temp_str);
		temp_node = temp_node->next;
	}
	return (result);
}

int	ret_val(int return_val)
{
	if (return_val == 32256 || return_val == 32512)
		return_val /= 256;
	else
		return_val = return_val != 0;
	return (return_val);
}
