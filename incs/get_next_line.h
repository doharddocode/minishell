/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 01:59:30 by ivangluskov       #+#    #+#             */
/*   Updated: 2021/07/31 22:34:14 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct s_gnl
{
	int				fd;
	char			*remainer;
	struct s_gnl	*next;
}					t_gnl;

t_gnl				*gnl_ft_lstnew(int fd);
t_gnl				*ft_free_lst(t_gnl *lst, t_gnl *root);

int					get_next_line(int fd, char **line);
int					ft_get_line(int fd, int b_r, char **line, char **remain);

char				*ft_strdup(const char *s1);
char				*ft_gnl_strchr(const char *str, int c);
char				*ft_gnl_strncpy(char *dst, const char *src);
char				*ft_strjoin(char const *s1, char const *s2);
char				*process_remainer(char **remainer, char **line);

size_t				g_strlen(const char *str, int flag);

#endif
