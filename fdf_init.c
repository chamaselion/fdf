/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:15:19 by bszikora          #+#    #+#             */
/*   Updated: 2024/08/23 14:42:59 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_window_size(t_drawdata *drawdata)
{
	int	a;

	a = 175;
	drawdata->windowsize.x -= a * 0.5625;
	drawdata->windowsize.y -= a;
}

void	init_image_size(t_drawdata *drawdata)
{
	drawdata->imagesize.x = drawdata->windowsize.x;
	drawdata->imagesize.y = drawdata->windowsize.y;
}

int	interpolate(int start, int end, float factor)
{
	return ((int)(start + (end - start) * factor));
}

int	init_color(int z, int min_z, int max_z)
{
	int		red;
	int		green;
	int		blue;
	float	normalized;

	if (z < 0)
	{
		return ((0 << 16) | (255 << 8) | 0);
	}
	if (z == 0)
	{
		return ((255 << 16) | (255 << 8) | 255);
	}
	normalized = (float)(z - min_z) / (max_z - min_z);
	red = (int)(normalized * 255);
	green = (int)((1 - normalized) * 255);
	blue = 255;
	return ((red << 16) | (green << 8) | blue);
}

void	init_window_size_vars(t_imagesize *size)
{
	size->x = 0;
	size->y = 0;
	size->sx = 0;
	size->sy = 0;
}
