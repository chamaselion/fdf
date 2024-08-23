/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:19:33 by bszikora          #+#    #+#             */
/*   Updated: 2024/08/23 16:43:33 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_vertical_line(t_drawparams *params, int x, int y, int *z)
{
	if (y < params->map->height - 1)
	{
		z[1] = params->map->values[y + 1][x];
		params->vars->scaled_next_z = (z[1] - params->vars->min_z)
			* params->vars->z_scale;
		params->vars->next_x_iso = (x - params->map->width / 2)
			* params->drawdata->scale;
		params->vars->next_y_iso = ((y + 1) - params->map->height / 2)
			* params->drawdata->scale;
		params->vars->next_x2d = (params->vars->next_x_iso
				- params->vars->next_y_iso) * cos(M_PI / 4)
			+ params->vars->offsetx;
		params->vars->next_y2d = (params->vars->next_x_iso
				+ params->vars->next_y_iso) * sin(M_PI / 6)
			- params->vars->scaled_next_z * params->drawdata->scale
			+ params->vars->offsety;
		params->linedata->x0 = params->vars->x2d;
		params->linedata->y0 = params->vars->y2d;
		params->linedata->x1 = params->vars->next_x2d;
		params->linedata->y1 = params->vars->next_y2d;
		params->linedata->color = params->drawdata->color;
		draw_line(params->linedata, params->drawdata);
	}
}

void	draw_horizontal_line(t_drawparams *params, int x, int y, int *z)
{
	if (x < params->map->width - 1)
	{
		z[1] = params->map->values[y][x + 1];
		params->vars->scaled_next_z = (z[1] - params->vars->min_z)
			* params->vars->z_scale;
		params->vars->next_x_iso = ((x + 1) - params->map->width / 2)
			* params->drawdata->scale;
		params->vars->next_y_iso = (y - params->map->height / 2)
			* params->drawdata->scale;
		params->vars->next_x2d = (params->vars->next_x_iso
				- params->vars->next_y_iso) * cos(M_PI / 4)
			+ params->vars->offsetx;
		params->vars->next_y2d = (params->vars->next_x_iso
				+ params->vars->next_y_iso) * sin(M_PI / 6)
			- params->vars->scaled_next_z * params->drawdata->scale
			+ params->vars->offsety;
		params->linedata->x0 = params->vars->x2d;
		params->linedata->y0 = params->vars->y2d;
		params->linedata->x1 = params->vars->next_x2d;
		params->linedata->y1 = params->vars->next_y2d;
		params->linedata->color = params->drawdata->color;
		draw_line(params->linedata, params->drawdata);
	}
}

void	calculate_iso_coordinates(t_drawparams *params, int x, int y, int *z)
{
	z[0] = params->map->values[y][x];
	params->drawdata->color = init_color(z[0], params->vars->min_z,
			params->vars->max_z);
	params->vars->scaled_z = (z[0] - params->vars->min_z)
		* params->vars->z_scale;
	params->vars->x_iso = (x - params->map->width / 2)
		* params->drawdata->scale;
	params->vars->y_iso = (y - params->map->height / 2)
		* params->drawdata->scale;
	params->vars->x2d = (params->vars->x_iso - params->vars->y_iso) * cos(M_PI
			/ 4);
	params->vars->y2d = (params->vars->x_iso + params->vars->y_iso) * sin(M_PI
			/ 6) - params->vars->scaled_z * params->drawdata->scale;
	params->vars->x2d += params->vars->offsetx;
	params->vars->y2d += params->vars->offsety;
}

void	draw_map_looped(t_drawparams *params, int *z)
{
	int	x;
	int	y;

	y = 0;
	while (y < params->map->height)
	{
		x = 0;
		while (x < params->map->width)
		{
			calculate_iso_coordinates(params, x, y, z);
			draw_horizontal_line(params, x, y, z);
			draw_vertical_line(params, x, y, z);
			x++;
		}
		y++;
	}
}

void	draw_map_loop(t_drawdata *drawdata, t_map *map, t_drawmapvars *vars)
{
	int				*z;
	t_linedata		linedata;
	t_drawparams	params;

	z = malloc(sizeof(int) * 2);
	if (!z)
		return ;
	params.drawdata = drawdata;
	params.map = map;
	params.vars = vars;
	params.linedata = &linedata;
	draw_map_looped(&params, z);
	free(z);
}
