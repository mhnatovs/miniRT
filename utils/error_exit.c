#include "minirt.h"

void    error_exit(int code)
{
    if (code == -1)
        write (STDERR_FILENO, "Error: memory allocation\n", 25);
    exit(code);
}
