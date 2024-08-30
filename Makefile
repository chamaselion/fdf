NAME        := fdf
CC          := gcc
FLAGS       := -Wall -Wextra -Werror
SRCS        :=      fdf_draw_map.c \
                          fdf_draw_utis.c \
                          fdf_draw_utis_2.c \
                          fdf_error_utis.c \
                          fdf_file_utis.c \
                          fdf_ft_functions.c \
                          fdf_init.c \
                          fdf_init_2.c \
                          fdf_main.c \
                          fdf_map_filling.c \
                          fdf_map_utis.c \
                          str_to_intarr.c \
                         
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC}	${FLAGS}	-c 	$<	-o	${<:.c=.o}

RM          := rm -f

$(NAME): ${OBJS}
			@ $(MAKE) -C mlx all
			@ cp ./mlx/libmlx.a .
			@ $(MAKE) -C libft all
			$(CC) $(CFLAGS) -o $(NAME) -Imlx $(OBJS) -Lmlx -lmlx -L./libft -lft -lm -framework OpenGL -framework AppKit

all:        ${NAME}

clean:
			@ $(MAKE) -C mlx clean
			@ $(MAKE) -C libft clean
			@ ${RM} *.o */*.o */*/*.o
			@ rm -rf $(NAME).dSYM


fclean:     clean
			@ $(MAKE) -C libft fclean
			@ ${RM} ${NAME}
			@ rm -f libmlx.a
			@ $(MAKE) -C mlx fclean
			@ ${RM} libft/libft.a

re:         fclean all

.PHONY:     all clean fclean re


