NAME = lib_printf.a

C_SOURCES = ft_printf.c ft_putchar.c ft_putnbr_base.c \
			ft_putptr_base.c ft_putstr.c ../libft_gnl/ft_strlen.c

OBJ = $(C_SOURCES:.c=.o)

CREATE = @ar -rc

REMOVE = @rm -f

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):	$(OBJ)
			$(CREATE) $(NAME) $(OBJ)

clean:
		$(REMOVE) *.o

fclean:	clean
		$(REMOVE) $(NAME)

re: clean all

.PHONY: all bonus clean fclean re