# 1st makefile
NAME = libft.a

# Mandatory .c Files
C_SOURCES = ft_split.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_strncmp.c \
			ft_strlen.c ft_strjoin.c ft_substr.c ft_putnbr_fd.c ft_strdup.c \
			ft_calloc.c get_next_line_bonus.c get_next_line_utils_bonus.c

# Object Files
OBJ = $(C_SOURCES:.c=.o)

#Command to Create:
CREATE = @ar -rc

CC = @gcc

#Command to Remove:
REMOVE = @rm -f

# Flags for the Compiler
CFLAGS = -Wall -Wextra -Werror

#Compilation and Linking
all: $(NAME)

$(NAME):	$(OBJ)
			$(CREATE) $(NAME) $(OBJ)

bonus:	all

clean:	
		$(REMOVE) *.o

fclean:	clean
		$(REMOVE) $(NAME)

re:		clean all

.PHONY: all bonus clean fclean re