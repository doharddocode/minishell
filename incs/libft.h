/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oryndoon <oryndoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:50:53 by oryndoon          #+#    #+#             */
/*   Updated: 2020/11/18 14:26:33 by oryndoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

void			ft_bzero(void *s, size_t n);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			*ft_calloc(size_t count, size_t size);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);

size_t			ft_strlen(const char *str);
size_t			ft_strlcpy(char *d, const char *sr, size_t s);
size_t			ft_strlcat(char *dst, const char *src, size_t size);

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isprint(int c);
int				ft_isascii(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_lstsize(t_list *lst);
int				ft_atoi(const char *str);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_strncmp(const char *str1, const char *str2, size_t n);

char			*ft_itoa(int n);
char			*ft_strdup(const char *s1);
char			**ft_split(char const *s, char c);
char			*ft_strchr(const char *str, int c);
char			*ft_strrchr(const char *str, int c);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strnstr(const char *h, const char *n, size_t len);

t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstnew(void *content);
t_list			*ft_lstmap(t_list *l, void *(*f)(void *), void (*d)(void *));

#endif
