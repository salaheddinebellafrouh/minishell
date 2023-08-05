NAME = minishell

CFLAGS = -Wall -Werror -Wextra  -g -I /Users/sbellafr/.brew/opt/readline/include/ #-fsanitize=leak

EXECUTION = ./execution/execute_built_ins.c ./execution/execve.c ./execution/redirection.c
PARSING = ./parsing/ft_free.c ./parsing/ft_expand.c ./parsing/ft_helpers.c  \
		./parsing/tokenizing_syntax.c ./parsing/add_to_list.c ./parsing/quotes_management.c \
		./parsing/syntax_errors.c ./parsing/add_elements.c ./parsing/ft_free_extend.c \
		./parsing/remove_quotes.c ./parsing/ft_expander.c ./parsing/ft_expander_2.c \
		./parsing/count_dollar_expand.c ./parsing/free_syntax_errors.c ./parsing/ft_count.c \
		ft_itoa.c 
BUILT_IN = ./built_ins/cd.c ./built_ins/echo.c ./built_ins/env.c ./built_ins/exit.c \
		./built_ins/export.c ./built_ins/pwd.c ./built_ins/unset.c ./built_ins/builts_utils.c \
		./built_ins/builts_utils2.c

SRCS = $(BUILT_IN) $(PARSING) $(EXECUTION) minishell.c Utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -lreadline $(CFLAGS)  -L /Users/sbellafr/.brew/opt/readline/lib/  $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
