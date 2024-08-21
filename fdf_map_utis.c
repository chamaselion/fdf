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

int find_min_z_value(t_Map *map)
{
    int min_z = map->values[0][0];
    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            if (map->values[y][x] < min_z)
                min_z = map->values[y][x];
        }
    }
    return min_z;
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

void fill_map_lines(t_Map *map, char *line)
{
    int length;
    int *intArray = string_to_int_array(line, &length);
    if (intArray == NULL)
        return;

    // Allocate memory for the new row
    int **new_values = (int **)ft_realloc(map->values, sizeof(int *) * (map->height + 1));
    if (new_values == NULL)
    {
        free(intArray); // Free the allocated intArray if realloc fails
        perror("Error reallocating memory");
        return;
    }

    map->values = new_values;
    map->values[map->height] = intArray;
    map->width = length;
    map->height++;
}

int map_filling(t_Map *map, char *file_name)
{
    int fd;
    char *line;
    char *folder_line = "test_maps/";
    char *file_path = malloc(sizeof(char) * (strlen(folder_line) + strlen(file_name) + 1));
    if (file_path == NULL)
        return (-1);
    strcpy(file_path, folder_line);
    strcat(file_path, file_name);

    fd = open_file(file_path);
    if (fd <= 1)
    {
        free(file_path);
        printf("Error opening file. If test_maps folder is not present,\ncreate it and put the map files in it pls.\n");
        exit(1);
        return (-1);
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        fill_map_lines(map, line);
        if (map->height > 0 && map->values != NULL && map->values[0] != NULL)
        {
        }
        free(line);
    }

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