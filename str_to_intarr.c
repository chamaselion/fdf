/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_intarr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:11:19 by bszikora          #+#    #+#             */
/*   Updated: 2024/08/23 16:12:41 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	parse_string(char *str, int *array, char *tempstr, int *index)
{
	int	length;

	length = strlen(str);
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
}

int	*string_to_int_array(char *str, int *outlength)
{
	int		numelements;
	int		*array;
	char	*tempstr;
	int		*index;

	index = initialize_memory(&tempstr, &index, outlength);
	if (index == NULL)
		return (NULL);
	numelements = count_integers_in_string(str);
	array = allocate_array(numelements, tempstr, outlength);
	if (array == NULL)
		return (NULL);
	index[0] = 0;
	index[1] = 0;
	index[2] = 0;
	parse_string(str, array, tempstr, index);
	free(tempstr);
	*outlength = numelements;
	free(index);
	return (array);
}
