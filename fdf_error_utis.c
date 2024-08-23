#include "fdf.h"

void free_draw_data(t_DrawData *drawData)
{
    if (drawData->image != NULL)
    {
        mlx_destroy_image(drawData->mlx, drawData->image);
        drawData->image = NULL;
    }
    if (drawData->window != NULL)
    {
        mlx_destroy_window(drawData->mlx, drawData->window);
        drawData->window = NULL;
    }
    if (drawData->mlx != NULL)
    {
        mlx_destroy_display(drawData->mlx);
        free(drawData->mlx);
        drawData->mlx = NULL;
    }
    if (drawData->original_data != NULL)
    {
        free(drawData->original_data);
        drawData->original_data = NULL;
    }
    if (drawData->scaled_image != NULL)
    {
        free(drawData->scaled_image);
        drawData->scaled_image = NULL;
    }
}

void free_map(t_Map *map)
{
    int i;

    i = 0;
    if (map != NULL)
    {
        if (map->values != NULL)
        {
            while (i < map->height)
            {
                if (map->values[i] != NULL)
                {
                    free(map->values[i]);
                    map->values[i] = NULL;
                }
                i++;
            }
            free(map->values);
            map->values = NULL;
        }
        //free(map);
    }
}