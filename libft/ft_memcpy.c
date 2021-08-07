#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int				i;
	unsigned char	*dest;
	unsigned char	*source;

	i = 0;
	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (dest == NULL && source == NULL)
		return (dst);
	while (i < (int)n)
	{
		dest[i] = source[i];
		i++;
	}
	return (dst);
}
