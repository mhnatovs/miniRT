#include "minirt.h"

void    error_exit(char *msg)
{
    if (msg)
        write (STDERR_FILENO, msg, ft_strlen(msg));
    write (STDERR_FILENO, "\n", 1);
    exit(1);
}
