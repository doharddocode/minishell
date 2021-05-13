NAME 			= minishell

FLAGS			= -Wall -Werror -Wextra

LIBFT_DIR 		= libft/

GNL_DIR			= gnl/

INCS			= incs/

HEADERS			= $(INCS)minishell.h \
					$(INCS)libft.h \
					$(INCS)get_next_line.h

MAIN_DIR 		= srcs/

BUILINTS_DIR	= srcs/builtins/

GNL_FILES		= get_next_line.c \
					get_next_line_utils.c \

MAIN_FILES 		= minishell.c

BUILINS_FILES	= echo.c

SRCS 			= $(addprefix $(GNL_DIR), $(GNL_FILES)) \
					$(addprefix $(MAIN_DIR), $(MAIN_FILES)) \
					$(addprefix $(BUILINTS_DIR), $(BUILINS_FILES)) \

OBJS 			= $(SRCS:.c=.o)

all: $(NAME)

.c.o: $(HEADERS)
	gcc $(FLAGS) -I$(INCS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS) $(HEADERS)
	make -C $(LIBFT_DIR)
	gcc $(FLAGS) $(LIBFT_DIR)/libft.a $(OBJS) -o $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(LIBFT_DIR)libft.a
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re