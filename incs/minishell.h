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

typedef struct s_arg
{
	char symb;
	struct s_arg *next;
} t_arg;

typedef struct s_minishell
{
	t_envp *envp;
	t_list *args;
	int exit;
} t_minishell;

int parser(t_minishell *mini, char *str);
void parse_env_vars(t_minishell *mini, t_arg **arg_list, char *arg, int *i);
char *get_var_value(t_minishell *mini, char *var_name);
int is_valid_quotes(char *arg, char quote);
int parse_double_quotes(t_minishell *mini, t_arg **arg_list, char *arg, int *i);
int parse_single_quotes(t_minishell *mini, t_arg **arg_list, char *arg, int *i);
int skip_spaces(char *str, int i);

int builtins(t_minishell *mini);

int ft_echo(t_minishell *mini);

int is_builtin(char *arg, char *builtin_name);

void	ft_free_str(char *str);
char	*t_list_to_string(t_list *list);
char	*ft_remove_chrnstr(const char *str, char symb);

t_envp *ft_envp_new_node(char *var);
t_envp *ft_envp_last_node(t_envp *envp);
void ft_envp_addback_node(t_envp **envp, t_envp *new_node);
int ft_cpy_env(t_minishell *mini, char **envp);

t_arg *t_arg_new_node(char symb);
t_arg *t_arg_last_node(t_arg *arg);
void t_arg_addnode_back(t_arg **arg, t_arg *new_node);
char *t_arg_to_string(t_arg *arg);

#endif