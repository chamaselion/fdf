#include "fdf.h"

int open_file(const char *filepath)
{
    int fd = open(filepath, O_RDONLY);
    return fd;
}

void *ft_realloc(void *ptr, size_t new_size)
{
    void *new_ptr;

    if (new_size == 0)
    {
        free(ptr);
        return NULL;
    }

    new_ptr = malloc(new_size);
    if (new_ptr == NULL)
        return NULL;

    if (ptr != NULL)
    {
        memcpy(new_ptr, ptr, new_size);
        free(ptr);
    }

    return new_ptr;
}


int find_min_z_value(t_Map *map)
{
    int min_z = map->values[0][0];
    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            if (map->values[y][x] < min_z)
                min_z = map->values[y][x];
        }
    }
    return min_z;
}

void draw_line(void *image, int x0, int y0, int x1, int y1, int color)
{
    int image_width = 800;
    int image_height = 600;
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

    int err = (dx > dy ? dx : -dy) / 2;
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

void draw_map(t_DrawData *drawData, t_Map *map)
{
    if (!drawData->mlx || !drawData->window || map->values == NULL)
        return;
    if (map->width <= 0 || map->height <= 0)
        return;
    drawData->image = mlx_new_image(drawData->mlx, drawData->imageSize.x, drawData->imageSize.y);
    if (drawData->image == NULL)
        return;
    int max_z = find_max_z_value(map);
    int min_z = find_min_z_value(map);
    drawData->scale = drawData->imageSize.y / (max_z - min_z + map->height + map->width);
    printf("scale: %f\n", drawData->scale);

    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            int z = map->values[y][x];
            int color = init_color(z, min_z, max_z);

            // Isometric projection
            int x2D = (x - y) * drawData->scale;
            int y2D = (x + y) * drawData->scale / 2 - z * drawData->scale; // Adjust angle by changing the divisor

            // Center the map
            x2D += drawData->imageSize.x / 2; // Adjust the x position to center the map
            y2D += drawData->imageSize.y / 4; // Adjust the y position to center the map

            if (x < map->width - 1)
            {
                int next_x2D = ((x + 1) - y) * drawData->scale + drawData->imageSize.x / 2;
                int next_y2D = ((x + 1) + y) * drawData->scale / 2 - map->values[y][x + 1] * drawData->scale + drawData->imageSize.y / 4;
                draw_line(drawData->image, x2D, y2D, next_x2D, next_y2D, color);
            }
            if (y < map->height - 1)
            {
                int next_x2D = (x - (y + 1)) * drawData->scale + drawData->imageSize.x / 2;
                int next_y2D = (x + (y + 1)) * drawData->scale / 2 - map->values[y + 1][x] * drawData->scale + drawData->imageSize.y / 4;
                draw_line(drawData->image, x2D, y2D, next_x2D, next_y2D, color);
            }
        }
    }
}

void put_pixel_to_image(void *image, int x, int y, int color)
{
    char *buffer;
    int pixel_bits, line_bytes, endian;
    buffer = mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);
    int pos = (y * line_bytes) + (x * (pixel_bits / 8));
    *(int *)(buffer + pos) = color;
}

int main(void)
{
    t_DrawData drawData;
    t_Map map;

    map.values = NULL;
    map.width = 0;
    map.height = 0;

    printf("before mapfill\n");
    if (map_filling(&map) == 0)
    {
        printf("mapfill\n");
        drawData.mlx = mlx_init();
        if (!drawData.mlx)
            return 1;

        mlx_get_screen_size(drawData.mlx, &drawData.windowSize.x, &drawData.windowSize.y);
        init_window_size(&drawData, &map);
        init_image_size(&drawData, &map);

        drawData.window = mlx_new_window(drawData.mlx, drawData.windowSize.x, drawData.windowSize.y, "MiniLibX Test");
        if (!drawData.window)
            return 1;
        print_map(&map);
        printf("before image\n");
        draw_map(&drawData, &map);
        printf("after image\n");
        if (drawData.image != NULL)
        {
            mlx_put_image_to_window(drawData.mlx, drawData.window, drawData.image, drawData.imagePosition.x, drawData.imagePosition.y);
        }
        mlx_key_hook(drawData.window, drawData.mlx, &drawData);

        mlx_loop(drawData.mlx);
    }

    return 0;
}