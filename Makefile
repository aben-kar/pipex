NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = pipex.c utils_pipex.c my_split.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
