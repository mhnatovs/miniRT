/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:36:01 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/04/14 12:17:02 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// calculates ray intersection with plane and
// returns t if the point is in front of the ray
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
	if (t < 0.001f)
		return (-1.0);
	return (t);
}

t_vector	get_normal_plane(t_plane plane, t_ray ray)
{
	t_vector	n;

	n = plane.normal;
	if (vector_dot(ray.direction, n) > 0)
		n = vector_scale(n, -1.0f);
	return (n);
}
