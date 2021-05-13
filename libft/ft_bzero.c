#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	int				i;
	unsigned char	*str;

	i = 0;
	str = s;
	if (n != 0)
	{
		while (i < (int)n)
		{
			str[i] = 0;
			i++;
		}
	}
}
