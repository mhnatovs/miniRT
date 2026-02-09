#ifndef VECTOR_H
# define VECTOR_H

# include "minirt.h"

typedef struct	s_vector
{
	float	x;
	float	y;
	float	z;
}				t_vector;

t_vector	*new_vector(float x, float y, float z);

#endif