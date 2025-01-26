# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Target name
NAME = pipex

# Source files
SRCS = pipex.c ft_strlen.c ft_calloc.c ft_memcpy.c ft_strjoin.c ft_split.c ft_strstr.c

# Object files
OBJS = $(SRCS:.c=.o)

# Header files
HEADER = pipex.h

# Default rule
all: $(NAME)

# Build the executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compile source files into object files
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS)

# Clean all generated files
fclean: clean
	rm -f $(NAME)

# Rebuild the project
re: fclean all
