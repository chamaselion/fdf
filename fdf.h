/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:33:47 by bszikora          #+#    #+#             */
/*   Updated: 2024/08/23 16:22:27 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "get_next_line/get_next_line.h"
# include "mlx.h"
# include <ctype.h> // For isspace
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h> // For malloc, free, and atoi
# include <string.h> // For strlen
# include <unistd.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct s_imagesize
{
	int				x;
	int				y;
	int				sx;
	int				sy;
}					t_imagesize;

typedef struct s_linedata
{
	int				x0;
	int				y0;
	int				x1;
	int				y1;
	int				color;
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	int				e2;
}					t_linedata;

typedef struct s_drawmapvars
{
	int				max_z;
	int				min_z;
	float			z_scale;
	int				map_center_x;
	int				map_center_y;
	int				offsetx;
	int				offsety;
	int				x2d;
	int				y2d;
	int				next_x2d;
	int				next_y2d;
	float			scaled_z;
	float			scaled_next_z;
	float			x_iso;
	float			y_iso;
	float			next_x_iso;
	float			next_y_iso;
}					t_drawmapvars;

typedef struct s_map
{
	int				width;
	int				height;
	int				**values;
}					t_map;

typedef struct s_drawdata
{
	void			*mlx;
	void			*window;
	void			*image;
	t_imagesize		windowsize;
	t_imagesize		imagesize;
	float			scalex;
	float			scaley;
	float			scale;
	int				offsetx;
	int				offsety;
	int				bpp;
	int				line_bytes;
	int				endian;
	char			*original_data;
	void			*scaled_image;
	int				color;
	t_map			*map;
}					t_drawdata;

typedef struct s_drawparams
{
	t_drawdata		*drawdata;
	t_map			*map;
	t_drawmapvars	*vars;
	t_linedata		*linedata;
}					t_drawparams;

// draw utilities
void				put_pixel_to_image(void *image, int x, int y, int color);
void				draw_line(t_linedata *linedata, t_drawdata *drawdata);
int					close_window(t_drawdata *drawdata);
int					key_event_handler(int keycode, t_drawdata *drawdata);

// draw map
void				draw_vertical_line(t_drawparams *params, int x, int y,
						int *z);
void				draw_horizontal_line(t_drawparams *params, int x, int y,
						int *z);
void				calculate_iso_coordinates(t_drawparams *params, int x,
						int y, int *z);
void				draw_map_looped(t_drawparams *params, int *z);
void				draw_map_loop(t_drawdata *drawdata, t_map *map,
						t_drawmapvars *vars);
// error utilities
void				free_draw_data(t_drawdata *drawdata);
void				free_map(t_map *map);

// file utilities
int					open_file(const char *filepath);
int					count_integers_in_string(char *str);

// custom functions
void				*ft_realloc(void *ptr, size_t original_size,
						size_t new_size);

// initialization fucntions
void				init_window_size(t_drawdata *drawdata);
void				init_image_size(t_drawdata *drawdata);
int					interpolate(int start, int end, float factor);
int					init_color(int z, int min_z, int max_z);
void				init_draw_data(t_drawdata *drawdata);
void				init_window_size_vars(t_imagesize *size);
void				initialize_z_scale(t_map *map, t_drawmapvars *vars);

// map utilities
int					find_max_z_value(t_map *map);
int					find_min_z_value(t_map *map);
int					*string_to_int_array(char *str, int *outlength);
void				fill_map_lines(t_map *map, char *line);
int					map_filling(t_map *map, char *file_name);
void				print_map(t_map *map);

#endif
