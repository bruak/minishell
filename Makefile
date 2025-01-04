NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = main.c env/env.c env/env2.c env/env3.c\
		utils/utils.c error_free/errors.c error_free/free.c error_free/free2.c\
		execute/builtin.c execute/builtin2.c execute/builtin3.c execute/builtin4.c\
		execute/builtin5.c execute/execute.c execute/execute2.c execute/execute3.c\
		execute/execute4.c execute/execute5.c execute/execve.c execute/ft_export.c execute/ft_export2.c \
		execute/heredoc.c lexer_parser/expander.c lexer_parser/expander2.c lexer_parser/expander3.c\
		lexer_parser/expander4.c lexer_parser/lexer.c lexer_parser/lexer2.c lexer_parser/lexer3.c lexer_parser/lexer4.c\
		lexer_parser/parser.c signal/signals.c execute/ft_export3.c\
		
OBJS = $(SRCS:.c=.o)
RM = rm -rf

all:	$(NAME)

$(NAME):	$(OBJS)
	@make -C libft
	@make -C memory
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a memory/allocate.a -lreadline -o minishell

clean:
	@make clean -C libft
	@make clean -C memory
	@$(RM) $(OBJS)

fclean:
	@make fclean -C libft
	@make fclean -C memory
	@$(RM) $(OBJS) $(NAME)
re:			fclean all
