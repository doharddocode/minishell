#include "get_next_line.h"

t_gnl	*gnl_ft_lstnew(int fd)
{
	t_gnl	*res;

	res = malloc(sizeof(t_gnl));
	if (res)
	{
		res->fd = fd;
		res->remainer = NULL;
		res->next = NULL;
		return (res);
	}
	return (NULL);
}

char	*process_remainer(char **remainer, char **line)
{
	char	*e_l_p;

	e_l_p = NULL;
	if (*remainer)
		fill_line(e_l_p, remainer, line);
	else
	{
		*line = (char *)malloc(sizeof(char) * 1);
		if (!(*line))
			return (NULL);
		*line[0] = '\0';
	}
	return (e_l_p);
}

t_gnl	*ft_free_lst(t_gnl *lst, t_gnl *root)
{
	t_gnl	*temp;

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

int	ft_get_line(int fd, int bytes_r, char **line, char **remain)
{
	char	*e_l_p;
	char	*old_ptr;
	char	buffer[BUFF_SIZE + 1];

	e_l_p = process_remainer(remain, line);
	bytes_r = 1;
	while (*line && !e_l_p && bytes_r > 0)
	{
		bytes_r = (int)read(fd, buffer, BUFF_SIZE);
		buffer[bytes_r] = '\0';
		e_l_p = ft_gnl_strchr(buffer, '\n');
		if (e_l_p)
		{
			*e_l_p = '\0';
			*remain = ft_gnl_strdup(++e_l_p);
			if (!(*remain))
				return (-1);
		}
		old_ptr = *line;
		*line = ft_gnl_strjoin(*line, buffer);
		ft_gnl_free_str(old_ptr, 1);
	}
	if (bytes_r == -1 || !*line)
		return (ft_gnl_free_str(*line, -1));
	return (bytes_r || e_l_p);
}

int	get_next_line(int fd, char **line)
{
	static t_gnl	*first;
	t_gnl			*lst;
	int				res;
	int				bytes_r;

	bytes_r = 0;
	if ((fd < 0 || !line) != 0)
		return (-1);
	if (!first)
	{
		first = gnl_ft_lstnew(fd);
		if (!first)
			return (-1);
	}
	lst = first;
	while (lst->fd != fd)
	{
		if (!lst->next)
			lst->next = gnl_ft_lstnew(fd);
		lst = lst->next;
	}
	res = ft_get_line(lst->fd, bytes_r, line, &lst->remainer);
	if (res < 1)
		first = ft_free_lst(lst, first);
	return (res);
}
