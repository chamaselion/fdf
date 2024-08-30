NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_printf.c ft_printf_outerft.c ft_printf_outerft2.c ft_putnbr_base.c ft_putnbr.c ft_putstr.c ft_putchar.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f ft_printf
	rm -f libftprintf.a

re: fclean all

.PHONY: all clean fclean re
