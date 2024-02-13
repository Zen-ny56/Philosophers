NAME = philosophers

SRCS = main.c parsing_utils.c init.c process.c time.c actions.c moniter.c  compare.c free_mem.c\

OBJ = $(SRCS:.c=.o)

CC = gcc

CFLAGS =  -Wall -Werror -Werror -Iheader -pthread

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