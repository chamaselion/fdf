/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:42:35 by bszikora          #+#    #+#             */
/*   Updated: 2024/08/23 14:43:06 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_image_size_vars(t_imagesize *size)
{
	size->x = 0;
	size->y = 0;
	size->sx = 0;
	size->sy = 0;
}

void	init_draw_data(t_drawdata *drawdata)
{
	drawdata->mlx = NULL;
	drawdata->window = NULL;
	drawdata->image = NULL;
	init_window_size_vars(&drawdata->windowsize);
	init_image_size_vars(&drawdata->imagesize);
	drawdata->scalex = 1.0;
	drawdata->scaley = 1.0;
	drawdata->scale = 1.0f;
	drawdata->offsetx = 0;
	drawdata->offsety = 0;
	drawdata->bpp = 0;
	drawdata->line_bytes = 0;
	drawdata->endian = 0;
	drawdata->original_data = NULL;
	drawdata->scaled_image = NULL;
	drawdata->color = 0xffffff;
}
