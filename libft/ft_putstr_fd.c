#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (fd > 0 && s)
		write(fd, s, ft_strlen(s));
}
