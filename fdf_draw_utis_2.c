/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_utis_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:54:42 by bszikora          #+#    #+#             */
/*   Updated: 2024/08/23 14:54:57 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
