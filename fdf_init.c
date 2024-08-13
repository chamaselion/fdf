#include "fdf.h"

void init_window_size(t_DrawData *drawData, t_Map *map)
{
    // Get the window size to the default values
   // mlx_get_screen_size(drawData->mlx, &drawData->windowSize.x, &drawData->windowSize.y);
    drawData->windowSize.x = 1200;
    drawData->windowSize.y = 1200;

}

void init_image_size(t_DrawData *drawData, t_Map *map)
{
    drawData->imageSize.x = 800; // Assuming the image size is 800x800
    drawData->imageSize.y = 800;

    // Calculate the center position of the window
    int window_center_x = drawData->windowSize.x / 2;
    int window_center_y = drawData->windowSize.y / 2;

    // Calculate the center position of the image
    int image_center_x = drawData->imageSize.x / 2;
    int image_center_y = drawData->imageSize.y / 2;

    // Adjust the image position to center it in the window
    drawData->imagePosition.x = window_center_x - image_center_x;
    drawData->imagePosition.y = window_center_y - image_center_y;
}

int init_color(int z, int min_z, int max_z)
{
    // Normalize the height value to a range between 0 and 1
    float normalized = (float)(z - min_z) / (max_z - min_z);

    // Map the normalized value to a color gradient (e.g., blue to red)
    int red = (int)(normalized * 255);
    int green = 0;
    int blue = (int)((1 - normalized) * 255);

    // Combine the RGB values into a single integer
    return (red << 16) | (green << 8) | blue;
}