/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:21:01 by bszikora          #+#    #+#             */
/*   Updated: 2024/08/23 16:54:17 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	all_values_same(t_map *map)
{
	int	first_value;
	int	x;
	int	y;

	if (map->height == 0 || map->width == 0)
		return (1);
	first_value = map->values[0][0];
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->values[y][x] != first_value)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

void	adjust_values_if_same(t_map *map)
{
	int	y;
	int	x;

	if (all_values_same(map))
	{
		y = 0;
		while (y < map->height)
		{
			x = 0;
			while (x < map->width)
			{
				map->values[y][x] += y + x;
				x++;
			}
			y++;
		}
	}
}

void	draw_map(t_drawdata *drawdata, t_map *map)
{
	t_drawmapvars	vars;

	if (!drawdata->mlx || !drawdata->window || map->values == NULL)
		return ;
	if (map->width <= 0 || map->height <= 0)
		return ;
	drawdata->image = mlx_new_image(drawdata->mlx, drawdata->imagesize.x,
			drawdata->imagesize.y);
	if (drawdata->image == NULL)
		return ;
	adjust_values_if_same(map);
	initialize_z_scale(map, &vars);
	drawdata->scale = fmin(drawdata->imagesize.x, drawdata->imagesize.y)
		/ (map->height + map->width) * 1;
	vars.map_center_x = (map->width - 1 - (map->height - 1)) * cos(M_PI / 4)
		* drawdata->scale / 2;
	vars.map_center_y = ((map->width - 1) + (map->height - 1)) * sin(M_PI / 6)
		* drawdata->scale / 2;
	vars.offsetx = (drawdata->imagesize.x / 1.85) - vars.map_center_x;
	vars.offsety = (drawdata->imagesize.y / 1.3) - vars.map_center_y;
	draw_map_loop(drawdata, map, &vars);
}

int	lessdo_fdf(t_drawdata *drawdata, t_map *map)
{
	drawdata->map = map;
	init_draw_data(drawdata);
	drawdata->mlx = mlx_init();
	if (!drawdata->mlx)
		return (1);
	mlx_get_screen_size(drawdata->mlx, &drawdata->windowsize.x,
		&drawdata->windowsize.y);
	init_window_size(drawdata);
	init_image_size(drawdata);
	drawdata->window = mlx_new_window(drawdata->mlx, drawdata->windowsize.x,
			drawdata->windowsize.y, "fdf");
	if (!drawdata->window)
		return (1);
	draw_map(drawdata, map);
	if (drawdata->image != NULL)
		mlx_put_image_to_window(drawdata->mlx, drawdata->window,
			drawdata->image, 0, 0);
	mlx_key_hook(drawdata->window, key_event_handler, drawdata);
	mlx_hook(drawdata->window, 17, 0, close_window, drawdata);
	mlx_loop(drawdata->mlx);
	return (0);
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
		lessdo_fdf(&drawdata, &map);
	else
	{
		printf("error. please make sure to give the name of an existing \n");
		printf(".fdf file as an argument. check the test_maps folder.\n");
		printf("if not present,create it and place the map files in it.\n");
		return (1);
	}
	free_map(&map);
	free_draw_data(&drawdata);
	return (0);
}
