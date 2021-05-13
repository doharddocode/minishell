/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivangluskov <ivangluskov@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 01:59:06 by ivangluskov       #+#    #+#             */
/*   Updated: 2020/12/13 01:59:07 by ivangluskov      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct		s_gnl
{
	int				fd;
	char			*remainer;
	struct s_gnl	*next;
}					t_gnl;

t_gnl				*ft_lstnew(int fd);
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
