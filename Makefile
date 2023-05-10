NAME = pipex
LIB = ./inc/pipex.h
C_SOURCES = ./src/main.c
OBJ = $(C_SOURCES:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

all:	$(NAME)
$(NAME):	$(C_SOURCES)
			$(CC) $(CFLAGS) $(^) -o $(@) -fsanitize=address

bonus:

clean:	
		@rm -f *.o

fclean:	clean
		@rm -f $(NAME)

re:	fclean all

.PHONY: all bonus clean fclean re