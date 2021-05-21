#include "minishell.h"

char *ft_remove_chrnstr(const char *str, char symb)
{
	int		i;
	int		j;
	int 	q_cnt;
	char	*result;

	q_cnt = 0;
	result = (char *)malloc(ft_strlen(str) * sizeof(char) + 1);
	if (result)
	{
		i = 0;
		j = 0;
		while (str[i])
		{
			if (str[i] != symb && q_cnt < 2)
				result[j++] = str[i];
			else
				(q_cnt)++;
			i++;
		}
		result[j] = '\0';
		return (result);
	}
	return (NULL);
}

int skip_spaces(char *str, int i)
{
	if (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
	}
	return (--i);
}
