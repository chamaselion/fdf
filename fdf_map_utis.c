/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map_utis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:31:24 by bszikora          #+#    #+#             */
/*   Updated: 2024/08/23 14:31:36 by bszikora         ###   ########.fr       */
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

int	*string_to_int_array(char *str, int *outlength)
{
	int		length;
	int		numelements;
	int		*array;
	char	*tempstr;
	int		*index;

	index = (int *)malloc(sizeof(int) * 3);
	index[2] = 0;
	tempstr = (char *)malloc(sizeof(char) * 11);
	if (tempstr == NULL)
	{
		*outlength = 0;
		return (NULL);
	}
	length = strlen(str);
	numelements = count_integers_in_string(str);
	array = (int *)malloc(sizeof(int) * numelements);
	if (array == NULL)
	{
		free(tempstr);
		*outlength = 0;
		return (NULL);
	}
	index[0] = 0;
	index[1] = 0;
	while (index[2] <= length)
	{
		if (isspace(str[index[2]]) || str[index[2]] == '\0')
		{
			if (index[0] > 0)
			{
				tempstr[index[0]] = '\0';
				array[index[1]++] = atoi(tempstr);
				index[0] = 0;
			}
		}
		else
		{
			tempstr[index[0]++] = str[index[2]];
		}
		index[2]++;
	}
	free(tempstr);
	*outlength = numelements;
	free(index);
	return (array);
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

int	map_filling(t_map *map, char *file_name)
{
	int		fd;
	char	*line;
	char	*folder_line;
	char	*file_path;

	folder_line = "test_maps/";
	file_path = malloc(sizeof(char) * (strlen(folder_line) + strlen(file_name)
				+ 1));
	if (file_path == NULL)
		return (-1);
	strcpy(file_path, folder_line);
	strcat(file_path, file_name);
	fd = open_file(file_path);
	if (fd <= 1)
	{
		free(file_path);
		printf("error opening file. if test_maps folder is not present,\ncreate it and put the map files in it pls.\n");
		exit(1);
		return (-1);
	}
	free(file_path);
	line = get_next_line(fd);
	while (line != NULL)
	{
		fill_map_lines(map, line);
		free(line);
		line = get_next_line(fd);
	}
	if (map->height == 0)
	{
		close(fd);
		printf("error reading file\n");
		exit(1);
	}
	close(fd);
	return (0);
}

/*
void	print_map(t_map *map)
{
   if (map == null || map->values == null)
   {
		printf("map is empty or not initialized.\n");
		return ;
   }
   printf("map (width: %d, height: %d):\n", map->width, map->height);
   for (int i = 0; i < map->height; i++)
   {
		for (int j = 0; j < map->width; j++)
		{
			printf("%d ", map->values[i][j]);
		}
		printf("\n");
   }
}
*/
