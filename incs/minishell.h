#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line.h"
# include "libft.h"

# include <stdio.h>
# include <stdlib.h>

#define SP_SYMBOLS "$\"\\`"
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
	int is_quote_parse;
	int exit;
	int ret;
} t_minishell;

int parser(t_minishell *mini, char *str);
int add_arg_to_args(t_minishell *mini, char *arg);
int get_arglen(char *str, int i);
void parse_env_vars(t_minishell *mini, t_arg **arg_list, char *arg, int *i);
char *get_var_value(t_minishell *mini, char *var_name);
int parse_quotes(t_minishell *mini, t_arg **arg_list, char *arg, int *i);
int skip_spaces(char *str, int i);
int parse_escape(t_minishell *mini, t_arg **arg_list, char *arg, int *i);
int is_shieild_symb(char symb);
void parse_to_arglist(t_minishell *mini, t_arg **arg_list, char *arg, int *i);
int is_normal_symbol(t_minishell *mini, char symb);
void next_symbol(char *str, int *counter);

int builtins(t_minishell *mini);
int is_builtin(char *arg, char *builtin_name);
int ft_echo(t_minishell *mini);
int	ft_cd(t_minishell *mini);
int ft_pwd(t_minishell *mini);
int ft_export(t_minishell *mini);
int ft_unset(t_minishell *mini);
int ft_exit(t_minishell *mini);

void	ft_free_str(char *str);
void 	ft_free_arr(char **arr);
char	*t_list_to_string(t_list *list);
void	ft_stricpy(char **dest, char *src, int *pos);

t_envp *ft_envp_new_node(char *key, char *value);
t_envp *ft_envp_last_node(t_envp *envp);
void ft_envp_addback_node(t_envp **envp, t_envp *new_node);
int ft_cpy_env(t_minishell *mini, char **envp);
int ft_envp_update_node(t_envp **envp, char *key, char *new_value);
t_envp	*ft_get_envp_node(t_envp *envp, char *key);
int is_env_exist(t_envp *envp, char *var_name);
void sort_envp_list(t_envp **envp);
void	print_envp_list(t_envp *envp, char *prefix);
t_envp *ft_delete_envp_node(t_envp *root, t_envp *node);

t_arg *t_arg_new_node(char symb);
t_arg *t_arg_last_node(t_arg *arg);
void t_arg_addnode_back(t_arg **arg, t_arg *new_node);
char *t_arg_to_string(t_arg *arg);

#endif