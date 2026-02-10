#include "minirt.h"

t_vector	*new_vector(float x, float y, float z)
{
	t_vector	*vec;

	vec = malloc(sizeof(t_vector));
	if (!vec)
	{
		error_exit(-1);
		return (NULL);
	}
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (vec);
}
