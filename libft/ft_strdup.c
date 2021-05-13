#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s1);
	str = malloc(len + 1);
	if (str)
	{
		ft_strlcpy(str, s1, len + 1);
		return (str);
	}
	else
	{
		free(str);
		return (NULL);
	}
}
