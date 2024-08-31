/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map_filling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:15:13 by bszikora          #+#    #+#             */
/*   Updated: 2024/08/31 13:44:13 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*create_file_path(char *folder_line, char *file_name)
{
	char	*file_path;

	file_path = malloc(sizeof(char) * (ft_strlen(folder_line)
				+ ft_strlen(file_name) + 1));
	if (file_path == NULL)
		return (NULL);
	ft_strcpy(file_path, folder_line);
	ft_strcat(file_path, file_name);
	return (file_path);
}

int	open_file_with_error_handling(char *file_path)
{
	int	fd;

	fd = open_file(file_path);
	if (fd <= 1)
	{
		free(file_path);
		printf("error. if test_maps folder is not present, create it plz.\n");
		exit(1);
	}
	free(file_path);
	return (fd);
}

void	read_and_fill_map(t_map *map, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		fill_map_lines(map, line);
		free(line);
		line = get_next_line(fd);
	}
}

void	check_map_height(t_map *map, int fd)
{
	if (map->height == 0)
	{
		close(fd);
		printf("error reading file\n");
		exit(1);
	}
}

int	map_filling(t_map *map, char *file_name)
{
	int		fd;
	char	*folder_line;
	char	*file_path;

	folder_line = "test_maps/";
	file_path = create_file_path(folder_line, file_name);
	if (file_path == NULL)
		return (-1);
	fd = open_file_with_error_handling(file_path);
	read_and_fill_map(map, fd);
	check_map_height(map, fd);
	close(fd);
	return (0);
}
