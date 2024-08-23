#include "fdf.h"

int open_file(const char *filepath)
{
    int fd;
    fd = open(filepath, O_RDONLY);
    return fd;
}

int count_integers_in_string(char *str)
{
    int count;
    int length;
    int inNumber;
    int c;

    count = 0;
    length = strlen(str);
    inNumber = 0;
    c = 0;

    while (c <= length - 1)
    {
        if (!isspace(str[c]) && str[c] != '\0')
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
    c++;
    }

    return count;
}