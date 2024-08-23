#include "fdf.h"

void draw_map(t_DrawData *drawData, t_Map *map)
{
    t_DrawMapVars vars;
    t_LineData lineData;

    if (!drawData->mlx || !drawData->window || map->values == NULL)
        return;
    if (map->width <= 0 || map->height <= 0)
        return;
    drawData->image = mlx_new_image(drawData->mlx, drawData->imageSize.x, drawData->imageSize.y);
    if (drawData->image == NULL)
        return;
    vars.max_z = find_max_z_value(map);
    vars.min_z = find_min_z_value(map);
    vars.z_scale = 7.5 / (vars.max_z - vars.min_z);
    if ((vars.max_z - vars.min_z) <= 1000)
        vars.z_scale = 5.0 / (vars.max_z - vars.min_z);
    if ((vars.max_z - vars.min_z) <= 100)
        vars.z_scale = 2.5 / (vars.max_z - vars.min_z);
    if ((vars.max_z - vars.min_z) <= 10)
        vars.z_scale = 0.5 / (vars.max_z - vars.min_z);

    drawData->scale = fmin(drawData->imageSize.x, drawData->imageSize.y) / (map->height + map->width) * 1;

    vars.map_center_x = (map->width - 1 - (map->height - 1)) * cos(M_PI / 4) * drawData->scale / 2;
    vars.map_center_y = ((map->width - 1) + (map->height - 1)) * sin(M_PI / 6) * drawData->scale / 2;

    vars.offsetX = (drawData->imageSize.x / 1.85) - vars.map_center_x;
    vars.offsetY = (drawData->imageSize.y / 1.3) - vars.map_center_y;

    int y = 0;
    while (y < map->height)
    {
        int x = 0;
        while (x < map->width)
        {
            int z = map->values[y][x];
            int color = init_color(z, vars.min_z, vars.max_z);

            vars.scaled_z = (z - vars.min_z) * vars.z_scale;

            vars.x_iso = (x - map->width / 2) * drawData->scale;
            vars.y_iso = (y - map->height / 2) * drawData->scale;
            vars.x2D = (vars.x_iso - vars.y_iso) * cos(M_PI / 4);
            vars.y2D = (vars.x_iso + vars.y_iso) * sin(M_PI / 6) - vars.scaled_z * drawData->scale;

            vars.x2D += vars.offsetX;
            vars.y2D += vars.offsetY;

            if (x < map->width - 1)
            {
                int next_z = map->values[y][x + 1];
                vars.scaled_next_z = (next_z - vars.min_z) * vars.z_scale;
                vars.next_x_iso = ((x + 1) - map->width / 2) * drawData->scale;
                vars.next_y_iso = (y - map->height / 2) * drawData->scale;
                vars.next_x2D = (vars.next_x_iso - vars.next_y_iso) * cos(M_PI / 4) + vars.offsetX;
                vars.next_y2D = (vars.next_x_iso + vars.next_y_iso) * sin(M_PI / 6) - vars.scaled_next_z * drawData->scale + vars.offsetY;

                lineData.x0 = vars.x2D;
                lineData.y0 = vars.y2D;
                lineData.x1 = vars.next_x2D;
                lineData.y1 = vars.next_y2D;
                lineData.color = color;

                draw_line(&lineData, drawData);
            }
            if (y < map->height - 1)
            {
                int next_z = map->values[y + 1][x];
                vars.scaled_next_z = (next_z - vars.min_z) * vars.z_scale;
                vars.next_x_iso = (x - map->width / 2) * drawData->scale;
                vars.next_y_iso = ((y + 1) - map->height / 2) * drawData->scale;
                vars.next_x2D = (vars.next_x_iso - vars.next_y_iso) * cos(M_PI / 4) + vars.offsetX;
                vars.next_y2D = (vars.next_x_iso + vars.next_y_iso) * sin(M_PI / 6) - vars.scaled_next_z * drawData->scale + vars.offsetY;

                lineData.x0 = vars.x2D;
                lineData.y0 = vars.y2D;
                lineData.x1 = vars.next_x2D;
                lineData.y1 = vars.next_y2D;
                lineData.color = color;

                draw_line(&lineData, drawData);
            }
            x++;
        }
        y++;
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
        drawData.map = &map;
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
    free_map(&map);
    free_draw_data(&drawData);
    return 0;
}