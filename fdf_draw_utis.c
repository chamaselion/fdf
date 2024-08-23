/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_utis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:11:38 by bszikora          #+#    #+#             */
/*   Updated: 2024/08/23 14:28:38 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel_to_image(void *image, int x, int y, int color)
{
	char	*buffer;
	int		pos;
	int		pixel_bits;
	int		line_bytes;
	int		endian;

	buffer = mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);
	pos = (y * line_bytes) + (x * (pixel_bits / 8));
	*(int *)(buffer + pos) = color;
}

void	draw_line(t_linedata *linedata, t_drawdata *drawdata)
{
	int	image_width;
	int	image_height;

	image_width = drawdata->windowsize.x;
	image_height = drawdata->windowsize.y;
	if (linedata->x0 < 0 || linedata->x0 >= image_width || linedata->y0 < 0
		|| linedata->y0 >= image_height || linedata->x1 < 0
		|| linedata->x1 >= image_width || linedata->y1 < 0
		|| linedata->y1 >= image_height)
	{
		printf("coordinates out of bounds: (%d, %d) to (%d, %d)\n",
			linedata->x0, linedata->y0, linedata->x1, linedata->y1);
		return ;
	}
	linedata->dx = abs(linedata->x1 - linedata->x0);
	linedata->dy = abs(linedata->y1 - linedata->y0);
	if (linedata->x0 < linedata->x1)
		linedata->sx = 1;
	else
		linedata->sx = -1;
	if (linedata->y0 < linedata->y1)
		linedata->sy = 1;
	else
		linedata->sy = -1;
	if (linedata->dx > linedata->dy)
		linedata->err = linedata->dx;
	else
		linedata->err = -linedata->dy;
	linedata->err /= 2;
	while (1)
	{
		put_pixel_to_image(drawdata->image, linedata->x0, linedata->y0,
			linedata->color);
		if (linedata->x0 == linedata->x1 && linedata->y0 == linedata->y1)
			break ;
		linedata->e2 = linedata->err;
		if (linedata->e2 > -linedata->dx)
		{
			linedata->err -= linedata->dy;
			linedata->x0 += linedata->sx;
		}
		if (linedata->e2 < linedata->dy)
		{
			linedata->err += linedata->dx;
			linedata->y0 += linedata->sy;
		}
	}
}

int	close_window(t_drawdata *drawdata)
{
	if (drawdata->window != NULL)
	{
		mlx_destroy_window(drawdata->mlx, drawdata->window);
		drawdata->window = NULL;
	}
	free_draw_data(drawdata);
	free_map(drawdata->map);
	exit(0);
	return (0);
}

int	key_event_handler(int keycode, t_drawdata *drawdata)
{
	if (keycode == 65307)
	{
		if (drawdata->window != NULL)
		{
			mlx_destroy_window(drawdata->mlx, drawdata->window);
			drawdata->window = NULL;
		}
		free_draw_data(drawdata);
		free_map(drawdata->map);
		exit(0);
	}
	return (0);
}
