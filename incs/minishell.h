#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line.h"
# include "libft.h"

# include <stdio.h>
# include <stdlib.h>

#define SUCCESS 1
#define ERROR (-1)

typedef struct s_enpv
{
	char *key;
	char *value;
	struct s_enpv *next;
} t_envp;

typedef struct s_minishell
{
	t_envp *envp;
	t_list *args;
	int exit;
} t_minishell;

int parser(t_minishell *mini, const char *str);

int builtins(t_minishell *mini);

int ft_echo(t_minishell *mini);

void ft_free_arr(char **arr);
void ft_free_str(char *str);
t_list *delete_root(t_list *args_root);

t_envp *ft_envp_new_node(char *var);
t_envp *ft_envp_last_node(t_envp *envp);
void ft_envp_addback_node(t_envp **envp, t_envp *new_node);
int ft_cpy_env(t_minishell *mini, char **envp);

#endif