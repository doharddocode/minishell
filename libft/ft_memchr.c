#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*f;
	unsigned char	ch;

	ch = (unsigned char)c;
	i = 0;
	f = (void *)s;
	while (i < n)
	{
		if (f[i] == ch)
			return (&f[i]);
		i++;
	}
	return (NULL);
}
