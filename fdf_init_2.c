/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:42:35 by bszikora          #+#    #+#             */
/*   Updated: 2024/08/31 14:03:48 by bszikora         ###   ########.fr       */
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

void	initialize_z_scale(t_map *map, t_drawmapvars *vars)
{
	vars->max_z = find_max_z_value(map);
	vars->min_z = find_min_z_value(map);
	vars->z_scale = 3.5 / (vars->max_z - vars->min_z);
	if ((vars->max_z - vars->min_z) <= 1000)
		vars->z_scale = 3.0 / (vars->max_z - vars->min_z);
	if ((vars->max_z - vars->min_z) <= 100)
		vars->z_scale = 2.5 / (vars->max_z - vars->min_z);
	if ((vars->max_z - vars->min_z) <= 10)
		vars->z_scale = 0.5 / (vars->max_z - vars->min_z);
}

int	*initialize_memory(char **tempstr, int **index, int *outlength)
{
	*index = (int *)malloc(sizeof(int) * 3);
	*tempstr = (char *)malloc(sizeof(char) * 11);
	if (*tempstr == NULL)
	{
		*outlength = 0;
		return (NULL);
	}
	return (*index);
}

int	*allocate_array(int numelements, char *tempstr, int *outlength)
{
	int	*array;

	array = (int *)malloc(sizeof(int) * numelements);
	if (array == NULL)
	{
		free(tempstr);
		*outlength = 0;
		return (NULL);
	}
	return (array);
}
