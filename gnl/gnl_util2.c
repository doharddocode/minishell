#include "get_next_line.h"

size_t	g_strlen(const char *str, int flag)
{
	size_t	count;

	count = 0;
	if (flag)
		while (str[count] && str[count] != '\n')
			count++;
	else
		while (str[count])
			count++;
	return (count);
}
