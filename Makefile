NAME	=	fdf
CC	=	cc
CFLAGS	=
MLXFLAGS	=	-lmlx -lXext -lX11 -lm
SRC_DIR	=	.
SRC	=	fdf_main.c fdf_init.c fdf_map_utis.c fdf_draw_utis.c fdf_error_utis.c fdf_ft_functions.c fdf_file_utis.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
OBJ_DIR	=	obj
OBJ	=	$(SRC:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC)	$(OBJ)	-o	$(NAME)	$(MLXFLAGS)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	$(CC)	$(CFLAGS)	-c	$<	-o	$@

clean:
	rm	-f	$(OBJ)

fclean:	clean
	rm	-f	$(NAME)

re:	fclean	all