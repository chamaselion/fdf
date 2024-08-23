#include "fdf.h"

#include "fdf.h"

void *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void *new_ptr;

    if (new_size == 0)
    {
        free(ptr);
        return NULL;
    }

    new_ptr = malloc(new_size);
    if (new_ptr == NULL)
        return NULL;

    if (ptr != NULL)
    {
        if (old_size < new_size)
        {
            memmove(new_ptr, ptr, old_size);
        }
        else
        {
            memmove(new_ptr, ptr, new_size);
        }
        free(ptr);
    }

    return new_ptr;
}