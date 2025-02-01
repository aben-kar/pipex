# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Path to libft and the static library
LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

# Source files and object files
SRC = pipex.c
OBJ = $(SRC:.c=.o)

# Output executable
NAME = pipex

# Default target (build the program)
all: $(NAME)

# Build the program
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

# Compile the object files
%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJ)

# Clean everything (including libft.a if needed)
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

# Dependencies (in case you need specific build order)
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
