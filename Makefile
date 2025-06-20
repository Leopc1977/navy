NAME = navy

SRC = 	$(wildcard src/utils/*.c) \
		$(wildcard src/lib/*.c) \
		src/main.c

INCLUDE = include

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -I$(INCLUDE)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)
	clear

fclean: clean
	rm -f $(NAME)
	clear

re: fclean all

run: re
	./$(NAME)

play: re
	./$(NAME) pos1

join: re
	./$(NAME) $(PID) pos2

.PHONY: all clean fclean re
