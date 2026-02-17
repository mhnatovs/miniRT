/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:12:39 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/17 14:55:58 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector	project_perpend_axis(t_vector v, t_vector axis)
{
	float		proj_len;
	t_vector	parallel;

	proj_len = vector_dot(v, axis);
	parallel = vector_scale(axis, proj_len);
	return (vector_substract(v, parallel));
}

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

float	intersect_cylinder(t_ray ray, t_cylinder c)
{
	float		t_side;
	float		t_top;
	float		t_bottom;
	t_vector	top_center;
	t_vector	top_normal;
	t_vector	bot_normal;
	float		t_min;

	t_side = intersect_cyl_side(ray, c);
	top_center = vector_add(c.base, vector_scale(c.dir, c.height));
	top_normal = c.dir;
	t_top = intersect_cap(ray, top_center, top_normal, c.radius);
	bot_normal = vector_scale(c.dir, -1.0);
	t_bottom = intersect_cap(ray, c.base, bot_normal, c.radius);
	t_min = -1.0;
	if (t_side > 0)
		t_min = t_side;
	if (t_top > 0 && (t_min < 0 || t_top < t_min))
		t_min = t_top;
	if (t_bottom > 0 && (t_min < 0 || t_bottom < t_min))
		t_min = t_bottom;
	return (t_min);
}

float	intersect_cyl_side(t_ray ray, t_cylinder c)
{
	t_vector	oc;
	t_vector	proj_oc;
	t_vector	proj_dir;
	float		coef[3];
	float		discriminant;
	float		t;
	t_vector	hit_point;
	t_vector	v_from_base;
	float		height_on_axis;

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
	if (t > 0)
	{
		hit_point = vector_add(ray.origin, vector_scale(ray.direction, t));
		v_from_base = vector_substract(hit_point, c.base);
		height_on_axis = vector_dot(v_from_base, c.dir);
		if (height_on_axis >= 0 && height_on_axis <= c.height)
			return (t);
	}
	t = (-coef[1] + sqrt(discriminant)) / (2.0 * coef[0]);
	if (t > 0)
	{
		hit_point = vector_add(ray.origin, vector_scale(ray.direction, t));
		v_from_base = vector_substract(hit_point, c.base);
		height_on_axis = vector_dot(v_from_base, c.dir);
		if (height_on_axis >= 0 && height_on_axis <= c.height)
			return (t);
	}
	return (-1.0);
}

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
