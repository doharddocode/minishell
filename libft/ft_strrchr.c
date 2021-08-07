#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	const char	*rst;

	rst = NULL;
	while (*str)
	{
		if (*str == c)
			rst = str;
		str++;
	}
	if (*str == c)
		return ((char *)str);
	return ((char *)rst);
}
