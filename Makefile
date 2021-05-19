NAME 			= minishell

FLAGS			= -fsanitize=address -g #-Wall -Werror -Wextra

LIBFT_DIR 		= libft/

GNL_DIR			= gnl/

INCS			= incs/

HEADERS			= $(INCS)minishell.h \
					$(INCS)libft.h \
					$(INCS)get_next_line.h

MAIN_DIR 		= srcs/

PARSER_DIR		= $(MAIN_DIR)parser/

BUILINTS_DIR	= $(MAIN_DIR)builtins/

UTILS_DIR		= $(MAIN_DIR)utils/

GNL_FILES		= get_next_line.c \
					get_next_line_utils.c \

MAIN_FILES 		= minishell.c

PARSER_FILES	= parser.c env_vars.c quotes.c utils.c

BUILINS_FILES	= builtins.c echo.c utils.c

UTILS_FILES		= free.c envp_list_utils.c arg_list.c common.c

SRCS 			= $(addprefix $(GNL_DIR), $(GNL_FILES)) \
					$(addprefix $(MAIN_DIR), $(MAIN_FILES)) \
					$(addprefix $(BUILINTS_DIR), $(BUILINS_FILES)) \
					$(addprefix $(PARSER_DIR), $(PARSER_FILES)) \
					$(addprefix $(UTILS_DIR), $(UTILS_FILES)) \

OBJS 			= $(SRCS:.c=.o)

all: $(NAME)

.c.o: $(HEADERS)
	gcc $(FLAGS) -I$(INCS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS) $(HEADERS)
	make -C $(LIBFT_DIR)
	make bonus -C $(LIBFT_DIR)
	gcc $(FLAGS) $(LIBFT_DIR)libft.a $(OBJS) -o $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(LIBFT_DIR)libft.a
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re