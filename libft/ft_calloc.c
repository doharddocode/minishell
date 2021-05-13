#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if (count == 0)
		count = 1;
	if (size == 0)
		size = 1;
	str = (char *)malloc(count * size);
	if (str)
	{
		ft_bzero(str, count * size);
		return (str);
	}
	else
		return (NULL);
}
