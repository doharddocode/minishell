#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while ((str1[i] != '\0' || str2[i] != '\0') && i < (int)n)
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (res);
}
