NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS_LIBCF = ft_isalpha.c ft_isdigit.c ft_isalnum.c
SRC = $(SRCS_LIBCF)
OBJS = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
