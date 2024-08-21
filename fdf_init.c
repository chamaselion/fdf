#include "fdf.h"

void init_window_size(t_DrawData *drawData, t_Map *map)
{
    int a = 175;
  //  int b = 1300;
    drawData->windowSize.x -= a * 0.5625;
    drawData->windowSize.y -= a;
    //drawData->windowSize.x = b;
  //  drawData->windowSize.y = b;
}

void init_image_size(t_DrawData *drawData, t_Map *map)
{
    drawData->imageSize.x = drawData->windowSize.x; 
    drawData->imageSize.y = drawData->windowSize.y;
}

int interpolate(int start, int end, float factor)
{
    return (int)(start + (end - start) * factor);
}

int init_color(int z, int min_z, int max_z)
{
    // Check if z is negative
    if (z < 0) {
        // Return green color
        return (0 << 16) | (255 << 8) | 0;
    }

    // Check if z is zero
    if (z == 0) {
        // Return white color
        return (255 << 16) | (255 << 8) | 255;
    }

    // Normalize the height value to a range between 0 and 1
    float normalized = (float)(z - min_z) / (max_z - min_z);

    // Map the normalized value to a color gradient from white to magenta
    int red = (int)(normalized * 255);
    int green = (int)((1 - normalized) * 255);
    int blue = 255;

    return (red << 16) | (green << 8) | blue;
}

void init_draw_data(t_DrawData *drawData)
{
    drawData->mlx = NULL;
    drawData->window = NULL;
    drawData->image = NULL;
    drawData->windowSize.x = 0;
    drawData->windowSize.y = 0;
    drawData->windowSize.sx = 0;
    drawData->windowSize.sy = 0;
    drawData->imageSize.x = 0;
    drawData->imageSize.y = 0;
    drawData->imageSize.sx = 0;
    drawData->imageSize.sy = 0;
    drawData->scaleX = 1.0;
    drawData->scaleY = 1.0;
    drawData->scale = 1.0f;
    drawData->offsetX = 0;
    drawData->offsetY = 0;
    drawData->bpp = 0;
    drawData->line_bytes = 0;
    drawData->endian = 0;
    drawData->original_data = NULL;
    drawData->scaled_image = NULL;
    drawData->color = 0xFFFFFF; // Default color (white)
}