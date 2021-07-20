#include "minishell.h"

#include <readline/readline.h>
#include <readline/history.h>


void	heredoc(t_minishell *mini, t_arg_item * arg)
{
	char *end;
	size_t str_len;
	size_t wrote;

	end = arg->name;
	printf("end %s\n", end);
	close(mini->fd_temp);
	mini->fd_temp = open("tmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	char *buf;
	int flag = 1;
	printf("epta2\n");
	while (flag)
	{
		buf = readline("> ");
		printf("gg %s\n", buf);
		str_len = ft_strlen(buf);
		wrote = 0;
		if (!ft_strcmp(buf, end))
			break;
		while (wrote < str_len)
		{
			size_t byte = write(mini->fd_temp, buf + wrote, str_len - wrote);
			if (byte >= 0)
				wrote += byte;
		}
		write(mini->fd_temp, "\n", 1);
	}
	close(mini->fd_temp);
	mini->fd_temp = open("tmp", O_RDONLY, S_IRWXU);
	dup2(mini->fd_temp, 0);
	unlink("tmp");
}
