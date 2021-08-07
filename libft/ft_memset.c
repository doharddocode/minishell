#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	int				i;
	unsigned char	*str;

	i = 0;
	str = b;
	while (i < (int)len)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
