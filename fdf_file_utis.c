#include "fdf.h"

int open_file(const char *filepath)
{
    int fd = open(filepath, O_RDONLY);
    return fd;
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