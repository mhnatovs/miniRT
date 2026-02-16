/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:12:39 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/16 17:56:45 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	intersect_cylinder(t_ray ray, t_cylinder c)
{
	// t_vector	oc;
	// float		t;
	// float		x;

	// oc = vector_substract(ray.origin, c.base);
	// x = vector_dot(ray.direction, c.dir);
	// if (fabs(x) < 0.0001)
	// 	return (-1.0);
	// return (t);
	return (intersect_cyl_side(ray, c));
}

static t_vector	project_perpend_axis(t_vector v, t_vector axis)
{
	float		proj_len;
	t_vector	parallel;

	proj_len = vector_dot(v, axis);
	parallel = vector_scale(axis, proj_len);
	return (vector_substract(v, parallel));
}

float	intersect_cyl_side(t_ray ray, t_cylinder c)
{
	t_vector	oc;
	t_vector	proj_oc;
	t_vector	proj_dir;
	float		coef[3];
	float		discriminant;
	float		t;

	oc = vector_substract(ray.origin, c.base);
	proj_oc = project_perpend_axis(oc, c.dir);
	proj_dir = project_perpend_axis(ray.direction, c.dir);
	coef[0] = vector_dot(proj_dir, proj_dir);
	coef[1] = 2.0 * vector_dot(proj_oc, proj_dir);
	coef[2] = vector_dot(proj_oc, proj_oc) - c.radius * c.radius;
	discriminant = coef[1] * coef[1] - 4 * coef[0] * coef[2];
	if (discriminant < 0)
		return (-1.0);
	t = (-coef[1] - sqrt(discriminant)) / (2.0 * coef[0]);
	if (t < 0)
		t = (-coef[1] + sqrt(discriminant)) / (2.0 * coef[0]);
	if (t < 0)
		return (-1.0);
	return (t);
}

// t_vector	get_normal_cylinder(t_cylinder c)
// {
// 	return (c.base);
// }