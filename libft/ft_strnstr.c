#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*h_str;

	i = 0;
	j = 0;
	h_str = (char *)haystack;
	if (ft_strlen(needle) == 0)
		return (h_str);
	if (ft_strlen(haystack) < ft_strlen(needle) || len < ft_strlen(needle))
		return (NULL);
	while (haystack[i] && i <= len - ft_strlen(needle))
	{
		j = 0;
		while (needle[j] && needle[j] == haystack[i + j])
			j++;
		if (j == ft_strlen(needle))
			return (&h_str[i]);
		i++;
	}
	return (NULL);
}
