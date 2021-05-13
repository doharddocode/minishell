#include "libft.h"

static int	count_digits(int n, int minus)
{
	int	res;

	res = 1;
	n /= 10;
	while (n)
	{
		n /= 10;
		res++;
	}
	return (res + minus);
}

static void	set_params(long *n, int *minus)
{
	if (*n < 0)
	{
		*minus = 1;
		*n *= -1;
	}
	else
		*minus = 0;
}

char	*ft_itoa(int n1)
{
	char	*buff;
	int		i;
	int		minus;
	long	n;

	n = (long)n1;
	set_params(&n, &minus);
	i = count_digits((int)n, minus);
	buff = (char *)malloc(sizeof(char) * i + 1);
	if (buff)
	{
		buff[i--] = '\0';
		buff[minus] = '0';
		if (minus)
			buff[0] = '-';
		while (n > 0)
		{
			buff[i--] = '0' + n % 10;
			n /= 10;
		}
		return (buff);
	}
	return (NULL);
}
