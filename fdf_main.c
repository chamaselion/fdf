#include "fdf.h"

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
float z_scale = 7.5 / (max_z - min_z); // Calculate the z scale
if ((max_z - min_z) <= 1000)
    z_scale = 5.0 / (max_z - min_z);
if ((max_z - min_z) <= 100)
    z_scale = 2.5 / (max_z - min_z);
if ((max_z - min_z) <= 10)
    z_scale = 0.5 / (max_z - min_z);

// Calculate the dynamic scale based on image size and map dimensions
drawData->scale = fmin(drawData->imageSize.x, drawData->imageSize.y) / (map->height + map->width) * 1;

    int map_center_x = (map->width - 1 - (map->height - 1)) * cos(M_PI / 4) * drawData->scale / 2;
    int map_center_y = ((map->width - 1) + (map->height - 1)) * sin(M_PI / 6) * drawData->scale / 2;

    // Calculate offsets to center the map within the image
    int offsetX = (drawData->imageSize.x / 1.85) - map_center_x;
    int offsetY = (drawData->imageSize.y / 1.3) - map_center_y;


for (int y = 0; y < map->height; y++)
{
    for (int x = 0; x < map->width; x++)
    {
        int z = map->values[y][x];
        int color = init_color(z, min_z, max_z);

        // Apply the z scale
        float scaled_z = (z - min_z) * z_scale;

        // Isometric projection using rotation matrix
        float x_iso = (x - map->width / 2) * drawData->scale;
        float y_iso = (y - map->height / 2) * drawData->scale;
        int x2D = (x_iso - y_iso) * cos(M_PI / 4);
        int y2D = (x_iso + y_iso) * sin(M_PI / 6) - scaled_z * drawData->scale;

        // Center the map
        x2D += offsetX;
        y2D += offsetY;

        if (x < map->width - 1)
        {
            int next_z = map->values[y][x + 1];
            float scaled_next_z = (next_z - min_z) * z_scale;
            float next_x_iso = ((x + 1) - map->width / 2) * drawData->scale;
            float next_y_iso = (y - map->height / 2) * drawData->scale;
            int next_x2D = (next_x_iso - next_y_iso) * cos(M_PI / 4) + offsetX;
            int next_y2D = (next_x_iso + next_y_iso) * sin(M_PI / 6) - scaled_next_z * drawData->scale + offsetY;
            draw_line(drawData->image, x2D, y2D, next_x2D, next_y2D, color, drawData);
        }
        if (y < map->height - 1)
        {
            int next_z = map->values[y + 1][x];
            float scaled_next_z = (next_z - min_z) * z_scale;
            float next_x_iso = (x - map->width / 2) * drawData->scale;
            float next_y_iso = ((y + 1) - map->height / 2) * drawData->scale;
            int next_x2D = (next_x_iso - next_y_iso) * cos(M_PI / 4) + offsetX;
            int next_y2D = (next_x_iso + next_y_iso) * sin(M_PI / 6) - scaled_next_z * drawData->scale + offsetY;
            draw_line(drawData->image, x2D, y2D, next_x2D, next_y2D, color, drawData);
        }
    }
}
}

int main(int argc, char **argv)
{
    t_DrawData drawData;
    t_Map map;

    map.values = NULL;
    map.width = 0;
    map.height = 0;

    if (argc == 1 || argc > 2)
    {
        printf("Actually it's: %s <filename.fdf>\n", argv[0]);
        return 1;
    }


    if (map_filling(&map, argv[1]) == 0)
    {
        init_draw_data(&drawData);
        drawData.mlx = mlx_init();
        if (!drawData.mlx)
            return 1;
        mlx_get_screen_size(drawData.mlx, &drawData.windowSize.x, &drawData.windowSize.y);
        init_window_size(&drawData, &map);
        init_image_size(&drawData, &map);

        drawData.window = mlx_new_window(drawData.mlx, drawData.windowSize.x, drawData.windowSize.y, "FdF");
        if (!drawData.window)
            return 1;
        draw_map(&drawData, &map);
        if (drawData.image != NULL)
            mlx_put_image_to_window(drawData.mlx, drawData.window, drawData.image, 0, 0);
        mlx_key_hook(drawData.window, key_event_handler, &drawData);
        mlx_hook(drawData.window, 17, 0, close_window, &drawData);
        mlx_loop(drawData.mlx);
    }
    else 
    {
        printf("Error reading the map. Please make sure to give the name of an existing \n.fdf file as an argument. Chceck the presence of the test_maps folder.\nIf not present, create it and place the map files in it.");
        return 1;
    }

    return 0;
}