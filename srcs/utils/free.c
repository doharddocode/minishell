#include "minishell.h"

void	ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			ft_free_str(arr[i]);
			i++;
		}
		free(arr);
		arr = NULL;
	}
}

void	ft_free_str(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}
