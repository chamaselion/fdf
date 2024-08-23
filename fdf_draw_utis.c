#include "fdf.h"

void put_pixel_to_image(void *image, int x, int y, int color)
{
    char *buffer;
    int pixel_bits, line_bytes, endian;
    buffer = mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);
    int pos = (y * line_bytes) + (x * (pixel_bits / 8));
    *(int *)(buffer + pos) = color;
}

void draw_line(t_LineData *lineData, t_DrawData *drawData)
{
    int image_width;
    int image_height;
    
    image_width = drawData->windowSize.x;
    image_height = drawData->windowSize.y;


    if (lineData->x0 < 0 || lineData->x0 >= image_width || lineData->y0 < 0 || lineData->y0 >= image_height ||
        lineData->x1 < 0 || lineData->x1 >= image_width || lineData->y1 < 0 || lineData->y1 >= image_height)
    {
        printf("Coordinates out of bounds: (%d, %d) to (%d, %d)\n", lineData->x0, lineData->y0, lineData->x1, lineData->y1);
        return;
    }

    lineData->dx = abs(lineData->x1 - lineData->x0);
    lineData->dy = abs(lineData->y1 - lineData->y0);

    if (lineData->x0 < lineData->x1)
        lineData->sx = 1;
    else
        lineData->sx = -1;
    if (lineData->y0 < lineData->y1)
        lineData->sy = 1;
    else
        lineData->sy = -1;

    if (lineData->dx > lineData->dy)
        lineData->err = lineData->dx;
    else
        lineData->err = -lineData->dy;
    lineData->err /= 2;

    while (1)
    {
        put_pixel_to_image(drawData->image, lineData->x0, lineData->y0, lineData->color);
        if (lineData->x0 == lineData->x1 && lineData->y0 == lineData->y1)
            break;
        lineData->e2 = lineData->err;
        if (lineData->e2 > -lineData->dx)
        {
            lineData->err -= lineData->dy;
            lineData->x0 += lineData->sx;
        }
        if (lineData->e2 < lineData->dy)
        {
            lineData->err += lineData->dx;
            lineData->y0 += lineData->sy;
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
    free_map(drawData->map);
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
        free_map(drawData->map);
        exit(0);
    }
    // Handle other keys here
    return 0;
}