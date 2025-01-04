NAME	=	allocate.a

CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror
RM	=	rm -f

SRC	=	aborter.c allocator.c 

OBJ	=	$(SRC:.c=.o)


all:	$(NAME)

$(NAME):	$(OBJ)
			ar rcs $(NAME) $(OBJ)

clean:
			$(RM) $(OBJ)

fclean:	clean
			$(RM) $(NAME)

re:	fclean $(NAME)

.PHONY: all clean fclean re
