/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:44:32 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/20 14:26:08 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}			t_vector;

float		vector_length(t_vector a);
t_vector	vector_normalize(t_vector a);
t_vector	vector_add(t_vector a, t_vector b);
t_vector	vector_substract(t_vector a, t_vector b);
t_vector	vector_scale(t_vector v, float k);
float		vector_dot(t_vector a, t_vector b);
t_vector	vector_cross(t_vector a, t_vector b);

#endif