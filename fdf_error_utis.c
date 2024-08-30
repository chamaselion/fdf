/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error_utis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:13:15 by bszikora          #+#    #+#             */
/*   Updated: 2024/08/29 16:47:37 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_n_null(void **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_draw_data(t_drawdata *drawdata)
{
	if (drawdata->image != NULL)
	{
		mlx_destroy_image(drawdata->mlx, drawdata->image);
		drawdata->image = NULL;
	}
	if (drawdata->window != NULL)
	{
		mlx_destroy_window(drawdata->mlx, drawdata->window);
		drawdata->window = NULL;
	}
	if (drawdata->mlx != NULL)
	{
		free(drawdata->mlx);
		drawdata->mlx = NULL;
	}
	if (drawdata->original_data != NULL)
	{
		free(drawdata->original_data);
		drawdata->original_data = NULL;
	}
	if (drawdata->scaled_image != NULL)
		free_n_null((void **)&drawdata->scaled_image);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map != NULL)
	{
		if (map->values != NULL)
		{
			while (i < map->height)
			{
				if (map->values[i] != NULL)
				{
					free(map->values[i]);
					map->values[i] = NULL;
				}
				i++;
			}
			free(map->values);
			map->values = NULL;
		}
	}
}
