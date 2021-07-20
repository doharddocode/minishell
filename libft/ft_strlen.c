#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	if (str == NULL)
		return (0);
	while (*str)
	{
		count++;
		str++;
	}
	return (count);
}
