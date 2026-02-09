#ifndef VECTOR_H
# define VECTOR_H

typedef struct	s_vector
{
	float	x;
	float	y;
	float	z;
}				t_vector;

typedef struct s_matrix
{
	float rotation[4][4];
	float position[4][4];
	float trans[4][4];
} t_matrix;

t_vector	*new_vector(float x, float y, float z);

#endif