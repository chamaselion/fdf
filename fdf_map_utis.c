/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map_utis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:31:24 by bszikora          #+#    #+#             */
/*   Updated: 2024/08/29 13:55:01 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	find_max_z_value(t_map *map)
{
	int	max_z;
	int	y;
	int	x;

	if (map == NULL || map->values == NULL)
		return (0);
	max_z = map->values[0][0];
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->values[y][x] > max_z)
			{
				max_z = map->values[y][x];
			}
			x++;
		}
		y++;
	}
	return (max_z);
}

int	find_min_z_value(t_map *map)
{
	int	min_z;
	int	y;
	int	x;

	if (map == NULL || map->values == NULL)
		return (0);
	min_z = map->values[0][0];
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->values[y][x] < min_z)
			{
				min_z = map->values[y][x];
			}
			x++;
		}
		y++;
	}
	return (min_z);
}

void	fill_map_lines(t_map *map, char *line)
{
	int		length;
	int		*intarray;
	int		**new_values;
	size_t	original_size;

	intarray = string_to_int_array(line, &length);
	if (intarray == NULL)
		return ;
	original_size = sizeof(int *) * map->height;
	new_values = (int **)ft_realloc(map->values, original_size, sizeof(int *)
			* (map->height + 1));
	if (new_values == NULL)
	{
		free(intarray);
		perror("error reallocating memory");
		return ;
	}
	map->values = new_values;
	map->values[map->height] = intarray;
	map->width = length;
	map->height++;
}
