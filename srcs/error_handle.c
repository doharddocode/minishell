#include "minishell.h"

int exit_with_error(char *error_text)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(error_text, 2);
	return (ERROR);
}

int item_not_found(t_minishell *mini, char *command_name, char *err_text)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(err_text, 2);
	mini->ret = ERROR;
	return (ERROR);
}

int get_errror_msg(char *exec_path)
{
	int	fd;
	int	return_val;
	DIR *catalog;

	catalog = opendir(exec_path);
	fd = open(exec_path, O_WRONLY);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(exec_path, 2);
	if (ft_strchr(exec_path, '/') == NULL)
		ft_putendl_fd(": command not found", 2);
	else if (fd == -1 && catalog == NULL)
		ft_putendl_fd(": No such file or directory", 2);
	if (fd == -1 && catalog != NULL)
		ft_putendl_fd(": is a directory", 2);
	else if (fd != -1 && catalog == NULL)
		ft_putendl_fd(": Permission denied", 2);
	if (ft_strchr(exec_path, '/') == NULL || (fd == -1 && catalog == NULL))
		return_val = 127;
	else
		return_val = 126;
	if (catalog)
		closedir(catalog);
	ft_close(fd);
	return (return_val);
}