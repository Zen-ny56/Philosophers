NAME = philosophers

SRCS = main.c parsing_utils.c init.c thread_process.c utils.c time_utils.c

OBJ = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra -Iheader

HEADER =  philosophers.h

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all philosophers re