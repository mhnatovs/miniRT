/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:36:01 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/18 17:22:47 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// calculates ray intersection with plane and
// returns t if the point is in front of the ray
// 
// fabs() returns absolute value of a double type
float	intersect_plane(t_ray ray, t_plane plane)
{
	float		denominator;
	float		t;
	t_vector	p_to_origin;

	denominator = vector_dot(ray.direction, plane.normal);
	if (fabs(denominator) < 0.0001)
		return (-1.0);
	p_to_origin = vector_substract(plane.point, ray.origin);
	t = vector_dot(p_to_origin, plane.normal) / denominator;
	if (t < 0)
		return (-1.0);
	return (t);
}

t_vector	get_normal_plane(t_plane plane)
{
	return (plane.normal);
}
