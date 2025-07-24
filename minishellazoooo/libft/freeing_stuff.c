#include "libft.h"

void    free_array(char **map, int lines)
{
    int i;

    i = 0;
    while (i < lines)
    {
        free(map[i]);
        i++;
    }
    free(map);
}
