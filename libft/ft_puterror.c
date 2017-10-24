#include "libft.h"
#include <unistd.h>

void    ft_puterror(char *err)
{
    size_t  len;

    if (!err)
        return ;
    len = ft_strlen(err);
    write(2, err, len);
    write(2, "\n", 1);
}

