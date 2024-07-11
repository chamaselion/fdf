#include "fdf.h"

int open_file(const char *filepath)
{
    int fd = open(filepath, O_RDONLY);
    return fd;
}

void *ft_realloc(void *ptr, size_t new_size)
{
    if (new_size == 0)
    {
        free(ptr);
        return NULL;
    }
    if (!ptr)
    {
        return malloc(new_size);
    }
    void *new_ptr = malloc(new_size);
    if (!new_ptr)
    {
        return NULL;
    }
    memcpy(new_ptr, ptr, new_size);
    free(ptr);
    return new_ptr;
}

void *scale_and_center_image(void *mlx, void *original_image, t_ImageSize Image, t_ImageSize Window)
{

    float scaleX = (float)Window.x / Image.x;
    float scaleY = (float)Window.y / Image.y;
    float scale = fmin(scaleX, scaleY);

    int offsetX = (Window.x - (Image.x * scale)) / 2;
    int offsetY = (Window.y - (Image.y * scale)) / 2;

    void *scaled_image = mlx_new_image(mlx, Window.x, Window.y);
    char *original_data = mlx_get_data_addr(original_image, &(int){0}, &(int){0}, &(int){0});

    int bpp, line_bytes, endian;
    mlx_get_data_addr(original_image, &bpp, &line_bytes, &endian);

    for (int y = 0; y < Image.y; y++)
    {
        for (int x = 0; x < Image.x; x++)
        {
            int pos = (y * line_bytes) + (x * (bpp / 8));
            int color = *(int *)(original_data + pos);
            int newX = (int)(x * scale) + offsetX;
            int newY = (int)(y * scale) + offsetY;
            if (newX >= 0 && newX < Window.x && newY >= 0 && newY < Window.y)
            {
                put_pixel_to_image(scaled_image, newX, newY, color);
            }
        }
    }

    mlx_destroy_image(mlx, original_image);
    return scaled_image;
}

void put_pixel_to_image(void *image, int x, int y, int color)
{
    char *buffer;
    int pixel_bits, line_bytes, endian;
    buffer = mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);
    int pos = (y * line_bytes) + (x * (pixel_bits / 8));
    *(int *)(buffer + pos) = color;
}

void *draw_map(void *mlx, void *win, t_Map *map)
{
    int color = init_color();
    if (!mlx || !win || !map || !map->values)
        return NULL;
    if (map->width <= 0 || map->height <= 0)
        return NULL;
    void *image = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!image) return NULL;
    int max_z = find_max_z_value(map);
    int scale_factor = WINDOW_HEIGHT / (max_z * 2);

    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            int z = map->values[y][x];
            int x2D = x * 10;
            int y2D = (y * 10) - (z * scale_factor / 2);
            x2D += WINDOW_WIDTH / 4;
            y2D += WINDOW_HEIGHT / 4;

            if (x2D >= 0 && x2D < WINDOW_WIDTH && y2D >= 0 && y2D < WINDOW_HEIGHT) {
                put_pixel_to_image(image, x2D, y2D, color);
            }
        }
    }

    return image;
}

void fdf_main()
{
    void *mlx;
    void *win;
    void *image;
    int color;
    t_ImageSize Window;
    t_ImageSize Image;
    t_ImageSize PixelDraw;
    t_Map map;

    map_filling(&map);
    color = init_color();
    init_window_size(&Window, &map);
    init_image_size(&Image, &map);

    mlx = mlx_init();
    if (!mlx)
        return;
    win = mlx_new_window(mlx, Window.x, Window.y, "MiniLibX Test");
    if (!win)
        return;
    void *scaled_image = scale_and_center_image(mlx, draw_map(mlx, win, &map), Image, Window);
    if (scaled_image != NULL)
    {
        mlx_put_image_to_window(mlx, win, scaled_image, 0, 0);
    }
    mlx_loop(mlx);
}

int main()
{
    fdf_main();
    return 0;
}