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
#include <limits.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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

typedef struct s_Camera {
    float x, y, z; // Position
    float pitch, yaw; // Orientation
} t_Camera;

typedef struct s_DrawData {
    void *mlx;
    void *window;
    void *image;
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

// Draw utilities
void put_pixel_to_image(void *image, int x, int y, int color);
void draw_line(void *image, int x0, int y0, int x1, int y1, int color, t_DrawData *drawData);
int close_window(t_DrawData *drawData);
int key_event_handler(int keycode, t_DrawData *drawData);

// Error utilities
void free_draw_data(t_DrawData *drawData);

// File utilities
int open_file(const char *filepath);
int count_integers_in_string(char *str);

// Custom functions
void *ft_realloc(void *ptr, size_t new_size);

// Initialization fucntions
void init_window_size(t_DrawData *drawData, t_Map *map);
void init_image_size(t_DrawData *drawData, t_Map *map);
int interpolate(int start, int end, float factor);
int init_color(int z, int min_z, int max_z);
void init_draw_data(t_DrawData *drawData);

// Map utilities
int find_max_z_value(t_Map *map);
int find_min_z_value(t_Map *map);
int *string_to_int_array(char *str, int *outLength);
void fill_map_lines(t_Map *map, char *line);
int map_filling(t_Map *map, char *file_name);
void print_map(t_Map *map);


#endif