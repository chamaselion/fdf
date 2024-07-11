#include "fdf.h"

void init_window_size(t_ImageSize *Window, t_Map *map)
{
    Window->x = 1000;
    Window->y = 1000;
}

void init_image_size(t_ImageSize *Image, t_Map *map)
{
    Image->x = 800;
    Image->y = 800;
}

int init_color()
{
    int clr;

    clr = 0x00FF0000;

    return clr;
}