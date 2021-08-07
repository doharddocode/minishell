#include "libft.h"

size_t	ft_strlcpy(char *d, const char *sr, size_t s)
{
	int		i;
	size_t	len;

	if (!sr)
		return (0);
	i = 0;
	len = ft_strlen(sr);
	if (s == 0)
		return (len);
	while (sr[i] != '\0' && i < (int)s - 1)
	{
		d[i] = sr[i];
		i++;
	}
	d[i] = '\0';
	return (len);
}
