/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_file_utis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:26:02 by bszikora          #+#    #+#             */
/*   Updated: 2024/08/28 14:56:24 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	open_file(const char *filepath)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	return (fd);
}

int	count_integers_in_string(char *str)
{
	int	count;
	int	length;
	int	innumber;
	int	c;

	count = 0;
	length = ft_strlen(str);
	innumber = 0;
	c = 0;
	while (c <= length - 1)
	{
		if (!isspace(str[c]) && str[c] != '\0')
		{
			if (!innumber)
			{
				innumber = 1;
				count++;
			}
		}
		else
			innumber = 0;
		c++;
	}
	return (count);
}
