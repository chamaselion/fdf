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
        // Assuming mlx_destroy_display is available in your version of MiniLibX
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