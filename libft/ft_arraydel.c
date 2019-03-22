#include "libft.h"

void    ft_arraydel(char **array)
{
    while (*array)
    {
        ft_strdel(array);
        array++;
    }
}