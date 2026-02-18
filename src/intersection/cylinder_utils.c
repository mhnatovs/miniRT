/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:16:49 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/18 17:10:47 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// check if point is inside height
static int	is_inside_height(t_vector hit, t_cylinder c)
{
	t_vector	v;
	float		h;

	v = vector_substract(hit, c.base);
	h = vector_dot(v, c.dir);
	return (h >= 0 && h <= c.height);
}

// check if point in front of the ray is valid
// calculates hit_point and returns it (t) if it is between caps
static float	check_t(float t, t_ray ray, t_cylinder c)
{
	t_vector	hit;

	if (t <= 0)
		return (-1.0);
	hit = vector_add(ray.origin, vector_scale(ray.direction, t));
	if (is_inside_height(hit, c))
		return (t);
	return (-1.0);
}

// calculates the normal to the cylinder surface:
// returns the normal to the cap or side surface
// depending on the point of hit
t_vector	get_normal_cylinder(t_vector hit_point, t_cylinder c)
{
	t_vector	v_from_base;
	float		height_proj;
	t_vector	axis_point;
	t_vector	normal;

	v_from_base = vector_substract(hit_point, c.base);
	height_proj = vector_dot(v_from_base, c.dir);
	if (height_proj <= 0.001)
		return (vector_scale(c.dir, -1.0));
	if (height_proj >= c.height - 0.001)
		return (c.dir);
	axis_point = vector_add(c.base, vector_scale(c.dir, height_proj));
	normal = vector_substract(hit_point, axis_point);
	return (vector_normalize(normal));
}

// coef: coefficients of the quadratic equation (a, b, c)
// for the intersection of the ray with the side surface
// of the cylinder
float	intersect_cyl_side(t_ray ray, t_cylinder c)
{
	t_cyl_tmp	tmp;
	float		discriminant;
	float		t;

	tmp.oc = vector_substract(ray.origin, c.base);
	tmp.proj_oc = project_perpend_axis(tmp.oc, c.dir);
	tmp.proj_dir = project_perpend_axis(ray.direction, c.dir);
	tmp.coef[0] = vector_dot(tmp.proj_dir, tmp.proj_dir);
	tmp.coef[1] = 2.0 * vector_dot(tmp.proj_oc, tmp.proj_dir);
	tmp.coef[2] = vector_dot(tmp.proj_oc, tmp.proj_oc) - c.radius * c.radius;
	discriminant = tmp.coef[1] * tmp.coef[1] - 4 * tmp.coef[0] * tmp.coef[2];
	if (discriminant < 0)
		return (-1.0);
	t = check_t((-tmp.coef[1] - sqrt(discriminant))
			/ (2.0 * tmp.coef[0]), ray, c);
	if (t > 0)
		return (t);
	return (check_t((-tmp.coef[1] + sqrt(discriminant))
			/ (2.0 * tmp.coef[0]), ray, c));
}
