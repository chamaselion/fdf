NAME	=	fdf
CC	=	cc
CFLAGS	=
MLXFLAGS	=	-lmlx -lXext -lX11 -lm
SRC	=	fdf_main.c fdf_init.c fdf_map_utis.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
OBJ_DIR	=	obj
OBJ	=	$(SRC:.%.c=$(OBJ_DIR)/%.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC)	$(OBJ)	-o	$(NAME)	$(MLXFLAGS)

$(OBJ_DIR)/%.o:	%.c
	$(CC)	$(CFLAGS)	-c	$<	-o	$@

clean:
	rm	-f	$(OBJ)

fclean:	clean
	rm	-f	$(NAME)

re:	fclean	all