NAME = pipex
LIB = ./inc/pipex.h
LIBFT_DIR = ./libft_gnl
LIBFT = ./libft_gnl/libft.a
C_SOURCES = ./src/pipex.c ./src/pipex_utils.c ./src/error.c ./src/commands.c
B_SOURCES = ./src/bonus/pipex_bonus.c ./src/bonus/pipex_utils_bonus.c ./src/bonus/commands_bonus.c \
			./src/bonus/error_bonus.c ./src/bonus/process_utils_bonus.c
CC = @gcc
CFLAGS = -Wall -Wextra -Werror -g

all:	$(NAME)
$(NAME):	$(C_SOURCES)
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
			@$(CC) $(CFLAGS) $(^) -o $(@) $(LIBFT) -fsanitize=address

bonus:	$(B_SOURCES)
		@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
		@$(CC) $(CFLAGS) $(^) -o $(NAME) $(LIBFT) 
#-fsanitize=address

clean:	
		@rm -f *.o
		@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean:	clean
		@rm -f $(NAME)
		@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re:	fclean all

reb: fclean bonus

valgrind: 
		valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./pipex res/infile cat sort rev res/outfile

.PHONY: all bonus clean fclean re reb