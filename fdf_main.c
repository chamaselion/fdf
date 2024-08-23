/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:21:01 by bszikora          #+#    #+#             */
/*   Updated: 2024/08/23 14:31:14 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_map(t_drawdata *drawdata, t_map *map)
{
	t_drawmapvars	vars;
	t_linedata		linedata;
	int				y;
	int				x;
	int				*z;

	z = malloc(sizeof(int) * 2);
	if (!drawdata->mlx || !drawdata->window || map->values == NULL)
		return ;
	if (map->width <= 0 || map->height <= 0)
		return ;
	drawdata->image = mlx_new_image(drawdata->mlx, drawdata->imagesize.x,
			drawdata->imagesize.y);
	if (drawdata->image == NULL)
		return ;
	vars.max_z = find_max_z_value(map);
	vars.min_z = find_min_z_value(map);
	vars.z_scale = 7.5 / (vars.max_z - vars.min_z);
	if ((vars.max_z - vars.min_z) <= 1000)
		vars.z_scale = 5.0 / (vars.max_z - vars.min_z);
	if ((vars.max_z - vars.min_z) <= 100)
		vars.z_scale = 2.5 / (vars.max_z - vars.min_z);
	if ((vars.max_z - vars.min_z) <= 10)
		vars.z_scale = 0.5 / (vars.max_z - vars.min_z);
	drawdata->scale = fmin(drawdata->imagesize.x, drawdata->imagesize.y)
		/ (map->height + map->width) * 1;
	vars.map_center_x = (map->width - 1 - (map->height - 1)) * cos(M_PI / 4)
		* drawdata->scale / 2;
	vars.map_center_y = ((map->width - 1) + (map->height - 1)) * sin(M_PI / 6)
		* drawdata->scale / 2;
	vars.offsetx = (drawdata->imagesize.x / 1.85) - vars.map_center_x;
	vars.offsety = (drawdata->imagesize.y / 1.3) - vars.map_center_y;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			z[0] = map->values[y][x];
			drawdata->color = init_color(z[0], vars.min_z, vars.max_z);
			vars.scaled_z = (z[0] - vars.min_z) * vars.z_scale;
			vars.x_iso = (x - map->width / 2) * drawdata->scale;
			vars.y_iso = (y - map->height / 2) * drawdata->scale;
			vars.x2d = (vars.x_iso - vars.y_iso) * cos(M_PI / 4);
			vars.y2d = (vars.x_iso + vars.y_iso) * sin(M_PI / 6) - vars.scaled_z
				* drawdata->scale;
			vars.x2d += vars.offsetx;
			vars.y2d += vars.offsety;
			if (x < map->width - 1)
			{
				z[1] = map->values[y][x + 1];
				vars.scaled_next_z = (z[1] - vars.min_z) * vars.z_scale;
				vars.next_x_iso = ((x + 1) - map->width / 2) * drawdata->scale;
				vars.next_y_iso = (y - map->height / 2) * drawdata->scale;
				vars.next_x2d = (vars.next_x_iso - vars.next_y_iso) * cos(M_PI
						/ 4) + vars.offsetx;
				vars.next_y2d = (vars.next_x_iso + vars.next_y_iso) * sin(M_PI
						/ 6) - vars.scaled_next_z * drawdata->scale
					+ vars.offsety;
				linedata.x0 = vars.x2d;
				linedata.y0 = vars.y2d;
				linedata.x1 = vars.next_x2d;
				linedata.y1 = vars.next_y2d;
				linedata.color = drawdata->color;
				draw_line(&linedata, drawdata);
			}
			if (y < map->height - 1)
			{
				z[1] = map->values[y + 1][x];
				vars.scaled_next_z = (z[1] - vars.min_z) * vars.z_scale;
				vars.next_x_iso = (x - map->width / 2) * drawdata->scale;
				vars.next_y_iso = ((y + 1) - map->height / 2) * drawdata->scale;
				vars.next_x2d = (vars.next_x_iso - vars.next_y_iso) * cos(M_PI
						/ 4) + vars.offsetx;
				vars.next_y2d = (vars.next_x_iso + vars.next_y_iso) * sin(M_PI
						/ 6) - vars.scaled_next_z * drawdata->scale
					+ vars.offsety;
				linedata.x0 = vars.x2d;
				linedata.y0 = vars.y2d;
				linedata.x1 = vars.next_x2d;
				linedata.y1 = vars.next_y2d;
				linedata.color = drawdata->color;
				draw_line(&linedata, drawdata);
			}
			x++;
		}
		y++;
	}
	free(z);
}

int	main(int argc, char **argv)
{
	t_drawdata	drawdata;
	t_map		map;

	map.values = NULL;
	map.width = 0;
	map.height = 0;
	if (argc == 1 || argc > 2)
	{
		printf("actually it's: %s <filename.fdf>\n", argv[0]);
		return (1);
	}
	if (map_filling(&map, argv[1]) == 0)
	{
		drawdata.map = &map;
		init_draw_data(&drawdata);
		drawdata.mlx = mlx_init();
		if (!drawdata.mlx)
			return (1);
		mlx_get_screen_size(drawdata.mlx, &drawdata.windowsize.x,
			&drawdata.windowsize.y);
		init_window_size(&drawdata);
		init_image_size(&drawdata);
		drawdata.window = mlx_new_window(drawdata.mlx, drawdata.windowsize.x,
				drawdata.windowsize.y, "fdf");
		if (!drawdata.window)
			return (1);
		draw_map(&drawdata, &map);
		if (drawdata.image != NULL)
			mlx_put_image_to_window(drawdata.mlx, drawdata.window,
				drawdata.image, 0, 0);
		mlx_key_hook(drawdata.window, key_event_handler, &drawdata);
		mlx_hook(drawdata.window, 17, 0, close_window, &drawdata);
		mlx_loop(drawdata.mlx);
	}
	else
	{
		printf("error reading the map. please make sure to give the name of an existing \n.fdf file as an argument. chceck the presence of the test_maps folder.\nif not present, create it and place the map files in it.\n");
		return (1);
	}
	free_map(&map);
	free_draw_data(&drawdata);
	return (0);
}
