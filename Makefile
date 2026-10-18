NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS_LIBCF = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
    		ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c \
        	ft_strncmp.c ft_strnstr.c ft_strdup.c ft_toupper.c ft_tolower.c \
        	ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c \
        	ft_memcmp.c ft_calloc.c ft_atoi.c

SRCS_PART2 = ft_substr.c ft_strjoin.c ft_strtrim.c
SRC = $(SRCS_LIBCF) $(SRCS_PART2)
OBJS = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
so:
	gcc -nostartfiles -shared -o libft.so $(OBJS) -lbsd

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
