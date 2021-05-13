#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*source;

	if (!dst && !src)
		return (NULL);
	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	if ((size_t)(dest - source) >= len)
		return (ft_memcpy(dest, source, len));
	if (dest >= source)
	{
		dest += len;
		source += len;
		while (len--)
		{
			*--dest = *--source;
		}
		return (dest);
	}
	return (dest);
}
