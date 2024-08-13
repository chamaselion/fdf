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

    for (int i = 0; i <= length - 1; i++)
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
    printf("before string to arr\n");
    int *intArray = string_to_int_array(line, &length);
    printf("after string to arr\n");
    if (intArray == NULL)
        return;

    // Allocate memory for the new row
    printf("before realloc\n");
    int **new_values = (int **)ft_realloc(map->values, sizeof(int *) * (map->height + 1));
    if (new_values == NULL)
    {
        free(intArray); // Free the allocated intArray if realloc fails
        perror("Error reallocating memory");
        return;
    }
    printf("after realloc\n");

    map->values = new_values;
    map->values[map->height] = intArray;
    map->width = length;
    map->height++;
    printf("after updating map\n");
}

int map_filling(t_Map *map)
{
    int fd;
    char *line;

    printf("before openfile\n");
    fd = open_file("test_maps/42.fdf");
    printf("openfile\n");
    if (fd <= 1)
    {
        perror("Error opening file");
        return (-1);
    }

    printf("before gnl\n");
    while ((line = get_next_line(fd)) != NULL)
    {
        fill_map_lines(map, line);
        if (map->height > 0 && map->values != NULL && map->values[0] != NULL)
        {
            printf("gnl:%i\n", map->values[0][0]);
        }
        free(line);
    }

    printf("after gnl\n");
    if (map->height == 0)
    {
        close(fd);
        perror("Error reading file");
        return (-1);
    }

    close(fd);
    return (0);
}

void print_map(t_Map *map)
{
    if (map == NULL || map->values == NULL)
    {
        printf("Map is empty or not initialized.\n");
        return;
    }

    printf("Map (width: %d, height: %d):\n", map->width, map->height);
    for (int i = 0; i < map->height; i++)
    {
        for (int j = 0; j < map->width; j++)
        {
            printf("%d ", map->values[i][j]);
        }
        printf("\n");
    }
}