NAME = libft.a
PRINTF_NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Source files from the current folder
SRCS = ft_isalpha.c ft_memcmp.c ft_strdup.c ft_strnstr.c \
    ft_atoi.c ft_isascii.c ft_memcpy.c ft_strlcat.c ft_strrchr.c \
    ft_bzero.c ft_isdigit.c ft_memmove.c ft_strlcpy.c ft_tolower.c \
    ft_calloc.c ft_isprint.c ft_memset.c ft_strlen.c ft_toupper.c \
    ft_isalnum.c ft_memchr.c ft_strchr.c ft_strncmp.c ft_substr.c \
    ft_strjoin.c ft_itoa.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
    ft_split.c ft_striteri.c ft_strmapi.c ft_strtrim.c ft_putstr_fd.c \
    get_next_line/get_next_line.c

# Source files from the printf_42 folder
PRINTF_SRCS = printf_42/ft_printf.c printf_42/ft_printf_outerft.c \
    printf_42/ft_printf_outerft2.c printf_42/ft_putnbr_base.c \
    printf_42/ft_putnbr.c printf_42/ft_putstr.c printf_42/ft_putchar.c

# Create object files
OBJS = $(SRCS:.c=.o)
PRINTF_OBJS = $(PRINTF_SRCS:.c=.o)

all: $(NAME) $(PRINTF_NAME)

# Target to build the libftprintf.a library
$(PRINTF_NAME): $(PRINTF_OBJS)
	ar rcs $@ $(PRINTF_OBJS)

# Target to build the libft.a library
$(NAME): $(OBJS) $(PRINTF_NAME)
	ar rcs $@ $(OBJS) $(PRINTF_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C printf_42 clean

fclean: clean
	rm -f $(NAME)
	rm -f libftprintf.a
	$(MAKE) -C printf_42 fclean

re: fclean all

.PHONY: all clean fclean re