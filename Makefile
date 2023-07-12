NAME = minishell

#CFLAGS = -Wall -Werror -Wextra -fsanitize=address

BUILT_IN = ./built_ins/cd.c ./built_ins/echo.c ./built_ins/env.c ./built_ins/exit.c ./built_ins/export.c ./built_ins/pwd.c ./built_ins/unset.c

SRCS = $(BUILT_IN) minishell.c Utils.c execute_built_ins.c

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
