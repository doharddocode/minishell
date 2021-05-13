#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;

	int res;
	char *line;

	line = NULL;
	ft_atoi("1234");
	while ((res = get_next_line(0, &line)))
	{
		printf("[%d]{%s}\n", res, line);
		free(line);
	}
	printf("[%d]{%s}\n", res, line);
	free(line);
	return (0);
}
