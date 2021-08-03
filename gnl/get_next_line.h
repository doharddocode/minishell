/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosette <mrosette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:27:04 by mrosette          #+#    #+#             */
/*   Updated: 2021/08/03 20:27:04 by mrosette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFF_SIZE
#  define BUFF_SIZE 32
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
int					ft_gnl_free_str(char *str, int return_val);
char				*ft_gnl_strdup(const char *s1);
char				*ft_gnl_strchr(const char *str, int c);
char				*ft_gnl_strncpy(char *dst, const char *src);
char				*ft_gnl_strjoin(char const *s1, char const *s2);
char				*process_remainer(char **remainer, char **line);

size_t				ft_gnl_strlen(const char *str, int flag);
size_t				check_len(const char *str);

void				fill_line(char *e_l_p, char **remainer, char **line);

#endif
