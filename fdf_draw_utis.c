#include "fdf.h"

void put_pixel_to_image(void *image, int x, int y, int color)
{
    char *buffer;
    int pixel_bits, line_bytes, endian;
    buffer = mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);
    int pos = (y * line_bytes) + (x * (pixel_bits / 8));
    *(int *)(buffer + pos) = color;
}

void draw_line(void *image, int x0, int y0, int x1, int y1, int color, t_DrawData *drawData)
{
    int image_width = drawData->windowSize.x;
    int image_height = drawData->windowSize.y;
    if (x0 < 0 || x0 >= image_width || y0 < 0 || y0 >= image_height ||
        x1 < 0 || x1 >= image_width || y1 < 0 || y1 >= image_height)
    {
        printf("Coordinates out of bounds: (%d, %d) to (%d, %d)\n", x0, y0, x1, y1);
        return;
    }

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx, sy;

    if (x0 < x1)
        sx = 1;
    else
        sx = -1;
    if (y0 < y1)
        sy = 1;
    else
        sy = -1;
    int err;
    if (dx > dy)
    {
        err = dx;
    }
    else
    {
        err = -dy;
    }
    err /= 2;
    int e2;

    while (1)
    {
        put_pixel_to_image(image, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            y0 += sy;
        }
    }
}

int close_window(t_DrawData *drawData)
{
    if (drawData->window != NULL)
    {
        mlx_destroy_window(drawData->mlx, drawData->window);
        drawData->window = NULL;
    }
    free_draw_data(drawData);
    exit(0);
    return 0;
}

int key_event_handler(int keycode, t_DrawData *drawData)
{
    if (keycode == 65307) // Escape key
    {
        if (drawData->window != NULL)
        {
            mlx_destroy_window(drawData->mlx, drawData->window);
            drawData->window = NULL;
        }
        free_draw_data(drawData);
        exit(0);
    }
    // Handle other keys here
    return 0;
}