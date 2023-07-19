NAME = minishell

CFLAGS = -Wall -Werror -Wextra #-fsanitize=address -g

BUILT_IN = ./built_ins/cd.c ./built_ins/echo.c ./built_ins/env.c ./built_ins/exit.c ./built_ins/export.c ./built_ins/pwd.c ./built_ins/unset.c
PARSING = ./parsing/ft_free.c ./parsing/ft_expand.c ./parsing/ft_helpers.c
SRCS = $(BUILT_IN) $(PARSING) minishell.c Utils.c execute_built_ins.c execve.c 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -lreadline $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
