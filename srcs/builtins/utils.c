#include "minishell.h"

int is_builtin(char *arg, char *builtin_name)
{
	if (!ft_strncmp(arg, builtin_name, ft_strlen(builtin_name))
			&& ft_strlen(arg) == ft_strlen(builtin_name))
		return (1);
	return (0);
}
