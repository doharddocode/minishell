#include "get_next_line.h"

t_gnl		*ft_lstnew(int fd)
{
	t_gnl *res;

	if ((res = malloc(sizeof(t_gnl))))
	{
		res->fd = fd;
		res->remainer = NULL;
		res->next = NULL;
		return (res);
	}
	return (NULL);
}

char		*process_remainer(char **remainer, char **line)
{
	char	*e_l_p;

	e_l_p = NULL;
	if (*remainer)
		if ((e_l_p = ft_gnl_strchr(*remainer, '\n')))
		{
			*e_l_p = '\0';
			*line = ft_strdup(*remainer);
			ft_gnl_strncpy(*remainer, ++e_l_p);
		}
		else
		{
			*line = ft_strdup(*remainer);
			free(*remainer);
			*remainer = NULL;
		}
	else
	{
		if (!(*line = ((char *)malloc(sizeof(char) * 1))))
			return (NULL);
		*line[0] = '\0';
	}
	return (e_l_p);
}

t_gnl		*ft_free_lst(t_gnl *lst, t_gnl *root)
{
	t_gnl *temp;

	temp = root;
	if (lst == root)
	{
		root = root->next;
		free(temp);
	}
	else
	{
		while (temp->next != lst)
			temp = temp->next;
		temp->next = lst->next;
		free(lst);
	}
	return (root);
}

int			ft_get_line(int fd, int bytes_r, char **line, char **remain)
{
	char	*e_l_p;
	char	*old_ptr;
	char	buffer[BUFFER_SIZE + 1];

	e_l_p = process_remainer(remain, line);
	while (*line && !e_l_p && (bytes_r = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_r] = '\0';
		if ((e_l_p = ft_gnl_strchr(buffer, '\n')))
		{
			*e_l_p = '\0';
			if (!(*remain = ft_strdup(++e_l_p)))
				return (-1);
		}
		old_ptr = *line;
		*line = ft_strjoin(*line, buffer);
		free(old_ptr);
	}
	if (bytes_r == -1 || !*line)
	{
		free(*line);
		*line = NULL;
		return (-1);
	}
	return (bytes_r || e_l_p);
}

int			get_next_line(int fd, char **line)
{
	static t_gnl	*first;
	t_gnl			*lst;
	int				res;
	int				bytes_r;

	bytes_r = 0;
	if (fd < 0 || !line || !BUFFER_SIZE)
		return (-1);
	if (!first)
		if (!(first = ft_lstnew(fd)))
			return (-1);
	lst = first;
	while (lst->fd != fd)
	{
		if (!lst->next)
			lst->next = ft_lstnew(fd);
		lst = lst->next;
	}
	if ((res = ft_get_line(lst->fd, bytes_r, line, &lst->remainer)) < 1)
		first = ft_free_lst(lst, first);
	return (res);
}