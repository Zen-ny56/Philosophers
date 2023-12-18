NAME = philosophers

SRCS = main.c parsing_utils.c init.c new.c time.c eat.c

OBJ = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra -Iheader -lpthread

all: $(NAME)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re