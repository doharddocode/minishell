#include "libft.h"

static	int	ft_isspace(char c)
{
	c = (unsigned char)c;
	if (c == '\t'
		|| c == '\n'
		|| c == '\v'
		|| c == '\f'
		|| c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

static	int	is_number(char c)
{
	c = (unsigned char)c;
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static void	set_mines(char c, int *mines)
{
	if (c == '-')
		*mines = -1;
	else
		*mines = 1;
}

int	ft_atoi(const char *str)
{
	unsigned long	result;
	unsigned long	border;
	size_t			i;
	int				mines;

	result = 0;
	border = (unsigned long)(2147483647 / 10);
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	set_mines(str[i], &mines);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (is_number(str[i]))
	{
		if ((result > border || (result == border && (str[i] - '0') > 7))
			&& mines == 1)
			return (-1);
		else if ((result > border || (result == border && (str[i] - '0') > 8))
			&& mines == -1)
			return (0);
		result = result * 10 + (str[i++] - '0');
	}
	return ((int)(result * mines));
}
