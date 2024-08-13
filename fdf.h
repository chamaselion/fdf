#ifndef FDF_H
#define FDF_H

#include "mlx.h"
#include "get_next_line/get_next_line.h"
#include <stdlib.h> // For malloc, free, and atoi
#include <ctype.h>  // For isspace
#include <string.h> // For strlen
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <math.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

    typedef struct
{
    int x;
    int y;
    int sx;
    int sy;
} t_ImageSize;

typedef struct
{
    int width, height;
    int **values;
} t_Map;

typedef struct s_DrawData {
    void *mlx;
    void *window;
    void *image;
    t_ImageSize imagePosition;
    t_ImageSize windowSize;
    t_ImageSize imageSize;
    float scaleX;
    float scaleY;
    float scale;
    int offsetX;
    int offsetY;
    int bpp;
    int line_bytes;
    int endian;
    char *original_data;
    void *scaled_image;
    int color;
} t_DrawData;

int find_max_z_value(t_Map *map);
int *string_to_int_array(char *str, int *outLength);
int count_integers_in_string(char *str);
void fill_map_lines(t_Map *map, char *line);
void init_window_size(t_DrawData *drawData, t_Map *map);
void init_image_size(t_DrawData *drawData, t_Map *map);
int init_color(int z, int min_z, int max_z);
int open_file(const char *filepath);
void *ft_realloc(void *ptr, size_t new_size);
void *scale_and_center_image(void *mlx, void *original_image, t_ImageSize Image, t_ImageSize Window);
void put_pixel_to_image(void *image, int x, int y, int color);
void draw_map(t_DrawData *drawData, t_Map *map);
void fdf_main();
int map_filling(t_Map *map);
int main();
void print_map(t_Map *map);


#endif