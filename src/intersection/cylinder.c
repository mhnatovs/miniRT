/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:12:39 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/18 17:18:21 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	project_perpend_axis(t_vector v, t_vector axis)
{
	float		proj_len;
	t_vector	parallel;

	proj_len = vector_dot(v, axis);
	parallel = vector_scale(axis, proj_len);
	return (vector_substract(v, parallel));
}

// calculates the intersection of ray with
// cylinder cap and returns t
// if the point is within the radius
static float	intersect_cap(t_ray ray, t_vector center,
								t_vector normal, float radius)
{
	float		denominator;
	float		t;
	t_vector	p_to_center;
	t_vector	hit_point;
	t_vector	v;

	denominator = vector_dot(ray.direction, normal);
	if (fabs(denominator) < 0.0001)
		return (-1.0);
	p_to_center = vector_substract(center, ray.origin);
	t = vector_dot(p_to_center, normal) / denominator;
	if (t < 0)
		return (-1.0);
	hit_point = vector_add(ray.origin, vector_scale(ray.direction, t));
	v = vector_substract(hit_point, center);
	if (vector_dot(v, v) <= radius * radius)
		return (t);
	return (-1.0);
}

// calculates the intersection of the ray
// with the upper and lower cylinder caps
// and returns the minimum positive t
static float	cyl_caps(t_ray ray, t_cylinder c)
{
	t_vector	top_center;
	float		t_top;
	float		t_bottom;

	top_center = vector_add(c.base, vector_scale(c.dir, c.height));
	t_top = intersect_cap(ray, top_center, c.dir, c.radius);
	t_bottom = intersect_cap(ray, c.base, vector_scale(c.dir, -1.0), c.radius);
	if (t_top > 0 && (t_bottom < 0 || t_top < t_bottom))
		return (t_top);
	return (t_bottom);
}

// returns the closest positive intersection between
// the side surface and cylinder caps
float	intersect_cylinder(t_ray ray, t_cylinder c)
{
	float	t_side;
	float	t_caps;

	t_side = intersect_cyl_side(ray, c);
	t_caps = cyl_caps(ray, c);
	if (t_side > 0 && (t_caps < 0 || t_side < t_caps))
		return (t_side);
	return (t_caps);
}
