#include "libft.h"

static void	ft_unicode(char c, int fd)
{
	char	bt[2];

	bt[1] = (c & 0x3F) | 0x80;
	bt[0] = ((c & 0xC0) >> 6) | 0xC0;
	write(fd, &bt, 2);
}

void	ft_putchar_fd(char c, int fd)
{
	if (fd > 0)
	{
		if (c < 0)
			ft_unicode(c, fd);
		else
			write(fd, &c, sizeof(c));
	}
}
