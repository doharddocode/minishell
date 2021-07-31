NAME 			= minishell
FLAGS			= -g -lreadline -L/usr/local/Cellar/readline/8.1/lib/ -I/usr/local/Cellar/readline/8.1/include#-Wall -Werror -Wextra

LIBFT_DIR 		= libft/

GNL_DIR			= gnl/

INCS			= incs/

HEADERS			= $(INCS)minishell.h \
					$(INCS)libft.h \
					$(INCS)get_next_line.h

MAIN_DIR 		= srcs/

PARSER_DIR		= $(MAIN_DIR)parser/

EXECUTE_DIR		= $(MAIN_DIR)execute/

BUILINTS_DIR	= $(MAIN_DIR)builtins/

UTILS_DIR		= $(MAIN_DIR)utils/

PIPE_DIR		= $(MAIN_DIR)redirs/

GNL_FILES		= get_next_line.c \
					get_next_line_utils.c gnl_util2.c\

MAIN_FILES 		= minishell.c signal.c error_handle.c

PARSER_FILES	= parser.c arg.c env_var.c quote.c escape.c utils.c

EXECUTE_FILES	= exec.c

BUILINS_FILES	= builtins.c echo.c cd.c pwd.c export.c unset.c env.c exit.c utils.c

UTILS_FILES		= free.c envp_list.c arg_list.c common.c tools.c history.c arg_item.c \
					free_src.c validate_line.c arg_utils.c arg_utils2.c

PIPE_FILES		= pipes.c fd.c heredoc.c

SRCS 			= $(addprefix $(GNL_DIR), $(GNL_FILES)) \
					$(addprefix $(MAIN_DIR), $(MAIN_FILES)) \
					$(addprefix $(EXECUTE_DIR), $(EXECUTE_FILES)) \
					$(addprefix $(BUILINTS_DIR), $(BUILINS_FILES)) \
					$(addprefix $(PARSER_DIR), $(PARSER_FILES)) \
					$(addprefix $(UTILS_DIR), $(UTILS_FILES)) \
					$(addprefix $(PIPE_DIR), $(PIPE_FILES)) \

OBJS 			= $(SRCS:.c=.o)

all: $(NAME)

.c.o: $(HEADERS)
	@printf "\033[mMinishell: %-33.33s\r" $@
	@gcc -I$(INCS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS) $(HEADERS)
	@echo ""
	@make -C $(LIBFT_DIR)
	@make bonus -C $(LIBFT_DIR)
	@gcc $(FLAGS) $(LIBFT_DIR)libft.a $(OBJS) -o $(NAME)
	@echo "\033[0mMinishel is ready!"

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(LIBFT_DIR)libft.a
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
