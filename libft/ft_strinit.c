#include "libft.h"

char	*ft_strinit(size_t size, char *value)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * size + 1);
	if (!(str))
		return (NULL);
	str[size] = '\0';
	ft_strlcpy(str, value, size + 1);
	return (str);
}
