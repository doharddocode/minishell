#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line.h"
# include "libft.h"

# include <stdio.h>
# include <stdlib.h>

#define SUCCESS 1
#define ERROR (-1)

typedef struct s_minishell
{
	char **envp;
	t_list *args;
	int exit;
} t_minishell;

int parser(t_minishell *mini, const char *str);

int builtins(t_minishell *mini);

int ft_echo(t_minishell *mini);

void ft_free_arr(char **arr);
void ft_free_str(char *str);

#endif