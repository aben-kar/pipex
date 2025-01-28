NAME = pipex

CC = cc

CFLAGS = -Werror -Wall -Wextra

RM = rm -rf

SRCS = 	pipex.c\
		libft/libft.a\


$(NAME) :
	@make all -C libft
	@gcc $(CFLAGS) $(SRCS) -o $(NAME)


all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	@make fclean -C libft

clean :
	$(RM) $(NAME)
	@make clean -C libft

re : fclean all