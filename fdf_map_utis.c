#include "fdf.h"

int find_max_z_value(t_Map *map)
{
    if (map == NULL || map->values == NULL)
        return 0;

    int max_z = map->values[0][0];

    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            if (map->values[y][x] > max_z)
            {
                max_z = map->values[y][x];
            }
        }
    }

    return max_z;
}

int *string_to_int_array(char *str, int *outLength)
{
    int length = strlen(str);
    int numElements = count_integers_in_string(str);
    int *array = (int *)malloc(sizeof(int) * numElements);
    if (array == NULL)
    {
        *outLength = 0;
        return NULL;
    }

    char tempStr[11]; 
    int tempStrIndex = 0;
    int arrayIndex = 0;

    for (int i = 0; i <= length; i++)
    {
        if (isspace(str[i]) || str[i] == '\0')
        {
            if (tempStrIndex > 0)
            {
                tempStr[tempStrIndex] = '\0';
                array[arrayIndex++] = atoi(tempStr);
                tempStrIndex = 0;
            }
        }
        else
        {
            tempStr[tempStrIndex++] = str[i];
        }
    }

    *outLength = numElements;
    return array;
}

int count_integers_in_string(char *str)
{
    int count = 0;
    int length = strlen(str);
    int inNumber = 0;

    for (int i = 0; i <= length; i++)
    {
        if (!isspace(str[i]) && str[i] != '\0')
        {
            if (!inNumber)
            {
                inNumber = 1;
                count++;
            }
        }
        else
        {
            inNumber = 0;
        }
    }

    return count;
}

void fill_map_lines(t_Map *map, char *line)
{
    int length;
    int *intArray = string_to_int_array(line, &length);
    if (intArray == NULL)
        return;

    map->values = (int **)ft_realloc(map->values, sizeof(int *) * (map->height + 1));
    map->values[map->height] = intArray;
    map->width = length;
    map->height++;
}

void    map_filling(t_Map *map)
{
    int fd;
    char *line;

    fd = open_file("test.fdf");
    while ((line = get_next_line(fd)) != NULL)
    {
        fill_map_lines(map, line);
        free(line);
    }
    close(fd);
}