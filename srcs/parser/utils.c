#include "minishell.h"

char *ft_remove_chrnstr(const char *str, char symb)
{
	int		i;
	int		j;
	char	*result;

	result = (char *)malloc(ft_strlen(str) * sizeof(char) + 1);
	if (result)
	{
		i = 0;
		j = 0;
		while (str[i])
		{
			if (str[i] != symb)
				result[j++] = str[i];
			i++;
		}
		result[j] = '\0';
		return (result);
	}
	return (NULL);
}

int skip_spaces(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (--i);
}
