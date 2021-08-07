#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	full_len;

	dest_len = ft_strlen(dst);
	if (size > dest_len)
		full_len = dest_len + ft_strlen(src);
	else
		full_len = size + ft_strlen(src);
	if (size > dest_len)
	{
		dst += dest_len;
		size -= dest_len;
		while (*src && size > 1)
		{
			*dst++ = *src++;
			size--;
		}
		*dst = '\0';
	}
	return (full_len);
}
