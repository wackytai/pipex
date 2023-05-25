NAME = pipex
LIB = ./inc/pipex.h
LIBFT_DIR = ./libft_gnl
LIBFT = ./libft_gnl/libft.a
C_SOURCES = ./src/main.c ./src/pipex_utils.c ./src/error.c
CC = @gcc
CFLAGS = -Wall -Wextra -Werror -g

all:	$(NAME)
$(NAME):	$(C_SOURCES)
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
			@$(CC) $(CFLAGS) $(^) -o $(@) $(LIBFT) -fsanitize=address

bonus:	all

clean:	
		@rm -f *.o
		@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean:	clean
		@rm -f $(NAME)
		@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re:	fclean all

.PHONY: all bonus clean fclean re